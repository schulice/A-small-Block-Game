#include "Button.h"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>
#include "constant.cpp"
#include <string>

extern std::string BUTTON_PATH;
extern TTF_Font* FONT;

Button::Button(){
    x = 0, y = 0;
    w = 0, h = 0;
    button = {x, y, w, h};
}
Button::Button(int _x, int _y, int _w, int _h){
    x = _x, y = _y;
    w = _w, h = _h;
    button = {x, y, w, h};
}

void Button::draw( SDL_Renderer* mainrenderer ){
    //texture init here
    texture = IMG_LoadTexture(mainrenderer, BUTTON_PATH.c_str());
    //image draw here
    SDL_RenderCopy(mainrenderer, texture, NULL, &button);
    //text draw here
    SDL_Color color = {0, 0, 0, 0xff};
    SDL_Surface* text_surface = TTF_RenderText_Solid(FONT, text.c_str(), color);
    SDL_Texture* text_texture = SDL_CreateTextureFromSurface(mainrenderer, text_surface);
    SDL_Rect text_rect = {x + w/2 - text_surface->w/2, y + h/2 - text_surface->h/2, text_surface->w, text_surface->h};
    SDL_RenderCopy(mainrenderer, text_texture, NULL, &text_rect);
    SDL_FreeSurface(text_surface);
    SDL_DestroyTexture(text_texture);
}

void Button::update( std::string _text ){
    text = _text;
}

bool Button::CheckEvent( int _x, int _y ){
    bool clicked = false;
    if (_x >= this->x && _x <= this->x + this->w && _y >= this->y && _y <= this->y + this->h){
        clicked = true;
    }
    return clicked;
}