#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char * removeDuplicates(char word[]);

int targetFound(char charArray[], int num, char target);

void initializeEncryptArray(char key[], char encrypt[]);

void initializeDecryptArray(char encrypt[], char decrypt);

void processInput(FILE * inf, FILE * outf, char substitute[]);

int main()
{

FILE *input = fopen("test.txt", "rb");
if(input == NULL)
{
		printf("Could not find file\n");
		exit(1);
}
FILE *output = fopen("out.txt", "w");
char *encrypt = calloc(26, sizeof(char));
char *decrypt = calloc(26, sizeof(char));

//need to check if encryption or decryption here
processInput(input, output, encrypt);

}

char * removeDuplicates(char word[])
{
	int i;
	char letters[strlen(word)];
	letters[0] = '\0';
	for(i = 0; i < strlen(word); i++)
	{
		if(strchr(letters, word[i]) == NULL)
		{
			//letters[i] = word[i];
			strncat(letters, &word[i], 1);
		}
	}
	char *returnptr = calloc(strlen(letters), sizeof(char));
	returnptr = letters;
	return returnptr;
}
//Done, but I don't think I need this function
int targetFound(char charArray[], int num, char target)
{
	int x = num;
	while(x >= 0)
	{
		if(charArray[x] == target)
		{
			return x;
		}
		x--;
	}
	return 0;
}

void initializeEncryptArray(char key[], char encrypt[])
{
	key = removeDuplicates(key);
	encrypt[0] = '\0';
	int len = strlen(key);
	while(len >= 0)
	{
		encrypt[len] = key[len];
		len--;
	}
	//len = strlen(encrypt);
	len = 0;
	char letter = 'z';
	
	//add the alphabet to encrypt
	while(len <=  25)
	{	
		const char *ptr = strchr(encrypt, letter);
		//add the char to encrypt if it's not in it already
		if(!ptr)
		{
			strncat(encrypt, &letter, 1);
		}
		
		len++;
		letter--;
	}
	
}

void processInput(FILE * inf, FILE * outf, char substitute[])
{
	//later here will need to use argv[n] to get the key
	char *key = "hello";
	char *input;
	
	//get the size of the input file
	fseek(inf, 0, SEEK_END);
	long size = ftell(inf)+1;
	input = calloc(size, sizeof(char));
	rewind(inf);
	
	//get the contents of 
	fgets(input, size, (FILE*)inf);
	printf("File contents: %s\n", input);
	
	/////////////////////////////////////////////
	//if encrypt, initialize encrypt, else decrypt
	/////////////////////////////////////////////
	//initialize array for encryption
	initializeEncryptArray(key, substitute);
	int pos;
	int i;
	for(i = 0; i < strlen(input); i++)
	{
		pos = targetFound(substitute, 25, input[i]);
		if(pos != 0)
		{
			printf("Before: %c\n", input[i]);
			input[i] = substitute[pos];
			printf("After: %c\n", input[i]);
		}
	}
	printf("Input Encrypted: %s\n", input);
}


