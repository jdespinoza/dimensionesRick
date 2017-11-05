#include "myheader.h"


/***************************************************************************/
/* function create new node with input data as integer type in linked list _PROCINTNODE*/
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


/***************************************************************************/
/* function create new node of _VIRTMEMPAGEBLOCKS of linked list */
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


/***************************************************************************/
/* function to insert new node at the end of list _PROCINTNODE */
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



/***************************************************************************/
/* function to insert new node at the end of list _VIRTMEMPAGEBLOCKS */
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


/***************************************************************************/
/* function to create new list of _PROCINTNODE by reading data from _INTNODE list */
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
_PROCINTNODE *getDataFromINTNODEList(_INTNODE *inthead, _PROCINTNODE **prochead)
{
    _INTNODE *current = inthead;
    int count = 0;
    int process;
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


/***************************************************************************/
/* function that returns total memory size required by all processes */
int getProcessMemSizeSum(_PROCINTNODE *procinthead)
{
    int sum = 0;
    while(procinthead != NULL){
        sum += procinthead->size;
        procinthead = procinthead->next;
    }
    return sum;
}



/*******************************************************/
/* function to count nodes of integer type linked list _PROCINTNODE*/
int _countPROCINTNodes(_PROCINTNODE *prochead)
{
    int count = 0;
    while(prochead != NULL){
        count++;
        prochead = prochead->next;
  }
    return count;
}


/**********************************************************************/
/* function to delete node whose contain 0 value in _PROCINTNODE list */
void _deleteProcINTNode_ZeroData(_PROCINTNODE **procinthead)
{
    _PROCINTNODE *current = *procinthead;
    _PROCINTNODE *temp = *procinthead;

    if(current == NULL) { }else{
        if(_countPROCINTNodes(current) == 1){
            if(current->size == 0){
                *procinthead=NULL;
                free(current);
            }
        }else{
            while(current != NULL){
                if(current->size == 0){
                    temp->next = current->next;
                    free(current);
                    current = temp->next;
                }else{
                    temp = current;
                    current = current->next;
                }
            }
        }
    }
    current = *procinthead;
    if(current-> size == 0){
        *procinthead = current->next;
    }
}



