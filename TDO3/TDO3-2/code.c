


/*Fonction qui recherche une image cachée dans une autre image*/
void recherche_image_cachee(SDL_Surface * IMAGE_MERE, SDL_Surface * image_cachee)
{
  int x_f, x_m, y_m, larg_img_mere, hau_img_mere;
  int bpp = image_cachee->format->BytesPerPixel; /*Nombre d'octets/pixel de la surface de l'image cachée*/
  Uint32 PIXEL1, PIXEL2; /*PIXEL1 sera utilisé pour l'image mère et PIXEL2 pour l'image cachée*/
  Uint8 * p;                /*pointeur pour balayer et indexer les contenus des pixels de l'image cachée*/
  Uint8 R, G, B;            /*composants R=>rouge, G=>vert et B=> bleu pour le pixel PIXEL1 de l'image mère*/
  larg_img_mere = IMAGE_MERE->w; /*Pour obtenir la largeur de l'image mère*/
  hau_img_mere = IMAGE_MERE->h;  /*Pour obtenir la hauteur de l'image mère*/
  //printf("%d %d\n", larg_img_mere, hau_img_mere);
  y_m=0;
 
  while (y_m < hau_img_mere)
  {
    x_m=0; x_f=0;
    while (x_m < larg_img_mere)
    {
      
      PIXEL1 = getpixel(IMAGE_MERE, y_m, x_m); /*récupération du pixel de l'image mère*/
      SDL_GetRGB(PIXEL1, IMAGE_MERE->format, &R, &G, &B); /*Récupération des composants RGB du pixel de l'image mère*/
      
      PIXEL2=0;
      
      PIXEL2 = PIXEL2 ^ ((Uint32)(R&15) << 20);
      
      PIXEL2 = PIXEL2 ^ ((Uint32)(G&15) << 12);
      
      PIXEL2 = PIXEL2 ^ ((Uint32)(B&15) << 4);
      /*Fin de la récupération des bits de poids fort de l'image fille*/
      
      x_m++; /*pour aller au pixel suivant de l'image mère*/
      PIXEL1 = getpixel(IMAGE_MERE, y_m, x_m); /*récupération du pixel de l'image mère*/
      SDL_GetRGB(PIXEL1, IMAGE_MERE->format, &R, &G, &B); /*Récupération des composants RGB du pixel de l'image mère*/
     

      /*Début de la récuperation des bits de poids faible initialement cachés de l'image fille pour chaque composant couleur*/
     
      PIXEL2 = PIXEL2 ^ ((Uint32)(R&15) << 16);
      
      PIXEL2 = PIXEL2 ^ ((Uint32)(G&15) << 8);
      
      PIXEL2 = PIXEL2 ^ ((Uint32)(B&15));
      /*Fin de la récupération des bits de poids faible de l'image fille*/
     /*A ce stade la valeur du pixel "PIXEL2" est prête à être injectée dans l'image fille. Il faut donc l'affecter à la surface de l'image cachée*/
      /*
        image_cachee->pixels contient l'adresse du premier composant couleur (ici BLEU) du premier pixel de l'image cachée. 
        Avec ce pointeur on va pouvoir balayer l'image comme une suite d'octets RGB correspondant à chaque pixel.
      */
     
     p = (Uint8 *)image_cachee->pixels + y_m * image_cachee->pitch + x_f * bpp; /*positionnement du pointeur sur le pixel de l'image fille, afin de pouvoir changer sa valeur*/
      switch (bpp) /*Pour stocker les octets dans le bon format*/
      {
	case 1:
	  *p = PIXEL2;
	  break;
	  
	case 2:
	  *(Uint16 *)p = PIXEL2;
	  break;
	  
	case 3:
	  if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
	  {
	    p[0] = (PIXEL2 >> 16) & 255; p[1] = (PIXEL2 >> 8) & 255; p[2] = PIXEL2 & 255;
	  }
	  else
	  {
	    p[0] = PIXEL2 & 255; p[1] = (PIXEL2 >> 8) & 255; p[2] = (PIXEL2 >> 16) & 255;
	  }
          break;
	  
	case 4:
	  *(Uint32 *)p = PIXEL2;
	  break;
      }
     x_m++; x_f++;
    }
    
    y_m++;
  }

}
