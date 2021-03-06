LSystems_OpenGL
===============

L-System fractals programmed in C using OpenGL.<br><br>

Install OpenGL.<br>
sudo apt-get install freeglut3-dev<br><br>

To run:<br>
1. make<br>
2. cd bin<br>
3. ./lsystems (path to an l-system configuration file) (number of iterations)<br>
    For example: ./lsystems ../grammars/dragon_curve.lst 18<br><br><br>
    

How to create a .lst file<br><br>

The file has three sections<br>
1. Grammar<br>
2. Symbol Meanings<br>
3. Angle configurations<br><br>

Each section is detailed as follows:<br><br>

<b>Grammar section</b><br>
_begin_grammar <br>
(grammar information)<br>
_end_grammar<br>

It contains the context free grammar for your L-system fractal. Each gramamr symbol is always a single character.
The first non terminal of the first statement is always the start symbol. The production rules are specified as<br><br>

A:p<br><br>

where A is the non terminal and p is the production.<br><br>

<b>Symbol meanings section</b><br>
_begin_symbol_meanings<br>
(symbol meanings)<br>
_end_symbol_meanings<br><br>

The section can has five types of symbol meanings<br>
1. draw<br>
2. increase_angle<br>
3. decrease_angle<br>
4. stack_push<br>
5. stack_pop<br><br>

The symbol being specified for an action is written in the next line after the action.<br>
For example, if 'F' is a grammar symbol which means 'draw a line', it can be specified as:<br><br>

draw<br>
F<br><br>

Multiple symbols cannot be accomodated after an action. They have to be written separately.<br>
For example,<br><br>

draw<br>
A<br>
draw<br>
B<br><br>

<b>Angle configurations section</b><br>
_begin_config<br>
(configuration information)<br>
_end_config<br><br>

This contains angle specifications (initial angle and angle change with every corresponding symbol read) to draw the fractal. Written in the same line-wise way as the previous section.<br><br>

start_angle<br>
(initial value for the angle of the line to be drawn, to be specified in degrees)<br><br>

change_angle<br>
(value that the angle changes after every increase_angle or decrease_angle symbol is encountered, in degrees)<br><br>
