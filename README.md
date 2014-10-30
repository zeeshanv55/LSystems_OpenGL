LSystems_OpenGL
===============

L-System fractals programmed in C using OpenGL.

Install OpenGL.

To run:
1. make
2. cd bin
3. ./lsystems <path to an l-system configuration file>
    For example: ./lsystems ../grammars/dragon_curve.lst
    

How to create a .lst file

The file has three sections
1. Grammar
2. Symbol Meanings
3. Other configurations

Each section is detailed as follows:

1. Grammar section
_begin_grammar 
<grammar information>
_end_grammar

It contains the context free grammar for your L-system fractal. Each gramamr symbol is always a single character.
The first non terminal of the first statement is always the start symbol. The production rules are specified as

A:p

where A is the non terminal and p is the production.

2. Symbol meanings section
_begin_symbol_meanings
<symbol meanings>
_end_symbol_meanings

The section can has five types of symbol meanings
1. draw
2. increase_angle
3. decrease_angle
4. stack_push
5. stack_pop

The symbol being specified for an action is written in the next line after the action.
For example, if 'F' is a grammar symbol which means 'draw a line', it can be specified as:

draw
F

Multiple symbols cannot be accomodated after an action. They have to be written separately.
For example,

draw
A
draw
B

3. Other configurations section
_begin_config
<configuration information>
_end_config

This contains other specifications to draw the fractal. Written in the same line-wise way as the previous section.

start_x
<starting x position for the fractal drawing>

start_y
<starting y position for the fractal drawing>

start_angle
<initial value for the angle of the line to be drawn, to be specified in degrees>

change_angle
<value that the angle changes after every increase_angle or decrease_angle symbol is encountered, in degrees>

line_size
<length of a line in pixels, can be a float value>

iterations
<the number of iterations for generating the L-system string from the grammar>
