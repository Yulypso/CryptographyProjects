/**************************************************************************/
/****                                                                  ****/
/****                   Cryptanalyse Vigenere                          ****/
/****                                                                  ****/
/**************************************************************************/



#include "LIBRAIRIES.h"
#include "CRYPTANALYSE_VIGENERE.h"


int comp_int(int * a, int * b)
{
  return 0;
}



/****                 Affichage numérique d'un texte                 ***/
void affiche_numerique(int * texte, int longueur_texte)
{

}



/****                 Affichage alphabetique d'un texte                 ***/
/*ATTENTION : Les lettres sont normalement en minuscule*/
void affichage_alphabetique_texte(int * texte, int longueur_texte)
{
  
}



/****                 Affichage côte à côte du texte clair partiellement retrouvé et du texte chiffré correspondant                 ***/
void affiche_clair_vigenere(int * texte, int longueur_texte,  int longueur, int * clef_analysee, int periode)
{
  
}





/****       Fonction affiche le texte clair complètement retrouvé                    ****/
void affiche_clair(int *texte_chiffre, int longueur_texte, int * clef_analysee, int periode)
{
 
}


  
/****       Fonction qui compte le nombre de "lettre" dans un texte                    ****/
int compter_lettre(int *texte, int longueur_texte, int lettre)
{
  /* 
   *
   * A remplir
   * 
   */
  
  return 0; 
}



/****       Fonction de calcul d'indices de coincidences                          *******/
double indice_coincidence( int * texte, int longueur_texte)
{
  /*
   * 
   * 
   * A remplir (La formule est simple et est donnée par la somme des Pi^2 où i=a, b, ..., z et 
   * Pm désigne par exemple la probabilité de tomber sur la lettre m)
   * Vous pouvez utiliser la fonction compter_lettre juste au dessus.
   * 
   * 
   */
  return 0;

}



/****        Fonction pour extraire un sous-texte                         *******/
/*On tient compte de la période et du décalage à effectuer à chaque fois pour bien se positionner*/
void extraction_sous_texte( int * texte, int * sous_texte, int longueur_sous_texte, int periode, int indice_dec)
{
  /* 
   *
   * A remplir
   * 
   * 
   */
}



/****       Fonction qui cherche les indices de coincidences pour toutes le périodes données                        *******/
void analyse_coincidence(int *texte_chiffre, int longueur_texte)
{
  
}


/****       Fonction qui recherche les éléments de la clé par rapport à sa longueur                       *******/
/*Cette fonction tente également le déchiffrement associée à la clé choisie*/
void analyse_decalage(int *texte_chiffre, int longueur_texte,int periode,int * clef_analysee)
{
 
}
