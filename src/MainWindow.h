#include <SDL2/SDL.h>
#include "Button.h"
#include "user.h"
#include "Shape.h"

class MainWindow 
{
protected:
    const int window_x = SDL_WINDOWPOS_UNDEFINED;
    const int window_y = SDL_WINDOWPOS_UNDEFINED;
    const int each_rec_w = 20;
    int w = 1600;
    int h = 900;

    int row_x;
    int line_y;
    bool pause;
    
    bool quit;
    User user;

    ShapeItem this_item = {0, 0};
    ShapeItem next_item = {0, 0};

    Shape *active_shape = NULL;
    Shape *hint_shape = NULL;
    SDL_Window* mainwindow = NULL;
    SDL_Surface* mainsurface =  NULL;
    SDL_Texture* backgroundtexture = NULL;
    SDL_Renderer* mainrenderer = NULL;
    bool play_pool[100][200];
    Uint32 color_pool[100][200] = {{0}};
    Button *speed_plus;
    Button *speed_minus;
    Button *pause_button;
    Button *quit_button;
public:
    MainWindow();
    MainWindow(int _w, int _h, User _user);
    bool WindowInit();
    bool BlockInit(Shape* &p, int b_x, int b_y, ShapeItem &item);
    bool ButtonInit();
    bool CheckRedLine();
    bool DataLoad();
    bool DataSave();
    int DeleteLine(int y);
    void DrawRedLine();
    void DrawShape(Shape* &p);
    void EventLoop( SDL_Event &e );
    void GameStart();
    void ItemInit(ShapeItem &re);
    void PoolInit(int row, int line);
    bool TryAgain();
    void UpdateScreen();
    User getUser();
    bool NameInput();
    bool GameOver();
    void Close();
    ~MainWindow();
};
