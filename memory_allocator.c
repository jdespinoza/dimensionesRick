#include <stdio.h>
#include <stdbool.h>

/*
 * estructura de lista enlazada
 * next, puntero que apunta al proximo bloque de memoria
 * isfree, indica si el memory block esta libre o no
 * size, tamanio que se asigna a la memoria
 * memoryAddress, direccion de memria donde se asigna
 * BLOCK_SIZE, tamanio de la estructura
 */
typedef struct __s_block{
    struct __s_block *next;
    bool isfree;
    size_t size;
    void *memoryAddress;
}_SBLOCK;


#define BLOCK_SIZE sizeof(_SBLOCK)

/*
 * Allocate Memory Block
 * Toma como argumento el tamanio de memoria que desea asignar
 * Simplemente crea un nodo, y hace la configuracion de la memoria
 * 
 */

_SBLOCK *allocateMemBlock(size_t size) {
	
	//sbrk, syscall, me brinda memoria, el parametro es la cantidad
	//de bytes que incrementa en el espacio de datos del programa
	//se puede ver como si sbrk fuera un malloc
    _SBLOCK *block = (_SBLOCK*)sbrk(0);
    void *memadr = (void*)sbrk(0);
    void *allocate_mem = (void*)sbrk(BLOCK_SIZE + size);

    if(allocate_mem == (void*)-1){
		//error en el momento de incrementar
        return NULL;
    }else{
        block->next = NULL;
        block->isfree = false;
        block->size = size;
        block->memoryAddress = memadr+BLOCK_SIZE;
        return block;
    }
    
}

/*
 * Agrega un nodo a la lista enlazada
 * SIempre se agrega al final
 */
void allocateNextMemBlock(size_t size, _SBLOCK **head) {
	
    _SBLOCK *current = *head;
    void *allocate_mem = NULL;
    void *memadr = (void*)sbrk(0);

    if(current==NULL){
        *head = allocateMemBlock(size);
    }else{
        while(current->next != NULL){
            current = current->next;
        }
        _SBLOCK *newblock = sbrk(0);

        allocate_mem = (void*)sbrk(BLOCK_SIZE + size);      
        if(allocate_mem == (void*) - 1){ }
        else{
            newblock->next = NULL;
            newblock->isfree = false;
            newblock->size = size;
            newblock->memoryAddress = memadr+BLOCK_SIZE;
            current->next = newblock;
      }
    }
    
}

/*
 * Cuando se libera la memoria solo se sobreescribe los datos
 * en otras palabras, poner el campo isfree en verdadero, asi
 * cuando otro bloque quiera asignar memoria, solo debera de 
 * verificar que esta variable este en verdadero
 */

void freeMemBlock(_SBLOCK **head) {
	
    if(*head == NULL){}
    else{
        (*head)->isfree = true;
    }
    
}

/*
 * Imprime la lista enlazada
 */
void printMemBlocks(_SBLOCK *current) {
	
    while(current != NULL){
        printf("isfree = %d, size = %d, memoryAddress = %p, current = %p, next-node = %p\n",
                current->isfree, current->size, current->memoryAddress, current, current->next);
        current = current->next;
    }
    
}

int main() {
	
    _SBLOCK *sMemBlock = NULL;
    allocateNextMemBlock(10,&sMemBlock);
    allocateNextMemBlock(35,&sMemBlock);
    allocateNextMemBlock(62,&sMemBlock);
    printMemBlocks(sMemBlock);
    
    printf("\nAfter freeing second node\n");
    freeMemBlock(&(sMemBlock->next));
    printMemBlocks(sMemBlock);

    return 0;

}
