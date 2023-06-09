#ifndef TEXTINPUT_H
#define TEXTINPUT_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <string>

class TextInput
{
private:
    int x, y, w, h;
    std::string text;
    SDL_Color color = {0, 0, 0, 0xff};

public:
    TextInput(int _x, int _y, int _w, int _h, std::string _text);
    void Render(SDL_Renderer *renderer);
    void SetText(std::string _text);
    void Input(SDL_Event &e);
    std::string GetText();
    bool Check(int _x, int _y);
    ~TextInput();
};

#endif