#include "config.h"

char* int_array_dump( stk_element_t* data, int N_element )
{
	assert( data );


	char* dump_string = ( char* )calloc( N_element * MAXIMUM_ELEMENT_SIZE, sizeof( int ) ); //!TODO убрать magicnumber
	for( int i = 0; i <= N_element; i++ )
	{
		sprintf( dump_string + strlen( dump_string ), "%d ", data[i] );
	}

	return dump_string;
}
