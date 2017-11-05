#include "myheader.h"


/********************************************************************************/
/* function to create new node with input data as character type in linked list */
///////////////////////////////////////
/////////////////////////////////////////
/////////////////////////////////////////
/////////////////////////////////////////
_NODE* _createNewNode(char data)
{
    _NODE *newNode = NULL;
    newNode=(_NODE*)malloc(sizeof(_NODE));
    if(newNode == NULL) {
        printf("Memory allocation error\n");
        return NULL;
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}


/***************************************************************************/
/* function create new node with input data as integer type in linked list */
///////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////
/////////////////////////////////////////////////
_INTNODE* _intcreateNewNode(int data)
{
    _INTNODE *newNode = NULL;
    newNode=(_INTNODE*)malloc(sizeof(_INTNODE));
    if(newNode == NULL) {
        printf("Memory allocation error\n");
        return NULL;
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

/*******************************************************************/
/* function to insert new node of type character at the end of list */
//////////////////////////////////////////
//////////////////////////////////////////
////////////////////////////////////////////
////////////////////////////////////////////
_NODE* _insertAtEnd(char data, _NODE **head)
{
    _NODE *current = *head;
       if (current == NULL) {
        *head = _createNewNode(data);
    }else{
        while(current->next != NULL){
            current = current->next;
        }
        current->next = _createNewNode(data);
    }
    return *head;
}


/******************************************************************/
/* function to insert new node of type integer at the end of list */
/////////////////////////////////////////////////
///////////////////////////////////////////////////
///////////////////////////////////////////////////
////////////////////////////////////////////////////
_INTNODE* _intinsertAtEnd(int data, _INTNODE **head)
{
    _INTNODE *current = *head;
       if (current == NULL) {
        *head = _intcreateNewNode(data);
    }else{
        while(current->next != NULL){
            current = current->next;
        }
        current->next = _intcreateNewNode(data);
    }
    return *head;
}


/*******************************************************************************************/
/* function to remove nodes when more than one space characters occures in the linked list */
//////////////////////////////////////
/////////////////////////////////////
////////////////////////////////////
////////////////////////////////////
_NODE* _removeExtraSpaces(_NODE** head)
{
    _NODE*current = *head;
    while(current->next != NULL){
        if(current->data == ' '){
            if((current->next)->data == ' '){
                _NODE*temp = (current->next)->next;
                free(current->next);
                current->next = temp;
            }
        }
        current = current->next;
    }
    return *head;
}


/*******************************************************/
/* function to count nodes of integer type linked list */
/*
int _countINTNodes(_INTNODE *head)
{
    int count=0;
    while(head != NULL){
        count++;
        head=head->next;
  }
    return count;
}
*/

/*************************************************/
/* function to delete character type linked list */
////////////////////////////////////////////////
//////////////////////////////////////////////////
/////////////////////////////////////////////
/////////////////////////////////////////////
void _deleteCharList(_NODE **head)
{
    _NODE *current = *head;
    while(current->next != NULL){
        *head = current->next;
        free(current);
        current=*head;
    }
}


/*********************************************/
/* function to delete intger type linked list */
/*
void _deleteINTList(_INTNODE **inthead)
{
    _INTNODE *current = *inthead;
    while(current != NULL){
        *inthead = current->next;
        free(current);
        current=*inthead;
    }
}
*/

/***********************************************************/
/* function to delete front node from integer type of list */
/////////////////////////////////////////////////
///////////////////////////////////////////////
////////////////////////////////////////////////
/////////////////////////////////////////////////
_INTNODE *_deleteINTFront(_INTNODE **inthead)
{
    _INTNODE *current = *inthead;
    if(current == NULL) {
        printf("\nList is empty\n");
        return NULL;
    }else{
        *inthead = current->next;
        free(current);
    }
    current = current->next;
    return *inthead;
}


/**********************************************************/
/* function to delete last node from integer type of list */
/*
_INTNODE *_deleteINTEnd(_INTNODE **inthead)
{
    _INTNODE *current = *inthead;

    if(_countINTNodes(current) >= 2){
        while((current->next)->next != NULL){
            current=current->next;
        }
        free(current->next);
        current->next=NULL;
    }else{
        return _deleteINTFront(&(*inthead));
    }

    return *inthead;
}
*/

/*************************************************************************************/
/* function to delete node when its data is 0, starting from second node of the list */
/*
_INTNODE* _deleteINT_FromSecondNode(_INTNODE **inthead)
{
    _INTNODE *headTemp = *inthead;
    if(_countINTNodes(*inthead) > 1){
        _INTNODE*current = (*inthead)->next;

        while(current != NULL){
            if(current->data == 0){
                headTemp->next = current->next;
                free(current);
                current = headTemp->next;
            }else{
                break;
            }
        }
    }
    return headTemp;
}
*/

/**********************************************************************************************/
//get each char node value from _NODE structure,
// insert node with data space at the end,
//check if that data is space or not,
//if it is space then insertNewNode at the end of integer type of linked list using atoi() function,
//otherwise hold that value in variable(holdstr),
//this function separate the data,what we actually want from file
// e.g: 1 2 45  67  234  943  (each are separate characters in char type linked list,9,4 & 3 are characters)
// returns: 1 2 45 67 234 943 (each are integers stored in integer type of linked list)
////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
void _separateNumbDatas(_NODE *head, _INTNODE **inthead)
{
    head = _insertAtEnd(' ',&head);
    _NODE*current = head;
    char holdStr[50];
    int index = 0;

    while(current != NULL){
        if(current->data == ' '){
                holdStr[index] = '\0';
                _intinsertAtEnd(atoi(holdStr),&(*inthead));
                index = 0;
               holdStr[index] = '\0';
               current = current->next;
        }else{
                holdStr[index] = current->data;
                index++;
                current = current->next;
            }
        }
}


/*********************************************************/
/* function to read file by skipping comments & 
call above functions to make integer type of linked list*/
//////////////////////////////////////////////////////
///////////////////////////////////////////////////////
/////////////////////////////////////////////////////
_INTNODE *getProcessData(const char *filename)
{
    _NODE* head = NULL;
    _INTNODE *inthead = NULL;   
    FILE *fp;
    char readData;
    bool flag = false;

    fp=fopen(filename,"r");
    if(fp == NULL) {
        printf("File openning error\n");
        exit(0);
    }

    //read each character from file
    do{
        readData = getc(fp);
        if(readData == ' '&& !flag){
            flag = false;
        }
        else{
            flag=true;
        }

        if(readData=='\t'){
            readData=' ';
        }
        /* check # character and EOF character occurs or not
        when # sign occurs keep reading data from file without adding it to list */
        if(readData == '#'){
            readData = ' ';
            char ch;
            while((ch=getc(fp)) != '\n' && ch != EOF){
            }
            readData = '\n';
        }
                    
        //inserting each char value to linked list
        if(flag){
            head = _insertAtEnd(readData,&head);
        }

    } while(readData != EOF);

    fclose(fp);

    //remove extra spaces from char type linked list
    for(int i=0;i<5;i++){
       head = _removeExtraSpaces(&head);
    }

    //separate integer data values & store them into new linked list(inthead)
    _separateNumbDatas(head,&inthead);

    //delete unnecessary character(0),which is head
    _deleteINTFront(&inthead); 

    //once intger list is created,then delete the character type list
    _deleteCharList(&head);
    free(head);


    return inthead;
}


