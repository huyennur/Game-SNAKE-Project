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
#include <deque>
using namespace std;

class Snake
{
public:
    Snake();
    ~Snake();
    int exec();
    void draw();
    void tick();
    
    static const auto HeadOpenMouth = 0;
    static const auto Tail = 1;
    static const auto Turn = 2;
    static const auto Straight = 3;
    static const auto Head = 4;
    static const auto Strawberry = 5;

    const static auto Width = 1280;
    const static auto Height = 720;
private:
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *SnakeMaterials;
    
    deque<pair<int, int>> segmentList;
    
    unsigned ticks = 0;
       
       int dx = 1;
       int dy = 0;
    
};

#endif /* Snake_hpp */
