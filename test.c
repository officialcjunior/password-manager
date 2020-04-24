
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

char baseStr[40], reference[40];
char encrypted[40], key[40], decrypted[40];

void keygen(char *key, int n)
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


void encryptDecrypt(char *input, char *output, char *key) 
{
	int i;
	for(i = 0; i < strlen(input); i++) 
	{
		output[i] = input[i] ^ key[i]; //i % (sizeof(key)/sizeof(char))
	}
	output[i]='\0';
}


void save()
{	
	puts("Enter your reference");
	scanf("%s", &reference);
	puts("Enter your password");
	scanf("%s", &baseStr);  //basestr is the password

	keygen(key,strlen(baseStr));

	encryptDecrypt(baseStr, encrypted, key);

	printf("reference: %s key:%s encrypted:%s \n",reference,key, encrypted );

	FILE *fp;
	fp=fopen("vault.txt","a");
	if (fp == NULL)
		puts("File failed to open");
	else
	{
		fprintf(fp,"%s %s %s \n",reference, encrypted, key);
	}
	fclose(fp);

	printf("Encrypted:%s", encrypted);

}


void open ()
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
	printf("reference: %s key:%s encrypted:%s \n",reference, key, encrypted );

	encryptDecrypt(encrypted, decrypted, key); //output is at decrypted

	printf("Decrypted:%s\n", decrypted);
}

int main () {

	int choice;
	puts("Welcome to the password manager");
	do
	{
		puts("\n1. Save a new password\n2. Open a saved password\n3. Exit");
		scanf("%d",&choice);
		switch(choice)
		{
			case 1:save();break;
			case 2:open();break;
			default: puts("Enter a valid choice");break;
		}
	}
	while (choice!=3);

}