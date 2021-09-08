/*-------------------------------------------------------------------------
	Include files:
-------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdbool.h>

/*-------------------------------------------------------------------------
	Constants and definitions:
-------------------------------------------------------------------------*/
#define N 11
#define HISTORY_ARRAY_SIZE 2
#define XHISTORY 0
#define YHISTORY 1

/*-------------------------------------------------------------------------
	Function declaration
-------------------------------------------------------------------------*/
void print_welcome();
void print_enter_board_size();
void print_board(char board[N][N], int n);
void print_player_turn(int player_index);
void print_error();
void print_winner(int player_index);
void print_tie();
void game_intruduction(char gameBoard[N][N], int gameHistory[N*N][HISTORY_ARRAY_SIZE]);
void main_game_function(char gameBoard[N][N], int boardSize, int gameHistory[N*N][HISTORY_ARRAY_SIZE]);
bool normal_move(int xMove, int yMove, char gameBoard[N][N], int boardSize, int gameHistory[N*N][HISTORY_ARRAY_SIZE], int playerindex);
int player_number(int playerindex);
int check_win(char gameBoard[N][N], int boardSize, int playerindex);
int legal_move(int xMove, int yMove, char gameBoard[N][N], int boardSize);
void make_move(int xMove, int yMove, char gameBoard[N][N], int playerindex, int boardSize, int gameHistory[N*N][HISTORY_ARRAY_SIZE]);
bool negative_move(int xMove, int gameHistory[N*N][HISTORY_ARRAY_SIZE], char gameBoard[N][N], int boardSize);
int legal_undo(int xMove, int gameHistory[N*N][HISTORY_ARRAY_SIZE]);
void go_undo(int xMove, int gameHistory[N*N][HISTORY_ARRAY_SIZE], char gameBoard[N][N], int boardSize);
void insert_to_catalog(int gameHistory[N*N][HISTORY_ARRAY_SIZE], int xMove, int yMove);
int horizontal_win_check(char gameBoard[N][N], int boardSize);
int vertical_win_check(char gameBoard[N][N], int boardSize);
int primary_diagonal_win_check(char gameBoard[N][N], int boardSize);
int secondary_diagonal_win_check(char gameBoard[N][N], int boardSize);
int check_tie(char gameBoard[N][N], int boardSize);

/*-------------------------------------------------------------------------
	Implementation
-------------------------------------------------------------------------*/

//Initiates the game, sets up all the arrays
//7 lines
int main() {
	char gameBoard[N][N] = { {0} }; 
	int gameHistory[N*N][HISTORY_ARRAY_SIZE] = { {20} };
	for (int i = 0; i < N*N; i++) {
		gameHistory[i][XHISTORY] = 20;
		gameHistory[i][1] = 20;
	}
	game_intruduction(gameBoard, gameHistory);
	return 0;
}

//Starts the game by doing all the functions that happen only at the beginning of the game
//9 lines
void game_intruduction(char gameBoard[N][N], int gameHistory[N*N][HISTORY_ARRAY_SIZE]) {
	print_welcome();
	print_enter_board_size();
	int boardSize;
	scanf("%d", &boardSize);
	for (int i = 0; i < boardSize; i++) {
		for (int j = 0; j < boardSize; j++) {
			gameBoard[i][j] = '_';
		}
	}
	print_board(gameBoard, boardSize);
	main_game_function(gameBoard, boardSize, gameHistory);
}

//Continues the game to the next turn so long as no one has won or no tie
//10 lines
void main_game_function(char gameBoard[N][N], int boardSize, int gameHistory[N*N][HISTORY_ARRAY_SIZE]) {
	int playerindex = 0, xMove, yMove;
	bool lastMoveLegal = true;
	do {
		if (lastMoveLegal == true) {
			print_player_turn(player_number((++playerindex)));
		}
		scanf("%d", &xMove);
		if (xMove < 0) { // if its undo
			lastMoveLegal = negative_move(xMove, gameHistory, gameBoard, boardSize);
		}
		else{
			scanf("%d", &yMove);
			lastMoveLegal = normal_move(xMove, yMove, gameBoard, boardSize, gameHistory, playerindex);
		}
	}while (check_win(gameBoard, boardSize, player_number(playerindex)) == 0); //continues if no one one or a tie
	
}

//if the move is a normal, make move sends it to the relevant functions to be preformed
//7 lines
bool normal_move(int xMove, int yMove, char gameBoard[N][N], int boardSize, int gameHistory[N*N][HISTORY_ARRAY_SIZE], int playerindex) {
	xMove -= 1;
	yMove -= 1;
	if (legal_move(xMove, yMove, gameBoard, boardSize) == 1) {
		make_move(xMove, yMove, gameBoard, playerindex, boardSize, gameHistory);
		return true;
	}
	else {
		print_error();
		return false;
	}
}

//Checks whether a normal move is legal or not
//5 lines
int legal_move(int xMove,int yMove,char gameBoard[N][N],int boardSize) {
	if (xMove >= boardSize || yMove >= boardSize)
		return 0;
	if (gameBoard[xMove][yMove] != '_')//the space isnt taken
		return 0;

	return 1;
}

//if a normal legal move, puts the piece on the board, sends it to be put in the game history, and requests the board to be printed
//5 lines
void make_move(int xMove, int yMove, char gameBoard[N][N], int playerindex, int boardSize, int gameHistory[N*N][HISTORY_ARRAY_SIZE]) {
	if (playerindex % 2 == 1)
		gameBoard[xMove][yMove] = 'X';
	else
		gameBoard[xMove][yMove] = 'O';
	insert_to_catalog(gameHistory, xMove, yMove);
	print_board(gameBoard, boardSize);

}

//if its a legal undo, sends it to the relevant functions to be preformed
//5 lines
bool negative_move(int xMove, int gameHistory[N*N][HISTORY_ARRAY_SIZE], char gameBoard[N][N], int boardSize) {
	if (legal_undo(xMove, gameHistory) == 1) {
		go_undo(xMove, gameHistory, gameBoard, boardSize);
		return true;
	}
	else {
		print_error();
		return false;
	}
}

//function checks if its a legal undo
//10 lines
int legal_undo(int xMove, int gameHistory[N*N][HISTORY_ARRAY_SIZE]) {
	xMove = xMove * -1;
	if (xMove % 2 == 0)
		return 0;
	int counter = 0;
	for (int i = 0; i < N*N; i++) { // checks that the undo isn't more number of moves played
		if (gameHistory[i][XHISTORY] != 20)
			counter++;
	}
	if ((xMove) > counter)
		return 0;
	return 1;
}

//if a legal undo, it deletes the relevant pieces from the board and from the game history and sends to print board again
//12 lines
void go_undo(int xMove, int gameHistory[N*N][HISTORY_ARRAY_SIZE], char gameBoard[N][N],int boardSize) {
	int rowCounter = 0;
	while (gameHistory[rowCounter][XHISTORY] != 20) { // finds the last non "empty" cell
		rowCounter++;
	}
	rowCounter -= 1;
	xMove *= -1;
	for (int i = 0; i < xMove; i++) {
		int xPosition = gameHistory[rowCounter][XHISTORY], yPosition = gameHistory[rowCounter][YHISTORY]; // gets the x,y postions of moves
		gameBoard[xPosition][yPosition] = '_'; 
		gameHistory[rowCounter][XHISTORY] = 20;//puts it back to 20
		gameHistory[rowCounter][YHISTORY] = 20;
		rowCounter--;
	}
	print_board(gameBoard, boardSize);
}

//inserts the current move into the game history array
//5 lines 
void insert_to_catalog(int gameHistory[N*N][HISTORY_ARRAY_SIZE], int xMove, int yMove) {
	int rowCounter = 0;
	while (gameHistory[rowCounter][XHISTORY] != 20 && rowCounter<N*N) {
		rowCounter++;
	}
	gameHistory[rowCounter][XHISTORY] = xMove;
	gameHistory[rowCounter][YHISTORY] = yMove;

}

//calls on all the winning conditions functions to see if any situation is a winning one and send back if it is
//12 lines
int check_win(char gameBoard[N][N], int boardSize, int playerindex) {
	if (horizontal_win_check(gameBoard, boardSize) == 1 || vertical_win_check(gameBoard, boardSize) == 1) {
		playerindex = player_number(playerindex + 1);
		print_winner(playerindex);
		return 1;
	}

	if (primary_diagonal_win_check(gameBoard, boardSize) == 1 || secondary_diagonal_win_check(gameBoard, boardSize) == 1){
		playerindex = player_number(playerindex + 1);
		print_winner(playerindex);
		return 1;
	}
	if (check_tie(gameBoard, boardSize) == 1) {
		print_tie();
		return 1;
	}
	return 0;
}

//checks if there are any in a row horizontally
//9 lines
int horizontal_win_check(char gameBoard[N][N], int boardSize) {
	int horizontalCounter = 1;
	for (int i = 0; i < boardSize; i++) {
		for (int j = 1; j < boardSize; j++) {
			if (gameBoard[i][j - 1] == gameBoard[i][j] && gameBoard[i][j - 1] != '_')
				horizontalCounter++;
		}
		if (horizontalCounter == boardSize)
			return 1;
		else
			horizontalCounter = 1;
	}
	return 0;
}

//checks if there are any in a row vertically
//9 lines
int vertical_win_check(char gameBoard[N][N], int boardSize) {
	int verticalCounter = 1;
	for (int i = 0; i < boardSize; i++) {
		for (int j = 1; j < boardSize; j++) {
			if (gameBoard[j-1][i] == gameBoard[j][i] && gameBoard[j-1][i] != '_')
				verticalCounter++;
		}
		if (verticalCounter == boardSize)
			return 1;
		else
			verticalCounter = 1;
	}
	return 0;
}

//checks if there are any in a row on the primary diagonal
//7 lines
int primary_diagonal_win_check(char gameBoard[N][N], int boardSize) {
	int diagnalCounter = 1;
	for (int i = 1; i < boardSize; i++) {
			if (gameBoard[i - 1][i - 1] == gameBoard[i][i] && gameBoard[i-1][i-1] != '_')
				diagnalCounter++;
	}
	if (diagnalCounter == boardSize)
		return 1;
	return 0;
}

//checks if there are any in a row on the secondary diagonal
//12 lines
int secondary_diagonal_win_check(char gameBoard[N][N], int boardSize) {
	int diagonalCounter = 1;
	char temp = gameBoard[0][boardSize-1];
	if (temp != '_')
	{
		for (int i = 1; i < boardSize; i++) {
			for (int j = 0; j < boardSize; j++) {
				if (i + j == boardSize-1)
				{
					if (gameBoard[i][j] == temp && gameBoard[i][j] != '_') {
						diagonalCounter++;
						temp = gameBoard[i][j];
					}
						
				}

			}

		}
	}
	if (diagonalCounter == boardSize)
		return 1;
	return 0;
}

//checks if the board is full and there is a tie
//8 lines
int check_tie(char gameBoard[N][N], int boardSize) {
	int fullCounter =0;
	for (int i = 0; i < boardSize; i++) {
		for (int j = 0; j < boardSize; j++) {
			if (gameBoard[i][j] == '_')
				fullCounter++;
		}
	}
	if (fullCounter == 0)
		return 1;
	return 0;
}

//returns the player turn number according to the player index
//3 lines
int player_number (int playerindex){
	if (playerindex % 2 == 0)
		return 2;
	return 1;
}

//print welcome message
//1 lines
void print_welcome()
{
	printf("*** Welcome to AVOIDANCE TIC-TAC-TOE game ***\n\n");
}

//print message to enter board size
//1 lines
void print_enter_board_size()
{
	printf("Please enter board size (1 to %d):\n", N);
}

//print the board
//7 lines
void print_board(char board[N][N], int n)
{
	printf("\nCurrent board:\n");
	for (int i = 0; i < n; i++)
	{
		printf("|");
		for (int j = 0; j < n; j++)
		{
			printf("%c|", board[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

//print a request for player with index "player_index" to move
//1 lines
void print_player_turn(int player_index)
{
	printf("\nPlayer ** %d **, enter next move:\n", player_index);
}

//print error message
//1 lines
void print_error()
{
	printf("Illegal move!!!, please try again:\n");
}

//print the winner
//1 lines
void print_winner(int player_index)
{
	printf("Player %d Wins! Hooray!\n", player_index);
}

//print message to announce there is a tie (no one wins)
//1 lines
void print_tie()
{
	printf("It's a tie!\n");
}