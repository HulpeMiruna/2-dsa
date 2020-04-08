#include <stdio.h>
#include <stdlib.h>
#include <string.h>
const int MAXNROFNODES=200;
const int MAXLINELENGHT=500;

void ReadInstruction(FILE *f,FILE *g)
{
    int i=0,j,n=0,x,y,m=0;
    int *Nodes =(int *) malloc (sizeof (int )*MAXNROFNODES);
    int *SubgraphNodes =(int *) malloc (sizeof (int )*MAXNROFNODES);
    int **AdiacenceMatrix= (int **) malloc (sizeof (int *)*MAXNROFNODES);
    for(i=0; i<MAXNROFNODES; i++)
        AdiacenceMatrix[i]=(int *) malloc (sizeof (int )*MAXNROFNODES);
    char *strbuf=(char *) malloc (sizeof (char)*MAXLINELENGHT);
    fscanf(f,"%s ",strbuf);
    char *p;
    p=strtok(strbuf,"_\n");
    p=strtok(NULL,"_\n");
    p=strtok(NULL,"_\n");
    while(p!=NULL)
    {
        Nodes[n]=atoi(p);
        n++;
        p=strtok(NULL,"_\n");

    }
    for(i=0; i<n; i++)
        for(j=0; j<n; j++)
            AdiacenceMatrix[i][j]=0;
    fscanf(f,"%s ",strbuf);
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
    fscanf(f,"%s ",strbuf);
    p=strtok(strbuf,"_\n");
    p=strtok(NULL,"_\n");
    p=strtok(NULL,"_\n");
    while(p!=NULL)
    {
        SubgraphNodes[m]=atoi(p);
        m++;
        p=strtok(NULL,"_\n");

    }
    fprintf(g,"V'_arcs");
    for(int k=0; k<m; k++)
        for(int l=k; l<m; l++)
        {
            x=0;
            while(x<SubgraphNodes[k]||x<SubgraphNodes[l])
            {
                if(Nodes[x]==SubgraphNodes[k])
                    j=x;
                if(Nodes[x]==SubgraphNodes[l])
                    i=x;
                x++;
            }
            if(AdiacenceMatrix[i][j]!=0)
                fprintf(g,"_(%d_%d)",SubgraphNodes[k],SubgraphNodes[l]);
        }

}

int main()
{
    FILE * f=fopen ("input.txt","r+");
    FILE * g=fopen ("output.txt","r+");
    ReadInstruction(f,g);
    return 0;
}
