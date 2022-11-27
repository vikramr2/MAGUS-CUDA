#include "replaceu.c"

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
    char dorp = 'n';
    int njob = 0;
    int nlenmax = 0;
    int nlenmin = 0;

    replaceu(unaligned, unaligned_charlen, inputfile, &dorp, &njob, &nlenmax, &nlenmin);

    fprintf(stderr, "dorp:\t%c\nnjob:\t%d\nnlenmax:\t%d\nnlenmin:\t%d\n", dorp, njob, nlenmax, nlenmin);

    //fprintf(stderr, "%s", extract_file_contents(inputfile));
}