#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#define ESCAPE '\033'

char nonTerminals[50];
char productions[50][100];
int grammarCount;
char lsystemString[5000000];
char drawSymbol[10];
char angleIncrementSymbol[10];
char angleDecrementSymbol[10];
char stackPushSymbol;
char stackPopSymbol;
int drawSymbolCount;
int angleIncrementSymbolCount;
int angleDecrementSymbolCount;
float start_x;
float start_y;
float start_angle;
float change_angle;
float line_size;
int iterations;
float direction_stack[1000000];
float x_position_stack[1000000];
float y_position_stack[1000000];
int direction_stack_top = -1;
int x_position_stack_top = -1;
int y_position_stack_top = -1;
GLint Width = 1920;
GLint Height = 1080;

float current_x;
float current_y;
float next_x;
float next_y;
float angle;
float direction;

void read_lsystem_file(char*);
void expand(int);
int production(char, int);
void display(void);
void reshape(GLint, GLint);
void keyboard(unsigned char, int, int);
void stack_push();
void stack_pop();


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

void display(void)
{
	current_x = start_x;
	current_y = start_y;
	next_x = current_x;
	next_y = current_y;
	angle = change_angle;
	direction = start_angle;

    	glClearColor(0, 0, 0, 1);
    	glClear(GL_COLOR_BUFFER_BIT);
    	glColor3ub(255,255,255);	

	int i, j;
	for (i=0; lsystemString[i]!='\0'; i++)
	{
		for (j=0; j<drawSymbolCount; j++) {
			if (lsystemString[i] == drawSymbol[j]) {
				next_x = current_x + (line_size*cos(direction));
				next_y = current_y + (line_size*sin(direction));

				glBegin(GL_LINES);
     				glVertex2f(current_x, current_y);
      				glVertex2f(next_x, next_y);
    				glEnd();

				current_x = next_x;
				current_y = next_y;
				break;
			}
		}

		for (j=0; j<angleIncrementSymbolCount; j++) {
			if (lsystemString[i] == angleIncrementSymbol[j]) {
				direction += angle;
				break;
			}
		}

		for (j=0; j<angleDecrementSymbolCount; j++) {		
			if (lsystemString[i] == angleDecrementSymbol[j]) {
				direction -= angle;
				break;
			}
		}

		if (lsystemString[i] == stackPushSymbol) {
			stack_push();
		}

		if (lsystemString[i] == stackPopSymbol) {
			stack_pop();
		}
	}

    	glFinish();
}

void reshape(GLint w, GLint h)
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

void keyboard(unsigned char key, int x, int y)
{
    if( key == ESCAPE )
        exit(0);
}

void read_lsystem_file(char filename[]) {
	FILE *file;
	char *line = NULL;
	size_t len = 0;
	int i, j;

	file = fopen(filename, "r");
	if (file == NULL) {
		printf("\nCannot open file. Exiting.\n");
		exit(EXIT_FAILURE);
	}

	while (getline(&line, &len, file) != -1) {
		if (strcmp(line, "_begin_grammar\n") == 0) {
			printf("\n%s\n", "Reading grammar...");
			i=0;
			while(1) {
				getline(&line, &len, file);
				if (strcmp(line, "_end_grammar\n") == 0)
					break;
	
				nonTerminals[i] = line[0];
				for (j=2; j<strlen(line); j++) {
					productions[i][j-2] = line[j];
				}
				
				if (productions[i][strlen(productions[i])-1] == '\n') {
					productions[i][strlen(productions[i])-1] = '\0';
				}

				printf("%c -> %s\n", nonTerminals[i], productions[i]);
				i++;
			}
			grammarCount = i;
		}
		else if (strcmp(line, "_begin_symbol_meanings\n") == 0){
			printf("\n%s\n", "Reading symbol meanings...");
			drawSymbolCount = 0;
			angleIncrementSymbolCount = 0;
			angleDecrementSymbolCount = 0;
			while(1) {
				getline(&line, &len, file);
				if (strcmp(line, "_end_symbol_meanings\n") == 0)
					break;
	
				if (strcmp(line, "draw\n") == 0) {
					getline(&line, &len, file);
					drawSymbol[drawSymbolCount++] = line[0];
				}

				if (strcmp(line, "increase_angle\n") == 0) {
					getline(&line, &len, file);
					angleIncrementSymbol[angleIncrementSymbolCount++] = line[0];
				}

				if (strcmp(line, "decrease_angle\n") == 0) {
					getline(&line, &len, file);
					angleDecrementSymbol[angleDecrementSymbolCount++] = line[0];
				}
				if (strcmp(line, "stack_push\n") == 0) {
					getline(&line, &len, file);
					stackPushSymbol = line[0];
					printf("\nStack push symbol read. %c", stackPushSymbol);
				}
				if (strcmp(line, "stack_pop\n") == 0) {
					getline(&line, &len, file);
					stackPopSymbol = line[0];
					printf("\nStack pop symbol read. %c", stackPopSymbol);
				}
			}
		}
		else if (strcmp(line, "_begin_config\n") == 0){
			printf("\n%s\n", "Reading other configurations...");
			while(1) {
				getline(&line, &len, file);
				if (strcmp(line, "_end_config\n") == 0)
					break;
	
				if (strcmp(line, "start_x\n") == 0) {
					getline(&line, &len, file);
					line[len-1] = '\0';
					start_x = atof(line);
				}

				if (strcmp(line, "start_y\n") == 0) {
					getline(&line, &len, file);
					line[len-1] = '\0';
					start_y = atof(line);
				}

				if (strcmp(line, "start_angle\n") == 0) {
					getline(&line, &len, file);
					line[len-1] = '\0';
					start_angle = atof(line);
				}
				
				if (strcmp(line, "change_angle\n") == 0) {
					getline(&line, &len, file);
					line[len-1] = '\0';
					change_angle = (3.14159/180.0)*atof(line);
				}

				if (strcmp(line, "line_size\n") == 0) {
					getline(&line, &len, file);
					line[len-1] = '\0';
					line_size = atof(line);
				}

				if (strcmp(line, "iterations\n") == 0) {
					getline(&line, &len, file);
					line[len-1] = '\0';
					iterations = atoi(line);
				}
			}
		}
	}

	printf("\n%d lines of grammar read.\n", grammarCount);
	printf("\n%d drawing symbol(s) read.\n", drawSymbolCount);
	printf("\n%d angle increment symbol(s) read.\n", angleIncrementSymbolCount);
	printf("\n%d angle decrement symbol(s) read.\n", angleDecrementSymbolCount);

	fclose(file);
}

void expand(int iterations) {
	char lsystemStringCopy[5000000];
	int i, j, lsystemIndex;

	printf("\n%s", "Expanding L-System String...\n");
	lsystemString[0] = nonTerminals[0];
	lsystemString[1] = '\0';

	for (i=0; i<iterations; i++) {
		for (j=0; lsystemString[j]!='\0'; j++) {
			lsystemStringCopy[j] = lsystemString[j];
		}

		lsystemIndex = 0;
		for (j=0; lsystemStringCopy[j]!='\0'; j++) {
			lsystemIndex += production(lsystemStringCopy[j], lsystemIndex);
		}
	
		lsystemString[lsystemIndex] = '\0';
	}

	printf("\n%s\n", "Drawing fractal...");
}

int production(char parent, int position) {
	int I, i;	

	for (I=0; I<grammarCount; I++) {
		if (parent == nonTerminals[I]) {
			break;
		}
	}

	if (I != grammarCount) {
		for (i=0; i<strlen(productions[I]); i++) {
			lsystemString[position+i] = productions[I][i];
		}

		return strlen(productions[I]);
	}
	else {
		lsystemString[position] = parent;
		return (1);
	}
}

int main(int argc, char *argv[])
{	
	read_lsystem_file(argv[1]);
	expand(iterations);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowSize(Width, Height);
	glutCreateWindow("L-System");

	glutDisplayFunc(display);	
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);

	glutMainLoop();

	return (0);
}
