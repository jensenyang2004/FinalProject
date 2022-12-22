//
//  main.cpp
//  finalProject
//
//  Created by 楊景丞 on 2022/12/6.
#include "Game.hpp"
#include <SDl2/SDL_mixer.h>
#include <iostream>
#include <string>
#include "progress.hpp"

#define floor 522

using namespace std;

SDL_Texture* cat;
SDL_Texture* Background;
SDL_Texture* dialogue;
SDL_Rect srcR, destR;
SDL_Rect dialogue_Rect = {250, 400, 800, 200};
SDL_Rect textRect = {250, 400, 500, 200};

TTF_Font* font = TTF_OpenFont("/System/Library/Fonts/Supplemental/AmericanTypewriter.ttc", 25);
SDL_Color textColor = {0, 0, 0, 255};

SDL_Texture* textTexture;
SDL_Rect dstRect;

//starting menu
SDL_Texture* button;
SDL_Texture* starting_background;
SDL_Rect buttonRec = {450, 430, 300, 160};
SDL_Surface* buttonsurface1 = IMG_Load("/Users/yangjingcheng/programming_workspace/FinalProject/FinalProject/resources/button/start1.png");
SDL_Surface* buttonsurface2 = IMG_Load("/Users/yangjingcheng/programming_workspace/FinalProject/FinalProject/resources/button/start2.png");
//starting menu


Game :: Game(){
    
}
Game :: ~Game(){
    
}

progress Progress;

void Game :: init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen){
    //Window
    int flags = 0;
    if(fullscreen){
        flags = SDL_WINDOW_FULLSCREEN;
    }
    if(SDL_Init(SDL_INIT_EVERYTHING) == 0){
        
        //bgm
        SDL_Init(SDL_INIT_AUDIO);
        if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
            cout << "ERROR" << Mix_GetError() << std::endl;
          bgm = Mix_LoadMUS("/Users/yangjingcheng/programming_workspace/FinalProject/FinalProject/resources/soundtrack/ending.mp3");
        if (bgm)
        {
           cout << "bgm is ready" << endl;
        }
        Mix_PlayMusic(bgm, -1);
        cout << "Subsystem initialised..." << endl;
        window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
        if(window){
            cout << "Window created" << endl;
        }
        //bgm
        
        renderer = SDL_CreateRenderer(window, -1, 0);
        if(renderer){
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            cout << "Renderer created" << endl;
        }
        isRunning = true;
    }
    TTF_Init();
    //Window
    
    //cat image
    SDL_Surface* tmpSurface = IMG_Load("/Users/yangjingcheng/programming_workspace/FinalProject/FinalProject/resources/pixilart-layers 2/pixil-layer-0.png");
    //tmpSurface = IMG_Load("resources/pixilart-layers 2/pixil-layer-0.png");

    if( tmpSurface == NULL )
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", "image.png", IMG_GetError() );
        return;
    }
    cat = SDL_CreateTextureFromSurface(renderer, tmpSurface);
    SDL_FreeSurface(tmpSurface);
    //cat image
    
    //background class
    init_background();
    //background class

    //dialogue box
    SDL_Surface* dialogue_box = IMG_Load("/Users/yangjingcheng/programming_workspace/FinalProject/FinalProject/resources/dialoguebox.png");
    if(dialogue_box == NULL){
        printf("Unable to load image %s! SDL_image Error: %s\n", "image.png", IMG_GetError());
        return;
    }
    
    dialogue = SDL_CreateTextureFromSurface(renderer, dialogue_box);
    SDL_FreeSurface(dialogue_box);
}


void Game :: update(bool move, int direction){
    int limit = 0;
    if(move){
        switch (direction) {
            case 1:
                limit = 7;
                cat_posh = 150;
                cat_posw = 150;
                cat_posx -= 10;
                cat_hitbox_x -= 10;
                cat_walk_left(cnt);
                break;
            case 2:
                limit = 7;
                cat_posx += 10;
                cat_hitbox_x += 10;
                cat_posh = 150;
                cat_posw = 150;
                cat_walk_right(cnt);
                break;
            default:
                break;
        }
        cnt++;
        if(cnt > limit)
            cnt = 0;
    }
    check_boundary();
    destR.h = cat_posh;
    destR.w = cat_posw;
    destR.x = cat_posx;
    destR.y = cat_posy;
    srcR.h = 600;
    srcR.w = 1000;
}

void Game :: check_boundary(){
    if(cat_posx > bg[background_index-1].right_bound){
        //loading_scene();
        if(background_index < 2){
            background_index++;
            cat_posx = bg[background_index-1].left_bound;
        }else
            cat_posx = bg[background_index-1].right_bound;
    }else if(cat_posx < bg[background_index-1].left_bound ){
        //loading_scene();
        if(background_index > 1){
            background_index--;
            cat_posx = bg[background_index-1].right_bound;
        }else
            cat_posx = bg[background_index-1].left_bound;
    }
}


void Game :: render(){
    //SDL_RenderClear(renderer);
    
    //this is where we would add stuff to render
    
//    SDL_RenderCopy(renderer, Background, NULL, &srcR);
    bg[background_index-1].change_background(renderer);
    
    
    
    SDL_RenderCopy(renderer, cat, NULL, &destR);
    if(interaction){
        SDL_RenderCopy(renderer, dialogue, NULL, &dialogue_Rect);
        SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
    }
    
    SDL_RenderPresent(renderer);
}

void Game :: handleEvents(){
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type) {
        case SDL_QUIT:
            isRunning = false;
            break;
        default:
            break;
    }
}

void Game :: clean(){
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    cout << "Game Cleaned" << endl;
}

bool Game :: running(){
    return isRunning;
}

void Game :: jump(int key){
    cat_posh = 400;
    cat_posw = 500;
    cat_posy -= 250;
    if(key == 1){
        cat_posx -= 350;
        //cat_hitbox_x -= 350;
    }
    for(int i = 0;i < 11;i++){
        handleEvents();
        cat_jump_success(i, key);
        update(false, 0);
        render();
    }
    if(key == 2){
        cat_posx += 350;
        //cat_hitbox_x += 350;
    }
    handleEvents();
    cat_still(key);
    update(false,0);
    render();
    
}

void Game :: cat_still(int key){
    cat_posh = 150;
    cat_posw = 150;
    SDL_Surface* surface_left = IMG_Load("/Users/yangjingcheng/programming_workspace/FinalProject/FinalProject/resources/pixilart-layers 2/pixil-layer-0.png");
    SDL_Surface* surface_right = IMG_Load("/Users/yangjingcheng/programming_workspace/FinalProject/FinalProject/resources/pixilart-layers_right/pixil-layer-0.png");
    if(key == 1)
        cat = SDL_CreateTextureFromSurface(renderer, surface_left);
    else if(key == 2)
        cat = SDL_CreateTextureFromSurface(renderer, surface_right);
}

void Game :: cat_walk_left(int i){
    SDL_Delay(30);
    SDL_Surface* tmpSurface[8];
    tmpSurface[0] = IMG_Load("/Users/yangjingcheng/programming_workspace/FinalProject/FinalProject/resources/pixilart-layers 2/pixil-layer-1.png");
    tmpSurface[1] = IMG_Load("/Users/yangjingcheng/programming_workspace/FinalProject/FinalProject/resources/pixilart-layers 2/pixil-layer-2.png");
    tmpSurface[2] = IMG_Load("/Users/yangjingcheng/programming_workspace/FinalProject/FinalProject/resources/pixilart-layers 2/pixil-layer-3.png");
    tmpSurface[3] = IMG_Load("/Users/yangjingcheng/programming_workspace/FinalProject/FinalProject/resources/pixilart-layers 2/pixil-layer-4.png");
    tmpSurface[4] = IMG_Load("/Users/yangjingcheng/programming_workspace/FinalProject/FinalProject/resources/pixilart-layers 2/pixil-layer-5.png");
    tmpSurface[5] = IMG_Load("/Users/yangjingcheng/programming_workspace/FinalProject/FinalProject/resources/pixilart-layers 2/pixil-layer-6.png");
    tmpSurface[6] = IMG_Load("/Users/yangjingcheng/programming_workspace/FinalProject/FinalProject/resources/pixilart-layers 2/pixil-layer-7.png");
    tmpSurface[7] = IMG_Load("/Users/yangjingcheng/programming_workspace/FinalProject/FinalProject/resources/pixilart-layers 2/pixil-layer-8.png");
    if( tmpSurface[i] == NULL )
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", "image.png", IMG_GetError() );
        return;
    }
    cat = SDL_CreateTextureFromSurface(renderer, tmpSurface[i]);
    
}

void Game :: cat_walk_right(int i){
    SDL_Delay(30);
    SDL_Surface* Surface[9];
    Surface[0] = IMG_Load("/Users/yangjingcheng/programming_workspace/FinalProject/FinalProject/resources/pixilart-layers_right/pixil-layer-1.png");
    Surface[1] = IMG_Load("/Users/yangjingcheng/programming_workspace/FinalProject/FinalProject/resources/pixilart-layers_right/pixil-layer-2.png");
    Surface[2] = IMG_Load("/Users/yangjingcheng/programming_workspace/FinalProject/FinalProject/resources/pixilart-layers_right/pixil-layer-3.png");
    Surface[3] = IMG_Load("/Users/yangjingcheng/programming_workspace/FinalProject/FinalProject/resources/pixilart-layers_right/pixil-layer-4.png");
    Surface[4] = IMG_Load("/Users/yangjingcheng/programming_workspace/FinalProject/FinalProject/resources/pixilart-layers_right/pixil-layer-5.png");
    Surface[5] = IMG_Load("/Users/yangjingcheng/programming_workspace/FinalProject/FinalProject/resources/pixilart-layers_right/pixil-layer-6.png");
    Surface[6] = IMG_Load("/Users/yangjingcheng/programming_workspace/FinalProject/FinalProject/resources/pixilart-layers_right/pixil-layer-7.png");
    Surface[7] = IMG_Load("/Users/yangjingcheng/programming_workspace/FinalProject/FinalProject/resources/pixilart-layers_right/pixil-layer-8.png");
    if( Surface[i] == NULL )
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", "image.png", IMG_GetError() );
        return;
    }
    cat = SDL_CreateTextureFromSurface(renderer, Surface[i]);
}

void Game :: cat_jump_success(int i, int key){
    SDL_Surface* jumpanimation[11];
    SDL_Surface* jumpanimation_left[11];
    SDL_Delay(20);
    jumpanimation[0] = IMG_Load("/Users/yangjingcheng/programming_workspace/FinalProject/FinalProject/resources/cat_jump/1.png");
    jumpanimation[1] = IMG_Load("/Users/yangjingcheng/programming_workspace/FinalProject/FinalProject/resources/cat_jump/2.png");
    jumpanimation[2] = IMG_Load("/Users/yangjingcheng/programming_workspace/FinalProject/FinalProject/resources/cat_jump/3.png");
    jumpanimation[3] = IMG_Load("/Users/yangjingcheng/programming_workspace/FinalProject/FinalProject/resources/cat_jump/4.png");
    jumpanimation[4] = IMG_Load("/Users/yangjingcheng/programming_workspace/FinalProject/FinalProject/resources/cat_jump/5.png");
    jumpanimation[5] = IMG_Load("/Users/yangjingcheng/programming_workspace/FinalProject/FinalProject/resources/cat_jump/6.png");
    jumpanimation[6] = IMG_Load("/Users/yangjingcheng/programming_workspace/FinalProject/FinalProject/resources/cat_jump/7.png");
    jumpanimation[7] = IMG_Load("/Users/yangjingcheng/programming_workspace/FinalProject/FinalProject/resources/cat_jump/8.png");
    jumpanimation[8] = IMG_Load("/Users/yangjingcheng/programming_workspace/FinalProject/FinalProject/resources/cat_jump/9.png");
    jumpanimation[9] = IMG_Load("/Users/yangjingcheng/programming_workspace/FinalProject/FinalProject/resources/cat_jump/10.png");
    jumpanimation[10] = IMG_Load("/Users/yangjingcheng/programming_workspace/FinalProject/FinalProject/resources/cat_jump/11.png");
    
    jumpanimation_left[0] = IMG_Load("/Users/yangjingcheng/programming_workspace/FinalProject/FinalProject/resources/cat_jump_left/1.png");
    jumpanimation_left[1] = IMG_Load("/Users/yangjingcheng/programming_workspace/FinalProject/FinalProject/resources/cat_jump_left/2.png");
    jumpanimation_left[2] = IMG_Load("/Users/yangjingcheng/programming_workspace/FinalProject/FinalProject/resources/cat_jump_left/3.png");
    jumpanimation_left[3] = IMG_Load("/Users/yangjingcheng/programming_workspace/FinalProject/FinalProject/resources/cat_jump_left/4.png");
    jumpanimation_left[4] = IMG_Load("/Users/yangjingcheng/programming_workspace/FinalProject/FinalProject/resources/cat_jump_left/5.png");
    jumpanimation_left[5] = IMG_Load("/Users/yangjingcheng/programming_workspace/FinalProject/FinalProject/resources/cat_jump_left/6.png");
    jumpanimation_left[6] = IMG_Load("/Users/yangjingcheng/programming_workspace/FinalProject/FinalProject/resources/cat_jump_left/7.png");
    jumpanimation_left[7] = IMG_Load("/Users/yangjingcheng/programming_workspace/FinalProject/FinalProject/resources/cat_jump_left/8.png");
    jumpanimation_left[8] = IMG_Load("/Users/yangjingcheng/programming_workspace/FinalProject/FinalProject/resources/cat_jump_left/9.png");
    jumpanimation_left[9] = IMG_Load("/Users/yangjingcheng/programming_workspace/FinalProject/FinalProject/resources/cat_jump_left/10.png");
    jumpanimation_left[10] = IMG_Load("/Users/yangjingcheng/programming_workspace/FinalProject/FinalProject/resources/cat_jump_left/11.png");
    
    switch (key) {
        case 1:
            if( jumpanimation_left[i] == NULL )
            {
                printf( "Unable to load image %s! SDL_image Error: %s\n", "image.png", IMG_GetError() );
                return;
            }
            cat = SDL_CreateTextureFromSurface(renderer, jumpanimation_left[i]);
            break;
        case 2:
            if( jumpanimation[i] == NULL )
            {
                printf( "Unable to load image %s! SDL_image Error: %s\n", "image.png", IMG_GetError() );
                return;
            }
            cat = SDL_CreateTextureFromSurface(renderer, jumpanimation[i]);
            break;
        default:
            break;
    }
    
}

void Game :: init_background(){
    char path[1000] = "/Users/yangjingcheng/programming_workspace/FinalProject/FinalProject/resources/background/1.png";
    for(int i = 1;i < 3;i++){
        path[strlen(path)-5] = static_cast<char>(i+49);
        bg[i-1].init(renderer, path);
    }
    
    int posx[3] = {380, 0, 850};
    int posy[3] = {432, 522, 0};
    int posw[3] = {280, 200, 95};
    int posh[3] = {240, 450, 720};
    
    int length_dialogue_1[3] = {2, 1, 1};
    string** dialogues_1 = new string*[3];
    
    string* dialogue_1_1 = new string[2];
    dialogue_1_1[0] = "Is there anything special?";
    dialogue_1_1[1] = "Oh, it's a piece of picture.";
    dialogues_1[0] = dialogue_1_1;
    
    string* dialogue_1_2 = new string[1];
    dialogue_1_2[0] = "The door is locked...";
    dialogues_1[1] = dialogue_1_2;
    
    string* dialogue_1_3 = new string[1];
    dialogue_1_3[0] = "This is my bowl.";
    dialogues_1[2] = dialogue_1_3;

    bg[0].init_objects(3, posx, posy, posh, posw, length_dialogue_1 , dialogues_1);
    
    bg[0].objects[2].init_image("/Users/yangjingcheng/programming_workspace/FinalProject/FinalProject/resources/micelaneous/bowl.png");
    bg[0].objects[0].init_set_index(5);
    bg[0].objects[1].init_set_index(2);
    
    int posx_2[5] = {532, 112, 358, 532, 970};
    int posy_2[5] = {130, 261, 327, 422, 350};
    int posw_2[5] = {342, 216, 138, 452, 358};
    int posh_2[5] = {150, 336, 240, 300, 228};

    int length_dialogue_2[5] = {1, 2, 2, 2, 10};
    string** dialogues_2 = new string*[5];
    
    string* dialogue_2_1 = new string[1];
    dialogue_2_1[0] = "This is my photo! Wait...";
    dialogues_2[0] = dialogue_2_1;
    
    string* dialogue_2_2 = new string[2];
    dialogue_2_2[0] = "Is there anything special?";
    dialogue_2_2[1] = "Oh, it's a piece of picture.";
    dialogues_2[1] = dialogue_2_2;
    
    string* dialogue_2_3 = new string[2];
    dialogue_2_3[0] = "Oops, the drawer is locked.";
    dialogue_2_3[1] = "What are the passwords?";
    dialogues_2[2] = dialogue_2_3;
    
    string* dialogue_2_4 = new string[2];
    dialogue_2_4[0] = "Is there anything special?";
    dialogue_2_4[1] = "Oh, it's a piece of picture.";
    dialogues_2[3] = dialogue_2_4;
    
    string* dialogue_2_5 = new string[10];
    dialogue_2_5[0] = "This is my owner's computer. Here is his diary...";
    dialogue_2_5[1] = "Jun, 30th, 2022, a sunny day.";
    dialogue_2_5[2] = "I have adopted a lovely cat!";
    dialogue_2_5[3] = "Aug, 10th, 2022, a sunny day.";
    dialogue_2_5[4] = "She is so cute, and I love her so much.";
    dialogue_2_5[5] = "Oct, 25th, 2022, a cloudy day.";
    dialogue_2_5[6] = "She is sick, and I bring her to the clinic.";
    dialogue_2_5[7] = "Dec, 20th, 2022, a rainy day.";
    dialogue_2_5[8] = "I dreamed of her last night.";
    dialogue_2_5[9] = "I do miss her.";
    dialogues_2[4] = dialogue_2_5;
    
    bg[1].init_objects(5, posx_2, posy_2, posh_2, posw_2, length_dialogue_2 , dialogues_2);
    
    bg[1].objects[1].init_set_index(6);
    bg[1].objects[3].init_set_index(7);
    bg[1].objects[2].init_set_index(3);
    bg[0].init_position(350, 0, 1050);
    bg[1].init_position(200, 70, 1130);
}

void Game :: check_interaction(){
    for(int i = 0;i < bg[background_index - 1].number_of_object;i++){
        if(bg[background_index - 1].objects[i].check_interaction(cat_posx, cat_posy)){
            show_dialogue(bg[background_index - 1].objects[i]);
        }
    }
}

void Game :: show_dialogue(object& objects){
    interaction = true;
    for(int i = 0;i < objects.number_of_dialogues;i++){
        interaction = true;
        char tmparray[objects.dialogue[i].length() + 1];
        strcpy(tmparray, objects.dialogue[i].c_str());
        TTF_Font* font = TTF_OpenFont("/System/Library/Fonts/Supplemental/AmericanTypewriter.ttc", 25);
        SDL_Color textColor = {0, 0, 0, 255};

        SDL_Surface* textSurface = TTF_RenderText_Solid(font, tmparray, textColor);

        textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

        textRect = {300, 450, textSurface->w, textSurface->h};
        handleEvents();
        update(false, 1);
        render();
        SDL_Event event;
        while(true){
            if(SDL_PollEvent(&event)){
                if(SDL_KEYDOWN == event.type){
                    if(SDL_SCANCODE_SPACE == event.key.keysym.scancode){
                        interaction = false;
                        break;
                    }
                }
            }
        }
    }
//    if(objects.has_image){
//        interaction = true;
//        SDL_Surface* textSurface = TTF_RenderText_Solid(font, "", textColor);
//        textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
//        show_image(objects);
//    }
    
    if(objects.has_event){
        event(objects.plot_determine);
    }
}

void Game :: game_start_init(){

    SDL_Surface* tmpsurface = IMG_Load("/Users/yangjingcheng/programming_workspace/FinalProject/FinalProject/resources/background/starting_background.jpg");
    //SDL_Surface* tmpsurface = IMG_Load("/Users/yangjingcheng/programming_workspace/FinalProject/FinalProject/starting_background.jpg");

    //SDL_Surface* tmpsurface = IMG_Load("./background/starting_background.jpg");
    starting_background = SDL_CreateTextureFromSurface(renderer, tmpsurface);
    
    button = SDL_CreateTextureFromSurface(renderer, buttonsurface1);
}

void Game :: game_start_render(){
    SDL_RenderCopy(renderer, starting_background, NULL, NULL);
    SDL_RenderCopy(renderer, button, NULL, &buttonRec);
    SDL_RenderPresent(renderer);
}

void Game :: game_start_update(bool button_key){
    if(button_key)
        button = SDL_CreateTextureFromSurface(renderer, buttonsurface2);
    else
        button = SDL_CreateTextureFromSurface(renderer, buttonsurface1);
}

bool Game :: game_check(int x, int y){
    if(x >= buttonRec.x && x <= buttonRec.w + buttonRec.x ){
        if(y >= buttonRec.y && y <= buttonRec.h + buttonRec.y){
            return true;
        }
    }
    return false;
}


bool Game :: is_falling(int key){
    switch (key) {
        case 1:
            if(cat_hitbox_x != cat_posx){
                cat_hitbox_x = cat_posx;
            }
            break;
        case 2:
            if(cat_hitbox_x != cat_posx + 75){
                cat_hitbox_x = cat_posx + 75;
            }
            break;
        default:
            break;
    }
    bool determine = false;
    for(int i = 0;i < bg[background_index-1].number_of_object;i++){
        if(cat_hitbox_x >= bg[background_index-1].objects[i].hitbox.x
           && cat_hitbox_x <= bg[background_index-1].objects[i].hitbox.w + bg[background_index-1].objects[i].hitbox.x){
            if(cat_posy < bg[background_index-1].objects[i].hitbox.y){
                //cout << "checkpoint 1" << endl;
                determine = false;
                }else if(cat_posy < floor && cat_posy >  bg[background_index-1].objects[i].hitbox.y){
                    //cout << "checkpoint 2" << endl;
                    determine = false;
                }else if(cat_posy == bg[background_index-1].objects[i].hitbox.y || cat_posy == floor){
                    //cout << "checkpoint 3" << endl;
                    determine = true;
                    break;
                }
        }
    }
    if(cat_posy == floor){
        //cout << "checkpoint 4" << endl;
        determine = true;
    }
    if(!determine){
        //cout << "why ???????" << endl;
        cat_fall(key);
    }
    return false;
}


void Game :: loading_scene(){
    SDL_Surface* tmp[3];
    tmp[0] = IMG_Load("/Users/yangjingcheng/programming_workspace/FinalProject/FinalProject/resources/loading/1.jpg");
    tmp[1] = IMG_Load("/Users/yangjingcheng/programming_workspace/FinalProject/FinalProject/resources/loading/2.jpg");
    
    tmp[2] = IMG_Load("/Users/yangjingcheng/programming_workspace/FinalProject/FinalProject/resources/loading/3.jpg");
    
    SDL_Texture* background;
    for(int i = 0;i < 6;i++){
        SDL_Delay(400);
        background = SDL_CreateTextureFromSurface(renderer, tmp[i % 3]);
        SDL_RenderCopy(renderer, background, NULL, NULL);
        SDL_RenderPresent(renderer);
    }
}

void Game :: cat_fall(int key){
    SDL_Delay(30);
    SDL_Surface* tmp = IMG_Load("/Users/yangjingcheng/programming_workspace/FinalProject/FinalProject/resources/cat_fall/2.png");
    if(key == 1){
        tmp = IMG_Load("/Users/yangjingcheng/programming_workspace/FinalProject/FinalProject/resources/cat_fall_left/2.png");
    }
    cat = SDL_CreateTextureFromSurface(renderer, tmp);
    //int delay = 20;
    //int i = 0;
    while(true){
        int ground = floor;
        //i++;
        for(int i = 0;i < bg[background_index-1].number_of_object;i++){
            if(cat_hitbox_x >= bg[background_index-1].objects[i].hitbox.x
               && cat_hitbox_x <= bg[background_index-1].objects[i].hitbox.w + bg[background_index-1].objects[i].hitbox.x){
                if(cat_posy <= bg[background_index-1].objects[i].hitbox.y){
                    ground = min(ground, bg[background_index-1].objects[i].hitbox.y);
                }
            }
        }
        
        SDL_Delay(30);
        cat_posy += 10;
        cat_hitbox_x += (key == 1) ? (-5) : (5);
        cat_posx += (key == 1) ? (-5) : (5);
        if(cat_posy >= ground){
            cat_posy = ground;
            cat_still(key);
            break;
        }
        update(false, 0);
        render();
    }
}

void Game :: show_image(object& object){
    if(!object.has_image){
        return;
    }
    dialogue_Rect =  {256, 0, 768, 768};
    dialogue = SDL_CreateTextureFromSurface(renderer, object.image);
    handleEvents();
    update(false, 1);
    render();
    SDL_Event event;
    while(true){
        if(SDL_PollEvent(&event)){
            if(SDL_KEYDOWN == event.type){
                if(SDL_SCANCODE_SPACE == event.key.keysym.scancode){
                    interaction = false;
                    SDL_Surface* dialogue_box = IMG_Load("/Users/yangjingcheng/programming_workspace/FinalProject/FinalProject/resources/dialoguebox.png");
                    dialogue_Rect = {250, 400, 800, 200};
                    dialogue = SDL_CreateTextureFromSurface(renderer, dialogue_box);
                    break;
                }
            }
        }
    }
}

void Game :: event(int a){

    if(a == 2){
        Progress.Ending();
        if(Progress.ending){
            if(Progress.photo){
                cout << "happy ending" << endl;
            }else{
                cout << "bad ending" << endl;
            }
        }
    }else if(a == 3){
        lock();
        Progress.Lock(1209);
        if(Progress.lock){
            Progress.key = true;
        }
    }else if(a == 4){
        
    }else if(a == 5){
        Progress.Photo(5);
        //photo();
    }else if(a == 6){
        Progress.Photo(6);
        //photo();
    }else if(a == 7){
        Progress.Photo(7);
        //photo();
    }
}

void Game :: lock(){
    
    TTF_Font* font = TTF_OpenFont("/System/Library/Fonts/Supplemental/AmericanTypewriter.ttc", 25);
    SDL_Color textColor = {0, 0, 0, 255};
    SDL_Surface* tmpsurface = IMG_Load("/Users/yangjingcheng/programming_workspace/FinalProject/FinalProject/resources/micelaneous/locking.png");
    SDL_Surface* number[4];
    char number1[2] = "0";
    number[0] = TTF_RenderText_Solid(font, number1, textColor);
    char number2[2] = "0";
    number[1]  = TTF_RenderText_Solid(font, number2, textColor);
    char number3[2] = "0";
    number[2]  = TTF_RenderText_Solid(font, number2, textColor);
    char number4[2] = "0";
    number[3]  = TTF_RenderText_Solid(font, number2, textColor);
    
    SDL_Rect lock_rect = {256, 0, 768, 768};
    SDL_Texture* lock_image = SDL_CreateTextureFromSurface(renderer, tmpsurface);
    
    SDL_Texture* number_image[4];
    int number_number[4] = {0};
    number_image[0] = SDL_CreateTextureFromSurface(renderer, number[0]);
    number_image[1] = SDL_CreateTextureFromSurface(renderer, number[1]);
    number_image[2] = SDL_CreateTextureFromSurface(renderer, number[2]);
    number_image[3] = SDL_CreateTextureFromSurface(renderer, number[3]);

    SDL_Rect number_rect[4];
    number_rect[0] = {739, 297, 25, 50};
    number_rect[1] = {739, 362, 25, 50};
    number_rect[2] = {739, 427, 25, 50};
    number_rect[3] = {739, 492, 25, 50};

    
    


    //SDL_RenderPresent(renderer);
    
    
    SDL_Event event;

    while(true){
        number[0] = TTF_RenderText_Solid(font, number1, textColor);
        number[1]  = TTF_RenderText_Solid(font, number2, textColor);
        number[2]  = TTF_RenderText_Solid(font, number2, textColor);
        number[3]  = TTF_RenderText_Solid(font, number2, textColor);
        
        number_image[0] = SDL_CreateTextureFromSurface(renderer, number[0]);
        number_image[1] = SDL_CreateTextureFromSurface(renderer, number[1]);
        number_image[2] = SDL_CreateTextureFromSurface(renderer, number[2]);
        number_image[3] = SDL_CreateTextureFromSurface(renderer, number[3]);

        bg[background_index-1].change_background(renderer);
        SDL_RenderCopy(renderer, lock_image, NULL, &lock_rect);
        SDL_RenderCopy(renderer, number_image[0], NULL, &number_rect[0]);
        SDL_RenderCopy(renderer, number_image[1], NULL, &number_rect[1]);
        SDL_RenderCopy(renderer, number_image[2], NULL, &number_rect[2]);
        SDL_RenderCopy(renderer, number_image[3], NULL, &number_rect[3]);
        SDL_RenderPresent(renderer);
        if(SDL_PollEvent(&event)){
            if(SDL_KEYDOWN == event.type){
                if(SDL_SCANCODE_SPACE == event.key.keysym.scancode){
                    break;
                }
            }else if(SDL_MOUSEBUTTONDOWN == event.type){
                int x, y;
                SDL_GetMouseState(&x, &y);
                if(x >= 724 && x <= 784){
                    if(y >= 290 && y <= 347){
                        number_number[0]++;
                        if(number_number[0] > 9)
                            number_number[0] = 0;
                        number1[0] = static_cast<char>(number_number[0] + 48);
                    }else if(y >= 360 && y <= 413){
                        number_number[1]++;
                        if(number_number[1] > 9)
                            number_number[1] = 0;
                        number2[0] = static_cast<char>(number_number[1] + 48);
                    }else if(y >= 423 && y <= 477){
                        number_number[2]++;
                        if(number_number[2] > 9)
                            number_number[2] = 0;
                        number3[0] = static_cast<char>(number_number[2] + 48);
                    }else if(y >= 490 && y <= 546){
                        number_number[3]++;
                        if(number_number[3] > 9)
                            number_number[3] = 0;
                        number4[0] = static_cast<char>(number_number[3] + 48);
                    }
                }
            }
        }
    }


}
