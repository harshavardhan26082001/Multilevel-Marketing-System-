#include<stdio.h>
#include<stdlib.h>
#define SIZE 1024
#define word 4
typedef struct heap_element_type 
{
    int address;
    int size;
    struct heap_element_type* next;
}heap_Node;
typedef struct heap_type
{
    heap_Node* alloc_ptr;
    heap_Node* free_ptr;
}heap;
heap_Node* Create_Node(int address,int size)
{
    heap_Node* hnptr=(heap_Node*)malloc(sizeof(heap_Node));
    hnptr->address=address;
    hnptr->size=size;
    hnptr->next=NULL;
    return hnptr;
}
void Initialise_heap(heap* hptr)
{
    hptr->alloc_ptr=NULL;
    hptr->free_ptr=Create_Node(0,256);
}
void print(heap_Node* lptr)
{
    if(lptr!=NULL)
    {
        heap_Node* tptr=lptr;
        while(tptr!=NULL)
        {
            printf("ADDRESS               :%d\n",tptr->address);
            printf("SIZE(in bits)         :%d\n",tptr->size*4);
            printf("No of words allocated :%d\n",tptr->size);
            printf("\n"); 
            tptr=tptr->next;
        }
    }
    else
    {
        printf("Empty\n");
    }
    
}
//FREE METHOD
void free_type(heap* hptr,int address)
{
    
    heap_Node* tptr=hptr->alloc_ptr,*prev=NULL;
    int found=0;
    
    while(tptr!=NULL && found==0)
    {
      
        if(tptr->address==address)
        found=1;
        else
        {
            prev=tptr;
            tptr=tptr->next;
        }
    }
    if(found==1)
    {
        if(prev==NULL)
        {
            hptr->alloc_ptr=tptr->next;
        }
        else
        {
            prev->next=tptr->next;
        }
        
        heap_Node* tail,*middle=NULL,*ahead=hptr->free_ptr,*temp;
        int found2=0;
        while(ahead!=NULL && found2==0)
        {
            
            if (ahead->address>tptr->address)
            found2=1;
            else
            {
                tail=middle;
                middle=ahead;
                ahead=ahead->next;
            }
        }
            if(found2==1)
            {
                if(middle==NULL)
                {
                    if(tptr->address+tptr->size==ahead->address)
                    {
                        temp=Create_Node(tptr->address,ahead->size+tptr->size);
                        temp->next=ahead->next;
                        free(ahead);
                    }
                    else
                    {
                        temp=Create_Node(tptr->address,tptr->size);
                        temp->next=ahead;
                    }
                    hptr->free_ptr=temp;
                }
                else
                {
                    int flag1=0,flag2=0;
                
                    if(tptr->address==middle->address+middle->size)
                    flag1=1;

                    if(tptr->address+tptr->size==ahead->address)
                    flag2=1;
                    
                    if(flag1==1 && flag2==1)
                    {
                        temp=Create_Node(middle->address,middle->size+tptr->size+ahead->size);
                        temp->next=ahead->next;
                        if(tail==NULL)
                        {
                            hptr->free_ptr=temp;
                        }
                        else
                        {
                            tail->next=temp;
                        }
                        free(middle);
                        free(ahead);
                    }
                    else if(flag1==1)
                    {
                        temp=Create_Node(middle->address,middle->size+tptr->size);
                        temp->next=ahead;
                        if(tail==NULL)
                        {
                            hptr->free_ptr=temp;
                        }
                        else
                        {
                            tail->next=temp;
                        }
                        free(middle);
                    }
                    else if(flag2==1)
                    {
                        temp=Create_Node(tptr->address,ahead->size+tptr->size);
                        temp->next=ahead->next;
                        free(ahead);
                        middle->next=temp;
                    }
                    else
                    {
                        temp=Create_Node(tptr->address,tptr->size);
                        temp->next=ahead;
                        middle->next=temp;
                    }
                }
            }
            else
            {
                    if(tptr->address==middle->address+middle->size)
                    {
                        temp=Create_Node(middle->address,middle->size+tptr->size);
                        tail->next=temp;
                        free(middle);
                    }
                    else
                    {
                        temp=Create_Node(tptr->address,tptr->size);
                        middle->next=temp;
                    }
                    temp->next=NULL;
            }
            
        
    }
    else
    {
        printf("No element exits at address you entered\n");
    }
    
}
int  allocation(heap* hptr,int size)
{
    heap_Node* tptr=hptr->free_ptr,*prev=NULL;
    int found=0,diff=257;
    int address;

    while(tptr!=NULL)
    {
        if((tptr->size)>=size)
        {
            found=1;
            if((tptr->size)-size<diff)
            {
                diff=(tptr->size)-size;
                address=tptr->address;
            }
        }
        tptr=tptr->next;
    }
    if (found==1)
    {
        int found3=0;
        tptr=hptr->free_ptr;
        while(tptr!=NULL && found3==0)
        {
            if(tptr->address==address)
            found3=1;
            else
            {
                prev=tptr;
                tptr=tptr->next;
            }
        }
       
        if(tptr->size==size)
        {

            if(prev==NULL)
            hptr->free_ptr=NULL;
            else
            prev->next=tptr->next;

        }
        else
        {
            
            heap_Node* temp=Create_Node(tptr->address,size);
            
            tptr->address+=size;
            tptr->size-=size;
            tptr=temp;
        }
        //ADDDING TO ALLOCATION LIST
        tptr->next=hptr->alloc_ptr;
        hptr->alloc_ptr=tptr;
    }
    else
    {
        printf("Memory is full\n");
        address=-1;
    }
    return address;
}
int main()
{
    heap hp;
    Initialise_heap(&hp);
    int flag=1,option,size,address;
    char c_option;
    printf("SIZE OF MEMORY IS 1024 bits\nIt composed of words with word size 4 bits\n\n");
    printf("Enter the respective numbers to perform following operations:\n");
    printf("1-allocation\n");
    printf("2-free operation deallocation\n");
    while(flag==1)
    {
        printf("Enter the option:\n");
        scanf("%d",&option);
        if(option==1)
        {
            printf("Enter the size u want to allocate(in bits):");
            scanf("%d",&size);

            if(size%4==0)
            size/=4;
            else
            size=(size/4)+1;
            address=allocation(&hp,size);
            if(address>=0)
            printf("Address of allocated space:%d\n",address);
        }
        else
        {
            printf("Enter the address u want to free:");
            scanf("%d",&address);
            free_type(&hp,address);
        }
        printf("\nALLOCATION LIST:\n\n");
        print(hp.alloc_ptr);
        printf("\n");
        printf("FREE LIST:\n\n");
        print(hp.free_ptr);
        printf("\n");
        printf("whether u want to perform any operation again(enter y(1)/n(0)):");
        printf("\n");
        scanf("%d",&flag);
    } 
    return 0;  
}
