/*-------------------------------------------------------------------------
  Include files:
--------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define KEY_SIZE 52
#define WORDS_ARRAY_SIZE 100
#define MAX_STR_LEN 50
#define TRUE_VAL 1
#define TEMP_ARRAY_SIZE 2



char encrypt(unsigned char key[KEY_SIZE], char ch);
int read_words(char* words[], int size, int max_str_len);
void encrypt_words(char* words[], int num_words, unsigned char key[KEY_SIZE]);
void release_memory(char* words[], int num_words);

//prints all the encrypted words
void print_words(char* words[], int num_words)
{
	int i;
	for (i = 0; i < num_words; i++) {
		printf("%s\n", words[i]);
	}
}

//initiates all the other functions
int main()
{
	unsigned char key[KEY_SIZE] = {

		'>', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '~', 'S', 'D',
		'F', 'G', '*', 'J', 'K', 'L', 'Z', 'X', 'C', 'V', 'B', '+', 'M',
		'm','b','n','v','z','c','@','q','r','u','i','e','r',
		't','o','p','w','$','j','g','d','%','s','f','h','k'
	};
	int num_words = 0, i;
	char* words[WORDS_ARRAY_SIZE];

	for (i = 0; i < WORDS_ARRAY_SIZE; i++) {
		words[i] = NULL;
	}

	num_words = read_words(words, WORDS_ARRAY_SIZE, MAX_STR_LEN);
	if (num_words == -1)
	{
		printf("Failed to read words.\n");
		return 0;
	}
	encrypt_words(words, num_words, key);
	print_words(words, num_words);
	release_memory(words, num_words);
	return 0;
}

//gets one char at a time and sends back the corresponding char is represnted in the cypher
char encrypt(unsigned char key[KEY_SIZE], char ch) {
	unsigned char normalLetters[KEY_SIZE] = {
		'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
		'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
		'a','b','c','d','e','f','g','h','i','j','k','l','m',
		'n','o','p','q','r','s','t','u','v','w','x','y','z'
	};
	int letterPlace = 0;
	for (int i = 0; i < KEY_SIZE; i++) {
		if (ch == normalLetters[i])
			letterPlace = i;
	}
	return key[letterPlace];
}

//reads all the words into an array and dinamiclley allocates space for them. 
//returns the number of words that have been read.
int read_words(char* words[], int size, int max_str_len) {
	int wordCounter = 0;
	int isEnd = 0;
	char wholeString[MAX_STR_LEN+1];
	int scanResult = TRUE_VAL;

	while (isEnd == 0 && wordCounter<size) {
		scanResult = scanf("%s", wholeString);
		int i = 0;
		if (scanResult != TRUE_VAL)
			isEnd = 1;
		if (scanResult == TRUE_VAL) {
			char *wordMemory = ((char*)malloc(sizeof(char)*strlen(wholeString) + 1));
			*wordMemory = '\0';
			while (wholeString[i] != '\0' && i <= max_str_len) {
				char currentChar[TEMP_ARRAY_SIZE] = { wholeString[i],'\0' };
				strcat(wordMemory, currentChar);
				i++;
			}
			words[wordCounter] = wordMemory;
			wordCounter++;
			
		}
	}

	if (wordCounter == 0) {
		return -1;
	}
	return wordCounter;
}

//takes every word in the array and switchs it around to the encoded word.
//puts the encoded word back into the same array
void encrypt_words(char* words[], int num_words, unsigned char key[KEY_SIZE]) {
	for (int i = 0; i < num_words; i++) {
		int wordLength = (strlen(words[i]))+1;
		char* tempWord = (char*)malloc(sizeof(char)*wordLength);
		*tempWord = '\0';
		strcpy(tempWord, words[i]);
		char* tempEncriptedWord = (char*)malloc(sizeof(char)*wordLength);
		*tempEncriptedWord = '\0';
		for (int j = 0; j < wordLength-1; j++) {
			char tempLetter = tempWord[j];
			
			char encriptedLetter = encrypt(key, tempLetter);
			char encriptedLetterStr[TEMP_ARRAY_SIZE] = { encriptedLetter,'\0' };
			strcat(tempEncriptedWord, encriptedLetterStr);
		}
		
		strcpy(words[i], tempEncriptedWord);
		free(tempWord);
		free(tempEncriptedWord);
	}
}

//releases the memory of all the encoded words in the array
void release_memory(char* words[], int num_words) {
	for (int i = 0; i < num_words; i++) {
		free(words[i]);
	}
}