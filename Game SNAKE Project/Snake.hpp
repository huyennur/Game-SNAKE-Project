//
//  Snake.hpp
//  Game SNAKE Project
//
//  Created by DO NGOC HUYEN on 4/6/20.
//  Copyright © 2020 DO NGOC HUYEN. All rights reserved.
//

#ifndef Snake_hpp
#define Snake_hpp

#include "/Library/Frameworks/SDL2.framework/Headers/SDL.h"
//#include <SDL2/SDL.h> không hoạt động trên Xcode bản 11
using namespace std;

class Snake
{
public:
    Snake();
    ~Snake();
    int exec();

    const static auto Width = 1280;
    const static auto Height = 720;
private:
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *SnakeMaterials;
    
};

#endif /* Snake_hpp */
