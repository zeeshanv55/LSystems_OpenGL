//  Compile as
//  gcc gosper_curve.c -o gosper_curve -lGL -lGLU -lglut -lm

//  Run as
//  ./gosper_curve

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#define ESCAPE '\033'

char lsystem[1000000];
char lsystem_copy[1000000];
GLint Width = 1680;
GLint Height = 1024;

int productionA(int toposition)
{
	lsystem[toposition] = 'A';
	lsystem[toposition+1] = '-';
	lsystem[toposition+2] = 'B';
	lsystem[toposition+3] = '-';
	lsystem[toposition+4] = '-';
	lsystem[toposition+5] = 'B';
	lsystem[toposition+6] = '+';
	lsystem[toposition+7] = 'A';
	lsystem[toposition+8] = '+';
	lsystem[toposition+9] = '+';
	lsystem[toposition+10] = 'A';
	lsystem[toposition+11] = 'A';
	lsystem[toposition+12] = '+';
	lsystem[toposition+13] = 'B';
	lsystem[toposition+14] = '-';

	return (15);	
}

int productionB(int toposition)
{
	lsystem[toposition] = '+';
	lsystem[toposition+1] = 'A';
	lsystem[toposition+2] = '-';
	lsystem[toposition+3] = 'B';
	lsystem[toposition+4] = 'B';
	lsystem[toposition+5] = '-';
	lsystem[toposition+6] = '-';
	lsystem[toposition+7] = 'B';
	lsystem[toposition+8] = '-';
	lsystem[toposition+9] = 'A';
	lsystem[toposition+10] = '+';
	lsystem[toposition+11] = '+';
	lsystem[toposition+12] = 'A';
	lsystem[toposition+13] = '+';
	lsystem[toposition+14] = 'B';

	return (15);	
}

void runIteration()
{
	int i;

	for (i=0; lsystem[i]!='\0'; i++)
	{
		lsystem_copy[i] = lsystem[i];
	}

	int lsystem_index = 0;
	for (i=0; lsystem_copy[i]!='\0'; i++)
	{
		switch (lsystem_copy[i])
		{
			
			case 'A':
				lsystem_index += productionA(lsystem_index);
				break;
			case 'B':
				lsystem_index += productionB(lsystem_index);
				break;
			default:
				lsystem[lsystem_index] = lsystem_copy[i];
				lsystem_index++;
				break;
		}
	}
	
	lsystem[lsystem_index] = '\0';

	printf("\n%d", lsystem_index);
}

void Display(void)
{
    	glClearColor(0, 0, 0, 1);
    	glClear(GL_COLOR_BUFFER_BIT);

    	glColor3ub(255,255,255);
	
	float current_x = 1180.0;
	float current_y = 250.0;
	float next_x = current_x;
	float next_y = current_y;
	float angle = (3.14/3.0);
	float direction = 0.0;
	float line_size = 2.3;	

	int i;
	for (i=0; lsystem[i]!='\0'; i++)
	{
		switch (lsystem[i])
		{
			case 'A':
			case 'B':
				current_x = next_x;
				current_y = next_y;
				next_x = current_x + (line_size*cos(direction));
				next_y = current_y + (line_size*sin(direction));

				glBegin(GL_LINES);
     				glVertex2f(current_x, current_y);
      				glVertex2f(next_x, next_y);
    				glEnd();
				break;

			case '-':
				direction += angle;
				break;

			case '+':
				direction -= angle;
				break;
			
			case '\0':
				break;			
		}
	}

    	glFinish();
}

void Reshape(GLint w, GLint h)
{
    	Width = w;
    	Height = h;
    	glViewport(0, 0, w, h);

    	glMatrixMode(GL_PROJECTION);
    	glLoadIdentity();
    	glOrtho(0, w, 0, h, -1.0, 1.0);

    	glMatrixMode(GL_MODELVIEW);
    	glLoadIdentity();
}

void Keyboard(unsigned char key, int x, int y)
{
    if( key == ESCAPE )
        exit(0);
}

int main(int argc, char *argv[])
{
	lsystem[0] = 'A';
	lsystem[1] = '\0';

	int i;
	for (i=0; i<6; i++)
	{
		runIteration();
	}	

	//printf("\n%s\n", lsystem);
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowSize(Width, Height);
	glutCreateWindow("L-System Test");

	glutDisplayFunc(Display);	
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);

	glutMainLoop();

	return (0);
}
