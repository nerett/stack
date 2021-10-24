#ifndef CONFIG_H_INCLUDED
#define CONFIG_H_INCLUDED


//#include "stack.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


static const size_t MAXIMUM_ELEMENT_SIZE = 100;

typedef int stk_element_t; //!!!

char* int_array_dump( stk_element_t* data, int N_element );
/*
{
	assert( data );

	char* dump_string = ( char* )calloc( N_element * 100, sizeof( int ) ); //!TODO убрать magicnumber
	for( int i = 0; i < N_element; i++ )
	{
		//dump_string[];
		sprintf( dump_string, "%d ", data[i] );
	}

	return dump_string;
}
*/


#endif //CONFIG_H_INCLUDED
