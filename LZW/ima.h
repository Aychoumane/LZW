#include <stdio.h> 
#include <stdlib.h>
#include <assert.h>

/* pour Bocal */
#include <GL/gl.h> 
#include <GL/glut.h>
#include <GL/freeglut.h>  

/* pour Mac */
// #include <GLUT/glut.h>




struct Image {
    unsigned long sizeX;
    unsigned long sizeY;
    GLubyte *data;
};
typedef struct Image Image;
typedef unsigned short utab [3][3][3];

struct comp{
    GLubyte pixel ; // Valeur entre 0 et 255 
    int repetition; // Nombre de fois que la meme valeur se suit 
    int type; // 0 -> R / 1 -> G / 2 -> B
}; 
typedef struct comp comp_t;

struct comp_tab{
    int taille ; 
    comp_t * tab;
};
typedef struct comp_tab comp_tab_t;

int ImageLoad_PPM(char *filename, Image *image);
void imagesave_PPM(char *filename, Image *image);
void upsidedown(Image *im);
void vert(Image *image);
void vert_moy(Image *image); 
void vert_uniforme(Image *image);
void gris_uniforme (Image *image);
void rouge_origin(Image *image);
void swap_green_red(Image *image);
GLubyte * tri_color(Image *im);
comp_tab_t RLE_naif(GLubyte * tab_of_tri_color, Image * im, char * name_file); 
GLubyte * decompression(char * nom_fichier); 


