#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

enum err_code { OK, NO_ELEMENTS_TO_POP, CALLOC_ERROR, INVALID_DATA_PTR, REALLOCATION_ERROR };

const size_t START_CAPACITY = 1;
const int INT_POISON = 0;

struct Stack //чтобы использовать стек надо после его создания вызвать конструктор; после вызова деструктора стек можно пересоздать и использовать заново;
{
    int* data = NULL;
    int max_capacity = 0; //size_t
    int N_element = -1;

    double up_resize_coeff = 0;
    double down_resize_coeff = 0;
    //double smoothing_downsize_coeff = 0;

	bool is_initialized = false; //! static
};

void StackCtor( Stack* some_stack, err_code* error_variable = NULL );
void StackDtor( Stack* some_stack, err_code* error_variable = NULL );

void stack_push( Stack* some_stack, int value, err_code* error_variable = NULL );
int stack_pop( Stack* some_stack, err_code* error_variable = NULL );
static void stack_resize( Stack* some_stack, err_code* error_variable = NULL );
static void init_stack( Stack* some_stack, err_code* error_variable = NULL );
static void calc_upsize_coeff( Stack* some_stack );
static void calc_downsize_coeff( Stack* some_stack );

static void upsize_stack( Stack* some_stack, err_code* error_variable = NULL );
static void downsize_stack( Stack* some_stack, err_code* error_variable = NULL );

static double calc_smoothing_downsize_coeff( const Stack* some_stack );

//static void upsize_stack( Stack* some_stack, err_code* error_variable = NULL );
//static void downsize_stack( Stack* some_stack, err_code* error_variable = NULL );


#endif // STACK_H_INCLUDED
