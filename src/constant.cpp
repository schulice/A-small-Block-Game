#ifndef CONSTANT_CPP
#define CONSTANT_CPP
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include "Button.h"
#include "user.h"

SDL_KeyCode CHANGE_PRESS = SDLK_UP;
SDL_KeyCode LEFT_PRESS = SDLK_LEFT;
SDL_KeyCode RIGHT_PRESS = SDLK_RIGHT;
SDL_KeyCode DOWN_PRESS = SDLK_DOWN;
SDL_KeyCode PAUSE_PRESS = SDLK_p;
uint32_t STYLE_SPEED = 10;
std::string BACKGROUND_PATH = "resources/97517782_p0.jpg";
const int LINE_SCORE[5] = {0, 10, 30, 60, 100};
const Uint32 SHAPE_COLOR[8] = {0x006aa84f, 0x00ff9900, 0x0033c38a, 0x005aa5ea, 0x000d406f, 0x008e7cc3, 0x00d9d9d9, 0x007f6000};

std::string USER_DATA_PATH = "data/user_data.dat";
std::string FONT_PATH = "resources/JetBrainsMono-Light.ttf";
std::string BUTTON_PATH = "resources/button.png";
std::string MUSIC_BG_PATH = "resources/bgm.mp3";
User USER[9] = {{"", "",0, 0, 0}};
TTF_Font* FONT;

extern SDL_KeyCode CHANGE_PRESS;
extern SDL_KeyCode LEFT_PRESS;
extern SDL_KeyCode RIGHT_PRESS;
extern SDL_KeyCode DOWN_PRESS;
extern SDL_KeyCode PAUSE_PRESS;
extern uint32_t STYLE_SPEED;
extern std::string BACKGROUND_PATH;
extern const int LINE_SCORE[5];
extern const Uint32 SHAPE_COLOR[8];

extern std::string USER_DATA_PATH;
extern std::string FONT_PATH;
extern User USER[9];
extern TTF_Font* FONT;
extern std::string BUTTON_PATH;
extern std::string MUSIC_BG_PATH;
extern Button CONTRACETING_BUTTON[5];
extern Button USER_BUTTON[9];


#endif