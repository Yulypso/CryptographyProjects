#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* CORRIGÉ EXAMEN LUCY ZHU */

/* Constantes symboliques */
#define CLE 1
#define N 1000

/* Prototypes */
void encode_decode(char tab[], int cle);
void ecrire_message(int user, char *tab);
void lire_message(int user, char *tab, char *type);
int envoyer_message(int fromuser, int touser, char *tab1, char *tab2);

/* Fonction principale */
int main()
{
    // Déclaration des Tableaux et alias
    char out1[N], in1[N];
    char *out2 = in1;
    char *in2 = out1;

    int nbcara = 0;

    // Boucle infinie
    while (1)
    {
        ecrire_message(1, out1);
        printf("debug 1\n");
        encode_decode(out1, CLE);
        printf("debug 2\n");
        nbcara = envoyer_message(1, 2, out1, in2);
        printf("debug 3\n");
        printf("Nombre de caracteres envoyes : %d\n", nbcara);

        lire_message(2, in2, "crypte");
        printf("debug 4\n");
        encode_decode(in2, -CLE);
        lire_message(2, in2, "decrypte");

        ecrire_message(2, out2); //Reponse de l'utilisateur 2
        encode_decode(out2, CLE);
        nbcara = envoyer_message(1, 2, out2, in1);
        printf("Nombre de caracteres envoyes : %d\n", nbcara);

        lire_message(2, in1, "crypte");
        encode_decode(in1, -CLE);
        lire_message(2, in1, "decrypte");

        //FIN de la boucle
        if (strcmp(in1, "fin") == 0 || strcmp(in2, "fin") == 0)
            break;
    }
    printf("Deconnexion\n");
    return 0;
}

/* Fonctions */
void encode_decode(char tab[], int cle)
{
    int i = 0;
    while (tab[i] != '\0')
    {
        tab[i++] += cle;
    }
}

void ecrire_message(int user, char *tab)
{
    printf("Utilisateur %d taper votre message : \n", user);
    fgets(tab, N, stdin); // Safer to use fgets(tab, N, stdin); instead of gets(tab)
}

void lire_message(int user, char *tab, char *type)
{
    printf("Message %s recu par %d : %s\n", type, user, tab);
}

int envoyer_message(int fromuser, int touser, char *tab1, char *tab2)
{
    strcpy(tab2, tab1);
    printf("Message de %d envoye a %d: %s \n", fromuser, touser, tab2);
    return strlen(tab2);
}
