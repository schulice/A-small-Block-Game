#ifndef _BUTTON_H_
#define _BUTTON_H_
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

class Button
{
public:
    Button();
    Button(int _x, int _y, int _w, int _h);
    ~Button();
    void draw( SDL_Renderer* mainrenderer );
    void update( std::string _text );
    bool CheckEvent( int x, int y );
private:
    int x, y;
    int w, h;
    SDL_Texture* texture;
    std::string text;
    SDL_Rect button;
};

#endif