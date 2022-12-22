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
    void Photo(int a){
       
        bool boo_1 = true, boo2 = true, boo3 = true;
        switch (a) {
            case 5:
                boo_1 = false;
                if(!boo_1)
                photo_amount++;
                break;
            case 6:
                boo2 = false;
                if(!boo2)
                photo_amount++;
                break;
            case 7:
                boo3 = false;
                if(!boo3)
                photo_amount++;
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
