#include <stdio.h>
#include <stdlib.h>
#include <string.h>
const int MAXVALUE=90000;
const int MAXNAME=200;
typedef struct node
{
    char *name;
    struct node *next;
} Node;

Node *first[90000];

void initial()
{
    for(int i=0; i<MAXVALUE; i++)
        first[i]=NULL;
}

int findHashValue(char *name)
{
    int sum=0;
    for(int i=0; i<strlen(name); i++)
    {
        int x=name[i];
        sum=sum+x;
    }
    return sum/strlen(name);
}

void insert (char *c)
{
    int h;
    Node *p=(Node *) malloc (sizeof(Node));
    p->name=(char *) malloc(sizeof(char)*MAXNAME);
    h=findHashValue(c);
    strcpy(p->name,c);
    p->next=NULL;
    if(first[h]==NULL)
    {
        first[h]=p;

    }
    else
    {
        Node *Element= first[h];
        while(Element->next!=NULL && strcmp(Element->name,c)!=0)
            Element=Element->next;
        if(Element->next==NULL && strcmp(Element->name,c)!=0)
            Element->next=p;

    }
}
void print (FILE *g)
{
    int i;
    for(i=0; i<MAXVALUE; i++)
    {
        if(first[i]!=NULL)
        {
            Node *Element= first[i];
            while(Element!=NULL)
            {
                fprintf(g,"%s ",Element->name);
                Element=Element->next;

            }
            fprintf(g,"\n");
        }
    }
}
int findElement (char *c)
{
    int h;
    h=findHashValue(c);
    Node *Element = first[h];
    while(Element !=NULL)
    {
        if(strcmp(Element->name,c)==0)
            return h;
        Element=Element->next;
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
    int h,OK =1;
    Node *Element;
    Node *Next;
    h=findHashValue(c);
    Element=first[h];
    Next= Element->next;
    if(strcmp(Element->name,c)==0)
        first[h]=Next;
    else
        while(Next!=NULL&& OK==1)
        {
            if(strcmp(Next->name,c)==0)
            {
                Element->next=Next->next;
                OK=0;
            }
            else
            {
                Next=Next->next;
                Element=Element->next;
            }

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
