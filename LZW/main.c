#include <unistd.h>     
#include <math.h>
#include "ima.h"
#include "dico.h"

Image *image;

#define ESCAPE 27

void Keyboard(unsigned char key, int x, int y)  {
  switch(key){
  case ESCAPE :
    exit(0);                   
    break;
  default:
    fprintf(stderr, "Unused key\n");
  }
}

void Mouse(int button, int state, int x, int y) {
  switch(button){
  case GLUT_LEFT_BUTTON:
    break;
  case GLUT_MIDDLE_BUTTON:
    break;
  case GLUT_RIGHT_BUTTON:
    break;    
  }
  glutPostRedisplay();
}

int Init(char *s) {
  image = (Image *) malloc(sizeof(Image));
  if (image == NULL) {
    fprintf(stderr, "Out of memory\n");
    return(-1);
  }
  if (ImageLoad_PPM(s, image)==-1) 
	return(-1);
  printf("tailles %d %d\n",(int) image->sizeX, (int) image->sizeY);
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glShadeModel(GL_FLAT);
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  glutReshapeWindow(image->sizeX, image->sizeY);
  
  return (0);
}
int ReInit() {
  /*
  if (ImageLoad_PPM(s, image)==-1) 
	return(-1);
  */
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glShadeModel(GL_FLAT);
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  glutReshapeWindow(image->sizeX, image->sizeY);
  
  return (0);
}

void Display(void) {
  glClear(GL_COLOR_BUFFER_BIT);
  //GLint w = glutGet(GLUT_WINDOW_WIDTH);
  //GLint h = glutGet(GLUT_WINDOW_HEIGHT);
  glDrawPixels(image->sizeX, image->sizeY, GL_RGB, GL_UNSIGNED_BYTE, 
	       image->data);

  glFlush();
}

void Reshape(int w, int h) {
  glViewport(0, 0, (GLsizei)w, (GLsizei) h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0.0, (GLdouble) w, 0.0, (GLdouble)h);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void menuFunc(int item) {
  char s[256];
  switch(item){
  case 0:
    free(image);
    exit(0);
    break;
  case 1:
    printf("Vert \n");
    vert(image);
    Display();
    break;
  case 2:
    printf("Vert uniforme \n");
    vert_uniforme(image);
    Display();
    break;
  case 3:
    printf("Gris uniforme \n");
    gris_uniforme(image);
    Display();
    break;
  case 4:
    printf("Swap red and green \n");
    swap_green_red(image);
    Display();
    break;
  case 5:
    printf("Entrer le nom pour l'image dans cette taille\n");
    scanf("%s", &s[0]);
    imagesave_PPM(s, image);
    break;
  case 6:
    printf("Taille de l image : %d %d\n", (int) image->sizeX, (int) image->sizeY);
    break;
  case 7:
    printf("Rouge origin \n");
    rouge_origin(image);
    Display();
    break;
  case 8:
    printf("Vert moyen \n");
    vert_moy(image);
    Display();
    break;
  case 9:
    printf("Compression RLE \n");
    char * name_fichier = "tableau.txt" ; 
    GLubyte* test = tri_color(image);
    comp_tab_t test_modif = RLE_naif(test, image, name_fichier ) ; 
    Display();
    break;
  case 10:
    printf("Compression LZW \n");
    //Init dico 
    char * name_fichier2 = "tableau2.txt" ;
    dictionnaire_t dictionnaire = init_dico(3000000) ;
    for(int i = 0 ; i < 256 ; i++){
      add_elem_dico(&dictionnaire , int_to_string(i) , i) ; 
    }
    //print_dico_t(&dictionnaire) ; 
    add_tab_to_dico_and_write(image ,&dictionnaire , name_fichier2) ; 
    //print_dico_t(&dictionnaire) ;
    Display();
    break;
  case 11:
    printf("Décompression LZW \n"); 
    char name_fichier3[] = "tableau2.txt" ;
    dictionnaire_t dictionnaire_decomp = init_dico(3000000) ;
    for(int i = 0 ; i < 256 ; i++){
      add_elem_dico(&dictionnaire_decomp , int_to_string(i) , i) ; 
    }
   /* print_dico_t(&dictionnaire_decomp) ; 
    for(int i=0 ; i < (image->sizeY * image ->sizeX) * 3 ; i++)
      printf("i vaut %d : %d \n", i , image->data[i]) ; */
    Image * new_img = decompression_lzw(&dictionnaire_decomp, name_fichier3); 
    
    Display();
    break;
  default:
    break;
  }
}

int main(int argc, char **argv) {  

  if (argc<2) {
    fprintf(stderr, "Usage : palette nom_de_fichier\n");
    exit(0);
  }

  glutInit(&argc, argv); 
  glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
  glutInitWindowSize(640,480);  
  glutInitWindowPosition(100, 100);  
  glutCreateWindow("VPUP8");  

  Init(argv[1]);

  glutCreateMenu(menuFunc);
  glutAddMenuEntry("Quit", 0);
  glutAddMenuEntry("Vert", 1);
  glutAddMenuEntry("Vert uniforme", 2);
  glutAddMenuEntry("Gris uniforme", 3);
  glutAddMenuEntry("Swap G and R", 4);
  glutAddMenuEntry("Save", 5);
  glutAddMenuEntry("Infos", 6);
  glutAddMenuEntry("Rouge", 7);
  glutAddMenuEntry("Vert Moy", 8);
  glutAddMenuEntry("Compression RLE", 9);
  glutAddMenuEntry("Compression LZW", 10);
  glutAddMenuEntry("Decompression LZW", 11);
  glutAttachMenu(GLUT_LEFT_BUTTON);


  glutDisplayFunc(Display);  
  glutReshapeFunc(Reshape);
  glutKeyboardFunc(Keyboard);
  
  glutMouseFunc(Mouse);

  glutMainLoop();  

  return 1;
}
