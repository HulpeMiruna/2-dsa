#include <stdio.h>
#include <stdlib.h>
typedef struct
{
    int startTime;
    int finishTime;
    int activityNr;
} Activity;

Activity * readInstructions(FILE *f,int NrOfActivities)
{
    int i;
    Activity *Activities=(Activity *) malloc (sizeof (Activity)*NrOfActivities);
    for(i=0; i<NrOfActivities; i++)
    {
        fscanf(f,"%d %d\n",&Activities[i].startTime,&Activities[i].finishTime);
        Activities[i].activityNr=i;

    }
    return Activities;
}
void BestPlanning (FILE *f,FILE *g)
{
    int NrOfActivities,i,j;
    fscanf(f,"%d\n",&NrOfActivities);
    Activity *Activities=readInstructions(f,NrOfActivities);
    for(i=0; i<NrOfActivities-1; i++)
        for(j=1; j<NrOfActivities; j++)
        {
            if(Activities[i].finishTime>Activities[j].finishTime)
            {
                Activity Aux;
                Aux=Activities[i];
                Activities[i]=Activities[j];
                Activities[j]=Aux;
            }

        }
    int CurrentTime=0;
    for(i=0; i<NrOfActivities; i++)
    {
        if(Activities[i].startTime>=CurrentTime)
        {
            CurrentTime=Activities[i].finishTime;
            fprintf(g,"%d ",Activities[i].activityNr+1);

        }
    }

}
int main()
{
    FILE *f=fopen("input.txt","r+");
    FILE *g=fopen("output.txt","r+");
    BestPlanning (f,g);
    return 0;
}
