#include <SDL2/SDL_render.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_video.h>
#include <sys/types.h>
#include <SDL2/SDL.h>
#include <new>
#include <vector>
#include <cstdlib> 
#include <ctime>
constexpr int EACH_BLOCK_WIDTH = 20;

class Shape
{
protected:
    //int width;
    //int length;
    const int edge = 0;
    std::vector<std::vector<std::vector<bool>>> a;
    Uint32 color;
    int x;
    int y;
    int status;
public:
    Shape(int _x, int _y, int _status, Uint32 _color);
    bool Check(int _x, int _y, std::vector<std::vector<bool> > &play_ground);//if OK return 1
    void Move(int delta_x, int delta_y, std::vector<std::vector<bool> > &play_ground);
    void Change(std::vector<std::vector<bool> > &play_ground);
    void Stick();
};

Shape::Shape(int _x, int _y, int _status, Uint32 _color){
    x = _x;
    y = _y;
    status = _status;
    color = _color;
}
bool Shape::Check(int _x, int _y, std::vector<std::vector<bool> > &play_ground){
    bool is_empty = 1;
    for (int i = 0; i < edge; i++){
        for (int j = 0; j < edge; j++)
            if (a[status][i][j] && play_ground[_x+i][_y+j]) {is_empty = 0; break;}
    }
    return is_empty;
}
void Shape::Move(int _x, int _y, std::vector<std::vector<bool> > &play_ground){
    if (Check(x+_x, y+_y, play_ground)){
        x += _x;
        y += _y;
    }
}
void Shape::Change(std::vector<std::vector<bool> > &play_ground){
    int status_before = status;
    status++;
    if (status == edge) status = 0;
    if (!Check(x, y, play_ground)) status = status_before;
}
//TODO stick()

class Shape_I : public Shape
{
protected:
    const int edge = 4;
    std::vector<std::vector<std::vector<int>>> a = {{{0, 0, 0, 0},
                                                        {1, 1, 1, 1},
                                                        {0, 0, 0, 0},
                                                        {0, 0, 0, 0}},
                                                    {{0, 0, 1, 0},
                                                        {0, 0, 1, 0},
                                                        {0, 0, 1, 0},
                                                        {0, 0, 1, 0}},
                                                    {{0, 0, 0, 0},
                                                        {0, 0, 0, 0},
                                                        {1, 1, 1, 1},
                                                        {0, 0, 0, 0}},
                                                    {{0, 1, 0, 0},
                                                        {0, 1, 0, 0},
                                                        {0, 1, 0, 0},
                                                        {0, 1, 0, 0}}};
public:
    Shape_I(int _x, int _y, int _status, Uint32 _color) : Shape(_x, _y, _status,_color){};
};

class Shape_J : public Shape
{
protected:
    const int edge = 3;
    std::vector<std::vector<std::vector<int>>> a = {{{1, 0, 0},
                                                        {1, 1, 1},
                                                        {0, 0, 0}},
                                                    {{0, 1, 1},
                                                        {0, 1, 0},
                                                        {0, 1, 0}},
                                                    {{0, 0, 0},
                                                        {1, 1, 1},
                                                        {0, 0, 1}},
                                                    {{0, 1, 0},
                                                        {0, 1, 0},
                                                        {1, 1, 0}}};
public:
    Shape_J(int _x, int _y, int _status, Uint32 _color) : Shape(_x, _y, _status,_color){};
};

class Shape_L : public Shape
{
protected:
    const int edge = 3;
    std::vector<std::vector<std::vector<int>>> a = {{{0, 0, 0},
                                                        {1, 1, 1},
                                                        {1, 0, 0}},
                                                    {{1, 1, 0},
                                                        {0, 1, 0},
                                                        {0, 1, 0}},
                                                    {{0, 0, 1},
                                                        {1, 1, 1},
                                                        {0, 0, 0}},
                                                    {{0, 1, 0},
                                                        {0, 1, 0},
                                                        {0, 1, 1}}};
public:
    Shape_L(int _x, int _y, int _status, Uint32 _color) : Shape(_x, _y, _status,_color){};
};

class Shape_O : public Shape
{
protected:
    const int edge = 4;
    std::vector<std::vector<std::vector<int>>> a = {{{0, 1, 1, 0},
                                                        {0, 1, 1, 0},
                                                        {0, 0, 0, 0},
                                                        {0, 0, 0, 0}},
                                                        {{0, 1, 1, 0},
                                                        {0, 1, 1, 0},
                                                        {0, 0, 0, 0},
                                                        {0, 0, 0, 0}},
                                                        {{0, 1, 1, 0},
                                                        {0, 1, 1, 0},
                                                        {0, 0, 0, 0},
                                                        {0, 0, 0, 0}},
                                                        {{0, 1, 1, 0},
                                                        {0, 1, 1, 0},
                                                        {0, 0, 0, 0},
                                                        {0, 0, 0, 0}}};
public:
    Shape_O(int _x, int _y, int _status, Uint32 _color) : Shape(_x, _y, _status,_color){};
};

class Shape_S : public Shape
{
protected:
    const int edge = 3;
    std::vector<std::vector<std::vector<int>>> a = {{{0, 1, 1},
                                                        {1, 1, 0},
                                                        {0, 0, 0}},
                                                        {{0, 1, 0},
                                                        {0, 1, 1},
                                                        {0, 0, 1}},
                                                        {{0, 0, 0},
                                                        {0, 1, 1},
                                                        {1, 1, 0}},
                                                        {{1, 0, 0},
                                                        {1, 1, 0},
                                                        {0, 1, 0}}};
public:
    Shape_S(int _x, int _y, int _status, Uint32 _color) : Shape(_x, _y, _status,_color){};
};

class Shape_T : public Shape
{
protected:
    const int edge = 3;
    std::vector<std::vector<std::vector<int>>> a = {{{0, 1, 0},
                                                        {1, 1, 1},
                                                        {0, 0, 0}},
                                                        {{0, 1, 0},
                                                        {0, 1, 1},
                                                        {0, 1, 0}},
                                                        {{0, 0, 0},
                                                        {1, 1, 1},
                                                        {0, 1, 0}},
                                                        {{0, 1, 0},
                                                        {1, 1, 0},
                                                        {0, 1, 0}}};
public:
    Shape_T(int _x, int _y, int _status, Uint32 _color) : Shape(_x, _y, _status,_color){};
};

class Shape_Z : public Shape
{
protected:
    const int edge = 3;
    std::vector<std::vector<std::vector<int>>> a = {{{1, 1, 0},
                                                        {0, 1, 1},
                                                        {0, 0, 0}},
                                                        {{0, 0, 1},
                                                        {0, 1, 1},
                                                        {0, 1, 0}},
                                                        {{0, 0, 0},
                                                        {1, 1, 0},
                                                        {0, 1, 1}},
                                                        {{0, 1, 0},
                                                        {1, 1, 0},
                                                        {1, 0, 0}}};
public:
    Shape_Z(int _x, int _y, int _status, Uint32 _color) : Shape(_x, _y, _status,_color){};
};


class MainWindow 
{
protected:
    const int x = SDL_WINDOWPOS_UNDEFINED;
    const int y = SDL_WINDOWPOS_UNDEFINED;
    int w;
    int h;

    SDL_Window* mainwindow;
    SDL_Surface* mainsurface;
    SDL_Renderer* mainrenderer;
    std::vector<std::vector<bool>> play_pool;
    std::vector<std::vector<Uint32>> color_pool;
public:
    MainWindow(int _w, int _h){
        w = _w, h = _h;
        play_pool.resize(w+8, std::vector<bool>(h+8, true));
        for (int i = 0; i < w; i++)
            for (int j = 0; j < h; j++) play_pool[i+4][y] = false;
        color_pool.resize(w+4, std::vector<Uint32>(h, 0x000000));

        std::srand(std::time(nullptr));
        Shape *p = nullptr;
        BlockInit(p, x/2, y/2);
    };
    bool WindowInit(){
        bool sucess = true;
        mainwindow = SDL_CreateWindow("GAMEPLAYING",
                                x,
                                y,
                                w * EACH_BLOCK_WIDTH,
                                (h+4) * EACH_BLOCK_WIDTH,
                                0);
        if (mainwindow == nullptr) sucess = false;
        mainsurface = SDL_GetWindowSurface(mainwindow);
        if (mainsurface == nullptr) sucess = false;
        return sucess;
    }
    bool BlockInit(Shape* &p, int b_x, int b_y){
        int tmp = std::rand() % 7 + 1;
        Uint32 tmp_color = std::rand() % 0x01000000;
        Uint32 color = 0xff000000 + tmp_color;
        switch(tmp){
            case 1:
                p = new Shape_I(b_x, b_y, 0, color);
                break;
            case 2:
                p = new Shape_I(b_x, b_y, 0, color);
                break;
            case 3:
                p = new Shape_I(b_x, b_y, 0, color);
                break;
            case 4:
                p = new Shape_I(b_x, b_y, 0, color);
                break;
            case 5:
                p = new Shape_I(b_x, b_y, 0, color);
                break;
        }
        if (p == nullptr) return false;
        else return true;
    };
    void EventLoop(){};//TODO eventloop
    void Close(){};
    ~MainWindow(){
        SDL_DestroyWindow(mainwindow);
    }
};
