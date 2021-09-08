/*-------------------------------------------------------------------------
  Include files:
--------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>



/*=========================================================================
  Constants and definitions:
==========================================================================*/

/* put your #defines and typedefs here*/



/*-------------------------------------------------------------------------
  The main program. (describe what your program does here)
 -------------------------------------------------------------------------*/

int print_enter_enemy_name(); // gets name intput and does the calculations
int print_dragonA_sent(); // prints if dragon A has been sent
int print_dragonB_sent(); // prints if dragon B has been sent
int print_dragonC_sent(); // prints if dragon C has been sent
int print_no_dragon_sent(); // prints if no dragon has been sent

int main()
{
	int result = print_enter_enemy_name();
	int resultMeaning=0;
	resultMeaning=(result / 10 == 1) && print_dragonC_sent();
	resultMeaning = (result / 5 == 1) && print_dragonB_sent();
	resultMeaning = (result / 2 == 1) && print_dragonA_sent();
	resultMeaning = (result == 0) && print_no_dragon_sent();
	return resultMeaning-resultMeaning;
}

int print_enter_enemy_name() {
	char name='A';
	int counter = 0, sum = 0, prevName = 0, sFlag = 0, prevFlag = 0; // set up variables for name length, sum, previous char, and flags
	printf("Please enter enemy name:\n");
	scanf("%c", &name);
	do
	{
		sFlag += (name == 's'); // sees if it has any s in the name
		prevFlag += (prevName > (int)(name)); // sees if its a rising series
		counter++; //length check
		sum += (int)(name);
		prevName = (int)(name); // sets it up for the next check
		scanf("%c", &name);
	} while (name != '!');
	// Each dragon has been assiged a 'number' that is bigger then the sum of the other two.
	// Dragon C is 10, B is 5, C is 5 so like that the fuctions return a number and i can see if its bigger then 10 then its C
	// if its bigger then 2 but smaller then 10 its B and if its 2 its A. zero is none
	return ((10 * (counter < 6 && sFlag == 0)) + (5 * (prevFlag == 0)) + 2 * (counter > 4 || sum % 5 != 0));
	
}

//below all printing functions

int print_dragonA_sent() {
	return printf("\nKhalisi sent dragonA into the battle!!!\n");
}

int print_dragonB_sent() {
	return printf("\nKhalisi sent dragonB into the battle!!!\n");
}

int print_dragonC_sent() {
	return printf("\nKhalisi sent dragonC into the battle!!!\n");
}

int print_no_dragon_sent() {
	return printf("\nNO Dragon has been sent into the battle!!!\n");
}