#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>


struct Sides {
	char gondor[5];
	char mordor[5];

};
struct CastarCoins
{
	int gon;
	int mor;
};

int main()
{
	int sides = 1; //por exemplo 1 se o player escolhesse mondor e 0 se fosse gondor
	int c1, c2;
	
	struct Sides bases = { "GGGG", "MMMM" };
	struct Sides mines = { "SS", "EE" };
	struct Sides barracks = { "RR", "II" };
	struct Sides stables = { "LL", "MK" };
	struct Sides armoury = { "GF", "DF" };
	struct Sides infantry = { "G", "OW" };
	struct Sides cavalry = { "SK", "W" };
	struct Sides artillery = { "T", "ST" };
	struct CastarCoins startingCoin;
	startingCoin.gon = 100;
	startingCoin.mor = 100;
	
	


	printf("What do you want to build: \n1-Bases\n2-Mines\n3-Barracks\n4-Stables\n5-Armoury\n");
	scanf("%d", &c1);
	if (c1 = 1)
	{
		if (sides = 1)
		{
			printf("Base Construida: %s\n", bases.mordor);
			startingCoin.mor -= 25;
			printf("%s\n", infantry.mordor);
			printf("%d", startingCoin.mor);
		}
	}

}



