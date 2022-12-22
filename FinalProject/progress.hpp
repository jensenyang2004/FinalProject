//
//  progress.hpp
//  FinalProject
//
//  Created by 楊景丞 on 2022/12/22.
//

#ifndef progress_hpp
#define progress_hpp

#include <stdio.h>

class progress{
public:
    int lock = 1209;
    bool lock_determine = false;
    
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
        if(key && photo){
            ending = true;
        }
    }
    
    void Photo(){
        photo_amount++;
        if(photo_amount == 3){
            photo = true;
        }
    }
};

#endif /* progress_hpp */
