#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


struct node{
char *word; 
int status;
struct node *next; 
};

struct node *HashTable(int m)
{
    struct node * HashTab =(struct node*)malloc(sizeof(struct node)*m);
    for(int i=0;i<m;i++)
    {
        HashTab[i].next=NULL;
        HashTab[i].status=0;
        
    }
    return HashTab;
}

int hashfunction(char words[500],int size)
{
    int sum =0;
    for(int i=0;i<strlen(words);i++)
    {
        if(words[i]<97)
        {
            sum+=(words[i]-64)*pow(3,i);
        }
        else
        {
            sum+=(words[i]-96)*pow(3,i) ;
        }
    }
   return sum%size;
    
}


void INSERT(struct node * Table, char words[500],int size )
{
  
   int index = hashfunction(words,size);
   
   struct node * temp = Table;
   struct node * newnode = (struct node*)malloc(sizeof(struct node));
   newnode->next=NULL;
   temp+=index;
   while(temp->next!=NULL)
   {   
       temp=temp->next;
   }
   temp->word=words;
   temp->status = 1;
   temp->next=newnode;
   
  // printf("%s",temp->word);
  
}


void DeleteData(struct node * Table, char words[500],int size )
{

   int index = hashfunction(words,size);
   struct node * temp = Table;
   temp+=index;
   while(temp->next!=NULL)
   {   
       if(strcmp(temp->word,words)==0)
       { //printf("%s",temp->word);
         temp->word[0]='\0';
         temp->status = 2; 
     
       }
       
       temp=temp->next;
   }
}

void Print(struct node * Table,int size )
{
    int stat=0;
    for(int i=0;i<size;i++)
    { 
        struct node * temp = Table;
        temp+=i;
        if(temp->next==NULL)
        continue;
        if((temp->next->status)==1)
         {stat++;
          break;
             
         }
    }
    if(stat==0)
    printf("1\n");
    else 
    printf("-1\n");
    
}


int main(void) {
    int size;
   
    scanf("%d",&size);
    struct node *Table=HashTable(size);
    char name[100];
	char ch='a';
    while (ch!='t')
    {   scanf("%c", &ch);
        switch (ch)
      {
        case 'i':
            scanf("%s", name);
            INSERT(Table, name,size);
            break;
            
        case 'd':
           scanf("%s", name);
            DeleteData(Table, name,size);
           break;
         case 'p':
          
          Print(Table,size);
           break;     
        case 't':
            return 0;
      }
    }
}