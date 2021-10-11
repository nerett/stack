#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

typedef int stk_element_t; //!!!

enum err_code { OK, NO_ELEMENTS_TO_POP, CALLOC_ERROR, INVALID_DATA_PTR, REALLOCATION_ERROR, FOPEN_ERROR, N_ELEMENT_MORE_CAPACITY, INVALID_UP_RESIZE_COEFF, INVALID_DOWN_RESIZE_COEFF, STACK_IS_NOT_CONSTRUCTED };

#define error_output( error_variable, possible_error_type ) do { \
    if( error_variable != NULL )                                 \
	{                                                            \
		*error_variable = possible_error_type;                   \
	}                                                            \
} while(0)

#define void_check_errors( error_variable ) do {                       \
    if( error_variable != NULL )                                       \
  	{                                                                  \
  		if( *error_variable != OK )                                    \
		{                                                              \
			return;                                                    \
		}                                                              \
  	}                                                                  \
} while(0)

#define int_check_errors( error_variable ) do {                      \
   if( error_variable != NULL )                                      \
   {                                                                 \
	   if( *error_variable != OK )                                   \
	   {                                                             \
		   return {};                                                \
	   }                                                             \
   }                                                                 \
} while(0)

const size_t START_CAPACITY = 8;
const int INT_POISON = 0; //TODO поменять на нормальный яд (или заставить пользователя создать его)

struct Stack //чтобы использовать стек надо после его создания вызвать конструктор; после вызова деструктора стек можно пересоздать и использовать заново;
{
    int max_capacity = 0; //size_t
    int N_element = -1;

	stk_element_t* data = NULL;

    double up_resize_coeff = 0;
    double down_resize_coeff = 0;
    //double smoothing_downsize_coeff = 0;

	bool is_initialized = false; //! static
};

void StackCtor( Stack* some_stack, err_code* error_variable = NULL );
void StackDtor( Stack* some_stack, err_code* error_variable = NULL );

void stack_push( Stack* some_stack, stk_element_t value, err_code* error_variable = NULL );
stk_element_t stack_pop( Stack* some_stack, err_code* error_variable = NULL );
static void stack_resize( Stack* some_stack, err_code* error_variable = NULL );

//static void init_stack( Stack* some_stack, err_code* error_variable = NULL );

static void calc_upsize_coeff( Stack* some_stack );
static void calc_downsize_coeff( Stack* some_stack );
static double calc_smoothing_downsize_coeff( const Stack* some_stack );

static void upsize_stack( Stack* some_stack, err_code* error_variable = NULL );
static void downsize_stack( Stack* some_stack, err_code* error_variable = NULL );

static bool validate_stack( Stack* some_stack, err_code* error_variable = NULL ); //< Returns true, if stack is OK
void stack_dump( Stack* some_stack, err_code stack_error ,err_code* error_variable = NULL );
void remake_log( err_code* error_variable = NULL );
//static void upsize_stack( Stack* some_stack, err_code* error_variable = NULL );
//static void downsize_stack( Stack* some_stack, err_code* error_variable = NULL );


#endif // STACK_H_INCLUDED
