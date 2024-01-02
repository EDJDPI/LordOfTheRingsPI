#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <string.h>
#include <windows.h>

//Global Variables
#define ROWS 17
#define COLUMNS 27
int currentPlayer; // 1 for GONDOR, 2 for MORDOR
int gameStatus = 0;
int turnNumber = 0;
int heroGon = 0;
int heroMon = 0;

//Structs
struct Building
{
	char name[20];
	int cost;
	int health;
	int buildID;
	int row;
	int col;
};

// Struct for representing units
struct Unit
{
	char name[20];
	int movecost;
	int attackPower;
	int health;
	int cost;
	int UnitID;
	int row;
	int col;
};
struct Mines
{
	char name[20];
	int cost;
	int health;
	int coinsperturn;
	int mineID;
	int row;
	int col;
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
}Heros;

struct PlacedEntity {
    int row;
    char col;
    int health;
    char type[20];  // Assuming a maximum length for the entity type
    int side;       // 1 for Gondor, 2 for Mordor
};

// Function declarations
void initializeBoard(char board[ROWS][COLUMNS]);
void printBoard(char board[ROWS][COLUMNS]);
void insertContent(char board[ROWS][COLUMNS], int row, int col, char content);
void TakeTurn(char board[ROWS][COLUMNS], struct Building gondorBuildings[], struct Building mordorBuildings[], struct Unit gondorUnits[], struct Unit mordorUnits[], struct Mines gondorMines[], struct Mines mordorMines[], struct CastarCoins *coins, Heros Gandalf[], struct PlacedEntity **placedHeroes, int *placedHeroCount);
void StartGame(char board[ROWS][COLUMNS], struct Building gondorBuildings[], struct Building mordorBuildings[], struct Unit gondorUnits[], struct Unit mordorUnits[], struct Mines gondorMines[], struct Mines mordorMines[], struct CastarCoins *coins, Heros Gandalf[], struct PlacedEntity **placedHeroes, int *placedHeroCount);
void MainMenu(char board[ROWS][COLUMNS], struct Building gondorBuildings[], struct Building mordorBuildings[], struct Unit gondorUnits[], struct Unit mordorUnits[], struct Mines gondorMines[], struct Mines mordorMines[], struct CastarCoins *coins, Heros Gandalf[], struct PlacedEntity **placedHeroes, int *placedHeroCount);
int CheckWin(struct Building gondorBuildings[], struct Building mordorBuildings[]);
void PlaceUnit(char board[ROWS][COLUMNS], struct Unit gondorUnits[], struct Unit mordorUnits[], struct CastarCoins *coins,struct PlacedEntity **placedHeroes, int *placedHeroCount);
void PlaceUnitHelper(char board[ROWS][COLUMNS], struct Unit *unitArray,struct PlacedEntity **placedHeroes, int *placedHeroCount);
void PlaceBuilding(char board[ROWS][COLUMNS], struct Building mordorBuildings[], struct Building gondorBuildings[], struct Mines gondorMines[], struct Mines mordorMines[], struct CastarCoins *coins,struct PlacedEntity **placedHeroes, int *placedHeroCount);
void PlaceBuildingHelper(char board[ROWS][COLUMNS], struct Building *building, struct PlacedEntity **placedHeroes, int *placedHeroCount);
void PlaceHero(char board[ROWS][COLUMNS], Heros *hero, struct PlacedEntity **placedHeroes, int *placedHeroCount, struct CastarCoins *coins);
void PlaceHeroHelper(char board[ROWS][COLUMNS], Heros *hero, struct PlacedEntity **placedHeroes, int *placedHeroCount, struct CastarCoins *coins);
void SelectSides(char board[ROWS][COLUMNS], struct Building gondorBuildings[], struct Building mordorBuildings[], struct Unit gondorUnits[], struct Unit mordorUnits[], struct Mines gondorMines[], struct Mines mordorMines[], struct CastarCoins *coins, Heros Gandalf[], struct PlacedEntity **placedHeroes, int *placedHeroCount);
void SelectGameMode(char board[ROWS][COLUMNS], struct Building gondorBuildings[], struct Building mordorBuildings[], struct Unit gondorUnits[], struct Unit mordorUnits[], struct Mines gondorMines[], struct Mines mordorMines[], struct CastarCoins *coins, Heros Gandalf[], struct PlacedEntity **placedHeroes, int *placedHeroCount);
void moverPeca(char board[ROWS][COLUMNS], struct PlacedEntity *placedHeroes, int placedHeroCount, Heros Gandalf[], struct CastarCoins *coins);


void debugPrintEntities(FILE *file, struct PlacedEntity *entities, int entityCount) {
    fprintf(file, "Debugging Placed Entities:\n");

    for (int i = 0; i < entityCount; ++i) {
        fprintf(file, "Entity %d:\n", i + 1);
        fprintf(file, "Type: %s\n", entities[i].type);
        fprintf(file, "Side: %d\n", entities[i].side);
        fprintf(file, "Row: %d\n", entities[i].row);
        fprintf(file, "Column: %c\n", entities[i].col);
        fprintf(file, "Health: %d\n", entities[i].health);
        fprintf(file, "------------------------\n");
    }

    fprintf(file, "End of Placed Entities Debug\n");
}



// Run Program
int main()
{

	   FILE *debugFile = fopen("debug_output.txt", "w");
    if (debugFile == NULL) {
        fprintf(stderr, "Error opening debug file.\n");
        exit(EXIT_FAILURE);
    }

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



	Heros Gandalf[]  =
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


	struct PlacedEntity *placedHeroes = NULL;
	int placedHeroCount = 0;

	struct CastarCoins startingCoin;
	startingCoin.gon = 100;
	startingCoin.mor = 100;

	char gameBoard[ROWS][COLUMNS];
	initializeBoard(gameBoard);
	MainMenu(gameBoard, gondorBuildings, mordorBuildings, gondorUnits, mordorUnits, gondorMines, mordorMines, &startingCoin, Gandalf, &placedHeroes, &placedHeroCount);


	debugPrintEntities(debugFile, placedHeroes, placedHeroCount);

    // Close the debug file
    fclose(debugFile);

	free(placedHeroes);
	return 0;
}



void SelectGameMode(char board[ROWS][COLUMNS], struct Building gondorBuildings[], struct Building mordorBuildings[], struct Unit gondorUnits[], struct Unit mordorUnits[], struct Mines gondorMines[], struct Mines mordorMines[], struct CastarCoins *coins, Heros Gandalf[], struct PlacedEntity **placedHeroes, int *placedHeroCount)
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
			SelectSides(board, gondorBuildings, mordorBuildings, gondorUnits, mordorUnits, gondorMines, mordorMines, coins, Gandalf, placedHeroes, placedHeroCount);
		}
	} while (choice != 1 && choice != 2);
}


void moverPeca(char board[ROWS][COLUMNS], struct PlacedEntity *placedHeroes, int placedHeroCount, Heros Gandalf[], struct CastarCoins *coins)
{
    char fromC, toC;
    int fromL, toL;

    // as coordenadas da peça a ser movida
    printf("Digite as coordenadas da peca a ser movida (linha/coluna): ");
    scanf("%d %c", &fromL, &fromC);

    // Validate coordinates
    if (fromL < 1 || fromL >= ROWS || fromC < 'A' || fromC > 'Z')
    {
        printf("Coordenadas invalidas. Tente novamente.\n");
        return;
    }

    fromC = toupper(fromC); // Convert to uppercase

    // Find the entity at the specified coordinates
    int entityIndex = -1;
    for (int i = 0; i < placedHeroCount; i++)
    {
        if (placedHeroes[i].row == fromL && placedHeroes[i].col == fromC)
        {
            entityIndex = i;
            break;
        }
    }

    if (entityIndex == -1)
    {
        printf("Nenhuma peca encontrada nas coordenadas especificadas.\n");
        return;
    }

    // as coordenadas para onde a peça será movida
    printf("Digite as coordenadas para onde a peca sera movida (linha/coluna): ");
    scanf("%d %c", &toL, &toC);

    // Validate coordinates
    if (toL < 1 || toL >= ROWS || toC < 'A' || toC > 'Z')
    {
        printf("Coordenadas invalidas. Tente novamente.\n");
        return;
    }

    toC = toupper(toC); // Convert to uppercase

    // Check if the target cell is empty
    if (board[toL][toC - 'A'] != ' ')
    {
        printf("A posicao de destino ja esta ocupada. Escolha outra posicao.\n");
        return;
    }

    // Update the board
// Update the board
for (int i = 0; i < strlen(placedHeroes[entityIndex].type); i++) {
    board[toL][toC - 'A' + i] = placedHeroes[entityIndex].type[i];
}

// Clear the cells of the previous position
for (int i = 0; i < strlen(placedHeroes[entityIndex].type); i++) {
    board[fromL][fromC - 'A' + i] = ' ';
}

    // Update the PlacedEntity
    placedHeroes[entityIndex].row = toL;
    placedHeroes[entityIndex].col = toC;

    printf("Peca movida com sucesso!\n");
}


void SelectSides(char board[ROWS][COLUMNS], struct Building gondorBuildings[], struct Building mordorBuildings[], struct Unit gondorUnits[], struct Unit mordorUnits[], struct Mines gondorMines[], struct Mines mordorMines[], struct CastarCoins *coins, Heros Gandalf[], struct PlacedEntity **placedHeroes, int *placedHeroCount)
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
			StartGame(board, gondorBuildings, mordorBuildings, gondorUnits, mordorUnits, gondorMines, mordorMines, coins, Gandalf, placedHeroes, placedHeroCount);
		}
		else if (choice == 2)
		{
			printf("You have chosen MORDOR side!!\n\n");
			currentPlayer = 2;
			StartGame(board, gondorBuildings, mordorBuildings, gondorUnits, mordorUnits, gondorMines, mordorMines, coins, Gandalf, placedHeroes, placedHeroCount);
		}
		else
		{
			printf("Invalid option, choose again\n");
		}
		
	} while (choice != 1 && choice != 2);
}




void StartGame(char board[ROWS][COLUMNS], struct Building gondorBuildings[], struct Building mordorBuildings[], struct Unit gondorUnits[], struct Unit mordorUnits[], struct Mines gondorMines[], struct Mines mordorMines[], struct CastarCoins *coins, Heros Gandalf[], struct PlacedEntity **placedHeroes, int *placedHeroCount)
{
	while (gameStatus == 0)
	{
		// Display the board
		printBoard(board);

		// Take a turn for the current player
		TakeTurn(board, gondorBuildings, mordorBuildings, gondorUnits, mordorUnits, gondorMines, mordorMines, coins, Gandalf, placedHeroes, placedHeroCount);

		// Check for a win or a draw
		gameStatus = 1;

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
void MainMenu(char board[ROWS][COLUMNS], struct Building gondorBuildings[], struct Building mordorBuildings[], struct Unit gondorUnits[], struct Unit mordorUnits[], struct Mines gondorMines[], struct Mines mordorMines[], struct CastarCoins *coins, Heros Gandalf[], struct PlacedEntity **placedHeroes, int *placedHeroCount)
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
		SelectGameMode(board, gondorBuildings, mordorBuildings, gondorUnits, mordorUnits, gondorMines, mordorMines, coins, Gandalf, placedHeroes, placedHeroCount);
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




void TakeTurn(char board[ROWS][COLUMNS], struct Building gondorBuildings[], struct Building mordorBuildings[], struct Unit gondorUnits[], struct Unit mordorUnits[], struct Mines gondorMines[], struct Mines mordorMines[], struct CastarCoins *coins, Heros Gandalf[], struct PlacedEntity **placedHeroes, int *placedHeroCount)
{
    int choice;
    int endTurn = 0;
    int selectedRow;
    char selectedColumn;

    while (endTurn != 1)
    {
        // Display Castar Coins information
        printf("\n\n\n %s side turn - Castar Coins: Gondor %d, Mordor %d\n", (currentPlayer == 1) ? "Gondor" : "Mordor", coins->gon, coins->mor);

        // Allow the player to choose between placing a building, unit, hero, moving a piece, or ending the turn
        printf("Choose an action:\n");
        printf("1- Place Building\n");
        printf("2- Place Unit\n");
        printf("3- Place Hero\n");
        printf("4- Move Piece\n");
        printf("5- End Turn\n");
        printf("6- Show Board\n");

        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            PlaceBuilding(board, gondorBuildings, mordorBuildings, gondorMines, mordorMines, coins, placedHeroes, placedHeroCount);
            break;
        case 2:
            PlaceUnit(board, gondorUnits, mordorUnits, coins, placedHeroes, placedHeroCount);
            break;
        case 3:
            PlaceHero(board, Gandalf, placedHeroes, placedHeroCount, coins);
            break;
        case 4:
            moverPeca(board, *placedHeroes, *placedHeroCount, Gandalf, coins);
            break;
        case 5:
            printf("Turn Ended. Player receives 15 coins.\n");
            endTurn = 1;

            // Reward the player with 15 coins
            if (currentPlayer == 1)
                coins->gon += 15;
            else
                coins->mor += 15;

            break;
        case 6:
            printBoard(board);
            break;
        default:
            printf("Invalid choice. Turn skipped.\n");
        }
    }
}





void PlaceBuilding(char board[ROWS][COLUMNS], struct Building gondorBuildings[], struct Building mordorBuildings[], struct Mines gondorMines[], struct Mines mordorMines[], struct CastarCoins *coins,struct PlacedEntity **placedHeroes, int *placedHeroCount)
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
		PlaceBuildingHelper(board, building,placedHeroes, placedHeroCount);
	}

	else
	{
		printf("Invalid choice. Building not placed.\n");
	}
}




void PlaceUnit(char board[ROWS][COLUMNS], struct Unit gondorUnits[], struct Unit mordorUnits[], struct CastarCoins *coins,struct PlacedEntity **placedHeroes, int *placedHeroCount)
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
		PlaceUnitHelper(board, units, placedHeroes, placedHeroCount);
	}
	else
	{
		printf("Invalid choice. Unit not placed.\n");
	}
}

void PlaceHero(char board[ROWS][COLUMNS], Heros *hero, struct PlacedEntity **placedHeroes, int *placedHeroCount, struct CastarCoins *coins)
{
    int choice;

    // Logic to choose a hero
    printf("Choose Hero:\n");

    printf("1-Gandalf\n");
    scanf("%d", &choice);

    if (choice == 1)
    {
        if ((currentPlayer == 1 && heroGon < hero->uPT) || (currentPlayer == 2 && heroMon < hero->uPT))
        {
            if (currentPlayer == 1)
            {
                coins->gon -= hero->character.cost;
                heroGon++;
            }
            else
            {
                coins->mor -= hero->character.cost;
                heroMon++;
            }
            PlaceHeroHelper(board, hero, placedHeroes, placedHeroCount, coins);
        }
        else
        {
            printf("You already have a hero placed.\n");
        }
    }
}



void PlaceHeroHelper(char board[ROWS][COLUMNS], Heros *hero, struct PlacedEntity **placedHeroes, int *placedHeroCount, struct CastarCoins *coins)
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

        char column;
        printf("Enter the column (A-Z): ");
        scanf(" %c", &column);
        column = toupper(column);

        printf("DEBUG: Hero name: %s\n", hero->character.name);

        if (column >= 'A' && column <= 'Z' && board[row][column - 'A'] == ' ')
        {
            printf("DEBUG: Column is valid, cell is empty.\n");

            int heroLength = strlen(hero->character.name);
            if (heroLength + (column - 'A') >= COLUMNS)
            {
                printf("DEBUG: Not enough space in the row for the entire hero. Please choose another location.\n");
                Sleep(1000);
            }
            else
            {
                // Place the hero
                for (int i = 0; hero->character.name[i] != '\0'; i++)
                {
                    board[row][column - 'A' + i + 1] = hero->character.name[i];
                }

                *placedHeroCount += 1;
                *placedHeroes = realloc(*placedHeroes, *placedHeroCount * sizeof(struct PlacedEntity));

                // Initialize the new PlacedEntity
                struct PlacedEntity newHero;
                newHero.row = row;
                newHero.col = column;
                newHero.health = 100;
                strcpy(newHero.type, hero->character.name);
                newHero.side = currentPlayer;

                // Store the new PlacedEntity in the array
                (*placedHeroes)[*placedHeroCount - 1] = newHero;

                printf("DEBUG: Hero placed successfully!\n");
                success = 1;
            }
        }
        else
        {
            printf("DEBUG: Invalid column or selected cell is occupied. Please choose a valid and empty cell.\n");
        }

    } while (success != 1);
}

void PlaceUnitHelper(char board[ROWS][COLUMNS], struct Unit *units, struct PlacedEntity **placedHeroes, int *placedHeroCount )
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
			int unitLength = strlen(units->name);
			if (unitLength + (column - 'A') > 16)
			{
				printf("Not enough space in the row for the entire building. Please choose another location.\n");
				Sleep(1000);
			}
			else
			{
				// Place the building
				for (int i = 0; units->name[i] != '\0'; i++)
				{
					board[row][column - 'A' + i] = units->name[i];
				}
				*placedHeroCount += 1;
                *placedHeroes = realloc(*placedHeroes, *placedHeroCount * sizeof(struct PlacedEntity));

                // Initialize the new PlacedEntity
                struct PlacedEntity newHero;
                newHero.row = row;
                newHero.col = column;
                newHero.health = 100;
                strcpy(newHero.type, units->name);
                newHero.side = currentPlayer;

                // Store the new PlacedEntity in the array
                (*placedHeroes)[*placedHeroCount - 1] = newHero;

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





void PlaceBuildingHelper(char board[ROWS][COLUMNS], struct Building *building, struct PlacedEntity **placedHeroes, int *placedHeroCount)
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
					board[row][column - 'A' + i + 1] = building->name[i];
				}
				*placedHeroCount += 1;
                *placedHeroes = realloc(*placedHeroes, *placedHeroCount * sizeof(struct PlacedEntity));

                // Initialize the new PlacedEntity
                struct PlacedEntity newHero;
                newHero.row = row;
                newHero.col = column;
                newHero.health = 100;
                strcpy(newHero.type, building->name);
                newHero.side = currentPlayer;

                // Store the new PlacedEntity in the array
                (*placedHeroes)[*placedHeroCount - 1] = newHero;
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

    printf("\n\n");

    // Print column labels
    printf("   ");
    for (int j = 1; j < COLUMNS; j++)
    {
        printf(" %2c ", 'A' + j - 1);
    }
    printf("\n");

    // Print top border above the first row
    printf("   ");
    printf("%c", 218);
    for (int j = 1; j < COLUMNS; j++)
    {
        if (j < COLUMNS - 1)
            printf("%c%c%c%c", 196, 196, 196, 194);
        else
            printf("%c%c%c%c", 196, 196, 196, 191);
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
            printf("%c %c ", 179, board[i][j]);
        }

        printf("%c\n", 179);

        // Print row separator
        if (i < ROWS - 1)
        {
            printf("   ");
            printf("%c", 195);
            for (int j = 1; j < COLUMNS; j++)
            {
                if (j < COLUMNS - 1)
                    printf("%c%c%c%c", 196, 196, 196, 197);
                else
                    printf("%c%c%c%c", 196, 196, 196, 180);
            }
            printf("\n");
        }
    }

    // Print bottom border below the last row
    printf("   ");
    printf("%c", 192);
    for (int j = 1; j < COLUMNS; j++)
    {
        if (j < COLUMNS - 1)
            printf("%c%c%c%c", 196, 196, 196, 193);
        else
            printf("%c%c%c%c", 196, 196, 196, 217);
    }
    printf("\n");
}


// Insert content into a specific grid square
void insertContent(char board[ROWS][COLUMNS], int row, int col, char content)
{
	board[row][col] = content;
}