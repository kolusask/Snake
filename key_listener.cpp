#include "key_listener.hpp"

Directions direct;
int quit;
bool listen;
unsigned DELAY = 400;

void read_input() {
    SDL_Event event;
    while(!quit) {
        SDL_WaitEvent(&event);
        switch(event.type) {
            case SDL_QUIT:
                quit = true;
                break;
            case SDL_KEYDOWN:
                if(listen) {
                    switch(event.key.keysym.sym) {
                        case SDLK_UP:
                            if(direct != DOWN) direct = UP;
                            break;
                        case SDLK_DOWN:
                            if(direct != UP) direct = DOWN;
                            break;
                        case SDLK_LEFT:
                            if(direct != RIGHT) direct = LEFT;
                            break;
                        case SDLK_RIGHT:
                            if(direct != LEFT) direct = RIGHT;
                            break;
                        default:
                            continue;
                    }
                    listen = false;
                }
                break;
            case SDL_WINDOWEVENT:
                if(event.window.type == SDL_WINDOWEVENT_EXPOSED ||
                   event.window.type == SDL_WINDOWEVENT_RESTORED)
                    quit = 2;
                break;
            default:
                continue;
        }
    }
}

void handle(Field *field) {
    quit = false;
    direct = RIGHT;
    std::thread listener(read_input);
    while(!quit) {
        if(quit == 2) {
            field->show();
            continue;
        }
        int res = field->update(direct);
        quit = !res;
        listen = true;
        if(res == 2) DELAY -= int(log(DELAY));
        SDL_Delay(DELAY);
    }
    listener.join();
}