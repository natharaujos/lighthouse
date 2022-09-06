#define _USE_MATH_DEFINES

#include <windows.h>
#include "glut.h"
#include <cmath>
#define LINHAS_DA_IMAGEM 60
#define COLUNAS_DA_IMAGEM 60

int anguloTotal, anguloTotalX, eixoNormal, sinalNormal;
bool iluminacaoLigada, texturaLigada, ativarAnimacao;
GLubyte dadosDaImagem[LINHAS_DA_IMAGEM][COLUNAS_DA_IMAGEM][3];

void geraImagemTextura()
{ // FUNÇÃO PARA CARREGAR AS TEXTURAS
	int valor;
	for (int linha = 0; linha < LINHAS_DA_IMAGEM; linha++)
	{
		for (int coluna = 0; coluna < COLUNAS_DA_IMAGEM; coluna++)
		{
			valor = (((linha & 0x2) == 0) ^ ((coluna & 0x4) == 0)) * 255;
			dadosDaImagem[linha][coluna][0] = (GLubyte)valor;
			dadosDaImagem[linha][coluna][1] = (GLubyte)valor;
			dadosDaImagem[linha][coluna][2] = (GLubyte)valor;
		}
	}
}

GLfloat *calculaNorma()
{
	static GLfloat norma[] = {0, 0, 0};
	norma[eixoNormal] = sinalNormal * 1;
	return norma;
}

void transladaSentidoHorario()
{
	anguloTotal = (anguloTotal + 10) % 360;
}

void transladaVerticalmente()
{
	anguloTotalX = (anguloTotalX + 10) % 360;
}

void statusAnimacao()
{
	ativarAnimacao = !ativarAnimacao;
}

void ligaIluminacao() //ATIVA E DESATIVA A ILUMINAÇÃO
{
	GLfloat mat_specular[] = {1, 1, 1, 1};
	GLfloat mat_shininess[] = {50};
	GLfloat light_position[] = {1, 1, 1, 0};
	glShadeModel(GL_SMOOTH);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glEnable(GL_COLOR_MATERIAL);

	if (!iluminacaoLigada)
	{
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		glEnable(GL_DEPTH_TEST);
	}
	else if (iluminacaoLigada)
	{
		glDisable(GL_LIGHTING);
		glDisable(GL_LIGHT0);
		glDisable(GL_DEPTH_TEST);
	}
}

void textura()
{
	if (texturaLigada)
	{
		glDisable(GL_TEXTURE_2D);
		texturaLigada = false;
	}
	else if(!texturaLigada)
	{
		glEnable(GL_TEXTURE_2D);
		texturaLigada = true;
	}
}

void desenhaParteCima() //DESENHA O TELHADO
{
	glPushMatrix();
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(1, 0, 0); //VERMELHO
	glVertex3f(0.5, 2.2, -0.4);
	glNormal3f(0, 1 / M_SQRT2, 1 / M_SQRT2);
	glVertex3f(0.1, 1.2, 0);
	glVertex3f(0.1 + 0.8, 1.2, 0);
	glNormal3f(1 / M_SQRT2, 1 / M_SQRT2, 0);
	glVertex3f(0.1 + 0.8, 1.2, -1);
	glNormal3f(0, -1 / M_SQRT2, -1 / M_SQRT2);
	glVertex3f(0.1, 1.2, -1);
	glNormal3f(-1 / M_SQRT2, -1 / M_SQRT2, 0);
	glVertex3f(0.1, 1.2, 0);
	glEnd();
	glPopMatrix();
}

void desenhaFaceMeio() //DESENHA AS FACES DAS PILASTRAS DO MEIO QUE "SEGURAM" O TELHADO
{
	glPushMatrix();
	glBegin(GL_POLYGON);
	glNormal3fv(calculaNorma());
	glVertex3f(0.1, 0, 0);
	glVertex3f(0.25, 0, 0);
	glVertex3f(0.25, 1.2, 0);
	glVertex3f(0.1, 1.2, 0);

	glEnd();
	glPopMatrix();

	sinalNormal = -1 * sinalNormal;

	glPushMatrix();
	glRotatef(180, 0, 1, 0);
	glTranslatef(-1, 0, 0);
	glBegin(GL_POLYGON);
	glNormal3fv(calculaNorma());
	glVertex3f(0.1, 0, 0);
	glVertex3f(0.25, 0, 0);
	glVertex3f(0.25, 1.2, 0);
	glVertex3f(0.1, 1.2, 0);
	glEnd();
	glPopMatrix();

	sinalNormal = -1 * sinalNormal;
}

void desenhaParteMeio() //FUNÇÃO QUE CHAMA O MÉTODO desenhaFaceMeio() PARA DESENHAR AS PILASTRAS EM SEUS RESPECTIVOS LUGARES
{
	eixoNormal = 2;
	sinalNormal = 1;

	glPushMatrix();
	glTranslatef(0, 0, -0.1);
	desenhaFaceMeio();
	glPopMatrix();

	sinalNormal = -1;

	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glTranslatef(0, 0, 0.1);
	desenhaFaceMeio();
	glPopMatrix();

	sinalNormal = 1;

	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glTranslatef(0, 0, 0.9);
	desenhaFaceMeio();
	glPopMatrix();

	sinalNormal = -1;

	glPushMatrix();
	glTranslatef(0, 0, -0.9);
	desenhaFaceMeio();
	glPopMatrix();
}

void desenhaParteBaixo() //DESENHA O CORPO DA TORRE
{
	eixoNormal = 2;
	sinalNormal = 1;
	glColor3f(1, 0, 0); //VERMELHO

	//glTexCoord2f SAO AS COORDENADAS DAS TEXTURAS QUE SÃO DESIGNADAS AOS VÉRTICES QUE ESTÃO ABAIXO
	//## DESENHA PARTE DA FRENTE
	glPushMatrix();
	glBegin(GL_QUADS);
	glNormal3fv(calculaNorma());
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0, 3, 0);
	//glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1, 3, 0);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1, -1, 0);
	//glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0, -1, 0);
	sinalNormal = -1 * sinalNormal;
	glEnd();
	glPopMatrix(); 

	//DESENHA LADO ESQUERDO
	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glBegin(GL_QUADS);
	glNormal3fv(calculaNorma());
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0, 3, 0);
	//glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1, 3, 0);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1, -1, 0);
	//glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0, -1, 0);
	sinalNormal = -1 * sinalNormal;
	glEnd();
	glPopMatrix();

	
	//desenha lado direito
	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glTranslatef(0, 0, 1);
	glBegin(GL_QUADS);
	glNormal3fv(calculaNorma());
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0, 3, 0);
	//glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1.0, 3, 0);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1, -1, 0);
	//glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0, -1, 0);
	sinalNormal = -1 * sinalNormal;
	glEnd();
	glPopMatrix();
	
	//desenha parte de tras
	 glPushMatrix();
	glTranslatef(0, 0, -1);
	glBegin(GL_QUADS);
	glNormal3fv(calculaNorma());
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0, 3, 0);
	//glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1.0, 3, 0);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1, -1, 0);
	//glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0, -1, 0);
	sinalNormal = -1 * sinalNormal;
	glEnd();
	glPopMatrix();

	glColor3f(1, 1, 1); //VERMELHO
	
	//parte de cima (farol fica aqui em cima)
	glPushMatrix();
	glBegin(GL_QUADS);
	glNormal3fv(calculaNorma());
	glVertex3f(0, 3, 0);
	glVertex3f(1, 3, 0);
	glVertex3f(1, 3, -1);
	glVertex3f(0, 3, -1);
	sinalNormal = -1 * sinalNormal;
	glEnd();
	glPopMatrix(); 
}

void desenhaTorre() //DESENHA A TORRE COMPLETA
{
	//FUNÇÃO QUE DESENHA O CORPO DA TORRE
	desenhaParteBaixo();

	glPushMatrix();
	glTranslatef(0, 3, 0);
	//FUNÇÃO QUE DESENHA O PILARES QUE SEGURA O TELHADO
	desenhaParteMeio();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 3, 0);
	//FUNÇÃO QUE DESENHA O TELHADO
	desenhaParteCima();
	glTranslatef(0.5, 2.2, -0.4);
	glPopMatrix();

}

void init(void)
{
	glClearColor(1, 1, 1, 0);
	geraImagemTextura();
	//FUNÇÕES QUE ATRIBUEM OS PARÂMETROS DAS TEXTURAS
	glTexImage2D(GL_TEXTURE_2D, 0, 3, COLUNAS_DA_IMAGEM, LINHAS_DA_IMAGEM, 0, GL_RGB,
				 GL_UNSIGNED_BYTE, dadosDaImagem);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	//FUNÇÃO PARA HABILITAR A TEXTURA
	glEnable(GL_TEXTURE_2D);
	//FUNÇÃO PARA CORRIGIR A TEXTURA QUANDO OCORRE MUDANÇA DE PERSPECTIVA
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glColor3f(0, 0, 0); //CINZA CLARO

	glPushMatrix();
	glRotatef(anguloTotal, 0, 1, 0);
	glRotatef(anguloTotalX, 1, 0, 0);
	glTranslatef(0, -2, 2);
	desenhaTorre();
	glPopMatrix();

	glutSwapBuffers();
}

void reshape(int w, int h)
{
	glViewport(0, 0, static_cast<GLsizei>(w), static_cast<GLsizei>(h));
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(100, static_cast<GLfloat>(w) / static_cast<GLfloat>(h), 1, 20);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0, 0, -5);
}

void opcoesTeclado(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27:
		exit(0);
		break;
	case 'm':
		//MOVE APENAS O PONTEIRO DE MINUTO
		//mexePonteiroMinuto();
		break;
	case 'h':
		//MOVE APENAS O PONTEIRO DE HORA
		//mexePonteiroHora();
		break;
	case 'l':
		//ATIVA ILUMINAÇÃO
		iluminacaoLigada = true;
		ligaIluminacao();
		break;
	case 'L':
		//DESATIVA ILUMINAÇÃO
		iluminacaoLigada = false;
		ligaIluminacao();
		break;
	case 'p':
		texturaLigada = false;
		textura();
		break;
	case 'P':
		texturaLigada = true;
		textura();
		break;
	default:
		break;
	}

	glutPostRedisplay();
}

void opcoesMouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON)
	{
		//MUDA O ÂNGULO, DANDO A IMPRESSÃO DE TRANSLADAR NO SENTIDO HORÁRIO
		transladaSentidoHorario();
	}
	else if (button == GLUT_RIGHT_BUTTON)
	{
		//MUDA O ÂNGULO, DANDO A IMPRESSÃO DE TRANSLADAR VERTICALMENTE
		transladaVerticalmente();
	}

	glutPostRedisplay();
}

int main(int argc, char **argv)
{
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
	glutMainLoop();
	return 0;
}