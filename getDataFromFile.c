#include "myheader.h"

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

/*
 * crea un nuevo nodo al final de la lista head
 */
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

/*
 * Inserta un nuevo nodo en la lista enlazada de enteros
 */
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

/*
 * elimina los nodos con espacios en blanco
 */
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

/*
 * Se elimina cada nodo de la lista enlazada de caracteres
 */
void _deleteCharList(_NODE **head)
{
    _NODE *current = *head;
    while(current->next != NULL){
        *head = current->next;
        free(current);
        current=*head;
    }
}

/*
 * elimina el primer nodo de la lista enlazada
 * de numeros enteros, ya que puede contener basura
 * y esto puede provocar un comportamiento no deseado
 */
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

/*
 * Forma una lista enlazada (inthead) con los numeros de tipo int
 * es decir, lo que antes era 2 4 1 5, ahora es 2415, los une
 */
void _separateNumbDatas(_NODE *head, _INTNODE **inthead)
{
	printf("P1\n");
    head = _insertAtEnd(' ',&head);
    _NODE*current = head;
    char holdStr[50];
    int index = 0;
	
	printf("P2\n");
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

/*
 * Lee el archivo ignorando los # y hace una lista enlazada
 * con los numeros que lee
 */
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

    //lee cada caracter del archivo
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
        //si hay # los ignora
        if(readData == '#'){
            readData = ' ';
            char ch;
            while((ch=getc(fp)) != '\n' && ch != EOF){
            }
            readData = '\n';
        }
                    
        //se inserta cada caracter en el head
        if(flag){
            head = _insertAtEnd(readData,&head);
        }

    } while(readData != EOF);

    fclose(fp);

    //se elimina los nodos con espacios en blanco
    for(int i=0;i<5;i++){
       head = _removeExtraSpaces(&head);
    }

    //da forma a una nueva lista enlazada (inthead)
    //con todos los numeros que se leyeron
    _separateNumbDatas(head,&inthead);

    //elimina el primer nodo (head)
    _deleteINTFront(&inthead); 

    //head ya no se usa, asi que se elimina para liberar memoria
    _deleteCharList(&head);
    free(head);


    return inthead;
}


