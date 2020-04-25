
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char baseStr[40], reference[40], encrypted[40], key[40], decrypted[40];

void key_generator(char *key, int n)
{
	srand((unsigned int)(time(NULL)));
	int index = 0;

	char char1[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
	
		for(index = 0; index <n; index++)
		{
			key[index] =char1[rand() % (sizeof char1 - 1)];
		}
	key[index]='\0';
}


void cipher(char *input, char *output, char *key) 
{
	int i;
	for(i = 0; i < strlen(input); i++) 
	{
		output[i] = input[i] ^ key[i]; //i % (sizeof(key)/sizeof(char))
	}
	output[i]='\0';
}


void save_password()
{	
	puts("Enter your reference");
	scanf("%s", &reference);
	puts("Enter your password");
	scanf("%s", &baseStr);  //basestr is the password

	key_generator(key,strlen(baseStr));

	cipher(baseStr, encrypted, key);

	//printf("reference: %s key:%s encrypted:%s \n",reference,key, encrypted );

	FILE *fp;
	fp=fopen("vault.txt","a");
	if (fp == NULL)
		puts("File failed to open");
	else
	{
		fprintf(fp,"%s %s %s \n",reference, encrypted, key);
	}
	fclose(fp);

	puts("Your password has been encrypted and saved");
}


void open_password ()
{
	char inputreference[40];
	puts("Enter reference word");
	scanf("%s", &inputreference);

	FILE *fp;
	fp=fopen("vault.txt","r");
	if (fp == NULL)
		puts("File failed to open");
	else
	{
		for (int i=0;i<40;i++)
		{	
			fscanf(fp,"%s %s %s \n", &reference, &encrypted, &key);
			if (strcmp(reference,inputreference)==0)			//randomString
				break;
		}
	}
	//printf("reference: %s key:%s encrypted:%s \n",reference, key, encrypted );

	cipher(encrypted, decrypted, key); //output is at decrypted

	printf("Decrypted password:%s\n", decrypted);
}

void display_references ()
{
	FILE *fp;
	fp=fopen("vault.txt","r");
	if (fp == NULL)
		puts("File failed to open");
	else
	{
		puts("The references are");
		while (!feof(fp))
		{	
			fscanf(fp,"%s %s %s \n", &reference, &encrypted, &key);
			puts(reference);
		}
	}		
}

erase_vault ()
{
	if (remove("vault.txt") == 0) 
      printf("Password vault deleted successfully"); 
    else
      printf("Unable to delete the vault"); 

}

int main () 
{

	int choice;
	puts("Welcome to the password manager\n Enter your choice");
	do
	{
		puts("\n1. Save a new password\n2. Open a saved password\n3. Display all the references\n4. Erase the vault\n5. Exit the password manager");
		scanf("%d",&choice);
		switch(choice)
		{
			case 1:save_password();break;
			case 2:open_password();break;
			case 3:display_references();break;
			case 4:erase_vault();break;
			default: puts("Enter a valid choice");break;
		}
	}
	while (choice!=5);

}