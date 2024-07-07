#include <stdlib.h>
#include <stdio.h>
#include <string.h>


//hsv en anglais , tsv en français 
struct tsv{
	int t ; // 0 à 360
	float s ; // entre 0 et 1 
	float v ; // Entre 0 et 1
};
typedef struct tsv tsv_t ; 


float min_of_two(float a, float b){
	if(a<b)
		return a ; 
	else
		return b ; 
}
float min_of_three(float a , float b , float c ){
	float temp_min ;
	temp_min = min_of_two(a,b) ; 
	temp_min = min_of_two(temp_min,c);
	return temp_min; 
}

float max_of_two(float a, float b){
	if(a>b)
		return a ; 
	else
		return b ; 
}
float max_of_three(float a , float b , float c ){
	float temp_max ;
	temp_max = max_of_two(a,b) ; 
	temp_max = max_of_two(temp_max,c);
	return temp_max; 
}


tsv_t rgb_to_hsv(int r , int g , int b ){
	//RGB doivent etre entre 0 et 1 
	float rf = r / 255.0 ; 
	float gf = g / 255.0 ; 
	float bf = b / 255.0 ; 

	float min = min_of_three(rf,gf,bf) ; 
	float max = max_of_three(rf,gf,bf) ; 
	tsv_t res ; 

	//Calcul de la composante T 
	if(min == max){
		res.t = 0 ; 
	}
	else if(max == rf){
		res.t = (int)(60 * ((gf - bf) / (max-min)) + 360) % 360 ; 
	}
	else if(max == gf){
		res.t = (60 * ((bf - rf) / (max-min)) + 120) ; 
	}
	else{
		res.t = (60 * ((rf - gf) / (max-min)) + 240); 
	}

	//Calcul de la composante S 
	if(max == 0){
		res.s = 0 ; 
	}
	else{
		res.s = 1 - (min/max) ; 
	}

	//Calcul de la composante V 
	res.v = max ; 
	return res ; 

}




int main(){
	printf("Minimoum : %f \n", min_of_three(11,7,9)) ; 
	printf("Maximoum : %f \n", max_of_three(25,13,12)); 
	tsv_t test = rgb_to_hsv(147,50,147) ; 
	printf("H : %d , S = %f , V = %f \n", test.t , test.s , test.v ) ; 


	return EXIT_SUCCESS;
}