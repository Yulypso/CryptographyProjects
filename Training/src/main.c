#include "../includes/main.h"

#define CARRE(a) ({ \
    (a) * (a);      \
})

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

    vigenereEncrypt(*(argv + 1), *(argv + 2), *(argv + 3));
    //vigenereDecrypt(*(argv + 1), *(argv + 2), *(argv + 3));

    return 0;
}
