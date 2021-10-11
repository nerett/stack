#include "stack.h"



void stack_push( Stack* some_stack, stk_element_t value, err_code* error_variable ) //есть какая-то ошибка памяти
{
	assert( some_stack );


	if( some_stack->is_initialized == false )
	{
		return;
	}

    stack_resize( some_stack, error_variable );
	void_check_errors( error_variable );

	some_stack->N_element++;

	//не знаю, нужна ли проверка N_element < max_capacity
	some_stack->data[some_stack->N_element] = value;
}



stk_element_t stack_pop( Stack* some_stack, err_code* error_variable ) //!TODO ошибка запроса нулевого элемента стека
{
	assert( some_stack );


	if( !some_stack->is_initialized )
	{
		return {};
	}
	if( some_stack->N_element < 0 )
	{
		return {};
	}

	if( some_stack->max_capacity < some_stack->N_element )
	{
		error_output( error_variable, NO_ELEMENTS_TO_POP );
		return {};
	}

	stk_element_t return_value = some_stack->data[some_stack->N_element];
	some_stack->data[some_stack->N_element] = INT_POISON;
	some_stack->N_element--;

	stack_resize( some_stack, error_variable );
	int_check_errors( error_variable );

	return return_value;
}



static void stack_resize( Stack* some_stack, err_code* error_variable )
{
	assert( some_stack );


	calc_upsize_coeff( some_stack );
	calc_downsize_coeff( some_stack );

    if( some_stack->N_element == some_stack->max_capacity )
    {
        upsize_stack( some_stack, error_variable );
    }
    else if( some_stack->N_element < some_stack->max_capacity * calc_smoothing_downsize_coeff( some_stack ) && some_stack->max_capacity > START_CAPACITY ) //! КОСТЫЛЬ!
    {
		downsize_stack( some_stack, error_variable );
    }

	void_check_errors( error_variable );
}



static void calc_upsize_coeff( Stack* some_stack )
{
	assert( some_stack );
	some_stack->up_resize_coeff = 2; //! HARDCODE
}



static void calc_downsize_coeff( Stack* some_stack )
{
	assert( some_stack );
	some_stack->down_resize_coeff = 0.5; //! HARDCODE
}



static double calc_smoothing_downsize_coeff( const Stack* some_stack )
{
	assert( some_stack );
	return 0.2; //! HARDCODE
}



void StackCtor( Stack* some_stack, err_code* error_variable )
{
	assert( some_stack );
	if( some_stack->is_initialized )
	{
		return; //! переделать
	}

	some_stack->max_capacity = START_CAPACITY; // проверить после каллока
	some_stack->data = ( stk_element_t* )calloc( some_stack->max_capacity, sizeof( stk_element_t ) ); //я не знаю, почему, но все ошибки valgrind исчезли после +1
	if( some_stack->data == NULL )
	{
		error_output( error_variable, CALLOC_ERROR );
		return;
	}

    some_stack->N_element = -1; //FIXED
    some_stack->up_resize_coeff = 0;
    some_stack->down_resize_coeff = 0;
    //double smoothing_downsize_coeff = 0

	some_stack->is_initialized = true;
}



void StackDtor( Stack* some_stack, err_code* error_variable )
{
	assert( some_stack );


	if( !some_stack->is_initialized )
	{
		return;
	}


	if( some_stack->data == NULL )
	{
		error_output( error_variable, INVALID_DATA_PTR );
		return;
	}
	free( some_stack->data );

	some_stack->is_initialized = false;
	some_stack->N_element = 0;
	some_stack->max_capacity = 0;
	some_stack->up_resize_coeff = 0;
	some_stack->down_resize_coeff = 0;
}



void upsize_stack( Stack* some_stack, err_code* error_variable )
{
	assert( some_stack );


	some_stack->max_capacity *= some_stack->up_resize_coeff;

	void* realloc_buffer = ( stk_element_t* )realloc( some_stack->data, sizeof( stk_element_t ) * some_stack->max_capacity ); //! recalloc
	if( realloc_buffer != NULL ) //макрос или функция
	{
		some_stack->data = ( stk_element_t* )realloc_buffer; //потом можно будет перенести на создание
	}
	else
	{
		error_output( error_variable, REALLOCATION_ERROR );
		return;
	}
}



void downsize_stack( Stack* some_stack, err_code* error_variable )
{
	assert( some_stack );


	some_stack->max_capacity *= some_stack->down_resize_coeff;

	void* realloc_buffer = ( stk_element_t* )realloc( some_stack->data, sizeof( stk_element_t ) * some_stack->max_capacity );
	if( realloc_buffer != NULL )
	{
		some_stack->data = ( stk_element_t* )realloc_buffer;
	}
	else
	{
		error_output( error_variable, REALLOCATION_ERROR );
		return;
	}
}



static bool validate_stack( Stack* some_stack, err_code* error_variable )
{
	if( some_stack->is_initialized == false )
	{
		error_output( error_variable, STACK_IS_NOT_CONSTRUCTED );
		return 0;
	}
	if( some_stack->N_element > some_stack->max_capacity )
	{
		error_output( error_variable, N_ELEMENT_MORE_CAPACITY );
		return 0;
	}
	if( some_stack->data == NULL )
	{
		error_output( error_variable, INVALID_DATA_PTR );
		return 0;
	}
	if( some_stack->up_resize_coeff <= 0 )
	{
		error_output( error_variable, INVALID_UP_RESIZE_COEFF );
		return 0;
	}
	if( some_stack->down_resize_coeff <= 0 )
	{
		error_output( error_variable, INVALID_DOWN_RESIZE_COEFF );
		return 0;
	}

	return true;
}



void stack_dump( Stack* some_stack, err_code stack_error, err_code* error_variable ) //! TODO использование пользовательской функции распечатки типа
{
	assert( some_stack );


	FILE* logfile = fopen( "stack_log.html", "a" );
	if( logfile == NULL )
	{
		error_output( error_variable, FOPEN_ERROR );
		return;
	}

	fprintf( logfile , "<font color=\"purple\">[STACK_DUMP]</font> " );
	if( stack_error == OK )
	{
		fprintf( logfile , "<font color=\"green\">[OK]</font>  \n" );
	}
	else
	{
		fprintf( logfile, "<font color=\"red  \">[ERROR] stack_error_code = %d</font>\n", stack_error );
		fprintf( logfile, "    struct Stack\n" );
		fprintf( logfile, "    {\n" );
		fprintf( logfile, "        max_capacity = %d\n", some_stack->max_capacity );
		fprintf( logfile, "        N_element = %d\n", some_stack->N_element );
		fprintf( logfile, "        *data = 0x%p\n", some_stack->data );
		fprintf( logfile, "        up_resize_coeff = %f\n", some_stack->up_resize_coeff );
		fprintf( logfile, "        down_resize_coeff = %f\n", some_stack->down_resize_coeff );
		fprintf( logfile, "        is_initialized = %d\n", some_stack->is_initialized );
		fprintf( logfile, "    };\n" );
	}
	fclose( logfile );
}



void remake_log( err_code* error_variable )
{
	FILE* logfile = fopen( "stack_log.html", "w" );
	if( logfile == NULL )
	{
		error_output( error_variable, FOPEN_ERROR );
		return;
	}

	fputs( "<pre>", logfile );
	fclose( logfile );
}
