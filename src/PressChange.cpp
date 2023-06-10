#include <SDL2/SDL.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_ttf.h>
#include "constant.cpp"
#include <future>
#include <string>
using namespace std;

class PressChange{
private:
    SDL_Keycode keycode;
    int x, y, w, h;
public:
    PressChange();
    PressChange(int _x, int _y, int _w, int _h, SDL_Keycode _keycode);
    void Set(int _x, int _y, int _w, int _h, SDL_Keycode _keycode);
    bool Change(SDL_Event &e);
    bool Check(int _x, int _y);
    SDL_Keycode GetKey();
    void Render(SDL_Renderer *renderer);
    bool TextDraw(SDL_Renderer *p, std::string s, int x, int y, int w, int h);
};

PressChange::PressChange(){
    keycode = SDLK_UNKNOWN;
    x = y = w = h = 0;
}

PressChange::PressChange(int _x, int _y, int _w, int _h, SDL_Keycode _keycode){
    keycode = _keycode;
    x = _x;
    y = _y;
    w = _w;
    h = _h;
}

void PressChange::Set(int _x, int _y, int _w, int _h , SDL_Keycode _keycode){
    keycode = _keycode;
    x = _x;
    y = _y;
    w = _w;
    h = _h;
}

bool PressChange::Change(SDL_Event &e){
    bool sucess = false;
    if (e.type == SDL_KEYDOWN){
        if (e.key.keysym.sym != SDLK_BACKSPACE){
            keycode = e.key.keysym.sym;
            sucess = true;
        }
    }
    return sucess;
}

bool PressChange::Check(int _x, int _y){
    if (_x >= x && _x <= x + w && _y >= y && _y <= y + h)
        return 1;
    return 0;
}

SDL_Keycode PressChange::GetKey(){
    return keycode;
}

bool PressChange::TextDraw(SDL_Renderer *p, std::string s, int _x, int _y, int _w, int _h){
    bool sucess = 1;
    SDL_Color color = {0, 0, 0, 0xff};
    SDL_Surface *text_surface = TTF_RenderText_Solid(FONT, s.c_str(), color);
    if (text_surface == NULL) {sucess = 0; return sucess;}
    SDL_Texture *text_texture = SDL_CreateTextureFromSurface(p, text_surface);
    if (text_texture == NULL) {sucess = 0; return sucess;}
    SDL_Rect text_rect = {_x, _y, _w, _h};
    SDL_RenderCopy(p, text_texture, NULL, &text_rect);
    SDL_FreeSurface(text_surface);
    SDL_DestroyTexture(text_texture);
    return sucess;
}

void PressChange::Render(SDL_Renderer *renderer){
    std::string text = SDL_GetKeyName(keycode);
    SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
    SDL_Rect rect = {x, y, w, h};
    SDL_RenderFillRect(renderer, &rect);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xff);
    SDL_RenderDrawRect(renderer, &rect);
    int tmp_w = text.size() > 0 ? text.size() * 25 : 10;
    if (tmp_w > w) tmp_w = w;
    TextDraw(renderer, text, x, y, tmp_w, h);
}