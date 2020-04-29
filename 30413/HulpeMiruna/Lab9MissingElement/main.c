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

int FindMissing(int *Values,int difference,int n)
{
    int start=0;
    int finish=n;
    while(start<=finish)
    {
        int mij=(start+finish)/2;
        if(Values[mij+1]-Values[mij]!=Values[mij]-Values[mij-1])
        {
            if(mij + 1 < n&&Values[mij+1]-Values[mij]!=difference)
            {
                return Values[mij]+difference;
            }

            else if(mij-1>=0&&Values[mij]-Values[mij-1])
            {
                return Values[mij-1]+difference;
            }
        }
        if(Values[mij] - Values[0] != (mij - 0) * difference)
            finish=mij-1;
        else
            start=mij+1;

    }
}
void Find(FILE *f,FILE *g)
{
    int n,difference;
    fscanf(f,"%d\n",&n);
    int *Values= ReadInstructions(f,n);
    difference=Values[1]-Values[0];
    int TwoThree=Values[2]-Values[1];
    if(difference!=TwoThree)
    {
        int ThreeFour=Values[3]-Values[2];
        if(difference!=ThreeFour)
            fprintf(g,"The missing value is %d",Values[0]+ThreeFour);
        else
            fprintf(g,"The missing value is %d",Values[1]+ThreeFour);
    }
    else
    {
        int Missing= FindMissing(Values,difference,n);
        fprintf(g,"The missing value is %d",Missing);
    }
}

int main()
{
    FILE *f=fopen("input.txt","r+");
    FILE *g=fopen("output.txt","r+");
    Find (f,g);
    return 0;
}
