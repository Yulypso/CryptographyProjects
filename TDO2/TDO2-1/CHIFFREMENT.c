#include "LIBRAIRIES.h"
#include "CHIFFREMENT.h"

/* Fonction de chiffrement par substitution  */
void Chiffrer_substitution(int *cle, int *texte_clair, int *texte_chiffre, int longueur_texte)
{
  for (int i = 0; i < longueur_texte; ++i)
    *(texte_chiffre + i) = *(cle + *(texte_clair + i));
}

/* Fonction de dechiffrement par substitution  */
void Dechiffrer_substitution(int *cle, int *texte_chiffre, int *texte_dechiffre, int longueur_texte)
{
  for (int i = 0; i < longueur_texte; ++i)
    *(texte_dechiffre + i) = *(cle + *(texte_chiffre + i));
}
