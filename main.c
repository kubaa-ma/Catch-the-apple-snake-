#include "raylib.h"
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h> 
#define vyska 700
#define sirka 900
int random_x_1 (int min, int max) {return min + rand() % (max - min + 1);}
int random_y_1 (int min, int max) {return min + rand() % (max - min + 1);}

typedef enum {MENU, HRAT, KONEC_HRY} stav;
int main() 
{

    //Okno nastavení
    InitWindow(sirka, vyska, "Chatch_the_apple");
    SetTargetFPS (8);

    //textury
    Texture2D pole = LoadTexture("./textury/pole.png");
    Texture2D jablko = LoadTexture("./textury/jablko.png");
    Texture2D had_hlava = LoadTexture("./textury/hlava.png");
    Texture2D pozadi = LoadTexture("./textury/pozadi.jpg");

    //počáteční stav hry
    stav state = MENU;

    //počátek hada
    int x = 400;
    int y = 300;            
    int smer = 1;  

    //počátek jablka
    int jablko_x_2 = random_x_1(0, 32);
    int jablko_y_2 = random_y_1(0, 24);
    int x_jab;
    int y_jab;
    int  pocet_jablek = 0;
    char pocet_jablek_text[50];

    //data polohy
    int zasobnik_x[10000] = {x};
    int zasobnik_y[10000] = {y};
    while(!WindowShouldClose()) 
    {

        if (state == MENU) {
            BeginDrawing();
            ClearBackground(GREEN);
            DrawText("CHATCH THE APPLE", sirka / 2 - 100, vyska / 2 - 50, 40, DARKBLUE);
            DrawText("STISKNI [ENTER] pro hrani", sirka / 2 - 100, vyska / 2, 20, DARKGREEN);
            EndDrawing();
            if (IsKeyPressed(KEY_ENTER)) {
                state = HRAT;
                continue;
            }
        }
        else if (state == HRAT) {

        
        //jablko mrizka
        int p = 0;
        int u = 0; 
        int policka_x[32];
        int policka_y[24]; 
        for (int i = 0; i<32; i++) {policka_x[i] = u; u = u + 25;}
        for (int i = 0; i<24; i++) {policka_y[i] = p; p = p + 25;}


    //snezeni jablka
    if (x == x_jab && y == y_jab) {
        jablko_y_2 = random_y_1(0, 24);
        jablko_x_2 = random_x_1(0, 32);
        pocet_jablek++; 
        sprintf(pocet_jablek_text, "Jablka: %d", pocet_jablek);
    }
        x_jab = policka_x[jablko_x_2];
        y_jab = policka_y[jablko_y_2]; 

    for (int i = pocet_jablek; i > 0; i--) {
        zasobnik_x[i] = zasobnik_x[i - 1];
        zasobnik_y[i] = zasobnik_y[i - 1];
    }
        zasobnik_x[0] = x;
        zasobnik_y[0] = y;

    
    //nastaveni smeru
    if (IsKeyPressed(KEY_A)) {if (smer==1) {smer=0;} else if(smer==0) {smer = -1;} else if (smer==-1) {smer = 2;} else if (smer == -2) {smer = -1;} else if (smer==2) {smer=1;} }
    if (IsKeyPressed(KEY_D)) {if (smer==1) {smer++;} else if(smer==2) {smer = -1;} else if(smer==-1) {smer = 0;} else if (smer == -2) {smer = 1;} else if (smer == 0) {smer++;}}
    if (IsKeyPressed(KEY_W)) {if (smer==1) {smer = 0;} else if (smer == -1) {smer = 0;}}
    if (IsKeyPressed(KEY_S)) {if (smer==1) {smer = 2;} else if(smer == -1) {smer = -2;}}
    //smer --> pohyb
    if (x<777) {if(smer == 1) {x = x + 25;}}
    if (x>-2) {if(smer ==-1) {x = x - 25;}}
    if (y<577) {if(smer == 2) {y = y + 25;} if(smer == -2) {y = y + 25;}}
    if (y>-2) {if(smer == 0) {y = y - 25;}}
    //hranice
    if (y<0 || y>575 || x < 0 || x>775) {BeginDrawing(); DrawText ("Konec Hry", 50, 50, 50, RED); EndDrawing(); return 0;}


    
    //naraz do tela --> konec hry
    for (int i = 1; i <= pocet_jablek; i++) {if (x == zasobnik_x[i] && y == zasobnik_y[i]) {DrawText("Konec hry", 50, 50, 50, RED); CloseWindow();return 0;}}


    //vykres
    BeginDrawing();
    DrawTexture(pozadi, 0, 0, WHITE);
    DrawTexture(pole, 0+50, 0+50, WHITE);
    DrawText("Hra had 32x24", 5, 5, 20, BLUE);
    DrawTexture(jablko, x_jab+50, y_jab+50, WHITE);
    DrawText(pocet_jablek_text, 650+90, 570+90, 30, BLUE);
    for (int i = 0; i<= pocet_jablek; i++) {DrawRectangle(zasobnik_x[i] + 50, zasobnik_y[i]+50,  25, 25, BLUE);}
    DrawTexture(had_hlava, x+50, y+50, WHITE);

    EndDrawing();
        }
    }
    //uvolnění textur
    UnloadTexture(pole);
    UnloadTexture(jablko);
    UnloadTexture(had_hlava);
    UnloadTexture(pozadi);
    CloseWindow();
    return 0;
}