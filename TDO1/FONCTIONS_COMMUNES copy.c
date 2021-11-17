#include "LIBRAIRIES.h"
#include "FONCTIONS_COMMUNES.h"


/***********            Fonction pour déterminer la longueur du texte             ************/
/* ATTENTION : 
 * le texte doit comporter uniquement les lettres de l'alphabet. 
 * Il ne faut pas aussi comptabiliser les retours à la ligne */

void Determination_long_texte(int * LT, char * nom_fichier)
{
  FILE *f = NULL;
  char c;

  if((f = fopen(nom_fichier, "rb")) != NULL)
  {
    while ((c = fgetc(f)) != EOF)
      if((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
        *LT += 1;
  }
  else
      printf("[Error]: output file: %s\n", nom_fichier);
  fclose(f);
}

 
/***********            Fonction de Lecture/chargement du texte                ************/
/*********** Attention !!! on ne stocke que les valeurs de l'alphabet comprises entre 0 et 25 inclus ************/

void Lire_et_charger_texte(int * texte, int longueur_texte, char * nom_fichier)
{
  FILE *f = NULL;
  char c;
  int i = 0;

  if((f = fopen(nom_fichier, "rb")) != NULL)
  {
    while ((c = fgetc(f)) != EOF)
      if((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
        *(texte + i++) = c;
  }
  else
      printf("[Error]: output file: %s\n", nom_fichier);
  fclose(f);
}


/******************* Ecriture du Texte Chiffré dans le fichier donné en paramètre ***************************/
void Ecrire_chiffre(int * texte_chiffre, int longueur_texte, char * nom_fichier)
{
  FILE *f = NULL;

  if((f = fopen(nom_fichier, "wb")) != NULL)
  {
    for (int i = 0; i < longueur_texte; ++i)
      fputc(*(texte_chiffre + i), f);
  }
  else
      printf("[Error]: output file: %s\n", nom_fichier);
  fclose(f);
}

int main(int argc, char **argv)
{    
  int length = 0;
  int texte[100];

  Determination_long_texte(&length, "test.txt");
  printf("%d\n", length);

  Lire_et_charger_texte(texte, 10, "test.txt");
  
  for (int i = 0; i < length; i++)
  {
    printf("%c", (char)texte[i]);
  }
  
  Ecrire_chiffre(texte, length, "textew.txt");
  
  return 0;
}