/*********************************************************************
** Program name: Project 0
** Author: Mario Franco-Munoz
** Date: 01/11/2018
** Description: Test program to demonstrate correctly operating IDE setup. 
** This program uses Heron's Formula to determine the area of a triangle. Returns output to console.
*********************************************************************/

#include <stdio.h>
#include <math.h>



int main (int argc, char **argv) {
	

	//a, b, and c represent the different sides of the triangle for which the area is being calculated for.
	int a = 10;
	int b = 10;
	int c = 10;
	double area;  //area variable for output.


	//area of triangle using Heron's Formula
	//Source: https://www.mathopenref.com/heronsformula.html
	double halfPerimiter = (a + b + c) / 2;
	area = (halfPerimiter * (halfPerimiter - a) * (halfPerimiter - b) * (halfPerimiter - c));
	area = sqrt(area);

	//print output
	printf("Area of the triangle is: %f\n", area);


	
	return 0;
}

