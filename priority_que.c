#include<stdio.h>
#include<stdlib.h>
#define size 30
struct queue{
    int items[size];
    int front,rear;
};

typedef struct queue que;

void insert(que *p){
    int item;
    printf("\nenter the item to be inserted: ");
    scanf("%d",&item);
    p->rear++;
    p->items[p->rear]=item;
}

void deletemin(que *p){
    int min,i,minindex;
    if(p->front>p->rear){
        printf("empty list");
        return;
    }
    min=p->items[p->front];
    minindex=p->front;
    for(i=1;i<=p->rear;i++){
        if(p->items[i]<min){
            min=p->items[i];
            minindex=i;
        }
    }
    for(i=minindex;i<p->rear;i++){
        p->items[i]=p->items[i+1];
    }
    printf("%d is deleted\n",min);
    p->rear--;
}

void display(que *p){
    for(int i=p->front;i<=p->rear;i++){
        printf("%d\t",p->items[i]);
    }
}

void main(){
    que p;
    p.front=0;
    p.rear=-1;
    int choice;
    printf("\n1.insert\n2.deletein\n3.exit");
    for(;;){
        printf("\nenter ur choice:");
        scanf("%d",&choice);

        switch(choice)
        {
            case 1:insert(&p);
                    display(&p);
                    break;
            case 2:deletemin(&p);
                    display(&p);
                    break;
            case 3:exit(0);
        }
    }
}
