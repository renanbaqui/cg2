/*
 * pinguim2.cpp
 *
 *  Created on: 29 de abril de 2021
 *      Author: Renan Almeida Baqui e Silvio Pereira dos Santos
 */
#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <GL/freeglut.h>
#include <windows.h>
#include <math.h>
#include <iostream> 	// biblioteca auxiliar para numeros aleatorios
#include <random>		// biblioteca auxiliar para numeros aleatorios
using namespace std;
// tamanho da janela inicial
GLint winWidth = 800, winHeight = 600;
// variavel de testes no teclado
GLfloat z = 1;

GLfloat moveping = 0.0, rotaping = 0.0;

GLint direcao = 2;



const double PI = 3.1415926535898;
void init();
void gelo()
{
	glColor3f(0.5, 0.5, 0.5);
	glBegin(GL_POLYGON); // Face posterior
	glNormal3f(0,0,1); // Normal da face
	glVertex3f(3.0, 0.25, 3.0);
	glVertex3f(-3.0, 0.25, 3.0);
	glVertex3f(-3.0, -0.25, 3.0);
	glVertex3f(3.0, -0.25, 3.0);
	glEnd();
	glBegin(GL_POLYGON); // Face frontal
	glNormal3f(0,0,-1); // Normal da face
	glVertex3f(3.0, 0.25, -3.0);
	glVertex3f(3.0, -0.25, -3.0);
	glVertex3f(-3.0, -0.25, -3.0);
	glVertex3f(-3.0, 0.25, -3.0);
	glEnd();
	glBegin(GL_POLYGON); // Face lateral esquerda
	glNormal3f(-1,0,0); // Normal da face
	glVertex3f(-3.0, 0.25, 3.0);
	glVertex3f(-3.0, 0.25, -3.0);
	glVertex3f(-3.0, -0.25, -3.0);
	glVertex3f(-3.0, -0.25, 3.0);
	glEnd();
	glBegin(GL_POLYGON); // Face lateral direita
	glNormal3f(1,0,0); // Normal da face
	glVertex3f(3.0, 0.25, 3.0);
	glVertex3f(3.0, -0.25, 3.0);
	glVertex3f(3.0, -0.25, -3.0);
	glVertex3f(3.0, 0.25, -3.0);
	glEnd();
	glBegin(GL_POLYGON); // Face superior
	glNormal3f(0,1,0); // Normal da face
	glVertex3f(-3.0, 0.25, -3.0);
	glVertex3f(-3.0, 0.25, 3.0);
	glVertex3f(3.0, 0.25, 3.0);
	glVertex3f(3.0, 0.25, -3.0);
	glEnd();
	glBegin(GL_POLYGON); // Face inferior
	glNormal3f(0,-1,0); // Normal da face
	glVertex3f(-3.0, -0.25, -3.0);
	glVertex3f(3.0, -0.25, -3.0);
	glVertex3f(3.0, -0.25, 3.0);
	glVertex3f(-3.0, -0.25, 3.0);
	glEnd();
}

void circulo(double raio)
{
	int pontos = 100;
  	double ang = 0;
  	int i = 0;
  	glBegin(GL_POLYGON);
  		for (i = 0; i < pontos; i++) {
  			ang = 2*PI*i / pontos;
  			glVertex2f(cos(ang)*raio, sin(ang)*raio);
  		}
  	glEnd();

}

void semiesfera(int escalay, int escalax, GLfloat r) {
   int i, j;
   GLfloat v[escalax*escalay][3];

   for (i=0; i<escalax; ++i)
   {
     for (j=0; j<escalay; ++j)
     {
       v[i*escalay+j][0]=r*cos(j*2*PI/escalay)*cos(i*PI/(2*escalax));
       v[i*escalay+j][1]=r*sin(i*PI/(2*escalax));
       v[i*escalay+j][2]=r*sin(j*2*PI/escalay)*cos(i*PI/(2*escalax));
     }
   }

   glBegin(GL_QUADS);
     for (i=0; i<escalax-1; ++i) {
       for (j=0; j<escalay; ++j) {
         glVertex3fv(v[i*escalay+j]);
         glVertex3fv(v[i*escalay+(j+1)%escalay]);
         glVertex3fv(v[(i+1)*escalay+(j+1)%escalay]);
         glVertex3fv(v[(i+1)*escalay+j]);
       }
     }
   glEnd();
}

void corpo()
{
	// tronco
	glPushMatrix();
	glColor3f(0.0, 0.0, 0.0);
	glTranslatef(0.0, 0.0, 0.0);
	glScalef(0.7, 1.0, 0.7);
	glutSolidSphere(1.0, 30, 30);
	glPopMatrix();
	// pe' esquerdo
	glPushMatrix();
	glColor3f(1.0, 1.0, 0.0);
	glTranslatef(0.3, -1.17, 0.0);
	semiesfera(24, 24, 0.25);
	glPopMatrix();
	// pe' direito
	glPushMatrix();
	glTranslatef(-0.3, -1.17, 0.0);
	semiesfera(24, 24, 0.25);
	glPopMatrix();
	// nadadeira esquerda
	glPushMatrix();
	glColor3f(1.0, 1.0, 1.0);
	glTranslatef(0.9, 0.0, -0.3);
	glRotatef(-35.0, 1.0, 1.0, 0.0);
	glutSolidCone(0.10, 0.80, 30, 30);
	glPopMatrix();
	// nadadeira direita
	glPushMatrix();
	glColor3f(1.0, 1.0, 1.0);
	glTranslatef(-0.9, 0.0, 0.4);
	glRotatef(145.0, -1.0, 1.0, 0.0);
	glutSolidCone(0.10, 0.80, 30, 30);
	glPopMatrix();
}

void face()
{
	// parte branca do corpo do pinguim
	glPushMatrix();
	glColor3f(1.0, 1.0, 1.0);
	glTranslatef(0.0, -0.2, -1.6);
	glScalef(0.5, 0.7, 0.0);
	glutSolidSphere(1.0, 30, 30);
	glPopMatrix();
	// pupila direita
	glPushMatrix();
	glColor3f(0.0, 0.0, 0.0);
	glTranslatef(-0.2, 0.6, -1.4);
	glScalef(0.06, 0.06, 0.06);
	glutSolidSphere(1.0, 30, 30);
	glPopMatrix();
	// pupila esquerda
	glPushMatrix();
	glColor3f(0.0, 0.0, 0.0);
	glTranslatef(0.2, 0.6, -1.4);
	glScalef(0.06, 0.06, 0.06);
	glutSolidSphere(1.0, 30, 30);
	glPopMatrix();
	// globo ocular direito
	glPushMatrix();
	glColor3f(1.0, 1.0, 1.0);
	glTranslatef(-0.2, 0.7, -1.5);
	glScalef(0.13, 0.17, 0.13);
	glutSolidSphere(1.0, 30, 30);
	glPopMatrix();
	// globo ocular esquerdo
	glPushMatrix();
	glColor3f(1.0, 1.0, 1.0);
	glTranslatef(0.2, 0.7, -1.5);
	glScalef(0.13, 0.17, 0.13);
	glutSolidSphere(1.0, 30, 30);
	glPopMatrix();
	// nariz
	glPushMatrix();
	glColor3f(1.0, 1.0, 0.0);
	glTranslatef(0.0, 0.6, -1.4);
	glRotatef(45.0, 1.0, 0.0, 0.0);
	glutSolidCone(0.10, 0.40, 30, 30);
	glPopMatrix();
}

void pinguim()
{
	glScalef(0.5, 0.5, 0.5);
	glPushMatrix();
	corpo();
	glTranslatef(0.0, 0.0, 2.0);
	face();
	glPopMatrix();
}

void filhote()
{
	glScalef(0.25, 0.25, 0.25);
	glPushMatrix();
	corpo();
	glTranslatef(0.0, 0.0, 2.0);
	face();
	glPopMatrix();
}

void peixe()
{

}

void pinguimcompeixe()
{

}

void display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Limpar buffers de cor e profundidade
  glMatrixMode(GL_MODELVIEW); // Para operar na matriz de visualização de modelo
  glLoadIdentity();

  // glRotatef(-20.0, 1.0, 0.0, 0.0); // Gira a cena para que possamos ver o topo das formas.
  // Desenha o gelo
  // canto superior esquerdo
  glViewport(0, winHeight/2, winWidth/2, winHeight/2);
  glLoadIdentity();
  gluLookAt(1, 6.3, 1, 1, 1, 0, 0, 1, 0); // janela em que a camera esta' “posicionada” acima da cena, no eixo Y


  glPushMatrix();
  glTranslatef(0.0, -1.5, 0.0);
  gelo();
  glPopMatrix();

  glPushMatrix();
  glTranslatef(0.0, -0.9, 0.0);
  filhote();
  glPopMatrix();

  glPushMatrix();
  glTranslatef(1.5, -0.6, moveping);
  glRotatef(rotaping, 0.0, 1.0, 0.0);
  pinguim();
  glPopMatrix();

  // canto inferior esquerdo
  glViewport(0, 0, winWidth/2, winHeight/2);
  glLoadIdentity();
  gluLookAt(1, 1, 1, 1, 1, 0, 0, 1, 0);	// janela em que a camera esta' “posicionada” de frente para a cena, no eixo Z


  glPushMatrix();
  glTranslatef(0.0, -1.5, 0.0);
  gelo();
  glPopMatrix();

  glPushMatrix();
  glTranslatef(0.0, -0.9, 0.0);
  filhote();
  glPopMatrix();

  glPushMatrix();
  glTranslatef(1.5, -0.6, moveping);
  glRotatef(rotaping, 0.0, 1.0, 0.0);
  pinguim();
  glPopMatrix();


  // canto superior direito
  glViewport(winWidth/2, winWidth/2, winWidth/2, winHeight/2);
  glLoadIdentity();
  gluLookAt(10, 1, 1, 1, 1, 0, 0, 1, 0); //  janela em que a camera esta' “posicionada” do lado da cena, no eixo X


  glPushMatrix();
  glTranslatef(0.0, -1.5, 0.0);
  gelo();
  glPopMatrix();

  glPushMatrix();
  glTranslatef(0.0, -0.9, 0.0);
  filhote();
  glPopMatrix();

  glPushMatrix();
  glTranslatef(1.5, -0.6, moveping);
  glRotatef(rotaping, 0.0, 1.0, 0.0);
  pinguim();
  glPopMatrix();


  glutSwapBuffers();
}

// Não queremos que a cena fique distorcida quando o tamanho da janela muda, então
// precisamos de um retorno de chamada remodelar. Sempre manteremos um intervalo de -2,5 a 2,5 pol.
// o menor entre a largura e a altura de nossa caixa de visualização e um intervalo de -10..10
// para a profundidade do viewbox.
void reshape(GLint w, GLint h) {
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  GLfloat aspect = GLfloat(w) / GLfloat(h);
  glLoadIdentity();
  if (w <= h) {
    // width is smaller, so stretch out the height
    glOrtho(-2.5, 2.5, -2.5/aspect, 2.5/aspect, -10.0, 10.0);
  } else {
    // height is smaller, so stretch out the width
    glOrtho(-2.5*aspect, 2.5*aspect, -2.5, 2.5, -10.0, 10.0);
  }
}

/*
void keyboard (unsigned char key, int x, int y){
  switch (key) {
  case 'z':
    z += 0.1;
    cout << "z: "<<z<<endl;
    break;

  case 'Z':
    z -= 0.1;
    cout << "z: "<<z<<endl;
    break;

  // seta esquerda: mover para direcao 0 (esquerda)
  case 'a':
	direcao = 0;
	break;
  // seta direita: mover para direcao 1 (direita)
  case 'd':
	direcao = 1;
	break;
  }
  glutPostRedisplay();
}
*/
void keyboard(int key, int x, int y){
  switch (key) {
  // seta esquerda: mover para direcao 0 (?)
  case GLUT_KEY_LEFT:
	rotaping += 5.0;
	break;
  // seta direita: mover para direcao 1 (?)
  case GLUT_KEY_RIGHT:
	rotaping -= 5.0;
	break;
  // seta cima: mover para direcao 1 (para frente)
  case GLUT_KEY_UP:
	direcao = 1;
	break;
  // seta beixo: mover para direcao 0 (para tras)
  case GLUT_KEY_DOWN:
	direcao = 0;
	break;
  // padrao: mover para direcao 2 (?)
  default:
    direcao = 2;
    break;
  }
}


void init()
{
  glClearColor(0.592, 0.807, 0.921, 1.0); // Define a cor de background da janela
  glClearDepth (1.0f);         // Define a profundidade do fundo para o mais distante
  //glMatrixMode(GL_PROJECTION);
  //glLoadIdentity();
  glEnable (GL_DEPTH_TEST);   // Habilita o teste de profundidade para z-abate
  glDepthFunc (GL_LEQUAL);    // Defina o tipo de teste de profundidade
  glShadeModel (GL_SMOOTH);   // Habilita sombreamento suave
  glHint (GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Boas correções de perspectiva
}

// move = funcao de movimentacao do pinguim
void move(int passo)
{
	// condicao de direcao 1 (direita)
	if(direcao==1)
	{
		// movimentacao de x do pinguim
		moveping += (float)passo/70;
		// desenho do pinguim na direcao do movimento
	/*	escalaping = 0.4;
		// limite direito de movimento
		if(moveping>0.2){
			moveping -= (float)passo/70;
		}*/
	}
	// condicao de direcao 0 (esquerda)
	if(direcao==0)
	{
		// movimentacao de x do pinguim
		moveping -= (float)passo/70;
		// desenho do pinguim na direcao do movimento
	/*	escalaping = -0.4;
		// limite esquerdo de movimento
		if(moveping<-4.5)
			direcao = 1;*/
	}
	glutPostRedisplay();
	glutTimerFunc(10,move,1);
}


// The usual application statup code.
int main(int argc, char** argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowPosition(80, 80);
  glutInitWindowSize(winWidth, winHeight);
  glutCreateWindow("Trabalho 2");
  glutReshapeFunc(reshape);
  glutDisplayFunc(display);

  // movimentacao do pinguim
  glutTimerFunc(10,move,1);

  // glutKeyboardFunc(keyboard);

  // Funcao especial do GLUT para teclas de setas
  glutSpecialFunc(keyboard);

  init();
  glutMainLoop();
}

