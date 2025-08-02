#include "raylib.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

// 0 = nada
// 1 = X
// 2 = O
typedef struct Game {
    int estado[9];
    bool vencido;
} Game;

void next_turn(int *vez) {
    if (vez == 1) vez = 2;
    else          vez = 1;
}

int check_ganhou(Game *game) {
    // Linhas horizontais
    if (game->estado[0] == game->estado[1] && game->estado[0] == game->estado[2] && game->estado[0] != 0) return true;
    if (game->estado[3] == game->estado[4] && game->estado[3] == game->estado[5] && game->estado[3] != 0) return true;
    if (game->estado[6] == game->estado[7] && game->estado[6] == game->estado[8] && game->estado[6] != 0) return true;

    // Linhas verticais
    if (game->estado[0] == game->estado[3] && game->estado[0] == game->estado[6] && game->estado[0] != 0) return true;
    if (game->estado[1] == game->estado[4] && game->estado[1] == game->estado[7] && game->estado[1] != 0) return true;
    if (game->estado[2] == game->estado[5] && game->estado[2] == game->estado[8] && game->estado[2] != 0) return true;
    
    // Linhas diagonais
    if (game->estado[0] == game->estado[4] && game->estado[0] == game->estado[8] && game->estado[0] != 0) return true;
    if (game->estado[2] == game->estado[4] && game->estado[2] == game->estado[6] && game->estado[2] != 0) return true;

    return false;
}

void print_vencedor(int vez, int start, int padding) {
    if (vez == 2) DrawText("X", start + padding + 150, 120, 50, RED);
    else          DrawText("O", start + padding + 150, 120, 50, GREEN);
    DrawText("VENCEU", start + padding + 58, 180, 50, GRAY);
    if (vez == 2) DrawText("O", start + padding + 150, 240, 50, GREEN);
    else          DrawText("X", start + padding + 150, 240, 50, RED);
}

int main(void) {
    Game game = {
        .estado = {0, 0, 0, 0, 0, 0, 0, 0, 0},
        .vencido = 0
    };

    const int screenWidth  = 800;
    const int screenHeight = 450;
    int vez = 1;
    
    InitWindow(screenWidth, screenHeight, "TicTacToe");
    SetTargetFPS(60);     
    
    Texture2D campo = LoadTexture("src/campo.png");
    const int campo_x = 30;
    const int campo_y = 16;

    Texture2D x = LoadTexture("src/x.png");
    Texture2D o = LoadTexture("src/o.png");

    Rectangle sourceRec = { 0.0f, 0.0f, (float)o.width, (float)o.height };
    Rectangle destRec   = { campo_x + 58, campo_y + 58, campo.width, campo.height };
    Vector2   origin    = { (float)o.width/2, (float)o.height/2 };

    int offset = 25;
    Rectangle cells[] = {
        // X                                             Y                                                        
        { (campo_x) + (                           (10)), (campo_y) + (                            (10)), o.width, o.height },
        { (campo_x) + (    o.width + (offset     + 10)), (campo_y) + (                            (10)), o.width, o.height },
        { (campo_x) + (2 * o.width + (offset * 2 + 10)), (campo_y) + (                            (10)), o.width, o.height },
        { (campo_x) + (                           (10)), (campo_y) + (    o.height + (offset     + 10)), o.width, o.height },
        { (campo_x) + (    o.width + (offset     + 10)), (campo_y) + (    o.height + (offset     + 10)), o.width, o.height },
        { (campo_x) + (2 * o.width + (offset * 2 + 10)), (campo_y) + (    o.height + (offset     + 10)), o.width, o.height },
        { (campo_x) + (                           (10)), (campo_y) + (2 * o.height + (offset * 2 + 10)), o.width, o.height },
        { (campo_x) + (    o.width + (offset     + 10)), (campo_y) + (2 * o.height + (offset * 2 + 10)), o.width, o.height },
        { (campo_x) + (2 * o.width + (offset * 2 + 10)), (campo_y) + (2 * o.height + (offset * 2 + 10)), o.width, o.height }
    };

    Vector2 mousePoint = { 0.0f, 0.0f };
    while (!WindowShouldClose()) { 
        mousePoint = GetMousePosition();
        
        if (game.vencido == 0) {
            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
                if (CheckCollisionPointRec(mousePoint, cells[0]) && game.estado[0] == 0) {
                    game.estado[0] = vez; 
                    if (vez == 1) vez = 2;
                    else          vez = 1;
                } else if (CheckCollisionPointRec(mousePoint, cells[1]) && game.estado[1] == 0) {
                    game.estado[1] = vez; 
                    if (vez == 1) vez = 2;
                    else          vez = 1;
                } else if (CheckCollisionPointRec(mousePoint, cells[2]) && game.estado[2] == 0) {
                    game.estado[2] = vez; 
                    if (vez == 1) vez = 2;
                    else          vez = 1;
                } else if (CheckCollisionPointRec(mousePoint, cells[3]) && game.estado[3] == 0) {
                    game.estado[3] = vez; 
                    if (vez == 1) vez = 2;
                    else          vez = 1;
                } else if (CheckCollisionPointRec(mousePoint, cells[4]) && game.estado[4] == 0) {
                    game.estado[4] = vez; 
                    if (vez == 1) vez = 2;
                    else          vez = 1;
                } else if (CheckCollisionPointRec(mousePoint, cells[5]) && game.estado[5] == 0) {
                    game.estado[5] = vez; 
                    if (vez == 1) vez = 2;
                    else          vez = 1;
                } else if (CheckCollisionPointRec(mousePoint, cells[6]) && game.estado[6] == 0) {
                    game.estado[6] = vez; 
                    if (vez == 1) vez = 2;
                    else          vez = 1;
                } else if (CheckCollisionPointRec(mousePoint, cells[7]) && game.estado[7] == 0) {
                    game.estado[7] = vez; 
                    if (vez == 1) vez = 2;
                    else          vez = 1;
                } else if (CheckCollisionPointRec(mousePoint, cells[8]) && game.estado[8] == 0) {
                    game.estado[8] = vez; 
                    if (vez == 1) vez = 2;
                    else          vez = 1;
                } 
            }        
    
            game.vencido = check_ganhou(&game);
        }

        BeginDrawing();

            ClearBackground(RAYWHITE);
            DrawTexture(campo, campo_x, campo_y, WHITE);

            for (size_t i = 0; i < 9; i++) {
                if (game.estado[i] == 1) {
                    DrawTexture(x, cells[i].x, cells[i].y, WHITE);
                } else if (game.estado[i] == 2) {
                    DrawTexture(o, cells[i].x, cells[i].y, WHITE);
                }
            }

            if (game.vencido != 0) {              
                if (vez == 2){
                    DrawTexturePro(x, sourceRec, destRec, origin, 0.0f, WHITE);
                } else {
                    DrawTexturePro(o, sourceRec, destRec, origin, 0.0f, WHITE);
                }    
                print_vencedor(vez, campo_x, campo.width);
            } else {
                if (vez == 1) {
                    DrawText("Vez de: X", campo_x + campo.width + 30, 20, 50, GRAY);
                } else {
                    DrawText("Vez de: O", campo_x + campo.width + 30, 20, 50, GRAY);
                }
            }

        EndDrawing();
    }
    
    UnloadTexture(campo);
    CloseWindow();       
    return 0;
}