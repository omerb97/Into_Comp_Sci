#include <stdio.h>


int DigitFind(int id) { // a function that figures out the checking number
	int sum = 0;
	int isolate = 0;
	int powerOf = 10000000;
	for (int i = 8; i > 0; i--) {
		isolate = id / powerOf;
		id %= powerOf;
		isolate *= ((i % 2) + 1);
		sum += (isolate > 9) ? isolate - 9 : isolate;
		powerOf /= 10;
	}
	return (10 - (sum % 10));
}

int isDig(char idchar) { // checks if its all numbers
	if (idchar >= 48 && idchar <= 57)
		return 1;
	return 0;
}

int main() {
	char action;
	char checkChar;
	int realnum;
	int flag = 0;
	int id = 0, secDigit;
	printf("Please enter the letter C for calculating CheckDigit and the letter V for validating an ID by its CheckDigit:\n\n");
	scanf("%c", &action); //what action does he want to preform?
	if (action == 'C') { // if he entered C
		printf("Calculating CheckDigit, please enter 8 digits:\n\n");
		//scanf("%c", &checkChar);
			
		for (int i = 0; i < 8; i++)
		{
			scanf("%c", &checkChar);
			while (flag == 0) { // if no numbe is entered then it countinues to ask
				if (checkChar >= 48 && checkChar <= 57)
					flag = 1;
				else if (checkChar > 57) {
					printf("ERROR");
					return 1;
				}
				else
					scanf("%c", &checkChar);
			}
			if (isDig(checkChar) == 0) { //ends program if its not a numbers
				printf("ERROR");
				return 1;
			}
			if (isDig(checkChar) == 1) {
				realnum = checkChar - '0';
				id = id * 10 + realnum;
			}// sums up the numbers so that it adds up to the ID

		}
		secDigit = DigitFind(id);
		printf("CheckDigit = %d", secDigit);
	}
	else if (action == 'V') { // if he entered V
		printf("Validating ID, please enter 9 digits ID:\n\n");
		scanf("%c", &checkChar);

		for (int i = 0; i < 9; i++)
		{
			scanf("%c", &checkChar);
			while (flag == 0) { // if no numbe is entered then it countinues to ask
				if (checkChar != '\n')
					flag = 1;
				else if (checkChar > 57) {
					printf("ERROR");
					return 1;
				}
				else {
					scanf("%c", &checkChar);
				}
			}
			//scanf("%c", &checkChar); // checks that it doesnt have any non number chars
			if (isDig(checkChar) == 0 && checkChar != '\n') {
				printf("ERROR");
				return 1;
			}
			if (isDig(checkChar) == 1) {
				realnum = checkChar - '0';
				id = id * 10 + realnum;
			}// sums up the numbers so that it adds up to the ID

		}
		int enteredChecked = id % 10;
		id /= 10;
		secDigit = DigitFind(id);
		printf("You have entered CheckDigit = %d\n", enteredChecked);
		printf("Calculated CheckDigit = %d\n", secDigit);
		if (enteredChecked == secDigit) // if the last digit is the same as the calculated one
			printf("\nLegal ID :)");
		else
			printf("\nIllegal ID :(");
	}
	else printf("ERROR");// any value that isnt C or V
	return 0;

}