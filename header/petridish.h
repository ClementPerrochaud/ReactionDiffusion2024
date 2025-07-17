#pragma once
#include <iostream>
#include "cell.h"
using namespace std;

class PetriDish {

private:
    int width, height;    // taille de la grille (nombre de cellules)
    Cell** Grid;          // grille
    Cell** Grid1; 

    // parametres pour Draw()
    int offsetX, offsetY;
    int dx;

    bool is_DA_grid = false, is_DB_grid = false;
    bool is_f_grid  = false, is_k_grid  = false;
    bool is_u_grid  = false, is_v_grid  = false;

    double DA, DB, f, k, u, v;
    double** DA_grid; 
    double** DB_grid;
    double** f_grid;
    double** k_grid;
    double** u_grid;
    double** v_grid;

    void SelectParameters(int i, int j);

    int colormapid = 1;
    Color ColorMap(double value);

public:
    // constructeurs
    PetriDish();
    PetriDish(int width, int height);

    // initialiseur
    void Random_ConcentrationInit(int seed = 0);
    void Import_ConcentrationInit(string path = "patern.png");
    void Perlin_ConcentrationInit(double scale = 1.0);

    void Set_DA(double DA); void Set_DA(string path, double DA0 = 0., double DA1= 1.); // canal vert
    void Set_DB(double DB); void Set_DB(string path, double DB0 = 0., double DB1= 1.); // canal bleu
    void Set_f (double f ); void Set_f (string path, double f0  = 0., double f1 = 1.); // canal rouge
    void Set_k (double k ); void Set_k (string path, double k0  = 0., double k1 = 1.); // canal bleu
    void Set_u (double u ); void Set_u (string path, double u0  = 0., double u1 = 1.); // canal rouge
    void Set_v (double v ); void Set_v (string path, double v0  = 0., double v1 = 1.); // canal bleu

    // affichage
    void DrawInit(int offset_min,
                  int screenWidth,
                  int screenHeight,
                  int colormapid = 1);
    void Draw();

    // calculs
    void Update();

    double LaplacienA(int i, int j);
    double LaplacienB(int i, int j);

    void Diffuse();
    void GrayScott();
    void Brusselator();
};
