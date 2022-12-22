//
//  background.hpp
//  FinalProject
//
//  Created by 楊景丞 on 2022/12/15.
//

#ifndef background_hpp
#define background_hpp

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <iostream>

using namespace std;

struct object{
    int number_of_dialogues = 0;
    string* dialogue = nullptr;
    void init_object(int posx, int posy, int posh, int posw, int length_dialogue, string* dialogue);
    bool check_interaction(int x, int y);
    void init_hitbox(int x, int y, int w, int h);
    SDL_Rect hitbox;
};

class background{
    public:
    SDL_Texture* bg;
    int up = 0, down = 0, left = 0,right = 0;
    int initial_posx = 0;
    int left_bound = 0, right_bound = 0;
    int number_of_object = 0;
    void init(SDL_Renderer*, char* path);
    void change_background(SDL_Renderer* renderer);
    void init_position(int a, int b, int c){
        initial_posx = a;
        left_bound = b;
        right_bound = c;
    }
    
    object* objects = nullptr;
    void init_objects(int n, int posx[], int posy[], int posh[], int posw[], int length_dialogue[], string** dialogues){
        number_of_object = n;
        object* objects = new object[n];
        this -> objects = objects;
        for(int i = 0;i < n;i++){
            this -> objects[i].init_object(posx[i], posy[i], posh[i], posw[i], length_dialogue[i], dialogues[i]);
        }
    }
    
};

#endif /* background_hpp */
