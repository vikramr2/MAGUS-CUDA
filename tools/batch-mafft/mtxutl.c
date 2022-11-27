#include <stdlib.h>
#include <stddef.h>

void FreeCharMtx( char **mtx )
{
	int i;
	for( i=0; mtx[i]; i++ ) 
	{
		free( mtx[i] );
	}
	free( mtx );
}

char *AllocateCharVec( int l1 )
{
	char *cvec;
	
	cvec = (char *)calloc( l1, sizeof( char ) );
	if (!cvec) exit( 1 );
	return( cvec );
}

char **AllocateCharMtx( int l1, int l2 )
{
	int i;
	char **cmtx;
	
	cmtx = (char **)calloc( l1+1, sizeof( char * ) );
	if( cmtx == NULL ) exit( 1 );

	if( l2 )
	{
		for( i=0; i<l1; i++ ) 
		{
			cmtx[i] = AllocateCharVec( l2 );
		}
	}
	cmtx[l1] = NULL;
	return( cmtx );
} 

int *AllocateIntVec( int ll1 )
{
	int *vec;

	vec = (int *)calloc( ll1, sizeof( int ) );
	if( vec == NULL ) exit( 1 );
	return( vec );
}	