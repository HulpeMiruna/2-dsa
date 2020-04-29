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
void Merge(int *Values, int start, int middle, int end)
{
    int i,j;
    int LenghtLeft=middle-start+1;
    int LenghtRight=end-middle;
    int *Left=(int *) malloc (sizeof(int)*LenghtLeft);
    int *Right=(int *) malloc (sizeof(int)*LenghtRight);
    int k=start;
    for(i=0; i<LenghtLeft; i++)
    {
        Left[i]=Values[k];
        k++;
    }
    for(i=0; i<LenghtRight; i++)
    {
        Right[i]=Values[k];
        k++;
    }
    k=start;
    i=0;
    j=0;
    while(i<LenghtLeft&&j<LenghtRight)
    {
        if(Left[i]<Right[j])
        {
            Values[k]=Left[i];
            i++;
        }
        else
        {
            Values[k]=Right[j];
            j++;
        }
        k++;
    }
    while(i<LenghtLeft)
    {
        Values[k]=Left[i];
        i++;
        k++;
    }
    while(j<LenghtRight)
    {
        Values[k]=Right[j];
        j++;
        k++;
    }

}

void MergeSort(int *Values,int start,int end)
{
    int Middle=(start+end)/2;
    if(start<end)
    {
        MergeSort(Values,start,Middle);
        MergeSort(Values,Middle+1,end);
        Merge (Values,start,Middle,end);
    }


}

void Sort (FILE *f, FILE *g)
{
    int n,i;
    fscanf(f,"%d\n",&n);
    int *Values= ReadInstructions(f,n);
    MergeSort(Values,0,n);

    for(i=0; i<n; i++)
        fprintf (g,"%d ",Values[i]);

}

int main()
{
    FILE *f=fopen("input.txt","r+");
    FILE *g=fopen("output.txt","r+");
    Sort (f,g);
    return 0;
}
