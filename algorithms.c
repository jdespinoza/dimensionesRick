#include "myheader.h"

/*
 * Asigna un bloque de memoria para paginacion
 */
_MEMPAGEBLOCKS *allocateMemPageBlock(size_t size)
{
    _MEMPAGEBLOCKS *block = (_MEMPAGEBLOCKS *)sbrk(0);
    if(sbrk(MEM_PAGE_BLOCK_SIZE + size) == (void*) - 1){ 
		return NULL;
    }else{
        sbrk(MEM_PAGE_BLOCK_SIZE + size);
        block->next = NULL;
        block->isfree = true;
        block->memoryaddress = sbrk(0);
        return block;
    }
}

/*
 * Asigna el bloque de memoria para paginacion
 */
void allocateNextMemPageBlock(size_t size, _MEMPAGEBLOCKS **head)
{
    _MEMPAGEBLOCKS *current = *head;
    void *allocate_mem = NULL;
    if(current == NULL){
        *head = allocateMemPageBlock(size);
    }else{
        while(current->next != NULL){
            current = current->next;
        }
        //syscall: sbrk
        _MEMPAGEBLOCKS *newblock = (_MEMPAGEBLOCKS *)sbrk(0);

        allocate_mem = sbrk(MEM_PAGE_BLOCK_SIZE + size);      
        if(allocate_mem == (void*) - 1){ }
        else{
            sbrk(MEM_PAGE_BLOCK_SIZE + size);
            newblock->next = NULL;
            newblock->isfree = true;
            newblock->memoryaddress = sbrk(0);
            current->next = newblock;
      }
    }
}

/*
 * Divide la memoria en bloques de 4KB (PAGE_SIZE)
 */
void divideProc_Mem_IntoPageBlocks(_PROCINTNODE *procinthead, _VIRTMEMPAGEBLOCKS **virtmempageblockshead,
                                    _MEMPAGEBLOCKS **mempageblocksHead)
{
    _PROCINTNODE *current = procinthead;
    //inicio de paginacion
    unsigned int pagenumber = 0;
    //inicio de dirreccion de memoria
    void *address = (void*)0x12345678;

    /*
     * Divide el archivo inicial en bloques de 4KB y se inserta en una lista
     * enlazada (_VIRTMEMPAGEBLOCKS) en el disco usando sus ubicaciones
     * de memoria para formar una tabla sin formar una lista en el disco
     * antes de cargar en la memoria, y asignar una direccion de memoria
     * virtual con numero de pagina
     */
    
    while(current != NULL){
        if(current->size < PAGE_SIZE){
			//si el bloque es mas pequeno que el tamanio establecido
			//entonces solo se ubica al final de la lista enlazada
			//y sigue con el siguiente bloque
            _virtmempageblocksinsertAtEnd(current->process, PAGE_SIZE, pagenumber, address, &(*virtmempageblockshead));
            current = current->next;
        }else{
			//si el tamanio del bloque es mayor del establecido entonces
			//se ubica parte del bloque al final de la lista enlazada
			//y la otra parte del bloque en otro nodo de la lista
            _virtmempageblocksinsertAtEnd(current->process, PAGE_SIZE, pagenumber, address, &(*virtmempageblockshead));
            current->size = (current->size - PAGE_SIZE);
            pagenumber++;
            address += PAGE_MEM_SIZE;
        }
    }

    //divide la memoria en el tamanio de pagina establecido (PAGE_SIZE)
    for(int i = 0; i < MAX_PAGES; i++){
        allocateNextMemPageBlock(PAGE_MEM_SIZE, &(*mempageblocksHead));
    }
}

/*
 * Mapea la direccion virtual al la direccion fisica en la pagina
 */
void mapVirtPhyAddressPageTable(_VIRTMEMPAGEBLOCKS **virtmempageblockshead, _MEMPAGEBLOCKS **mempageblocksHead)
{
    _MEMPAGEBLOCKS *currentmem = *mempageblocksHead;
    _MEMPAGEBLOCKS *currentmem2 = *mempageblocksHead;
    _VIRTMEMPAGEBLOCKS *currentvirt = *virtmempageblockshead;
    _MEMPAGEBLOCKS *currtemp = NULL;
    int count = 0;


    printf("\n[ Memory mapped Virtual/Physical Page Table ]\n");
    printf("\n-----------------------------------------------------------------------------------");
    printf("\n|    Process    |    PageNumber    |    VirtualAddress    |    PhysicalAddress    |\n");
    printf("-----------------------------------------------------------------------------------\n");

    while(currentmem != NULL){
            if(currentmem->isfree){
					printf("|       P%d      |        %d         |     %p       |        %p      |\n",
                        currentvirt->process, currentvirt->pagenumber, currentvirt->memoryaddress, currentmem->memoryaddress);
                    
                    currentmem->isfree = false;
                    count++;

                    /* do your work here on allocated memory
                        declare your program loader code here
                    */

                    if(count == 256){
                        printf("***- 1MB block of pages loaded -***\n");
                        count = 0;
                    }
            }
			
            currentvirt = currentvirt->next;
            currentmem = currentmem->next;

            if(currentvirt == NULL){
                goto exitLoop;
            }
    }

    printf("-----------------------------------------------------------------------------------\n");


    //libera la memoria de _MEMPAGEBLOCKS
    currentmem = *mempageblocksHead;
    while(currentmem != NULL){
        if(!(currentmem->isfree)){
            currentmem->isfree = true;
            printf("Memory Frame freed, Address = %p\n", currentmem->memoryaddress);
        }
        currentmem = currentmem->next;
    }

    //llama otra vez para cumplir con todos los procesos
    mapVirtPhyAddressPageTable(&currentvirt, &(*mempageblocksHead));

exitLoop:

    //libera la memoria de _MEMPAGEBLOCKS
    currentmem = *mempageblocksHead;
    while(currentmem != NULL){
        if(!(currentmem->isfree)){
            currentmem->isfree = true;
            printf("Memory Frame freed, Address = %p\n", currentmem->memoryaddress);
        }
        currentmem = currentmem->next;
    }
}

int **myMalloc(int row, int col){
	int **grid;
	
	grid = (int **)malloc(row * sizeof(int*));
	
	for(int i = 0; i < row; i++) {
		grid[i] = (int *)malloc(col * sizeof(int));
	}
	
	return grid;
	
}

/*
int **RickMalloc(int row, int col)
{
	//_INTNODE *dataList;
	_SBLOCK *s_blockHead = NULL;
    _VIRTMEMPAGEBLOCKS *virtmempageBlocks = NULL;
    _MEMPAGEBLOCKS *mempageBlocks = NULL;
    //_NODE* head = NULL;
    _INTNODE *inthead = NULL; 
    
    //int size = row + col;
    //while (size > 0) {
		//_intinsertAtEnd(0,&(dataList));
		//head = _insertAtEnd('0',&head);
		//size--;
		
	//}
	
	
	_intinsertAtEnd(9,&inthead);
    //head ya no se usa, asi que se elimina para liberar memoria
    //_deleteCharList(&head);
    
    //free(head);
	
	_PROCINTNODE *procintHead = NULL;
    procintHead = getDataFromINTNODEList(inthead, &procintHead);
   
    divideProc_Mem_IntoPageBlocks(procintHead, &virtmempageBlocks, &mempageBlocks);
    
    printf("\n\n\t\t[ Allocate memory ]\n\n");
    
    mapVirtPhyAddressPageTable(&virtmempageBlocks, &mempageBlocks);
    
    return myMalloc(row, col);
	
}*/

/*
 * Inicio
 */
int **RickMalloc(_SBLOCK *s_blockHead,_VIRTMEMPAGEBLOCKS *virtmempageBlocks,
                   _MEMPAGEBLOCKS *mempageBlocks, const char *inputFile, int row, int col)
{
    //se obtiene los datos del archivo
    _INTNODE *dataList = getProcessData(inputFile);
    _PROCINTNODE *procintHead = NULL;
    procintHead = getDataFromINTNODEList(dataList, &procintHead);
    
    printf("\n\n\t* Reading data from file \"%s\"......\n", inputFile);

    divideProc_Mem_IntoPageBlocks(procintHead, &virtmempageBlocks, &mempageBlocks);

    printf("\n\n\t\t[ Allocate memory using Paging ]\n\n");

    mapVirtPhyAddressPageTable(&virtmempageBlocks, &mempageBlocks);
    
    return myMalloc(row, col);
}
