#include "config.h"

char* int_array_dump( stk_element_t* data, int N_element )
{
	assert( data );


	char* dump_string = ( char* )calloc( N_element * MAXIMUM_ELEMENT_SIZE, sizeof( int ) ); //!TODO убрать magicnumber
	for( int i = 0; i <= N_element; i++ )
	{
		//strcpy( dump_string, ( const char* )data[i] );
		//dump_string[];
		sprintf( dump_string + strlen( dump_string ), "%d ", data[i] );
//printf("%TEST DATA PRINTING %d \n", data[i] );
	}
	//strcpy( dump_string, "\0" );

printf("DUMP_STRING IN USER FUNCTION = %s\n", dump_string );
	return dump_string;
}
