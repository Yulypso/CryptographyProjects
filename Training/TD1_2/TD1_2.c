#include <stdio.h>
#include <stdlib.h>

#define IFCHIFFRER 0
#define IFDECHIFFRER 1


void CHIFF_CESAR(int k, char * nom_fic_clair, char * nom_fic_chiff);
void DECHIFF_CESAR(int k, char * nom_fic_clair, char * nom_fic_dechiff);

int main(int argc, char *argv[])
{
	if(IFCHIFFRER)
	{
		CHIFF_CESAR(7, argv[1], argv[2]);
	}

	if(IFDECHIFFRER)
	{
		DECHIFF_CESAR(16, argv[1], argv[2]);
	}

	return 0;
}



void CHIFF_CESAR(int k, char * nom_fic_clair, char * nom_fic_chiff)
{
	FILE* fic = NULL;
	fic = fopen(nom_fic_clair, "r");

	FILE* foc = NULL;
	foc = fopen(nom_fic_chiff, "w");

	char copy;

	while((copy = fgetc(fic))!=EOF)
	{
		if(copy >= 'a' && copy <= 'z')
		{
			copy = copy+k-'a'; //on ajoute le décalage et on enlève le gap
			copy = copy%26; //on modulo
			copy = copy + 'a'; //on rajoute le gap
			fprintf(foc, "%c", copy); //on ecrit la valeur
		}
	}

	fclose(fic);
	fclose(foc);
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
			copy = copy+26;
			copy = copy%26; //on modulo
			copy = copy + 'a'; //on rajoute le gap
			fprintf(foc, "%c", copy); //on ecrit la valeur
		}
	}

	fclose(fic);
	fclose(foc);
}