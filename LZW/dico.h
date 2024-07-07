//Ichou Aymane L3B 21007668 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>



struct couple{
	char * cle;
	int valeur ; 
};
typedef struct couple couple_t ; 


struct dictionnaire{
	couple_t * dico ; 
	int nb_element;
	int nb_max ; 
};
typedef struct dictionnaire dictionnaire_t ; 

struct tab{
	int taille ; 
	int * tab ; 
};
typedef struct tab tab_t ; 


dictionnaire_t init_dico(int nb_elem);
void free_dico(dictionnaire_t * dico) ; 
void print_dico(dictionnaire_t  dico);
void print_dico_t(dictionnaire_t * dico);
void add_elem_dico(dictionnaire_t * dico , char * chaine , int valeur);
int val_find_dico(dictionnaire_t * dico , char * chaine);
char * val_find_dico_with_val(dictionnaire_t * dico , int value);
int bool_find_dico(dictionnaire_t * dico , char * cle);
int bool_find_dico_with_value(dictionnaire_t * dico , int value);
int nb_of_chiffre(int nombre);
char * int_to_string(int nombre);
void remove_some_character(char *str, int nb) ;
tab_t format_char_to_tab(char * chaine);
char* premiere_valeur(char* chaine) ;
int nombre_elements(char *chaine); 
GLubyte* ord_RRRGGGBBB_to_RGBRGBRGB(int* tab, int taille) ; 
char * add_tab_to_dico_and_write(Image * image ,  dictionnaire_t * dico, char * fichier_res) ; 
Image * decompression_lzw(dictionnaire_t * new_dico,  char * fichier);