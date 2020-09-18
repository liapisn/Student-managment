#include <stdio.h>
#include <stdlib.h>
#include "student.h"

int main (int argc,char **argv)
{   
    int choice; 
    list l =list_create();
    student st;   
    student* currentst;
    int ans;
    if(argc==2)
    {
        l=load(argv[1]);
        printf("\n");
    }else
    {
        printf("To start the programm you have to give a filename on command line after the executable file (e.g. ./a.out data.dat)\n");
        exit(1);
    }
    
    while (1)
    {
        printMenu();
        do 
        {
            scanf("%d",&choice);
            if(choice < 1 || choice > 6 )
            {
                printf("Wrong input your choice must be between 1 and 6 \n");
                printMenu();
            }
        }while(choice < 1 || choice > 6 );

        switch (choice)
        {
            case 1:       
                addStudent(st,l);
                break;
            case 2:
                printf("Provide the id of the student that you want to delete: ");
                scanf("%d",&st.id);
                currentst=findStudent(st.id,l);
                if(currentst==NULL)
                {
                    printf("there is not any student with this id to delete...\n");
                    break;
                }
                deleteStudent(*findStudent(st.id,l),l);
                break;
            case 3:
                printf("provide id of the student\n");
                scanf("%d",&st.id);
                currentst=findStudent(st.id,l);
                if(currentst==NULL)
                {
                    printf("there is not any student with this id\n");
                    break;
                }
                print(*findStudent(st.id,l));
                break;
            case 4:
                printstudents(l);
                break;
            case 5:
                printf("provide id of the student\n");
                scanf("%d",&st.id);
                currentst=findStudent(st.id,l);
                if(currentst==NULL)
                {
                    printf("there is not any student with this id\n");
                    break;
                }
                print(*findStudent(st.id,l));
                updateStudent(*findStudent(st.id,l),l);
                break;
            case 6 :
                printf("Do you want to save your list of students\nProvide 1 for yes and 2 for no \n");
                do 
                {
                    scanf("%d",&ans);
                    if(ans < 1 || ans > 2 )
                    {
                        printf("Wrong input your choice must be 1 or 2\n");
                    }
                }while(ans < 1 || ans > 2 );
                switch(ans)
                {
                    case 1:
                        save (argv[1],l);
                        printf("your list is saved!\n");
                        exit(1);
                    
                    case 2:
                        exit(1);
                }
        }
    } 
} 
