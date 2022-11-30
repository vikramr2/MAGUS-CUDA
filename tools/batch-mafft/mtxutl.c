#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

void MtxuntDouble( double **mtx, int n )
{
    int i, j;
    for( i=0; i<n; i++ ) for( j=0; j<n; j++ ) mtx[i][j] = 0.0;
    for( i=0; i<n; i++ ) mtx[i][i] = 1.0;
}

void MtxmltDouble( double **mtx1, double **mtx2, int n )
{
    int i, j, k;
    double s, *tmp;

	tmp = (double *)calloc( n, sizeof( double ) );
    for( i=0; i<n; i++ ) 
    {
        for( k=0; k<n; k++ ) tmp[k] = mtx1[i][k];
        for( j=0; j<n; j++ ) 
        {
            s = 0.0;
            for( k=0; k<n; k++ ) s += tmp[k] * mtx2[k][j];
            mtx1[i][j] = s;
        }
    }
	free( tmp );
}

char *AllocateCharVec( int l1 )
{
	char *cvec;
	
	cvec = (char *)calloc( l1, sizeof( char ) );
	if( cvec == NULL )
	{
		fprintf( stderr, "Cannot allocate %d character vector.\n", l1 );
		exit( 1 );
	}
	return( cvec );
}
	
void ReallocateCharMtx( char **mtx, int l1, int l2 )
{
	int i;
	for( i=0; i<l1; i++ ) 
	{
		mtx[i] = (char *)realloc( mtx[i], (l2+1) * sizeof( char ) );
		if( mtx[i] == NULL )
		{
			fprintf( stderr, "Cannot reallocate %d x %d character matrix.\n", l1, l2 );
		}
	}
}

char **AllocateCharMtx( int l1, int l2 )
{
	int i;
	char **cmtx;
	
	cmtx = (char **)calloc( l1+1, sizeof( char * ) );
	if( cmtx == NULL )
	{
		fprintf( stderr, "Cannot allocate %d x %d character matrix.\n", l1, l2 );
		exit( 1 );
	}   
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

void FreeCharMtx( char **mtx )
{
	int i;
	for( i=0; mtx[i]; i++ ) 
	{
		free( mtx[i] );
	}
	free( mtx );
}

double *AllocateFloatVec( int l1 )
{
	double *vec;

	vec = (double *)calloc( (unsigned int)l1, sizeof( double ) );
	if( vec == NULL )
	{
		fprintf( stderr, "Allocation error ( %d fload vec )\n", l1 );
		exit( 1 );
	}
	return( vec );
}

void FreeFloatVec( double *vec )
{
	free( (char *)vec );
}

double **AllocateFloatHalfMtx( int ll1 )
{
	double **mtx;
	int i;

	mtx = (double **)calloc( (unsigned int)ll1+1, sizeof( double * ) );
	if( mtx == NULL )
	{
		fprintf( stderr, "Allocation error ( %d fload halfmtx )\n", ll1 );
		exit( 1 );
	}
	for( i=0; i<ll1; i++ )
	{
		mtx[i] = (double *)calloc( ll1-i, sizeof( double ) );
		if( !mtx[i] )
		{
			fprintf( stderr, "Allocation error( %d doublehalfmtx )\n", ll1 );
			exit( 1 );
		}
	}
	mtx[ll1] = NULL;
	return( mtx );
}

double **AllocateFloatMtx( int ll1, int ll2 )
{
	double **mtx;
	int i;

	mtx = (double **)calloc( (unsigned int)ll1+1, sizeof( double * ) );
	if( mtx == NULL )
	{
		fprintf( stderr, "Allocation error ( %d x %d fload mtx )\n", ll1, ll2 );
		exit( 1 );
	}
	if( ll2 )
	{
		for( i=0; i<ll1; i++ )
		{
			mtx[i] = (double *)calloc( ll2, sizeof( double ) );
			if( !mtx[i] )
			{
				fprintf( stderr, "Allocation error( %d x %d doublemtx )\n", ll1, ll2 );
				exit( 1 );
			}
		}
	}
	mtx[ll1] = NULL;
	return( mtx );
}

void FreeFloatHalfMtx( double **mtx, int n )
{
	int i;

	for( i=0; i<n; i++ ) 
	{
		if( mtx[i] ) FreeFloatVec( mtx[i] ); mtx[i] = NULL;
	}
	free( mtx );
}
void FreeFloatMtx( double **mtx )
{
	int i;

	for( i=0; mtx[i]; i++ ) 
	{
		if( mtx[i] ) FreeFloatVec( mtx[i] ); mtx[i] = NULL;
	}
	free( mtx );
}

int *AllocateIntVecLarge( unsigned long long ll1 )
{
	int *vec;

	vec = (int *)calloc( ll1, sizeof( int ) );
	if( vec == NULL )
	{	
		fprintf( stderr, "Allocation error( %lld int vec )\n", ll1 );
		exit( 1 );
	}
	return( vec );
}	

int *AllocateIntVec( int ll1 )
{
	int *vec;

	vec = (int *)calloc( ll1, sizeof( int ) );
	if( vec == NULL )
	{	
		fprintf( stderr, "Allocation error( %d int vec )\n", ll1 );
		exit( 1 );
	}
	return( vec );
}	

void FreeIntVec( int *vec )
{
	free( (char *)vec );
}

double **AllocateFloatTri( int ll1 )
{
	double **tri;
	int i;

	tri = (double **)calloc( (unsigned int)ll1+1, sizeof( double * ) );
	if( !tri )
	{
		fprintf( stderr, "Allocation error ( double tri )\n" );
		exit( 1 );
	}
	for( i=0; i<ll1; i++ ) 
	{
		tri[i] = AllocateFloatVec( i+3 );
	}
	tri[ll1] = NULL;
		
	return( tri );
}

void FreeFloatTri( double **tri )
{
	int i;
	for( i=0; tri[i]; i++ ) 
		free( tri[i] );
	free( tri );
}
		
int **AllocateIntMtx( int ll1, int ll2 )
{
	int i;
	int **mtx;

	mtx = (int **)calloc( ll1+1, sizeof( int * ) );
	if( !mtx )
	{
		fprintf( stderr, "Allocation error( %d x %d int mtx )\n", ll1, ll2 );
		exit( 1 );
	}
	if( ll2 )
	{
		for( i=0; i<ll1; i++ ) mtx[i] = AllocateIntVec( ll2 );
	}
	else
	{
		for( i=0; i<ll1; i++ ) mtx[i] = NULL;
	}
	mtx[ll1] = NULL;
	return( mtx );
}

int **AllocateIntMtxLarge( unsigned long long ll1, unsigned long long ll2 )
{
	unsigned long long i;
	int **mtx;

	mtx = (int **)calloc( ll1+1, sizeof( int * ) );
	if( !mtx )
	{
		fprintf( stderr, "Allocation error( %lld x %lld int mtx )\n", ll1, ll2 );
		exit( 1 );
	}
	if( ll2 )
	{
		for( i=0; i<ll1; i++ ) mtx[i] = AllocateIntVecLarge( ll2 );
	}
	else
	{
		for( i=0; i<ll1; i++ ) mtx[i] = NULL;
	}
	mtx[ll1] = NULL;
	return( mtx );
}

char ***AllocateCharCub( int ll1, int ll2, int  ll3 )
{
	int i;
	char ***cub;

	cub = (char ***)calloc( ll1+1, sizeof( char ** ) );
	if( !cub ) 
	{
		fprintf( stderr, "Allocation error( %d x %d x %d char cube\n", ll1, ll2, ll3 );
		exit( 1 );
	}
	if( ll2 )
	{
		for( i=0; i<ll1; i++ ) 
		{
			cub[i] = AllocateCharMtx( ll2, ll3 );
		}
	}
	cub[ll1] = NULL;
	return( cub );
}

void FreeCharCub( char ***cub )
{
	int i;

	for( i=0; cub[i]; i++ ) 
	{
		FreeCharMtx( cub[i] );
	}
	free( cub );
}

void freeintmtx( int **mtx, int ll1 )
{
    int i;

    for( i=0; i<ll1; i++ ) free( (char *)mtx[i] );
    free( (char *)mtx );
}
      
void FreeIntMtx( int **mtx )
{
	int i;

	for( i=0; mtx[i]; i++ ) 
	{
		if( mtx[i] ) free( (char *)mtx[i] ); mtx[i] = NULL;
	}
	free( (char *)mtx );
}

char ****AllocateCharHcu( int ll1, int ll2, int ll3, int ll4 )
{
	int i;
	char ****hcu;

	hcu = (char ****)calloc( ll1+1, sizeof( char *** ) );
	if( hcu == NULL ) exit( 1 );
	for( i=0; i<ll1; i++ ) 
		hcu[i] = AllocateCharCub( ll2, ll3, ll4 );
	hcu[ll1] = NULL;
	return( hcu );
}

void FreeCharHcu( char ****hcu )
{
	int i;
	for( i=0; hcu[i]; i++ )
	{
		FreeCharCub( hcu[i] );
	}
	free ( (char *)hcu );
}

double *AllocateDoubleVec( int ll1 )
{
	double *vec;

	vec = (double *)calloc( ll1, sizeof( double ) ); 
	return( vec );
}

void FreeDoubleVec( double *vec )
{
	free( vec );
}

int ***AllocateIntCub( int ll1, int ll2, int ll3 )
{
	int i;
	int ***cub;

	cub = (int ***)calloc( ll1+1, sizeof( int ** ) );
	if( cub == NULL )
	{
		fprintf( stderr, "cannot allocate IntCub\n" );
		exit( 1 );
	}
	for( i=0; i<ll1; i++ ) 
		cub[i] = AllocateIntMtx( ll2, ll3 );
	cub[ll1] = NULL;

	return cub;
}

void FreeIntCub( int ***cub )
{
	int i;
	for( i=0; cub[i]; i++ ) 
	{
		if( cub[i] ) FreeIntMtx( cub[i] ); cub[i] = NULL;
	}
	free( cub );
}

double **AllocateDoubleHalfMtx( int ll1 )
{
	double **mtx;
	int i;

	mtx = (double **)calloc( (unsigned int)ll1+1, sizeof( double * ) );
	if( mtx == NULL )
	{
		fprintf( stderr, "Allocation error ( %d double halfmtx )\n", ll1 );
		exit( 1 );
	}
	for( i=0; i<ll1; i++ )
	{
		mtx[i] = (double *)calloc( ll1-i, sizeof( double ) );
		if( !mtx[i] )
		{
			fprintf( stderr, "Allocation error( %d double halfmtx )\n", ll1 );
			exit( 1 );
		}
	}
	mtx[ll1] = NULL;
	return( mtx );
}

double **AllocateDoubleMtx( int ll1, int ll2 )
{
	int i;
	double **mtx;
	mtx = (double **)calloc( ll1+1, sizeof( double * ) );
	if( !mtx )
	{
		fprintf( stderr, "cannot allocate DoubleMtx\n" );
		exit( 1 );
	}
	if( ll2 )
	{
		for( i=0; i<ll1; i++ ) 
			mtx[i] = AllocateDoubleVec( ll2 );
	}
	mtx[ll1] = NULL;

	return mtx;
}

void FreeDoubleHalfMtx( double **mtx, int n )
{
	int i;

	for( i=0; i<n; i++ ) 
	{
		if( mtx[i] ) FreeFloatVec( mtx[i] ); mtx[i] = NULL;
	}
	free( mtx );
}
void FreeDoubleMtx( double **mtx )
{
	int i;
	for( i=0; mtx[i]; i++ )
	{
		FreeDoubleVec( mtx[i] );
		mtx[i] = NULL;
	}
	free( mtx );
}

double ***AllocateFloatCub( int ll1, int ll2, int  ll3 )
{
	int i;
	double ***cub;

	cub = (double ***)calloc( ll1+1, sizeof( double ** ) );
	if( !cub ) 
	{
		fprintf( stderr, "cannot allocate double cube.\n" );
		exit( 1 );
	}
	for( i=0; i<ll1; i++ ) 
	{
		cub[i] = AllocateFloatMtx( ll2, ll3 );
	}
	cub[ll1] = NULL;
	return( cub );
}

void FreeFloatCub( double ***cub )
{
	int i;

	for( i=0; cub[i]; i++ ) 
	{
		FreeFloatMtx( cub[i] );
	}
	free( cub );
}

double ***AllocateDoubleCub( int ll1, int ll2, int  ll3 )
{
	int i;
	double ***cub;

	cub = (double ***)calloc( ll1+1, sizeof( double ** ) );
	if( !cub ) 
	{
		fprintf( stderr, "cannot allocate double cube.\n" );
		exit( 1 );
	}
	for( i=0; i<ll1; i++ ) 
	{
		cub[i] = AllocateDoubleMtx( ll2, ll3 );
	}
	cub[ll1] = NULL;
	return( cub );
}

void FreeDoubleCub( double ***cub )
{
	int i;

	for( i=0; cub[i]; i++ ) 
	{
		FreeDoubleMtx( cub[i] );
	}
	free( cub );
}


short *AllocateShortVec( int ll1 )
{
	short *vec;

	vec = (short *)calloc( ll1, sizeof( short ) );
	if( vec == NULL )
	{	
		fprintf( stderr, "Allocation error( %d short vec )\n", ll1 );
		exit( 1 );
	}
	return( vec );
}	

void FreeShortVec( short *vec )
{
	free( (char *)vec );
}

short **AllocateShortMtx( int ll1, int ll2 )
{
	int i;
	short **mtx;


	mtx = (short **)calloc( ll1+1, sizeof( short * ) );
	if( !mtx )
	{
		fprintf( stderr, "Allocation error( %d x %d short mtx ) \n", ll1, ll2 );
		exit( 1 );
	}
	for( i=0; i<ll1; i++ ) 
	{
		mtx[i] = AllocateShortVec( ll2 );
	}
	mtx[ll1] = NULL;
	return( mtx );
}

void FreeShortMtx( short **mtx )
{
	int i;

	for( i=0; mtx[i]; i++ ) 
		free( (char *)mtx[i] );
	free( (char *)mtx );
}

void BLOSUMmtx( int n, double **matrix, double *freq, unsigned char *amino, char *amino_grp, int *rescalept )
{
	char locaminod[] = "ARNDCQEGHILKMFPSTWYVBZX.-J";
	char locgrpd[] = 
	{
		0, 3, 2, 2, 5, 2, 2, 0, 3, 1, 1, 3, 1, 4, 0, 0, 0, 4, 4, 1, 2, 2,
		6, 6, 6, 1,
	};
	double freqd[20] = 
	{
	    0.077,
	    0.051,
	    0.043,
	    0.052,
	    0.020,
	    0.041,
	    0.062,
	    0.074,
	    0.023,
	    0.052,
	    0.091,
	    0.059,
	    0.024,
	    0.040,
	    0.051,
	    0.069,
	    0.059,
	    0.014,
	    0.032,
	    0.066,
	};

	double tmpmtx30[] = 
	{
    4,
   -1,     8,
    0,    -2,     8,
    0,    -1,     1,     9,
   -3,    -2,    -1,    -3,    17,
    1,     3,    -1,    -1,    -2,     8,
    0,    -1,    -1,     1,     1,     2,     6,
    0,    -2,     0,    -1,    -4,    -2,    -2,     8,
   -2,    -1,    -1,    -2,    -5,     0,     0,    -3,    14,
    0,    -3,     0,    -4,    -2,    -2,    -3,    -1,    -2,     6,
   -1,    -2,    -2,    -1,     0,    -2,    -1,    -2,    -1,     2,     4,
    0,     1,     0,     0,    -3,     0,     2,    -1,    -2,    -2,    -2,     4,
    1,     0,     0,    -3,    -2,    -1,    -1,    -2,     2,     1,     2,     2,     6,
   -2,    -1,    -1,    -5,    -3,    -3,    -4,    -3,    -3,     0,     2,    -1,    -2,    10,
   -1,    -1,    -3,    -1,    -3,     0,     1,    -1,     1,    -3,    -3,     1,    -4,    -4,    11,
    1,    -1,     0,     0,    -2,    -1,     0,     0,    -1,    -1,    -2,     0,    -2,    -1,    -1,     4,
    1,    -3,     1,    -1,    -2,     0,    -2,    -2,    -2,     0,     0,    -1,     0,    -2,     0,     2,     5,
   -5,     0,    -7,    -4,    -2,    -1,    -1,     1,    -5,    -3,    -2,    -2,    -3,     1,    -3,    -3,    -5,    20,
   -4,     0,    -4,    -1,    -6,    -1,    -2,    -3,     0,    -1,     3,    -1,    -1,     3,    -2,    -2,    -1,     5,     9,
    1,    -1,    -2,    -2,    -2,    -3,    -3,    -3,    -3,     4,     1,    -2,     0,     1,    -4,    -1,     1,    -3,     1,     5,
    0,    -2,     4,     5,    -2,    -1,     0,     0,    -2,    -2,    -1,     0,    -2,    -3,    -2,     0,     0,    -5,    -3,    -2,     5,
    0,     0,    -1,     0,     0,     4,     5,    -2,     0,    -3,    -1,     1,    -1,    -4,     0,    -1,    -1,    -1,    -2,    -3,     0,     4,
    0,    -1,     0,    -1,    -2,     0,    -1,    -1,    -1,     0,     0,     0,     0,    -1,    -1,     0,     0,    -2,    -1,     0,    -1,     0,    -1,
	};
	
	double tmpmtx45[] = 
	{
      5,
     -2,      7,
     -1,      0,      6,
     -2,     -1,      2,      7,
     -1,     -3,     -2,     -3,     12,
     -1,      1,      0,      0,     -3,      6,
     -1,      0,      0,      2,     -3,      2,      6,
      0,     -2,      0,     -1,     -3,     -2,     -2,      7,
     -2,      0,      1,      0,     -3,      1,      0,     -2,     10,
     -1,     -3,     -2,     -4,     -3,     -2,     -3,     -4,     -3,      5,
     -1,     -2,     -3,     -3,     -2,     -2,     -2,     -3,     -2,      2,      5,
     -1,      3,      0,      0,     -3,      1,      1,     -2,     -1,     -3,     -3,      5,
     -1,     -1,     -2,     -3,     -2,      0,     -2,     -2,      0,      2,      2,     -1,      6,
     -2,     -2,     -2,     -4,     -2,     -4,     -3,     -3,     -2,      0,      1,     -3,      0,      8,
     -1,     -2,     -2,     -1,     -4,     -1,      0,     -2,     -2,     -2,     -3,     -1,     -2,     -3,      9,
      1,     -1,      1,      0,     -1,      0,      0,      0,     -1,     -2,     -3,     -1,     -2,     -2,     -1,      4,
      0,     -1,      0,     -1,     -1,     -1,     -1,     -2,     -2,     -1,     -1,     -1,     -1,     -1,     -1,      2,      5,
     -2,     -2,     -4,     -4,     -5,     -2,     -3,     -2,     -3,     -2,     -2,     -2,     -2,      1,     -3,     -4,     -3,     15,
     -2,     -1,     -2,     -2,     -3,     -1,     -2,     -3,      2,      0,      0,     -1,      0,      3,     -3,     -2,     -1,      3,      8,
      0,     -2,     -3,     -3,     -1,     -3,     -3,     -3,     -3,      3,      1,     -2,      1,      0,     -3,     -1,      0,     -3,     -1,      5,
	};
    double tmpmtx50[] = 
    {
       5,
      -2,      7,
      -1,     -1,      7,
      -2,     -2,      2,      8,
      -1,     -4,     -2,     -4,     13,
      -1,      1,      0,      0,     -3,      7,
      -1,      0,      0,      2,     -3,      2,      6,
       0,     -3,      0,     -1,     -3,     -2,     -3,      8,
      -2,      0,      1,     -1,     -3,      1,      0,     -2,     10,
      -1,     -4,     -3,     -4,     -2,     -3,     -4,     -4,     -4,      5,
      -2,     -3,     -4,     -4,     -2,     -2,     -3,     -4,     -3,      2,      5,
      -1,      3,      0,     -1,     -3,      2,      1,     -2,      0,     -3,     -3,      6,
      -1,     -2,     -2,     -4,     -2,      0,     -2,     -3,     -1,      2,      3,     -2,      7,
      -3,     -3,     -4,     -5,     -2,     -4,     -3,     -4,     -1,      0,      1,     -4,      0,      8,
      -1,     -3,     -2,     -1,     -4,     -1,     -1,     -2,     -2,     -3,     -4,     -1,     -3,     -4,     10,
       1,     -1,      1,      0,     -1,      0,     -1,      0,     -1,     -3,     -3,      0,     -2,     -3,     -1,      5,
       0,     -1,      0,     -1,     -1,     -1,     -1,     -2,     -2,     -1,     -1,     -1,     -1,     -2,     -1,      2,      5,
      -3,     -3,     -4,     -5,     -5,     -1,     -3,     -3,     -3,     -3,     -2,     -3,     -1,      1,     -4,     -4,     -3,     15,
      -2,     -1,     -2,     -3,     -3,     -1,     -2,     -3,      2,     -1,     -1,     -2,      0,      4,     -3,     -2,     -2,      2,      8,
       0,     -3,     -3,     -4,     -1,     -3,     -3,     -4,     -4,      4,      1,     -3,      1,     -1,     -3,     -2,      0,     -3,     -1,      5,
    };
	double tmpmtx62[] = 
	{ 5.893685,
	 -2.120252,  8.210189,
	 -2.296072, -0.659672,  8.479856,
	 -2.630151, -2.408668,  1.907550,  8.661363,
	 -0.612761, -5.083814, -3.989626, -5.189966, 12.873172,
	 -1.206025,  1.474162,  0.002529, -0.470069, -4.352838,  7.927704,
	 -1.295821, -0.173087, -0.402015,  2.265459, -5.418729,  2.781955,  7.354247,
	  0.239392, -3.456163, -0.634136, -1.970281, -3.750621, -2.677743, -3.165266,  8.344902,
	 -2.437724, -0.374792,  0.867735, -1.678363, -4.481724,  0.672051, -0.176497, -3.061315, 11.266586,
	 -1.982718, -4.485360, -4.825558, -4.681732, -1.841495, -4.154454, -4.791538, -5.587336, -4.847345,  5.997760,
	 -2.196882, -3.231860, -5.068375, -5.408471, -1.916207, -3.200863, -4.269723, -5.440437, -4.180099,  2.282412,  5.774148,
	 -1.101017,  3.163105, -0.268534, -1.052724, -4.554510,  1.908859,  1.163010, -2.291924, -1.081539, -4.005209, -3.670219,  6.756827,
	 -1.402897, -2.050705, -3.226290, -4.587785, -2.129758, -0.631437, -2.997038, -4.014898, -2.326896,  1.690191,  2.987638, -2.032119,  8.088951,
	 -3.315080, -4.179521, -4.491005, -5.225795, -3.563219, -4.746598, -4.788639, -4.661029, -1.851231, -0.241317,  0.622170, -4.618016,  0.018880,  9.069126,
	 -1.221394, -3.162863, -3.000581, -2.220163, -4.192770, -1.922917, -1.674258, -3.200320, -3.241363, -4.135001, -4.290107, -1.520445, -3.714633, -5.395930, 11.046892,
	  1.673639, -1.147170,  0.901353, -0.391548, -1.312485, -0.151708, -0.220375, -0.438748, -1.322366, -3.522266, -3.663923, -0.305170, -2.221304, -3.553533, -1.213470,  5.826527,
	 -0.068042, -1.683495, -0.069138, -1.576054, -1.299983, -1.012997, -1.294878, -2.363065, -2.528844, -1.076382, -1.796229, -1.004336, -0.999449, -3.161436, -1.612919,  2.071710,  6.817956,
	 -3.790328, -4.019108, -5.543911, -6.321502, -3.456164, -2.919725, -4.253197, -3.737232, -3.513238, -3.870811, -2.447829, -4.434676, -2.137255,  1.376341, -5.481260, -4.127804, -3.643382, 15.756041,
	 -2.646022, -2.540799, -3.122641, -4.597428, -3.610671, -2.131601, -3.030688, -4.559647,  2.538948, -1.997058, -1.593097, -2.730047, -1.492308,  4.408690, -4.379667, -2.528713, -2.408996,  3.231335,  9.892544,
	 -0.284140, -3.753871, -4.314525, -4.713963, -1.211518, -3.297575, -3.663425, -4.708118, -4.676220,  3.820569,  1.182672, -3.393535,  1.030861, -1.273542, -3.523054, -2.469318, -0.083276, -4.251392, -1.811267,  5.653391,
	};
	double tmpmtx80[] = 
	{
      7,
     -3,      9,
     -3,     -1,      9,
     -3,     -3,      2,     10,
     -1,     -6,     -5,     -7,     13,
     -2,      1,      0,     -1,     -5,      9,
     -2,     -1,     -1,      2,     -7,      3,      8,
      0,     -4,     -1,     -3,     -6,     -4,     -4,      9,
     -3,      0,      1,     -2,     -7,      1,      0,     -4,     12,
     -3,     -5,     -6,     -7,     -2,     -5,     -6,     -7,     -6,      7,
     -3,     -4,     -6,     -7,     -3,     -4,     -6,     -7,     -5,      2,      6,
     -1,      3,      0,     -2,     -6,      2,      1,     -3,     -1,     -5,     -4,      8,
     -2,     -3,     -4,     -6,     -3,     -1,     -4,     -5,     -4,      2,      3,     -3,      9,
     -4,     -5,     -6,     -6,     -4,     -5,     -6,     -6,     -2,     -1,      0,     -5,      0,     10,
     -1,     -3,     -4,     -3,     -6,     -3,     -2,     -5,     -4,     -5,     -5,     -2,     -4,     -6,     12,
      2,     -2,      1,     -1,     -2,     -1,     -1,     -1,     -2,     -4,     -4,     -1,     -3,     -4,     -2,      7,
      0,     -2,      0,     -2,     -2,     -1,     -2,     -3,     -3,     -2,     -3,     -1,     -1,     -4,     -3,      2,      8,
     -5,     -5,     -7,     -8,     -5,     -4,     -6,     -6,     -4,     -5,     -4,     -6,     -3,      0,     -7,     -6,     -5,     16,
     -4,     -4,     -4,     -6,     -5,     -3,     -5,     -6,      3,     -3,     -2,     -4,     -3,      4,     -6,     -3,     -3,      3,     11,
     -1,     -4,     -5,     -6,     -2,     -4,     -4,     -6,     -5,      4,      1,     -4,      1,     -2,     -4,     -3,      0,     -5,     -3,      7,
	};
	double tmpmtx90[] = 
	{
 5,
-2,  6,
-2, -1,  7,
-3, -3,  1,  7,
-1, -5, -4, -5,  9,
-1,  1,  0, -1, -4,  7,
-1, -1, -1,  1, -6,  2,  6,
 0, -3, -1, -2, -4, -3, -3,  6,
-2,  0,  0, -2, -5,  1, -1, -3,  8,
-2, -4, -4, -5, -2, -4, -4, -5, -4,  5,
-2, -3, -4, -5, -2, -3, -4, -5, -4,  1,  5,
-1,  2,  0, -1, -4,  1,  0, -2, -1, -4, -3,  6,
-2, -2, -3, -4, -2,  0, -3, -4, -3,  1,  2, -2,  7,
-3, -4, -4, -5, -3, -4, -5, -5, -2, -1,  0, -4, -1,  7,
-1, -3, -3, -3, -4, -2, -2, -3, -3, -4, -4, -2, -3, -4,  8,
 1, -1,  0, -1, -2, -1, -1, -1, -2, -3, -3, -1, -2, -3, -2,  5,
 0, -2,  0, -2, -2, -1, -1, -3, -2, -1, -2, -1, -1, -3, -2,  1,  6,
-4, -4, -5, -6, -4, -3, -5, -4, -3, -4, -3, -5, -2,  0, -5, -4, -4, 11,
-3, -3, -3, -4, -4, -3, -4, -5,  1, -2, -2, -3, -2,  3, -4, -3, -2,  2,  8,
-1, -3, -4, -5, -2, -3, -3, -5, -4,  3,  0, -3,  0, -2, -3, -2, -1, -3, -3,  5,
	};
	double tmpmtx100[] = 
	{
 8,
-3,10,
-4,-2,11,
-5,-5, 1,10,
-2,-8,-5,-8,14,
-2, 0,-1,-2,-7,11,
-3,-2,-2, 2,-9, 2,10,
-1,-6,-2,-4,-7,-5,-6, 9,
-4,-1, 0,-3,-8, 1,-2,-6,13,
-4,-7,-7,-8,-3,-6,-7,-9,-7, 8,
-4,-6,-7,-8,-5,-5,-7,-8,-6, 2, 8,
-2, 3,-1,-3,-8, 2, 0,-5,-3,-6,-6,10,
-3,-4,-5,-8,-4,-2,-5,-7,-5, 1, 3,-4,12,
-5,-6,-7,-8,-4,-6,-8,-8,-4,-2, 0,-6,-1,11,
-2,-5,-5,-5,-8,-4,-4,-6,-5,-7,-7,-3,-5,-7,12,
 1,-3, 0,-2,-3,-2,-2,-2,-3,-5,-6,-2,-4,-5,-3, 9,
-1,-3,-1,-4,-3,-3,-3,-5,-4,-3,-4,-3,-2,-5,-4, 2, 9,
-6,-7,-8,-10,-7,-5,-8,-7,-5,-6,-5,-8,-4, 0,-8,-7,-7,17,
-5,-5,-5,-7,-6,-4,-7,-8, 1,-4,-4,-5,-5, 4,-7,-5,-5, 2,12,
-2,-6,-7,-8,-3,-5,-5,-8,-7, 4, 0,-5, 0,-3,-6,-4,-1,-5,-5, 8,
	};
	double tmpmtx0[] = 
	{
     2.4,
    -0.6,    4.7,
    -0.3,    0.3,    3.8,
    -0.3,   -0.3,    2.2,    4.7,
     0.5,   -2.2,   -1.8,   -3.2,   11.5,
    -0.2,    1.5,    0.7,    0.9,   -2.4,    2.7,
     0.0,    0.4,    0.9,    2.7,   -3.0,    1.7,    3.6,
     0.5,   -1.0,    0.4,    0.1,   -2.0,   -1.0,   -0.8,    6.6,
    -0.8,    0.6,    1.2,    0.4,   -1.3,    1.2,    0.4,   -1.4,    6.0,
    -0.8,   -2.4,   -2.8,   -3.8,   -1.1,   -1.9,   -2.7,   -4.5,   -2.2,    4.0,
    -1.2,   -2.2,   -3.0,   -4.0,   -1.5,   -1.6,   -2.8,   -4.4,   -1.9,    2.8,    4.0,
    -0.4,    2.7,    0.8,    0.5,   -2.8,    1.5,    1.2,   -1.1,    0.6,   -2.1,   -2.1,    3.2,
    -0.7,   -1.7,   -2.2,   -3.0,   -0.9,   -1.0,   -2.0,   -3.5,   -1.3,    2.5,    2.8,   -1.4,    4.3,
    -2.3,   -3.2,   -3.1,   -4.5,   -0.8,   -2.6,   -3.9,   -5.2,   -0.1,    1.0,    2.0,   -3.3,    1.6,    7.0,
     0.3,   -0.9,   -0.9,   -0.7,   -3.1,   -0.2,   -0.5,   -1.6,   -1.1,   -2.6,   -2.3,   -0.6,   -2.4,   -3.8,    7.6,
     1.1,   -0.2,    0.9,    0.5,    0.1,    0.2,    0.2,    0.4,   -0.2,   -1.8,   -2.1,    0.1,   -1.4,   -2.8,    0.4,    2.2,
     0.6,   -0.2,    0.5,    0.0,   -0.5,    0.0,   -0.1,   -1.1,   -0.3,   -0.6,   -1.3,    0.1,   -0.6,   -2.2,    0.1,    1.5,    2.5,
    -3.6,   -1.6,   -3.6,   -5.2,   -1.0,   -2.7,   -4.3,   -4.0,   -0.8,   -1.8,   -0.7,   -3.5,   -1.0,    3.6,   -5.0,   -3.3,   -3.5,   14.2,
    -2.2,   -1.8,   -1.4,   -2.8,   -0.5,   -1.7,   -2.7,   -4.0,    2.2,   -0.7,    0.0,   -2.1,   -0.2,    5.1,   -3.1,   -1.9,   -1.9,    4.1,    7.8,
     0.1,   -2.0,   -2.2,   -2.9,    0.0,   -1.5,   -1.9,   -3.3,   -2.0,    3.1,    1.8,   -1.7,    1.6,    0.1,   -1.8,   -1.0,    0.0,   -2.6,   -1.1,    3.4,
	};

	int i, j, count;
	double av;
	double *tmpmtx;

	if( n == 30 ) tmpmtx = tmpmtx30;
	else if( n == 45 ) tmpmtx = tmpmtx45;
	else if( n == 50 ) tmpmtx = tmpmtx50;
	else if( n == 62 ) tmpmtx = tmpmtx62;
	else if( n == 80 ) tmpmtx = tmpmtx80;
	else if( n == 90 ) tmpmtx = tmpmtx90;
	else if( n == 100 ) tmpmtx = tmpmtx100;
	else if( n == 0 ) tmpmtx = tmpmtx0;
	//else if( n == -1 ) tmpmtx = loadaamtx( rescalept );
	else
	{
		return;
	}

	count = 0;
	for( i=0; i<20; i++ )
	{
		for( j=0; j<=i; j++ )
		{
			matrix[i][j] = matrix[j][i] = (double)tmpmtx[count++];
		}
	}
	if( n == -1 && tmpmtx[400] != -1.0 ) 
	{
		for( i=0; i<20; i++ ) freq[i] = tmpmtx[400+i];
		av = 0.0;
		for( i=0; i<20; i++ ) av += freq[i];
		for( i=0; i<20; i++ ) freq[i] /= av;
	}
	else
		for( i=0; i<20; i++ ) freq[i] = freqd[i];

	if( n == -1 ) free( tmpmtx );
    for( i=0; i<26; i++ ) amino[i] = locaminod[i];
    for( i=0; i<26; i++ ) amino_grp[(int)amino[i]] = locgrpd[i];
}