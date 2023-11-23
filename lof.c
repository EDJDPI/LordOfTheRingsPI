#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include "lof.h"
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
				}
				else if (choice2 == 2)
				{
					printf("You have chosen MORDOR side!!\n\n STARTING GAME.....");
					
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
