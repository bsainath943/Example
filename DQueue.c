#include<stdio.h>
#include<stdlib.h>
int size;

struct dq{
    int *items;
    int front,rare;
};
typedef struct dq q;

void insert_rare(q *pq){
    int val;
    if(pq->rare==size-1){
        printf("que is overflow\nReallocating memory");
        pq->items=(int *)realloc(pq->items,size*2*sizeof(int));
        printf("\nenter the value to be inserted");
        scanf("%d",&val);   
        *(pq->items+ ++pq->rare)=val;
    }
    else{
       printf("enter the value to be inserted");
        scanf("%d",&val);   
        *(pq->items+ ++pq->rare)=val;
    }
}

void delete_front(q *pq){
    if(pq->front==0 && pq->rare==-1){
        printf("que underflow");
    }
    else{
        printf("deleted item is %d",*(pq->items+pq->front));
        pq->front++;
    }
}

void insert_front(q *pq){
    int val;
     if(pq->front==0 && pq->rare>=0){
        printf("front insertion is not possible");
    }
    if(pq->front==0 && pq->rare==-1){
        printf("enter the item to be inserted");
        scanf("%d",&val);
        *(pq->items+ ++pq->rare)=val;
    }
    if(pq->front!=0){
         printf("enter the item to be inserted");
        scanf("%d",&val);
        *(pq->items+ --pq->front)=val;
    }
}

void delete_rare(q *pq){
    if(pq->rare==-1 && pq->front==0){
        printf("que underflow");
    }
    else{
        printf("deleted item is %d",*(pq->items+pq->rare));
        pq->rare--;
    }
}

void display(q *pq){
    if(pq->rare==-1 && pq->front==0){
        printf("que underflow");
    }
    else{
        for(int i=pq->front;i<=pq->rare;i++){
            printf("%d",*(pq->items+i));
        }
    }
}

void main(){
    int choice;
    q pq;
    pq.front=0;
    pq.rare=-1;
    printf("enter the size of the que");
    scanf("%d",&size);
    pq.items=(int *)malloc(size*sizeof(int));
    printf("\nMenu\n1.insert front\n2.insert rare\n3.delete front\n4.delete rare\n5.display\n6.exit");
    for(;;){
        printf("\nenter the choice");
        scanf("%d",&choice);

        switch(choice)
        {
            case 1:insert_front(&pq);
                break;
            case 2:insert_rare(&pq);
                break;
            case 3:delete_front(&pq);
                break;
            case 4:delete_rare(&pq);
                break;
            case 5:display(&pq);
                break;
            case 6:exit(0);
        }
    }
}
