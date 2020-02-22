#include "field.hpp"

void Field::drop_treat() {
    while(map[treat_x][treat_y] != EMPTY) {
        treat_x = rand() % width;
        treat_y = rand() % height;
    }
}

int Field::draw() {
    for(int i = 0; i < height; i++)
        for(int j = 0; j < width; j++) map[i][j] = EMPTY;
    map[treat_x][treat_y] = TREAT;
    for(int i = 1; i < snake_length; i++)
        map[snake.sections[i].Y][snake.sections[i].X] = TAIL;
    if(map[snake.sections[0].Y][snake.sections[0].X] == EMPTY)
        map[snake.sections[0].Y][snake.sections[0].X] = HEAD;
    else if(map[snake.sections[0].Y][snake.sections[0].X] == TREAT) {
        map[snake.sections[0].Y][snake.sections[0].X] = HEAD;
        snake.grow();
        snake_length++;
        drop_treat();
        return 2;
    } else
        return 0;
    return 1;
}

void Field::show() {
    SDL_RenderClear(renderer);
    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            if(map[i][j] == EMPTY) continue;
            SDL_Rect dest;
            dest.x = j * TILE_WIDTH;
            dest.y = i * TILE_HEIGHT;
            dest.w = TILE_WIDTH;
            dest.h = TILE_HEIGHT;
            SDL_RenderCopy(
                renderer,
                map[i][j] == HEAD
                    ? head_texture
                    : map[i][j] == TAIL ? tail_texture : treat_texture,
                NULL, &dest);
        }
    }
    SDL_RenderPresent(renderer);
}

Field::Field(const int w, const int h, const unsigned snake_len)
    : width(w),
      height(h),
      snake_length(snake_len),
      snake(Snake(snake_len, height, width)),
      renderer(NULL) {
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("Snake", SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED, width * TILE_WIDTH,
                              height * TILE_HEIGHT, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, 0);
    IMG_Init(IMG_INIT_PNG);
    SDL_Surface *surface = IMG_Load("img/head.png");
    head_texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    surface = IMG_Load("img/tail.png");
    tail_texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    surface = IMG_Load("img/treat.png");
    treat_texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    map = (Tiles **)malloc(height * sizeof(Tiles *));
    for(int i = 0; i < height; i++)
        map[i] = (Tiles *)malloc(width * sizeof(Tiles));
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    drop_treat();
    draw();
    show();
}

int Field::update(Directions dir) {
    snake.move(dir);
    int res = draw();
    show();
    return res;
}

Field::~Field() {
    SDL_RenderClear(renderer);
    SDL_DestroyTexture(head_texture);
    SDL_DestroyTexture(tail_texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    for(int i = 0; i < height; i++) free(map[i]);
    free(map);
}
