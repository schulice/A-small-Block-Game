#include <SDL2/SDL_atomic.h>
#include "constant.cpp"
#include "TextInput.h"

bool TextDraw(SDL_Renderer *p, std::string s, int x, int y, int w, int h){
    bool sucess = 1;
    SDL_Color color = {0, 0, 0, 0xff};
    SDL_Surface *text_surface = TTF_RenderText_Solid(FONT, s.c_str(), color);
    if (text_surface == NULL) {sucess = 0; return sucess;}
    SDL_Texture *text_texture = SDL_CreateTextureFromSurface(p, text_surface);
    if (text_texture == NULL) {sucess = 0; return sucess;}
    SDL_Rect text_rect = {x, y, w, h};
    SDL_RenderCopy(p, text_texture, NULL, &text_rect);
    SDL_FreeSurface(text_surface);
    SDL_DestroyTexture(text_texture);
    return sucess;
}

TextInput::TextInput(int _x, int _y, int _w, int _h, std::string _text){
    x = _x;
    y = _y;
    w = _w;
    h = _h;
    text = _text;
}

void TextInput::Render(SDL_Renderer *renderer){
    SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
    SDL_Rect rect = {x, y, w, h};
    SDL_RenderFillRect(renderer, &rect);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xff);
    SDL_RenderDrawRect(renderer, &rect);
    TextDraw(renderer, text, x, y, w, h);
}

void TextInput::SetText(std::string _text){
    text = _text;
}

void TextInput::Input(SDL_Event &e){
    if (e.type == SDL_MOUSEBUTTONDOWN){
        int _x, _y;
        SDL_GetMouseState(&_x, &_y);
        if (Check(_x, _y)){
            SDL_StartTextInput();
            SDL_SetTextInputRect(NULL);
        }
        else SDL_StopTextInput();
    }
    else if (e.type == SDL_KEYDOWN){
        if (e.key.keysym.sym == SDLK_BACKSPACE && text.length() > 0)
            text.pop_back();
        else if (e.key.keysym.sym == SDLK_c && SDL_GetModState() & KMOD_CTRL)
            SDL_SetClipboardText(text.c_str());
        else if (e.key.keysym.sym == SDLK_v && SDL_GetModState() & KMOD_CTRL)
            text = SDL_GetClipboardText();
    }
    else if (e.type == SDL_TEXTINPUT)
        text += e.text.text;
}

std::string TextInput::GetText(){
    return text;
}

bool TextInput::Check(int _x, int _y){
    if (_x >= x && _x <= x + w && _y >= y && _y <= y + h)
        return 1;
    return 0;
}