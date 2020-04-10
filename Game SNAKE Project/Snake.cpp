//
//  Snake.cpp
//  Game SNAKE Project
//
//  Created by DO NGOC HUYEN on 4/6/20.
//  Commit first time on 4/10/20.
//  Copyright © 2020 DO NGOC HUYEN. All rights reserved.
//

#include "Snake.hpp"
#include "Check.h"

using namespace std;

Snake::Snake()
{
    auto res = SDL_Init(SDL_INIT_EVERYTHING);
    SDL_CHECK(res == 0, "SDL_Init");
    SDL_CreateWindowAndRenderer(Width, Height, SDL_WINDOW_BORDERLESS, &window, &renderer);
    SDL_CHECK(window, "SDL_CreateWindowAndRenderer");
    SDL_CHECK(renderer, "SDL_CreateWindowAndRenderer");
    
    SDL_SetWindowPosition(window, 65, 126);
    
    auto surface = SDL_LoadBMP("/Users/dongochuyen/Desktop/SnakeMaterials.bmp");
    SDL_CHECK(surface, "SDL_LoadBMP(\"SnakeMaterials.bmfp\")");
    SnakeMaterials = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_CHECK(SnakeMaterials, "SDL_CreateTextureFromSurface");
    SDL_FreeSurface(surface);
    

    segmentList.push_back(make_pair(5, 5));
    segmentList.push_back(make_pair(5, 6));
    segmentList.push_back(make_pair(5, 7));
}

Snake::~Snake()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

int Snake::exec()
{
    for (auto done = false; !done;)
    {
        SDL_Event e;
        if (SDL_PollEvent(&e))
        {
            switch (e.type)
            {
                case SDL_QUIT:
                    done = true;
                    break;
            }
        }
    SDL_SetRenderDrawColor(renderer, 150, 100, 150, 100);
    SDL_RenderClear(renderer);
    draw();
    SDL_RenderPresent(renderer);
    }
    return 0;
}

void Snake::draw()
{
    SDL_Rect src;
    src.x = 0;
    src.y = 0;
    src.w = 64;
    src.h = 64;
    
    SDL_Rect dst;
    dst.w = 64;
    dst.h = 64;
    
    for(auto i = begin(segmentList); i != end(segmentList); i++)
    {
        const auto &segment = *i;
        if(i == begin(segmentList))
        {
            src.x = Head * 64;
        }
        else if( i+1 == end(segmentList))
        {
            src.x = Tail * 64;
        }
        else
        {
            src.x = Straight * 64;
        }
        dst.x = 64 * segment.first;
        dst.y = 64 * segment.second;
        SDL_RenderCopyEx(renderer, SnakeMaterials, &src, &dst, -90, nullptr, SDL_FLIP_NONE);
       
    }
}
