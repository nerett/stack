#include "stack.h"


int main()
{
	Stack some_stack;
	StackCtor( &some_stack );
//printf( "dataptr_in_main=%d\n", some_stack.data );

	stack_push( &some_stack, 1 );
//printf( "dataptr_in_main=%d\n", some_stack.data );
	stack_push( &some_stack, 2 );
//printf( "dataptr_in_main=%d\n", some_stack.data );
	stack_push( &some_stack, 3 );
	stack_push( &some_stack, 4 );
	stack_push( &some_stack, 5 );
	stack_push( &some_stack, 6 );
	stack_push( &some_stack, 7 );
	stack_push( &some_stack, 8 );
	stack_push( &some_stack, 9 );
	stack_push( &some_stack, 10 );
//printf( "dataptr_in_main=%d\n", some_stack.data );
//printf( "N_element=%d ", some_stack.N_element );
	printf("pop=%d\n", stack_pop( &some_stack ));

//stack_pop( &some_stack );
//printf( "N_element=%d ", some_stack.N_element );
	printf("pop=%d\n", stack_pop( &some_stack ));
//printf( "N_element=%d ", some_stack.N_element );
	printf("pop=%d\n", stack_pop( &some_stack ));
//printf( "N_element=%d ", some_stack.N_element );
	printf("pop=%d\n", stack_pop( &some_stack ));

//printf("--------------------\n" );
	printf("pop=%d\n", stack_pop( &some_stack ));
	printf("pop=%d\n", stack_pop( &some_stack ));
	printf("pop=%d\n", stack_pop( &some_stack ));
	printf("pop=%d\n", stack_pop( &some_stack ));
	printf("pop=%d\n", stack_pop( &some_stack ));
	printf("pop=%d\n", stack_pop( &some_stack ));
	printf("pop=%d\n", stack_pop( &some_stack ));
	printf("pop=%d\n", stack_pop( &some_stack ));

	StackDtor( &some_stack );
    return 0;
}
