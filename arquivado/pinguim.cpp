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
#include <stdio.h>
#include "stb_image.h"  // biblioteca para texturas
#include "glext.h"		// biblioteca para texturas
#include <iostream> 	// biblioteca auxiliar para numeros aleatorios
#include <random>		// biblioteca auxiliar para numeros aleatorios
using namespace std;

GLuint texID[6];	// IDs de textura para as cinco texturas

char const* textureFileNames[6] = { 	// nomes de arquivo para os arquivos dos quais as imagens de textura sao carregadas
            "texturas/container.jpg",
            "texturas/paredegelo.jpg",
			"texturas/montahas.jpg",
			"texturas/marble.jpg",
			"texturas/derretimento.jpg",
			"texturas/buraco.jpg"
       };

// tamanho da janela inicial
GLint winWidth = 800, winHeight = 600;
// variavel de testes no teclado
GLfloat z = 0;
// variaveis de posicao e direcao do pinguim
GLfloat movePingX = 0.0, movePingZ = 0.0, rotaping = 0.0, rotaNadadeira = 90.0;
GLint direcao = 2, nadadeiras = 0;

// constante Pi
const double PI = 3.1415926535898;
// coordenadas dos pontos aleatorios
GLfloat p1x, p1z, p2x, p2z;

GLfloat vetor[2]= {0,0}, vetorD[2]={0,0};


// tempoConta = contador de tempo total do jogo (5 minutos)
GLint tempoConta = 18000;
// tempoFilhote = contador de tempo de vida do filhote (1 minuto)
GLint tempoFilhote = 3600;
// tempoBuraco = contador de tempo de aparecimento de novo buraco (10 segundos)
GLint tempoBuraco = 250;
// tempoBuraco = contador de tempo de aparecimento de novo peixe (20 segundos)
GLint tempoPeixe = 500;

// obtem um numero aleatorio do hardware
std::random_device rd;
// alimenta o gerador de numeros
std::mt19937 gen(rd());

std::uniform_real_distribution<> distr(-2.5, 2.5); 		// funcao que define a variacao de p1x
std::uniform_real_distribution<> distr2(-2.5, 2.5); 	// funcao que define a variacao de p1z
std::uniform_real_distribution<> distr3(-2.5, 2.5); 	// funcao que define a variacao de p2x
std::uniform_real_distribution<> distr4(-2.5, 2.5); 	// funcao que define a variacao de p2z

void initGL();

// gera ponto x,y para buraco
void gera(){
	p1x = distr(gen);
	p1z = distr2(gen);
}
// gera ponto x,y para peixe
void gera2(){
	p2x = distr3(gen);
	p2z = distr4(gen);
}
// bloco de gelo
void gelo()
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture( GL_TEXTURE_2D, texID[3] );	// Amarra a textura #3 para usar no gelo
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POLYGON); 	// Face posterior
	glNormal3f(0,0,1); 		// Normal da face
	glTexCoord2d(0, 1);
	glVertex3f(3.0, 0.25, 3.0);
	glTexCoord2d(1, 1);
	glVertex3f(-3.0, 0.25, 3.0);
	glTexCoord2d(1, 0);
	glVertex3f(-3.0, -0.25, 3.0);
	glTexCoord2d(0, 0);
	glVertex3f(3.0, -0.25, 3.0);
	glEnd();
	glBegin(GL_POLYGON); 	// Face frontal
	glNormal3f(0,0,-1); 	// Normal da face
	glTexCoord2d(1, 1);
	glVertex3f(3.0, 0.25, -3.0);
	glTexCoord2d(1, 0);
	glVertex3f(3.0, -0.25, -3.0);
	glTexCoord2d(0, 0);
	glVertex3f(-3.0, -0.25, -3.0);
	glTexCoord2d(0, 1);
	glVertex3f(-3.0, 0.25, -3.0);
	glEnd();
	glBegin(GL_POLYGON); 	// Face lateral esquerda
	glNormal3f(-1,0,0); 	// Normal da face
	glTexCoord2d(1, 1);
	glVertex3f(-3.0, 0.25, 3.0);
	glTexCoord2d(0, 1);
	glVertex3f(-3.0, 0.25, -3.0);
	glTexCoord2d(0, 0);
	glVertex3f(-3.0, -0.25, -3.0);
	glTexCoord2d(1, 0);
	glVertex3f(-3.0, -0.25, 3.0);
	glEnd();
	glBegin(GL_POLYGON); 	// Face lateral direita
	glNormal3f(1,0,0); 		// Normal da face
	glTexCoord2d(0, 1);
	glVertex3f(3.0, 0.25, 3.0);
	glTexCoord2d(0, 0);
	glVertex3f(3.0, -0.25, 3.0);
	glTexCoord2d(1, 0);
	glVertex3f(3.0, -0.25, -3.0);
	glTexCoord2d(1, 1);
	glVertex3f(3.0, 0.25, -3.0);
	glEnd();
	glBegin(GL_POLYGON); 	// Face superior
	glNormal3f(0,1,0); 		// Normal da face
	glTexCoord2d(0, 1);
	glVertex3f(-3.0, 0.25, -3.0);
	glTexCoord2d(0, 0);
	glVertex3f(-3.0, 0.25, 3.0);
	glTexCoord2d(1, 0);
	glVertex3f(3.0, 0.25, 3.0);
	glTexCoord2d(1, 1);
	glVertex3f(3.0, 0.25, -3.0);
	glEnd();
	glBegin(GL_POLYGON); 	// Face inferior
	glNormal3f(0,-1,0); 	// Normal da face
	glTexCoord2d(1, 1);
	glVertex3f(-3.0, -0.25, -3.0);
	glTexCoord2d(0, 1);
	glVertex3f(3.0, -0.25, -3.0);
	glTexCoord2d(0, 0);
	glVertex3f(3.0, -0.25, 3.0);
	glTexCoord2d(1, 0);
	glVertex3f(-3.0, -0.25, 3.0);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}
// cenario de fundo
void DesenhaCenario()
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture( GL_TEXTURE_2D, texID[2] );	// Amarra a textura #2 para usar no cenario de fundo
	glColor3f(1.0, 1.0, 1.0);
	glBegin (GL_POLYGON);
    // Back Face
    glTexCoord2f(0.0f, 0.0f);
    glVertex2f( -3.0f, -1.5f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex2f(-3.0f, 1.5f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex2f(3.0f,  1.5f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex2f( 3.0f,  -1.5f);
    glEnd();
    glDisable(GL_TEXTURE_2D);
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
// corpo de pinguim
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
	glColor3f(0.98, 0.63, 0.01);	// cor laranja
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
	glTranslatef(0.8, 0.0, 0.0);
	glRotatef(rotaNadadeira, 1.0, 0.0, 0.0); //glRotatef(rotaNadadeira, 1.0, 0.0, 0.0);
	glutSolidCone(0.10, 0.80, 30, 30);
	glPopMatrix();
	// nadadeira direita
	glPushMatrix();
	glColor3f(1.0, 1.0, 1.0);
	glTranslatef(-0.8, 0.0, 0.0);
	glRotatef(rotaNadadeira, 1.0, 0.0, 0.0);
	glutSolidCone(0.10, 0.80, 30, 30);
	glPopMatrix();
}
// face de pinguim
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
	glColor3f(0.98, 0.63, 0.01);
	glTranslatef(0.0, 0.6, -1.4);
	glRotatef(45.0, 1.0, 0.0, 0.0);
	glutSolidCone(0.10, 0.40, 30, 30);
	glPopMatrix();
}
// pinguim pai
void pinguim()
{
	glScalef(0.5, 0.5, 0.5);
	glPushMatrix();
	corpo();
	glTranslatef(0.0, 0.0, 2.0);
	face();
	glPopMatrix();
}
// pinguim filho
void filhote()
{
	glScalef(0.25, 0.25, 0.25);
	glPushMatrix();
	corpo();
	glTranslatef(0.0, 0.0, 2.0);
	face();
	glPopMatrix();
}

void esferaPeixe(){

	glEnable(GL_TEXTURE_2D);
	glBindTexture( GL_TEXTURE_2D, texID[0] );
	// Create the sphere
	glPushMatrix();
	glRotatef(90.0, 1.0, 0.0, 0.0);
	GLUquadric *quadric = gluNewQuadric();
	gluQuadricDrawStyle(quadric, GLU_FILL);
	gluQuadricNormals(quadric, GLU_SMOOTH);
	gluQuadricTexture(quadric, GL_TRUE);
	gluSphere(quadric, 1.0, 20, 20);
	gluDeleteQuadric(quadric);
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

void peixe()
{
	 glEnable(GL_TEXTURE_2D);
	 glBindTexture( GL_TEXTURE_2D, texID[0] );
	// corpo do peixe
	//glColor3f(1.0, 1.0, 1.0);
	glPushMatrix();
	glTranslatef(0.0, 0.25, 0.0);
	glScalef(1.0, 1.9, 1.0);
	GLUquadricObj *sphere=NULL;
	sphere = gluNewQuadric();
	gluQuadricDrawStyle(sphere, GLU_FILL);
	gluQuadricTexture(sphere, TRUE);
	gluQuadricNormals(sphere, GLU_SMOOTH);

	glPopMatrix();
	// rabo do peixe
	//glColor3f(1.0, 1.0, 1.0);
	glPushMatrix();
	glTranslatef(0.0, 0.0, 0.0);
	glScalef(1.0, 1.0, 1.0);
	glRotatef(-90.0, 1.0, 0.0, 0.0);
	glutSolidCone(0.08, 0.20, 30, 30);
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	/*
	// globo ocular direito
	glPushMatrix();
	glColor3f(1.0, 1.0, 1.0);
	glTranslatef(-0.6, 9.7, -1.5);
	glScalef(0.042, 0.056, 0.042);
	glutSolidSphere(1.0, 30, 30);
	glPopMatrix();
	// globo ocular esquerdo
	glPushMatrix();
	glColor3f(1.0, 1.0, 1.0);
	glTranslatef(-0.7, 9.7, -1.5);
	glScalef(0.042, 0.056, 0.042);
	glutSolidSphere(1.0, 30, 30);
	glPopMatrix();
	*/
}

void pinguimComPeixe()
{
	glPushMatrix();
	pinguim();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.0, 0.0, 0.43);
	glScalef(0.5, 0.5, 0.5);
	glRotatef(0.0, 0.0, 0.0, 0.0);
	peixe();
	glPopMatrix();
}

void buraco()
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture( GL_TEXTURE_2D, texID[4] );
	glColor3f(1.0, 1.0, 1.0);
	circulo(0.4);
	glDisable(GL_TEXTURE_2D);
}

void display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Limpar buffers de cor e profundidade
  glMatrixMode(GL_MODELVIEW); // Para operar na matriz de visualiza????o de modelo
  glLoadIdentity();

  // glRotatef(-20.0, 1.0, 0.0, 0.0); // Gira a cena para que possamos ver o topo das formas.
  // Desenha o gelo

  // canto superior esquerdo
  glViewport(0, winHeight/2, winWidth/2, winHeight/2);
  glLoadIdentity();
  gluLookAt(0, 6.3, 0, 1.5, -0.6, movePingZ, 0, 1, 0); // janela em que a camera esta' ???posicionada??? acima da cena, no eixo Y


  glPushMatrix();
  glTranslatef(0.0, -1.5, 0.0);
  gelo();
  glPopMatrix();

  glPushMatrix();
  glTranslatef(0.0, -0.9, 0.0);	// filhote posicionado no centro da placa de gelo
  filhote();
  glPopMatrix();

  glPushMatrix();
  glTranslatef(movePingX, -0.6, movePingZ);
  glRotatef(rotaping, 0.0, 1.0, 0.0);
  pinguim();
  glPopMatrix();

  glPushMatrix();
  glTranslatef(p1x, -1.1, p1z);
  glRotatef(90, 1.0, 0.0, 0.0);
  buraco();
  glPopMatrix();

  glPushMatrix();
  glTranslatef(p2x, -1.1, p2z);
  glRotatef(90, 1.0, 0.0, 0.0);
  peixe();
  glPopMatrix();

  glPushMatrix();
  glTranslatef(0.0, 0.0, 0.0);
  esferaPeixe();
  glPopMatrix();


  // canto inferior esquerdo
  glViewport(0, 0, winWidth/2, winHeight/2);
  glLoadIdentity();
  gluLookAt(1, 0.5, 7, 1.5, -0.6, movePingZ, 0, 1, 0);	// janela em que a camera esta' ???posicionada??? de frente para a cena, no eixo Z


  glPushMatrix();
  glTranslatef(1.4, -1.5, 0.0);
  gelo();
  glPopMatrix();

  glPushMatrix();
  glTranslatef(0.0, -0.9, 0.0);	// filhote posicionado no centro da placa de gelo
  filhote();
  glPopMatrix();

  glPushMatrix();
  glTranslatef(1.5, -0.6, movePingZ);
  glRotatef(rotaping, 0.0, 1.0, 0.0);
  pinguim();
  glPopMatrix();

  glPushMatrix();
  glTranslatef(p1x, -1.1, p1z);
  glRotatef(90, 1.0, 0.0, 0.0);
  buraco();
  glPopMatrix();

  glPushMatrix();
  glTranslatef(p2x, -1.1, p2z);
  glRotatef(90, 1.0, 0.0, 0.0);
  peixe();
  glPopMatrix();

  glPushMatrix();
  glTranslatef(1.4, 0.0, -2.60);
  glRotatef(180, 1.0, 0.0, 0.0);
  DesenhaCenario();
  glPopMatrix();

  glPushMatrix();
  glTranslatef(0.0, 0.0, 0.0);
  esferaPeixe();
  glPopMatrix();


  // canto superior direito
  glViewport(winWidth/2, winWidth/2, winWidth/2, winHeight/2);
  glLoadIdentity();
  gluLookAt(7, 0.5, 0, 1.5, -0.6, movePingZ, 0, 1, 0); //  janela em que a camera esta' ???posicionada??? do lado da cena, no eixo X


  glPushMatrix();
  glTranslatef(0.0, -1.5, 0.0);
  gelo();
  glPopMatrix();

  glPushMatrix();
  glTranslatef(0.0, -0.9, 0.0);	// filhote posicionado no centro da placa de gelo
  filhote();
  glPopMatrix();

  glPushMatrix();
  glTranslatef(1.5, -0.6, movePingZ);
  glRotatef(rotaping, 0.0, 1.0, 0.0);
  pinguim();
  glPopMatrix();

  glPushMatrix();
  glTranslatef(p1x, -1.1, p1z);
  glRotatef(90, 1.0, 0.0, 0.0);
  buraco();
  glPopMatrix();

  glPushMatrix();
  glTranslatef(p2x, -1.1, p2z);
  glRotatef(90, 1.0, 0.0, 0.0);
  peixe();
  glPopMatrix();

  glPushMatrix();
  glTranslatef(1.4, 0.0, -2.60);
  glRotatef(180, 1.0, 0.0, 0.0);
  DesenhaCenario();
  glPopMatrix();

  glPushMatrix();
  glTranslatef(0.0, 0.0, 0.0);
  esferaPeixe();
  glPopMatrix();


  // canto inferior direito
  glViewport(winWidth/2, 0, winWidth/2, winHeight/2);
  glLoadIdentity();
  gluLookAt(3.0, 4.0, 5.0, 1.5, -0.6, movePingZ, 0, 1, 0);	// janela em que a camera esta' ???posicionada??? em uma posicao livre


  glPushMatrix();
  glTranslatef(0.0, -1.5, 0.0);
  gelo();
  glPopMatrix();

  glPushMatrix();
  glTranslatef(0.0, -0.9, 0.0);	// filhote posicionado no centro da placa de gelo
  filhote();
  glPopMatrix();

  glPushMatrix();
  glTranslatef(1.5, -0.6, movePingZ);
  glRotatef(rotaping, 0.0, 1.0, 0.0);
  pinguim();
  glPopMatrix();

  glPushMatrix();
  glTranslatef(p1x, -1.1, p1z);
  glRotatef(90, 1.0, 0.0, 0.0);
  buraco();
  glPopMatrix();

  glPushMatrix();
  glTranslatef(p2x, -1.1, p2z);
  glRotatef(90, 1.0, 0.0, 0.0);
  peixe();
  glPopMatrix();

  glPushMatrix();
  glTranslatef(0.0, 0.0, 0.0);
  esferaPeixe();
  glPopMatrix();


  glutSwapBuffers();	// (required for double-buffered drawing)
}

// N??o queremos que a cena fique distorcida quando o tamanho da janela muda, ent??o
// precisamos de um retorno de chamada remodelar. Sempre manteremos um intervalo de -2,5 a 2,5 pol.
// o menor entre a largura e a altura de nossa caixa de visualiza????o e um intervalo de -10..10
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

// funcao para testes com o teclado
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
  }
  glutPostRedisplay();
}

// funcao de teclas especiais do teclado
void keyboard(int key, int x, int y){
  switch (key) {
  // seta esquerda: rotacionar o pinguim em torno do seu eixo para a esquerda
  case GLUT_KEY_LEFT:
	if(rotaping >=360) rotaping = 0;
	rotaping += 3.0;
	vetor[0] = cos(-(rotaping + 270)*PI/180);
	vetor[1] = sin(-(rotaping + 270)*PI/180);
	vetorD[0] = vetor[0]*movePingX - vetor[1]*movePingZ;
	vetorD[1] = vetor[1]*movePingX + vetor[0]*movePingZ;

	break;
  // seta direita: rotacionar o pinguim em torno do seu eixo para a direita
  case GLUT_KEY_RIGHT:
	if(rotaping <=-360) rotaping = 0;
	rotaping -= 3.0;
	vetor[0] = cos(-(rotaping + 270)*PI/180);
	vetor[1] = sin(-(rotaping + 270)*PI/180);
	vetorD[0] = vetor[0]*movePingX - vetor[1]*movePingZ;
	vetorD[1] = vetor[1]*movePingX + vetor[0]*movePingZ;
	break;
  // seta cima: mover para direcao 1 (para frente)
  case GLUT_KEY_UP:
	movePingX += 0.1*vetor[0];
	movePingZ += 0.1*vetor[1];
	nadadeiras = 1;
	break;
  // seta beixo: mover para direcao 0 (para tras)
  case GLUT_KEY_DOWN:
	movePingX += -0.1*vetor[0];
	movePingZ += -0.1*vetor[1];
	nadadeiras = 1;
	break;
  // padrao: mover para direcao 2 (parado)
  default:
    direcao = 2;
    nadadeiras = 0;
    break;
  }
}


void initGL()
{
  glClearColor(0.592, 0.807, 0.921, 1.0); // Define a cor de background da janela / cor do ce'u
  glClearDepth (1.0f);         	// Define a profundidade do fundo para o mais distante
  //glMatrixMode(GL_PROJECTION);
  //glLoadIdentity();
  glEnable (GL_DEPTH_TEST); 	// Habilita o teste de profundidade para z-abate
  glDepthFunc (GL_LEQUAL);    	// Defina o tipo de teste de profundidade
  glShadeModel (GL_SMOOTH);   	// Habilita sombreamento suave
  glHint (GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Boas corre????es de perspectiva
}

// move = funcao de movimentacao do pinguim
void move(int passo)
{
	// condicao de direcao 1 (frente)
	if(direcao==1)
	{

		// movimentacao em Z do pinguim
		movePingZ += (float)passo/70;

		// limite de movimento do pinguim em Z
		if((movePingZ<-2.9) || (movePingZ>2.9)) {
			movePingZ -= (float)passo/70;
		}

		// desenho do pinguim na direcao do movimento
	/*	escalaping = 0.4;
		// limite direito de movimento
		if(moveping>0.2){
			moveping -= (float)passo/70;
		}*/
	}
	// condicao de direcao 0 (tras)
	if(direcao==0)
	{

		// movimentacao em Z do pinguim
		movePingZ -= (float)passo/70;

		// limite de movimento do pinguim em Z
		if((movePingZ<-2.9) || (movePingZ>2.9)) {
			movePingZ += (float)passo/70;
		}


		// desenho do pinguim na direcao do movimento
	/*	escalaping = -0.4;
		// limite esquerdo de movimento
		if(moveping<-4.5)
			direcao = 1;*/
	}


	// movimentacao das nadadeiras
	// nadadeiras paradas
	if (nadadeiras==0){
		rotaNadadeira = 90.0;
	}
	// nadadeiras em movimento
	if (nadadeiras==1){
		if (rotaNadadeira == 270.0){
			rotaNadadeira = 90.0;
		}
		else if (rotaNadadeira == 90.0){
			rotaNadadeira = 270.0;
		}
	}

    // condicao de colisao com o buraco  (funciona mas nao utilizado ainda pois falta implementar 'movePingX')
	/*
	if ((movePingX <= p1x + 0.35) && (movePingZ <= p1z + 0.35)){
		// em caso de colisao, encerra o tempo e insere texto
		tempoConta = -10;
		//texto4 = 3.0;
	}*/

	glutPostRedisplay();
	glutTimerFunc(10,move,1);
}

// funcao de movimentacao do buraco
void moveBuraco(int passo)
{
	tempoBuraco -= 1;
	if(tempoBuraco<0)
	{
		tempoBuraco += 250;
		gera();
	}

	glutPostRedisplay();
	glutTimerFunc(10,moveBuraco,1);
}

// funcao de movimentacao do peixe
void movePeixe(int passo)
{
	tempoPeixe -= 1;
	if(tempoPeixe<0)
	{
		tempoPeixe += 500;
		gera2();
	}

	glutPostRedisplay();
	glutTimerFunc(10,movePeixe,1);
}

void tempoJogo(int passo){

	tempoConta -= 1;
	// tempoFilhote -= 1;
    // condicao de termino do tempo de jogo
	if(tempoConta<0){
		// o pinguim e' movido para um ponto fixo e paralisado
		movePingZ = -2.0;
		rotaping = 0.0;
//		movepetrel = 0.0;
//		alturapetrel = 1.0;
		// exibe o texto de final de jogo
		//texto = 5.0;
	}

	/*
	// condicao de termino do tempo de vida do filhote
	else if(tempoFilhote<0){
		// o pinguim e o petrel sao paralisados
		moveping = -3.0;
		movepetrel = 0.0;
		alturapetrel = 1.0;
		// exibe o texto "o filhote morreu" e "voc?? perdeu"
		texto2 = 4.0;
		texto4 = 3.0;
	}*/

	glutPostRedisplay();
	glutTimerFunc(10,tempoJogo,1);
}

/*  Esta fun????o carrega 5 texturas de arquivos de textura, que devem estar dispon??veis
  * para o programa quando ele ?? executado. Os caminhos para os arquivos s??o armazenados no global
  * array textureFileNames. A fun????o gera 5 identificadores de objetos de textura
  * e os armazena no array global textID para que possam ser usados quando
  * texturas de liga????o em display (). Em seguida, carrega as 5 imagens de textura em
  * os objetos de textura. Ele chama glTexParameteri para cada textura a ser alterada
  * o filtro de minifica????o para GL_LINEAR (sem isso, a textura n??o funcionar??
  * porque n??o h?? mipmaps para as texturas).
 */
void loadTextures() {
	int width, height, nrChannels;
	unsigned char *data;

	glGenTextures(6, texID);

	for(int i = 0; i < 6;i++)
	{
	glBindTexture(GL_TEXTURE_2D, texID[i]);
	// definir as op????es de envolvimento / filtragem de textura (no objeto de textura atualmente vinculado)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// carrega e gera a textura

	data = stbi_load(textureFileNames[i], &width, &height, &nrChannels, 0);

	if (data)
	{
	    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	    glTexParameteri  (GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE );
	    //glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		 printf("Falha ao carregar textura\n");
	}
	stbi_image_free(data);
	}

}

// The usual application statup code.
int main(int argc, char** argv)
{
  // funcoes necessarias para os numeros aleatorios
  std::random_device rd; 	// obtem um numero aleatorio do hardware
  std::mt19937 gen(rd()); 	// alimenta o gerador de numeros

  // funcoes de geracao de numeros aleatorios
  gera();
  gera2();

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowPosition(80, 80);
  glutInitWindowSize(winWidth, winHeight);
  glutCreateWindow("Trabalho 2");
  initGL();
  loadTextures();
  glutReshapeFunc(reshape);
  glutDisplayFunc(display);

  // movimentacao do pinguim
  glutTimerFunc(10,move,1);

  glutTimerFunc(10,moveBuraco,1);
  glutTimerFunc(10,movePeixe,1);
  glutTimerFunc(10,tempoJogo,1);

  // funcao do teclado
  glutKeyboardFunc(keyboard);

  // funcao do GLUT para teclas especiais
  glutSpecialFunc(keyboard);


  glutMainLoop();
}
