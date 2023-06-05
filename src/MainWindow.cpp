#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "MainWindow.h"
#include "Button.cpp"
#include "constant.cpp"
#include <string>
#include <random>

constexpr int EACH_BLOCK_WIDTH = 20;
constexpr int FREAM_RAET = 1;
constexpr int RESERVE_WIDTH = 400;

extern SDL_KeyCode CHANGE_PRESS;
extern SDL_KeyCode LEFT_PRESS;
extern SDL_KeyCode RIGHT_PRESS;
extern SDL_KeyCode DOWN_PRESS;
extern SDL_KeyCode PAUSE_PRESS;
extern uint32_t STYLE_SPEED;
extern std::string BACKGROUND_PATH;
extern const int LINE_SCORE[5];
extern const Uint32 SHAPE_COLOR[8];

class RandomGenerator {
public:
    RandomGenerator() : engine(rd()) {}

    int getRandomNumber(int min, int max) {
        std::uniform_int_distribution<int> dist(min, max);
        return dist(engine);
    }
private:
    std::random_device rd;
    std::mt19937 engine;
};

MainWindow::MainWindow(){
    w = 0, h = 0;
}
MainWindow::MainWindow(int _w, int _h, User _user){
    w = _w, h = _h;
    user = _user;
    if (user.name == ""){
        play_pool.resize(w+8, std::vector<bool>(h+8, true));
        for (int i = 0; i < w; i++)
            for (int j = 0; j < h + 4; j++) play_pool[i+4][j] = false;
        color_pool.resize(w+8, std::vector<Uint32>(h+8, 0x000000));
    }
    else{
        //DataLoad();//TODO dataload
    }
};
bool MainWindow::WindowInit(){
    bool sucess = true;
    pause = 0;
    quit = 0;
    mainwindow = SDL_CreateWindow("GAMEPLAYING",
                            window_x,
                            window_y,
                            1600,
                            900,
                            0);
    if (mainwindow == nullptr) sucess = false, SDL_Log("window error!\n");
    mainsurface = SDL_GetWindowSurface(mainwindow);
    if (mainsurface == nullptr) sucess = false, SDL_Log("surface error!\n");
    mainrenderer = SDL_CreateRenderer(mainwindow, -1, 0);
    if (mainrenderer == nullptr) sucess = false, SDL_Log("renderer error!\n");
    backgroundtexture = IMG_LoadTexture( mainrenderer, BACKGROUND_PATH.c_str() );
    if ( backgroundtexture == nullptr ) sucess = false, SDL_Log("background error!\n");
    return sucess;
};
void MainWindow::ItemInit(ShapeItem &p){
    RandomGenerator rng;
    if (p.style == 0){
        p.style = rng.getRandomNumber(1, 7);
        int color_tmp = rng.getRandomNumber(0, 7);
        Uint32 tmp_color = 0xff000000 + SHAPE_COLOR[color_tmp];
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
            p = new Shape_J(b_x, b_y, 0, item.color);
            break;
        case 3:
            p = new Shape_L(b_x, b_y, 0, item.color);
            break;
        case 4:
            p = new Shape_O(b_x, b_y, 0, item.color);
            break;
        case 5:
            p = new Shape_S(b_x, b_y, 0, item.color);
            break;
        case 6:
            p = new Shape_T(b_x, b_y, 0, item.color);
            break;
        case 7:
            p = new Shape_Z(b_x, b_y, 0, item.color);
            break;
    }
    if (p == nullptr) {printf("item init error\n"); return false;}
    else return true;
};
bool MainWindow::CheckRedLine(){
    bool is_red = false;
    for (int i = 0; i < w; i++){
        if (play_pool[i+4][4]) is_red = true;
    }
    return is_red;
}
void MainWindow::Close(){
    SDL_DestroyTexture( backgroundtexture );
	backgroundtexture = NULL;
	//Destroy window
    SDL_RenderClear(mainrenderer);
	SDL_DestroyRenderer( mainrenderer );
	SDL_DestroyWindow( mainwindow );
	mainrenderer = NULL;
	mainsurface = NULL;
	//Quit SDL subsystems
}
void MainWindow::DrawRedLine(){
    SDL_SetRenderDrawColor(mainrenderer, 0xff, 0x00, 0x00, 0xff);
    SDL_Rect tmp = {RESERVE_WIDTH, 4*each_rec_w, w*each_rec_w, each_rec_w};
    SDL_RenderFillRect(mainrenderer, &tmp);
    return;
}
void MainWindow::DrawShape(Shape* &p){
    for (int i = 0; i < p->edge; i++){
        for(int j = 0; j < p->edge; j++)
            if (p->GetBool(i, j)){
                Uint32 color_tmp = p->GetColor();
                Uint8 r_tmp = color_tmp % 0x01000000 / 0x00010000;
                Uint8 b_tmp = color_tmp % 0x00010000 / 0x00000100;
                Uint8 g_tmp = color_tmp % 0x00000100 / 0x00000001;
                SDL_SetRenderDrawColor(mainrenderer, r_tmp, b_tmp, g_tmp, 0xff);
                SDL_Rect tmp = {(p->x+i-4)*each_rec_w + RESERVE_WIDTH, (p->y+j)*each_rec_w, each_rec_w, each_rec_w};
                SDL_RenderFillRect( mainrenderer, &tmp );
            }
    }
    return;
}
void MainWindow::UpdateScreen(){
    //background draw
    SDL_RenderClear(mainrenderer);
    SDL_RenderCopy( mainrenderer, backgroundtexture, NULL, NULL );
    //red line draw
    DrawRedLine();
    //active style draw
    if (active_shape != nullptr) DrawShape(active_shape);
    if (hint_shape != nullptr) DrawShape(hint_shape);
    printf("finish active shape draw\n");
    //play pool draw
    for (int j = 0; j < h+4; j++){
        for (int i = 0; i < w; i++){
            if (!play_pool[i+4][j]) continue;
            Uint32 color_tmp = color_pool[i+4][j];
            Uint8 r_tmp = color_tmp % 0x01000000 / 0x00010000;
            Uint8 b_tmp = color_tmp % 0x00010000 / 0x00000100;
            Uint8 g_tmp = color_tmp % 0x00000100 / 0x00000001;
            SDL_SetRenderDrawColor(mainrenderer, r_tmp, b_tmp, g_tmp, 0xff);
            SDL_Rect tmp = {i*each_rec_w + RESERVE_WIDTH, j*each_rec_w, each_rec_w, each_rec_w};
            SDL_RenderFillRect( mainrenderer, &tmp );
        }
    }
    SDL_RenderPresent( mainrenderer );
}
void MainWindow::EventLoop( SDL_Event &e ){
    while( SDL_PollEvent( &e ) != 0 )
    {
        switch( e.type )
        {
        case SDL_QUIT:{
            quit = true;
            printf("quit\n");
            break;
        }
        case SDL_KEYDOWN:{
            SDL_Keycode key = e.key.keysym.sym;
            if ( key == CHANGE_PRESS ){
                active_shape->Change(play_pool);
            }else if ( key == LEFT_PRESS && !pause ){
                active_shape->Move(-1, 0, play_pool);
            }else if ( key == RIGHT_PRESS && !pause ){
                active_shape->Move(1, 0, play_pool);
            }else if ( key == DOWN_PRESS && !pause ){
                active_shape->Move(0, 1, play_pool);
            }else if ( key == PAUSE_PRESS ){
                if (!pause) pause = true;
                else pause = false;
            }else { continue; };
            UpdateScreen();
            SDL_Delay(10);
            break;
        }
        case SDL_MOUSEBUTTONDOWN:{
            //TODO mouse event

            break;
        }
        };
        if (quit) break;
    }
}
int MainWindow::DeleteLine(int _y){
    int counter = 0;
    for (int j =_y; j < _y+4 && j < h+4; j++){
        bool is_full = 1;
        for (int i = 1; i < w; i++){
            if(!play_pool[i+4][j]) {is_full = 0; break;}
        }
        if (is_full){
            counter++;
            for (int k = j; k > 0; k--){
                for (int tmp = 0; tmp < w; tmp++){
                    play_pool[tmp+4][k] = play_pool[tmp+4][k-1];
                    color_pool[tmp+4][k] = color_pool[tmp+4][k-1];
                }
            }
        }
    }
    return counter;
};
void MainWindow::GameStart(){
    ItemInit(this_item);
    ItemInit(next_item);
    uint32_t speed_counter = 0;
    while (!CheckRedLine()){
        printf("game start: %d\n", speed_counter);//FIXME test
        BlockInit(active_shape, w/2 + 4, 0, this_item);
        BlockInit(hint_shape, -2, 0, next_item);
        printf("end block init\n");
        int delete_line = 0;
        while (active_shape != nullptr){
            Uint32 begin = SDL_GetTicks();
            SDL_Event e;
            EventLoop(e); 
            if (quit) break;
            if (!pause) speed_counter++;
            if (!pause && (speed_counter == STYLE_SPEED)){
                speed_counter = 0;
                if (!active_shape->Move(0, 1, play_pool)){
                    active_shape->Stick(play_pool, color_pool);
                    delete_line = DeleteLine(active_shape->y);
                    delete active_shape;
                    active_shape = nullptr;
                    printf("end stick\n");
                }
            };
            UpdateScreen();
            Uint32 end = SDL_GetTicks();
            Uint32 delay = 1000/FREAM_RAET - (end - begin);
            printf("delay: %d\n", delay);
            if (delay <= 1000/FREAM_RAET) SDL_Delay(delay);
            // TODO savedata
        }
        user.score += LINE_SCORE[delete_line];
        printf("Score is: %d\n", user.score);
        if (quit) break;
        this_item = next_item;
        next_item.style = 0;
        delete hint_shape;
        hint_shape = nullptr;
        ItemInit(next_item);
    }
    return;
};
User MainWindow::getUser(){
    return user;
};
MainWindow::~MainWindow(){
    Close();
};