#ifndef game_h
#define game_h

//define struct ship
struct ship {
	int number;
	char name[20];
};

//data of each ship & printout
void defineShips(struct ship *l, struct ship* m)
{
	l[0] = m[0] = { 5, "Carrier" };
	l[1] = m[1] = { 4, "Batlleship" };
	l[2] = m[2] = { 3, "Destroyer" };
	l[3] = m[3] = { 3, "Submarine" };
	l[4] = m[4] = { 2, "Patrol Boat" };
	printf("\t\tNr. \tName \t Tiles\n");
	for (int i = 0; i < MASS; i++)
	{
		printf("\t\t%i %14s     %i\n", i+1, l[i].name, l[i].number);
	}
}

//creation and prinout of the game board
void board(int player, int b[MAX][MAX], int c[MAX][MAX], int d[MAX][MAX])
{
	// recurring parts of the board
	int	y = 0, x = 0;
	printf("\n\n |");
	for (x = 0; x < MAX; x++) {
		printf(" | %i", x);
	}
	printf(" | <-X\n ===========================================\n\n");

	for (y = 0; y < MAX; y++) {
		printf("%i|", y);
		for (x = 0; x < MAX; x++) {
			switch (player)
			{
				// Turn of the Human player
				// you see which tiles you hit
			case 1:
				switch (c[y][x])
				{
				case 0:
					printf(" | %i", c[y][x]);
					break;
				case 1:
					printf(" | \x1b[32m%i\x1b[0m", c[y][x]);
					break;
				case 2:
					printf(" | \x1b[32m%i\x1b[0m", c[y][x]);
					break;
				case 3:
					printf(" | \x1b[32m%i\x1b[0m", c[y][x]);
					break;
				case 4:
					printf(" | \x1b[32m%i\x1b[0m", c[y][x]);
					break;
				case 5:
					printf(" | \x1b[32m%i\x1b[0m", c[y][x]);
					break;
				case 6:
					printf(" | \x1b[96m%i\x1b[0m", c[y][x]);
					break;
				case 7:
					printf(" | \x1b[31m%i\x1b[0m", c[y][x]);
					break;
				}
				break;
				//Turn of the Computer player
				//you see where your ships are placed on the battlefield and wich tiles the enemy has hit
			case 2:
				switch (d[y][x])
				{
				case 0:
					printf(" | %i", d[y][x]);
					break;
				case 1:
					printf(" | \x1b[32m%i\x1b[0m", d[y][x]);
					break;
				case 2:
					printf(" | \x1b[32m%i\x1b[0m", d[y][x]);
					break;
				case 3:
					printf(" | \x1b[32m%i\x1b[0m", d[y][x]);
					break;
				case 4:
					printf(" | \x1b[32m%i\x1b[0m", d[y][x]);
					break;
				case 5:
					printf(" | \x1b[32m%i\x1b[0m", d[y][x]);
					break;
				case 6:
					printf(" | \x1b[96m%i\x1b[0m", d[y][x]);
					break;
				case 7:
					printf(" | \x1b[31m%i\x1b[0m", d[y][x]);
					break;
				}
				break;
			}
		}
		printf(" | \n\n");
	}
	printf("^\nY\n");
}

//turn of the players
int turn(struct ship* l, struct ship* m, int player, int b[MAX][MAX], int c[MAX][MAX], int d[MAX][MAX])
{
	//X- and Y-coordinates on the battlefield
	int	y = -1, x = -1;
	//checks if a ship is destroyed
	int destroyed = 0;
	//checks if you have choosen a valid target
	int test = 0;

	switch (player)
	{
		// Human players turn
		// input of coordinates
	case 1:
		while (test == 0)
		{
			while (x < 0 || x >= MAX)
			{
				printf("\nChoose a X-Coordinate between 0 and %i: ", MAX - 1);
				scanf_s("%i", &x);
			}
			while (y < 0 || y >= MAX)
			{
				printf("\nChoose a Y-Coordinate between 0 and %i: ", MAX - 1);
				scanf_s("%i", &y);
			}
			if (c[y][x] > MASS)
			{
				printf("\n\t\tYou already shot this tile.\n");
				y = -1, x = -1;
			}
			else if (b[y][x] == 0)
			{
				printf("\n\t\tMiss!!\n");
				b[y][x] = 6;
				c[y][x] = 6;
				test = 1;
			}
			else if (b[y][x] > 0 && b[y][x] < 6)
			{
				int r = (b[y][x] - 1);
				printf("\n\t\tHit!! %s", m[r].name);

				if (m[r].number == 1)
				{
					printf("\x1b[31m destroyed!!\x1b[0m\n");
					destroyed = 1;
					m[r].number--;
				}
				else
				{
					m[r].number--;
				}
				b[y][x] = 7;
				c[y][x] = 7;
				test = 1;
			}
		}
		break;

		//turn of the Computer player
	case 2:
		Sleep(3000);
		y = (rand() % MAX);
		x = (rand() % MAX);
		// with || d[y][x]==0 the computer hits at every shot
		while (d[y][x] >MASS) 
		{
			y = (rand() % MAX);
			x = (rand() % MAX);
		}
		if (d[y][x] == 0)
		{
			printf("\n\t\tMiss!!\n");
			d[y][x] = 6;
		}
		else
		{
			int r = (d[y][x] - 1);
			printf("\n\t\tHit!! %s", l[r].name);

			if (l[r].number == 1)
			{
				destroyed = 1;
				printf("\x1b[31m destroyed!!\x1b[0m\n");
				l[r].number--;
			}
			else
			{
				l[r].number--;
			}
			d[y][x] = 7;
		}
		break;
	}
	board(player, b, c, d);
	//Sleep(3000);
	return destroyed;
}

//placing of the ships on the board
void placeShips(struct ship* l, int b[MAX][MAX], int c[MAX][MAX], int d[MAX][MAX])
{
	srand((unsigned int)time(NULL));
	int direction = 0;
	int start_x = -1;
	int start_y = -1;
	int len = 0;
	int player = 2; //setting player to 2 to see where you have placed your ship on the board
	for (int i = 0; i < MASS; i++)
	{
		printf("\n\t\t   \x1b[32mPlace your %s\x1b[0m\n", l[i].name);
		//setting X- and Y-coordinates to invalid values for the while loops to work
		start_x = -1;
		start_y = -1;
		len = l[i].number;
		int controll = len;
		printf("\nDirection of your %s 0 = Horizontal, 1 = Vertical: ", l[i].name);
		scanf_s("%i", &direction);
		if (direction == 0)
		{
			while (controll > 0)
			{
				while (start_x<0 || start_x>MAX - len)
				{
					printf("\nX-coorinate of your %s between 0 and %i: ", l[i].name, MAX - len);
					scanf_s("%i", &start_x);
				}
				while (start_y < 0 || start_y >= MAX)
				{
					printf("\nY-coorinate of your %s between 0 and %i: ", l[i].name, MAX - 1);
					scanf_s("%i", &start_y);
				}
				for (int k = 0; k < len; k++)
				{
					if (d[start_y][start_x + k] == 0)
					{
						controll--;
					}
					else
					{
						controll = len;
						printf("\nOverlapping ships!\n");
						start_x = -1;
						start_y = -1;
						break;
					}
				}
			}
		}
		else
		{
			while (controll > 0)
			{
				while (start_x < 0 || start_x >= MAX)
				{
					printf("\nX-coorinate of your %s between 0 and %i: ", l[i].name, MAX - 1);
					scanf_s("%i", &start_x);
				}
				while (start_y < 0 || start_y > MAX - len)
				{
					printf("\nY-coorinate of your %s between 0 and %i: ", l[i].name, MAX - len);
					scanf_s("%i", &start_y);
				}
				for (int k = 0; k < len; k++)
				{
					if (d[start_y + k][start_x] == 0)
					{
						controll--;
					}
					else
					{
						controll = len;
						printf("\nOverlapping ships!\n");
						start_x = -1;
						start_y = -1;
						break;
					}
				}
			}
		}


		for (int j = 0; j < len; j++)
		{
			if (direction == 0)
			{
				d[start_y][start_x + j] = (i + 1);
			}
			else
			{
				d[start_y + j][start_x] = (i + 1);
			}
		}
		printf("\n\t\t%s placed", l[i].name);
		board(player, b, c, d);
	}

	//placing the enemy ships on the invisible board
	for (int i = 0; i < MASS; i++)
	{
		len = l[i].number;
		int controll = len;
		direction = (rand() % 2);
		if (direction == 0)
		{
			while (controll > 0)
			{
				start_x = (rand() % (MAX - len));
				start_y = (rand() % MAX);
				for (int k = 0; k < len; k++)
				{
					if (b[start_y][start_x + k] == 0)
					{
						controll--;
					}
					else
					{
						controll = len;
						break;
					}
				}
			}
		}
		else
		{
			while (controll > 0)
			{
				start_x = (rand() % MAX);
				start_y = (rand() % (MAX - len));
				for (int k = 0; k < len; k++)
				{
					if (b[start_y + k][start_x] == 0)
					{
						controll--;
					}
					else
					{
						controll = len;
						break;
					}
				}
			}
		}


		for (int j = 0; j < len; j++)
		{
			if (direction == 0)
			{
				b[start_y][start_x + j] = (i + 1);
			}
			else
			{
				b[start_y + j][start_x] = (i + 1);
			}
		}
	}
}
#endif // !game_h