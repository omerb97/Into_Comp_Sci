/*-------------------------------------------------------------------------
  Include files:
--------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>



/*=========================================================================
  Constants and definitions:
==========================================================================*/

/* put your #defines and typedefs here*/
#define MATRIX_SIZE 25



/*-------------------------------------------------------------------------
  The main program. (describe what your program does here)
 -------------------------------------------------------------------------*/

void print_enter_matrix_size();
void print_enter_first_matrix();
void print_enter_second_matrix();
void print_invalid_input();
void print_enter_required_operation();
void print_number(int number);
void print_enter();
int matrixBuilder1(int firstMatrix[MATRIX_SIZE][MATRIX_SIZE], int N, int num);// builds the first matrix
int matrixBuilder2(int secondMatrix[MATRIX_SIZE][MATRIX_SIZE], int N, int num); // builds the second matrix
void operationSelector(int firstMatrix[MATRIX_SIZE][MATRIX_SIZE], int secondMatrix[MATRIX_SIZE][MATRIX_SIZE], int N);
//routes the program to the correct operation
void addingOp(int firstMatrix[MATRIX_SIZE][MATRIX_SIZE], int secondMatrix[MATRIX_SIZE][MATRIX_SIZE], int N); // adds the matrices
void multiplyOp(int firstMatrix[MATRIX_SIZE][MATRIX_SIZE], int secondMatrix[MATRIX_SIZE][MATRIX_SIZE], int N);// multiplys the matrices

int main()
{
	int N = 0, firstMatrix[MATRIX_SIZE][MATRIX_SIZE] = { {0} }, secondMatrix[MATRIX_SIZE][MATRIX_SIZE], num=0;
	print_enter_matrix_size();
	scanf("%d", &N); // enters matrix size
	int reValue1 = matrixBuilder1(firstMatrix, N, num); // returns value bigger the 0 if invalid
	if (reValue1 != 0) {
		print_invalid_input();
		return 1;
	}
	int reValue2 = matrixBuilder2(secondMatrix, N, num); // returns value bigger the 0 if invalid
	if (reValue2 != 0) {
		print_invalid_input();
		return 1;
	}
	operationSelector(firstMatrix, secondMatrix, N);
	return reValue1+reValue2;
}

int matrixBuilder1(int firstMatrix[MATRIX_SIZE][MATRIX_SIZE], int N, int num) { // builds the first matrix
	print_enter_first_matrix();
	for (int i = 0; i < N; i++) { // inserts into the first matrix
		for (int j = 0; j < N; j++) {
			if (scanf("%d", &num) == 1)
				firstMatrix[i][j] = num;
			else {
				return 1;
			}
		}
	}
	return 0;
}

int matrixBuilder2(int secondMatrix[MATRIX_SIZE][MATRIX_SIZE],int N,int num) { // builds the second matrix

	print_enter_second_matrix();
	for (int i = 0; i < N; i++) { // inserts into the second matrix
		for (int j = 0; j < N; j++) {
			if (scanf("%d", &num) == 1)
				secondMatrix[i][j] = num;
			else {
				return 1;
			}
		}
	}
	return 0;
}


void operationSelector(int firstMatrix[MATRIX_SIZE][MATRIX_SIZE], int secondMatrix[MATRIX_SIZE][MATRIX_SIZE], int N) {
	//the fuction routes the program to the correct operation
	print_enter_required_operation();
	char operation;
	scanf(" %c", &operation);
	if (operation == '+') // if selects the addition operation
		addingOp(firstMatrix, secondMatrix,N);
	else if (operation == '*') // if selects the multipication operation
		multiplyOp(firstMatrix, secondMatrix, N);
	else // if does an invalid command 
		print_invalid_input(); 
		
}

void addingOp(int firstMatrix[MATRIX_SIZE][MATRIX_SIZE], int secondMatrix[MATRIX_SIZE][MATRIX_SIZE], int N) {
	//adds the two matrices together
	int addition = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			addition = firstMatrix[i][j] + secondMatrix[i][j];
			print_number(addition);
		}
		print_enter();
	}
}

void multiplyOp (int firstMatrix[MATRIX_SIZE][MATRIX_SIZE], int secondMatrix[MATRIX_SIZE][MATRIX_SIZE], int N)
//multiplies the matrices
{
	int digitSum=0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			for (int h = 0; h < N; h++) { // all the i line * all the j row 
				digitSum += firstMatrix[i][h] * secondMatrix[h][j];
			}
			print_number(digitSum);
			digitSum = 0;
		}
		print_enter();
	}
}

// below are all printing commands provided
void print_enter_matrix_size() {
	printf("Please enter the matrix size:\n");
}

void print_enter_first_matrix() {
	printf("Please enter the first matrix:\n");
}

void print_enter_second_matrix() {
	printf("Please enter the second matrix:\n");
}

void print_invalid_input() {
	printf("Invalid input.");
}

void print_enter_required_operation() {
	printf("Please enter the required operation:\n");
}

void print_number(int number) {
	printf("%d ", number);
}

void print_enter() {
	printf("\n");
}