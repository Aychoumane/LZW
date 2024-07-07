//Ichou Aymane L3B 21007668 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "ima.h"

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

//Fonction qui permet d'initialiser un dictionnaire, avec un certain nombre d'éléments 
dictionnaire_t init_dico(int nb_elem){
	dictionnaire_t dictionnaire ; 
	dictionnaire.dico = malloc(sizeof(couple_t)* nb_elem) ; 
	dictionnaire.nb_element = 0 ; 
	dictionnaire.nb_max = nb_elem ; 
	return dictionnaire;
}

//Fonction qui free un dictionnaire
void free_dico(dictionnaire_t * dico){
	if (dico == NULL){
		printf("Libération inutile \n"); 
	}
	free(dico->dico); 
}

//Fonction d'impression, affiche "clé -> valeur" , présent dans le dictionnaire
void print_dico(dictionnaire_t  dico){
	int i ;
	printf("-----Impression du dictionnaire-----\n") ; 
	for(i=0 ; i< dico.nb_element ; i++){
		printf("%s -> %d \n", dico.dico[i].cle , dico.dico[i].valeur) ; 
	}
	printf("-----Fin de l'impression, %d éléments trouvés-----\n" , dico.nb_element) ; 
}

//Fonction d'impression, affiche "clé -> valeur" , présent dans le dictionnaire

void print_dico_t(dictionnaire_t * dico){
	int i ;
	printf("-----Impression du dictionnaire-----\n") ; 
	for(i=0 ; i< dico -> nb_element ; i++){
		printf("%s -> %d \n", dico->dico[i].cle , dico->dico[i].valeur) ; 
	}
	printf("-----Fin de l'impression, %d éléments trouvés-----\n" , dico->nb_element) ; 
}

//Fonction qui ajoute un élément à un dictionnaire_t 
//Gère aussi le realloc pour augmenter la taille du dictionnaire si besoin 
void add_elem_dico(dictionnaire_t * dico , char * chaine , int valeur){
	if(dico -> nb_element == dico -> nb_max){
		int nouvelle_taille = dico->nb_max ; 
		printf("Augmentation de la taille du dictionnaire.\n"); 
		dico->dico = realloc(dico->dico , nouvelle_taille *sizeof(couple_t)); 
		if(dico->dico == NULL){
			fprintf(stderr, "Réallocation de mémoire échouée.\n");
		}
		dico->nb_max += nouvelle_taille ; 
	}
	couple_t temp  ; 
	temp.cle = malloc(sizeof(char) * (strlen(chaine) + 1) ); 
	strcpy(temp.cle, chaine) ;  
	temp.valeur = valeur ; 

	dico->dico[dico->nb_element] = temp ; 
	dico->nb_element += 1 ;  
}

//Fonction qui prend un dictionnaire_t et une clé(chaine de caractere) et renvoie la valeur associé, -1 sinon  

int val_find_dico(dictionnaire_t * dico , char * chaine){
	int i ; 
	for(i = 0; i < dico -> nb_element ; i++){
		if(strcmp(dico->dico[i].cle , chaine ) == 0) 
			return dico->dico[i].valeur ; 
	}
	//printf("Valeur non trouvé. \n") ; 
	return -1 ; 
}

//Fonction qui prend un dictionnaire_t et une valeur, et renvoie la clé associé, -1 sinon
//Fonction inverse de val_find_dico  

char * val_find_dico_with_val(dictionnaire_t * dico , int value){
	int i ; 
	for(i = 0; i < dico -> nb_element ; i++){
		if(dico->dico[i].valeur == value) 
			return dico->dico[i].cle ; 
	}
	//printf("Clé non trouvé. \n") ; 
	return "Clé non trouvé" ; 
}

//Fonction qui prend un dictionnaire_t et une clé(chaine de caractere) et renvoie un booleen:
//1 -> si vrai = que la clé est présente, 0 sinon  

int bool_find_dico(dictionnaire_t * dico , char * cle){
	int i ; 
	for(i = 0; i < dico -> nb_element ; i++){
		if(strcmp(dico->dico[i].cle , cle ) == 0) 
			return 1 ; 
	}
	//printf("Valeur non trouvé. \n") ; 
	return 0 ; 
}

//Fonction qui prend un dictionnaire_t et une valeur et renvoie un booleen:
//1 -> si vrai = que la valeur est présente, 0 sinon 
//Fonction inverse de bool_find_dico 

int bool_find_dico_with_value(dictionnaire_t * dico , int value){
	int i ; 
	for(i = 0; i < dico -> nb_element ; i++){
		if(dico->dico[i].valeur == value ) 
			return 1 ; 
	}
	//printf("Valeur non trouvé. \n") ; 
	return 0 ; 
}


//Fonction qui renvoie le nombre de chiffre d'un nombre, exemple 123 -> 3 / 34 -> 2 / 1000-> 4 

int nb_of_chiffre(int nombre){
    int count = 0;
    // Si le nombre est 0, il a un chiffre
    if (nombre == 0) {
        return 1;
    }
    while (nombre != 0) {
        nombre = nombre / 10;
        ++count;
    }
    return count;
}

//Fonction qui prend un nombre et le transforme en sa chaîne de caractère 123 -> "123"

char * int_to_string(int nombre){
	int nb_chiffre = nb_of_chiffre(nombre) ; 
	char * temp = malloc(sizeof(char) * (nb_chiffre + 1)) ; 
	sprintf(temp, "%d" , nombre); 
	/*printf("Le résultat est : %s \n", temp) ;*/
	return temp ; 
}

void remove_some_character(char *str, int nb) {
    int length = strlen(str);
    if(nb > length){
    	printf("error, trop de caractères à enlever !\n") ; 
    }

    if (length > 0) {
        // Déplacer le caractère de fin de chaîne d'une position vers la gauche
        str[length - nb] = '\0';
    }
}

//Fonction qui prends une chaine formaté séparé de '|', et renvoie un tableau d'entiers
tab_t format_char_to_tab(char * chaine){
	if (chaine == NULL){
		exit(1); 
	}
	int taille = 1 ; 
	int index = 0 ; 
	int i ; 
	tab_t res ; 

	char delimiteur = '|' ; 

	//On compte le nombre de valeur entre |
	for(i=0 ; i < strlen(chaine) ; i++){
		if(chaine[i] == delimiteur ){
			taille++ ; 
		}
	}
	res.taille = taille ; 
	res.tab = malloc(sizeof(*res.tab) * taille) ; 
	if(res.tab == NULL){
		printf("Allocation echoué \n") ; 
		exit(1); 
	}
	//printf("taille ici  = %d \n", taille) ; 

	char * tempi = malloc(sizeof(char) * strlen(chaine));
	strcpy(tempi,chaine); 
	char *token = strtok((char *)tempi, &delimiteur); 

	while (token != NULL) {
        // Conversion du token en entier et stockage dans le tableau
        res.tab[index] = atoi(token);

        // Obtenir le prochain token
        token = strtok(NULL, &delimiteur);
        index++; 
    }
	
	/*for(i = 0 ; i< taille ; i++){
		printf("%d \n", res[i] ); 
	}
	*/

	return res ; 
}

//Fonction qui prend une chaine formaté de | et renvoie que la premiere valeur. 
//"123|234|234" -> "123" , ou "123" -> "123"
char* premiere_valeur(char* chaine) {
    if (chaine == NULL) {
        fprintf(stderr, "Chaine non valide\n");
        return NULL;
    }

    // Utilisation de strtok pour extraire la première valeur
    char* premiere = strtok(chaine, "|");

    // Vérification si la première valeur existe
    if (premiere == NULL) {
        fprintf(stderr, "Aucune valeur trouvée\n");
        return NULL;
    }

    // Allouer de la mémoire pour la première valeur et la copier
    char* resultat = malloc(strlen(premiere) + 1);
    if (resultat == NULL) {
        perror("Allocation de mémoire échouée");
        exit(EXIT_FAILURE);
    }
    strcpy(resultat, premiere);

    return resultat;
}

int nombre_elements(char *chaine) {
	if(chaine == NULL){
		return 0 ; 
	}
    int nombre = 1; 
    for (int i = 0; chaine[i] != '\0'; i++) {
        if (chaine[i] == '|') {
            nombre++;
        }
    }
    return nombre;
}

//Fonction qui permet de réordonner les couleurs ensemble de façon à avoir des suites de RGB 
//Fonction inverse de tri_color
GLubyte* ord_RRRGGGBBB_to_RGBRGBRGB(int* tab, int taille) {
	if(taille % 3 != 0){
		printf("Erreur de taille dans la fonction \"ord_RRRGGGBBB_to_RGBRGBRGB\" \n"); 
		exit(EXIT_FAILURE);
	}
    int i;
    GLubyte* res = malloc(sizeof(*res) * taille);
    int taille_div = taille / 3;

    for (i = 0; i < taille_div; i++) {
        res[i * 3] = tab[i];
        res[i * 3 + 1] = tab[i + taille_div];
        res[i * 3 + 2] = tab[i + taille_div + taille_div];
    }

   /* for (int i = 0; i < taille; i++)
        printf("%d \n", res[i]);
*/
    return res;
}


//Fonction qui prend un tableau, et qui va appliquer l'algo LZW et écrire dans un fichier la compression
//Pour cela, il est important d'initialiser le dictionnaire avec toutes les valeurs unaires possibles
//Par exemple, dans le cas de RGB, il faut au préalable enregistrer toutes les valeurs de 0 à 255
char * add_tab_to_dico_and_write(Image * image ,  dictionnaire_t * dico, char * fichier_res){
	int i ; 
	char * c ; //Nouveau char à chaque tour 
	char * p ; 
	char res[100000]  ; 
	int taille_tab = (image->sizeX * image->sizeY) * 3 ; 
	printf("taille tab vaut %d \n", taille_tab) ; 
	image-> data = tri_color(image) ;
	/*printf("parcours de data : \n"); 
	for(i = 0 ; i < taille_tab ; i++)
		printf("%d : %d \n",i, image-> data[i]) ; */
	FILE *fichier = fopen (fichier_res , "w");
  	if (fichier == NULL) {
  		exit(0);
  	}
  	fprintf(fichier, "taille_x : %ld \n", image->sizeX);
	fprintf(fichier, "taille_y : %ld \n", image->sizeY);
	p = int_to_string(image->data[0]) ; 

	for(i = 1 ; i< taille_tab ; i++){
		c = int_to_string(image->data[i]) ; 
		strcpy(res,"") ;
		strcat(res, p) ;  
		//res = p ;  
		strcat(res,"|") ; 
		strcat(res,c) ; 

		if(bool_find_dico(dico , res) == 1){
			strcat(p,"|") ; 
			strcat(p,c) ; 
		}
		else{
			add_elem_dico(dico, res, dico -> nb_element ); 
			fprintf(fichier, "<%d>", val_find_dico(dico, p)); 
			strcpy(p,"") ;
			strcat(p,c) ; 			
		}
		if(i % 10000 == 0){
			printf("Compression à %.2f%% \n", ((float)i / taille_tab) * 100);
		}
	}
	
	fprintf(fichier, "<%d>", val_find_dico(dico, p));
	/*printf("Affichage du dictionnaire de compression: \n"); 
	print_dico_t(dico) ; */
	printf("Compression terminée. \n") ; 
    fclose(fichier); // Fermer le fichier une fois l'écriture terminée 
    return fichier_res; 
}



Image * decompression_lzw(dictionnaire_t * new_dico,  char * fichier){
	FILE * fichier_comp = fopen(fichier, "r"); 
	int * res ; 
	unsigned long taille_x , taille_y ; 
	int val_act , i;  

	int taille = 0 ;  
	tab_t temp_tab ;
	int index = 0 ; 

	fscanf(fichier_comp, "taille_x : %ld \n", &taille_x);
	printf("Taille de l'image en x : %ld \n", taille_x); 
	fscanf(fichier_comp, "taille_y : %ld \n", &taille_y);
	printf("Taille de l'image en y : %ld \n", taille_y); 
	
	Image * rim = malloc(sizeof(Image)) ; 
	rim -> sizeX = taille_x ; 
	rim -> sizeY = taille_y ; 

	int precedent ;
	fscanf(fichier_comp, "<%d>", &precedent);
	char chaine_temp1[10000]; 
	char chaine_temp2[10000]; 
	taille += nombre_elements(val_find_dico_with_val(new_dico, precedent)) ; 

	//Construction du dictionnaire + calcul de la taille du tableau qui va être renvoyé 
	while (fscanf(fichier_comp, "<%d>", &val_act) == 1 ) {
		//printf("val_act = %d \n", val_act) ; 
		//Si la valeur est trouvé, on concatène l'element précédent avec le premier caractere actuel 
	   	if(bool_find_dico_with_value(new_dico, val_act) == 1){
	   		strcpy(chaine_temp1, val_find_dico_with_val(new_dico, precedent)) ; 
	   		strcpy(chaine_temp2, val_find_dico_with_val(new_dico, val_act)) ; 
	   		strcpy(chaine_temp2, premiere_valeur(chaine_temp2)); 
	   		strcat(chaine_temp1,"|") ; 
	   		strcat(chaine_temp1, chaine_temp2) ; 
	   		add_elem_dico(new_dico, chaine_temp1 , new_dico -> nb_element); 
	   	}
	   	//Sinon, on concatène l'element precedent avec son premier caractere 
	   	else{	 
	   		strcpy(chaine_temp1, val_find_dico_with_val(new_dico, precedent)) ; 
	   		strcpy(chaine_temp2, val_find_dico_with_val(new_dico, precedent)) ; 
	   		strcpy(chaine_temp2, premiere_valeur(chaine_temp2)) ; 
	   		strcat(chaine_temp1,"|") ; 
	   		strcat(chaine_temp1, chaine_temp2) ; 
	   		add_elem_dico(new_dico, chaine_temp1 , new_dico -> nb_element); 
	   	}
	   	taille += nombre_elements(val_find_dico_with_val(new_dico, val_act)) ;
    	precedent = val_act ;
    	if(taille %10000 == 0){
   				printf("Construction à %.2f%% \n", ((float)taille / (taille_x*taille_y*3)) * 100);
   			}
   	}
   	printf("Construction du dictionnaire terminée \n") ; 
   /*	printf("NEW DICO \n") ; 
   	print_dico_t(new_dico); */

   	res = malloc(sizeof(int) * taille) ; 
   	//On remet le curseur au bon endroit. 
   	fseek(fichier_comp, 0, SEEK_SET);
   	fscanf(fichier_comp, "taille_x : %ld \n", &taille_x);
	fscanf(fichier_comp, "taille_y : %ld \n", &taille_y);

   	//Le dictionnaire est construit, il suffit de chercher les valeurs 
   	while (fscanf(fichier_comp, "<%d>", &val_act) == 1 ) {
   		//printf("------val_act------- : %d\n", val_act) ; 
   		//printf("valeur trouvé dans le dico : %s \n ", val_find_dico_with_val(new_dico, val_act)); 
   		temp_tab = format_char_to_tab(val_find_dico_with_val(new_dico, val_act)); 
   		for(i=0 ; i< temp_tab.taille ; i++){
   			res[index+i] = temp_tab.tab[i] ; 
   			//printf("res vaut : %d \n", res[index+i]); 
   			if(index %10000 == 0){
   				printf("Recherche à %.2f%% \n", ((float)index / taille) * 100);
   			}
   		}
   		index+= temp_tab.taille; 
   		free(temp_tab.tab) ; 
   		
   	}

   	rim -> data = ord_RRRGGGBBB_to_RGBRGBRGB(res, taille) ; 
/*
   	printf("Impression : \n"); 
   	for(i=0 ; i< taille ; i++){
   		printf("%d : %d \n" ,i, rim->data[i]) ; 
   	}*/
   	printf("Décompression terminée. \n") ; 
   	fclose(fichier_comp);
   	return rim ; 
}



