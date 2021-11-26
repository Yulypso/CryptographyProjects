/*
 On suppose que vous avez le package SDL déjà installé sur votre machine, sinon il faudra l'installer. Pour compiler il suffit de taper la commande :
 gcc -o EXEC STEGANALYSE.c `sdl-config --cflags --libs` -Wall
 
 Le code a été largement commenté pour vous permettre de le comprendre plus facilement et plus rapidement.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <SDL.h>

/*Fonction qui sert à charger une image*/
SDL_Surface *load_image(char *filename)
{
    SDL_Surface *Image_chargee = NULL;   //Surface tampon qui nous servira pour charger l'image
    SDL_Surface *Image_optimisee = NULL; //L'image optimisée qu'on va utiliser

    Image_chargee = SDL_LoadBMP(filename); //Chargement de l'image BMP

    if (Image_chargee != NULL) //Si le chargement se passe bien
    {
        Image_optimisee = SDL_DisplayFormat(Image_chargee); /*Pour convertir l'image chargée vers le format 
	                                                       d'affichage adapté (celui de l'écran actuel)*/
        SDL_FreeSurface(Image_chargee);                     //Libération de l'ancienne image chargée
    }
    return Image_optimisee; //On retourne l'image optimisée
}

/* Pour applliquer une surface sur une autre à partir de la position en haut à gauche (y,x) (y pour l'ordonnée et x pour l'abscisse)*/
void appliquer_surface(int y, int x, SDL_Surface *source, SDL_Surface *destination)
{
    SDL_Rect POS;                                     /*Pour définir une zone rectangulaire commençant en haut à gauche*/
    POS.x = x;                                        /*position x de depart en haut à gauche*/
    POS.y = y;                                        /*position y de depart en haut à gauche*/
    SDL_BlitSurface(source, NULL, destination, &POS); //On applique toute la surface source => destination
}

/* Fonction qui permet de recuperer la valeur d'un pixel d'une image, à une position (y,x) donnée (y pour l'ordonnée et x pour l'abscisse). 
   Ce qui permettrait ensuite de recupérer les valeurs des composant RGB du pixel via la fonction SDL_GetRGB.*/
Uint32 getpixel(SDL_Surface *surface, int y, int x)
{
    int bpp = surface->format->BytesPerPixel; /*Pour obtenir l'encodage des pixels de l'image*/
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    switch (bpp)
    {
    case 1:
        return *p;

    case 2:
        return *(Uint16 *)p;

    case 3:
        if (SDL_BYTEORDER == SDL_BIG_ENDIAN) //L'octet le plus fort est mis à l'adresse mémoire la plus petite
            return p[0] << 16 | p[1] << 8 | p[2];
        else //L'octet le plus faible est mis à l'adresse mémoire la plus petite
            return p[0] | p[1] << 8 | p[2] << 16;
    case 4:

        return *(Uint32 *)p;

    default:
        return 0;
    }
}

Uint32 setpixelMsb(Uint32 PIXEL, Uint8 r, Uint8 g, Uint8 b)
{

    PIXEL = PIXEL ^ ((Uint32)(r & 15) << 20);

    PIXEL = PIXEL ^ ((Uint32)(g & 15) << 12);

    PIXEL = PIXEL ^ ((Uint32)(b & 15) << 4);

    return PIXEL;
}

Uint32 setpixelLsb(Uint32 PIXEL, Uint8 r, Uint8 g, Uint8 b)
{
    PIXEL = PIXEL ^ ((Uint32)(r & 15) << 16);

    PIXEL = PIXEL ^ ((Uint32)(g & 15) << 8);

    PIXEL = PIXEL ^ ((Uint32)(b & 15));

    return PIXEL;
}

/*Fonction qui recherche une image cachée dans une autre image*/
void recherche_image_cachee(SDL_Surface *IMAGE_MERE, SDL_Surface *image_cachee)
{

    /*ATTENTION : lisez attentivement !!!

   Vous aurez besoin de deux pixels de type Uint32 (PIXEL1 et PIXEL2). 
   On va dire PIXEL1 contiendra le pixel en cours d'utilisation de l'image mère et PIXEL2 servira à préparer les valeurs du pixel de l'image fille avant son intégration dans la surface via un pointeur.

   Il faut parcourir l'image mère de haut en bas et de gauche à droite pour récupérer les deux pixels l'un après l'autre et extraire les composants RGB.
   Pour celà, vous utiliserez la fonction fournie getpixel pour récupérer le pixel de l'image mère au fur et à mésure.
   Vous utiliserez aussi la fonction SDL_GetRGB pour récupérer les composants RGB (de type Uint8) du pixel de l'image mère en cours, qui vont nous servir à constituer la moitié du PIXEL2.

   Une fois le PIXEL2 (RGB) en cours de l'image fille est prêt il faut l'intégrer dans l'image fille à bonne coordonnée.

   Pour celà, vous aurez besoin d'un pointeur de type Uint8* pour balayer et indexer les contenus des pixels de l'image cachée. Les valeurs p[0], p[1] et p[2] seront mis à jour via les octets du PIXEL2 calculés depuis les deux pixels de l'image mère. Vous pouvez vous inspirer du code de la fonction "getpixel" pour cette partie.

   Vous pouvez rajouter d'autres variables si nécessaire pour le bon déroulement de la fonction comme par exemple les tailles de l'image mère, etc.*/

    Uint32 PIXEL1 = 0, PIXEL2 = 0;
    Uint8 r = 0, g = 0, b = 0;

    Uint8 *p;
    int bpp = image_cachee->format->BytesPerPixel, x_f;

    for (int i = 0; i < IMAGE_MERE->h; ++i)
    {
        x_f = 0;
        for (int j = 0; j < IMAGE_MERE->w; ++j)
        {
            PIXEL2 = 0;

            PIXEL1 = getpixel(IMAGE_MERE, i, j);
            SDL_GetRGB(PIXEL1, IMAGE_MERE->format, &r, &g, &b);
            PIXEL2 = setpixelMsb(PIXEL2, r, g, b);

            PIXEL1 = getpixel(IMAGE_MERE, i, ++j);
            SDL_GetRGB(PIXEL1, IMAGE_MERE->format, &r, &g, &b);
            PIXEL2 = setpixelLsb(PIXEL2, r, g, b);

            p = (Uint8 *)image_cachee->pixels + i * image_cachee->pitch + x_f * bpp; /*positionnement du pointeur sur le pixel de l'image fille, afin de pouvoir changer sa valeur*/
            switch (bpp)                                                             /*Pour stocker les octets dans le bon format*/
            {
            case 1:
                *p = PIXEL2;
                break;

            case 2:
                *(Uint16 *)p = PIXEL2;
                break;

            case 3:
                if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
                {
                    p[0] = (PIXEL2 >> 16) & 255;
                    p[1] = (PIXEL2 >> 8) & 255;
                    p[2] = PIXEL2 & 255;
                }
                else
                {
                    p[0] = PIXEL2 & 255;
                    p[1] = (PIXEL2 >> 8) & 255;
                    p[2] = (PIXEL2 >> 16) & 255;
                }
                break;

            case 4:
                *(Uint32 *)p = PIXEL2;
                break;
            }
            ++x_f;
        }
    }
}

/*Fonction qui recherche le texte caché dans l'image fille*/
void recherche_texte_cache_dans_image(SDL_Surface *image, char *TEXTE)
{
    int x_m, y_m;
    Uint32 PIXEL1;
    Uint8 R, G, B;
    char caractere;

    int cpt = 0;

    y_m = 0;
    while (y_m < image->h)
    {
        x_m = 0;
        while (x_m < image->w)
        {
            PIXEL1 = getpixel(image, y_m, x_m);            /*récupération du pixel de l'image mère*/
            SDL_GetRGB(PIXEL1, image->format, &R, &G, &B); /*Récupération des composants RGB du pixel de l'image mère*/

            caractere = 0;
            TEXTE[cpt++] = caractere | (R & 3) << 5 | (G & 3) << 3 | (B & 7);
            ++x_m;
        }
        ++y_m;
    }
}

/*Fonction qui affiche un texte sur la sortie standard*/
void affichage_texte(char *TEXTE)
{
    printf("-----------------------------------------------------------------------------------------------\n");
    printf("%s\n", TEXTE);
    printf("-----------------------------------------------------------------------------------------------\n");
}

int main(int argc, char *argv[])
{
    int LARGEUR_ECRAN, HAUTEUR_ECRAN, CODAGE, PAUSE;
    LARGEUR_ECRAN = 1300;
    HAUTEUR_ECRAN = 650;
    CODAGE = 24; //8x3=24 bits / pixel couleur
    char *TEXTE;
    SDL_Surface *ecran = NULL;        //déclaration d'une surface d'écran de base (sur laquelle on va travailler)
    SDL_Surface *IMAGE = NULL;        //déclaration d'une surface (pour l'image qui cache)
    SDL_Surface *image_cachee = NULL; //Déclaration d'une autre surface (pour l'image cachée)

    SDL_Event event; //Pour gérer les evénements type clic de souris

    ecran = SDL_SetVideoMode(LARGEUR_ECRAN, HAUTEUR_ECRAN, CODAGE, SDL_SWSURFACE); //Initialisation du mode video
    SDL_WM_SetCaption("Steganalyse Image BMP", NULL);                              //Mise en place de la barre caption nommée "Steganalyse Image BMP"

    IMAGE = load_image("tiger_stegano.bmp"); //Chargement de l'image mère contenant les informations cachées

    appliquer_surface(0, 0, IMAGE, ecran); //On applique l'image mère sur l'écran de base au coin haut gauche (0,0)

    SDL_Flip(ecran); //pour mettre à jour l'écran et faire apparaitre la nouvelle surface appliquée juste avant

    PAUSE = 1;
    while (PAUSE)
    {
        SDL_WaitEvent(&event); //attend qu'un événement se produise
        switch (event.type)
        {
        case SDL_MOUSEBUTTONUP: // en cas de Clic de la souris
            if (event.button.button == SDL_BUTTON_LEFT)
            {
                PAUSE = 0; /*Pour ensuite sortir de la boucle et conituer le programme*/
            }
        }
    }

    image_cachee = SDL_CreateRGBSurface(0, 400, 555, 24, 0, 0, 0, 0); //Création d'une surface RGB 150x250 (24 bits/pixel)

    recherche_image_cachee(IMAGE, image_cachee); //on cherche l'image cachée dans l'image mère

    printf("L'image cachée est la suivante :\n");
    appliquer_surface(0, 850, image_cachee, ecran); //On applique l'image sur l'écran à la position (y=0 et x=350)
    SDL_Flip(ecran);                                //pour mettre à jour l'écran et faire apparaitre la nouvelle surface appliquée précédemment

    PAUSE = 1;
    while (PAUSE) /*Pour faire une pause sur l'écran et observer */
    {
        SDL_WaitEvent(&event); //attend qu'un événement se produise
        switch (event.type)
        {
        case SDL_MOUSEBUTTONUP:                         // en cas de Clic de la souris
            if (event.button.button == SDL_BUTTON_LEFT) //Si on clique sur le bouton gauche de la souris
            {
                PAUSE = 0;
            }
        }
    }

    /*Recherche puis affichage du texte caché dans une image*/
    TEXTE = malloc(sizeof(char) * 222000);
    recherche_texte_cache_dans_image(image_cachee, TEXTE);
    printf("Le texte caché est le suivant :\n");
    affichage_texte(TEXTE);

    SDL_FreeSurface(IMAGE);
    SDL_FreeSurface(image_cachee);
    SDL_FreeSurface(ecran);
    free(TEXTE);
    SDL_Quit();

    return EXIT_SUCCESS;
}
