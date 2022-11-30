#include "replaceu.c"
#include "tbfast.c"

#define er 0
#define progname "linsi"
#define anysymbol 1
#define ep 0.123

// linsi properties
#define fft 0
#define cycle 1
#define iterate 1000
#define distance "local"
#define strategy "L-INS-i"

// other properties to keep track of
#define addfile NULL
#define tmpfile "/var/folders/xb/ttq_ycbj3x7013f1p015bhv00000gn/T/mafft-linsi.XXXXXXXXXX.OqQAktC0"
#define seed NULL
#define seednseq 0
#define numthreads 0
#define numthreadstb 0
#define numthreadsit 0
#define nadd 0
#define gopdist 1.53
#define aof -0.123
#define laof 0.1
#define pgaof 0.1
#define iteratelimit 16
//#define iterate 16
#define rnaopt "  "
#define rnaoptit " -F "
#define swopt " "
#define parttreeoutopt " "
#define treeoutopt " "
#define distoutopt " "
#define formatcheck 0
#define fragment 0
#define pairspecified 0
#define localparam "-l 2.7"
#define param_fft " "
#define cycletbfast 1
#define cycledisttbfast 1
#define outputformat "pir"
#define outputopt "-f -l 60"

static int unaligned_charlen = 0;

// TODO: ​mafft-linsi --ep 0.123 --quiet --anysymbol input > output

char* extract_file_contents(char* filename) {
    FILE *f;
    char s;

    f=fopen(filename,"r");
    int len = 0;
    while((s=fgetc(f))!=EOF) {
        len++;
    }

    char* ret = malloc((len+1)*sizeof(char));
    int i = 0;
    rewind(f);
    while ((s=fgetc(f))!=EOF) {
        ret[i] = s;
        i++;
    }

    unaligned_charlen = i;

    fclose(f);
    return ret;
}

char* mafft_magus(char* unaligned, int nseq) {
    return "pass";
}

int main(int argc, char* argv[]) {
    char* inputfile = "../mafft-main/test/sample";
    char* unaligned = extract_file_contents(inputfile);

    char** seq;
    char** name;
    int* nlen;
    char dorp = 'n';
    int njob = 0;
    int nlenmax = 0;
    int nlenmin = 0;

    replaceu(unaligned, unaligned_charlen, &dorp, &njob, &nlenmax, &nlenmin, name, seq, nlen);

    tbfast();

    char** mseq1;
    char** mseq2;
    int* selfscore;
    double** len;
    double* eff;
    char* kozoarivec;
    char* mergeoralign;
    Treedep* dep;
    int** localmem;
    double** iscore;
    int* targetmap;
    int* targetmapr;
    LocalHom** localhomtable;
    char **pav, **tav;
    int tbfast_argc = 43;

    // Allocate all necessary memory
    mseq1 = AllocateCharMtx( njob, 0 );
	mseq2 = AllocateCharMtx( njob, 0 );
    selfscore = AllocateIntVec( njob );
    len = AllocateFloatMtx( njob, 2 );
	eff = AllocateDoubleVec( njob );
	kozoarivec = AllocateCharVec( njob );
    mergeoralign = AllocateCharVec( njob );
    dep = (Treedep *)calloc( njob, sizeof( Treedep ) );
    localmem = AllocateIntMtx( 2, njob+1 );
    iscore = AllocateFloatHalfMtx( njob );

    targetmap = calloc( njob, sizeof( int ) );
    targetmapr = calloc( njob, sizeof( int ) );
    for( i=0; i<njob; i++ ) targetmap[i] = targetmapr[i] = i;

    localhomtable = (LocalHom **)calloc( ntarget, sizeof( LocalHom *) );
    for( i=0; i<ntarget; i++ ) localhomtable[i] = (LocalHom *)calloc( ilim, sizeof( LocalHom ) );

    pav = calloc( tbfast_argc, sizeof( char * ) );
	tav = calloc( tbfast_argc, sizeof( char * ) );

    pav[0]= "tbfast-pair"
    pav[1]= "-u"
    pav[2]= "0.0"
    pav[3]= "-l"
    pav[4]= "2.7"
    pav[5]= "-C"
    pav[6]= "0"
    pav[7]= "-b"
    pav[8]= "62"
    pav[9]= "-g"
    pav[10]= "-0.100"
    pav[11]= "-f"
    pav[12]= "-2.00"
    pav[13]= "-Q"
    pav[14]= "100.0"
    pav[15]= "-h"
    pav[16]= "0.1"
    pav[17]= "-L"

    tav[0]= "tbfast"
    tav[1]= "-+"
    tav[2]= "16"
    tav[3]= "-W"
    tav[4]= "0.00001"
    tav[5]= "-V"
    tav[6]= "-1.53"
    tav[7]= "-s"
    tav[8]= "0.0"
    tav[9]= "-O"
    tav[10]= "-C"
    tav[11]= "0"
    tav[12]= "-b"
    tav[13]= "62"
    tav[14]= "-f"
    tav[15]= "-1.53"
    tav[16]= "-Q"
    tav[17]= "100.0"
    tav[18]= "-h"
    tav[19]= "-0.123"
    tav[20]= "-l"
    tav[21]= "2.7"
    tav[22]= "-X"
    tav[23]= "0.1"

    fprintf(stderr, "dorp:\t%c\nnjob:\t%d\nnlenmax:\t%d\nnlenmin:\t%d\n", dorp, njob, nlenmax, nlenmin);
}