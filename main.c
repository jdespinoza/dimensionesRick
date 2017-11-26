#include "myheader.h"

int main(int argc,char *argv[])
{
    int option;
    char *inputFile, *algoType;

    _SBLOCK *s_blockHead = NULL;
    _VIRTMEMPAGEBLOCKS *virtmempageBlocks = NULL;
    _MEMPAGEBLOCKS *mempageBlocks = NULL;
    //_MEMSEGMENTBLOCKS *memSegBlocksHead = NULL;
    
    /* reading options of type i & t
       -i = input file name
       -t = type of algorithm */
    while((option = getopt(argc,argv,":it") != -1)) {}

    inputFile = argv[optind];
    algoType = argv[optind+1];
            
    if(strcmp(algoType, "ALLMEMORY") == 0){
            //AllocateALLMemory(s_blockHead, inputFile);
            printf("hola");
    }else if(strcmp(algoType, "FCFS") == 0){
            //AllocateFCFS(s_blockHead, inputFile);
            printf("hola");
    }else if(strcmp(algoType, "PAGING") == 0){
            AllocatePAGING(s_blockHead, virtmempageBlocks, mempageBlocks, inputFile);
    }else if(strcmp(algoType, "SEGMENTATION") == 0){
            //AllocateSEGMENTATION(s_blockHead, memSegBlocksHead, inputFile);
            printf("hola");
    }else{
            printf("Error to implement algorithms,command arguments error....\n"
                    "\n   <exe_file_name>  -i <input_filename>  -t <type_of_algorithm>\n"
                    "\ne.g.: ./a.out -i \"files/process_1.txt\" -t \"ALLMEMORY\"\n"
                    "\ntype_of_algorithm = \"ALLMEMORY\" or \"FCFS\" or \"PAGING\" or \"SEGMENTATION\"\n\n");
        }

    return 0;
}
