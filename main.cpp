#include "stack.h"


int main()
{
	remake_log();
	Stack some_stack;
	StackCtor( &some_stack );
//printf( "dataptr_in_main=%d\n", some_stack.data );

	stack_push( &some_stack, 125 );
	stack_push( &some_stack, 3 );
	stack_push( &some_stack, 533 );

	stack_push( &some_stack, stack_pop( &some_stack ) + stack_pop( &some_stack ) ); //add
	stack_push( &some_stack, stack_pop( &some_stack ) + stack_pop( &some_stack ) ); //add

	stack_push( &some_stack, 81939131 );
	stack_push( &some_stack, 81939131 );
	stack_push( &some_stack, 81939131 );
	stack_push( &some_stack, 81939131 );
	stack_push( &some_stack, 81939131 );
	stack_push( &some_stack, 81939131 );
	stack_push( &some_stack, 81939131 );
	stack_push( &some_stack, 81939131 );
	stack_push( &some_stack, 81939131 );
	stack_push( &some_stack, 81939131 );
	stack_push( &some_stack, 81939131 );
	stack_push( &some_stack, 81939131 );
	stack_push( &some_stack, 81939131 );

	stack_pop( &some_stack );
	stack_pop( &some_stack );
	stack_pop( &some_stack );
	stack_pop( &some_stack );
	stack_pop( &some_stack );
	stack_pop( &some_stack );
	stack_pop( &some_stack );

	stack_push( &some_stack, 81939131 );
	stack_push( &some_stack, 81939131 );
	stack_push( &some_stack, 81939131 );
	stack_push( &some_stack, 81939131 );
	stack_push( &some_stack, 81939131 );

	stack_pop( &some_stack );
	stack_pop( &some_stack );
	stack_pop( &some_stack );

	stack_pop( &some_stack );
	stack_pop( &some_stack );
	stack_pop( &some_stack );
	stack_pop( &some_stack );
	stack_pop( &some_stack );
	stack_pop( &some_stack );
	stack_pop( &some_stack );
	stack_pop( &some_stack );
	stack_pop( &some_stack );
	stack_pop( &some_stack );
	stack_pop( &some_stack );
	stack_pop( &some_stack );
	stack_pop( &some_stack );
	stack_pop( &some_stack );
	stack_pop( &some_stack );
	stack_pop( &some_stack );
	stack_pop( &some_stack );
	stack_pop( &some_stack );
	stack_pop( &some_stack );
	stack_pop( &some_stack );
	stack_pop( &some_stack );
	stack_pop( &some_stack );
	stack_pop( &some_stack );
	stack_pop( &some_stack );
	stack_pop( &some_stack );
	stack_pop( &some_stack );
	stack_pop( &some_stack );
	stack_pop( &some_stack );
	stack_pop( &some_stack );
	

	printf("result=%d\n", stack_pop( &some_stack ) );

/*
	stack_dump( &some_stack, CALLOC_ERROR ); //DEBUG TEST
	stack_dump( &some_stack, OK ); //DEBUG TEST
	stack_dump( &some_stack, FOPEN_ERROR ); //DEBUG TEST
	stack_dump( &some_stack, INVALID_DATA_PTR ); //DEBUG TEST
	stack_dump( &some_stack, REALLOCATION_ERROR ); //DEBUG TEST
*/

	StackDtor( &some_stack );
    return 0;
}
