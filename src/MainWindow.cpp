#include <SDL2/SDL_haptic.h>
#include <SDL2/SDL_keycode.h>
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
constexpr int EACH_BLOCK_WIDTH = 20;
constexpr int FREAM_RAET = 60;
constexpr int RESERVE_WIDTH = 200;
SDL_KeyCode CHANGE_PRESS = SDLK_UP;
SDL_KeyCode LEFT_PRESS = SDLK_LEFT;
SDL_KeyCode RIGHT_PRESS = SDLK_RIGHT;
SDL_KeyCode DOWN_PRESS = SDLK_DOWN;
SDL_KeyCode PAUSE_PRESS = SDLK_p;
uint32_t STYLE_SPEED = 1;
std::string BACKGROUND_PATH = "resources/97517782_p0.jpg";



struct ShapeItem
{
    int style;
    Uint32 color; 
};

class Shape
{
protected:
    //int width;
    //int length;
    const int edge = 0;
    std::vector<std::vector<std::vector<bool>>> a;
    Uint32 color;
    int status;
public:
    int x;
    int y;
public:
    Shape(int _x, int _y, int _status, Uint32 _color);
    bool Check(std::vector<std::vector<bool> > &play_ground);//if OK return 1
    bool Move(int delta_x, int delta_y, std::vector<std::vector<bool> > &play_ground);
    void Change(std::vector<std::vector<bool> > &play_ground);
    void Stick(std::vector<std::vector<bool> > &play_pool, std::vector<std::vector<Uint32> > &color_pool);
};

Shape::Shape(int _x, int _y, int _status, Uint32 _color){
    x = _x;
    y = _y;
    status = _status;
    color = _color;
}
bool Shape::Check(std::vector<std::vector<bool> > &play_ground){
    bool is_empty = 1;
    for (int i = 0; i < edge; i++){
        for (int j = 0; j < edge; j++)
            if (a[status][i][j] && play_ground[x+i][y+j]) {is_empty = 0; break;}
    }
    return is_empty;
}
bool Shape::Move(int _x, int _y, std::vector<std::vector<bool> > &play_ground){
    bool sucess = 1;
    x += _x;
    y += _y;
    if (!Check(play_ground)){
        x -= _x;
        y -= _y;
        sucess = 0;
    }
    return sucess;
}
void Shape::Change(std::vector<std::vector<bool> > &play_ground){
    int status_before = status;
    status++;
    if (status == edge) status = 0;
    if (!Check(play_ground)) status = status_before;
}
void Shape::Stick(std::vector<std::vector<bool> > &play_pool, std::vector<std::vector<Uint32> > &color_pool){
    for (int i = 0; i < edge; i++)
        for (int j = 0; j < edge; j++)
            if (a[status][i][j]){
                play_pool[x+i][y+i] = 1;
                color_pool[x-4+i][y-4+i] = color;
            }
}

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
    const int window_x = SDL_WINDOWPOS_UNDEFINED;
    const int window_y = SDL_WINDOWPOS_UNDEFINED;
    const int each_rec_w = 20;
    int w;
    int h;
    bool pause;
    bool quit;
    ShapeItem this_item;
    ShapeItem next_item;
    Shape *active_shape;
    Shape *hint_shape;
    SDL_Window* mainwindow;
    SDL_Surface* mainsurface;
    SDL_Texture* backgroundtexture;
    SDL_Renderer* mainrenderer;
    std::vector<std::vector<bool>> play_pool;
    std::vector<std::vector<Uint32>> color_pool;
public:
    MainWindow();
    MainWindow(int _w, int _h);
    bool WindowInit();
    void ItemInit(ShapeItem &re);
    bool BlockInit(Shape* &p, int b_x, int b_y, ShapeItem &item);
    void GameStart();
    void UpdateScreen();//TODO upscr
    bool CheckRedLine();
    void EventLoop();
    void Close();//TODO close()
    ~MainWindow();
};

MainWindow::MainWindow(){
    w = RESERVE_WIDTH, h = 0;
}
MainWindow::MainWindow(int _w, int _h){
    w = RESERVE_WIDTH + _w, h = _h;
    play_pool.resize(w+8, std::vector<bool>(h+8, true));
    for (int i = 0; i < w; i++)
        for (int j = 0; j < h; j++) play_pool[i+4][j] = false;
    color_pool.resize(w, std::vector<Uint32>(h+4, 0x000000));
};
bool MainWindow::WindowInit(){
    bool sucess = true;
    pause = 0;
    quit = 0;
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 ) sucess = false;
    if ( !( IMG_Init( IMG_INIT_PNG ) & IMG_INIT_PNG ) ) sucess = false;
    mainwindow = SDL_CreateWindow("GAMEPLAYING",
                            window_x,
                            window_y,
                            w * EACH_BLOCK_WIDTH + RESERVE_WIDTH,
                            (h+4) * EACH_BLOCK_WIDTH,
                            0);
    if (mainwindow == nullptr) sucess = false;
    mainsurface = SDL_GetWindowSurface(mainwindow);
    if (mainsurface == nullptr) sucess = false;
    mainrenderer = SDL_GetRenderer(mainwindow);
    if (mainrenderer == nullptr) sucess = false;
    backgroundtexture = IMG_LoadTexture( mainrenderer, BACKGROUND_PATH.c_str() );
    return sucess;
};
void MainWindow::ItemInit(ShapeItem &p){
    if (p.style == 0){
        p.style = std::rand() % 7 + 1;
        Uint32 tmp_color = std::rand() % 0x01000000;
        p.color = 0xff000000 + tmp_color;
    };
    return;
}
bool MainWindow::BlockInit(Shape* &p, int b_x, int b_y, ShapeItem &item){
    if (p != nullptr) return true;
    switch(item.style){
        case 1:
            p = new Shape_I(b_x, b_y, 0, item.color);
            break;
        case 2:
            p = new Shape_I(b_x, b_y, 0, item.color);
            break;
        case 3:
            p = new Shape_I(b_x, b_y, 0, item.color);
            break;
        case 4:
            p = new Shape_I(b_x, b_y, 0, item.color);
            break;
        case 5:
            p = new Shape_I(b_x, b_y, 0, item.color);
            break;
    }
    if (p == nullptr) return false;
    else return true;
};
void MainWindow::GameStart(){
    std::srand(std::time(nullptr));
    ItemInit(this_item);
    ItemInit(next_item);
    uint32_t speed_counter = 0;
    while (!CheckRedLine()){
        BlockInit(active_shape, w/2, 0, this_item);
        BlockInit(hint_shape, w/2, 0, next_item);
        while (active_shape != nullptr){
            uint32_t begin = SDL_GetTicks();
            EventLoop();
            speed_counter++;
            if (!pause && (speed_counter == STYLE_SPEED)){
                speed_counter = 0;
                if (!active_shape->Move(0, 1, play_pool)){
                    active_shape->Stick(play_pool, color_pool);
                    active_shape = nullptr;
                }
            };
            UpdateScreen();
            uint32_t delay = 1000/FREAM_RAET - (SDL_GetTicks() - begin);
            if (delay > 0) SDL_Delay(delay);
            if (quit) break;// TODO savedata
        }
        if (quit) break;
        active_shape = hint_shape;
        delete hint_shape;
        hint_shape = nullptr;
        ItemInit(next_item);
    }
    return;
};
void MainWindow::UpdateScreen(){

    SDL_RenderCopy( mainrenderer, backgroundtexture, NULL, NULL );
    SDL_RenderPresent( mainrenderer );
}
void MainWindow::EventLoop(){
    SDL_Event e;
    while( SDL_PollEvent( &e ) != 0 )
    {
        if( e.type == SDL_QUIT ){
            quit = true;
        }
        else if ( e.type == SDL_KEYDOWN && !pause ){
            if ( e.key.keysym.sym == CHANGE_PRESS ){
                active_shape->Change(play_pool);
            }else if ( e.key.keysym.sym == LEFT_PRESS ){
                active_shape->Move(-1, 0, play_pool);
            }else if ( e.key.keysym.sym == RIGHT_PRESS ){
                active_shape->Move(1, 0, play_pool);
            }else if ( e.key.keysym.sym == DOWN_PRESS ){
                active_shape->Move(0, 1, play_pool);
            }else if ( e.key.keysym.sym == PAUSE_PRESS){
                pause = true;
            }else {};
            UpdateScreen();
        };
    }
}
bool MainWindow::CheckRedLine(){
    bool is_red = false;
    for (int i = 0; i < w; i++){
        if (play_pool[i+4][4]) is_red = true;
    }
    return is_red;
}
