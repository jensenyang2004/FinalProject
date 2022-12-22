//
//  background.cpp
//  FinalProject
//
//  Created by 楊景丞 on 2022/12/15.
//

#include "background.hpp"
#include <iostream>

using namespace std;

void background :: init(SDL_Renderer* renderer, char* path){
    SDL_Surface* bg = IMG_Load(path);
    this -> bg = SDL_CreateTextureFromSurface(renderer, bg);
    if(bg == NULL){
        printf("Unable to load image %s! SDL_image Error: %s\n", "image.png", IMG_GetError());
        return;
    }
}

void background :: change_background(SDL_Renderer* renderer){
    SDL_RenderCopy(renderer, this -> bg, NULL, NULL);
}


bool object :: check_interaction(int x, int y){
    if(x >= hitbox.x && x <= hitbox.x + hitbox.w){
        if(y >= hitbox.y && y <= hitbox.y + hitbox.h){
            return true;
        }
    }
    return false;
}

void object :: init_object(int posx, int posy, int posh, int posw, int length_dialogue, string* dialogue){
    hitbox.x = posx;
    hitbox.y = posy;
    hitbox.h = posh;
    hitbox.w = posw;
    this -> dialogue =  dialogue;
    this -> number_of_dialogues = length_dialogue;
}

void object :: init_hitbox(int x, int y, int w, int h){
    hitbox.x = x;
    hitbox.y = y;
    hitbox.w = w;
    hitbox.h = h;
}
