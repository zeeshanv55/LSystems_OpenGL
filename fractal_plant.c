//  Compile as
//  gcc fractal_plant.c -o fractal_plant -lGL -lGLU -lglut -lm

//  Run as
//  ./fractal_plant

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#define ESCAPE '\033'

char lsystem[5000000];
char lsystem_copy[5000000];
GLint Width = 1680;
GLint Height = 1024;

float current_x = 950.0;
float current_y = 525.0;
float next_x = 500.0;
float next_y = 500.0;
float angle = (25.0 * (3.14/180.0));
float direction = (200.0 * (3.14/180.0));
float line_size = 0.85;	

float direction_stack[1000000];
float x_position_stack[1000000];
float y_position_stack[1000000];

int direction_stack_top = -1;
int x_position_stack_top = -1;
int y_position_stack_top = -1;

void stack_push()
{
	direction_stack[++direction_stack_top] = direction;
	x_position_stack[++x_position_stack_top] = current_x;
	y_position_stack[++y_position_stack_top] = current_y;
}

void stack_pop()
{
	direction = direction_stack[direction_stack_top--];
	current_x = x_position_stack[x_position_stack_top--];
	current_y = y_position_stack[y_position_stack_top--];
}

int productionX(int toposition)
{
	lsystem[toposition] =    'F';
	lsystem[toposition+1] =  '-';
	lsystem[toposition+2] =  '[';
	lsystem[toposition+3] =  '[';
	lsystem[toposition+4] =  'X';
	lsystem[toposition+5] =  ']';
	lsystem[toposition+6] =  '+';
	lsystem[toposition+7] =  'X';
	lsystem[toposition+8] =  ']';
	lsystem[toposition+9] =  '+';
	lsystem[toposition+10] = 'F';
	lsystem[toposition+11] = '[';
	lsystem[toposition+12] = '+';
	lsystem[toposition+13] = 'F';
	lsystem[toposition+14] = 'X';
	lsystem[toposition+15] = ']';
	lsystem[toposition+16] = '-';
	lsystem[toposition+17] = 'X';

	return (18);	
}

int productionF(int toposition)
{
	lsystem[toposition] = 'F';
	lsystem[toposition+1] = 'F';

	return (2);	
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
			
			case 'X':
				lsystem_index += productionX(lsystem_index);
				break;

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

	int i;
	for (i=0; lsystem[i]!='\0'; i++)
	{
		switch (lsystem[i])
		{
			case 'F':
				next_x = current_x + (line_size*cos(direction));
				next_y = current_y + (line_size*sin(direction));

				glBegin(GL_LINES);
     				glVertex2f(current_x, current_y);
      				glVertex2f(next_x, next_y);
    				glEnd();

				current_x = next_x;
				current_y = next_y;
				break;

			case '[':
				stack_push();
				break;

			case ']':
				stack_pop();
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
	lsystem[0] = 'X';
	lsystem[1] = '\0';

	int i;
	for (i=0; i<9; i++)
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
