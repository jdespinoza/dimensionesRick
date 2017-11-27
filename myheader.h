#ifndef _MYHEADER_H
#define _MYHEADER_H


#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<stdbool.h>
#include<string.h>
#include<unistd.h>


//tamanio maximo de memoria 1MB
#define MAX_MEM_SIZE (1024*1024)    // 1048576


#define PAGE_SIZE 4096
#define MAX_PAGES 256
#define PAGE_MEM_SIZE 0x256


#define MAX_SEGMENT_SIZE 256000 //256 KB


//estructua para ubicar memoria fisica usando FCFS o ALL
typedef struct __s_block{
    struct __s_block *next;
    struct __s_block *prev;
    bool isfree;
    size_t size;
}_SBLOCK;



#define BLOCK_SIZE sizeof(_SBLOCK)


//estructura para almacenar en la memoria virtual usando paginas
typedef struct __memvirtpageblocks{
    struct __memvirtpageblocks *next;
    size_t size;
    int process;
    int pagenumber;
    void *memoryaddress;
}_VIRTMEMPAGEBLOCKS;


//estructura para almacenar en la memoria fisica usando paginas
typedef struct __mempageblocks{
    struct __mempageblocks *next;
    bool isfree;
    void *memoryaddress;
}_MEMPAGEBLOCKS;



#define MEM_PAGE_BLOCK_SIZE sizeof(_MEMPAGEBLOCKS)

//no se usa
//structure for allocate memory using segmentation
typedef struct __memsegmentblocks{
    struct __memsegmentblocks *next;
    bool isfree;
    size_t size;
    void *memoryaddress;
}_MEMSEGMENTBLOCKS;



#define MEM_SEGMENT_BLOCK_SIZE sizeof(_MEMSEGMENTBLOCKS)


//estrctura que almacena informacion de un archivo en un caracter
typedef struct __node {
    char data;
    struct __node *next;
}_NODE;

typedef struct __intnode {
    int data;
    struct __intnode *next;
}_INTNODE;


//estructura para almacenar datos enteros 
typedef struct __procintnode {
    int process;
    int size;
    struct __procintnode *next;
}_PROCINTNODE;


//getDataFromFile.c, memoryListFunctions.c , algorithms.c
extern _NODE* _createNewNode(char );
extern _INTNODE* _intcreateNewNode(int );
extern _NODE* _insertAtEnd(char , _NODE **);
extern _INTNODE* _intinsertAtEnd(int , _INTNODE **);
extern _NODE* _removeExtraSpaces(_NODE** );
extern int _countINTNodes(_INTNODE *);
extern void _deleteCharList(_NODE **);
extern void _deleteINTList(_INTNODE **);
extern _INTNODE *_deleteINTFront(_INTNODE **);
extern _INTNODE *_deleteINTEnd(_INTNODE **);
extern _INTNODE* _deleteINT_FromSecondNode(_INTNODE **);
extern void _separateNumbDatas(_NODE *head, _INTNODE **);
extern _INTNODE *getProcessData(const char *);
extern _PROCINTNODE* _procintcreateNewNode(int ,int );
extern _VIRTMEMPAGEBLOCKS* _virtmempageblockscreateNewNode(int ,size_t ,int ,void *);
extern _PROCINTNODE* _procintinsertAtEnd(int ,int , _PROCINTNODE **);
extern _VIRTMEMPAGEBLOCKS* _virtmempageblocksinsertAtEnd(int ,size_t ,int ,void *, _VIRTMEMPAGEBLOCKS **);
extern _PROCINTNODE *getDataFromINTNODEList(_INTNODE *, _PROCINTNODE **);
extern int getProcessMemSizeSum(_PROCINTNODE *);
extern int _countPROCINTNodes(_PROCINTNODE *);
extern void _deleteProcINTNode_ZeroData(_PROCINTNODE **);
extern bool _isMemoryEnough(int );
extern _SBLOCK *allocateMemBlock(size_t );
extern void allocateNextMemBlock(size_t , _SBLOCK **);
extern _MEMPAGEBLOCKS *allocateMemPageBlock(size_t );
extern void allocateNextMemPageBlock(size_t , _MEMPAGEBLOCKS **);
extern _MEMSEGMENTBLOCKS *allocateMemSegmentBlock(size_t );
extern void allocateNextMemSegmentBlock(size_t , _MEMSEGMENTBLOCKS **);
extern void allocate_allMemory(_SBLOCK **,_PROCINTNODE *);
extern void allocate_using_FCFS(_SBLOCK **, _PROCINTNODE * );
extern void divideProc_Mem_IntoPageBlocks(_PROCINTNODE *, _VIRTMEMPAGEBLOCKS **,  _MEMPAGEBLOCKS **);
extern void mapVirtPhyAddressPageTable(_VIRTMEMPAGEBLOCKS **,_MEMPAGEBLOCKS ** );
extern void allocateMemory_using_Segmentation(_PROCINTNODE **,_MEMSEGMENTBLOCKS **);
extern void getFreeMemoryAddress(_MEMSEGMENTBLOCKS *,unsigned int ,void **);
extern void allocateMemory_using_Segment_remain(_PROCINTNODE **,_MEMSEGMENTBLOCKS **);
extern void AllocateALLMemory(_SBLOCK *, const char *);
extern void AllocateFCFS(_SBLOCK *, const char *);
extern int **RickMalloc(_SBLOCK *, _VIRTMEMPAGEBLOCKS *, _MEMPAGEBLOCKS *, const char *, int, int);
extern void AllocateSEGMENTATION(_SBLOCK *, _MEMSEGMENTBLOCKS *, const char *);
extern int **myMalloc(int , int );
//extern int **RickMalloc(int , int );




#endif
