#include <iostream>
#include <random>
#include <raylib.h>

#include "petridish.h"
#include "cell.h"
#include "tools.h"

using namespace std;


// - - - - - - CONSTRUCTEURS - - - - - - - - - - - - - - - - - - - - - //

PetriDish::PetriDish(){}
PetriDish::PetriDish(
    int width  = 100,
    int height = 100 ):
                         
    width(width), height(height) {

    Grid  = new Cell*[height];
    Grid1 = new Cell*[height];
    for (int i = 0; i < height; i++) {
        Grid[i]  = new Cell[width];
        Grid1[i] = new Cell[width];
        for (int j = 0; j < width; j++) {
            Grid[i][j]  = Cell();
            Grid1[i][j] = Cell();
        }
    }
}


// - - - - - - INITIALISEUR - - - - - - - - - - - - - - - - - - - - - //

void PetriDish::Random_ConcentrationInit(int seed) {
    mt19937 gen(seed);
    uniform_real_distribution<double> dis(0.0f, 1.0f);
    double A, B;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            A = dis(gen); B = dis(gen);
            Grid[i][j].A = A; Grid1[i][j].A = A;
            Grid[i][j].B = B; Grid1[i][j].B = B;
        }
    }
}

void PetriDish::Import_ConcentrationInit(string path) {
    Image image = LoadImage(path.c_str());
    ImageResize(&image, width, height);
    Color *pixels = LoadImageColors(image);
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            Grid[i][j].A = 1.*pixels[i*width+j].g/255; Grid1[i][j].A = Grid[i][j].A;
            Grid[i][j].B = 1.*pixels[i*width+j].b/255; Grid1[i][j].B = Grid[i][j].B;
        }
    }
    void UnloadImageColors(Color *colors);
}

void PetriDish::Perlin_ConcentrationInit(double scale) {
    Image imageA = GenImagePerlinNoise(width, height, 0,          0,           scale);
    Image imageB = GenImagePerlinNoise(width, height, 0.05*width, 0.05*height, scale);
    Color *pixelsA = LoadImageColors(imageA);
    Color *pixelsB = LoadImageColors(imageB);
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            Grid[i][j].A = 1.*pixelsA[i*width+j].g/255; Grid1[i][j].A = Grid[i][j].A;
            Grid[i][j].B = 1.*pixelsB[i*width+j].b/255; Grid1[i][j].B = Grid[i][j].B;
        }
    }
    void UnloadImageColors(Color *colors);
}


// parametres uniformes

void PetriDish::Set_DA(double DA) { this->DA = DA; }
void PetriDish::Set_DB(double DB) { this->DB = DB; }
void PetriDish::Set_f (double f)  { this->f  = f;  }
void PetriDish::Set_k (double k)  { this->k  = k;  }
void PetriDish::Set_u (double u)  { this->u  = u;  }
void PetriDish::Set_v (double v)  { this->v  = v;  }


// parametres non uniformes

void PetriDish::Set_DA(string path, double DA0, double DA1) { // canal vert
    is_DA_grid = true;
    DA_grid = new double*[height];
    Image image = LoadImage(path.c_str());
    ImageResize(&image, width, height);
    Color *pixels = LoadImageColors(image);
    for (int i = 0; i < height; i++) {
        DA_grid[i] = new double[width];
        for (int j = 0; j < width; j++) {
            DA_grid[i][j] = DA0 + (DA1-DA0)*pixels[i*width+j].g/255;
    }   } void UnloadImageColors(Color *colors);
}
void PetriDish::Set_DB(string path, double DB0, double DB1) { // canal bleu
    is_DB_grid = true;
    DB_grid = new double*[height];
    Image image = LoadImage(path.c_str());
    ImageResize(&image, width, height);
    Color *pixels = LoadImageColors(image);
    for (int i = 0; i < height; i++) {
        DB_grid[i] = new double[width];
        for (int j = 0; j < width; j++) {
            DB_grid[i][j] = DB0 + (DB1-DB0)*pixels[i*width+j].b/255;
    }   } void UnloadImageColors(Color *colors);
}
void PetriDish::Set_f(string path, double f0, double f1) { // canal rouge
    is_f_grid = true;
    f_grid = new double*[height];
    Image image = LoadImage(path.c_str());
    ImageResize(&image, width, height);
    Color *pixels = LoadImageColors(image);
    for (int i = 0; i < height; i++) {
        f_grid[i] = new double[width];
        for (int j = 0; j < width; j++) {
            f_grid[i][j] = f0 + (f1-f0)*pixels[i*width+j].r/255;
    }   } void UnloadImageColors(Color *colors);
}
void PetriDish::Set_k(string path, double k0, double k1) { // canal bleu
    is_k_grid = true;
    k_grid = new double*[height];
    Image image = LoadImage(path.c_str());
    ImageResize(&image, width, height);
    Color *pixels = LoadImageColors(image);
    for (int i = 0; i < height; i++) {
        k_grid[i] = new double[width];
        for (int j = 0; j < width; j++) {
            k_grid[i][j] = k0 + (k1-k0)*pixels[i*width+j].b/255;
    }   } void UnloadImageColors(Color *colors);
}
void PetriDish::Set_u(string path, double u0, double u1) { // canal rouge
    is_u_grid = true;
    u_grid = new double*[height];
    Image image = LoadImage(path.c_str());
    ImageResize(&image, width, height);
    Color *pixels = LoadImageColors(image);
    for (int i = 0; i < height; i++) {
        u_grid[i] = new double[width];
        for (int j = 0; j < width; j++) {
            u_grid[i][j] = u0 + (u1-u0)*pixels[i*width+j].r/255;
    }   } void UnloadImageColors(Color *colors);
}
void PetriDish::Set_v(string path, double v0, double v1) { // canal bleu
    is_v_grid = true;
    v_grid = new double*[height];
    Image image = LoadImage(path.c_str());
    ImageResize(&image, width, height);
    Color *pixels = LoadImageColors(image);
    for (int i = 0; i < height; i++) {
        v_grid[i] = new double[width];
        for (int j = 0; j < width; j++) {
            v_grid[i][j] = v0 + (v1-v0)*pixels[i*width+j].b/255;
    }   } void UnloadImageColors(Color *colors);
}


void PetriDish::SelectParameters(int i, int j) {
    if (is_DA_grid) { DA = DA_grid[i][j]; }
    if (is_DB_grid) { DB = DB_grid[i][j]; }
    if (is_f_grid ) { f  =  f_grid[i][j]; }
    if (is_k_grid ) { k  =  k_grid[i][j]; }
    if (is_u_grid ) { u  =  u_grid[i][j]; }
    if (is_v_grid ) { v  =  v_grid[i][j]; }
}



// - - - - - - AFFICHAGE - - - - - - - - - - - - - - - - - - - - - //

void PetriDish::DrawInit(int offset_min,
                         int screenWidth,
                         int screenHeight,
                         int colormapid) {
    dx = min((screenHeight-2*offset_min)/height,
             (screenWidth -2*offset_min)/width);
    offsetY = (screenHeight - dx*height)/2;
    offsetX = (screenWidth  - dx*width )/2;
    this->colormapid = colormapid;

}

void PetriDish::Draw() {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            DrawRectangle(offsetX + dx*j,
                          offsetY + dx*i,
                          dx, dx,
                          ColorMap(Grid[i][j].A));
        }
    }
}

Color PetriDish::ColorMap(double value) {
    switch (colormapid) {
        case 1: return ColorMap1(value); break;
        case 2: return ColorMap2(value); break;
    }
}



// - - - - - - CALCULS - - - - - - - - - - - - - - - - - - - - - //

void PetriDish::Update() {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            Grid[i][j].A = Grid1[i][j].A;
            Grid[i][j].B = Grid1[i][j].B;
        }
    }
}


// laplaciens

double PetriDish::LaplacienA(int i, int j) { 
    int &w = width, &h = height;
    double lap = -Grid[i][j].A;                 // 5 (voir positions pave numerique)
    lap +=  0.2 * Grid[(i+h+1)%h][j].A;         // 2
    lap +=  0.2 * Grid[(i+h-1)%h][j].A;         // 8
    lap +=  0.2 * Grid[i][(j+w+1)%w].A;         // 6
    lap +=  0.2 * Grid[i][(j+w-1)%w].A;         // 4
    lap += 0.05 * Grid[(i+h+1)%h][(j+w+1)%w].A; // 3
    lap += 0.05 * Grid[(i+h-1)%h][(j+w+1)%w].A; // 9
    lap += 0.05 * Grid[(i+h+1)%h][(j+w-1)%w].A; // 1
    lap += 0.05 * Grid[(i+h-1)%h][(j+w-1)%w].A; // 7
    return lap;
}
double PetriDish::LaplacienB(int i, int j) { 
    int &w = width, &h = height;
    double lap = -Grid[i][j].B;                
    lap +=  0.2 * Grid[(i+h+1)%h][j].B;        
    lap +=  0.2 * Grid[(i+h-1)%h][j].B;        
    lap +=  0.2 * Grid[i][(j+w+1)%w].B;        
    lap +=  0.2 * Grid[i][(j+w-1)%w].B;        
    lap += 0.05 * Grid[(i+h+1)%h][(j+w+1)%w].B;
    lap += 0.05 * Grid[(i+h-1)%h][(j+w+1)%w].B;
    lap += 0.05 * Grid[(i+h+1)%h][(j+w-1)%w].B;
    lap += 0.05 * Grid[(i+h-1)%h][(j+w-1)%w].B;
    return lap;
}


// reactions-diffusions

void PetriDish::Diffuse() {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            SelectParameters(i,j);
            Grid1[i][j].A += DA*LaplacienA(i,j);
            Grid1[i][j].B += DB*LaplacienB(i,j);
        }
    }
}

void PetriDish::GrayScott() {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            SelectParameters(i,j);
            Grid1[i][j].A += - Grid[i][j].A * Grid[i][j].B * Grid[i][j].B
                             + f * ( 1 - Grid[i][j].A );
            Grid1[i][j].B += Grid[i][j].A * Grid[i][j].B * Grid[i][j].B
                           - ( f + k ) * Grid[i][j].B;
        }
    }
}

void PetriDish::Brusselator() {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            SelectParameters(i,j);
            Grid1[i][j].A += u - ( v + 1 ) * Grid[i][j].A
                           + Grid[i][j].A * Grid[i][j].A * Grid[i][j].B;
            Grid1[i][j].B += v * Grid[i][j].A
                           - Grid[i][j].A * Grid[i][j].A * Grid[i][j].B;
        }
    }
}

