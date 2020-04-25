/* 

	File: password-manager.c

	Declares the necessary function defintions and modules for the password manager.

*/




#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void cipher(char[],char[],char[]);

void save_password();

void open_password();

void display_password();

void erase_fault();

char password[100], reference[100], encrypted[100], key[100], decrypted[100];
