#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <my_global.h>
#include <my_sys.h>
#include <mysql.h>
#include <ctype.h>
#include "gost_f.h"



char * gost512(UDF_INIT *initid, UDF_ARGS *args, char *result, unsigned long *length, char *is_null, char *error)
{	
	char *M;
	unsigned char *h;
	
	*length=args->lengths[0];
	memcpy(result, args->args[0],*length);
	memcpy(M,result,*length);
	long long M_length=*length*8;
	unsigned char IV[64] =
	{
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
		
	};

	h = calc_hash(M,M_length,IV);
	unsigned char res[128];
	unsigned char hex_str[]= "0123456789abcdef";
	for(int i=0;i<64;i++)
	{
		res[i*2+0]=hex_str[(h[i] >> 4) & 0x0F];
		res[i*2+1]=hex_str[(h[i] ) & 0x0F];
	}
	*length=128;
	memcpy(result, res,*length);
	result[*length]= 0;
	return result;
}


my_bool gost512_init (UDF_INIT *initid, UDF_ARGS *args, char *message)
{
	if(args->arg_count != 1)
	{
		strcpy(message, "hello requires exactly one string argument");
		return 1;
	}
	if(args->arg_type[0] != STRING_RESULT)
	{
		strcpy(message, "hello requires exactly one string argument");
		return 1;
	}

	
	return 0; /* true */
}

void gost512_deinit (UDF_INIT *initid)
{
	;
}


char * gost256(UDF_INIT *initid, UDF_ARGS *args, char *result, unsigned long *length, char *is_null, char *error)
{	
	char *M;
	unsigned char *h;
	*length=args->lengths[0];
	memcpy(result, args->args[0],*length);
	memcpy(M,result,*length);
	long long M_length=*length*8;
	

	unsigned char IV[64] = 
	{
		0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
		0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
		0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
		0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01
	};

	h = calc_hash(M,M_length,IV);
	unsigned char res[128];
	unsigned char hex_str[]= "0123456789abcdef";
	for(int i=0;i<64;i++)
	{
		res[i*2+0]=hex_str[(h[i] >> 4) & 0x0F];
		res[i*2+1]=hex_str[(h[i] ) & 0x0F];
	}
	*length=64;
	memcpy(result, res,*length);
	result[*length]= 0;
	return result;
}



my_bool gost256_init (UDF_INIT *initid, UDF_ARGS *args, char *message)
{
	if(args->arg_count != 1)
	{
		strcpy(message, "hello requires exactly one string argument");
		return 1;
	}
	if(args->arg_type[0] != STRING_RESULT)
	{
		strcpy(message, "hello requires exactly one string argument");
		return 1;
	}

	
	return 0; /* true */
}

void gost256_deinit (UDF_INIT *initid)
{
	;
}

