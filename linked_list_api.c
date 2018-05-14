#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//Node struct
typedef struct list_node_t
{
    void* data;
    struct list_node_t *next;
	void (*data_type)(void*);

} list_node_t;
//Struct to create a list and store its size
typedef struct list_t
{
    struct list_node_t *head;
    int size;

} list_t;

void list_insert(list_t* list,void (*data_type)(void* p),void* value,int (*getSize)());

void print_int(void* data)
{
    printf("%d\t",*(int*)data);
}

void print_float(void* data)
{
    printf("%f\t",*(float*)data);
}

void print_char(void* data)
{
	printf("%c\t", *(char*)data);
}

void print_double(void* data)
{
	printf("%lf\t", *(double*)data);
}

void print_string(void* data)
{
    printf("%s\t",(char*)data);
}
int getIntSize(void* data)
{
    return sizeof(int);
}

int getFloatSize(void* data)
{
    return sizeof(float);
}

int getDoubleSize(void* data)
{
    return sizeof(double);
}

int getCharSize(void* data)
{
	return sizeof(char);
}

int getStringSize(void* data)
{
    return strlen((char*)data)+1;
}

void insert_String(list_t *list,char* value)
{
    list_insert(list,print_string,(void*)value,getStringSize);
}
void insert_int(list_t *list,int value)
{
  list_insert(list,print_int,(void*)&value,getIntSize);
}

void insert_float(list_t *list,float value)
{
    list_insert(list,print_float,(void*)&value,getFloatSize);
}

void insert_char(list_t *list,char value)
{
    list_insert(list,print_char,(void*)&value,getCharSize);
}

void insert_double(list_t *list,double value)
{
    list_insert(list,print_double,(void*)&value,getDoubleSize);
}

//creates a list and initializes head ptr to NULL and size to 0
list_t* create_list()
{
    list_t *list = (list_t *)calloc(1, sizeof(list_t));
    list->head = NULL;
    list->size = 0;
    return list;
}

//create a node and returns its address
list_node_t* create_node()
{
    list_node_t *node = (list_node_t * )malloc( 1 * sizeof(list_node_t));
    return node;
}

//inserts into the list
void list_insert(list_t* list,void (*data_type)(void* p),void* value,int (*getSize)())
{
    list_node_t *temp = list->head,*current;
    int flag = 0;

    if(temp == NULL)
    {
        current = temp;
        flag = 1;
    }
    else
    {
        for(temp = list->head ; temp->next != NULL ; temp = temp->next);
        current = temp->next;

    }

    current = create_node();
    current->data = malloc(getSize(value));
    current->data_type = data_type;
    memcpy(current->data,value,getSize(value));

    list->size++;
    current->next = NULL;

    if(flag == 1)
    {
        list->head = current;
    }
    else
    {
        temp->next = current;
    }

}

void display(list_t* list)
{
    if(list->head == NULL)
    {
        printf("NO VALUES!!\n");
    }

    else
    {
        list_node_t *temp;
        for(temp = list -> head ; temp != NULL ; temp = temp->next)
        {
            (*temp->data_type)(temp->data);
        }
    }
}


int main()
{

    int n = 10, integer ;
    float floatnum;
    list_t *list_1;
    list_1 = create_list();

    for( integer = 0 ; integer < 10 ; integer++)
    {
        insert_int(list_1,integer);
    }
    printf("\n");
    insert_float(list_1,89.099);
    display(list_1);

    list_t *list_2;
    list_2 = create_list();
    for( floatnum = 0 ; floatnum < 10 ; floatnum++)
    {
        insert_float(list_2,floatnum);
    }
    printf("\n");
    display(list_2);
    insert_char(list_2,'A');
    display(list_2);

    char *str="helloworld";
    insert_String(list_2,str);
    display(list_2);
    return 0;
}
