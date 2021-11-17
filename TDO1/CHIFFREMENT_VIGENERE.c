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
    int *rKey = cle;
    int c;

    for (int i = 0; i < longueur_texte; ++i)
    {
        c = *(texte_clair + i);
        if (!*rKey)
            rKey = cle;
        *(texte_chiffre + i) = ((c + *(rKey++)) % 26);
    }
}


/******************** Fonction de DÃ©chiffrement Vigenere **********************/
void Dechiffrement_vigenere(int * cle, int longueur_cle,  int * texte_chiffre, int * texte_dechiffre, int longueur_texte)
{
    int j = 0;

    for (int i = 0; i < longueur_texte; ++i)
        *(texte_dechiffre + i) = (*(texte_chiffre + i) - *(cle + j++%longueur_cle) + 26) % 26;

}
