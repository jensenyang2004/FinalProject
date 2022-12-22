//
//  Game.hpp
//  finalProject
//
//  Created by 楊景丞 on 2022/12/9.
//

#ifndef Game_hpp
#define Game_hpp

#include "background.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDl2/SDL_mixer.h>
#include <stdio.h>

#define floor 522

class Game{
public:
    Game();
    ~Game();
    
    //method for cat movement
    void init(const char* title, int xpos, int ypos, int witdth, int height, bool fullscreen);
    void handleEvents();
    void update();
    void update(bool move, int direction);
    void render();
    void clean();
    void jump(int key);
    
    //starting menu
    void menu_render();
    void menu_update();
    void menu_init();
    
    bool running();
    void change_image(int i, bool direction);
    
    void cat_still(int key);
    void cat_walk_left(int i);
    void cat_walk_right(int i);
    void cat_jump_success(int i, int key);
    void cat_jump_fail();
    void cat_fall(int key, int index);
    void cat_fall(int key);
    bool is_falling(int key);
    
    void init_background();
    void check_boundary();
    
    void check_interaction();
    void show_dialogue(object&);
    void show_image(object&);
    
    void game_start_init();
    void game_start_update(bool button_key);
    void game_start_render();
    bool game_check(int x, int y);
    
    void loading_scene();
    
public:
    bool isRunning;
    int cnt = 0;
    SDL_Window* window;
    SDL_Renderer* renderer;
    int cat_posx = 350;
    int cat_posy = floor;
    int cat_hitbox_x = 350, cat_hitbox_y = floor;
    int cat_posh = 150, cat_posw = 150;
    int background_index = 1;
    bool interaction = false;
    Mix_Music* bgm;
    background bg[2];
};


#endif /* Game_hpp */

