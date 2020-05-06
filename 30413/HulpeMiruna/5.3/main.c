#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

const int MAXNAME=200;

typedef struct
{
    char *name;
    float price;
    int amount;
    int dateOfManufacturing;
    int dateOfExpiration;
} Pharmacy;


typedef struct nodeT
{
    Pharmacy Medicine;
    struct nodeT *left, *right;
} NodeT;

typedef struct node
{
    char *name;
    struct node *left, *right;
} NodeChar;

NodeChar *ExpiredTree=NULL;

NodeT *insert (Pharmacy M,NodeT *tree)
{
 if(tree==NULL)
 {
     NodeT *p=(NodeT *) malloc (sizeof(NodeT));
     p->Medicine.name=(char *) malloc (sizeof(char)*MAXNAME);
     strcpy(p->Medicine.name,M.name);
     p->Medicine.amount=M.amount;
     p->Medicine.dateOfExpiration=M.dateOfExpiration;
     p->Medicine.dateOfManufacturing=M.dateOfManufacturing;
     p->Medicine.price=M.price;
     p->left=NULL;
     p->right=NULL;
     return p;
 }
 else{
          if(strcmp(tree->Medicine.name,M.name)<0)
           {
            tree->right=insert (M,tree->right);
           }
           else tree->left=insert (M,tree->left);
        return tree;
    }
}

NodeT*  find (char *c, NodeT *T)
{
    if(T!=NULL)
    {  if (strcmp(T->Medicine.name,c)==0)
          return T;
        if(strcmp(T->Medicine.name,c)<0) return  find (c,T->right);
            else if(strcmp(T->Medicine.name,c)>0) return  find (c,T->left);
    }
    return NULL;
}
NodeT * FindMax(NodeT *T)
{
    while(T->right!=NULL)
    {
        T=T->right;
    }
    return T;
}
NodeChar * FindMaxx(NodeChar *T)
{
    while(T->right!=NULL)
    {
        T=T->right;
    }
    return T;
}
NodeT *deletee(char *c,NodeT *T)
{  if(T!=NULL)
{
    if(strcmp(T->Medicine.name,c)>0)  T->left=deletee(c,T->left);
    else if(strcmp(T->Medicine.name,c)<0) T->right=deletee(c,T->right);
    else if(strcmp(T->Medicine.name,c)==0)
    {
        if(T->right==NULL&&T->left==NULL) T=NULL;
        else if(T->right!=NULL&&T->left==NULL) T=T->right;
             else if(T->right==NULL&&T->left!=NULL) T=T->left;
                  else T= FindMax(T->left);
    }
}
return T;
}
void inorder(NodeChar *T,int level,FILE *g)
{
    if(T!=NULL)
    {
        inorder( T->left, level + 1 ,g);
        int i;
        for ( i = 0; i <= level; i++ )
            fprintf(g, " " );
        fprintf(g,"%s\n",T->name);
        inorder( T->right, level + 1,g );
    }
}
NodeChar *insertee (char *c,NodeChar *tree)
{
 if(tree==NULL)
 {
     NodeChar *p=(NodeChar *) malloc (sizeof(NodeT));
     p->name=(char *) malloc (sizeof(char)*MAXNAME);
     strcpy(p->name,c);
     p->left=NULL;
     p->right=NULL;
     return p;
 }
 else{
          if(strcmp(tree->name,c)<0)
           {
            tree->right=insertee (c,tree->right);
           }
           else tree->left=insertee (c,tree->left);
        return tree;
    }
}
NodeChar *deleteee(char *c,NodeChar *T)
{
    if(T!=NULL)
    {
        if(strcmp(T->name,c)>0)
            T->left=deleteee(c,T->left);
        else if(c>T->name)
            T->right=deleteee(c,T->right);
        else if(strcmp(T->name,c)==0)
        {
            if(T->right==NULL&&T->left==NULL)
                T=NULL;
            else if(T->right!=NULL&&T->left==NULL)
                T=T->right;
            else if(T->right==NULL&&T->left!=NULL)
                T=T->left;
            else
                T= FindMaxx(T->left);
        }
    }
    return T;
}
int returnDate()
{   int date;
    int day,month,year;
    time_t now=time(&now);
    struct tm *local=localtime(&now);
    day=local->tm_mday;
    month=local->tm_mon+1;
    year=local->tm_year+1900;
    date = year*10000+month*100+day;
    return date;
}
NodeChar  *findd (char *c, NodeChar *T)
{
    if(T!=NULL)
    {
        if (strcmp(T->name,c)==0)
            return T;
        if(strcmp(T->name,c)<0)
            return  findd (c,T->right);
        else if(strcmp(T->name,c)>0)
            return  findd (c,T->left);
    }
    return NULL;
}

void readInstructions(FILE *f,FILE *g,NodeT *tree)
{    Pharmacy M;
    M.name=(char*) malloc (sizeof(char)*MAXNAME);
    char *strbuf=(char* ) malloc (sizeof(char)*MAXNAME);
    int date=returnDate();
    while(fscanf(f,"%s",strbuf)!=EOF)
    {
        char *p;
        p=strtok(strbuf,",\n");
        if(p[0]=='i')
        {
            strcpy(p,p+1);
            strcpy(M.name,p);
            p=strtok(NULL,",\n");
            M.price=atof(p);
            p=strtok(NULL,",\n");
            M.amount=atoi(p);
            p=strtok(NULL,",\n");
            M.dateOfManufacturing=atoi(p);
            p=strtok(NULL,",\n");
            M.dateOfExpiration=atoi(p);
            if(M.dateOfExpiration<date)
            {
                ExpiredTree=insertee(M.name,ExpiredTree);
            }
            tree=insert (M,tree);



        }
        else if(p[0]=='u')
            {strcpy(p,p+1);
             tree=find (p,tree);
             p=strtok(NULL,",\n");
            if(strcmp(p,"~")!=0)strcpy(tree->Medicine.name,p);
            p=strtok(NULL,",\n");
            if(strcmp(p,"~")!=0)tree->Medicine.price=atof(p);
            p=strtok(NULL,",\n");
            if(strcmp(p,"~")!=0)tree->Medicine.amount=atoi(p);
             p=strtok(NULL,",\n");
            if(strcmp(p,"~")!=0)tree->Medicine.dateOfManufacturing=atoi(p);
            p=strtok(NULL,",\n");
            if(strcmp(p,"~")!=0)
            {tree->Medicine.dateOfExpiration=atoi(p);
            if(tree->Medicine.dateOfExpiration!=date)
            {
                ExpiredTree=findd(tree->Medicine.name,ExpiredTree);
                if(ExpiredTree!=NULL)
                {if(tree->Medicine.dateOfExpiration>date)
                ExpiredTree=deleteee(p,ExpiredTree);
                else  ExpiredTree=insertee(p,ExpiredTree);
                }
            }
            }
            }
            else if(p[0]=='d')
            {strcpy(p,p+1);

             tree=deletee(p,tree);
             ExpiredTree=deleteee(p,ExpiredTree);
            }
            else if(strcmp(p,"ce")==0)
                 {
                  inorder(ExpiredTree,0,g);

                 }

    }
}

int main()
{
    FILE *f=fopen ("input.txt","r+");
    FILE *g=fopen ("output.txt","r+");
    NodeT *tree;
    tree=NULL;
    readInstructions(f,g,tree);
    return 0;
}
