#ifndef CONFIG_H_INCLUDED
#define CONFIG_H_INCLUDED


#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


static const size_t MAXIMUM_ELEMENT_SIZE = 100;

typedef int stk_element_t; //!!!

char* int_array_dump( stk_element_t* data, int N_element );


#endif //CONFIG_H_INCLUDED
