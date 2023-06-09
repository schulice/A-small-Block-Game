#include <SDL2/SDL.h>
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
    std::string data_path;
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
    MainWindow(int _w, int _h, User _user);
    bool WindowInit();

    bool BlockInit(Shape* &p, int b_x, int b_y, ShapeItem &item);
    bool CheckRedLine();
    bool DataLoad();
    bool DataSave();
    int DeleteLine(int y);
    void DrawRedLine();
    void DrawShape(Shape* &p);
    void EventLoop( SDL_Event &e );
    void GameStart();
    void ItemInit(ShapeItem &re);
    void UpdateScreen();
    User getUser();

    bool NameInput();// TODO stl text input & path init
    bool GameOver();
    void Close();
    ~MainWindow();
};
