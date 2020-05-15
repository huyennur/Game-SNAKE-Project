#ifndef Snake_hpp
#define Snake_hpp

#include <SDL.h>
#include <deque>

using namespace std;

class Snake
{
public:
    Snake();
    ~Snake();
    int exec();
    void draw();
    bool tick();
    
    const int Width = 1280;
    const int Height = 720;
    
    //đặt toạ độ theo chiều của bức ảnh
    const int HeadOpenMouth = 0;
    const int Tail = 1;
    const int Turn = 2;
    const int Straight = 3;
    const int Head = 4;
    const int Strawberry = 5;

private:
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *SnakeMaterials;
    
    //khởi tạo toạ độ
    deque<pair<int, int>> segmentList;
    
    int ticks = 0;
       
    //khởi tạo position of snake
    int dx = 1;
    int dy = 0;
    
    //khởi tạo toạ độ của Strawberry
    int strawberryX;
    int strawberryY;
    
    void generateStrawberry();
    
};

#endif /* Snake_hpp */
