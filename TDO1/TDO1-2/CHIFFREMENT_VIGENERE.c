/*******************************************************************************/
/****                                                                        ***/
/****                    CHIFFREMENT DE VIGENERE                             ***/
/****                                                                        ***/
/*******************************************************************************/

#include "LIBRAIRIES.h"
#include "CHIFFREMENT_VIGENERE.h"
#include "FONCTIONS_COMMUNES.h"


/******************** Fonction de Chiffrement Vigenere **********************/
void Chiffrement_vigenere(int * cle, int longueur_cle,  int * texte_clair, int * texte_chiffre, int longueur_texte)
{
/*
  texte_clair contient le message en clair
  texte_chiffre va contenir le message chiffré
*/

  int i, j;
  
  j=0;
  for(i=0;i<longueur_texte;i++)
	  {
	      texte_chiffre[i]=(texte_clair[i] + cle[j%longueur_cle]) % 26;
          j++;
	  }
  
}


/******************** Fonction de Déchiffrement Vigenere **********************/
void Dechiffrement_vigenere( int * cle, int longueur_cle,  int * texte_chiffre, int * texte_dechiffre, int longueur_texte)
{
/*
  texte_chiffre contient le message chiffré
  texte_dechiffre va contenir le message dechiffré
*/

  int i, j;
  
   j=0;
  for(i=0;i<longueur_texte;i++)
	  {
	      texte_dechiffre[i]=(texte_chiffre[i] - cle[j%longueur_cle] + 26) % 26;
          j++;
	  }
  
 
  
}
