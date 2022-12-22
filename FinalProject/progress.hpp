//
//  progress.hpp
//  FinalProject
//
//  Created by 楊景丞 on 2022/12/22.
//

#ifndef progress_hpp
#define progress_hpp

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class progress{
public:
    int lock = 630;
    bool lock_determine = false;
    bool boo_1 = false, boo2 = false, boo3 = false;

    bool ending = false;
    
    bool key = false;
    
    int photo_amount = 0;
    bool photo = false;
    
    void Lock(int password){
        if(password == lock){
            lock_determine = true;
        }
    }
    
    void Ending(){
        if(key){
            ending = true;
        }
    }
    void Photo(int a){
       
                switch (a) {
            case 5:
                if(!boo_1)
                photo_amount++;
                boo_1 = true;
                break;
            case 6:
                if(!boo2)
                photo_amount++;
                boo2 = true;
                break;
            case 7:
                if(!boo3)
                photo_amount++;
                boo3 = true;
                break;
            default:
                break;
        }
        if(photo_amount == 3){
            photo = true;
        }
    }
};

#endif /* progress_hpp */
