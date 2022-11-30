//#include "mltaln.h"
#include "mtxutl.c"

#define DEBUG 0
#define IODEBUG 0
#define SCOREOUT 0
#define NOT_SPECIFIED 100009
#define FFT_THRESHOLD 80
#define FFT_WINSIZE_D 100
#define FFT_WINSIZE_P 20
#define REPORTCOSTS 0

typedef struct _Treedep
{
	int child0;
	int child1;
	int done;
	double distfromtip;
} Treedep;

typedef struct _LocalHom
{
	struct _LocalHom *next;
	struct _LocalHom *last;
	int start1;
	int end1;
	int start2;
	int end2;
	double opt;
	int overlapaa;
	int extended;
	double importance;
	double rimportance;
	char korh;
	int nokori;
} LocalHom;

typedef struct _lastresx
{
	int score;
	int naln;
	Aln *aln;
} Lastresx;

int shishagonyuu(double in) {
	int out;
	if     ( in >  0.0 ) out = ( (int)( in + 0.5 ) );
	else if( in == 0.0 ) out = ( 0 );
	else if( in <  0.0 ) out = ( (int)( in - 0.5 ) );
	else                 out = 0;
	return( out );
}

void constants() {
}

int pairlocalalign() {
}

/* /usr/local/libexec/mafft/tbfast _  
	-u 0.0 
	-l 2.7 
	-C 0 
	-b 62 
	-g -0.100 
	-f -2.00 
	-Q 100.0
	-h 0.1 
	-L _ -+ 16 
	-W 0.00001 
	-V -1.53 
	-s 0.0 
	-O        
	-C 0                
	-b 62        
	-f -1.53 
	-Q 100.0 
	-h -0.123 
	-l 2.7 
	-X 0.1     
*/
void tbfast() {
}