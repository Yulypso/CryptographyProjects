#include "LIBRAIRIES.h"
#include "CRYPTANALYSE.h"

void Lire_et_charger_texte(int *texte, int longueur_texte, char *nom_fichier)
{
    FILE *f = NULL;
    char c;
    int i = 0;

    if ((f = fopen(nom_fichier, "rb")) != NULL)
    {
        while ((c = fgetc(f)) != EOF)
            if (((c >= 'A') && (c <= 'Z')))
                *(texte + i++) = c - 'A';
            else if ((c >= 'a') && (c <= 'z'))
                *(texte + i++) = c - 'a';
    }
    else
        fprintf(stderr, "[Error]: output file: %s\n", nom_fichier);
    fclose(f);
}

/* Fonction qui compte le nombre de "lettre" dans un texte ets qui le renvoi en retour*/
int Compter_lettre(int *texte, int longueur_texte, int lettre)
{
    int cpt = 0;
    for (int i = 0; i < longueur_texte; ++i)
        if (*(texte + i) == lettre)
            ++cpt;

    return cpt;
}

/* Fonction qui compte et affiche le nombre d'apparition de chaque lettre dans un texte */
void Comptage_nb_apparition(int *texte, int longueur_texte)
{
    int alphabet[26] = {0};

    for (int i = 0; i < 26; ++i)
        *(alphabet + i) = Compter_lettre(texte, longueur_texte, i);

    printf("Nombre d'apparition de chaque lettre dans un texte\n");
    for (int i = 0; i < 26; ++i)
    {
        if (i % 7 == 0)
            printf("\n");
        printf(i < 10 ? " [%d]: %d | " : "[%d]: %d | ", i, *(alphabet + i));
    }
    printf("\n\n");
}

/* Fonction qui calcule la fréquence d'apparition des lettres dans un texte donné */
void Comptage_frequence_apparition(int *texte, int longueur_texte)
{
    int alphabet[26] = {0};

    for (int i = 0; i < longueur_texte; ++i)
        ++(*(alphabet + *(texte + i)));

    printf("Frequence d'apparition de chaque lettre dans un texte\n");
    for (int i = 0; i < 26; ++i)
    {
        if (i % 7 == 0)
            printf("\n");
        printf(i < 10 ? " [%d]: %lf | " : "[%d]: %lf | ", i, (double)*(alphabet + i) / (double)longueur_texte);
    }
    printf("\n\n");
}

/* Fonction qui calcule le nombre des bigrammes ou couples 'lettre1lettre2' dans un texte donné en entrée*/
int Compter_bigramme(int *texte, int longueur_texte, int lettre1, int lettre2)
{
    int cpt = 0;

    for (int i = 0; i < longueur_texte - 1; ++i)
    {
        if (*(texte + i) == lettre1 && *(texte + i + 1) == lettre2)
            ++cpt;
    }

    return cpt;
}

/* Fonction qui affiche sur la sortie standard le texte clair associé au texte chiffré donné en entrée */
void Affiche_clair(int *texte, int longueur_texte, char *clef_analysee)
{
    int i, lettre;
    printf("\n");
    for (i = 0; i < longueur_texte; ++i)
    {
        if (*(clef_analysee + i) == -1)
            printf("*");
        else
        {
            lettre = *(clef_analysee + *(texte + i));
            if (lettre >= 26)
                printf("%c", ((char)(lettre - 26)) + 'a');
            if (lettre < 0)
                printf("%c", ((char)(lettre + 26)) + 'a');
            else
                printf("%c", ((char)(lettre)) + 'a');
        }
    }
    printf("\n");
}

/* Fonction qui affiche un texte tel quel (alphabetique) sur la sortie standard */
void Affiche_alphabetique(int *texte, int longueur_texte)
{
    int i;
    printf("\n");
    for (i = 0; i < longueur_texte; ++i)
        printf("%c", (char)(*(texte + i) + ((int)'a')));

    printf("\n\nLa longueur du texte est de %d caractères\n\n", longueur_texte);
}

/* Fonction qui affiche en superposant le texte clair avec le texte chiffré */
void Affiche_clair_chiffre(int *texte, int longueur_texte, int longueur, char *clef_analysee)
{
    int i, j, longueur_ligne, nb_ligne, lettre, reste, fin;
    longueur_ligne = 100;
    fin = longueur_ligne;

    //pour adapter la longueur du texte à afficher en fonction de la longueur d'une ligne qui est ici de 100
    if ((longueur > 0) && (longueur < longueur_ligne))
    {
        nb_ligne = 1;
        reste = longueur;
    }
    else if (longueur == longueur_ligne)
    {
        nb_ligne = 1;
        reste = 0;
    }
    else if (longueur > longueur_texte)
    {
        nb_ligne = longueur_texte / longueur_ligne;
        nb_ligne++;
        reste = longueur_texte - (longueur_ligne * (nb_ligne - 1));
    }
    else if (longueur <= longueur_texte)
    {
        nb_ligne = longueur / longueur_ligne;
        nb_ligne++;
        reste = longueur - (longueur_ligne * (nb_ligne - 1));
    }

    for (i = 0; i < nb_ligne; i++)
    {
        /* affichage de la ligne claire */
        if (i == (nb_ligne - 1) && reste != 0)
        {
            fin = reste;
        }
        for (j = 0; j < fin; j++)
        {
            if (clef_analysee[((i * longueur_ligne + j) % periode)] == -1)
            {
                printf("*");
            }
            else
            {
                lettre = (texte[(i * longueur_ligne + j)] - clef_analysee[((i * longueur_ligne + j) % periode)]);
                if (lettre >= 26)
                {
                    printf("%c", ((char)(lettre - 26)) + 'a');
                }
                if (lettre < 0)
                {
                    printf("%c", ((char)(lettre + 26)) + 'a');
                }
                else
                {
                    printf("%c", ((char)(lettre)) + 'a');
                }
            }
        }

        printf("\n");

        /* affichage de la ligne chiffre */
        for (j = 0; j < fin; j++)
        {
            printf("%c", (char)(texte[i * longueur_ligne + j] + ((int)'a')));
        }
        printf("\n\n");
    }
}

/* Fonction de cryptanalyse */
void Cryptanalyse(int *texte_chiffre, int longueur_texte, char *clef)
{
}

int main(int argc, char const *argv[])
{
    int texte[26];

    Lire_et_charger_texte(texte, 26, "./test.txt");
    Comptage_nb_apparition(texte, 26);
    Comptage_frequence_apparition(texte, 26);
    printf("nombre bigramme: %d \n", Compter_bigramme(texte, 26, 0, 0));

    return 0;
}
