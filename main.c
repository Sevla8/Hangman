#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#define ATTEMPTS 10
#define CENT 100

char readCharacter();
void echo(int, char*);

int main(int argc, char** argv) {

	FILE* file = fopen("dico.txt", "r");
	if (file == NULL)
		exit(1);

	long size = 0;
	char current;
	do {
		current = fgetc(file);
		if (current == '\n')
			size += 1;
	} while (current != EOF);
	rewind(file);

	srand(time(NULL));
	const long min = 0;
	const long max = size;
	long line = (rand() % (max - min + 1)) + min;

	char buff[CENT];
	while (line--) {
		fgets(buff, CENT, file);
	}

	fclose(file);

	int length = strlen(buff)-2;	// '\n' & '\0'
	char* word = malloc(sizeof(char)*(length+1));
	char* secret = malloc(sizeof(char)*(length+1));
	for (int i = 0; i < length; i += 1) {
		word[i] = buff[i];
		secret[i] = '*';
	}
	word[length] = '\0';
	secret[length] = '\0';

	int count = ATTEMPTS;

	printf("Welcome to Hangman Game\n");

	while (count && strcmp(word, secret)) {
		echo(count, secret);
		char input = readCharacter();

		char* found = strchr(word, input);

		if (found != NULL) {
			for (int i = 0; i < length; i += 1) {
				if (word[i] == input)
					secret[i] = input;
			}
		}
		else
			count -= 1;
	}

	if (count)
		printf("\nCongratulation ! The secret word is indeed : %s\n", word);
	else
		printf("\nYou lost ! :-( The secret word was : %s\n", word);

	free(word);
	free(secret);

	exit(0);
}

char readCharacter() {
	char character = toupper(getchar());
	while (getchar() != '\n');
	return character;
}

void echo(int count, char* secret) {
	printf("\nYou still have %d attempts\n", count);
	printf("What is the secret word? %s\n", secret);
	printf("Submit a letter: ");
}
