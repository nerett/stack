#include "stack.h"



void stack_push( Stack* some_stack, int value, err_code* error_variable )
{
	if( some_stack->is_initialized == false )
	{
		return;
	}

    stack_resize( some_stack );

	some_stack->N_element++;

	some_stack->data[some_stack->N_element] = value;
}



int stack_pop( Stack* some_stack, err_code* error_variable ) //!TODO ошибка запроса нулевого элемента стека
{
	if( !some_stack->is_initialized )
	{
		return {};
	}
	if( some_stack->N_element == 0 )
	{
		return {};
	}

	int return_value = some_stack->data[some_stack->N_element];
	some_stack->data[some_stack->N_element] = INT_POISON;
	some_stack->N_element--;

	stack_resize( some_stack );

	return return_value;
}



static void stack_resize( Stack* some_stack, err_code* error_variable )
{
	calc_upsize_coeff( some_stack );
	calc_downsize_coeff( some_stack );

    if( some_stack->N_element == some_stack->max_capacity )
    {
        upsize_stack( some_stack );
    }
    else if( some_stack->N_element < some_stack->max_capacity * calc_smoothing_downsize_coeff( some_stack ) && some_stack->max_capacity > START_CAPACITY ) //! КОСТЫЛЬ!
    {
		downsize_stack( some_stack );
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
	some_stack->up_resize_coeff = 2; //! HARDCODE
}



static void calc_downsize_coeff( Stack* some_stack )
{
	some_stack->down_resize_coeff = 0,5; //! HARDCODE
}



static double calc_smoothing_downsize_coeff( const Stack* some_stack )
{
	return 0.2; //! HARDCODE
}



void StackCtor( Stack* some_stack, err_code* error_variable )
{
	if( some_stack->is_initialized )
	{
		return; //! переделать
	}

	some_stack->max_capacity = START_CAPACITY; // проверить после каллока
	some_stack->data = ( int* )calloc( some_stack->max_capacity, sizeof( int ) );

    int N_element = -1;
    double up_resize_coeff = 0;
    double down_resize_coeff = 0;
    //double smoothing_downsize_coeff = 0

	some_stack->is_initialized = true;

}



void StackDtor( Stack* some_stack, err_code* error_variable )
{
	if( !some_stack->is_initialized )
	{
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
	some_stack->data = ( int* )realloc( some_stack->data, some_stack->max_capacity * some_stack->up_resize_coeff ); //! recalloc
}



void downsize_stack( Stack* some_stack, err_code* error_variable )
{
	some_stack->data = ( int* )realloc( some_stack->data, some_stack->max_capacity * some_stack->down_resize_coeff );
}
