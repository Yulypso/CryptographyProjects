#include "LIBRAIRIES.h"
#include "FONCTIONS_COMMUNES.h"

/***********            Fonction pour déterminer la taille du texte donné en entrée             ************/
void Determination_long_texte(int *LT, char *nom_fichier) /*LT est un pointeur qui contiendra la taille du texte*/
{
  FILE *f = NULL;
  char c;
  *LT = 0;

  if ((f = fopen(nom_fichier, "rb")) != NULL)
  {
    while ((c = fgetc(f)) != EOF)
      if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
        ++(*LT);
  }
  else
    fprintf(stderr, "[Error]: output file: %s\n", nom_fichier);
  fclose(f);
}

/***********            Fonction de Lecture/chargement du texte                ************/
/*********** Attention !!! on ne stocke que les valeurs de l'alphabet comprises entre 0 et 25 inclus ************/

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

/******************* Ecriture du Texte Chiffré dans le fichier donné en parametre ***************************/
void Ecrire_chiffre(int *texte_chiffre, int longueur_texte, char *nom_fichier)
{
  FILE *f = NULL;

  if ((f = fopen(nom_fichier, "wb")) != NULL)
  {
    for (int i = 0; i < longueur_texte; ++i)
      fputc((char)*(texte_chiffre + i) + 'a', f);
  }
  else
    fprintf(stderr, "[Error]: output file: %s\n", nom_fichier);
  fclose(f);
}

/************Fonction pour lire et charger la clé contenue dans le fichier "fichier_cle" ********************/
void Lire_cle(int cle[26], char *fichier_cle)
{
  FILE *f = NULL;
  char c;
  int i = 0;

  if ((f = fopen(fichier_cle, "rb")) != NULL)
  {
    while ((c = fgetc(f)) != EOF)
      if (((c >= 'A') && (c <= 'Z')))
        *(cle + i++) = c - 'A';
      else if ((c >= 'a') && (c <= 'z'))
        *(cle + i++) = c - 'a';
  }
  else
    fprintf(stderr, "[Error]: output file: %s\n", fichier_cle);
  fclose(f);
}
