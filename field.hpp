#ifndef FIELD_H
#define FIELD_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdlib.h>
#include "snake.hpp"
#define TILE_WIDTH 50
#define TILE_HEIGHT 50

enum Tiles { EMPTY, HEAD, TAIL, TREAT };

class Field {
   public:
    Field(const int w, const int h, const unsigned snake_len);
    ~Field();
    int update(Directions dir);
   private:
    int draw();
    void show();
    void drop_treat();
    const int width;
    const int height;
    int snake_length;
    int treat_x;
    int treat_y;
    Snake snake;
    Tiles **map;
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *head_texture;
    SDL_Texture *tail_texture;
    SDL_Texture *treat_texture;
    friend void handle(Field*);
};

#endif
