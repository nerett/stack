#include "stack.h"



void stack_push( Stack* some_stack, int value, err_code* error_variable ) //есть какая-то ошибка памяти
{
	assert( some_stack );

/*
	if( error_variable == NULL ) //функция
	{
		//error_variable = ( err_code* )calloc( error_variable, 1, sizeof( err_code ) );
	}
*/
//printf( "[FUNC_CALL]stack_push \n" );
	//err_code error_variable = OK;

	if( some_stack->is_initialized == false )
	{
		return;
	}

    stack_resize( some_stack, error_variable );
	if( error_variable != NULL && *error_variable != OK ) //макрос
	{
		return;
	}

	some_stack->N_element++;

	//не знаю, нужна ли проверка N_element < max_capacity
	some_stack->data[some_stack->N_element] = value;

	//free( error_variable );
}



int stack_pop( Stack* some_stack, err_code* error_variable ) //!TODO ошибка запроса нулевого элемента стека
{
	assert( some_stack );


//printf( "[FUNC_CALL]stack_pop \n" );
//printf("N_element=%d\n", some_stack->N_element );
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
		if( error_variable != NULL )
		{
			*error_variable = NO_ELEMENTS_TO_POP;
		}
		return {};
	}

	int return_value = some_stack->data[some_stack->N_element];
	some_stack->data[some_stack->N_element] = INT_POISON;
	some_stack->N_element--;

	stack_resize( some_stack, error_variable );
	if( error_variable != NULL && *error_variable != OK ) //макрос
	{
		return {};
	}

	//free( error_variable );
	return return_value;
}



static void stack_resize( Stack* some_stack, err_code* error_variable )
{
	assert( some_stack );


//printf( "[FUNC_CALL]stack_resize \n" );
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

	if( error_variable != NULL && *error_variable != OK )
	{
		return;
	}
    ///stack_size
}


/*
static void init_stack( Stack* some_stack, err_code* error_variable )
{
    some_stack->data = ( int* )calloc( START_NUMBER_OF_ELEMENTS, sizeof( int ) );
}
*/


static void calc_upsize_coeff( Stack* some_stack )
{
	assert( some_stack );
//printf( "[FUNC_CALL]calc_upsize_coeff \n" );
	some_stack->up_resize_coeff = 2; //! HARDCODE
}



static void calc_downsize_coeff( Stack* some_stack )
{
	assert( some_stack );
//printf( "[FUNC_CALL]calc_downsize_coeff \n" );
	some_stack->down_resize_coeff = 0.5; //! HARDCODE
}



static double calc_smoothing_downsize_coeff( const Stack* some_stack )
{
	assert( some_stack );
//printf( "[FUNC_CALL]calc_smoothing_downsize_coeff \n" );
	return 0.2; //! HARDCODE
}



void StackCtor( Stack* some_stack, err_code* error_variable )
{
	assert( some_stack );
//printf( "[FUNC_CALL]StackCtor \n" );
	if( some_stack->is_initialized )
	{
		return; //! переделать
	}

	some_stack->max_capacity = START_CAPACITY; // проверить после каллока
	some_stack->data = ( int* )calloc( some_stack->max_capacity, sizeof( int ) ); //я не знаю, почему, но все ошибки valgrind исчезли после +1
	if( some_stack->data == NULL )
	{
		if( error_variable != NULL )
		{
			*error_variable = CALLOC_ERROR;
		}
		return;
	}

    int N_element = -1;
    double up_resize_coeff = 0;
    double down_resize_coeff = 0;
    //double smoothing_downsize_coeff = 0

	some_stack->is_initialized = true;

}



void StackDtor( Stack* some_stack, err_code* error_variable )
{
	assert( some_stack );


//printf( "[FUNC_CALL]StackDtor \n" );
	if( !some_stack->is_initialized )
	{
		return;
	}


	if( some_stack->data == NULL )
	{
		if( error_variable != NULL )
		{
			*error_variable = INVALID_DATA_PTR;
		}
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


//printf( "[FUNC_CALL]upsize_stack \n" );
	some_stack->max_capacity *= some_stack->up_resize_coeff;
//printf("MAXCAPACITY=%d \n", some_stack->max_capacity );

	void* realloc_buffer = ( int* )realloc( some_stack->data, sizeof( int ) * some_stack->max_capacity ); //! recalloc
	if( realloc_buffer != NULL ) //макрос или функция
	{
		some_stack->data = ( int* )realloc_buffer; //потом можно будет перенести на создание
	}
	else
	{
		if( error_variable != NULL )
		{
			*error_variable = REALLOCATION_ERROR;
		}
		return;
	}
	//some_stack->data = ( int* )realloc( some_stack->data, some_stack->max_capacity * some_stack->up_resize_coeff ); //! recalloc

}



void downsize_stack( Stack* some_stack, err_code* error_variable )
{
	assert( some_stack );
//printf( "[FUNC_CALL]downsize_stack\n" );
	some_stack->max_capacity *= some_stack->down_resize_coeff;
//printf("downsize:max_capacity=%d\n", some_stack->max_capacity );
	void* realloc_buffer = ( int* )realloc( some_stack->data, sizeof( int ) * some_stack->max_capacity );
	if( realloc_buffer != NULL )
	{
		some_stack->data = ( int* )realloc_buffer;
	}
	else
	{
		if( error_variable != NULL )
		{
			*error_variable = REALLOCATION_ERROR;
		}
		return;
	}
}
