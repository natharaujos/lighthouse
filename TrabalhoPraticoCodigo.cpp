#define _USE_MATH_DEFINES

#include <windows.h>
#include "glut.h"
#include <cmath>
#define LINHAS_DA_IMAGEM 64
#define COLUNAS_DA_IMAGEM 64

int anguloTotal, anguloTotalX, anguloSino, anguloBadalo, anguloMinutos, anguloHoras, eixoNormal, sinalNormal;
bool sinoPositivo, iluminacaoLigada, texturaLigada, ativarAnimacao;
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

double ptsMeio[][2] = {
	{0.1, 0},
	{0.2, 0},
	{0.1, 0.8},
	{0.2, 0.7},
	{0.1, 1},
	{0.5, 1},
	{0.1, 1.2},
	{0.5, 1.2}};

double ptsBaixo[][2] = {
	{0, 0},
	{0.2, 0},
	{0, 0.8},
	{0.2, 0.7},
	{0, 1},
	{0.5, 1},
	{0, 3},
	{0.2, 3},
	{0.5, 3.3},
	{0.5, 3}};

GLfloat *calculaNorma()
{
	static GLfloat norma[] = {0, 0, 0};
	norma[eixoNormal] = sinalNormal * 1;
	return norma;
}

/* void mexePonteiroMinuto()
{
	anguloMinutos = (anguloMinutos - 5) % 360;
}

void mexePonteiroHora() 
{
	anguloHoras = (anguloHoras - 5) % 360;
}
*/

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

void ilumina() //ATIVA E DESATIVA A ILUMINAÇÃO
{
	GLfloat mat_specular[] = {1, 1, 1, 1};
	GLfloat mat_shininess[] = {50};
	GLfloat light_position[] = {1, 1, 1, 0};
	glShadeModel(GL_SMOOTH);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glEnable(GL_COLOR_MATERIAL);

	if (iluminacaoLigada)
	{
		glDisable(GL_LIGHTING);
		glDisable(GL_LIGHT0);
		glDisable(GL_DEPTH_TEST);
		iluminacaoLigada = false;
	}

	else
	{
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		glEnable(GL_DEPTH_TEST);
		iluminacaoLigada = true;
	}
}

void textura()
{
	if (texturaLigada)
	{
		glDisable(GL_TEXTURE_2D);
		texturaLigada = false;
	}
	else
	{
		glEnable(GL_TEXTURE_2D);
		texturaLigada = true;
	}
}

void animacao(int null) //DEFINE O COMPORTAMENTO DOS PONTEIROS DE HORA E MINUTO E DO SINO COM O BADALO
{
	if (!ativarAnimacao)
		return;

	glutPostRedisplay();
	anguloMinutos = (anguloMinutos - 1) % 360;

	if (anguloMinutos % 72 == 0)
	{
		anguloHoras = ((anguloHoras - 6) % 360);
	}

	if (sinoPositivo)
	{
		if ((anguloSino + 1) % 360 < 8)
		{
			anguloSino = (anguloSino + 1) % 360;
			anguloBadalo = (anguloBadalo - (1 + 2)) % 360;
		}
		else
		{
			sinoPositivo = !sinoPositivo;
		}
	}

	else
	{
		if ((anguloSino - 1) % 360 > -8)
		{
			anguloSino = (anguloSino - 1) % 360;
			anguloBadalo = (anguloBadalo + (1 + 2)) % 360;
		}
		else
		{
			sinoPositivo = !sinoPositivo;
		}
	}
	glutTimerFunc(1000 / 60, animacao, NULL);
}

void quartoDeCirculo(double *extremaEsquerda, double *baixo, double *cima, int qtdPts) //DESENHA UM QUARTO DE UM CÍRCULO
{
	for (int i = 0; i <= qtdPts; i++)
	{
		double angulo = i * ((M_PI / 2) / qtdPts);
		double raio = cima[0] - baixo[0];
		double x = raio - (cos(angulo) * raio);
		x += baixo[0];
		double y = (sin(angulo) * raio);
		y += baixo[1];
		glVertex3f(x, y, 0);
		glVertex3f(extremaEsquerda[0], extremaEsquerda[1], 0);
	}
	glVertex3f(cima[0], cima[1], 0);
}

/* void desenhaCirculoCompleto(double raio) //DESENHA UM CÍRCULO COMPLETO A PARTIR DE 4 QUARTOS DE CÍRCULO
{
	double ptsAux[][2] = {{raio, 0}, {0, 0}, {raio, raio}};

	glPushMatrix();
	sinalNormal = 1;
	glBegin(GL_TRIANGLE_FAN);
	glNormal3fv(calculaNorma());
	quartoDeCirculo(ptsAux[0], ptsAux[1], ptsAux[2], 100);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glRotatef(180, 0, 1, 0);
	glTranslatef(-0.5, 0, 0);
	sinalNormal = -1;
	glBegin(GL_TRIANGLE_FAN);
	glNormal3fv(calculaNorma());
	quartoDeCirculo(ptsAux[0], ptsAux[1], ptsAux[2], 100);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glRotatef(180, 1, 0, 0);
	sinalNormal = -1;
	glPushMatrix();
	glBegin(GL_TRIANGLE_FAN);
	glNormal3fv(calculaNorma());
	quartoDeCirculo(ptsAux[0], ptsAux[1], ptsAux[2], 100);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glRotatef(180, 0, 1, 0);
	glTranslatef(-0.5, 0, 0);
	sinalNormal = 1;
	glBegin(GL_TRIANGLE_FAN);
	glNormal3fv(calculaNorma());
	quartoDeCirculo(ptsAux[0], ptsAux[1], ptsAux[2], 100);
	glEnd();
	glPopMatrix();

	glPopMatrix();
} */

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

/* void desenhaSino() //DESENHA O SINO
{
	glColor3f(1, 1, 0); //AMARELO

	glPushMatrix();
	glRotatef(anguloSino, 1, 0, 0);
	glRotatef(270, 1, 0, 0);
	glPushMatrix();
	gluCylinder(gluNewQuadric(), 0.15, 0.1, 0.1, 32, 32);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, 0.1);
	gluCylinder(gluNewQuadric(), 0.1, 0.1, 0.2, 32, 32);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, 0.3);
	gluCylinder(gluNewQuadric(), 0.1, 0, 0.1, 32, 32);
	glPopMatrix();

	//DESENHA O BADALO
	glPushMatrix();
	glColor3f(0.6, 0.3, 0.1); //MARROM
	glTranslatef(0, 0, 0.2);
	glRotatef(anguloBadalo, 1, 0, 0);
	glTranslatef(0.0, 0.0, -0.3);
	gluCylinder(gluNewQuadric(), 0.05, 0.05, 0.3, 32, 32);
	glutSolidSphere(0.06, 32, 32);
	glPopMatrix();

	glPopMatrix();
} */
/* 
void desenhaRelogio() //DESENHA O RELÓGIO
{
	//CIRCULO DO RELOGIO
	glPushMatrix();
	desenhaCirculoCompleto(0.25);
	glPushMatrix();
	glTranslatef(0.25, 0, 0);
	gluCylinder(gluNewQuadric(), 0.25, 0.25, 0.1, 32, 32);
	glPopMatrix();

	glTranslatef(0, 0, 0.1);
	desenhaCirculoCompleto(0.25);
	glTranslatef(0.25, 0, 0.01);

	//PONTEIRO MINUTO
	glPushMatrix();
	glRotatef(anguloMinutos, 0, 0, 1);
	glColor3f(1, 1, 1); //BRANCO
	glBegin(GL_QUADS);
	glVertex3f(0, 0, 0);
	glVertex3f(0.03, 0.15, 0);
	glVertex3f(0, 0.2, 0);
	glVertex3f(-0.03, 0.15, 0);
	glEnd();
	glPopMatrix();

	//PONTEIRO HORA
	glPushMatrix();
	glRotatef(anguloHoras, 0, 0, 1);
	glBegin(GL_QUADS);
	glVertex3f(0, 0, 0);
	glVertex3f(0.03, 0.1, 0);
	glVertex3f(0, 0.15, 0);
	glVertex3f(-0.03, 0.1, 0);
	glEnd();
	glPopMatrix();

	glPopMatrix();
}
 */
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
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1, 3, 0);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1, -1, 0);
	glTexCoord2f(0.0f, 1.0f);
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
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1.0, 3, 0);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1, -1, 0);
	glTexCoord2f(0.0f, 1.0f);
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
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1.0, 3, 0);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1, -1, 0);
	glTexCoord2f(0.0f, 1.0f);
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

	/* glPushMatrix();
	glTranslatef(0.5, 3.6, -0.5);
	//FUNÇÃO QUE DESENHA O SINO
	desenhaSino();
	glPopMatrix(); */

	/* glPushMatrix();
	glColor3f(0, 0, 1); //AZUL
	glTranslatef(0.25, 3, 0.01);
	//FUNÇÃO QUE DESENHA O RELÓGIO
	desenhaRelogio();
	glPopMatrix(); */
}

void init(void)
{
	glClearColor(0, 0, 0, 0);
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

	//INICIA POR PADRÃO COM A ILUMINAÇÃO E TEXTURA ATIVADAS
	ilumina();
	textura();
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
	case 'a':
		//ATIVA E DESATIVA A ANIMAÇÃO COMPLETA DO RELÓGIO E DO SINO
		statusAnimacao();
		animacao(NULL);
		break;
	case 'm':
		//MOVE APENAS O PONTEIRO DE MINUTO
		//mexePonteiroMinuto();
		break;
	case 'h':
		//MOVE APENAS O PONTEIRO DE HORA
		//mexePonteiroHora();
		break;
	case 'i':
		//ATIVA E DESATIVA A ILUMINAÇÃO
		ilumina();
		break;
	case 't':
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