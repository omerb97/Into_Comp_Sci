/*-------------------------------------------------------------------------
  Include files:
--------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>



/*=========================================================================
  Constants and definitions:
==========================================================================*/

/* put your #defines and typedefs here*/
#define PLATOON_SIZE 10



/*-------------------------------------------------------------------------
  The main program. (describe what your program does here)
 -------------------------------------------------------------------------*/

void print_warriors_details();
void print_army_size(int size);
void print_biggest_platoon_and_size(int index, int size);
void print_active_platoons_and_avg(int size, double avg);
void print_show_army();
void print_number(int num);
void print_enter();
void print_star();
void print_space();
void CalculateBiggest(int armyArray[PLATOON_SIZE]); // Calculates the biggest platoon	
void CalculateAvg(int armyArray[PLATOON_SIZE]); // Calculates the average
void showArmyHelper(int armyArray[PLATOON_SIZE], int armyCount); // Helper function for doing the army show



int main()
{
	print_warriors_details();
	int armyArray[PLATOON_SIZE] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };//build platoon
	int soldierID, IDsum = 0, counter = 0;
	scanf("%d", &soldierID);
	while (soldierID > 99 && soldierID < 1000){
		counter++;
		IDsum = (soldierID / 100 + ((soldierID % 100) / 10) + soldierID % 100) % 10; // calculates which platoon 
		armyArray[IDsum]++; //inserts into platoon
		scanf("%d", &soldierID);
	}
	switch (soldierID) { // last soldier ID is the command so check which command it is
		case 1: print_army_size(counter); break;
		case 2: CalculateBiggest(armyArray); break;
		case 3: CalculateAvg(armyArray); break;
		case 4: showArmyHelper(armyArray, counter); break;
	}
	return 0;
}

void CalculateBiggest(int armyArray[PLATOON_SIZE]){ // calculate biggest platoon
	int maxSize = 0;
	int maxPlatoon = 10;
	for (int i = 0; i < PLATOON_SIZE; i++) {
		if (armyArray[i] >= maxSize) {
			maxPlatoon = i;
			maxSize = armyArray[i];
		}
			
	}
	print_biggest_platoon_and_size(maxPlatoon, maxSize);

}

void CalculateAvg(int armyArray[PLATOON_SIZE]) { // calculates platoon avg
	int notEmpty = 0, sumcount=0;
	for (int i = 0; i < PLATOON_SIZE; i++) {
		if (armyArray[i] != 0) {
			notEmpty++;
			sumcount += armyArray[i];
		}
	}
	double avg = (double)sumcount / (double)notEmpty; // avg of none empty
	print_active_platoons_and_avg(notEmpty, avg);
}
void showArmyHelper(int armyArray[PLATOON_SIZE], int armyCount) { //does the army show
	print_show_army();
	while (armyCount > 0) {
		print_enter();
		for (int i = 0; i < PLATOON_SIZE; i++) {
			if (armyArray[i] > 0) { // if there exists a soldier, put a star
				print_star();
				armyCount--;
				armyArray[i]--;
			}
			else {
				print_space(); // if not, put a space
			}
		}
		
	}
}

//below all printing commands

void print_warriors_details() {
	printf("Enter warriors id and demand at the end:\n\n");
}

void print_army_size(int size) {
	printf("The army size is: %d\n", size);
}

void print_biggest_platoon_and_size(int index, int size) {
	printf("The biggest platoon index is: %d and its size is: %d\n", index, size);
}

void print_active_platoons_and_avg(int size, double avg) {
	printf("There are %d active platoons \n\nThe avg size of a platoon is: %.2f\n", size, avg);
}

void print_show_army() { // prints show aremy and all the platoon numbers
	printf("Show army!\n\n");
	for (int i = 0; i < PLATOON_SIZE; i++) {
		print_number(i);
	}
	
}

void print_number(int num) {
	printf("%d", num);
}

void print_enter() {
	printf("\n");
}

void print_star() {
	printf("*");
}

void print_space() {
	printf(" ");
}