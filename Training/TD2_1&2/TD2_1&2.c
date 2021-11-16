#include <stdio.h>
#include <stdlib.h>


int DETERM_LONG_TXTE(char * nom_fic);
void CHARGER_CLE(int T, char cle[T], char* nom_fic_cle);
void AFFICHER_CLE(int T, char cle[T]);
void CHIFF_VEGENERE(int T, char cle[T], char * nom_fic_clair, char * nom_fic_chiff);
void DECHIFF_VIGENERE(int T, char cle[T], char * nom_fic_chiff, char * nom_fic_dechiff);
void RECHERCHE_CLE(char * nom_fic_clair, char * nom_fic_chiff, char * nom_fic_cle_rep); 
void EXTRACTION_CLE(char*nom_fic_cle_rep);


int main(int argc, char *argv[])
{
	int T = DETERM_LONG_TXTE(argv[1]);
	printf("La longueur du texte est : %d\n", T);
	char cle[T];

	CHARGER_CLE(T, cle, argv[1]);
	AFFICHER_CLE(T, cle);

	CHIFF_VEGENERE(T, cle, argv[2], argv[3]);
	DECHIFF_VIGENERE(T, cle, argv[3], argv[4]);
	RECHERCHE_CLE(argv[2], argv[3], argv[5]);
	EXTRACTION_CLE(argv[5]);

}


int DETERM_LONG_TXTE(char * nom_fic)
{
	char copy;
	int cpt = 0;

	FILE* fic = NULL;
	fic = fopen(nom_fic, "r");

	while((copy = fgetc(fic))!=EOF)
	{
		if(copy >= 'a' && copy <= 'z')
		{
			cpt++;
		}
	}
	fclose(fic);

return cpt;
}


void CHARGER_CLE(int T, char cle[T], char* nom_fic_cle)
{
	FILE* fic = NULL;
	fic = fopen(nom_fic_cle, "r");

	char copy;
	int i=0;

	while((copy = fgetc(fic))!=EOF)
	{
		if(copy >= 'a' && copy <= 'z')
		{
			cle[i] = copy;
			i++;
		}
	}
	fclose(fic);
}

void AFFICHER_CLE(int T, char cle[T])
{
	printf("La clé est : ");

	for(int i=0; i<T; i++)
	{
		printf("%c", cle[i]);
	}

	printf("\n");
}

void CHIFF_VEGENERE(int T, char cle[T], char * nom_fic_clair, char * nom_fic_chiff)
{
	FILE* fic = NULL;
	fic = fopen(nom_fic_clair, "r");

	FILE* foc = NULL;
	foc = fopen(nom_fic_chiff, "w");

	int cpt = 0;
	char copy;


	while((copy = fgetc(fic))!=EOF)
	{
		if(copy >= 'a' && copy <= 'z')
		{
			copy = copy - 'a' + (cle[cpt] - 'a');
			copy = copy%26;
			copy = copy +'a';
			fprintf(foc, "%c", copy);
			cpt++;
			cpt = cpt%T;
		}
	}

	fclose(fic);
	fclose(foc);
}


void DECHIFF_VIGENERE(int T, char cle[T], char * nom_fic_chiff, char * nom_fic_dechiff)
{
	FILE* fic = NULL;
	fic = fopen(nom_fic_chiff, "r");

	FILE* foc = NULL;
	foc = fopen(nom_fic_dechiff, "w");	

	int cpt = 0;
	char copy;

	
	while((copy = fgetc(fic))!=EOF)
	{
		if(copy >= 'a' && copy <= 'z')
		{
			copy = copy - 'a' - (cle[cpt] - 'a');
			copy = copy + 26;
			copy = copy%26;
			copy = copy +'a';
			fprintf(foc, "%c", copy);
			cpt++;
			cpt = cpt%T;
		}
	}

	fclose(fic);
	fclose(foc);
}

void RECHERCHE_CLE(char * nom_fic_clair, char * nom_fic_chiff, char * nom_fic_cle_rep)
{
	FILE* fic = NULL;
	fic = fopen(nom_fic_clair, "r");

	FILE* foc = NULL;
	foc = fopen(nom_fic_chiff, "r");	

	FILE* fac = NULL;
	fac = fopen(nom_fic_cle_rep, "w");

	char copy, copy1, copy2;

	while(((copy1 = fgetc(fic))!=EOF) && ((copy2 = fgetc(foc))!=EOF))
	{
		if((copy1 >= 'a' && copy1 <= 'z')&&(copy2 >= 'a' && copy2 <= 'z'))
		{
			copy = (copy2-'a') - (copy1-'a');
			copy = copy + 26;
			copy = copy%26;
			copy = copy+'a';

			fprintf(fac, "%c", copy);
		}
	}

	printf("ah\n");
	fclose(fic);
	fclose(foc);
	fclose(fac);
}

void EXTRACTION_CLE(char * nom_fic_cle_rep)
{
	FILE * fic = NULL;
	fic = fopen(nom_fic_cle_rep, "r");

	char copy_debut, copy;

	copy_debut = fgetc(fic);
	printf("%c", copy);

	printf("La clé est : ");
	while((copy = fgetc(fic))!=EOF)
	{
		if(copy != copy_debut)
		{
			printf("%c", copy);
		}
	}

}




