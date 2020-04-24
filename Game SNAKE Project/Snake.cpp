
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
    // load pictures into the window
    auto surface = SDL_LoadBMP("/Users/dongochuyen/Desktop/SnakeMaterials.bmp"); // vì không lấy được ảnh trực tiếp nên lấy qua đường path của ảnh ở desktop
    
    SDL_CHECK(surface, "SDL_LoadBMP(\"SnakeMaterials.bmp\")");
    SnakeMaterials = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_CHECK(SnakeMaterials, "SDL_CreateTextureFromSurface");
    SDL_FreeSurface(surface);
    

    segmentList.push_back(make_pair(5, 5));
    segmentList.push_back(make_pair(5, 6));
    segmentList.push_back(make_pair(4, 6));
    
    generateStrawberry();
}

void Snake::generateStrawberry()
{
  auto done = false;
  do
  {
    strawberryX = rand() % (Width / 64);
    strawberryY = rand() % (Height / 64);
    done = true;
    for (const auto &segment: segmentList)
    {
      if (strawberryX == segment.first && strawberryY == segment.second)
      {
        done = false;
        break;
      }
    }
  } while (!done);
}

Snake::~Snake()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

int Snake::exec()
{
    auto oldTick = SDL_GetTicks();
    for (auto done = false; !done;)
    {
        SDL_Event e;
        if (SDL_PollEvent(&e))
        {
            switch (e.type)
            {
                case SDL_KEYDOWN:
                {
                    switch(e.key.keysym.sym)
                    {
                        case SDLK_UP:
                            dx = 0;
                            dy = -1;
                            break;
                        case SDLK_RIGHT:
                            dx = 1;
                            dy = 0;
                            break;
                        case SDLK_DOWN:
                            dx = 0;
                            dy = 1;
                            break;
                        case SDLK_LEFT:
                            dx = -1;
                            dy = 0;
                            break;
                    }
                }
                    
                    break;
                case SDL_QUIT:
                    done = true;
                    break;
            }
        }
    SDL_SetRenderDrawColor(renderer, 150, 100, 150, 100);
    SDL_RenderClear(renderer);
        auto currentTick = SDL_GetTicks();
        for (auto t = oldTick; t < currentTick; t++)
        {
          if(!tick())
              return 1;
        }
        oldTick = currentTick;
        draw();
        SDL_RenderPresent(renderer); // give time to see window
        }
        return 0;
    }

bool Snake::tick()
{
  if (ticks++ % 250 == 0)
  {
    auto p = segmentList.front();
    p.first += dx;
    p.second += dy;
    if (p.first < 0 || p.first >= Width / 64 ||
        p.second < 0 || p.second >= Height / 64)
      return false; // gameover when snake get out of the screen
    for (const auto &segment: segmentList)
      if (p == segment)
        return false;
    segmentList.push_front(p);
    if (p.first != strawberryX || p.second != strawberryY)
      segmentList.pop_back();
    else
      generateStrawberry();
  }
  return true;
}

//draw a snake
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
    
    int ds[][3] = {
        {-1 , 0 , 0},
        {0 , -1 , 90},
        {1 , 0 , 180},
        {0 , 1 , -90},
    };
    
    //head part
    for(auto i = begin(segmentList); i != end(segmentList); i++)
    {
        float direction = 0;
        const auto &segment = *i;
        if(i == begin(segmentList))
        {// headopenmouth
            if(i->first + dx == strawberryX && i->second + dy == strawberryY)
            {
                src.x = HeadOpenMouth * 64;
            }
            else
            {
                src.x = Head * 64;
                if( i+1 != end(segmentList))
                {
                    const auto &nextSegment = * (i+1);
                    for(const auto &d:ds )
                    {
                        if(segment.first + d[0] == nextSegment.first && segment.second + d[1] == nextSegment.second)
                        {
                            direction = d[2];
                            break;
                        }
                    }
                }
            }
        }
        
        //tail part
        else if( i+1 == end(segmentList))
        {
            src.x = Tail * 64;
            const auto &previousSegment = * (i-1);
            for(const auto &d:ds )
            {
                if(segment.first == previousSegment.first + d[0]  && segment.second== previousSegment.second + d[1] )
                {
                        direction = d[2];
                        break;
                }
            }
        }
        
        else
        {//body part
            const auto &nextSegment = * (i+1);
            const auto &previousSegment = * (i-1);
            if(nextSegment.first == previousSegment.first)
            {
                src.x = Straight * 64;
                direction = 90;
            }
            else if(nextSegment.second == previousSegment.second)
            {
                src.x = Straight * 64;
                direction = 0;
            }
            else
            {
                src.x = Turn * 64;
                bool up = false;
                if(segment.first == nextSegment.first && segment.second - 1 == nextSegment.second)
                        up = true;
                if(segment.first == previousSegment.first && segment.second - 1 == previousSegment.second)
                        up = true;
        
                bool right= false;
                if(segment.first + 1 == nextSegment.first && segment.second == nextSegment.second)
                        right = true;
                if(segment.first + 1 == previousSegment.first && segment.second == previousSegment.second)
                        right = true;
                    
                bool down= false;
                if(segment.first == nextSegment.first && segment.second + 1 == nextSegment.second)
                        down = true;
                if(segment.first == previousSegment.first && segment.second + 1 == previousSegment.second)
                        down = true;
                    
                bool left= false;
                if(segment.first - 1 == nextSegment.first && segment.second == nextSegment.second)
                        left = true;
                if(segment.first - 1 == previousSegment.first && segment.second == previousSegment.second)
                        left = true;
                    
                if(up && right) direction =0;
                else if(right && down) direction = 90;
                else if(down && left) direction = 180;
                else if(left && up) direction = 270;
            }
        }
        dst.x = 64 * segment.first;
        dst.y = 64 * segment.second;
        
        SDL_RenderCopyEx(renderer, SnakeMaterials, &src, &dst, direction, nullptr, SDL_FLIP_NONE);
    }
    src.x = Strawberry * 64;
        
    dst.x = strawberryX * 64;
    dst.y = strawberryY * 64;
    SDL_RenderCopyEx(renderer, SnakeMaterials, &src, &dst, 0, nullptr, SDL_FLIP_NONE);
       
}
