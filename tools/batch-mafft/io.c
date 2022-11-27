#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "mtxutl.c"

#define NOTSPECIFIED 'n'
#define N 5000000 
#define B 256

static int upperCase = 0;

int countATGC( char *s, int *total )
{
	int nATGC;
	int nChar;
	char c;
	nATGC = nChar = 0;

	if( *s == 0 ) 
	{
		*total = 0;
		return( 0 );
	}

	do
	{
		c = tolower( *s );
		if( isalpha( c ) )
		{
			nChar++;
			if( c == 'a' || c == 't' || c == 'g' || c == 'c' || c == 'u' || c == 'n' )
				nATGC++;
		}
	}
	while( *++s );

	*total = nChar;
	return( nATGC );
}

static int charfilter( unsigned char *str )
{
	unsigned char tmp;
	unsigned char *res = str;
	unsigned char *bk = str;

	while( (tmp=*str++) )
	{
		if( tmp == '=' || tmp == '<' || tmp == '>' ) exit( 1 );
		if( tmp != 0x0a && tmp != 0x20 && tmp != 0x0d )
		{
			*res++ = tmp;
		}
	}
	*res = 0;
	return( res - bk );
}

static int countKUorWA( char* unaligned, int unaligned_charlen )
{
	int value;
	int b;

	value= 0;
	b = '\n';
	
	for (unsigned int i = 0; i < unaligned_charlen; i++) {
		if (b == '\n' && (unaligned[i] == '>')) {
			value++;
		}
		b = unaligned[i];
	}

	return( value );
}

/*void searchKUorWA( FILE *fp )
{
	int c, b;
	b = '\n';
	while( !( ( ( c = getc( fp ) ) == '>' || c == EOF ) && b == '\n' ) )
		b = c;
	ungetc( c, fp );
}*/

void searchKUorWA(char* unaligned, int unaligned_charlen, int* index) {
	int c, b, i;
	b = '\n';
	i = *index;

	while (!(((c = unaligned[i]) == '>' || i == unaligned_charlen) && b == '\n')) {
		b = c;
	}
	*index = i;
}

/*int myfgets(s, l, fp)
char    s[] ; int l ; FILE *fp ;
{
    int c = 0, i = 0;

    if( feof( fp ) ) return( 1 );

    for( i=0; i<l && ( c=getc( fp ) ) != '\n'; i++ ) 
        *s++ = c;
    *s = '\0' ;
    if( c != '\n' ) 
        while( getc(fp) != '\n' )
            ;
    return( 0 );
}*/

int myfgets(char s[], int l, char* unaligned, int unaligned_charlen, int* index) {
	int c = 0, i = 0;
	if (*index == unaligned_charlen) return 1;
	for (i = 0; i < l && (c = unaligned[*index] ) != '\n'; i++) {
		*s++ = c;
		(*index)++;
	}
	*s = '\0';
	if (c != '\n') {
		while(unaligned[*index] != '\n')  {
			(*index)++;
		}
	}
	return 0;
}

/*char *load1SeqWithoutName_realloc_casepreserve( FILE *fpp )
{
	int c, b;
	char *cbuf;
	int size = N;
	char *val;

	val = malloc( (size+1) * sizeof( char ) );
	cbuf = val;

	b = '\n';
	while( ( c = getc( fpp ) ) != EOF &&           
          !( ( c == '>' || c == EOF ) && b == '\n' ) )
	{
		*cbuf++ = (char)c;  
		if( cbuf - val == size )
		{
			size += N;
			val = (char *)realloc( val, (size+1) * sizeof( char ) );
			if( !val ) exit( 1 );
			cbuf = val + size-N;
		}
		b = c;
	}
	ungetc( c, fpp );
	*cbuf = 0;
	charfilter( (unsigned char *) val );
	return( val );
}*/

char *load1SeqWithoutName_realloc_casepreserve(char* unaligned, int unaligned_charlen, int* index) {
	int c, b;
	char* cbuf;
	int size = N;
	char* val;

	val = malloc((size + 1) * sizeof(char));
	cbuf = val;

	b = '\n';

	int i = *index;
	while ( i < unaligned_charlen && 
		   !( ( (c=unaligned[i]) == '>' ) && b == '\n')) {
		*cbuf++ = (char)c;
		if ( cbuf - val == size ) {
			size += N;
			val = (char*) realloc(val, (size+1) * sizeof(char));
			if (!val) {
				exit(1);
			}
			cbuf = val + size-N;
		}
		b = c;
		i++;
	}
	*cbuf = 0;
	charfilter( (unsigned char*) val);
	*index = i;
	return val;
}

/*void readData_pointer_casepreserve( FILE *fp, char **name, int *nlen, char **seq, int njob )
{
	int i; 
	static char *tmpseq = NULL;

	rewind( fp );
	searchKUorWA( fp );

	for( i=0; i<njob; i++ )
	{
		name[i][0] = '='; getc( fp ); 
		myfgets( name[i]+1, B-2, fp ); 
		tmpseq = load1SeqWithoutName_realloc_casepreserve( fp );
		strcpy( seq[i], tmpseq );
		free( tmpseq );
		nlen[i] = strlen( seq[i] );
	}
}*/

void readData_pointer_casepreserve(char* unaligned, int unaligned_charlen, char** name, int* nlen, char** seq, int njob) {
	int i;
	static char* tmpseq = NULL;
	
	int index = 0;
	searchKUorWA(unaligned, unaligned_charlen, &index);

	for (i = 0; i < njob; i++) {
		name[i][0] = '='; index++;
		myfgets(name[i]+1, B-2, unaligned, unaligned_charlen, &index);
		tmpseq = load1SeqWithoutName_realloc_casepreserve(unaligned, unaligned_charlen, &index);
		strcpy(seq[i], tmpseq);
		free(tmpseq);
		nlen[i] = strlen(seq[i]);
	}
}

void getnumlen_casepreserve( char* unaligned, int unaligned_charlen, int *nlenminpt, char *dorp, int *njob, int *nlenmax)
{
	int total;
	int nsite = 0;
	int atgcnum;
	int i, tmp;
	char *tmpseq, *tmpname;
	double atgcfreq;
	int index = 0;

	tmpname = AllocateCharVec( N );
	*njob = countKUorWA( unaligned, unaligned_charlen);
	searchKUorWA( unaligned, unaligned_charlen, &index );
	*nlenmax = 0;
	*nlenminpt = 99999999;
	atgcnum = 0;
	total = 0;
	for( i=0; i<*njob; i++ )
	{
		myfgets( tmpname, N-1, unaligned, unaligned_charlen, &index );
		tmpseq = load1SeqWithoutName_realloc_casepreserve( unaligned, unaligned_charlen, &index );
		tmp = strlen( tmpseq );
		if( tmp > *nlenmax ) *nlenmax  = tmp;
		if( tmp < *nlenminpt ) *nlenminpt  = tmp;
		if( total < 1000000 )
		{
			atgcnum += countATGC( tmpseq, &nsite );
			total += nsite;
		}
		free( tmpseq );
	}
	free( tmpname );
	atgcfreq = (double)atgcnum / total;
    
    if( *dorp == NOTSPECIFIED )
	{
		if( atgcfreq > 0.75 ) 	
		{
			*dorp = 'd';
			upperCase = -1;
		}
		else                  
		{
			*dorp = 'p';
			upperCase = 0;
		}
	}
}