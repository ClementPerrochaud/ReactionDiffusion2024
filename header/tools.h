#include <iostream>
#include <raylib.h>

Color RGB(double r, double g, double b); // renvoie la couleur raylib souhaitee en RGG
Color HSB(double h, double s, double b); // renvoie la couleur raylib souhaitee en HSB

Color ColorMap1(double value);
Color ColorMap2(double value);

double Sigmoid(double x, double a = 1, double b = 0);
