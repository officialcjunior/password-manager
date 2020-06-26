/* 
	File: key-generator.c

	With the help of rand() from stdlib.h, a random character from the character array is taken
	is repeated n times to create a random string of length n.
*/

extern void key_generator(char *key, int n)
{
	srand((unsigned int)(time(NULL)));
	int index = 0;

	char strings[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
	
		for(index = 0; index <n; index++)
		{
			key[index] = strings[rand() % (sizeof strings - 1)];
		}
	key[index]='\0';
}