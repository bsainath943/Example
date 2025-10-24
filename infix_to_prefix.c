#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<math.h>

// Stack structure for operators
struct stack1 {
    char items1[30];
    int top;
};
typedef struct stack1 stk1;

// Stack structure for operands
struct stack2 {
    char items2[30][30];  // Each element can store up to 30 characters
    int top;
};
typedef struct stack2 stk2;

void push1(stk1 *ps, char ch) {
    ps->top++;
    ps->items1[ps->top] = ch;
}

char pop1(stk1 *ps) {
    char ch = ps->items1[ps->top];
    ps->top--;
    return ch;
}

void push2(stk2 *ps, char *ch) {
    ps->top++;
    strcpy(ps->items2[ps->top], ch);
}

char* pop2(stk2 *ps) {
    char *ch = ps->items2[ps->top];
    ps->top--;
    return ch;
}

int isoperand(char ch) {
    switch (ch) {
        case '+':
        case '-':
        case '*':
        case '/':
        case '(':
        case ')':
        case '&':
        case '^':
            return 0;
        default:
            return 1;
    }
}

int stkpre(char ch) {
    switch (ch) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 3;
        case '&':
        case '^':
            return 6;
        case '(':
            return 0;
    }
    return -1;  // Default case to handle unexpected characters
}

int inpre(char ch) {
    switch (ch) {
        case '+':
        case '-':
            return 2;
        case '*':
        case '/':
            return 4;
        case '&':
        case '^':
            return 7;
        case '(':
            return 9;
        case ')':
            return 0;
    }
    return -1;  // Default case to handle unexpected characters
}

void partial(stk1 *ps1, stk2 *ps2) {
    char opr, s[2], *op1, *op2;
    char par[30];
    opr = ps1->items1[ps1->top--];
    s[0] = opr;
    s[1] = '\0';

    op2 = pop2(ps2);
    op1 = pop2(ps2);

    strcpy(par, s);
    strcat(par, op1);
    strcat(par, op2);

    push2(ps2, par);
}

void inprefix(char infix[], char prefix[]) {
    stk1 s1;
    s1.top = -1;
    stk2 s2;
    s2.top = -1;
    int i = 0, j = 0;
    char ch, s[2];
    while ((ch = infix[i++]) != '\0') {
        if (isoperand(ch)) {
            s[0] = ch;
            s[1] = '\0';
            push2(&s2, s);
        } else {
            while (s1.top != -1 && stkpre(s1.items1[s1.top]) > inpre(ch)) {
                if (ch == ')') {
                    while (s1.items1[s1.top] != '(') {
                        partial(&s1, &s2);
                    }
                    pop1(&s1);
                } else {
                    partial(&s1, &s2);
                }
            }
            if (ch != ')') {
                push1(&s1, ch);
            }
        }
    }
    while (s1.top != -1) {
        partial(&s1, &s2);
    }
    strcpy(prefix, s2.items2[s2.top]);
}

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

struct stack3{
    float items[30];
    int top;
};
typedef struct stack3 stk3;

void push3(stk3 *ps,float n){
    ps->top++;
    ps->items[ps->top]=n;
}

float pop3(stk3 *ps){
    float n=ps->items[ps->top--];
    return n;
}

void evalprefix(char prefix[]) {
    int i=strlen(prefix)-1;
    float n;
    stk3 es;
    es.top=-1;
    char ch;
    float opr1,opr2,result;
    while(i>=0 && (ch=prefix[i--])!='\0'){
        if(isoperand(ch)){
            printf("enter the vale for %c",ch);
            scanf("%f",&n);
            push3(&es,n);
        }
         else{
            opr2=pop3(&es);
            opr1=pop3(&es);
            result=compute(opr1,opr2,ch);
            push3(&es,result);
        }
    }
    result=pop3(&es);
    if(es.top!=-1)
    printf("invlaid expression");
    else
    printf("valid %f",result);
}

int main() {
    int choice;
    char infix[30], prefix[30];
    printf("\n1. Enter infix expression\n2. Infix to prefix\n3. Evaluate prefix\n4. Exit");
    for (;;) {
        printf("\nEnter the choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("Enter the infix expression: ");
                scanf("%s", infix);
                break;
            case 2:
                inprefix(infix, prefix);
                printf("%s\n", prefix);
                break;
            case 3:
                evalprefix(prefix);
                break;
            case 4:
                printf("Thank you\n");
                exit(0);
                break;
            default:
                printf("Invalid choice\n");
        }
    }
}
