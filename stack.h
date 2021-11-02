#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <malloc.h>///
#include "config.h"


//typedef int stk_element_t; //!!!
typedef char* ( user_dump )( stk_element_t* data, int N_elements );

enum err_code
{
	OK = 0,
	NO_ELEMENTS_TO_POP = 1,
	CALLOC_ERROR = 2,
	INVALID_DATA_PTR = 3,
	REALLOCATION_ERROR = 4,
	FOPEN_ERROR = 5,
	N_ELEMENT_MORE_CAPACITY = 6,
	INVALID_UP_RESIZE_COEFF = 7,
	INVALID_DOWN_RESIZE_COEFF = 8,
	STACK_IS_NOT_CONSTRUCTED = 9,
	INVALID__USER_TYPE_DUMP_STRING_PTR = 10,
	#ifndef NDEBUG
		LEFT_STRUCT_CANARY_DIED = 11,
		RIGHT_STRUCT_CANARY_DIED = 12,
		LEFT_DATA_CANARY_DIED = 13,
		RIGHT_DATA_CANARY_DIED = 14,
		DATA_HASH_SETTING_ERROR = 15,
		INVALID_DATA_HASH
	#endif
};

/*
char err_code_interpretation[10] = {
	"OK",
	"NO_ELEMENTS_TO_POP",
	"CALLOC_ERROR",
	"INVALID_DATA_PTR",
	"REALLOCATION_ERROR",
	"FOPEN_ERROR",
	"N_ELEMENT_MORE_CAPACITY",
	"INVALID_UP_RESIZE_COEFF",
	"INVALID_DOWN_RESIZE_COEFF",
	"STACK_IS_NOT_CONSTRUCTED",
	"INVALID__USER_TYPE_DUMP_STRING_PTR"
};
*/    // not working:(                                                        \

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

#define validate_dump( some_stack, error_variable ) do {                                                  \
		err_code stack_error = OK;                                                                        \
		validate_stack( some_stack, &stack_error );                                                       \
		stack_dump( some_stack, stack_error, __FILE__, __PRETTY_FUNCTION__, __LINE__, error_variable );   \
	} while(0)


const size_t START_CAPACITY = 8; //8
const unsigned long long CANARY = 0xAB0BAB0BAB0BAB0B;
const int INT_POISON = 0; //TODO поменять на нормальный яд (или заставить пользователя создать его)

const int START_HASH_KEY = 0;
#ifdef NDEBUG
	const int N_CANARIES = 0;
	const int DATA_PTR_OFFSET = 0;
	const int N_ELEMENT_OFFSET = 0;
#endif
#ifndef NDEBUG
	const int N_CANARIES = 2;
	const int DATA_PTR_OFFSET = 1;
	const int N_ELEMENT_OFFSET = 1;
#endif


struct Stack //чтобы использовать стек надо после его создания вызвать конструктор; после вызова деструктора стек можно пересоздать и использовать заново;
{
	#ifndef NDEBUG
		unsigned long long left_struct_canary = CANARY;
	#endif


    int max_capacity = 0; //size_t
    int N_element = -1;

	stk_element_t* data = NULL;

    double up_resize_coeff = 0;
    double down_resize_coeff = 0;
    //double smoothing_downsize_coeff = 0;

	//!TODO указатель на функцию дампа данных
	user_dump* user_type_dump_function = NULL;

	bool is_initialized = false; //! static


	#ifndef NDEBUG
		int data_hash = 0;

		unsigned long long right_struct_canary = CANARY;
	#endif
};

void StackCtor( Stack* some_stack, user_dump* user_type_dump_function = NULL, err_code* error_variable = NULL );
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
static void reallocate_stack( Stack* some_stack, err_code* error_variable );

static bool validate_stack( Stack* some_stack, err_code* error_variable = NULL ); //< Returns true, if stack is OK
void stack_dump( Stack* some_stack, err_code stack_error, const char* error_filename, const char* error_function, int error_line, err_code* error_variable = NULL );
void remake_log( err_code* error_variable = NULL );

static void set_data_canaries( Stack* some_stack );
static unsigned long long struct_canary_x_ptr( unsigned long long* canary_ptr );
static stk_element_t data_canary_x_ptr( stk_element_t* stack_data, int offset );
static bool check_struct_canary( unsigned long long* canary_ptr );
static bool check_data_canary( stk_element_t* stack_data, int offset );
static void set_stack_data_hash( Stack* some_stack, err_code* error_variable = NULL );
int xor_hash( stk_element_t* data, int N_elements );

//void set_canary(  );
//static void upsize_stack( Stack* some_stack, err_code* error_variable = NULL );
//static void downsize_stack( Stack* some_stack, err_code* error_variable = NULL );


#endif // STACK_H_INCLUDED
