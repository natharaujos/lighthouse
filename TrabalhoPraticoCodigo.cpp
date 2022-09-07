
#include <windows.h>
#include "glut.h"

#define _USE_MATH_DEFINES
#define COLUNAS_TEXTURA 60
#define LINHAS_TEXTURA 60

int anguloHorizontal, anguloVertical;
int eixoDaNormal, sinalDaNormal;
int anguloCone = 180; 
int velocidade = 8000;
bool LigaIluminacao, LigaTextura, LigaAnimacao;//, rotacaoAutomatica;
GLubyte dadosTextura[LINHAS_TEXTURA][COLUNAS_TEXTURA][3];

void criaTextura(){ // FUNÇÃO PARA CARREGAR AS TEXTURAS
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

void rodaHorario(){
	anguloHorizontal = (anguloHorizontal +=10) % 360;
}

void rodaAntiHorario(){
	anguloHorizontal = (anguloHorizontal -= 10) % 360;
}

void realizaAnimacao(int NULO){
	if (!LigaAnimacao){
		glutSwapBuffers();
		return;
	}else{

		glutPostRedisplay();
		anguloCone = (anguloCone += 50) % 360;
		glutTimerFunc(velocidade / 60, realizaAnimacao, NULL);
	
	}

}

void rotacionaCone(bool antihorario){

	if (antihorario){

		anguloCone = (anguloCone - 10) % 360;
	}else{
		anguloCone = (anguloCone + 10) % 360;
	}
}

void rodaVerticalmente(){
	anguloVertical = (anguloVertical + 10) % 360;
}

void ligaDesligaAnimacao(){
	LigaAnimacao = !LigaAnimacao;
}

void desenhaEstrelas(){

	glColor3f(1,1,1);
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
}

void ligaIluminacao() {// ATIVA E DESATIVA A ILUMINAÇÃO
	GLfloat specular[] = {1, 1, 1, 1};
	GLfloat shininess[] = {50};
	GLfloat lightPosition[] = {1, 3, 1, 0};
	glShadeModel(GL_SMOOTH);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
	glEnable(GL_COLOR_MATERIAL);

	if (!LigaIluminacao){
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		glEnable(GL_DEPTH_TEST);
	}else{
		glDisable(GL_LIGHTING);
		glDisable(GL_LIGHT0);
		glDisable(GL_DEPTH_TEST);
	}
}

void ligaDesligaTextura(){
	if (LigaTextura){
		glDisable(GL_TEXTURE_2D);
		LigaTextura = false;
	}else{
		glEnable(GL_TEXTURE_2D);
		LigaTextura = true;
	}
}

void desenhaTelhado(){// DESENHA O TELHADO
	glColor3f(1, 0, 0);
	glRotatef(270, 1, 0, 0);
	glutSolidCone(.8, 2, 25, 25);
}

void alteraNormal(){
	sinalDaNormal = -1 * sinalDaNormal;
}

void desenhaPilastras() {// DESENHA AS FACES DAS PILASTRAS DO MEIO QUE "SEGURAM" O TELHADO
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

void posicionaPilastras() {// FUNÇÃO QUE CHAMA O MÉTODO desenhaPilastras() PARA DESENHAR AS PILASTRAS EM SEUS RESPECTIVOS LUGARES
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

void desenhaCorpoTorre() // DESENHA O CORPO DA TORRE
{
	eixoDaNormal = 2;
	sinalDaNormal = 1;
	glColor3f(1, 0, 0); // VERMELHO

	// glTexCoord2f SAO AS COORDENADAS DAS TEXTURAS QUE SÃO DESIGNADAS AOS VÉRTICES QUE ESTÃO ABAIXO
	//## DESENHA PARTE DA FRENTE
	glPushMatrix();
	glBegin(GL_QUADS);
	glNormal3fv(getNormal());
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0, 3, 0);
	// glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1, 3, 0);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1, -1, 0);
	// glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0, -1, 0);
	alteraNormal();
	glEnd();
	glPopMatrix();

	// DESENHA LADO ESQUERDO
	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glBegin(GL_QUADS);
	glNormal3fv(getNormal());
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0, 3, 0);
	// glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1, 3, 0);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1, -1, 0);
	// glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0, -1, 0);
	alteraNormal();
	glEnd();
	glPopMatrix();

	// desenha lado direito
	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glTranslatef(0, 0, 1);
	glBegin(GL_QUADS);
	glNormal3fv(getNormal());
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0, 3, 0);
	// glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1.0, 3, 0);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1, -1, 0);
	// glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0, -1, 0);
	alteraNormal();
	glEnd();
	glPopMatrix();

	// desenha parte de tras
	glPushMatrix();
	glTranslatef(0, 0, -1);
	glBegin(GL_QUADS);
	glNormal3fv(getNormal());
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0, 3, 0);
	// glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1.0, 3, 0);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1, -1, 0);
	// glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0, -1, 0);
	alteraNormal();
	glEnd();
	glPopMatrix();

	glColor3f(1, 1, 1); // VERMELHO

	// parte de cima (farol fica aqui em cima)
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

void desenhaCone(){
	glColor3f(.33, .33, .33);
	glutSolidCone(.25, .33, 25, 25);
}

void desenhaFarol() {// DESENHA A TORRE COMPLETA

	// FUNÇÃO QUE DESENHA O CORPO DA TORRE
	desenhaCorpoTorre();

	glPushMatrix();
	glDisable(GL_TEXTURE_2D);
	glTranslatef(0, 2.7, 0);
	// FUNÇÃO QUE DESENHA O PILARES QUE SEGURA O TELHADO
	posicionaPilastras();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(.5, 3.8, -.5);
	// FUNÇÃO QUE DESENHA O TELHADO
	desenhaTelhado();
	glTranslatef(0.5, 2.2, -0.4);
	glPopMatrix();

	glPushMatrix();
	// FUNÇÃO QUE DESENHA O CONE
	glTranslatef(0.5, 3.5, -0.4);
	glRotatef(anguloCone, 0, 1, 0);
	desenhaCone();
	glEnable(GL_TEXTURE_2D);
	glPopMatrix();
}

void init(void){
	glClearColor(0, 0, 0.35, 0);
	criaTextura();
	// FUNÇÕES QUE ATRIBUEM OS PARÂMETROS DAS TEXTURAS
	glTexImage2D(GL_TEXTURE_2D, 0, 3, COLUNAS_TEXTURA, LINHAS_TEXTURA, 0, GL_RGB,
				 GL_UNSIGNED_BYTE, dadosTextura);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	GLfloat corTextura[4] = {.9, .9, .9, 0};

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_BLEND);

	glTexEnvfv(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, corTextura);

	// FUNÇÃO PARA HABILITAR A TEXTURA
	glEnable(GL_TEXTURE_2D);
	// FUNÇÃO PARA CORRIGIR A TEXTURA QUANDO OCORRE MUDANÇA DE PERSPECTIVA
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

void display(void){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	glPushMatrix();
	glRotatef(anguloHorizontal, 0, 1, 0);
	glRotatef(anguloVertical, 1, 0, 0);
	glTranslatef(0, -2, 2);
	desenhaFarol();
	glPopMatrix();

	desenhaEstrelas();
	glutSwapBuffers();
}

void reshape(int w, int h){
	glViewport(0, 0, static_cast<GLsizei>(w), static_cast<GLsizei>(h));
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(100, static_cast<GLfloat>(w) / static_cast<GLfloat>(h), 1, 20);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0, 0, -5);
}

void opcoesTeclado(unsigned char key, int x, int y){
	switch (key){
	case 27:
		exit(0);
		break;
	case 'g'://
		// MOVE cone horario
		rotacionaCone(false);
		break;
	case 'G'://
		// MOVE cone anti-horario
		rotacionaCone(true);
		break;
	case 'l'://
		// ATIVA ILUMINAÇÃO
		LigaIluminacao = true;
		ligaIluminacao();
		break;
	case 'L'://
		// DESATIVA ILUMINAÇÃO
		LigaIluminacao = false;
		ligaIluminacao();
		break;
	case 'f'://
		ligaDesligaAnimacao();
		realizaAnimacao(NULL);
		break;
	case 'F'://
		ligaDesligaAnimacao();
		break;
	case 'p'://
		LigaTextura = false;
		ligaDesligaTextura();
		break;
	case 'P'://
		LigaTextura = true;
		ligaDesligaTextura();
		break;
	default:
		break;
	}

	glutPostRedisplay();
}

void opcoesMouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON){
		// MUDA O ÂNGULO, DANDO A IMPRESSÃO DE TRANSLADAR NO SENTIDO HORÁRIO
		rodaHorario();
	}
	else if (button == GLUT_RIGHT_BUTTON){
		// MUDA O ÂNGULO, DANDO A IMPRESSÃO DE TRANSLADAR VERTICALMENTE
		rodaVerticalmente();
	}

	glutPostRedisplay();
}

void setas(int teclas, GLint x, GLint y){
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