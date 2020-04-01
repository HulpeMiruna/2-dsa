#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int MAXVALUE=90000;
const int MAXNAME=200;
typedef struct node
{
    char *name;
    int Deleted;
} Node;

Node *Table[90000];


void initial()
{
    for(int i=0; i<MAXVALUE; i++)
        Table[i]=NULL;
}
int findFirstHashValue(char *name)
{
    int sum=0;
    for(int i=0; i<strlen(name); i++)
    {
        int x=name[i];
        sum=sum+x;
    }
    return sum/strlen(name);
}
int findSecondHashValue(char *name,int index)
{
    return ((findFirstHashValue(name)+index*index)%strlen(name));
}
void insert(char *c)
{
    int h,OK=1,index=1;
    Node *p=(Node *) malloc (sizeof(Node));
    p->name=(char *) malloc(sizeof(char)*MAXNAME);
    h=findFirstHashValue(c);
    strcpy(p->name,c);
    p->Deleted=0;
    if(Table[h]==NULL)
    {
        Table[h]=p;

    }
    else
    {
        while(Table[h]!=NULL&&OK==1)
        {
            if(strcmp(Table[h]->name,c)==0)
                OK=0;
            h=findSecondHashValue(c,index);
            index++;

        }
        if(OK==1)
            Table[h]=p;

    }
}
void print(FILE *g)
{
    int i;
    for(i=0; i<MAXVALUE; i++)
    {
        if(Table[i]!=NULL)
            fprintf(g,"%s \n",Table[i]->name);
    }

}
int findElement (char *c)
{
    int h,index=1;
    h=findFirstHashValue(c);

    while(Table[h]!=NULL||Table[h]!=0)
    {
        if(strcmp(Table[h]->name,c)==0)
            return h;
        h=findSecondHashValue(c,index);
        index++;

    }
    return -1;

}
void find(char *c,FILE *g)
{
    int i;
    i= findElement(c);
    if(i!=-1)
        fprintf(g,"yes %d \n",i);
    else
        fprintf(g,"no \n");
}
void deletee(char *c)
{
    int h;
    h=findElement (c);
    if(h!=-1)
    {
        Table[h]=NULL;
        Table[h]->Deleted=1;
    }
}
void readInstructions(FILE *f,FILE *g)
{
    initial();
    char *strbuf= (char *) malloc (sizeof (char)*MAXNAME);
    while(fscanf(f,"%s\n",strbuf)!=EOF)
    {
        if(strbuf[0]=='i')
        {
            strcpy(strbuf,strbuf+1);
            insert(strbuf);

        }
        else if(strbuf[0]=='d')
        {
            strcpy(strbuf,strbuf+1);
            deletee(strbuf);

        }
        else if(strbuf[0]=='f')
        {
            strcpy(strbuf,strbuf+1);
            find(strbuf,g);

        }
        else if(strbuf[0]=='l')
        {
            print(g);
        }
    }
}
int main()
{
    FILE *f =fopen("input.txt","r+");
    FILE *g =fopen("output.txt","r+");
    readInstructions(f,g);
    return 0;
}

