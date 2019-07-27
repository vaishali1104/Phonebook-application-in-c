#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>


struct contact
{
	char name[40];
	char address[50];
	long int mobile_no;
	char mail[100];	
};

void menu();
void addcontact();
void viewcontact();
void searchcontact();
void deletecontact();

void menu()
{
	system("cls");
	printf("\t\t**********WELCOME TO PHONEBOOK*************");

	printf("\n\n\t\t___________________MENU__________________\t\n\n");
	printf("\t\t*******************************************\t\t");
	printf("\n\n\t\t 1. Add new contact \t\t");
	printf("\n\n\t\t 2. View list of cantacts  ");
	printf("\n\n\t\t 3. Search contact ");
	printf("\n\n\t\t 4. Delete contact ");	
	printf("\n\n\t\t 5. Exit ");
	printf("\n\n\t\t******************************************");
	printf("\n\t\tEnter your choice: ");
		
	switch(getch())
	{
    	case '1': addcontact();
    				break;
    				
		case '2': viewcontact();
    				break;
    				
    	case '3': searchcontact();
					break;
					
		case '4': deletecontact();
					break;
					
    	case '5': exit(0);
			
    	default: 	system("cls");
                	printf("\n\t\tEnter 1 to 5 only..");
                	printf("\n\t\tEnter any key");
                	getch();
					menu();
	}
}

void addcontact()
{
	system("cls");
	
	FILE *f;
	
	struct contact c;
	f=fopen("phonebook","ab+");
	
	printf("\n\t\tEnter name: ");
	gets(c.name);

	printf("\n\t\tEnter address: ");
	gets(c.address);
	
	printf("\n\t\tEnter email address: ");
	gets(c.mail);
	
	printf("\n\t\tEnter mobile number: ");
	scanf("%ld",&c.mobile_no);
	
	fwrite(&c,sizeof(c),1,f);

    fflush(stdin);
	printf("\n\t\tRecord saved..!!");

	fclose(f);

    printf("\n\n\t\tEnter any key");

	getch();
    system("cls");
    menu();
}

void viewcontact()
{
	struct contact c;
	
	FILE *f;
	
	f=fopen("phonebook","rb");
	
	if(f==NULL)
	{
		printf("\n\n\t\tNo contacts in list..!!");
		getch();
		system("cls");
		menu();
	}
	
	while(fread(&c,sizeof(c),1,f)==1)
	{
		system("cls");
		printf("\n\t\tContact Details are\n");
		
		printf("\n\t\tName: %s",c.name);
		printf("\n\t\tAddress: %s ",c.address);
		printf("\n\t\tMobile Number: %ld",c.mobile_no);
		printf("\n\t\tMail: %s",c.mail);
		
		getch();
		system("cls");
				
	}
	fclose(f);
	printf("\n\t\tEnter any key");
	getch();
	system("cls");
	menu();
}

void searchcontact()
{
	struct contact c;
	FILE *f;
	
	char name[40];
	
	f=fopen("phonebook","rb");
	
	if(f==NULL)
	{
		printf("\n\t\tNo contacts in list ");
		exit(1);
	}
	printf("\n\t\tEnter the name of the contact for detalis: ");
	gets(name);
	
	while(fread(&c,sizeof(c),1,f)==1)
	{
		if(strcmp(c.name,name)==0)
		{
			system("cls");
			printf("\n\t\tContact Details of %s",name);
			printf("\n\n\t\tName: %s",c.name);
			printf("\n\t\tAddress: %s ",c.address);
			printf("\n\t\tMobile Number: %ld", c.mobile_no);
			printf("\n\t\tMail: %s",c.mail);
			break;
		}
		else
		{
			
			printf("\n\t\tNo contact found with this name..!! ");
		}
		
	}
	
	fclose(f);
	printf("\n\t\tEnter any key");
	getch();
	system("cls");
	menu();
}

void deletecontact()
{
    struct contact c;
    
    FILE *f,*ft;
    
	int flag;
	char name[100];
	char a[30];
	
	f=fopen("phonebook","rb");
	
	if(f==NULL)
	{
		printf("\n\n\t\tContact details not added yet..!!");
	}
	else
	{
		ft=fopen("temp","wb+");
		if(ft==NULL)
		{
			printf("\n\n\t\tFile opening error..!!");
		}
		else
        {


			printf("\n\n\t\tEnter Contact name which you want to delete: ");
			gets(name);

			fflush(stdin);
		
			while(fread(&c,sizeof(c),1,f)==1)
			{
				if(strcmp(c.name,name)!=0)
				{
					fwrite(&c,sizeof(c),1,ft);
				}
				
				if(strcmp(c.name,name)==0)
                {
                	flag=1;
				}
			}
			
			fclose(f);
			fclose(ft);	
		
			if(flag!=1)
			{
				printf("\n\n\t\tNo contact to delete..!!");
				remove("temp.txt");
			}
			else if(flag==1)
			{
				if(remove("phonebook")==0)
				{
					rename("temp.txt","phonebook");
					printf("\t\tRecord deleted successfully..!!");
				}
			}
			
		}
	}
		
	printf("\n\n\t\tEnter any key");
	getch();
    system("cls");
	menu();
}

void main()
{
	system("color 74");
	menu();
}
