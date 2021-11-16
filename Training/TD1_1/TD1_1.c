/* 
   Pour compiler :   gcc -Wall /Users/Kyu/Documents/ESIEA/2A\ ESIEA/Mathématiques/Semestre\ 2/MAT\ 2053/2.Cryptographie/TD/TD1/TD1_1.c -o MAIN
   Pour chiffrer/dechiffrer :   ./MAIN cle.txt texte_clair.txt texte_reçu.txt
*/

#include <stdio.h>
#include <stdlib.h>

/*Ne pas activer les deux #define*/
#define IF_CHIFFRER 1
#define IF_DECHIFFRER 0

void CHARGER_CLE(char cle[26], char* nom_fic_cle);
void AFFICHER_TAB(char cle[26]);
void CHIFF_MONO_ALPHA(char cle[26], char* nom_fic_clair, char* nom_fic_chiffre);
void DECHIFF_MONO_ALPHA(char cle[26], char* nom_fic_chiffre, char* nom_fic_dechiffre);



int main(int argc, char *argv[])
{
	char cle[26];

	CHARGER_CLE(cle, argv[1]);
	//AFFICHER_TAB(cle);

	if(IF_CHIFFRER)
	{
		CHIFF_MONO_ALPHA(cle, argv[2], argv[3]);	
	}

	if(IF_DECHIFFRER)
	{
		DECHIFF_MONO_ALPHA(cle, argv[2], argv[3]);
	}

	return 0;
}


void AFFICHER_TAB(char cle[26])
{
	printf("La clé est : ");

	for(int i=0; i<26; i++)
	{
		printf("%c", cle[i]);
	}

	printf("\n");
}


void CHARGER_CLE(char cle[26], char* nom_fic_cle) 
{
	FILE* fic = NULL;
	fic = fopen(nom_fic_cle, "r");

	char copy;
	int i = 0;

	while((copy = fgetc(fic))!=EOF)
	{
		cle[i] = copy;
		i++;
	}

	fclose(fic);
}


void CHIFF_MONO_ALPHA(char cle[26], char* nom_fic_clair, char* nom_fic_chiffre)
{
	FILE* fic = NULL;
	fic = fopen(nom_fic_clair, "r");

	FILE* foc = NULL;
	foc = fopen(nom_fic_chiffre,"w");

	char copy;

	while((copy = fgetc(fic))!=EOF)
	{
		if(copy >= 'a' && copy <= 'z')
		{
			fprintf(foc, "%c", cle[copy-'a']);
		}
	}

	fclose(fic);
	fclose(foc);
}


void DECHIFF_MONO_ALPHA(char cle[26], char* nom_fic_chiffre, char* nom_fic_dechiffre)
{
	FILE* fic = NULL;
	fic = fopen(nom_fic_chiffre, "r");

	FILE* foc = NULL;
	foc = fopen(nom_fic_dechiffre, "w");

	char copy;
	int i = 0;

	while((copy = fgetc(fic))!=EOF)
	{
		if(copy >= 'a' && copy <= 'z')
		{
			for(i=0; i<26; i++)
			{
				if(cle[i] == copy)
				{
					fprintf(foc, "%c", i+'a');
				}
			}
		}
	}

	fclose(fic);
	fclose(foc);
}






