#include <SDL2/SDL_events.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_mixer.h>
#include <algorithm>
#include <cstdio>
#include <forward_list>
#include "Button.cpp"
#include "constant.cpp"
#include "Shape.cpp"
#include "MainWindow.cpp"

extern std::string USER_DATA_PATH;
extern std::string FONT_PATH;
extern User USER[9];
extern TTF_Font* FONT;
extern std::string BUTTON_PATH;
extern std::string BACKGROUND_PATH;
extern std::string MUSIC_BG_PATH;

void PrintText(std::string s, SDL_Renderer *r, int x, int y, int w, int h, SDL_Color color){
	//SDL_Color color = {0, 0, 0, 0xff};
    SDL_Surface* text_surface = TTF_RenderText_Solid(FONT, s.c_str(), color);
    SDL_Texture* text_texture = SDL_CreateTextureFromSurface(r, text_surface);
	SDL_Rect rect = {x, y, w, h};
    SDL_RenderCopy(r, text_texture, NULL, &rect);
}




int main( int, char ** ){
	bool sucess = true;
	if ( SDL_Init( SDL_INIT_VIDEO ) < 0 ) sucess = false;
    if ( !( IMG_Init( IMG_INIT_PNG ) & IMG_INIT_PNG ) ) sucess = false;
	if ( TTF_Init() < 0 ) sucess = false;
	if ( Mix_Init(MIX_INIT_MP3) < 0 ) sucess = false;
	if ( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 ) sucess = false;
	SDL_Log("SDL_Init: %d\n", sucess);
	FONT = TTF_OpenFont(FONT_PATH.c_str(), 24);
	Mix_Music *bg_music = Mix_LoadMUS(MUSIC_BG_PATH.c_str());
	//Mix_PlayMusic(bg_music, SDL_TRUE);
	if ( bg_music == nullptr ) SDL_Log("music error!\n");
	else SDL_Log("music sucess!\n");

	/**
	SDL_RWops* user_data_file = SDL_RWFromFile( "data/user_data.dat", "r+b" );
	SDL_RWread(user_data_file, &USER, sizeof(User),9);
	SDL_RWclose( user_data_file );
	**/
	init_contract:;
	int id = 0;
	bool start_game = false;
	SDL_Window *ui = SDL_CreateWindow("Contracting UI",
								SDL_WINDOWPOS_UNDEFINED,
								SDL_WINDOWPOS_UNDEFINED,
								1600, 
								900, 
								0);
	if ( ui == nullptr ) SDL_Log("window error!\n");
    SDL_Renderer *ui_renderer = SDL_CreateRenderer(ui, -1, 0);
    if (ui_renderer == nullptr)  SDL_Log("renderer error!\n");
    SDL_Texture *bg_texture = IMG_LoadTexture( ui_renderer , BACKGROUND_PATH.c_str() );
    if ( bg_texture == nullptr ) SDL_Log("background error!\n");
	//SDL_RenderPresent(ui_renderer);
	Button select_button[4];
		for (int i = 0; i < 4; i++){
			select_button[i] = { 100, 200 + 150 * i, 200, 100 };
		};
		select_button[0].update("Start Game");
		select_button[1].update("Ranking");
		select_button[2].update("Settings");
		select_button[3].update("Exit");
		auto DrawBG_Selec = [&](){
			SDL_RenderCopy(ui_renderer, bg_texture, NULL, NULL);
			for (int i = 0; i < 4; i++){
				select_button[i].draw(ui_renderer);
			};
	};
	DrawBG_Selec();
	SDL_RenderPresent(ui_renderer);
	SDL_Event event;
	bool quit = false;
	Button data_button[9];
	for (int i = 0; i < 9; i++){
		data_button[i] = { 400 + 300 * (i / 3), 200 + 150 * (i % 3), 200, 100 };
		data_button[i].update(USER[i].name);
	};

	bool StartBar = false;
	bool RatingBar = false;
	bool SettingBar = false;
	while (!quit){
		while (SDL_PollEvent(&event)){
			if (event.type == SDL_QUIT) quit = true;
			if (event.type == SDL_MOUSEBUTTONDOWN){
				int x, y;
				SDL_GetMouseState(&x, &y);
				if ( select_button[0].CheckEvent(x, y) )
				{
					SDL_RenderClear(ui_renderer);
					DrawBG_Selec();
					for (int i = 0; i < 9; i++){
						data_button[i].draw(ui_renderer);
					};
					SDL_RenderPresent(ui_renderer);
					StartBar = true;
					RatingBar = false;
					SettingBar = false;
				}
				else if ( select_button[1].CheckEvent(x, y) )
				{
					SDL_RenderClear(ui_renderer);
					DrawBG_Selec();
					std::stable_sort(USER, USER + 9, [](User a, User b){return a.best_score > b.best_score;});
					SDL_Color color = {0, 0, 0, 0xff};
					for (int i = 0; i < 9; i++){
						if (USER[i].name == "") continue;
						SDL_Surface* text_surface = TTF_RenderText_Solid(FONT, USER[i].name.c_str(), color);
						SDL_Texture* text_texture = SDL_CreateTextureFromSurface(ui_renderer, text_surface);
						SDL_Rect rect = {400, 200 + 150 * i, 200, 100};
						SDL_RenderCopy(ui_renderer, text_texture, NULL, &rect);
						
						text_surface = TTF_RenderText_Solid(FONT, std::to_string(USER[i].best_score).c_str(), color);
						text_texture = SDL_CreateTextureFromSurface(ui_renderer, text_surface);
						rect = {700, 200 + 150 * i, 200, 100};
						SDL_RenderCopy(ui_renderer, text_texture, NULL, &rect);
						
						SDL_FreeSurface(text_surface);
						SDL_DestroyTexture(text_texture);
					}
					SDL_RenderPresent(ui_renderer);
					StartBar = false;
					RatingBar = true;
					SettingBar = false;
				}
				else if ( select_button[2].CheckEvent(x, y) )
				{
					//TODO settingUI
					quit = true;
				}
				else if ( select_button[3].CheckEvent(x, y) )
				{
					quit = true;
				}
				else if (StartBar){
					for (int i = 0; i < 9; i++){
						if (data_button[i].CheckEvent(x, y)){
							printf("Button %d clicked!\n", i);
							start_game = 1;
							id = i; 
							quit = 1;
							break;
						}
					}
				}
				else if (SettingBar){

				}
				if (quit) break;
			};
		};
	};
	SDL_DestroyTexture(bg_texture);
	SDL_DestroyRenderer(ui_renderer);
	SDL_DestroyWindow(ui);

	if(start_game){
		MainWindow *mainwindow = new MainWindow(10, 20, USER[id]);
		if (!mainwindow->WindowInit()) printf("main window init error!");
		else printf("main window init sucess!");
		mainwindow->GameStart();
		USER[id] = mainwindow->getUser();
		mainwindow->Close();
		delete mainwindow;
		goto init_contract;
	}
	

	/**
	user_data_file = SDL_RWFromFile( "data/user_data.dat", "r+b" );
	SDL_RWwrite(user_data_file, &USER, sizeof(User),9);
	SDL_RWclose( user_data_file );
	**/


	Mix_FreeMusic(bg_music);
	Mix_CloseAudio();
	TTF_CloseFont(FONT);
	Mix_Quit();
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}