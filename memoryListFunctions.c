#include "myheader.h"

_PROCINTNODE* _procintcreateNewNode(int process, int size)
{
    _PROCINTNODE *newNode = NULL;
    newNode=(_PROCINTNODE*)malloc(sizeof(_PROCINTNODE));
    if(newNode == NULL) {
        printf("Memory allocation error\n");
        return NULL;
    }
    newNode->process = process;
    newNode->size = size;
    newNode->next = NULL;
    return newNode;
}

/*
 * Crea un nuevo nodo
 */
_VIRTMEMPAGEBLOCKS* _virtmempageblockscreateNewNode(int process, size_t size, int pagenumber, void *memoryaddress)
{
    _VIRTMEMPAGEBLOCKS *newNode = NULL;
    newNode=(_VIRTMEMPAGEBLOCKS*)malloc(sizeof(_VIRTMEMPAGEBLOCKS));
    if(newNode == NULL) {
        printf("Memory allocation error\n");
        return NULL;
    }
    newNode->process = process;
    newNode->size = size;
    newNode->pagenumber=pagenumber;
    newNode->memoryaddress=memoryaddress;
    newNode->next = NULL;
    return newNode;
}

/*
 * Inserta un nuevo nodo al final de la lista de PROCINTNODE
 */
_PROCINTNODE* _procintinsertAtEnd(int process, int size, _PROCINTNODE **head)
{
    _PROCINTNODE *current = *head;
    if (current == NULL) {
        *head = _procintcreateNewNode(process, size);
    }else{
        while(current->next != NULL){
            current = current->next;
        }
        current->next = _procintcreateNewNode(process, size);
    }
    return *head;
}

/*
 * Inserta un nodo al final de lista enlazada de la memoria virtual
 */
_VIRTMEMPAGEBLOCKS* _virtmempageblocksinsertAtEnd(int process,size_t size,int pagenumber,
                                                void *memoryaddress, _VIRTMEMPAGEBLOCKS **head)
{
    _VIRTMEMPAGEBLOCKS *current = *head;
    if (current == NULL) {
        *head = _virtmempageblockscreateNewNode(process, size, pagenumber, memoryaddress);
    }else{
        while(current->next != NULL){
            current = current->next;
        }
        current->next = _virtmempageblockscreateNewNode(process, size, pagenumber, memoryaddress);
    }
    return *head;
}

/*
 * Crea una nueva lista de _PROCINTNODE, segun lo leido de la lista
 * de INTNODE
 */
_PROCINTNODE *getDataFromINTNODEList(_INTNODE *inthead, _PROCINTNODE **prochead)
{
    _INTNODE *current = inthead;
    int count = 0;
    int process;
    //no hace falta inicializar process con un valor porque siempre se
    //cumplen las condiciones deseadas
    while(current != NULL){
        count++;
        switch(count){
            case 1 : process = current->data;
                    current = current->next;
                    break;

            case 2 : 
                    *prochead = _procintinsertAtEnd(process, current->data, &(*prochead));
                    count = 0;
                    current = current->next;
                    break;
            }
    }
    return *prochead;
}
