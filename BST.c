#include <stdio.h>
#include <stdlib.h>

struct node {
    int info;
    struct node *llink;
    struct node *rlink;
};

typedef struct node *NODE;

NODE construct(NODE);
void display(NODE);
NODE search(NODE, int, NODE*);
void inorder(NODE);
void preorder(NODE);
void postorder(NODE);
NODE delete(NODE);
int countleaf(NODE);
int countnonleaf(NODE);
int height(NODE);
void minele(NODE);
void maxele(NODE);
int more(int, int);

void main() {
    int ch, key;
    NODE Root = NULL, NS = NULL, PN = NULL;
     printf("\n1.Construct\n2.Display\n3.Search\n4.Delete\n5.count leaf\n6.count nonleaf\n7.height\n8.min and its parent\n9.max and its parent\n10.exit\n");
    for (;;) {
        printf("enter the choice");
        scanf("%d", &ch);
        switch (ch) {
            case 1: Root = construct(Root); break;
            case 2: display(Root); break;
            case 3:
                printf("Enter the key of the node to be searched\n");
                scanf("%d", &key);
                if (Root->info == key) {
                    printf("Searching info = %d and it does not have any parent root\n", Root->info);
                } else {
                    NS = search(Root, key, &PN);
                    if (NS == NULL)
                        printf("Node doesn't exist\n");
                    else
                        printf("Searching node info = %d and its parent node is %d\n", NS->info, PN->info);
                }
                break;
            case 4: Root = delete(Root); 
                    display(Root); 
                    break;
            case 5: printf("Total number of leaves is %d\n",countleaf(Root)); 
                    break;
            case 6: printf("Number of non-leaves is %d\n", countnonleaf(Root)); 
                    break;
            case 7: printf("Height of the tree is %d\n", height(Root)); 
                    break;
            case 8: minele(Root); 
                    break;
            case 9: maxele(Root); 
                    break;
            case 10:exit(0);
                    break;
            default: printf("invalid choice");
        }
    }
}

NODE construct(NODE R) {
    NODE NN, TP, PN;
    int ch;
    for (;;) {
        printf("Enter 1 to keep inserting node otherwise press -1\n");
        scanf("%d", &ch);
        if (ch != -1) {
            NN = (NODE)malloc(sizeof(struct node));
            printf("Enter the data\n");
            scanf("%d", &NN->info);
            NN->llink = NN->rlink = NULL;
            if (R == NULL) return NN;
            TP = R;
            PN = NULL;

            while (TP != NULL) {
                PN = TP;
                if (NN->info < TP->info)
                    TP = TP->llink;
                else
                    TP = TP->rlink;
            }
            if (NN->info < PN->info)
                PN->llink = NN;
            else
                PN->rlink = NN;
        } else break;
    }
    return R;
}

void display(NODE R) {
    if (R == NULL) {
        printf("Tree empty\n");
        return;
    }
    printf("\nInorder traversal is: ");
    inorder(R);
    printf("\nPreorder traversal is: ");
    preorder(R);
    printf("\nPostorder traversal is: ");
    postorder(R);
    printf("\n");
}

void inorder(NODE R) {
    if (R == NULL) return;
    inorder(R->llink);
    printf("%d ", R->info);
    inorder(R->rlink);
}

void preorder(NODE R) {
    if (R == NULL) return;
    printf("%d ", R->info);
    preorder(R->llink);
    preorder(R->rlink);
}

void postorder(NODE R) {
    if (R == NULL) return;
    postorder(R->llink);
    postorder(R->rlink);
    printf("%d ", R->info);
}

NODE search(NODE R, int key, NODE *PN) {
    NODE NS = NULL;
    if (R == NULL) return NULL;
    if (R->info == key) {
        NS = R;
    }
    if (NS == NULL) {
        *PN = R;
        if (key < R->info)
            NS = search(R->llink, key, PN);
        else
            NS = search(R->rlink, key, PN);
    }
    return NS;
}

NODE delete(NODE R) {
    int key;
    NODE ND = NULL, PN = NULL, IS, ISP; // IS = inorder successor, ISP = inorder successor parent
    NODE TP;
    if (R == NULL) {
        printf("Tree is empty\n");
        return NULL;
    }
    printf("Enter the key to be deleted\n");
    scanf("%d", &key);
    if (R->info == key && R->llink == NULL && R->rlink == NULL) {
        printf("Deleted = %d\n", R->info);
        free(R);
        return NULL;
    }
    ND = search(R, key, &PN);
    if (ND == NULL) {
        printf("Node doesn't exist\n");
        return R;
    }
    printf("Node to be deleted is %d and its parent root is %d\n", ND->info, PN->info);

    if (ND->llink == NULL && ND->rlink == NULL) {
        if (ND == PN->llink)
            PN->llink = NULL;
        else
            PN->rlink = NULL;
        printf("Deleted = %d\n", ND->info);
        free(ND);
        return R;
    } else if (ND->llink != NULL && ND->rlink == NULL || ND->llink == NULL && ND->rlink != NULL) {
        if (ND->rlink == NULL)
            TP = ND->llink;
        else
            TP = ND->rlink;
        if (ND == PN->rlink)
            PN->rlink = TP;
        else
            PN->llink = TP;
        printf("Deleted = %d\n", ND->info);
        free(ND);
        return R;
    } else {
        IS = ND->rlink;
        ISP = ND;
        while (IS->llink != NULL) {
            ISP = IS;
            IS = IS->llink;
        }
        printf("Deleted element is %d\n", ND->info);
        ND->info = IS->info;
        if (IS->llink == NULL && IS->rlink == NULL) {
            if (IS == ISP->llink)
                ISP->llink = NULL;
            else
                ISP->rlink = NULL;
        } else {
            if (IS == ISP->llink)
                ISP->llink = IS->rlink;
            else
                ISP->rlink = IS->rlink;
        }
        free(IS);
        return R;
    }
}

int countleaf(NODE R) {
    if (R == NULL) return 0;
    if (R->llink == NULL && R->rlink == NULL)
        return 1;
    return countleaf(R->llink) + countleaf(R->rlink);
}

int countnonleaf(NODE R) {
    if (R == NULL || (R->llink == NULL && R->rlink == NULL)) return 0;
    return 1 + countnonleaf(R->llink) + countnonleaf(R->rlink);
}

int height(NODE R) {
    if (R == NULL) return -1;
    return 1 + more(height(R->llink), height(R->rlink));
}

int more(int x, int y) {
    return (x > y) ? x : y;
}

void minele(NODE R) {
    NODE TP, PN;
    TP = R;
    PN = NULL;
    while (TP->llink != NULL) {
        PN = TP;
        TP = TP->llink;
    }
    if(PN == NULL){
        printf("Minimum is %d and it has no parent root\n",TP->info);
    }
    else
        printf("Minimum is %d and its parent root is %d\n", TP->info, PN->info);
}

void maxele(NODE R) {
    NODE TP, PN;
    TP = R;
    PN = NULL;
    while (TP->rlink != NULL) {
        PN = TP;
        TP = TP->rlink;
    }
    if(PN == NULL){
        printf("Maximum is %d and it has no parent root \n",TP->info);
    }
    else
        printf("Maximum is %d and its parent root is %d\n", TP->info, PN->info);
}

/*
void EnQ(QUE *pq, NODE item)
{
  // check for Full 
  pq->items[++pq->r]=item;
}

 NODE DQ(QUE *pq)
{   NODE item;
  // check for empty
   
  item=pq->items[pq->f];
  pq->f++;
   return item;
} 
void BFS(NODE R)
  {
     QUE Q;
       NODE TN;
       Q.f=0; Q.r=-1;

    if(R==NULL)
     {
        printf("\ntree is empty\n"); return;
     }
    printf("\nBFS Traversal:\n");   
  EnQ(&Q,R);
  while(Q.f<=Q.r)
   {
     TN=DQ(&Q);
     printf("%d   ",TN->data);
     if(TN->LL!=NULL)
      EnQ(&Q,TN->LL);
     if(TN->RL!=NULL)
      EnQ(&Q,TN->RL); 
   }
}
*/
