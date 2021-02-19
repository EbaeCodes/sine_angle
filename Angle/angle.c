

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <string.h>
#include <conio.h>

#define PI 3.14159265358979323846
#define DEBUG 0
#define FIXED_DEV 0.8
#define XMIN -PI
#define XMAX +PI
#define XSTEP (2*PI/ROWS)
#define XEXTRA 0.01
#define print printf
#define COLUMNS 80
#define ROWS 40
#define DEV 0.001
#define getch _getch


// Exercise 1a
	double norm_angle(double x) {
		/*Steps:
		1. check if the value is between -PI and +PI
		since the are already in radians.
		2. if it fall between the range then we continue
		otherwise add 2PI or remove 2PI to move it to that range 
		*/
		//checking if the value is between the range -PI and PI
		while (x < (-1 * PI) || x > PI) {
			//if it below -PI we add 2PI  
			if (x < -PI) { 
				x += (2 * PI);
				continue;
			}
			//if it is greater than PI we bring it into the range
			//by subtrating 2PI
			else if (x > PI) {
				x -= (2 * PI);
				continue;
			}
		}
		return x;
	}
// Exercise 1b
double sinus(double x, double deviation) {
  //declaraing variables of double type
	double sk = x;
	double sk_1 = x;
	double sine = x;
	double k = 1.0;
	// we keep looping until the absolute value of sk is greater than the absolute deviation
	while ((sk * sk) > (DEV * DEV)) { 
		//applying the formular
		sk = sk_1 * ((-1 * (x * x)) / ((2 * k) * ((2 * k) + 1)));
		sine += sk;
		sk_1 = sk;
		k++;
	}
	//return the value of sine which is our sinus
	return sine;
}
// Exercise 1c
void x_rad_con_fixed_dev(double x) {
	for (x = -10; x < 10.1; x += FIXED_DEV) {
		printf("%12.8lf\t%12.8lf\n",
			x, norm_angle(x));
	}
}
//creating number of columns and displaying blank or *
//depending the range it falls into.
void plot_value(double value, double y_min, double y_max) {
	double range = y_max - y_min;
	int column = (value - y_min) / (range) * (COLUMNS - 10); // between 0 .. 80
	for (int i = 0; i < column; i++) {
		printf(" ");
	}
	printf("*\n");
}

void plot_function_by_key(char ch) {
	if (DEBUG) printf("### plot_function_by_key('%c')\n", ch);
	int index = 0;
	double x, y, y_min = 0.0, y_max = 0.0;
	double x_array[100], y_array[100];
	// loop over range of x values:
	for(x = XMIN; x <= XMAX + XEXTRA; x = x + XSTEP) { // #steps is ROWS
		switch (ch) { // depend on key pressed
		case 's': y = sinus(x, 1e-6); break;
			/*
			case 's': y = sin(x); break;
			case 'c': y = cos(x); break;
			case 't': y = tan(x); break;
			case 'l': y = x; break;
			case 'q': y = x * x; break;
			*/
		default: y = 0;
		}
		//if (DEBUG) printf("x=%.3lf y=%.3lf\n", x, y);
		x_array[index] = x; // store into table
		y_array[index] = y; // store into table
		y_min = (y < y_min) ? y : y_min;
		y_max = (y > y_max) ? y : y_max;
		index++; // increase the index
	}
	int num_values = index; // so many elements in the table
	if (DEBUG) printf("num_values=%d, y_min=%.3f, y_max=%.3f\n", num_values, y_min, y_max);
	for (index = 0; index < num_values; index++) { // #steps is ROWS
		x = x_array[index]; // read out values from table
		y = y_array[index];
		//if (DEBUG) printf("x=%.3lf y=%.3lf\n", x, y);
		printf("x=%6.3lf ", x);
		plot_value(y, y_min, y_max);
	}
	if (DEBUG) printf("### plot_function_by_key() finished.\n");
}
//the function takes a character from the user to plot the required graph
void do_plotting_frontend() {
	if (DEBUG) printf("### do_plotting_frontend()\n");
	char ch; // character from keyboard
	int key_pressed = ' '; // keyboard key value
	// loop:
	while (key_pressed != '.') {
		print("Please select function to plot (keys s to plot the sine graph, .=quit)\n");
		key_pressed = getch();
		ch = key_pressed; // char <- int conversion
		if (DEBUG) print("Key pressed was '%c'=%04d=0x%04X\n", ch, key_pressed, key_pressed);
		plot_function_by_key(ch);
	}
	if (DEBUG) printf("### do_plotting_frontend() finished.\n");
}


int main(void) {
	//Exercise 1a
	double x;
	//looping from -10 to 10.1 to display the normalized angle
	//by calling the functions norm_angle() and passing the value 
	for (x = -10; x < 10.1; x += 2.0) {
		printf(" The angle %12.8lf ( radiants ) corresponds to %12.8lf \n",
			x, norm_angle(x));
	}
	printf("\n");
	//Exercise 1b
	//looping from -PI to +PI to display the sinus function for each value
	for (x = -M_PI; x <= M_PI; x += M_PI / 10) {
		printf("sinus(%lf) = %lf\n", x, sinus(x, 1e-6));
	}
	//Exercise 1c
	//ploting the sinus() function,that is the graph of the values obtain
	// table of values for x and y=f(X)
	//printf("x\t\ty=f(x)\n");
	//x_rad_con_fixed_dev(x);
	  do_plotting_frontend();

	return 0;
}