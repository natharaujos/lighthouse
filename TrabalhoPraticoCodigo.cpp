
#include <windows.h>
#include "glut.h"

#define _USE_MATH_DEFINES
#define COLUNAS_TEXTURA 60
#define LINHAS_TEXTURA 60

int anguloHorizontal, anguloVertical;
int eixoDaNormal, sinalDaNormal;
int anguloCone = 180; 
int velocidade = 8000;
float prop;
float corCeu[3] = {0,0,0.35};
float globalAmb[] = {0.6f,0.6f,0.6f,1.0f};
float globalDifusa[] = {1.0,1.0,1.0,1.0};
float posicaoLuzDifusa[4] = {0.0,10.0,-10.0,1.0};
float posicaoLuzAmbiente [4] = {0.0,0.0,0.0,0.0};
bool LigaIluminacao = true, LigaTextura, LigaAnimacao,noite = true;
GLubyte dadosTextura[LINHAS_TEXTURA][COLUNAS_TEXTURA][3];

void criaTextura(){ //Função para carregar as texturas
	int valor;
	for (int l = 0; l < LINHAS_TEXTURA; l++){
		for (int c = 0; c < COLUNAS_TEXTURA; c++){
			valor = (((l & 0x2) == 0) ^ ((c & 0x4) == 0)) * 255;
			dadosTextura[l][c][0] = (GLubyte)valor;
			dadosTextura[l][c][1] = (GLubyte)valor;
			dadosTextura[l][c][2] = (GLubyte)valor;
		}
	}
}

GLfloat *getNormal(){
	static GLfloat Normal[] = {0, 0, 0};
	Normal[eixoDaNormal] = sinalDaNormal * 1;
	return Normal;
}

void rodaHorario(){ // Função para fazer a torre girar no sentido horario
	anguloHorizontal = (anguloHorizontal +=10) % 360;
}

void rodaAntiHorario(){// Função para fazer a torre girar no sentido anti-horario
	anguloHorizontal = (anguloHorizontal -= 10) % 360;
}

void realizaAnimacao(int NULO){//Função que realiza que as animações 
	if (!LigaAnimacao){
		glutSwapBuffers();
		return;
	}else{

		glutPostRedisplay();
		anguloCone = (anguloCone += 50) % 360;
		glutTimerFunc(velocidade / 60, realizaAnimacao, NULL);
	
	}

}

void rotacionaCone(bool antihorario){//Função que rotaciona o cone para ambos os sentidos

	if (antihorario){

		anguloCone = (anguloCone - 10) % 360;
	}else{
		anguloCone = (anguloCone + 10) % 360;
	}
}

void rodaVerticalmente(){//Função que rotaciona a torre verticalmente
	anguloVertical = (anguloVertical + 10) % 360;
}

void ligaDesligaAnimacao(){//Função que controla a variavel booleana que comanda a animação
	LigaAnimacao = !LigaAnimacao;
}

void desenhaSol(){
	
	glDisable(GL_TEXTURE_2D);
	glTranslatef(5.8,4.2,0);
	glOrtho(-5,5,-5/prop,5/prop,-20,20);
	//glRotatef(-90.0, 1.0, 0.0, 0.0);
	glColor3f(1,0.9,0);
	glutSolidSphere(2, 15, 15);
	glEnable(GL_TEXTURE_2D);
}

void desenhaEstrelas(){//Função que desenha as estrelas

	//glDisable(GL_TEXTURE_2D);
	glColor4f(1,1,1,1);
	glBegin(GL_POLYGON); 
	glVertex3f(-5,4.6,0);
	glVertex3f(-5.1,4.7,0);
	glVertex3f(-5.2,4.6,0);
	glVertex3f(-5.1,4.5,0);
	glEnd();
	glBegin(GL_POLYGON); 
	glVertex3f(-1,4.7,0);
	glVertex3f(-1.1,4.8,0);
	glVertex3f(-1.2,4.7,0);
	glVertex3f(-1.1,4.6,0);
	glEnd();
	glBegin(GL_POLYGON); 
	glVertex3f(-2.3,5.3,0);
	glVertex3f(-2.4,5.4,0);
	glVertex3f(-2.5,5.3,0);
	glVertex3f(-2.4,5.2,0);
	glEnd();
	glBegin(GL_POLYGON); 
	glVertex3f(-3,3.5,0);
	glVertex3f(-3.1,3.6,0);
	glVertex3f(-3.2,3.5,0);
	glVertex3f(-3.1,3.4,0);
	glEnd();
	glBegin(GL_POLYGON); 
	glVertex3f(-4,5.8,0);
	glVertex3f(-4.1,5.9,0);
	glVertex3f(-4.2,5.8,0);
	glVertex3f(-4.1,5.7,0);
	glEnd();
	glBegin(GL_POLYGON); 
	glVertex3f(-6,2.7,0);
	glVertex3f(-6.1,2.8,0);
	glVertex3f(-6.2,2.7,0);
	glVertex3f(-6.1,2.6,0);
	glEnd();
	glBegin(GL_POLYGON); 
	glVertex3f(-6.3,5.3,0);
	glVertex3f(-6.4,5.4,0);
	glVertex3f(-6.5,5.3,0);
	glVertex3f(-6.4,5.2,0);
	glEnd();
	glBegin(GL_POLYGON); 
	glVertex3f(5,3.7,0);
	glVertex3f(5.1,3.8,0);
	glVertex3f(5.2,3.7,0);
	glVertex3f(5.1,3.6,0);
	glEnd();
	glBegin(GL_POLYGON); 
	glVertex3f(3,3,0);
	glVertex3f(3.1,3.1,0);
	glVertex3f(3.2,3,0);
	glVertex3f(3.1,2.9,0);
	glEnd();
	glBegin(GL_POLYGON); 
	glVertex3f(1,4.7,0);
	glVertex3f(1.1,4.8,0);
	glVertex3f(1.2,4.7,0);
	glVertex3f(1.1,4.6,0);
	glEnd();
	glBegin(GL_POLYGON); 
	glVertex3f(2.3,5.3,0);
	glVertex3f(2.4,5.4,0);
	glVertex3f(2.5,5.3,0);
	glVertex3f(2.4,5.2,0);
	glEnd();
	glBegin(GL_POLYGON); 
	glVertex3f(4,5,0);
	glVertex3f(4.1,5.1,0);
	glVertex3f(4.2,5,0);
	glVertex3f(4.1,4.9,0);
	glEnd();
	glBegin(GL_POLYGON); 
	glVertex3f(6,2,0);
	glVertex3f(6.1,2.1,0);
	glVertex3f(6.2,2,0);
	glVertex3f(6.1,1.9,0);
	glEnd();
	glBegin(GL_POLYGON); 
	glVertex3f(6.3,5,0);
	glVertex3f(6.4,5.1,0);
	glVertex3f(6.5,5,0);
	glVertex3f(6.4,4.9,0);
	glEnd();
	//glEnable(GL_TEXTURE_2D);
}

void ligaDesligaTextura(){//Função que liga e desliga a textura
	if (LigaTextura){
		glDisable(GL_TEXTURE_2D);
		LigaTextura = false;
	}else{
		glEnable(GL_TEXTURE_2D);
		LigaTextura = true;
	}
}

void desenhaTelhado(){// Função que desenha o telhado
	glColor3f(1, 0, 0);
	glRotatef(270, 1, 0, 0);
	glutSolidCone(.8, 2, 25, 25);
}

void alteraNormal(){
	sinalDaNormal = -1 * sinalDaNormal;
}

void desenhaPilastras() {// Função que desenha as pilastras que seguram o telhado
	glPushMatrix();
	glBegin(GL_POLYGON);
	glNormal3fv(getNormal());
	glVertex3f(0.1, 0, 0);
	glVertex3f(0.25, 0, 0);
	glVertex3f(0.25, 1.2, 0);
	glVertex3f(0.1, 1.2, 0);
	glEnd();
	glPopMatrix();

	alteraNormal();

	glPushMatrix();
	glRotatef(180, 0, 1, 0);
	glTranslatef(-1, 0, 0);
	glBegin(GL_POLYGON);
	glNormal3fv(getNormal());
	glVertex3f(0.1, 0, 0);
	glVertex3f(0.25, 0, 0);
	glVertex3f(0.25, 1.2, 0);
	glVertex3f(0.1, 1.2, 0);
	glEnd();
	glPopMatrix();

	alteraNormal();
}

void posicionaPilastras() {// Função que chama o metodo desenhaPilastras() para desenhar as pilastras no lugar certo
	eixoDaNormal = 2;
	sinalDaNormal = 1;

	glPushMatrix();
	glTranslatef(0, 0, -0.1);
	desenhaPilastras();
	glPopMatrix();

	sinalDaNormal = -1;

	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glTranslatef(0, 0, 0.1);
	desenhaPilastras();
	glPopMatrix();

	sinalDaNormal = 1;

	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glTranslatef(0, 0, 0.9);
	desenhaPilastras();
	glPopMatrix();

	sinalDaNormal = -1;

	glPushMatrix();
	glTranslatef(0, 0, -0.9);
	desenhaPilastras();
	glPopMatrix();
}

void desenhaCorpoTorre() // Função que desenha a torre
{
	eixoDaNormal = 2;
	sinalDaNormal = 1;
	glColor3f(1, 0, 0); // VERMELHO

	//Desenha parte da frente da torre
	glPushMatrix();
	glBegin(GL_QUADS);
	glNormal3fv(getNormal());
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0, 3, 0);
	glVertex3f(1, 3, 0);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1, -1, 0);
	glVertex3f(0, -1, 0);
	alteraNormal();
	glEnd();
	glPopMatrix();

	// Desenha lado esquerdo da torre
	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glBegin(GL_QUADS);
	glNormal3fv(getNormal());
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0, 3, 0);
	glVertex3f(1, 3, 0);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1, -1, 0);
	glVertex3f(0, -1, 0);
	alteraNormal();
	glEnd();
	glPopMatrix();

	// Desenha lado direito da torre
	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glTranslatef(0, 0, 1);
	glBegin(GL_QUADS);
	glNormal3fv(getNormal());
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0, 3, 0);
	glVertex3f(1.0, 3, 0);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1, -1, 0);
	glVertex3f(0, -1, 0);
	alteraNormal();
	glEnd();
	glPopMatrix();

	// Desenha parte de tras da torre
	glPushMatrix();
	glTranslatef(0, 0, -1);
	glBegin(GL_QUADS);
	glNormal3fv(getNormal());
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0, 3, 0);
	glVertex3f(1.0, 3, 0);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1, -1, 0);
	glVertex3f(0, -1, 0);
	alteraNormal();
	glEnd();
	glPopMatrix();

	glColor3f(1, 1, 1); // Preto

	// parte de cima da torre (lugar onde fica o farol)
	glPushMatrix();
	glBegin(GL_QUADS);
	glNormal3fv(getNormal());
	glVertex3f(0, 3, 0);
	glVertex3f(1, 3, 0);
	glVertex3f(1, 3, -1);
	glVertex3f(0, 3, -1);
	alteraNormal();
	glEnd();
	glPopMatrix();
}

void desenhaCone(){//Função que desenha um cone
	glColor3f(.33, .33, .33);
	glutSolidCone(.25, .33, 25, 25);
}

void desenhaFarol() {// Função que chama as outras funçoes de desenho do farol inteiro

	// Chamada da função que desenha o corpo da torre
	desenhaCorpoTorre();

	glPushMatrix();
	glDisable(GL_TEXTURE_2D);
	glTranslatef(0, 2.7, 0);
	// Chamada da função que desenha as pilastras 
	posicionaPilastras();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(.5, 3.8, -.5);
	// Chamada da função que desenha o telhado
	desenhaTelhado();
	glTranslatef(0.5, 2.2, -0.4);
	glPopMatrix();

	glPushMatrix();
	// Chamada da função que desenha o cone
	glTranslatef(0.5, 3.5, -0.4);
	glRotatef(anguloCone, 0, 1, 0);
	desenhaCone();
	glEnable(GL_TEXTURE_2D);
	glPopMatrix();
}

void init(void){
	glClearColor(corCeu[0], corCeu[1],corCeu[2], 0);
	glShadeModel(GL_SMOOTH);
	criaTextura();
	glTexImage2D(GL_TEXTURE_2D, 0, 3, COLUNAS_TEXTURA, LINHAS_TEXTURA, 0, GL_RGB,
				 GL_UNSIGNED_BYTE, dadosTextura);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	GLfloat corTextura[4] = {.9, .9, .9, 0};

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_BLEND);

	glTexEnvfv(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, corTextura);

	glEnable(GL_TEXTURE_2D);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

void display(void){//Função de desenho
	if(noite){
			glDisable(GL_LIGHT0);
			if(LigaIluminacao){

				glEnable(GL_LIGHT1);
			}else{
				glDisable(GL_LIGHT1);
			}
			corCeu[0] = 0;
			corCeu[1] = 0;
			corCeu[2] = 0.35;
		}else{
			glDisable(GL_LIGHT1);
			glEnable(GL_LIGHT0);
			corCeu[0] = .67;
			corCeu[1] = .84;
			corCeu[2] = 0.9;
		}
	glClearColor(corCeu[0], corCeu[1],corCeu[2], 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	glLightfv(GL_LIGHT0,GL_AMBIENT,globalAmb);
	glLightfv(GL_LIGHT0,GL_POSITION,posicaoLuzAmbiente);
	glLightfv(GL_LIGHT1,GL_DIFFUSE,globalDifusa);
	glPushMatrix();
	glTranslatef(1.5,2,0);
	glRotatef(anguloCone,0,1,0);
	glLightfv(GL_LIGHT1,GL_POSITION,posicaoLuzDifusa);
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_DEPTH_TEST);
	glPopMatrix();

	glPushMatrix();
	glRotatef(anguloHorizontal, 0, 1, 0);
	glRotatef(anguloVertical, 1, 0, 0);
	glTranslatef(0, -2, 2);
	desenhaFarol();
	glPopMatrix();

		if(noite){

			glPushMatrix();
			desenhaEstrelas();
			glPopMatrix();
			corCeu[0] = 0;
			corCeu[1] = 0;
			corCeu[2] = 0.35;
			
		}else{

			glPushMatrix();
			glColor3f(1.0, 1.0, 0.0);
			desenhaSol();
			glPopMatrix();
			corCeu[0] = .67;
			corCeu[1] = .84;
			corCeu[2] = 0.9;
			
		}

	glutSwapBuffers();
}

void reshape(int w, int h){//Função que fica redesenhando
	glViewport(0, 0, static_cast<GLsizei>(w), static_cast<GLsizei>(h));
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	prop  = static_cast<GLsizei>(w)/static_cast<GLsizei>(h);
	gluPerspective(100, static_cast<GLfloat>(w) / static_cast<GLfloat>(h), 1, 20);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0, 0, -5);
}

void opcoesTeclado(unsigned char key, int x, int y){//Função para configurar as teclas do teclado
	switch (key){
	case 27:
		exit(0);
		break;
	case 'g':
		// Rotaciona cone sentido horario
		rotacionaCone(false);
		break;
	case 'G':
		// Rotaciona cone sentido anti-horario
		rotacionaCone(true);
		break;
	 case 'l':
	 	// Liga iluminação ambiente
	 	glEnable(GL_LIGHT0);
		noite = false;
		LigaIluminacao = false;
		break;
	 case 'L':
	 	// Desliga iluminação ambiente
	 	glDisable(GL_LIGHT0);
		noite = true;
		LigaIluminacao = true;
	 	break;
	case 'j':
		if(noite){
			LigaIluminacao = true;
			//glEnable(GL_LIGHT1);
		}
		break;
	case 'J':
		LigaIluminacao = false;
		//glDisable(GL_LIGHT1);
		break;
	case 'f':
		//Liga a animação
		ligaDesligaAnimacao();
		realizaAnimacao(NULL);
		break;
	case 'F':
		//Desliga a animação
		ligaDesligaAnimacao();
		break;
	case 'p':
		//Liga a textura
		LigaTextura = false;
		ligaDesligaTextura();
		break;
	case 'P':
		//Desliga a textura
		LigaTextura = true;
		ligaDesligaTextura();
		break;
	default:
		break;
	}

	glutPostRedisplay();
}

void opcoesMouse(int button, int state, int x, int y)//Função que configura os botoes do mouse
{
	if (button == GLUT_LEFT_BUTTON){
		rodaHorario();
	}
	else if (button == GLUT_RIGHT_BUTTON){
		rodaVerticalmente();
	}

	glutPostRedisplay();
}

void setas(int teclas, GLint x, GLint y){//Função que configura as setas do teclado
	switch (teclas)
	{
	case GLUT_KEY_UP:
		velocidade -= 1000;
		break;
	case GLUT_KEY_DOWN:
		velocidade += 1000;
		break;
	case GLUT_KEY_LEFT:
		rodaAntiHorario();
		break;
	case GLUT_KEY_RIGHT:
		rodaHorario();
		break;
	}

	glutPostRedisplay();
}

int main(int argc, char **argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(0, 0);
	glutCreateWindow(argv[0]);
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(opcoesTeclado);
	glutMouseFunc(opcoesMouse);
	glutSpecialFunc(setas);
	glutMainLoop();
	return 0;
}