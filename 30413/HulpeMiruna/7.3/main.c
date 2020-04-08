#include <stdio.h>
#include <stdlib.h>
// Algoritmul meu afiseaza distanta minima dintre i si celelalte noduri
// Nu am inteles la ce s-a referit prin minimum cost
const int MAXLINELENGHT=200;
const int MAXNROFARCS=100;
int ** FormMatrix(FILE *f,int *n)
{
    int i,j,lenght;
    int **AdjMatrix=(int **) malloc (sizeof(int*)*MAXLINELENGHT);
    for(i=0; i<MAXLINELENGHT; i++)
        AdjMatrix[i]=(int *) malloc (sizeof(int)*MAXLINELENGHT);
    for(i=0; i<MAXLINELENGHT; i++)
        for(j=0; j<MAXLINELENGHT; j++)
            AdjMatrix[i][j]=0;
    while (fscanf(f,"%d %d=%d\n",&i,&j,&lenght)!=EOF)
    {
        AdjMatrix[i][j]=lenght;
        if(i>*n)
            *n=i;
        if(j>*n)
            *n=j;
    }
    return AdjMatrix;
}

void Djikstra (FILE *f,FILE *g)
{
    int n=0,LenghtPath=2,i,j;
    int **AdjMatrix=FormMatrix(f,&n);
    int *Visited= (int *) malloc (sizeof (int)*n);
    int *Path = (int *) malloc (sizeof (int)*n);
    int *Distances = (int *) malloc (sizeof (int)*n);
    for(i=1; i<=n; i++)
    {
        Visited[i]=0;
        Distances[i]=-1;
    }
    int StartingPoint;
    scanf("%d",&StartingPoint);
    Visited[StartingPoint]=1;
    Distances[StartingPoint]=0;
    Path[StartingPoint]=StartingPoint;
    i=StartingPoint;
    while(LenghtPath<=n)
    {
        for(j=1; j<=n; j++)
        {
            if(AdjMatrix[i][j]!=0)
            {
                if(Distances[j]==-1)
                {
                    Distances[j]=Distances[i]+AdjMatrix[i][j];
                }
                else
                {
                    int NewValue=Distances[i]+AdjMatrix[i][j];
                    if(Distances[j]>NewValue)
                    {
                        Distances[j]=NewValue;
                    }
                }

            }
        }

        int min=-1;
        for(j=1; j<=n; j++)
        {
            if(Distances[j]!=-1)
            {
                if(Visited[j]==0)
                {
                    if(min==-1||Distances[j]<min)
                    {
                        i=j;
                        min=Distances[j];
                    }

                }
            }
        }
        Path[LenghtPath]=i;
        Visited[i]=1;
        LenghtPath++;
    }
    int OK=1;
    for(i=1; i<=n&&OK==1; i++)
    {
        if(Distances[i]==-1)
            OK=0;
    }
    if(OK==0)
    {
        fprintf(g,"The graph doesn't support Dijkstra with starting point %d",StartingPoint);
    }
    else
    {
        for(i=1; i<n; i++)
            fprintf(g,"%d-",Path[i]);
        fprintf(g,"%d\n",Path[i]);

        for(i=1; i<=n; i++)
        {
            fprintf(g,"the minimum distance between %d and %d is %d\n",StartingPoint,i,Distances[i]);
        }
    }


}

int main()
{
    FILE *f=fopen("input.txt","r+");
    FILE *g=fopen("output.txt","r+");
    Djikstra(f,g);
    return 0;
}
