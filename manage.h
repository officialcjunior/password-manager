#include <string.h>

char password[40], reference[40], key[40], output[40], inputreference[40];
char *randomString = NULL;
int i;

char *randstring(size_t length) {

    static char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789,.-#'?!";        
    if (length) 
    {
        randomString = malloc(sizeof(char) * (length +1));
        if (randomString) 
        {            
            for (int n = 0;n < length;n++) 
            {            
                int key = rand() % (int)(sizeof(charset) -1);
                randomString[n] = charset[key];
            }
            randomString[length] = '\0';
        }
    }
    return randomString;
}

extern void save()
{
	puts("Enter your password");
	scanf("%s", &password);
	puts("Enter your reference word");
	scanf("%s", &reference);
	randstring(strlen(password));
	printf("%s\n",randomString);
	FILE *fp;
	fp=fopen("passwords.txt","a+");
	if (fp == NULL)
		puts("File failed to open");
	else
	{
		if (strlen(randomString)>0)
		{
			fputs(randomString,fp);
			fputs(" ",fp);
			fputs(reference,fp);
			fputs("\n",fp);
		}
	}
	fclose(fp);
	for (i=0;i<strlen(password);i++)
	{
		char temp=(char)randomString[i]^password[i];
		printf("%c",(char)randomString[i]^password[i] );
		key[i]=temp;
	}
	key[i]='\0';
	puts(key);
	FILE *p;
	p=fopen("keys.txt","a+");
	if (p == NULL)
		puts("File failed to open");
	else
	{
		if (strlen(reference)>0)
		{
			fputs(reference,p);
			fputs(" ",p);
			fputs(key,p);
		}
		fputs("\n",p);
	}		

}

extern void open()
{
	puts("Enter reference word");
	scanf("%s", &inputreference);
	FILE *fp;
	fp=fopen("passwords.txt","r");
	if (fp == NULL)
		puts("File failed to open");
	else
	{
		for (int i=0;i<40;i++)
		{	
			fscanf(fp,"%s %s", &randomString, &reference);
			if (strcmp(reference,inputreference)==0)			//randomString
				break;
		}
	}
	fclose(fp);
	printf("%s",password);
	FILE *f;
	f=fopen("keys.txt","r");
	if (fp == NULL)
		puts("File failed to open");
	else
	{
		for (int i=0;i<40;i++)
		{	
			fscanf(fp,"%s %s", &reference, &key);
			if (strcmp(reference,inputreference)==0)
				break;
		}
	}
	printf("%s\n",key);
	for (i=0;i<strlen(password);i++)
		output[i]=(char)key[i]^randomString[i];
	output[i]='\0';
	printf("%s ",output);	
}	 