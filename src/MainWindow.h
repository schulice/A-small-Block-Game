#include <SDL2/SDL_haptic.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_image.h>
#include <bits/fs_fwd.h>
#include <sys/types.h>
#include <SDL2/SDL.h>
#include <cstdint>
#include <new>
#include <vector>
#include <cstdlib> 
#include <ctime>
#include <string>

struct ShapeItem
{
    int style;
    Uint32 color; 
};

struct User
{
    std::string name;
    int score;
    int best_score;
    int sum_score;
};
class Shape
{
protected:
    //int width;
    //int length;
    std::vector<std::vector<std::vector<bool>>> a;
    Uint32 color;
    int status;
public:
    int edge = 0;
    int x;
    int y;
public:
    Shape(int _x, int _y, int _status, Uint32 _color);
    Uint32 GetColor();
    bool Check(std::vector<std::vector<bool> > &play_ground);//if OK return 1
    bool Move(int delta_x, int delta_y, std::vector<std::vector<bool> > &play_ground);
    bool Change(std::vector<std::vector<bool> > &play_ground);
    bool Stick(std::vector<std::vector<bool> > &play_pool, std::vector<std::vector<Uint32> > &color_pool);
    bool GetBool(int _x, int _y){
        return a[status][_x][_y];
    }
};
class Shape_I : public Shape
{
protected:
public:
    Shape_I(int _x, int _y, int _status, Uint32 _color) : Shape(_x, _y, _status,_color){
        edge = 4;
        a = {{{0, 0, 0, 0},
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
    };
};

class Shape_J : public Shape
{
protected:
public:
    Shape_J(int _x, int _y, int _status, Uint32 _color) : Shape(_x, _y, _status,_color){
        edge = 3;
        a = {{{1, 0, 0},
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
    };
};

class Shape_L : public Shape
{
protected:
public:
    Shape_L(int _x, int _y, int _status, Uint32 _color) : Shape(_x, _y, _status,_color){
        edge = 3;
        a = {{{0, 0, 1},
                {1, 1, 1},
                {0, 0, 0}},
            {{0, 1, 0},
                {0, 1, 0},
                {0, 1, 1}},
            {{0, 0, 0},
                {1, 1, 1},
                {1, 0, 0}},
            {{1, 1, 0},
                {0, 1, 0},
                {0, 1, 0}}};
    };
};

class Shape_O : public Shape
{
protected:
public:
    Shape_O(int _x, int _y, int _status, Uint32 _color) : Shape(_x, _y, _status,_color){
        edge = 4;
        a = {{{0,1, 1, 0},
                {0,1, 1, 0},
                {0,0, 0, 0},
                {0,0, 0, 0}},
            {{0,1, 1, 0},
                {0,1, 1, 0},
                {0,0, 0, 0},
                {0,0, 0, 0}},
            {{0,1, 1, 0},
                {0,1, 1, 0},
                {0,0, 0, 0},
                {0,0, 0, 0}},
            {{0,1, 1, 0},
                {0,1, 1, 0},
                {0,0, 0, 0},
                {0,0, 0, 0}}};
    };
};

class Shape_S : public Shape
{
protected:
public:
    Shape_S(int _x, int _y, int _status, Uint32 _color) : Shape(_x, _y, _status,_color){
        edge = 3;
        a = {{{0, 1, 1},
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
    };
};

class Shape_T : public Shape
{
protected:
public:
    Shape_T(int _x, int _y, int _status, Uint32 _color) : Shape(_x, _y, _status,_color){
        edge = 3;
        a = {{{0, 1, 0},
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
    };
};

class Shape_Z : public Shape
{
protected:
public:
    Shape_Z(int _x, int _y, int _status, Uint32 _color) : Shape(_x, _y, _status,_color){
        edge = 3;
        a = {{{1, 1, 0},
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
    };
};

class MainWindow 
{
protected:
    const int window_x = SDL_WINDOWPOS_UNDEFINED;
    const int window_y = SDL_WINDOWPOS_UNDEFINED;
    const int each_rec_w = 20;
    User user;
    int w;
    int h;
    bool pause;
    bool quit;
    ShapeItem this_item = {0, 0};
    ShapeItem next_item = {0, 0};
    Shape *active_shape = NULL;
    Shape *hint_shape = NULL;
    SDL_Window* mainwindow = NULL;
    SDL_Surface* mainsurface =  NULL;
    SDL_Texture* backgroundtexture = NULL;
    SDL_Renderer* mainrenderer = NULL;
    std::vector<std::vector<bool>> play_pool;
    std::vector<std::vector<Uint32>> color_pool;
public:
    MainWindow();
    MainWindow(int _w, int _h, std::string name);
    bool WindowInit();
    void ItemInit(ShapeItem &re);
    bool BlockInit(Shape* &p, int b_x, int b_y, ShapeItem &item);
    void GameStart();
    void UpdateScreen();//TODO up task
    bool CheckRedLine();
    void DrawRedLine();
    void DrawShape(Shape* &p);
    void EventLoop( SDL_Event &e );
    void Close();
    ~MainWindow();
};