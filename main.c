#include "myheader.h"

int main(int argc,char *argv[])
{
    int option;
    char *inputFile, *type;

    _SBLOCK *s_blockHead = NULL;
    _VIRTMEMPAGEBLOCKS *virtmempageBlocks = NULL;
    _MEMPAGEBLOCKS *mempageBlocks = NULL;
    
    while((option = getopt(argc,argv,":i") != -1)) {}

    inputFile = argv[optind];

    AllocatePAGING(s_blockHead, virtmempageBlocks, mempageBlocks, inputFile);

    return 0;
}
