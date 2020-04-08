#include <stdio.h>
#include <stdlib.h>
# include <string.h>
const int MAXNROFNODES=200;
const int MAXLINELENGHT=500;

typedef struct node
{
    int data;
    struct node * next;
    struct node *previous;

} ListNode;
typedef struct
{
    ListNode *first, *last;
} Sentinel;

Sentinel T;
void initial()
{
    T.first=NULL;
    T.last=NULL;
}

void PRINT_ALL(FILE *g)
{
    if (T.first==NULL)
        fprintf(g,"The list is empty \n");
    else
    {
        ListNode *CurrentElement;
        CurrentElement=T.last;
        while(CurrentElement != NULL)
        {
            fprintf(g,"%d ",CurrentElement->data);
            CurrentElement=CurrentElement->previous;
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

void AF (int x)
{
    ListNode *Element= (ListNode *) malloc (sizeof (ListNode));
    Element->data=x;
    Element->next=T.first;
    Element->previous=NULL;
    if (T.first == NULL)
    {
        T.first = Element;
        T.last=T.first;
    }
    else
    {
        T.first->previous=Element;
        T.first= Element;
    }
}
void DFS (FILE *f,FILE *g)
{
    int n=0,i,j;
    int *Nodes=NodesGraph(f, &n);
    int **AdjMatrix=FormMatrix(f,Nodes,n);
    int *visited=(int *) malloc (sizeof (int )*MAXNROFNODES);
    for(i=0; i<n; i++)
        visited[i]=0;
    initial();
    AF(Nodes[0]);
    ListNode *Element=T.first;
    visited[0]=1;
    int NrOfVisitedNodes=1;
    i=0;

    while(NrOfVisitedNodes<n)
    {
        j=0;
        int OK=0;
        while(j<n&&OK==0)
        {
            if(AdjMatrix[i][j]!=0)
            {
                if(visited[j]==0)
                {
                    NrOfVisitedNodes++;
                    visited[j]=1;
                    OK=1;
                    AF(Nodes[j]);
                }
            }
            j++;
        }
        if(j==n&&OK==0)
        {
            Element=Element->next;
        }
        else
            Element=T.first;
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
    DFS (f,g);
    return 0;
}


