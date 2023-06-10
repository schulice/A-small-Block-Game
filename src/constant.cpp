#ifndef CONSTANT_CPP
#define CONSTANT_CPP
#include <SDL2/SDL.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include "Button.h"
#include "user.h"

SDL_Keycode CHANGE_PRESS = SDLK_UP;
SDL_Keycode LEFT_PRESS = SDLK_LEFT;
SDL_Keycode RIGHT_PRESS = SDLK_RIGHT;
SDL_Keycode DOWN_PRESS = SDLK_DOWN;
SDL_Keycode PAUSE_PRESS = SDLK_p;
uint32_t STYLE_SPEED = 10;
const int LINE_SCORE[5] = {0, 10, 30, 60, 100};
const Uint32 SHAPE_COLOR_1[8] = {0x002f4f4f, 0x00800000, 0x00ff6347, 0x00db7093, 0x00e9967a, 0x008a2be2, 0x008b008b, 0x00ff69b4};
const Uint32 SHAPE_COLOR_2[8] = {0x006aa84f, 0x00ff9900, 0x0033c38a, 0x005aa5ea, 0x000d406f, 0x008e7cc3, 0x00d9d9d9, 0x007f6000};
Uint32 SHAPE_COLOR[8] = {0x006aa84f, 0x00ff9900, 0x0033c38a, 0x005aa5ea, 0x000d406f, 0x008e7cc3, 0x00d9d9d9, 0x007f6000};
int COLOR_STYLE = 1;

std::string BACKGROUND_PATH = "resources/background_1.jpg";
std::string USER_DATA_PATH = "data/user_data.txt";
std::string FONT_PATH = "resources/JetBrainsMono-Light.ttf";
std::string BUTTON_PATH = "resources/button.png";
std::string MUSIC_BG_PATH = "resources/bgm_1.mp3";
std::string SETTING_PATH = "data/setting.txt";
User USER[9] = {{"", "",0, 0, 0}};
TTF_Font* FONT;

int PLAY_ROW = 10;
int PLAY_LINE = 20;

extern SDL_Keycode CHANGE_PRESS;
extern SDL_Keycode LEFT_PRESS;
extern SDL_Keycode RIGHT_PRESS;
extern SDL_Keycode DOWN_PRESS;
extern SDL_Keycode PAUSE_PRESS;
extern uint32_t STYLE_SPEED;
extern std::string BACKGROUND_PATH;
extern const int LINE_SCORE[5];
extern Uint32 SHAPE_COLOR[8];


extern std::string SETTING_PATH;
extern std::string USER_DATA_PATH;
extern std::string FONT_PATH;
extern User USER[9];
extern TTF_Font* FONT;
extern std::string BUTTON_PATH;
extern std::string MUSIC_BG_PATH;
extern Button CONTRACETING_BUTTON[5];
extern Button USER_BUTTON[9];

extern int PLAY_ROW;
extern int PLAY_LINE;

#endif