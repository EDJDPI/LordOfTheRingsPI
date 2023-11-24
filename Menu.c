#define _CRT_SECURE_NO_WARNINGS
#define ROWS 17
#define COLUMNS 26
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>


//Start game selection



void StartGame() {
	int choice1, choice2;
	printf("Choose one option below: \n");
	printf("1-Single Player Mode\n");
	printf("2- 2 Player Game Mode\n");
	do {
		scanf("%d", &choice1);
		if (choice1 == 1)
		{
			
		}
		else if (choice1 == 2)
		{
			//Player choose side
			printf("CHOOSE YOUR SIDE:\n");
			printf("1-GONDOR/RIVENDELL\n");
			printf("2-MORDOR\n");
			//Loops it until player chooses a valid option
			do {
				scanf("%d", &choice2);
				if (choice2 == 1)
				{
					printf("You have chosen the GONDOR/RIVENDELL side!!\n\n STARTING GAME.....");
					coiso();
				}
				else if (choice2 == 2)
				{
					printf("You have chosen MORDOR side!!\n\n STARTING GAME.....");
					coiso();
				}
				else
				{
					printf("Invalid option, choose again\n");
				}
			} while (1);
		
		}
	} while (1);
}

	
int options() {
	printf("ola");
	}
//Main menu
int MainMenu() {
	int choice;
	system("cls");
	printf("------GAME MENU------\n");
	printf("------1-Start Game;------\n");
	printf("------2-Load Game;------\n");
	printf("------3-Options;------\n");
	printf("------4-Exit;------\n");
	printf("Enter your choice: ");
	scanf("%d", &choice);

	switch (choice) {
	case 1:
		system("cls");
		;
		StartGame();
		break;
	case 2:
		system("cls");
		printf("Loading game...");
		break;
	case 3:
		system("cls");
		printf("Menu Options : ");
		break;
	case 4:
		system("cls");
		printf("Exiting the game!!");
		break;
	}
}

// Declarations
void initializeBoard(char board[ROWS][COLUMNS]);
void printBoard(char board[ROWS][COLUMNS]);
void insertContent(char board[ROWS][COLUMNS], int row, int col, char content);

// Run Program
int main() {
	char gameBoard[ROWS][COLUMNS];
	initializeBoard(gameBoard); // Initialize the game grid

	while (1) {
		system("cls"); // Use "clear" on Unix-based systems
		printBoard(gameBoard); // Display the current board

		// Example: Insert 'G' at row 3, column 5
		insertContent(gameBoard, 3, 5, 'G');

		// Add any additional game logic or user input handling here

		// Introduce a delay to control the refresh rate (adjust as needed)
		// For example, on Windows, you can use Sleep(1000) for 1 second
		Sleep(1000);
	}

	return 0;
}

// Functions

// Initialize the game board with empty spaces
void initializeBoard(char board[ROWS][COLUMNS]) {
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLUMNS; j++) {
			board[i][j] = ' ';
		}
	}
}

// Print the game board
void printBoard(char board[ROWS][COLUMNS]) {
	// Print column labels
	printf("   ");
	for (int j = 1; j < COLUMNS; j++) {
		printf("%3c ", 'A' + j - 1);
	}
	printf("\n");

	// Print game board
	for (int i = 1; i < ROWS; i++) {
		// Print row label
		printf("%2d ", i);

		// Print row content
		for (int j = 1; j < COLUMNS; j++) {
			printf("| %c ", board[i][j]);
		}

		printf("|\n");

		// Print row separator
		printf("   ");
		for (int j = 1; j < COLUMNS; j++) {
			printf("+---");
		}
		printf("+\n");
	}
}

// Insert content into a specific grid square
void insertContent(char board[ROWS][COLUMNS], int row, int col, char content) {
	board[row][col] = content;
}