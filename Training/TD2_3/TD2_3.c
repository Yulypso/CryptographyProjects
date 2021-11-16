#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

void CHIFF_VERNAM_1(char* nom_fic_clair, char* nom_fic_chiff, char * nom_fic_cle);
void DECHIFF_VERNAM_1(char* nom_fic_chiff, char* nom_fic_dechiff, char* nom_fic_cle);

void CHIFF_VERNAM_2(char * nom_fic_clair, char * nom_fic_chiff, double seed);
void DECHIFF_VERNAM_2(char * nom_fic_chiff, char * nom_fic_dechiff, double seed);


int main(int argc, char *argv[])
{
	//CHIFF_VERNAM_1(argv[1], argv[2], argv[3]);
	//DECHIFF_VERNAM_1(argv[2], argv[4], argv[3]);
	CHIFF_VERNAM_2(argv[1], argv[2], 0.0125484);
	DECHIFF_VERNAM_2(argv[2], argv[4], 0.0125484);
	return 0;
}

void CHIFF_VERNAM_1(char* nom_fic_clair, char* nom_fic_chiff, char * nom_fic_cle)
{
	FILE * fic = NULL;
	fic = fopen(nom_fic_clair,"rb");

	FILE * foc = NULL;
	foc = fopen(nom_fic_chiff,"wb");

	FILE * fac = NULL;
	fac = fopen(nom_fic_cle,"wb");

	int L, R, C; // L = clair | R = clé | C = chiffré 

	while((L = fgetc(fic))!=EOF)
	{
		R = rand()%256;
		fputc(R, fac);
		C = L^R;
		fputc(C,foc);
	}

	fclose(fic);
	fclose(foc);
	fclose(fac);
}


void DECHIFF_VERNAM_1(char* nom_fic_chiff, char* nom_fic_dechiff, char* nom_fic_cle)
{
	FILE * fic = NULL;
	fic = fopen(nom_fic_chiff,"rb");

	FILE * foc = NULL;
	foc = fopen(nom_fic_dechiff,"wb");

	FILE * fac = NULL;
	fac = fopen(nom_fic_cle,"rb");

	int L, R, C;

	while((C = fgetc(fic))!=EOF)
	{
		R = fgetc(fac);
		L = C^R;
		fputc(L,foc);
	}

	fclose(fic);
	fclose(foc);
	fclose(fac);
}

void CHIFF_VERNAM_2(char * nom_fic_clair, char * nom_fic_chiff, double seed)
{
	FILE * fic = NULL;
	fic = fopen(nom_fic_clair,"rb");

	FILE * foc = NULL;
	foc = fopen(nom_fic_chiff,"wb");

	int R, C, L; // L = clair | R = clé | C = chiffré 
	unsigned long long int val;
	double X = seed;

	while((L = fgetc(fic))!=EOF)
	{
		X = 3.9999*X*(10-X);
		val = (unsigned long long int) floor(X * pow(10,15));
		R = val%256;
		C= L^R;
		fputc(C, foc);
	}
	fclose(fic);
	fclose(foc);
}

void DECHIFF_VERNAM_2(char * nom_fic_chiff, char * nom_fic_dechiff, double seed)
{
	FILE * fic = NULL;
	fic = fopen(nom_fic_chiff,"rb");

	FILE * foc = NULL;
	foc = fopen(nom_fic_dechiff,"wb");

	int R, C, L; // L = clair | R = clé | C = chiffré 
	unsigned long long int val;
	double X = seed;

	while((C = fgetc(fic))!=EOF)
	{
		X = 3.9999*X*(10-X);
		val = (unsigned long long int) floor(X * pow(10,15));
		R = val%256;
		L= C^R;
		fputc(L, foc);
	}

}









