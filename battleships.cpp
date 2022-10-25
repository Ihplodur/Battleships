#include <stdio.h>
#include <time.h> //needed for random numbers
#include <stdlib.h> //needed random numbers
#include <Windows.h> //needed for Sleep
#define MAX 10
#define MASS 5
#include "game.h"


int main() {
	printf("\t\t\x1b[32m      Battleships\x1b[0m\n\n");
	int shipMass = MASS;
	int shipMass2 = MASS;
	struct ship ships[MASS];
	struct ship enemyShips[MASS];
	int player = 1;
	//define arrays for the board
	//invisible board
	int b[MAX][MAX] = { 0 };

	//visible boards
	int c[MAX][MAX] = { 0 };
	int d[MAX][MAX] = { 0 };
	defineShips(ships, enemyShips);
	Sleep(2000); //the programm resumes after (milliseconds) 
				//so the user can read everything before the programm prints out the next part
	placeShips(ships, b, c, d);
	Sleep(3000);
	//main loop
	while (shipMass>0 && shipMass2>0)
	{
		printf("\n\t\tPlayer %i", player);
		board(player, b, c, d);
		int minus = turn(ships, enemyShips, player, b, c, d);
		Sleep(3000);
		switch (player)
		{
		case 1:
			printf("\n\t\tPlayer %i", player);
			shipMass -= minus;
			printf(" has to sink %i ships!\n", shipMass);
			break;
		case 2:
			printf("\n\t\tPlayer %i", player);
			shipMass2 -= minus;
			printf(" has to sink %i ships!\n", shipMass2);
			break;
		}
		
		if (shipMass==0)
		{
			printf("\n\t\tPlayer %i", player);
			board(player, b, c, d);
			printf("\n\x1b[32m\tYou win!!\x1b[0m");
			Sleep(3000);
			break;
		}
		else if (shipMass2 == 0)
		{
			printf("\n\t\tPlayer %i", player);
			board(player, b, c, d);
			printf("\n\x1b[31m\tYou loose!!\x1b[0m");
			Sleep(3000);
			break;
		}
		//idle between player 1 and 2
		switch (player)
		{
		case 1:
			player = 2;
			break;
		case 2:
			player = 1;
			break;
		}
	}
	return 0;
}