#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char * removeDuplicates(char word[]);

int targetFound(char charArray[], int num, char target);

void initializeEncryptArray(char key[], char encrypt[]);

void initializeDecryptArray(char encrypt[], char decrypt);

void processInput(FILE * inf, FILE * outf, char substitute[]);

char *key;
int choice;
char *inputFile;
char *outputFile;
int main(int argc, char **argv)
{
	if(argc < 5)
	{
		printf("Not enough arguments specified. The arguments are: [Encryption key] [Function (1 for encrypt 2 for decrypt)] [input file name] [output file name]\n");
		return -1;
	}
	key = malloc(sizeof(argv[1]));
	key = argv[1];
	choice = atoi(argv[2]);
	inputFile = malloc(sizeof(argv[3]));
	inputFile = argv[3];
	outputFile = malloc(sizeof(argv[4]));
	outputFile = argv[4];
	
	FILE *input = fopen(inputFile, "rb");
	if(input == NULL)
	{
			printf("Could not find file\n");
			exit(1);
	}
	FILE *output = fopen(outputFile, "w");
	char *substitute = calloc(26, sizeof(char));

	processInput(input, output, substitute);

	fclose(input);
	fclose(output);
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
	return -1;
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
	//char *key = "feather";
	char *input;
	
	//get the size of the input file
	fseek(inf, 0, SEEK_END);
	long size = ftell(inf)+1;
	input = calloc(size, sizeof(char));
	rewind(inf);
	
	//get the contents of 
	fgets(input, size, (FILE*)inf);
	printf("File contents: %s\n", input);
	
	//initialize array for encryption or decryption
	initializeEncryptArray(key, substitute);
	//pos is the position of the letter in the substitute array
	int pos;
	int i;
	
	if(choice == 1)
	{
		for(i = 0; i < strlen(input); i++)
		{
			pos = targetFound(substitute, 25, input[i]);
			if(pos >= 0)
			{
				input[i] = (97+pos);
			}
		}
		printf("Input Encrypted: %s\n", input);
		fprintf(outf, "%s", input);
		printf("Encrypted file created.\n");
	}
	else
	{
		for(i = 0; i < strlen(input); i++)
		{
			int num = (input[i] - 97);
			if(num >= 0)
			{
				printf("Input[%d]: %c\n", i, input[i]);
				input[i] = substitute[input[i] - 97];
			}
		}
		
		printf("Input Dencrypted: %s\n", input);
		fprintf(outf, "%s", input);
		printf("Dencrypted file created.\n");
	}
	
}



