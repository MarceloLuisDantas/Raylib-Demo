#include "raylib.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

// 0 = nada
// 1 = X
// 2 = O
typedef struct Game {
    int estado[9];

    // Vencido
    // 1 = primeira linha horizontal
    // 2 = segunda linha horizontal
    // 3 = terceira linha horizontal
    // 4 = primeira linha vertical
    // 5 = segunda linha vertical
    // 6 = terceira linha vertical
    // 7 = primeira diagonal
    // 8 = segunda diagonal
    int vencido;
} Game;

void next_turn(int *vez) {
    if (vez == 1) vez = 2;
    else          vez = 1;
}

int check_ganhou(Game *game) {
    // Linhas horizontais
    if (game->estado[0] == game->estado[1] && game->estado[0] == game->estado[2] && game->estado[0] != 0) return 1;
    if (game->estado[3] == game->estado[4] && game->estado[3] == game->estado[5] && game->estado[3] != 0) return 2;
    if (game->estado[6] == game->estado[7] && game->estado[6] == game->estado[8] && game->estado[6] != 0) return 3;
    
    // Linhas verticais
    if (game->estado[0] == game->estado[3] && game->estado[0] == game->estado[6] && game->estado[0] != 0) return 4;
    if (game->estado[1] == game->estado[4] && game->estado[1] == game->estado[7] && game->estado[1] != 0) return 5;
    if (game->estado[2] == game->estado[5] && game->estado[2] == game->estado[8] && game->estado[2] != 0) return 6;

    // Linhas diagonais
    if (game->estado[0] == game->estado[4] && game->estado[0] == game->estado[8] && game->estado[0] != 0) return 7;
    if (game->estado[2] == game->estado[4] && game->estado[2] == game->estado[6] && game->estado[2] != 0) return 8;

    return 0;
}

void draw_horizontal_line(Rectangle r1, Rectangle r2) {
    Vector2 start = { r1.x - r1.x/2,   r1.y + 57 };
    Vector2 end   = { r2.x + r2.x/2.4, r2.y + 57 };
    DrawLineEx(start, end, 20.0f, BLUE);    
}

void draw_vertical_line(Rectangle r1, Rectangle r2) {
    Vector2 start = { r1.x + 57, r1.y - 10 };
    Vector2 end   = { r2.x + 57, r2.y + r2.y/2.4 };
    DrawLineEx(start, end, 20.0f, BLUE);    
}

void draw_diagonal_line_1(Rectangle r1, Rectangle r2) {
    Vector2 start = { r1.x - r1.x/4,   r1.y - 0 };
    Vector2 end   = { r2.x + r2.width, r2.y + 115 };
    DrawLineEx(start, end, 20.0f, BLUE);    
}

void draw_diagonal_line_2(Rectangle r1, Rectangle r2) {
    Vector2 start = { r1.x + r1.width,   r1.y - 0 };
    Vector2 end   = { r2.x - r2.x/4, r2.y + 115 };
    DrawLineEx(start, end, 20.0f, BLUE);    
}

int main(void) {
    Game game = {
        .estado = {0, 0, 0, 0, 0, 0, 0, 0, 0},
        .vencido = 0
    };

    const int screenWidth  = 800;
    const int screenHeight = 450;
    int vez = 1;
    
    InitWindow(screenWidth, screenHeight, "TicTacToe²");
    SetTargetFPS(60);     
    
    Texture2D campo = LoadTexture("src/campo.png");
    const int campo_x = 30;
    const int campo_y = 16;

    Texture2D x = LoadTexture("src/x.png");
    Texture2D o = LoadTexture("src/o.png");

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
                switch (game.vencido) {
                    case 1:
                        draw_horizontal_line(cells[0], cells[2]);
                        break;
                    case 2:
                        draw_horizontal_line(cells[3], cells[5]);
                        break;
                    case 3:
                        draw_horizontal_line(cells[6], cells[8]);
                        break;

                    case 4:
                        draw_vertical_line(cells[0], cells[6]);
                        break;
                    case 5:
                        draw_vertical_line(cells[1], cells[7]);
                        break;
                    case 6:
                        draw_vertical_line(cells[2], cells[8]);
                        break;
                        
                    case 7:
                        draw_diagonal_line_1(cells[0], cells[8]);
                        break;
                    case 8:
                        draw_diagonal_line_2(cells[2], cells[6]);
                        break;
                }

                if (vez == 2){
                    DrawText("X",      campo_x + campo.width + 150, 120, 50, RED);
                    DrawText("VENCEU", campo_x + campo.width + 58, 180, 50, GRAY);
                    DrawText("O",      campo_x + campo.width + 150, 240, 50, GREEN);
                } else {
                    DrawText("O",      campo_x + campo.width + 150, 120, 50, GREEN);
                    DrawText("VENCEU", campo_x + campo.width + 58, 180, 50, GRAY);
                    DrawText("X",      campo_x + campo.width + 150, 240, 50, RED);
                }       

            } else {
                if (vez == 1)
                    DrawText("Vez de: X", campo_x + campo.width + 30, 20, 50, GRAY);
                else 
                    DrawText("Vez de: O", campo_x + campo.width + 30, 20, 50, GRAY);
            }

        EndDrawing();
    }
    
    UnloadTexture(campo);
    CloseWindow();       
    return 0;
}