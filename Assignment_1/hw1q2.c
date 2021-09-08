#include <stdio.h>

int main() {
	unsigned long int encodedNums;
	printf("Enter an encoded word and I'll do my best:\n");
	scanf("%lu", &encodedNums);
	int temp;
	int counter = 0; // counts to see if there are any digits at all
	unsigned long int n = 1;
	while (encodedNums%n != encodedNums) { // figures out how many digits are in the number
		n *= 10;
	}
	
	n = n / 10;
	//printf("%d\n", n);

	while (n > 0) {
		if (n==1) { // if there is only one digit left
			break;
		}
		else if (n==10) { // if there are only 2 digits left
			int leftDigit = encodedNums / n;
			int middleDigit = (encodedNums / (n / 10)) - (leftDigit * 10);
			temp = middleDigit * 10 + leftDigit;
			if (temp == 97 || temp == 98 || temp == 99) { //checks if they are of a,b,c
				counter++;
				if (counter == 1)
					printf("The decoded word is: ");
				if (temp % 2 == 0) { // if its even

					char tempchar = (temp - 32);
					printf("%c", tempchar);
				}
				else {
					char tempchar = temp;
					printf("%c", tempchar);
				}
				break;
			}
			else
				break;
		}
		else {
			int leftDigit = encodedNums / n;
			int middleDigit = (encodedNums / (n / 10)) - (leftDigit * 10);
			int rightDigit = (encodedNums / (n / 100)) - (leftDigit * 100) - (middleDigit * 10);
			int checking = leftDigit * 10 + middleDigit;
			if (checking == 79 || checking == 89 || checking == 99) { // if its a,b,c
				counter++;
				if (counter == 1)
					printf("The decoded word is: ");
				temp = middleDigit * 10 + leftDigit;
				if (temp % 2 == 0) {
					char tempchar = (temp - 32);
					printf("%c", tempchar);
				}
				else {
					char tempchar = temp;
					printf("%c", tempchar);
				}
				encodedNums = encodedNums % (n / 10);
				n = n / 100;
			}
			else { // if its anything other then a,b,c
				temp = (rightDigit * 100) + (middleDigit * 10) + leftDigit;
				if (temp >= 100 && temp <= 122) {
					counter++;
					if (counter == 1)
						printf("The decoded word is: ");
					if (temp % 2 == 0) {
						char tempchar = (temp - 32);
						printf("%c", tempchar);
					}
					else {
						char tempchar = temp;
						printf("%c", tempchar);
					}
					
				}
				encodedNums = encodedNums % (n / 100);
				n = n / 1000;
			}
		}
	}
	if (counter == 0) // if there were no letters
		printf("\nThere is nothing there :(");
	else // if there were letters
		printf("\nDone and even had time for coffee :)");
	return 0;
}