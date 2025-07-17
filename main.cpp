#include <iostream>
#include <cmath>
#include <fstream>
#include <raylib.h>

#include "header/petridish.h"
#include "header/cell.h"

using namespace std;


// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //


int main() {
    int screenWidth = 820, screenHeight = 820;
    int gridWidth   = 400, gridHeight   = 400; 
    int offset_min  = 10; // taille des bordures
    int fps      = 60;
    int drawSkip = 10; // nombre d'update() par image

    double DA = 0.5,   DB = 0.25;   // parametres de diffusion
    double f = 0.0353, k  = 0.0566; // taux d'alimentation & constante de desactivation
    double u = 5,      v  = 4;

    InitWindow(screenWidth, screenHeight, "REACTION-DIFFUSION");
    SetTargetFPS(fps);

    PetriDish DISH = PetriDish(gridWidth, gridHeight);
    DISH.DrawInit(offset_min, screenWidth, screenHeight);
    //DISH.Import_ConcentrationInit("template2.png");
    DISH.Perlin_ConcentrationInit(10);
    DISH.Set_DA(DA); DISH.Set_DB(DB);
    //DISH.Set_f(f); DISH.Set_k(k); 
    DISH.Set_f("kf.png", 0.02,  0.10 );
    DISH.Set_k("kf.png", 0.057, 0.066);
    //DISH.Set_u(u); DISH.Set_v(v);

    unsigned int frame = 0;
    while (WindowShouldClose() == false) {

        if (frame%drawSkip==0) {
            BeginDrawing();
            ClearBackground(BLACK);
            DISH.Draw();
            EndDrawing();
        }

        DISH.Diffuse();
        DISH.GrayScott();
        //DISH.Brusselator();
        DISH.Update();
        
        frame++;
        if ((frame*drawSkip)%fps==0) {cout << GetFPS() << endl;}
    }

    CloseWindow();
    return 0;
}