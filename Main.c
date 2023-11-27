#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

#define ROWS 17
#define COLUMNS 27

int currentPlayer;  // 1 for GONDOR, 2 for MORDOR
int gameStatus = 0;
int turnNumber = 0;


struct Building {
	char name[20];
	int cost;
	int health;
};

// Struct for representing units
struct Unit {
	char name[20];
	int cost;
	int attackPower;
	int health;
};

// Struct for representing player resources
struct CastarCoins {
	int gon;
	int mor;
};
#include <stdio.h>
#include <stdlib.h>

// Function declarations
void PlaceBuilding(char board[ROWS][COLUMNS], struct Building* building);
void initializeBoard(char board[ROWS][COLUMNS]);
void printBoard(char board[ROWS][COLUMNS]);
void insertContent(char board[ROWS][COLUMNS], int row, int col, char content);
void TakeTurn(char board[ROWS][COLUMNS], struct Building gondorBuildings[], struct Building mordorBuildings[], struct Unit gondorUnits[], struct Unit mordorUnits[], struct CastarCoins* coins);
void StartGame(char board[ROWS][COLUMNS], struct Building gondorBuildings[], struct Building mordorBuildings[], struct Unit gondorUnits[], struct Unit mordorUnits[], struct CastarCoins* coins);
void MainMenu(char board[ROWS][COLUMNS], struct Building gondorBuildings[], struct Building mordorBuildings[], struct Unit gondorUnits[], struct Unit mordorUnits[], struct CastarCoins* coins);
int CheckWin(struct Building gondorBuildings[], struct Building mordorBuildings[]);
void PlaceUnit(char board[ROWS][COLUMNS], struct Unit* unit);

// Run Program
int main()
{
	struct Building gondorBuildings[] = {
		{"GGGG", 30, 100},
		{"SS", 20, 50},
		{"RR", 25, 70},
		{"LL", 25, 70},
		{"GF", 30, 70}
	};

	struct Building mordorBuildings[] = {
		{"MMMM", 30, 100},
		{"EE", 20, 50 },
		{"II", 25, 70},
		{"MK", 25, 70},
		{"DF", 30, 70}
	};

	struct Unit gondorUnits[] = {
		{"G", 2, 5, 30},
		{"SK", 1, 7, 40},
		{"T", 3, 10, 20}
		
	};

	struct Unit mordorUnits[] = {
		{"OW", 2, 5, 30},
		{"W", 1, 7, 40},
		{"ST", 3, 10, 20}
	};

	struct CastarCoins startingCoin;
	startingCoin.gon = 100;
	startingCoin.mor = 100;

	char gameBoard[ROWS][COLUMNS];
	initializeBoard(gameBoard);
	MainMenu(gameBoard, gondorBuildings, mordorBuildings, gondorUnits, mordorUnits, &startingCoin);
	return 0;
}

void SelectSides(char board[ROWS][COLUMNS], struct Building gondorBuildings[], struct Building mordorBuildings[], struct Unit gondorUnits[], struct Unit mordorUnits[], struct CastarCoins* coins) {

	int choice1, choice2;
	printf("Choose one option below: \n");
	printf("1- Play vs Computer\n");
	printf("2- Play vs Friend\n");
	do {
		scanf("%d", &choice1);
		if (choice1 == 1) {
			// Handle computer logic (if needed)
		}
		else if (choice1 == 2) {
			// Player chooses side
			printf("Player 1 - Choose Your Side\n");
			printf("1-GONDOR\n");
			printf("2-MORDOR\n");
			// Loops until the player chooses a valid option
			do {
				scanf("%d", &choice2);
				if (choice2 == 1) {
					printf("You have chosen the GONDOR side!!\n\n");
					currentPlayer = 1;
					// Pass the necessary data to StartGame
					StartGame(board, gondorBuildings, mordorBuildings, gondorUnits, mordorUnits, coins);

				}
				else if (choice2 == 2) {
					printf("You have chosen MORDOR side!!\n\n");
					currentPlayer = 2;
					// Pass the necessary data to StartGame
					StartGame(board, gondorBuildings, mordorBuildings, gondorUnits, mordorUnits, coins);
				}
				else {
					printf("Invalid option, choose again\n");
				}
			} while (choice2 != 1 && choice2 != 2);
		}
	} while (choice1 != 1);
}



void StartGame(char board[ROWS][COLUMNS], struct Building gondorBuildings[], struct Building mordorBuildings[], struct Unit gondorUnits[], struct Unit mordorUnits[], struct CastarCoins* coins)
{
	while (gameStatus == 0) {
		// Display the board
		printBoard(board);

		// Take a turn for the current player
		TakeTurn(board, gondorBuildings, mordorBuildings, gondorUnits, mordorUnits, coins);

		// Check for a win or a draw
		gameStatus = CheckWin(gondorBuildings, mordorBuildings);

		// Switch to the next player for the next turn
		currentPlayer = (currentPlayer == 1) ? 2 : 1;
	}
}



int CheckWin(struct Building gondorBuildings[], struct Building mordorBuildings[]) {
	// Check the win conditions based on the state of buildings
	// ...

	// Example:
	if (gondorBuildings[0].health <= 0) {
		// MORDOR wins
		return 2;
	}

	if (mordorBuildings[0].health <= 0) {
		// GONDOR wins
		return 1;
	}

	// No winner yet
	return 0;
}


//Main menu
void MainMenu(char board[ROWS][COLUMNS], struct Building gondorBuildings[], struct Building mordorBuildings[], struct Unit gondorUnits[], struct Unit mordorUnits[], struct CastarCoins* coins) {

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
		SelectSides(board, gondorBuildings, mordorBuildings, gondorUnits, mordorUnits, coins);
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


// Implement the `TakeTurn` function
void TakeTurn(char board[ROWS][COLUMNS], struct Building gondorBuildings[], struct Building mordorBuildings[], struct Unit gondorUnits[], struct Unit mordorUnits[], struct CastarCoins* coins)
{
	int choice;

	// Display Castar Coins information
	printf("Player %d - Castar Coins: Gondor %d, Mordor %d\n", currentPlayer, coins->gon, coins->mor);

	// Allow the player to choose between placing a building or a unit
	printf("Choose an action:\n");
	printf("1- Place Building\n");
	printf("2- Place Unit\n");
	scanf("%d", &choice);

	switch (choice) {
	case 1:
		PlaceBuilding(board, (currentPlayer == 1) ? &gondorBuildings[0] : &mordorBuildings[0]);
		break;
	case 2:
		PlaceUnit(board, (currentPlayer == 1) ? &gondorUnits[0] : &mordorUnits[0]);
		break;
	default:
		printf("Invalid choice. Turn skipped.\n");
	}
}

void PlaceBuilding(char board[ROWS][COLUMNS], struct Building* building) {
	int row, col;

	// Get input for building placement
	printf("Enter the row (1-%d) and column (A-Z) separated by a space: ", ROWS - 1);
	scanf("%d", &row);



	// Convert column input to uppercase
	char column;
	printf("Enter the column (A-Z): ");
	scanf(" %c", &column);
	column = column + 1;
	column = toupper(column);

	// Validate column input


	// Check if the selected cell is empty
	if (board[row][column - 'A'] == ' ') {
		// Place the building
		for (int i = 0; building->name[i] != '\0'; i++) {
			// Place each character of the building to the right of the selected cell
			board[row][column - 'A' + i] = building->name[i];
		}
		printf("Building placed successfully!\n");
	}
	else {
		printf("Selected cell is occupied. Please choose an empty cell.\n");
	}
}

void PlaceUnit(char board[ROWS][COLUMNS], struct Unit* unit) {
	int row, col;

	// Get input for unit placement
	printf("Enter the row (1-%d) and column (A-Z) separated by a space: ", ROWS);
	scanf("%d", &row);

	// Convert column input to uppercase
	char column;
	printf("Enter the column (A-Z): ");
	scanf(" %c", &column);
	column = toupper(column);

	// Check if the selected cell is empty
	if (board[row][column - 'A'] == ' ') {
		// Place the unit
		board[row][column - 'A'] = unit->name[0];  // Place the first letter of the unit's name
		printf("Unit placed successfully!\n");
	}
	else {
		printf("Selected cell is occupied. Please choose an empty cell.\n");
	}
}

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
		printf("  ");
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

