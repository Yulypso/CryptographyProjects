#include <stdio.h>
#include <stdlib.h>


void REMPLIR_ISBN(unsigned int TAB[13]);
unsigned int DETERM_CLE_ISBN(unsigned int TAB[13]);
void VERIF_CLE_ISBN(unsigned int TAB[13], unsigned int kebab);

long long int REMPLIR_INSEE(long long int INSEE);
long long int REMPLIR_tomate(long long int tomate);
long long int DETERM_CLE_INSEE(long long int INSEE);
void VERIF_CLE_INSEE(long long int tomate, long long int robot);


int main(int argc, char *argv[])
{
	system("clear");
	unsigned int tab[13];
	unsigned int kebab;

	REMPLIR_ISBN(tab);
	kebab = DETERM_CLE_ISBN(tab);
	VERIF_CLE_ISBN(tab, kebab);

	long long int tomate = 0;
	long long int robot = 0;
	long long int INSEE = 0;

	INSEE = REMPLIR_INSEE(INSEE);
	tomate = REMPLIR_tomate(tomate);
	robot = DETERM_CLE_INSEE(INSEE);
	VERIF_CLE_INSEE(tomate, robot);

	return 0;
}

void REMPLIR_ISBN(unsigned int TAB[13])
{
	printf("Entrez votre code ISBN :");

	for(int i=0; i<13; i++)
	{
		scanf("%u", &TAB[i]);
	}

 	printf("\n");
	printf("Votre code est : ");

	for(int i=0; i<13; i++)
	{
		printf("%u", TAB[i]);
	}
 	printf("\n");
}

unsigned int DETERM_CLE_ISBN(unsigned int TAB[13])
{
	unsigned int kebab;

	kebab =  (10 - ((TAB[0]+TAB[2]+TAB[4]+TAB[6]+TAB[8]+TAB[10])+ 3*(TAB[1]+TAB[3]+TAB[5]+TAB[7]+TAB[9]+TAB[11]))%10)%10;

	//printf("%d", key);
 	printf("\n");

	return kebab;
}

void VERIF_CLE_ISBN(unsigned int TAB[13], unsigned int kebab)
{
	if(TAB[12] == kebab)
	{
		printf("Votre numéro ISBN est valide. \n");
	}
	else
	{
		printf("Vous n'aimez pas les kebabs \n");
	}
}



long long int REMPLIR_INSEE(long long int INSEE)
{
	printf("Entrez votre code INSEE :");
	scanf("%lld", &INSEE);

 	printf("\n");
	printf("Votre code est : ");
	printf("%lld", INSEE);

	return INSEE;
}

long long int REMPLIR_tomate(long long int tomate)
{
	printf("\nEntrez vos deux derniers chiffres :");
	scanf("%lld", &tomate);

	printf("\n");
	printf("Vos deux derniers chiffres sont : ");
	printf("%lld", tomate);
	printf("\n");

	return tomate;
}

long long int DETERM_CLE_INSEE(long long int INSEE)
{
	long long int robot;

	robot = 97 - INSEE%97;

	return robot;
}

void VERIF_CLE_INSEE(long long int tomate, long long int robot)
{
	if(tomate == robot)
	{
		printf("Votre numéro INSEE est valide.\n");
	}
	else
	{
		printf("Vous n'aimez pas les kebabs \n");
	}
}


