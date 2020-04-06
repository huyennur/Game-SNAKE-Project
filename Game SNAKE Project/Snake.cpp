//
//  Snake.cpp
//  Game SNAKE Project
//
//  Created by DO NGOC HUYEN on 4/6/20.
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
    SDL_RenderPresent(renderer); 
    }
    return 0;
}
