#include "../includes/main.h"

#define CARRE(a) ({ \
    (a) * (a);      \
})

int ppcm(int nbr1, int nbr2)
{
    int ppcmTmp = (nbr1 > nbr2) ? nbr1 : nbr2;

    while (1)
    {
        if (ppcmTmp % nbr1 == 0 && ppcmTmp % nbr2 == 0)
            return ppcmTmp;
        ++ppcmTmp;
    }
}

int pgcd(int nbr1, int nbr2)
{
    if (nbr2 != 0)
        return pgcd(nbr2, nbr1 % nbr2);
    else
        return nbr1;
}

void vigenereEncrypt(char *key, char *inputFile, char *outputFile)
{
    FILE *fin = NULL, *fout = NULL;
    char c;
    char *rKey = key;

    if ((fin = fopen(inputFile, "rb")) != NULL)
    {
        if ((fout = fopen(outputFile, "wb")) != NULL)
        {
            while ((c = fgetc(fin)) != EOF)
            {
                /* Cipher/Decipher here */
                if (!*rKey)
                    rKey = key;
                if (c >= 'a' && c <= 'z')
                    c = (((c - 'a') + (*(rKey++) - 'a')) % 26) + 'a';
                fputc(c, fout);
            }
        }
        else
            printf("[Error]: output file: %s\n", outputFile);
        fclose(fout);
    }
    else
        printf("[Error]: input file: %s\n", inputFile);
    fclose(fin);
}

void vigenereDecrypt(char *key, char *inputFile, char *outputFile)
{
    FILE *fin = NULL, *fout = NULL;
    char c;
    char *rKey = key;

    if ((fin = fopen(inputFile, "rb")) != NULL)
    {
        if ((fout = fopen(outputFile, "wb")) != NULL)
        {
            while ((c = fgetc(fin)) != EOF)
            {
                /* Cipher/Decipher here */
                if (!*rKey)
                    rKey = key;
                if (c >= 'a' && c <= 'z')
                    c = (((c - 'a') - (*(rKey++) - 'a') + 26) % 26) + 'a';
                fputc(c, fout);
            }
        }
        else
            printf("[Error]: output file: %s\n", outputFile);
        fclose(fout);
    }
    else
        printf("[Error]: input file: %s\n", inputFile);
    fclose(fin);
}

int main(int argc, char **argv)
{
    printf("ready Training\n");

    //vigenereEncrypt(*(argv + 1), *(argv + 2), *(argv + 3));
    vigenereDecrypt(*(argv + 1), *(argv + 2), *(argv + 3));
    printf("%d\n", ppcm(4, 16));

    return 0;
}
