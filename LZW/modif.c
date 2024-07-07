/* Il s agit de prendre une image et de la modifier */
//Ichou Aymane L3B 21007668 
#include "ima.h"
#include <limits.h>

//Fonction qui transforme l'image en vert 
void vert(Image *im){
  GLubyte *crt,val1,val2;
  int i, nb_pixels;
  nb_pixels = im->sizeX * im->sizeY;
  val1=0;
  val2=255;
  for (crt=im->data,i=0;i<nb_pixels;i++){
    *crt++=val1;
    *crt++=val2;
    *crt++=val1;
  }
}

//Fonction qui fait la moyenne des verts 
void vert_moy(Image *im){
  GLubyte *crt,val1;
  int i, nb_pixels;
  int temp;
  nb_pixels = im->sizeX * im->sizeY;
  val1=0;
  for (crt=im->data,i=0;i<nb_pixels;i++){
    temp = (*crt + *(crt+1) + *(crt+2) ) ; 
    *crt++=val1;
    *crt++=temp;
    *crt++=val1;
  }
}


void vert_uniforme(Image *im){
  GLubyte *crt,val1;
  int i, nb_pixels;
  int temp;
  nb_pixels = im->sizeX * im->sizeY;
  val1=0;
  for (crt=im->data,i=0;i<nb_pixels;i++){
    temp = ( (*crt * 2 ) + (*(crt+1) * 5 )  + ( *(crt+2) * 1)  ) / 8  ; 
    *crt++=val1;
    *crt++=temp;
    *crt++=val1;
  }
}

//Fonction qui tranforme l'image en rouge 
void rouge_origin(Image *im){
  GLubyte *crt,val1;
  int i, nb_pixels;
  nb_pixels = im->sizeX * im->sizeY;
  val1=0;
  for (crt=im->data,i=0;i<nb_pixels;i++){
    crt++;
    *crt++=val1;
    *crt++=val1;
  }
}

//Transforme l'image en noir et blanc 
void gris_uniforme(Image *im){
  GLubyte *crt;
  int i, nb_pixels;
  int temp;
  nb_pixels = im->sizeX * im->sizeY;
  for (crt=im->data,i=0;i<nb_pixels;i++){
    temp = ( (*crt * 2 ) + (*(crt+1) * 5 )  + ( *(crt+2) * 1)  ) / 8  ; 
    *crt++=temp;
    *crt++=temp;
    *crt++=temp;
  }

}

//Fonction qui echange les valeurs des pixels rouge et vert 
void swap_green_red(Image *im){
  GLubyte *crt;
  int i, nb_pixels;
  int vert , rouge;
  nb_pixels = im->sizeX * im->sizeY;
  for (crt=im->data,i=0;i<nb_pixels;i++){
    rouge = *crt ;  
    vert =  *(crt+1) ;
    *crt++=vert;
    *crt++=rouge;
    *crt++=0;
  }
}

//Fonction qui permet de trier les pixels dans l'ordre RRRGGGBBB 
//Fonction inverse de ord_RRRGGGBBB_to_RGBRGBRGB dans 'dico.c'
GLubyte * tri_color(Image *im){
  GLubyte *crt;
  int i, nb_pixels;
  nb_pixels = im->sizeX * im->sizeY;
  GLubyte * result;
  result = malloc(3*nb_pixels*sizeof(GLubyte)); 

  for (crt=im->data,i=0;i<nb_pixels;i++){
   result[i] = *crt ; 
   crt++ ; 
   result[i+nb_pixels] = *crt ; 
   crt++ ; 
   result[i+nb_pixels+nb_pixels] = *crt;
   crt++ ; 
  }
  crt = im->data; 
  //printf("im data %d , res %d \n", *(crt+23) , result[nb_pixels+nb_pixels+7] ); 
  return result;
}


//Fonction qui permet d'appliquer l'algorithme de compression RLE, et envoie un GLubyte * 
comp_tab_t RLE_naif(GLubyte * tab_of_tri_color, Image * im , char * name_file){
  int i, nb_pixels;
  nb_pixels = im->sizeX * im->sizeY;
  comp_t temp ; 
  int index = 0 ;
  comp_tab_t res ; 
  res.tab = malloc(3*nb_pixels*sizeof(comp_t)) ; 

  temp.pixel = tab_of_tri_color[0] ;
  temp.repetition = 1 ;
  temp.type = 0 ;  

  res.tab[0] = temp ; 
  res.taille = 1 ; 
   //Concaténation de type Red 
  for(i=1 ; i< nb_pixels ; i++){
    if(tab_of_tri_color[i] == res.tab[index].pixel){
      res.tab[index].repetition++ ;
    }
    else{
      index++ ; 
      temp.pixel = tab_of_tri_color[i] ;
      temp.repetition = 1 ;
      temp.type = 0 ;
      res.tab[index] = temp ; 
      res.taille++ ; 
    }
  }
  index++ ; 
  
   //Concaténation de type Green 
  temp.pixel = tab_of_tri_color[nb_pixels] ;
  temp.repetition = 1 ;
  temp.type = 1 ;  

  res.tab[index] = temp ; 
  res.taille++ ; 

  for(i=nb_pixels+1 ; i< nb_pixels*2 ; i++){
    if(tab_of_tri_color[i] == res.tab[index].pixel){
      res.tab[index].repetition++ ;
    }
    else{
      index++ ; 
      temp.pixel = tab_of_tri_color[i] ;
      temp.repetition = 1 ;
      temp.type = 1 ;
      res.tab[index] = temp ; 
      res.taille++ ; 
    }
  }
  index++ ; 
  
  //Concaténation de type Blue 
  temp.pixel = tab_of_tri_color[nb_pixels*2] ;
  temp.repetition = 1 ;
  temp.type = 2 ;  

  res.tab[index] = temp ; 
  res.taille++ ; 

  for(i= nb_pixels*2 + 1 ; i< nb_pixels*3 ; i++){
    if(tab_of_tri_color[i] == res.tab[index].pixel){
      res.tab[index].repetition++ ;
    }
    else{
      index++ ; 
      temp.pixel = tab_of_tri_color[i] ;
      temp.repetition = 1 ;
      temp.type = 2 ;
      res.tab[index] = temp ; 
      res.taille++ ; 
    }
  }

  //Ecriture de la compression dans un fichier 
  FILE *fichier = fopen (name_file, "w");
  if (fichier != NULL) {
        for(int i = 0 ; i < res.taille ; i++){
          fprintf(fichier,"%d",res.tab[i].repetition); 
          fprintf(fichier,"|");
          fprintf(fichier,"%u",res.tab[i].pixel); 
          fprintf(fichier,"|");   
        }  
        fclose(fichier); // Fermer le fichier une fois l'écriture terminée
        printf("Écriture dans le fichier terminée.\n");
    } else {
        printf("Erreur lors de l'ouverture du fichier.\n");
    }

  return res ; 

}

//Fonction de décompression de RLE 
GLubyte * decompression(char * nom_fichier){
  GLubyte * res ; 
  int mult , pixel ; 
  int index = 0 ; 
  long long int nb_pixels = 0 ;  
  FILE *fichier = fopen (nom_fichier, "r");

  // Lecture expression par expression et calcul du nombre de pixel 
  while (fscanf(fichier, "%d|%d", &mult, &pixel) == 2 ) {
    fscanf(fichier,"%d|%d",&mult, &pixel) ; 
    printf("le couple trouvé vaut %d , %d \n ", mult , pixel) ; 
    //printf("%ld \n ",ftell(fichier));
    fseek(fichier,1, SEEK_CUR);
    nb_pixels = nb_pixels + mult ; 
  }

  //Creation du tableau de pixel 
  fseek(fichier,0,SEEK_SET) ; 
  printf("nb_pixels %lld \n ", nb_pixels); 
  res = malloc(sizeof(GLubyte) * nb_pixels) ; 

  //Recuperation et traitement de l'information pour reconstituer le tableau des pixel trié (R-> G ->B)
  while (fscanf(fichier, "%d|%d", &mult, &pixel) == 2 ) {
    //fscanf(fichier,"%d|%d",&mult, &pixel) ; 
    //printf("le couple trouvé vaut %d , %d \n ", mult , pixel) ; 
    for(int i = index ; i< index + mult; i++){
      res[i] = (GLubyte)pixel; 
    }
    index += mult ; 
    printf("fini\n"); 
    //printf("%ld \n ",ftell(fichier));
    fseek(fichier,1, SEEK_CUR);
  }

  for(int i = 0; i< nb_pixels ; i++){
    printf("%d = %d \n", i , res[i]); 
  }
  fclose(fichier); // Ferme le fichier

  int part = nb_pixels/3 ; 
  //Création d'un nouveau fichier contenant les pixels dans l'ordre (RGB->RGB->RGB ...)
  FILE *fichier_res = fopen ("fichier_res.txt", "w");
  if (fichier != NULL) {
        for(int i = 0 ; i < part ; i++){
          fprintf(fichier,"%d",res[i]); 
          fprintf(fichier,"%d",res[i+part]);
          fprintf(fichier,"%d",res[i+part+part]);
        }  
        fclose(fichier_res); // Fermer le fichier une fois l'écriture terminée
        printf("Écriture dans le fichier terminée.\n");
    } else {
        printf("Erreur lors de l'ouverture du fichier.\n");
    }

  return res ;
}

