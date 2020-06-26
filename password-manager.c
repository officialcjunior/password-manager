/* 
	File: password-manager.c

	Source file of the password-manager.
*/


#include "headers/password-manager.h"
#include "external/key-generator.c"


/*
The main() function prompts the user to accept his or her choices. 
Corresponding functions are then invoked.
*/

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

/*
	cipher() implements the XOR cipher. The result is stored into *output 
*/

void cipher(char *input, char *output, char *key) 
{
	int i;
	for(i = 0; i < strlen(input); i++) 
	{
		output[i] = input[i] ^ key[i]; 			//i % (sizeof(key)/sizeof(char))
	}
	output[i]='\0';
}

/* 	
	A random string is generated using key_generator() and is passed to cipher() 
	and the resulting string is written to the password vault. 										
*/

void save_password()
{	
	puts("Enter your reference");
	scanf("%s", reference);
	puts("Enter your password");
	scanf("%s", password);

	key_generator(key,strlen(password));

	cipher(password, encrypted, key);

	//printf("reference: %s key:%s encrypted:%s \n",reference,key, encrypted );

	FILE *fp;
	fp=fopen("password-vault/vault.txt","a");
	if (fp == NULL)
		puts("File failed to open");
	else
	{
		fprintf(fp,"%s %s %s",reference, encrypted, key);
		fputs("\n",fp);
	}
	fclose(fp);

	puts("Your password has been encrypted and saved");
}

/*
	After prompting the user to enter the reference, password vault is opened
	and the references are compared.
	When found, the encrypted string and the key is passed to cipher() for
	decrypting
*/ 

void open_password ()
{
	char input_reference[40];
	puts("Enter reference word \n");
	scanf("%s", input_reference);

	FILE *fp;
	fp=fopen("password-vault/vault.txt","r");
	if (fp == NULL)
		puts("File failed to open");
	else
	{
		for (int i=0;i<40;i++)
		{	
			fscanf(fp,"%s %s %s \n", reference, encrypted, key);
			if (strcmp(reference,input_reference)==0)			
				break;
		}
	}
	//printf("reference: %s key:%s encrypted:%s \n",reference, key, encrypted );

	cipher(encrypted, decrypted, key); //output is at decrypted

	printf("Decrypted password:%s \n", decrypted);
}

/*
	The password vault is read and the references are printed out to STDOUT until EOF
*/

void display_references ()
{
	puts("The references are:");
	FILE *fp;
	fp=fopen("password-vault/vault.txt","r");
	if (fp == NULL)
		puts("File failed to open");
	else
	{
		while (!feof(fp))
		{	
			fscanf(fp,"%s %s %s \n", reference, encrypted, key);
			puts(reference);
		}
	}		
}

/*
	Deletes the password vault.
*/
void erase_vault ()
{
	if (remove("password-vault/vault.txt") == 0) 
    	printf("Password vault deleted successfully"); 
    else
    	printf("Unable to delete the vault"); 
}