#include <stdio.h>
#include <stdlib.h>
#include "student.h"


void swap(node a, node b) 
{ 
   student temp;
   temp = a->st; 
   a->st = b->st; 
   b->st = temp; 
} 

void bubbleSort( node start) 
{ 
   int swapped; 
   node ptr1; 
   node lptr = NULL; 
  
   
   if (start == NULL) 
      return; 
  
   do
   { 
      swapped = 0; 
      ptr1 = start; 
  
      while (ptr1->next != lptr) 
      { 
         if (ptr1->st.id > ptr1->next->st.id) 
         {  
            swap(ptr1, ptr1->next); 
            swapped = 1; 
         } 
         ptr1 = ptr1->next; 
      } 
      lptr = ptr1; 
   } 
   while (swapped); 
} 

void printMenu()
{
   printf("**************************************************\n");
   printf("*       To add a new student press 1             *\n");
   printf("*       To delete a student press 2              *\n");
   printf("*        To print a student press 3              *\n");
   printf("*     To print all the students press 4          *\n");
   printf("*     To update a Student's info press 5         *\n");
   printf("*              To exit press 6                   *\n");
   printf("**************************************************\n");
}

void list_insertafter(list l, node after, node n){
   //assert(l && after && n);
   if(l==NULL || after ==NULL || n==NULL)
   {
      printf("assertion errorn\n");
      return ;
   }
   n->next = after->next;
   after->next = n;
   l->size++;
}

node list_next(node n) 
{
   //assert(n);
   if(n == NULL)
   {
      printf("assertion error\n");
      return 0;
   }
   return n->next;
}

list list_create() 
{
   list l = (list) malloc(sizeof(struct _list));
   //assert(l);
   if(l==NULL)
   {
      printf("assertion error\n");
      return 0;
   }
   l->head = NULL;
   l->size = 0;
   return l;
}

node list_newnode(student st) 
{
   node n = (node) malloc(sizeof(struct _node));
   //assert(n);
   if(n==NULL)
   {
      printf("assertion error\n");
      return 0;
   }
   n->st = st;
   n->next = NULL;
   return n;
}

node list_first(list l) 
{
   //assert(l);
   if(l==NULL)
   {
      printf("assertion error\n");
      return 0;
   }
   return l->head;
}

void list_insertfirst(list l , node n)
{
   //assert(l && n);
   if(l==NULL || n==NULL)
   {
      printf("assertion error\n");
      return ;
   }
   n->next = l->head;
   l->head = n;
   l->size++;
}


int check_id(list l)
{
   int id;
   student* st;
   Start:
   printf("provide student's id (Give an integer,positive and unique number for id please) \n");
   while(scanf("%d",&id)!=1 || id<1 )
   {  
      printf("wrong input \n");
      while (getchar()!='\n')
      ;
      printf("provide student's id (Give an integer,positive and unique number for id please) \n");
   }
   st=findStudent(id,l);
   while(st!=NULL){
      printf("wrong input (There is another student with id!) \n");
      goto Start;
   }
   return  id;
   
}

student* findStudent(int id,list l)
{
   node currentnode=l->head;
   if(l->size==0) return (&currentnode->st);
   while(currentnode->st.id!=id){
      if(currentnode->next==NULL){
         return NULL;
      }
      currentnode=list_next(currentnode);
   }
   return(&currentnode->st);
}

int addStudent(student st,list l )
{
   st.id=check_id(l);
   printf("provide name\n");
   scanf("%s",st.name);
   list_insertfirst (l , list_newnode(st));
   
   printf("\n");
   printf("New student's name %s and id= %d\n\n",st.name,st.id);
   
   return 0;
}

void printstudents(list l)
{
   
   if(l->size==0){
      printf("list is empty \n");
   }else{
      node currenthead;
      for (currenthead=l->head;currenthead!=NULL;currenthead = list_next(currenthead)){
         bubbleSort(currenthead);
         print(currenthead->st);
      }
   } 
   return ;
}

int print(student st)
{
   printf("Name: %s \nId = %d\n\n",st.name ,st.id);
   return 0;
}

node findPrevStudent(int id,list l)
{
   node prevnode = l->head;
   while(prevnode->next!=NULL)
   {
      if(prevnode->next->st.id == id )
      {
         return prevnode;
      }else 
      {  
         prevnode = prevnode->next;
      }
   }
   return NULL;
}

void save(char *filename, list l)
{
   node x = l->head;
   FILE *fd = fopen(filename,"wb+");
   for(int i=0;i<l->size;i++)
   {
      fwrite(&x->st,sizeof(student),1,fd);
      x=list_next(x);
   }

   fclose(fd);
}

list load(char *filename)
{  
   int ans;
   student st;
   list ll = list_create();
   FILE *fd = fopen(filename,"rb");
   if(fd==NULL)
   {
      printf("The file is not exist\n");
      printf("Do you want to create it?\n");
      printf("Provide 1 for yes and 2 for no\n");
      do 
      {
         scanf("%d",&ans);
         if(ans < 1 || ans > 2 )
         {
            printf("Wrong input your choice must be 1 or 2\n");
         }
      }while(ans < 1 || ans > 2 );
      switch (ans)
      {
      case 1:
         save(filename,ll);
         return ll;
      
      case 2:
         exit(1);
      }   
   }
   while (1)
   {   
      fread(&st,sizeof(student),1,fd);
      if (!feof(fd))
      {
         list_insertfirst(ll,list_newnode(st));
      }
      else
      {
         break;
      }
   }

   fclose (fd);

   return ll;
}


int deleteStudent(student st,list l)
{  
   node prev;
   prev=findPrevStudent(st.id,l);
   if(l==NULL || prev==NULL || prev->next==NULL )
   {
      if(prev==NULL)
      {
        l->head=l->head->next; 
        l->size--;
      }
      printf("there is a problem in assertation\n");
      return 0;
   }
   node ret = prev->next;
   prev->next = ret->next;
   ret->next = NULL;
   l->size--;
   return 0;
}

int updateStudent(student st,list l)
{  
   int c;
   int new_id;
   int run =1 ; 
   printf("What do you want to change to this student ?\n");
   printf("To change his name press 1 \n");
   printf("To change his id press 2 \n");
   printf("To change both press 3 \n");
   do 
   {
      scanf("%d",&c);
      if(c < 1 || c > 3 )
      {
         printf("Wrong input your choice must be between 1 and 3 \n");
      }
   }while(c < 1 || c > 3 );
      
   while(run){
      switch (c)
      {
         case 1:
            new_id = st.id;
            deleteStudent(st,l);
            printf("provide the new name that you want to give to this student\n");
            scanf("%s",st.name);
            st.id = new_id;
            list_insertfirst (l , list_newnode(st));
            return 0;   
         case 2:
            deleteStudent(st,l);
            printf("provide the new id that you want to give to this student\n");
            scanf("%d",&st.id);
            list_insertfirst (l , list_newnode(st));
            return 0;
         case 3:
            deleteStudent(st,l);
            printf("provide student's new id:\n");
            do {
               scanf("%d",&st.id);
               if (st.id<=0){
                  printf("Wrong input , id must be a possitive number\n");
               }
            }while (st.id<=0);
   
            printf("provide the new id that you want to give to this student\n");
            scanf("%s",st.name);
            list_insertfirst (l , list_newnode(st));

            return 0; 
      }
   }
   return 0;  
}