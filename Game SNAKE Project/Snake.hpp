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
    
    //đặt toạ độ theo chiều của bức ảnh
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
    
    //khởi tạo toạ độ
    deque<pair<int, int>> segmentList;
    
    unsigned ticks = 0;
       
    //khởi tạo position of snake
    int dx = 1;
    int dy = 0;
    
    //khởi tạo toạ độ của Strawberry
    int strawberryX;
    int strawberryY;
    
    void generateStrawberry();
    
};

#endif /* Snake_hpp */
