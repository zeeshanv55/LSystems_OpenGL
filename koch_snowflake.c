//  Compile as
//  gcc koch_snowflake.c -o koch_snowflake -lGL -lGLU -lglut -lm

//  Run as
//  ./koch_snowflake

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

int productionF(int toposition)
{
	lsystem[toposition] = 'F';
	lsystem[toposition+1] = '-';
	lsystem[toposition+2] = 'F';
	lsystem[toposition+3] = '+';
	lsystem[toposition+4] = '+';
	lsystem[toposition+5] = 'F';
	lsystem[toposition+6] = '-';
	lsystem[toposition+7] = 'F';
	
	return (8);	
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
			case 'F':
				lsystem_index += productionF(lsystem_index);
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
	
	float current_x = 400.0;
	float current_y = 275.0;
	float next_x = current_x;
	float next_y = current_y;
	float angle = (3.14/3.0);
	float direction = 0.0;
	float line_size = 1.1;	

	int i;
	for (i=0; lsystem[i]!='\0'; i++)
	{
		switch (lsystem[i])
		{
			case 'F':
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
				direction -= angle;
				break;

			case '+':
				direction += angle;
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
	lsystem[0] = 'F';
	lsystem[1] = '+';
	lsystem[2] = '+';
	lsystem[3] = 'F';
	lsystem[4] = '+';
	lsystem[5] = '+';
	lsystem[6] = 'F';
	lsystem[7] = '\0';

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
