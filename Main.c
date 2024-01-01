#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <windows.h>

//Global Variables
#define ROWS 17
#define COLUMNS 27
int currentPlayer; // 1 for GONDOR, 2 for MORDOR
int gameStatus = 0;
int turnNumber = 0;

//Structs
struct Building
{
	char name[20];
	int cost;
	int health;
};

// Struct for representing units
struct Unit
{
	char name[20];
	int movecost;
	int attackPower;
	int health;
	int cost;
};
struct Mines
{
	char name[20];
	int cost;
	int health;
	int coinsperturn;
};

// Struct for representing player resources
struct CastarCoins
{
	int gon;
	int mor;
};

typedef struct SpecialChar
{
	char ability[20];
	int abPower;
	int abCost;
	int uPT; //units per team
	union 
	{
		struct Unit character;
	};
};


// Function declarations
void initializeBoard(char board[ROWS][COLUMNS]);
void printBoard(char board[ROWS][COLUMNS]);
void insertContent(char board[ROWS][COLUMNS], int row, int col, char content);
void TakeTurn(char board[ROWS][COLUMNS], struct Building gondorBuildings[], struct Building mordorBuildings[], struct Unit gondorUnits[], struct Unit mordorUnits[], struct Mines gondorMines[], struct Mines mordorMines[], struct CastarCoins *coins, struct SpecialChar Gandalf[]);
void StartGame(char board[ROWS][COLUMNS], struct Building gondorBuildings[], struct Building mordorBuildings[], struct Unit gondorUnits[], struct Unit mordorUnits[], struct Mines gondorMines[], struct Mines mordorMines[], struct CastarCoins *coins, struct SpecialChar Gandalf[]);
void MainMenu(char board[ROWS][COLUMNS], struct Building gondorBuildings[], struct Building mordorBuildings[], struct Unit gondorUnits[], struct Unit mordorUnits[], struct Mines gondorMines[], struct Mines mordorMines[], struct CastarCoins *coins, struct SpecialChar Gandalf[]);
int CheckWin(struct Building gondorBuildings[], struct Building mordorBuildings[]);
void PlaceUnit(char board[ROWS][COLUMNS], struct Unit gondorUnits[], struct Unit mordorUnits[], struct CastarCoins *coins);
void PlaceUnitHelper(char board[ROWS][COLUMNS], struct Unit *unitArray);
void PlaceBuilding(char board[ROWS][COLUMNS], struct Building mordorBuildings[], struct Building gondorBuildings[], struct Mines gondorMines[], struct Mines mordorMines[], struct CastarCoins *coins);
void PlaceBuildingHelper(char board[ROWS][COLUMNS], struct Building *building);
void PlaceHero(char board[ROWS][COLUMNS], struct SpecialChar *hero, struct CastarCoins *coins);
void PlaceHeroHelper(char board[ROWS][COLUMNS], struct SpecialChar *hero);
void SelectSides(char board[ROWS][COLUMNS], struct Building gondorBuildings[], struct Building mordorBuildings[], struct Unit gondorUnits[], struct Unit mordorUnits[], struct Mines gondorMines[], struct Mines mordorMines[], struct CastarCoins *coins, struct SpecialChar Gandalf[]);
void SelectGameMode(char board[ROWS][COLUMNS], struct Building gondorBuildings[], struct Building mordorBuildings[], struct Unit gondorUnits[], struct Unit mordorUnits[], struct Mines gondorMines[], struct Mines mordorMines[], struct CastarCoins *coins, struct SpecialChar Gandalf[]);





// Run Program
int main()
{
	struct Building gondorBuildings[] = {
		{"GGGG", 30, 100},
		{"RR", 25, 70},
		{"LL", 25, 70},
		{"GF", 30, 70}};

	struct Building mordorBuildings[] = {
		{"MMMM", 30, 100},
		{"II", 25, 70},
		{"MK", 25, 70},
		{"DF", 30, 70}};

	struct Unit gondorUnits[] = {
		{"G", 2, 5, 30, 20},
		{"SK", 1, 7, 40, 10},
		{"T", 3, 10, 20, 30}

	};

	struct Unit mordorUnits[] = {
		{"OW", 2, 5, 30, 20},
		{"W", 1, 7, 40, 10},
		{"ST", 3, 10, 20, 30}};

	struct Mines gondorMines[] = {
		{"SS", 20, 50, 5}};

	struct Mines mordorMines[] = {
		{"EE", 20, 50, 5}};



	struct SpecialChar Gandalf[] =
	{
		{
			"Heal", //Ability Name
			5, //Ability Power (how much he can heal)
			50, //Cost to use the ability
			1,
			"GA", //The hero's name 'Gandalf'
			15, //Move cost
			5, //His attack power
			40,//His health
			200 //How much he costs (expensive as its a special character)
		}
	};

	struct CastarCoins startingCoin;
	startingCoin.gon = 100;
	startingCoin.mor = 100;

	char gameBoard[ROWS][COLUMNS];
	initializeBoard(gameBoard);
	MainMenu(gameBoard, gondorBuildings, mordorBuildings, gondorUnits, mordorUnits, gondorMines, mordorMines, &startingCoin, Gandalf);
	return 0;
}



void SelectGameMode(char board[ROWS][COLUMNS], struct Building gondorBuildings[], struct Building mordorBuildings[], struct Unit gondorUnits[], struct Unit mordorUnits[], struct Mines gondorMines[], struct Mines mordorMines[], struct CastarCoins *coins, struct SpecialChar Gandalf[])
{
	int choice;
	printf("Choose one option below: \n");
	printf("1- Play vs Computer\n");
	printf("2- Play vs Friend\n");
	do
	{
		scanf("%d", &choice);
		if (choice == 1)
		{
			// Handle computer logic 
		}
		else if (choice == 2)
		{
			SelectSides(board, gondorBuildings, mordorBuildings, gondorUnits, mordorUnits, gondorMines, mordorMines, coins, Gandalf);
		}
	} while (choice != 1 && choice != 2);
}




void SelectSides(char board[ROWS][COLUMNS], struct Building gondorBuildings[], struct Building mordorBuildings[], struct Unit gondorUnits[], struct Unit mordorUnits[], struct Mines gondorMines[], struct Mines mordorMines[], struct CastarCoins *coins, struct SpecialChar Gandalf[])
{

	int choice;
	printf("Player 1 - Choose Your Side\n");
	printf("1-GONDOR\n");
	printf("2-MORDOR\n");
	// Loops until the player chooses a valid option
	do
	{
		scanf("%d", &choice);
		if (choice == 1)
		{
			printf("You have chosen the GONDOR side!!\n\n");
			currentPlayer = 1;
			StartGame(board, gondorBuildings, mordorBuildings, gondorUnits, mordorUnits, gondorMines, mordorMines, coins, Gandalf);
		}
		else if (choice == 2)
		{
			printf("You have chosen MORDOR side!!\n\n");
			currentPlayer = 2;
			StartGame(board, gondorBuildings, mordorBuildings, gondorUnits, mordorUnits, gondorMines, mordorMines, coins, Gandalf);
		}
		else
		{
			printf("Invalid option, choose again\n");
		}
		
	} while (choice != 1 && choice != 2);
}




void StartGame(char board[ROWS][COLUMNS], struct Building gondorBuildings[], struct Building mordorBuildings[], struct Unit gondorUnits[], struct Unit mordorUnits[], struct Mines gondorMines[], struct Mines mordorMines[], struct CastarCoins *coins, struct SpecialChar Gandalf[])
{
	while (gameStatus == 0)
	{
		// Display the board
		printBoard(board);

		// Take a turn for the current player
		TakeTurn(board, gondorBuildings, mordorBuildings, gondorUnits, mordorUnits, gondorMines, mordorMines, coins, Gandalf);

		// Check for a win or a draw
		gameStatus = CheckWin(gondorBuildings, mordorBuildings);

		// Switch to the next player for the next turn
		currentPlayer = (currentPlayer == 1) ? 2 : 1;
	}
}




int CheckWin(struct Building gondorBuildings[], struct Building mordorBuildings[])
{

	if (gondorBuildings[0].health <= 0)
	{
		// MORDOR wins
		return 2;
	}

	if (mordorBuildings[0].health <= 0)
	{
		// GONDOR wins
		return 1;
	}

	// No winner yet
	return 0;
}




// Main menu
void MainMenu(char board[ROWS][COLUMNS], struct Building gondorBuildings[], struct Building mordorBuildings[], struct Unit gondorUnits[], struct Unit mordorUnits[], struct Mines gondorMines[], struct Mines mordorMines[], struct CastarCoins *coins, struct SpecialChar Gandalf[])
{

	int choice;

	system("cls");
	printf("------- GAME MENU ---------\n");
	printf("------- 1-Start Game ------\n");
	printf("------- 2-Load Game -------\n");
	printf("------- 3-Options ---------\n");
	printf("------- 4-Exit ------------\n");
	printf("Enter your choice: ");
	scanf("%d", &choice);

	switch (choice)
	{
	case 1:
		system("cls");
		SelectGameMode(board, gondorBuildings, mordorBuildings, gondorUnits, mordorUnits, gondorMines, mordorMines, coins, Gandalf);
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




void TakeTurn(char board[ROWS][COLUMNS], struct Building gondorBuildings[], struct Building mordorBuildings[], struct Unit gondorUnits[], struct Unit mordorUnits[], struct Mines gondorMines[], struct Mines mordorMines[], struct CastarCoins *coins, struct SpecialChar Gandalf[])
{
	int choice;
	int endTurn = 0;
	int selectedRow;
	char selectedColumn;


	while (endTurn != 1)
	{
		// Display Castar Coins information
		printf("\n\n\n %s side turn - Castar Coins: Gondor %d, Mordor %d\n", (currentPlayer == 1) ? "Gondor" : "Mordor", coins->gon, coins->mor);

		// Allow the player to choose between placing a building or a unit
		printf("Choose an action:\n");
		printf("1- Place Building\n");
		printf("2- Place Unit\n");
		printf("3 - Place hero\n");
		printf("4- End Turn\n");
		printf("5- Show Board\n");
		
		scanf("%d", &choice);

		switch (choice)
		{
		case 1:
			PlaceBuilding(board, gondorBuildings, mordorBuildings, gondorMines, mordorMines, coins);
			break;
		case 2:
			PlaceUnit(board, gondorUnits, mordorUnits, coins);
			break;
		case 3:
			PlaceHero(board, Gandalf, coins);
			break;	
			
		case 4:
			printf("Turn Ended. Player receives 15 coins.\n");
			endTurn = 1;

			// Reward the player with 15 coins
			if (currentPlayer == 1)
				coins->gon += 15;
			else
				coins->mor += 15;
			break;



		case 5:
			printBoard(board);
			break;

		
		default:
			printf("Invalid choice. Turn skipped.\n");
		}
	}
}




void PlaceBuilding(char board[ROWS][COLUMNS], struct Building gondorBuildings[], struct Building mordorBuildings[], struct Mines gondorMines[], struct Mines mordorMines[], struct CastarCoins *coins)
{
	int choice;

	// Determine the building array based on the current player
	struct Building *buildingArray = (currentPlayer == 1) ? gondorBuildings : mordorBuildings;

	// Logic to choose a building
	printf("Choose building:\n");
	for (int i = 0; i < 4; ++i)
	{
		printf("%d - %s\n", i + 1, buildingArray[i].name);
	}

	scanf("%d", &choice);

	// Handle the user's choice
	if (choice >= 1 && choice <= 5)
	{
		// Set the chosen building
		struct Building *building = &buildingArray[choice - 1];
		if (currentPlayer == 1)
		{
			coins->gon -= building->cost;
		}
		else
		{
			coins->mor -= building->cost;
		}
		PlaceBuildingHelper(board, building);
	}

	else
	{
		printf("Invalid choice. Building not placed.\n");
	}
}




void PlaceUnit(char board[ROWS][COLUMNS], struct Unit gondorUnits[], struct Unit mordorUnits[], struct CastarCoins *coins)
{
	struct Unit *unitArray = (currentPlayer == 1) ? gondorUnits : mordorUnits;
	int choice;

	// Logic to choose a building
	printf("Choose Unit:\n");
	for (int i = 0; i < 3; ++i)
	{
		printf("%d - %s\n", i + 1, unitArray[i].name);
	}

	scanf("%d", &choice);

	// Handle the user's choice
	if (choice >= 1 && choice <= 5)
	{
		// Set the chosen building
		struct Unit *units = &unitArray[choice - 1];
		if (currentPlayer == 1)
		{
			coins->gon -= units->cost;
		}
		else
		{
			coins->mor -= units->cost;
		}
		PlaceBuildingHelper(board, units);
	}
	else
	{
		printf("Invalid choice. Unit not placed.\n");
	}
}

void PlaceHero(char board[ROWS][COLUMNS], struct SpecialChar *hero, struct CastarCoins *coins)
{
    
    int choice;

    // Logic to choose a building
    printf("Choose Hero:\n");

    printf("1-Gandalf\n");
    scanf("%d", &choice);

    if (choice == 1)
    {
            if (currentPlayer == 1)
                coins->gon -= hero->character.cost;
			
			PlaceHeroHelper(board, hero);
    }
}

void PlaceHeroHelper(char board[ROWS][COLUMNS], struct SpecialChar *hero)
{
	int row = 0;
	int success = 0;
	do
	{

		printf("Enter the row (1-%d): ", ROWS - 1);
		while (scanf("%d", &row) != 1 || row < 1 || row >= ROWS)
		{
			printf("Invalid input. Please enter a valid row.\n");
			printf("Enter the row (1-%d): ", ROWS - 1);
			// Clear the input buffer in case of non-integer input
			while (getchar() != '\n');
		}

		// Convert column input to uppercase
		char column;
		printf("Enter the column (A-Z): ");
		scanf(" %c", &column);
		column = column + 1;
		column = toupper(column);

		// Check if the selected cell is empty
		if (column >= 'A' && column <= 'Z' && board[row][column - 'A'] == ' ')
		{
			// Check if placing the building exceeds the maximum column index (16)
			int heroLength = strlen(hero->character.name);
			if (heroLength + (column - 'A') > 16)
			{
				printf("Not enough space in the row for the entire building. Please choose another location.\n");
				Sleep(1000);
			}
			else
			{
				// Place the building
				for (int i = 0; hero->character.name[i] != '\0'; i++)
				{
					board[row][column - 'A' + i] = hero->character.name[i];
				}
				printf("Building placed successfully!\n");
				success = 1;
			}
		}
		else
		{
			printf("Invalid column or selected cell is occupied. Please choose a valid and empty cell.\n");
		}

	} while (success != 1);
}

void PlaceUnitHelper(char board[ROWS][COLUMNS], struct Unit *units)
{
	int row;
	int success = 0;

	do
	{
		// Get input for unit placement
		printf("Enter the row (1-%d) and column (A-Z) separated by a space: ", ROWS);
		scanf("%d", &row);

		// Convert column input to uppercase
		char column;
		printf("Enter the column (A-Z): ");
		scanf(" %c", &column);
		column = toupper(column);

		// Check if the selected cell is empty
		if (row >= 1 && row < ROWS && column >= 'A' && column <= 'Z' && board[row][column - 'A'] == ' ')
		{
			// Place the unit
			board[row][column - 'A'] = units->name[0]; // Place the first letter of the unit's name
			printf("Unit placed successfully!\n");
			success = 1;
		}
		else
		{
			printf("Invalid row, column, or selected cell is occupied. Please choose a valid and empty cell.\n");
		}
	} while (success != 1);
}





void PlaceBuildingHelper(char board[ROWS][COLUMNS], struct Building *building)
{
	int row = 0;
	int success = 0;

	do
	{

		printf("Enter the row (1-%d): ", ROWS - 1);
		while (scanf("%d", &row) != 1 || row < 1 || row >= ROWS)
		{
			printf("Invalid input. Please enter a valid row.\n");
			printf("Enter the row (1-%d): ", ROWS - 1);
			// Clear the input buffer in case of non-integer input
			while (getchar() != '\n')
				;
		}

		// Convert column input to uppercase
		char column;
		printf("Enter the column (A-Z): ");
		scanf(" %c", &column);
		column = column + 1;
		column = toupper(column);

		// Check if the selected cell is empty
		if (column >= 'A' && column <= 'Z' && board[row][column - 'A'] == ' ')
		{
			// Check if placing the building exceeds the maximum column index (16)
			int buildingLength = strlen(building->name);
			if (buildingLength + (column - 'A') > 16)
			{
				printf("Not enough space in the row for the entire building. Please choose another location.\n");
				Sleep(1000);
			}
			else
			{
				// Place the building
				for (int i = 0; building->name[i] != '\0'; i++)
				{
					board[row][column - 'A' + i] = building->name[i];
				}
				printf("Building placed successfully!\n");
				success = 1;
			}
		}
		else
		{
			printf("Invalid column or selected cell is occupied. Please choose a valid and empty cell.\n");
		}

	} while (success != 1);
}




// Initialize the game board with empty spaces
void initializeBoard(char board[ROWS][COLUMNS])
{
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLUMNS; j++)
		{
			board[i][j] = ' ';
		}
	}
}




// Print the game board
void printBoard(char board[ROWS][COLUMNS])
{

	system("cls");
	printf("\n\n   ");
	for (int j = 1; j < COLUMNS; j++)
	{
		printf("%3c ", 'A' + j - 1);
	}
	printf("\n");

	// Print game board
	for (int i = 1; i < ROWS; i++)
	{
		// Print row label
		printf("%2d ", i);

		// Print row content
		for (int j = 1; j < COLUMNS; j++)
		{
			printf("| %c ", board[i][j]);
		}

		printf("|\n");

		// Print row separator
		printf("  ");
		for (int j = 1; j < COLUMNS; j++)
		{
			printf("+---");
		}
		printf("+\n");
	}
}



// Insert content into a specific grid square
void insertContent(char board[ROWS][COLUMNS], int row, int col, char content)
{
	board[row][col] = content;
}
