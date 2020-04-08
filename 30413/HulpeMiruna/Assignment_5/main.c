#include <stdio.h>
#include <stdlib.h>
//DFS and BFS on adiacence matrix are verified on ex 7.2

typedef struct node
{
    int frate;
    struct node *next;
} Node;

Node *first[90000];

void initial(int n)
{
    for(int i=0; i<n; i++)
        first[i]=NULL;
}

int ** ReadInstructions(FILE *f,int NrOfNodes)
{
    int i,j;
    int **AdjMatrix=(int **) malloc(sizeof (int *) *NrOfNodes);
    for(i=0;i<=NrOfNodes;i++)
    {
        AdjMatrix[i]=(int *) malloc(sizeof (int ) *NrOfNodes);
    }
    for(i=1;i<=NrOfNodes;i++)
    {
        for(j=1;j<=NrOfNodes;j++)
        {
            fscanf(f,"%d ",&AdjMatrix[i][j]);
        }
        fscanf(f,"\n");
    }

return AdjMatrix;
}

void AddListValue (int Location,int Value)
{
    Node*p=(Node *) malloc(sizeof(Node));
    p->frate=Value;
    p->next=NULL;
    if(first[Location]==NULL)
    {
        first[Location]=p;
    }
    else
    {
        Node *Element;
        Element=first[Location];
        while(Element->next!=NULL&&Element->frate!=Value)
        {
            Element=Element->next;
        }
        if(Element->next==NULL&&Element->frate!=Value) Element->next=p;
    }
}

void FromMAtrixToList (FILE *f,FILE *g,int n)
{   initial(n);
    int i,j;
    int **AdjMatrix=ReadInstructions(f,5);
    for(i=1;i<=n;i++)
    {
        for(j=1;j<=n;j++)
            if(AdjMatrix[i][j]!=0) AddListValue(i,j);
    }
    for(i=1;i<=n;i++)
    {
        fprintf(g,"Muchiile incepand cu %d se termina cu :",i);
        Node *Element=first[i];
        while(Element!=NULL)
        {
            fprintf(g,"%d, ",Element->frate);
            Element=Element->next;
        }
        fprintf(g,"\n");
    }
}

void FromListToMAtrix(FILE *g,int n)
{   int i,j;
    int **AdjMatrix=(int **) malloc(sizeof (int *) *n);
    for(i=0;i<=n;i++)
    {
        AdjMatrix[i]=(int *) malloc(sizeof (int ) *n);
    }
    for(i=1;i<=n;i++)
        for(j=1;j<=n;j++)
        AdjMatrix[i][j]=0;
    for(i=1;i<=n;i++)
    {
        Node *Element=first[i];
        while(Element!=NULL)
        {
            j=Element->frate;
            AdjMatrix[i][Element->frate]=AdjMatrix[i][j]+1;
            Element=Element->next;
        }
    }
    for(i=1;i<=n;i++)
       { for(j=1;j<=n;j++)
          fprintf(g,"%d ",AdjMatrix[i][j]);
          fprintf(g,"\n");
       }

}



void SolveProblem(FILE *f,FILE *g)
{   int n;
    scanf("%d",&n);
    FromMAtrixToList (f,g,n);
    FromListToMAtrix(g,n);
}
int main()
{
    FILE *f=fopen("input.txt","r+");
    FILE *g=fopen("output.txt","r+");
    FromMAtrixToList (f,g,5);
    FromListToMAtrix(g,5);
    return 0;
}
