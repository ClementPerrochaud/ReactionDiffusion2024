#include <iostream>
#include <cmath>
#include <raylib.h>

#include "tools.h"

using namespace std;

Color RGB(double R, double G, double B) {
    return (Color) { (unsigned char)(R*255),
                     (unsigned char)(G*255),
                     (unsigned char)(B*255),
                     255 };
}

Color HSB(double h, double s, double b) {
    double R, G, B;
    int i = int(h*6);
    double f = h*6-i;
    double p = b*(1-s);
    double q = b*(1-f*s);
    double t = b*(1-(1-f)*s);
    switch (i % 6) {
        case 0: R = b, G = t, B = p; break;
        case 1: R = q, G = b, B = p; break;
        case 2: R = p, G = b, B = t; break;
        case 3: R = p, G = q, B = b; break;
        case 4: R = t, G = p, B = b; break;
        case 5: R = b, G = p, B = q; break;
    }
    return (Color) { (unsigned char)(R*255),
                     (unsigned char)(G*255),
                     (unsigned char)(B*255),
                     255 };
}

Color ColorMap1(double value) {
    return HSB(0.7 - 0.5*value, 
               1, 
               1);
}

Color ColorMap2(double value) {
    return HSB(0, 0, Sigmoid(value, 25, 0.5));
}

double Sigmoid(double x, double a, double b) {
    return 1/(1+exp(-a*(x-b)));
}