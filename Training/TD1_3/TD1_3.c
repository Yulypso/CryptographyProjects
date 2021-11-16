#include <stdio.h>
#include <stdlib.h>

#define IFFREQUENCE 1
#define IFFORCE 0

void CALC_FREQ_LETTRES_ALPHA(float alpha[26], char * nom_fic);
int AFFIC_PLUS_GRDE_FREQ(float alpha[26]);
void INIT_TAB(float alpha[26]);
void SHOW_TAB(float alpha[26]);
void DECHIFF_CESAR(int k, char * nom_fic_clair, char * nom_fic_dechiff);

void RECHERCHE_EXHAUSTIVE(char * fic_chiff, char* fic_dechiff);
void DECHIFF_CESAR_2(int k, FILE* fic, FILE* foc);

int main(int argc, char *argv[])
{
	if(IFFREQUENCE)
	{
		int decalage = 0;
		float alpha[26];
		INIT_TAB(alpha);
		//printf("\navant le calcul de fréquence : ");
		//SHOW_TAB(alpha);

		CALC_FREQ_LETTRES_ALPHA(alpha, argv[1]);
		printf("\naprès le calcul de fréquence \n");
		SHOW_TAB(alpha);

		decalage = AFFIC_PLUS_GRDE_FREQ(alpha);
		DECHIFF_CESAR(decalage, argv[1], argv[2]);
	}

	if(IFFORCE)
	{
		RECHERCHE_EXHAUSTIVE(argv[1], argv[2]);
	}
	return 0;
}

void SHOW_TAB(float alpha[26])
{
	for(int i=0; i<26; i++)
	{
		printf("| %.4f |\n", alpha[i]);
	}
	printf("\n");
}


void INIT_TAB(float alpha[26])
{
	for(int i=0; i<26; i++)
	{
		alpha[i]= 0.0;
	}
}

void CALC_FREQ_LETTRES_ALPHA(float alpha[26], char * nom_fic)
{
	FILE* fic = NULL;
	fic = fopen(nom_fic, "r");

	int total = 0;
	char copy;

	while((copy = fgetc(fic))!= EOF)
	{
		if(copy >= 'a' && copy <= 'z')
		{
			copy = copy-'a'; //on retire le gap
			alpha[(int)copy] = alpha[(int)copy]+1.0;
			total = total+1;
		}
	}

	printf("total de caractères :%d\n", total);

	for(int i=0; i<26; i++)
	{
		alpha[i] = alpha[i]/(float)total;
	}


}

int AFFIC_PLUS_GRDE_FREQ(float alpha[26])
{
	float save = 0.0;
	int letter = 0;

	for(int i=0; i<26; i++)
	{
		if(alpha[i]>=save)
		{
			save = alpha[i];
			letter = i;
		}
	}
	printf("la plus grande frequence est la lettre |%c| pour une fréquence de : |%.4f|\n", letter+'a', save);
	printf("le décalage est donc : |%d| - |4| (e étant la lettre la plus utilisée) = |%d| \n", letter, letter-4);
	letter = letter - 4;
	return letter;
}


void DECHIFF_CESAR(int k, char * nom_fic_clair, char * nom_fic_dechiff)
{
	FILE* fic = NULL;
	fic = fopen(nom_fic_clair, "r");

	FILE* foc = NULL;
	foc = fopen(nom_fic_dechiff, "w");

	char copy;

	while((copy = fgetc(fic))!=EOF)
	{
		if(copy >= 'a' && copy <= 'z')
		{
			copy = copy-k-'a'; //on ajoute le décalage et on enlève le gap
			copy = copy+26; //pour mettre la valeur en positif 
			copy = copy%26; //on modulo
			copy = copy + 'a'; //on rajoute le gap
			fprintf(foc, "%c", copy); //on ecrit la valeur
		}
	}

	fclose(fic);
	fclose(foc);
}

void DECHIFF_CESAR_2(int k, FILE* fic, FILE* foc)
{
	char copy;

	fprintf(foc, "|%d| ", k);
	while((copy = fgetc(fic))!=EOF)
	{
		if(copy >= 'a' && copy <= 'z')
		{
			copy = copy-k-'a'; //on ajoute le décalage et on enlève le gap
			copy = copy+26;
			copy = copy%26; //on modulo
			copy = copy + 'a'; //on rajoute le gap
			fprintf(foc, "%c", copy); //on ecrit la valeur
		}
	}
	fprintf(foc, "\n");

}

void RECHERCHE_EXHAUSTIVE(char * fic_chiff, char * fic_dechiff)
{
	FILE* fic = NULL;
	fic = fopen(fic_chiff, "r");

	FILE * foc = NULL;
	foc = fopen(fic_dechiff, "w"); //w permet d'écraser un fichier et de réécrire || a permet d'écrire sans écraser

	fseek(foc, 0, SEEK_SET);

	for(int i=0; i<26; i++)
	{
		DECHIFF_CESAR_2(i, fic, foc);
		fseek(fic, 0, SEEK_SET); //permet de revenir au début d'un fichier texte

	}

	fclose(fic);
	fclose(foc);
}


