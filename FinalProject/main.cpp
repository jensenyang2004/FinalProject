//
//  main.cpp
//  finalProject
//
//  Created by 楊景丞 on 2022/12/6.
//

#include "Game.hpp"
#include <SDL2/SDL_image.h>
#include <iostream>
#include <thread>



Game* game = nullptr;

bool checkkey_status(SDL_Event event){
    if(SDL_PollEvent(&event)){
        if(SDL_KEYDOWN == event.type){
            return true;
        }else if(SDL_KEYUP == event.type){
            return false;
        }
    }
    return true;
}

void check_status(SDL_Event event, bool& keydown){
    while(true){
        if(SDL_PollEvent(&event)){
            if(SDL_KEYDOWN == event.type){
                keydown = true;
            }else if(SDL_KEYUP == event.type){
                keydown = false;
            }
        }
    }
}

int main(int argc, const char* argv[]){
    
    game = new Game();

    game -> init("Cat", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, false);
    game -> game_start_init();
    SDL_Event event1;
    bool start_game = false;
    int key = 1;
    while(game -> running()){
        if(!start_game){
            game -> game_start_render();
            if(SDL_PollEvent(&event1)){
                if(SDL_MOUSEBUTTONDOWN == event1.type){
                    int x, y;
                    SDL_GetMouseState(&x, &y);
                    if(game -> game_check(x, y)){
                        SDL_Delay(30);
                        game -> loading_scene();
                        start_game = true;
                    }
                }
            }
            int x, y;
            SDL_GetMouseState(&x, &y);
            if(game -> game_check(x, y)){
                game -> game_start_update(true);
            }else{
                game -> game_start_update(false);
            }
        }
        
        if(start_game){
            SDL_Event event;
            bool Keyup = false, Keydown = false, jump = false;
            game -> handleEvents();
            game -> update(false, 0);
            game -> render();
            game -> is_falling(key);
            if(SDL_PollEvent(&event)){
                if(SDL_KEYDOWN == event.type){
                    if(SDLK_a == event.key.keysym.sym){
                        Keydown = true;
                        Keyup = false;
                        key = 1;
                    }else if(SDLK_d == event.key.keysym.sym){
                        Keydown = true;
                        Keyup = false;
                        key = 2;
                    }else if(SDLK_w == event.key.keysym.sym){
                        Keydown = false;
                        Keyup = false;
                        jump = true;
                    }else if(SDL_SCANCODE_SPACE == event.key.keysym.scancode){
                        game -> interaction = false;
                        game -> check_interaction();
                    }else if(SDLK_s == event.key.keysym.sym){
                        //game -> cat_posy += 250;
                    }
                }else if(SDL_KEYUP == event.type){
                    Keyup = true;
                    Keydown = false;
                }
            }
            if(jump){
                game -> jump(key);
            }
            if(Keydown){
                while(Keydown){
                    Keydown = checkkey_status(event);
                    game -> handleEvents();
                    Keydown = checkkey_status(event);
                    game -> update(true, key);
                    Keydown = checkkey_status(event);
                    game -> render();
                    game -> is_falling(key);
                }
                game -> handleEvents();
                game -> cat_still(key);
                game -> update(false,0);
                game -> render();
            }
        }
    }
    game -> clean();
    return 0;
}

