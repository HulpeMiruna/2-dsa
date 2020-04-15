#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct
{
    int value;
    int weight;
    int used;
} Object;

Object   GreedyMaxValue (int NrOfObjects, Object *Objects, Object knapsack)
{
    // Acesta este primul algoritm greedy pe care il utilizez
    //Incerc sa adaug obiectele cu valoarea cea mai mare, indiferent de cat spatiu ocupa, dar in limita maxima
    int i,j;
    for(i=0; i<NrOfObjects-1; i++)
        for(j=i; j<NrOfObjects; j++)
        {
            if(Objects[i].value<Objects[j].value)
            {
                Object Aux;
                Aux=Objects[i];
                Objects[i]=Objects[j];
                Objects[j]=Aux;
            }
            if(Objects[i].value==Objects[j].value)
            {
                if(Objects[i].weight>Objects[j].weight)
                {
                    Object Aux;
                    Aux=Objects[i];
                    Objects[i]=Objects[j];
                    Objects[j]=Aux;
                }
            }
        }
    for(i=0; i<NrOfObjects; i++)
    {
        printf("%d %d\n",Objects[i].value,Objects[i].weight);
    }
    Object BestValue;
    BestValue.value=0;
    BestValue.weight=0;
    for(i=0; i<NrOfObjects; i++)
    {
        if(BestValue.weight+Objects[i].weight<=knapsack.weight)
        {
            BestValue.weight=BestValue.weight+Objects[i].weight;
            BestValue.value=BestValue.value+Objects[i].value;
            Objects[i].used=1;
        }
    }
    i=0;
    if(BestValue.weight!=knapsack.weight)
    {
        while(Objects[i].used==1)
        {
            i++;
        }
        knapsack.weight=knapsack.weight-BestValue.weight;//remaining free space
        Objects[i].value=Objects[i].value/Objects[i].weight;//price of one part
        Objects[i].value=Objects[i].value*knapsack.weight;

        BestValue.value=BestValue.value+Objects[i].value;
    }

    printf("\n");
    return BestValue;


}

Object GreedyMaxQuantitie (int NrOfObjects, Object *Objects, Object knapsack)
{
    // Acesta este al doilea algoritm greedy pe care il utilizez
    //Incerc sa adaug obiectele cu cantitatea minima, indiferent de valoare, deoarece multe obiecte mai nevaloroase pot fi mai valoroase impreuna decat unul mai putine
    int i,j;

    for(i=0; i<NrOfObjects-1; i++)
        for(j=i; j<NrOfObjects; j++)
        {
            if(Objects[i].weight>Objects[j].weight)
            {
                Object Aux;
                Aux=Objects[i];
                Objects[i]=Objects[j];
                Objects[j]=Aux;
            }
            if(Objects[i].weight==Objects[j].weight)
            {
                if(Objects[i].value<Objects[j].value)
                {
                    Object Aux;
                    Aux=Objects[i];
                    Objects[i]=Objects[j];
                    Objects[j]=Aux;
                }
            }
        }
    for(i=0; i<NrOfObjects; i++)
    {
        printf("%d %d\n",Objects[i].value,Objects[i].weight);

    }
    Object BestValue;
    BestValue.value=0;
    BestValue.weight=0;
    for(i=0; i<NrOfObjects; i++)
    {
        if(BestValue.weight+Objects[i].weight<=knapsack.weight)
        {
            BestValue.weight=BestValue.weight+Objects[i].weight;
            BestValue.value=BestValue.value+Objects[i].value;
            Objects[i].used=1;
        }
    }
    if(BestValue.weight < knapsack.weight)
    {
        for(i=0; i<NrOfObjects-1; i++)
            for(j=i; j<NrOfObjects; j++)
            {
                if(Objects[i].value<Objects[j].value)
                {
                    Object Aux;
                    Aux=Objects[i];
                    Objects[i]=Objects[j];
                    Objects[j]=Aux;
                }
                if(Objects[i].value==Objects[j].value)
                {
                    if(Objects[i].weight>Objects[j].weight)
                    {
                        Object Aux;
                        Aux=Objects[i];
                        Objects[i]=Objects[j];
                        Objects[j]=Aux;
                    }
                }
            }
        while(Objects[i].used==1)
        {
            i++;
        }
        knapsack.weight=knapsack.weight-BestValue.weight;//remaining free space
        Objects[i].value=Objects[i].value/Objects[i].weight;//price of one part
        Objects[i].value=Objects[i].value*knapsack.weight;

        BestValue.value=BestValue.value+Objects[i].value;

    }

    return BestValue;

}

void BestValue(FILE *f,FILE *g)
{
    int NrOfObj;
    fscanf(f,"%d\n",&NrOfObj);
    Object knapsack;
    Object *Objects=(Object*) malloc (sizeof(Object)*NrOfObj);
    fscanf(f,"%d %d\n",&knapsack.value,&knapsack.weight);
    for(int i=0; i<NrOfObj; i++)
    {
        fscanf(f,"%d %d\n",&Objects[i].value,&Objects[i].weight);
        Objects[i].used=0;
    }
    Object MaxValue=GreedyMaxValue (NrOfObj,Objects,knapsack);
    Object MaxQuantitie=GreedyMaxQuantitie (NrOfObj,Objects,knapsack);
    if(MaxValue.value>MaxQuantitie.value)
        fprintf(g,"%d ",MaxValue.value);
    else
        fprintf(g,"%d ",MaxQuantitie.value);
}

int main()
{
    FILE *f=fopen("input.txt","r+");
    FILE *g=fopen("output.txt","r+");
    BestValue(f,g);
    return 0;
}
