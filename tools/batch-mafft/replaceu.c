#include "io.c"

static int seedoffset;

static void replace_unusual( int n, char **seq, char *usual, char unknown, int (*uporlow)( int ) )
{
	int i;
	char *pt;
	for( i=0; i<n; i++ )
	{
		pt = seq[i];
		while( *pt )
		{
			if( !strchr( usual, *pt ) ) *pt = unknown;
			else *pt = uporlow( *pt );
			pt++;
		}
	}
}

void replaceu(char* unaligned, int unaligned_charlen, char* inputfile, char* dorp, int* njob, int* nlenmax, int* lenmin) {
    //FILE *infp;
	int nlenmin;
	char **name;
	char **seq;
	int *nlen;
	int i;
	char *usual;
    
    seedoffset = 0;
	*dorp = NOTSPECIFIED;

	//infp = fopen( inputfile, "r" );
	getnumlen_casepreserve( unaligned, unaligned_charlen, &nlenmin, dorp, njob, nlenmax);

	seq = AllocateCharMtx( *njob, (*nlenmax)+1 );
	name = AllocateCharMtx( *njob, B+1 );
	nlen = AllocateIntVec( *njob );

	readData_pointer_casepreserve( unaligned, unaligned_charlen, name, nlen, seq, *njob );
	//fclose( infp );

	if( *dorp == 'p' )
	{
		usual = "ARNDCQEGHILKMFPSTWYVarndcqeghilkmfpstwyv-.";
		replace_unusual( *njob, seq, usual, 'X', toupper );
	}
	else
	{
		usual = "ATGCUatgcuBDHKMNRSVWYXbdhkmnrsvwyx-";
		replace_unusual( *njob, seq, usual, 'n', tolower );
	}

    *lenmin = nlenmin;

	free( nlen );
	FreeCharMtx( seq );
	FreeCharMtx( name );
}