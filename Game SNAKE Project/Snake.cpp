#include "Snake.hpp"
#include <string>

using namespace std;

//check for error
#define SDL_CHECK(x, msg)\
if (!(x)) throw runtime_error(string(msg": ") + SDL_GetError());

Snake::Snake()
{
    auto res = SDL_Init(SDL_INIT_EVERYTHING);
    SDL_CHECK(res == 0, "SDL_Init");
    SDL_CreateWindowAndRenderer(Width, Height, SDL_WINDOW_BORDERLESS, &window, &renderer);
    //SDL_WINDOW_BORDERLESS: no window decoration(in SDL_WindowFlags)
    
    SDL_CHECK(window, "SDL_CreateWindowAndRenderer");
    SDL_CHECK(renderer, "SDL_CreateWindowAndRenderer");
    
    
    // load pictures into the window
    SDL_Surface *surface = SDL_LoadBMP("/Users/dongochuyen/Desktop/Snake.bmp");
    SDL_CHECK(surface, "SDL_LoadBMP(\"SnakeMaterials.bmp\")");
    
    SnakeMaterials = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_CHECK(SnakeMaterials, "SDL_CreateTextureFromSurface");
    
    SDL_FreeSurface(surface);
    
    //3 segments to draw a snake on the screen: tail, body, head
    segmentList.push_back(make_pair(5, 5));
    segmentList.push_back(make_pair(5, 6));
    segmentList.push_back(make_pair(4, 6));
    
    generateStrawberry();
}

void Snake::generateStrawberry()
{
    bool done = false;
    // generate strawberry again and again
    do
    {
        strawberryX = rand() % (Width / 64);
        strawberryY = rand() % (Height / 64);
        done = true;
        //check if the strawberry inside the snake
        for (const auto &segment: segmentList)
        {
            if (strawberryX == segment.first && strawberryY == segment.second)
            {
                done = false;
                break;
            }
        }
    }
    while (!done);
}

void waitUntilKeyPressed()
{
    SDL_Event e;
    while (true) {
        if ( SDL_WaitEvent(&e) != 0 &&
             (e.type == SDL_KEYDOWN || e.type == SDL_QUIT) )
            return;
        SDL_Delay(100);
    }
}

//destructor
Snake::~Snake()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_DestroyTexture(SnakeMaterials);
    SDL_Quit();
}

//hàm thực hiện
int Snake::exec()
{
    waitUntilKeyPressed();
    auto oldTick = SDL_GetTicks();
    for (bool done = false; !done;)
    {
        SDL_Event e;
        if (SDL_PollEvent(&e))
        {
            switch (e.type)
            {
                case SDL_KEYDOWN:
                {
                    // move snake by keyboard
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
        //tham khảo ở thenumbet.io và cplusplus.com
        auto currentTick = SDL_GetTicks();
        for (auto t = oldTick; t < currentTick; t++)
        {
          if(!tick())
              return 0;
        }
        oldTick = currentTick;
        draw();
        SDL_RenderPresent(renderer); // give time to see window
        }
        return 0;
    }


bool Snake::tick()
{
    if (ticks++ % 200 == 0) // speed the snake moves
    {
        auto p = segmentList.front();
        p.first += dx;
        p.second += dy;
        
        
        // it's out when snake get out of the screen
        if (p.first < 0 || p.first >= Width / 64 || p.second < 0 || p.second >= Height / 64)
        {
            return false;
        }
        
        // it's out if snake eats its body
        for (const auto &segment: segmentList)
        {
            if (p == segment)
            {
                return false;
            }
        }
        
        //add at the front of the snake
        segmentList.push_front(p);
        
        // this part makes snake grows when it eat strawberry
        //if one of the condition is not equal --> pop_back
        //if both are equal --> not pop_back --> make snake be longer
        if (p.first != strawberryX || p.second != strawberryY)
        {
            //move the back of the snake
            segmentList.pop_back();
        }
        else generateStrawberry();
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
    
    // direction of all circumstances
    int ds[][3] = {
        {-1 , 0 , 0},
        {0 , -1 , 90},
        {1 , 0 , 180},
        {0 , 1 , -90},
    };
    
    for(auto i = segmentList.begin(); i != segmentList.end(); i++)
    {
        int direction = 0;
        const auto &segment = *i;
        //head part
        if(i == segmentList.begin())
        {
            //snake with headopenmouth
            if(segment.first + dx == strawberryX && segment.second + dy == strawberryY)
            {
                src.x = HeadOpenMouth * 64;
            }
            //snake with head
            else
            {
                src.x = Head * 64;
            }
            if( i+1 != segmentList.end())
            {
                const auto &nextSegment = * (i+1);
                for(const auto &d:ds )
                {
                    if(segment.first + d[0] == nextSegment.first && segment.second + d[1] == nextSegment.second)
                    {
                        // direction of head
                        direction = d[2];
                        break;
                    }
                }
            }
        }
        
        
        //tail part
        else if(i+1 == segmentList.end())
        {
            src.x = Tail * 64;
            const auto &previousSegment = *(i-1);
            for(const auto &d:ds )
            {
                if(segment.first == previousSegment.first + d[0]  && segment.second == previousSegment.second + d[1] )
                {
                    //direction of tail
                    direction = d[2];
                    break;
                }
            }
        }
        
        //body part
        else
        {
            const auto &nextSegment = *(i+1);
            const auto &previousSegment = *(i-1);
            
            //straight
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
            
            //turning body --> have 4 directions
            else
            {
                src.x = Turn * 64;
                
                bool up = false;
                if(segment.first == nextSegment.first && segment.second - 1 == nextSegment.second)
                        up = true;
                if(segment.first == previousSegment.first && segment.second - 1 == previousSegment.second)
                        up = true;
        
                
                bool right = false;
                if(segment.first + 1 == nextSegment.first && segment.second == nextSegment.second)
                        right = true;
                if(segment.first + 1 == previousSegment.first && segment.second == previousSegment.second)
                        right = true;
                  
                
                bool down = false;
                if(segment.first == nextSegment.first && segment.second + 1 == nextSegment.second)
                        down = true;
                if(segment.first == previousSegment.first && segment.second + 1 == previousSegment.second)
                        down = true;
                   
                
                bool left = false;
                if(segment.first - 1 == nextSegment.first && segment.second == nextSegment.second)
                        left = true;
                if(segment.first - 1 == previousSegment.first && segment.second == previousSegment.second)
                        left = true;
                  
                
                if(up && right) direction =0;
                else if(right && down) direction = 90;
                else if(down && left) direction = 180;
                else if(left && up) direction = -90;
            }
        }
        dst.x = 64 * segment.first;
        dst.y = 64 * segment.second;
        
        SDL_RenderCopyEx(renderer, SnakeMaterials, &src, &dst, direction, nullptr, SDL_FLIP_NONE);
        // copy a portion in snakematerials to put it on window, we can rotate, put it left or right just like we want
    }
    // put the strawberry on the screen
    src.x = Strawberry * 64;
        
    dst.x = strawberryX * 64;
    dst.y = strawberryY * 64;
    SDL_RenderCopyEx(renderer, SnakeMaterials, &src, &dst, 0, nullptr, SDL_FLIP_NONE);
       
}
