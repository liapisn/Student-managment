#ifndef ASSIGNMENT_STUDENT_H
#define ASSIGNMENT_STUDENT_H


#define MAXSTRING 50

typedef struct
{
   char name[MAXSTRING];
   int id;
}student;

typedef struct _node* node;
struct _node 
{
	student st;
	node next;
};

typedef struct _list* list;
struct _list
{
	node head;
	int size ;
};


int addStudent(student ,list  );

list load(char *);

void save(char *, list );

void printstudents();

void printMenu();

student* findStudent(int ,list);

int deleteStudent(student,list);

int updateStudent(student , list);

int print(student );

void list_insertfirst(list, node);

node list_next( node );

node list_newnode(student);

list list_create();

node findPrevStudent(int ,list );

int check_id(list );


#endif //ASSIGNMENT_STUDENT_H
