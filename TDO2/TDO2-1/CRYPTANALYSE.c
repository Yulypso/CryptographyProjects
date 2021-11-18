#include "LIBRAIRIES.h"
#include "CRYPTANALYSE.h"

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

  for (int i = 0; i < longueur_texte; ++i)
    ++(*(alphabet + *(texte + i)));
}

/* Fonction qui calcule la fréquence d'apparition des lettres dans un texte donné */
void Comptage_frequence_apparition(int *texte, int longueur_texte)
{
}

/* Fonction qui calcule le nombre des bigrammes ou couples 'lettre1lettre2' dans un texte donné en entrée*/
int Compter_bigramme(int *texte, int longueur_texte, int lettre1, int lettre2)
{
  return 0;
}

/* Fonction qui affiche sur la sortie standard le texte clair associé au texte chiffré donné en entrée */
void Affiche_clair(int *texte, int longueur_texte, char *clef_analysee)
{
}

/* Fonction qui affiche un texte tel quel (alphabetique) sur la sortie standard */
void Affiche_alphabetique(int *texte, int longueur_texte)
{
}

/* Fonction qui affiche en superposant le texte clair avec le texte chiffré */
void Affiche_clair_chiffre(int *texte, int longueur_texte, int longueur, char *clef_analysee)
{
}

/* Fonction de cryptanalyse */
void Cryptanalyse(int *texte_chiffre, int longueur_texte, char *clef)
{
}
