#include <stdio.h>

#include "manage.h"

int main()
{
	int choice;
	puts("Welcome to cjunior's password manager");
	do
	{
		puts("1. Save a new password\n2. Open a saved password\n3. Exit");
		scanf("%d",&choice);
		switch(choice)
		{
			case 1:save();break;
			case 2:open();break;
			default: puts("Enter a valid choice");break;
		}
	}
	while (choice!=3);
	return 0;
}