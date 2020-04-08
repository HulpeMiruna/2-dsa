#include <stdio.h>
#include <stdlib.h>
# include <string.h>
const int MAXNROFNODES=200;
const int MAXLINELENGHT=500;

typedef struct node
{
    int data;
    struct node * next;

} ListNode;

ListNode *first, *last;

void initial()
{
    first=NULL;
    last=NULL;
}
void AL (int x)
{
    if(first==NULL)
    {
        first=(ListNode *) malloc (sizeof(ListNode));
        first->data=x;
        first->next=last;
        last=first;
    }
    else
    {
        ListNode *NewElement= (ListNode *) malloc (sizeof (ListNode));
        NewElement->data=x;
        last->next=NewElement;
        NewElement->next=NULL;
        last=NewElement;
    }
}

void PRINT_ALL(FILE *g)
{
    if (first==NULL)
        printf("The list is empty");
    else
    {
        ListNode *CurrentElement;
        CurrentElement=first;
        while(CurrentElement != NULL)
        {
            fprintf(g,"%d ",CurrentElement->data);
            CurrentElement=CurrentElement->next;
        }
    }
    fprintf(g,"\n");
}
int *NodesGraph(FILE *f,int *n)
{
    int *Nodes =(int *) malloc (sizeof (int )*MAXNROFNODES);
    char *strbuf=(char *) malloc (sizeof (char)*MAXLINELENGHT);
    fscanf(f,"%s ",strbuf);
    char *p;
    p=strtok(strbuf,"_\n");
    p=strtok(NULL,"_\n");
    p=strtok(NULL,"_\n");
    while(p!=NULL)
    {
        Nodes[*n]=atoi(p);
        *n=*n+1;
        p=strtok(NULL,"_\n");

    }
    return Nodes;
}
int **FormMatrix(FILE *f,int *Nodes,int n)
{
    int i=0,j,x,y;

    int **AdiacenceMatrix= (int **) malloc (sizeof (int *)*MAXNROFNODES);
    for(i=0; i<MAXNROFNODES; i++)
        AdiacenceMatrix[i]=(int *) malloc (sizeof (int )*MAXNROFNODES);
    char *strbuf=(char *) malloc (sizeof (char)*MAXLINELENGHT);
    for(i=0; i<n; i++)
        for(j=0; j<n; j++)
            AdiacenceMatrix[i][j]=0;
    fscanf(f,"%s ",strbuf);
    char *p;
    p=strtok(strbuf,"_\n");
    p=strtok(NULL,"_\n");
    p=strtok(NULL,"(_\n");
    while(p!=NULL)
    {
        x=atoi(p);
        p=strtok(NULL,"()_\n");
        y=atoi(p);

        int k=0;
        while(k<x||k<y)
        {
            if(Nodes[k]==x)
                j=k;
            if(Nodes[k]==y)
                i=k;
            k++;
        }

        p=strtok(NULL,"()_\n");
        AdiacenceMatrix[i][j]++;
        AdiacenceMatrix[j][i]++;
    }

    return AdiacenceMatrix;
}



void BFS (FILE *f,FILE *g)
{
    int n=0,i,j;
    int *Nodes=NodesGraph(f, &n);
    int **AdjMatrix=FormMatrix(f,Nodes,n);
    int *visited=(int *) malloc (sizeof (int )*MAXNROFNODES);
    for(i=0; i<n; i++)
        visited[i]=0;
    initial();
    AL(Nodes[0]);
    ListNode *Element=first;
    visited[0]=1;
    int NrOfVisitedNodes=1;
    i=0;

    while(NrOfVisitedNodes<n)
    {
        for(j=0; j<n; j++)
        {
            if(AdjMatrix[i][j]!=0)
                if(visited[j]==0)
                {
                    AL(Nodes[j]);
                    visited[j]=1;
                    NrOfVisitedNodes++;
                }
        }
        Element=Element->next;
        i=0;
        while(Nodes[i]<Element->data)
        {
            i++;
        }

    }
    PRINT_ALL(g);

}

int main()
{
    FILE *f=fopen("input.txt","r+");
    FILE *g=fopen("output.txt","r+");
    BFS (f,g);
    return 0;
}
