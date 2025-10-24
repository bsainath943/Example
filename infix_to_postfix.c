//infix to postfix convertion and evaluation
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
//infix to postfix converstion
struct stack1{
    char items[30];
    int top;
};



fdlk;
typedef struct stack1 stk1;

void push1(stk1 *ps,char ch){
    ps->top++;
    ps->items[ps->top]=ch;
}

char pop1(stk1 *ps){
    char ch=ps->items[ps->top];
    ps->top--;
    return ch;
}

int isoperand(char ch){
    switch(ch)
    {
        case '+':
        case '-':
        case '*':
        case '/':
        case '(':
        case ')':
        case '&':
        case '^':return 0;
        default:return 1;
    }
}

int stkpre(char ch){
    switch(ch)
    {
        case '+':
        case '-':return 1;
        case '*':
        case '/':return 3;
        case '&':
        case '^':return 6;
        case '(':return 0;
    }
}

int inpre(char ch){
    switch(ch)
    {
        case '+':
        case '-':return 2;
        case '*':
        case '/':return 4;
        case '&':
        case '^':return 7;
        case '(':return 9;
        case ')':return 0;
    }
}

void inpos(char infix[],char pofix[]){
    stk1 opr;
    opr.top=-1;
    int i=0,j=0;
    char ch;
    while((ch=infix[i++])!='\0'){
        if(isoperand(ch)){
            pofix[j++]=ch;
        }
        else
        {
            while(opr.top!=-1 && stkpre(opr.items[opr.top])>inpre(ch)){
                if(ch==')'){
                    while(opr.items[opr.top]!='('){
                        pofix[j++]=pop1(&opr);
                    }
                    pop1(&opr);
                }
                else
                {
                    pofix[j++]=pop1(&opr);
                }

            }
            if(ch!=')')
            {
                push1(&opr,ch);
            }

        }

    }
    while (opr.top != -1) {
        pofix[j++] = pop1(&opr);
    }
    pofix[j] = '\0';// Ensure postfix expression is null-terminated
}

//evaluation of postfix expression
float compute(float opr1,float opr2,char ch){
    switch(ch)
    {
        case '+':return opr1+opr2;
        case '-':return opr1-opr2;
        case '*':return opr1*opr2;
        case '/':return opr1/opr2;
        case '&':
        case '^':return pow(opr1,opr2);
    }
}

struct stack2{
    float items[30];
    int top;
};
typedef struct stack2 stk2;

void push2(stk2 *es,float n){
    es->top++;
    es->items[es->top]=n;
}

float pop2(stk2 *es){
    float n=es->items[es->top];
    es->top--;
    return n;
}

void evalpos(char pofix[]){
    int i=0;
    float n;
    stk2 es;
    es.top=-1;
    char ch;
    float opr1,opr2,result;
    while((ch=pofix[i++])!='\0'){
        if(isoperand(ch)){
            printf("enter the vale for %c",ch);
            scanf("%f",&n);
            push2(&es,n);
        }
        else{
            opr2=pop2(&es);
            opr1=pop2(&es);
            result=compute(opr1,opr2,ch);
            push2(&es,result);
        }
    }
    result=pop2(&es);
    if(es.top!=-1)
    printf("invlaid expression");
    else
    printf("valid %f",result);
}


void main(){
    int choice;
    char infix[30],pofix[30];
    printf("\n1.enter infix expression\n2.infix to postfix\n3.evaluate postfix\n4.exit");
    for(;;){
        printf("\nenter the choice");
        scanf("%d",&choice);
        switch(choice)
        {
            case 1:printf("enter the infix expression");
                    scanf("%s",infix);
                    break;
            case 2:inpos(infix,pofix);
                    printf("%s",pofix);
                    break;
            case 3:evalpos(pofix);
                    break;
            case 4:printf("Thank you");
                    exit(0);
                    break;
            default:printf("invalid choice");
        }
    }
}
