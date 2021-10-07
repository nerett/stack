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
	printf("[10]pop=%d\n", stack_pop( &some_stack )); //10

//stack_pop( &some_stack );
//printf( "N_element=%d ", some_stack.N_element );
	printf("[9]pop=%d\n", stack_pop( &some_stack )); //9
//printf( "N_element=%d ", some_stack.N_element );
	printf("[8]pop=%d\n", stack_pop( &some_stack )); //8
//printf( "N_element=%d ", some_stack.N_element );
	printf("[7]pop=%d\n", stack_pop( &some_stack )); //7
printf("max_capacity=%d\n", some_stack.max_capacity);
//printf("--------------------\n" );
	printf("[6]pop=%d\n", stack_pop( &some_stack )); //6
printf("max_capacity=%d\n", some_stack.max_capacity);
	printf("[5]pop=%d\n", stack_pop( &some_stack )); //5
printf("max_capacity=%d\n", some_stack.max_capacity);
//printf("!!!\n");
	printf("[4]pop=%d\n", stack_pop( &some_stack )); //4
printf("max_capacity=%d\n", some_stack.max_capacity);
	printf("[3]pop=%d\n", stack_pop( &some_stack )); //3
printf("max_capacity=%d\n", some_stack.max_capacity);
	printf("[2]pop=%d\n", stack_pop( &some_stack )); //2
printf("max_capacity=%d\n", some_stack.max_capacity);
	printf("[1]pop=%d\n", stack_pop( &some_stack )); //1
printf("max_capacity=%d\n", some_stack.max_capacity);
	printf("[NO]pop=%d\n", stack_pop( &some_stack )); //////////////
printf("max_capacity=%d\n", some_stack.max_capacity);
	printf("[NO]pop=%d\n", stack_pop( &some_stack )); ////////////

	StackDtor( &some_stack );
    return 0;
}
