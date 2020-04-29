#include <stdio.h>
#include <stdlib.h>

int *ReadInstructions (FILE *f,int n)
{
    int i;
    int *Values= (int *) malloc (sizeof(int )*n);
    for(i=0; i<n; i++)
        fscanf(f,"%d ",&Values[i]);
    return Values;
}

int Mini(int *Values,int start,int end,int NeededValue)
{
    int mij=(start+end)/2;
    if(start<end)
    {
        if(NeededValue<Values[mij])
            return Mini(Values,start,mij-1,NeededValue);
        else if(NeededValue<Values[mij])
        {
            return Mini(Values,mij+1,end,NeededValue);
        }
        else
        {
            return 1+Mini(Values,start,mij-1,NeededValue)+Mini(Values,mij+1,end,NeededValue);
        }
    }
    return 0;
}
void Find (FILE *f,FILE *g)
{
    int n, NeededValue;
    fscanf(f,"%d\n",&n);
    int *Values= ReadInstructions(f,n);
    fscanf(f,"%d",&NeededValue);
    int mini=Mini(Values,0,n,NeededValue);
    fprintf(g,"%d",mini);

}

int main()
{
    FILE *f=fopen("input.txt","r+");
    FILE *g=fopen("output.txt","r+");
    Find (f,g);
    return 0;
}
