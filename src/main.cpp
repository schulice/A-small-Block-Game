#include <SDL2/SDL.h>
#include <SDL2/SDL_cpuinfo.h>
#include <SDL2/SDL_gesture.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_mixer.h>
#include <charconv>
#include <cinttypes>
#include <cstdio>
#include <fstream>
#include <algorithm>
#include <cstdio>
#include <forward_list>
#include <string>
#include <utility>
#include "Button.cpp"
#include "TextInput.h"
#include "constant.cpp"		//CONSTANT
#include "Shape.cpp"
#include "MainWindow.cpp"
#include "PressChange.cpp"

void PrintText(std::string s, SDL_Renderer *r, int x, int y, int w, int h, SDL_Color color){
	//SDL_Color color = {0, 0, 0, 0xff};
    SDL_Surface* text_surface = TTF_RenderText_Solid(FONT, s.c_str(), color);
    SDL_Texture* text_texture = SDL_CreateTextureFromSurface(r, text_surface);
	SDL_Rect rect = {x, y, w, h};
    SDL_RenderCopy(r, text_texture, NULL, &rect);
	SDL_FreeSurface(text_surface);
	SDL_DestroyTexture(text_texture);
}

void SaveUser(){
	FILE *f = fopen(USER_DATA_PATH.c_str(), "w");
	for (int i = 0; i < 9; i++){
		fprintf(f, "%s\n", USER[i].name.c_str());
		fprintf(f, "%s\n", USER[i].data_path.c_str());
		fprintf(f, "%d\n", USER[i].best_score);
		fprintf(f, "%d\n", USER[i].sum_score);
		fprintf(f, "%lu\n", USER[i].size);
	}
	fclose(f);
}
void LoadUser(){
	std::ifstream  a(USER_DATA_PATH, std::ios::in);
	for (int i = 0; i < 9; i++){
		std::getline(a, USER[i].name);
		std::getline(a, USER[i].data_path);
		a >> USER[i].best_score;
		a >> USER[i].sum_score;
		a >> USER[i].size;
		a.ignore();
	}
	a.close();
}

void SaveSetting(){
	FILE *f = fopen(SETTING_PATH.c_str(), "w");
	fprintf(f, "%s\n", BACKGROUND_PATH.c_str());
	fprintf(f, "%s\n", MUSIC_BG_PATH.c_str());
	fprintf(f, "%d\n", PLAY_ROW);
	fprintf(f, "%d\n", PLAY_LINE);
	fprintf(f, "%d\n", LEFT_PRESS);
	fprintf(f, "%d\n", RIGHT_PRESS);
	fprintf(f, "%d\n", CHANGE_PRESS);
	fprintf(f, "%d\n", DOWN_PRESS);
	fprintf(f, "%d\n", PAUSE_PRESS);
	fclose(f);
}

void LoadSetting(){
	std::ifstream  a(SETTING_PATH, std::ios::in);
	std::getline(a, BACKGROUND_PATH);
	std::getline(a, MUSIC_BG_PATH);
	a >> PLAY_ROW;
	a >> PLAY_LINE;
	a >> LEFT_PRESS;
	a >> RIGHT_PRESS;
	a >> CHANGE_PRESS;
	a >> DOWN_PRESS;
	a >> PAUSE_PRESS;
	a.close();
}

int main( int, char ** ){
	//Init SDL
	bool sucess = true;
	if ( SDL_Init( SDL_INIT_VIDEO ) < 0 ) sucess = false;
    if ( !( IMG_Init( IMG_INIT_PNG ) & IMG_INIT_PNG ) ) sucess = false;
	if ( TTF_Init() < 0 ) sucess = false;
	if ( Mix_Init(MIX_INIT_MP3) < 0 ) sucess = false;
	if ( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 ) sucess = false;
	SDL_Log("SDL_Init: %d\n", sucess);
	FONT = TTF_OpenFont(FONT_PATH.c_str(), 24);
	Mix_Music *bg_music = Mix_LoadMUS(MUSIC_BG_PATH.c_str());
	Mix_PlayMusic(bg_music, SDL_TRUE);
	if ( bg_music == nullptr ) SDL_Log("music error!\n");
	else SDL_Log("music sucess!\n");
	
	LoadUser();
	printf("LoadUser\n");
	LoadSetting();

	//contracting window
	init_contract:;
	printf("init_contract\n");
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
		SDL_RenderClear(ui_renderer);
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

	Button BDI_setting[2];
	BDI_setting[0] = { 700, 200, 50, 50 };
	BDI_setting[1] = { 850, 200, 50, 50 };
	BDI_setting[0].update("1");
	BDI_setting[1].update("2");
	Button BDM_setting[2];
	BDM_setting[0] = { 700, 270, 50, 50 };
	BDM_setting[1] = { 850, 270, 50, 50 };
	BDM_setting[0].update("1");
	BDM_setting[1].update("2");
	Button color_setting[2]; 
	color_setting[0] = { 700, 340, 50, 50 };
	color_setting[1] = { 850, 340, 50, 50 };
	color_setting[0].update("1");
	color_setting[1].update("2");
	Button delete_all_user = { 800, 620, 350, 100 };
	delete_all_user.update("Delete_All_Users");
	TextInput row_input(600, 410, 100, 50, std::to_string(PLAY_ROW));
	TextInput line_input(800, 410, 100, 50, std::to_string(PLAY_LINE));

	PressChange press_change[5];
	press_change[0] = { 600, 480, 100, 50, LEFT_PRESS};
	press_change[1] = { 800, 480, 100, 50, RIGHT_PRESS};
	press_change[2] = { 600, 550, 100, 50, DOWN_PRESS};
	press_change[3] = { 800, 550, 100, 50, CHANGE_PRESS};
	press_change[4] = { 600, 620, 100, 50, PAUSE_PRESS};
	auto DrawSetting = [&](){
		DrawBG_Selec();
		SDL_Color color = { 00, 00, 00, 0xff };
		PrintText("BGI:", ui_renderer, 500, 200, 100, 50, color);
		PrintText("BGM:", ui_renderer, 500, 270, 100, 50, color);
		PrintText("Color:", ui_renderer, 500, 340, 100, 50, color);
		PrintText("Row:", ui_renderer, 500, 410, 100, 50, color);
		PrintText("Line:", ui_renderer, 700, 410, 100, 50, color);
		PrintText("Left:", ui_renderer, 500, 480, 100, 50, color);
		PrintText("Right:", ui_renderer, 700, 480, 100, 50, color);
		PrintText("Down:", ui_renderer, 500, 550, 100, 50, color);
		PrintText("Change:", ui_renderer, 700, 550, 100, 50, color);
		PrintText("Pause:", ui_renderer, 500, 620, 100, 50, color);

		for (int i = 0; i < 2; i++){
			BDI_setting[i].draw(ui_renderer);
			BDM_setting[i].draw(ui_renderer);
			color_setting[i].draw(ui_renderer);
		};
		row_input.Render(ui_renderer);
		line_input.Render(ui_renderer);
		delete_all_user.draw(ui_renderer);
		for (int i = 0; i < 5; i++){
			press_change[i].Render(ui_renderer);
		};
	};

	bool StartBar = false;
	bool RatingBar = false;
	bool SettingBar = false;
	//event loop
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
					for (int i = 0; i < 9; i++){
						data_button[i].update(USER[i].name);
					};
					SDL_Color color = {0, 0, 0, 0xff};
					for (int i = 0; i < 9; i++){
						if (USER[i].name == "") continue;
						PrintText(USER[i].name, ui_renderer, 500, 100+40*i, USER[i].name.size()*20, 50, color);
						std::string tmp = std::to_string(USER[i].best_score);
						PrintText(tmp, ui_renderer, 1000, 100+40*i, tmp.size()*20, 50, color);
					}
					SDL_RenderPresent(ui_renderer);
					StartBar = false;
					RatingBar = true;
					SettingBar = false;
				}
				else if ( select_button[2].CheckEvent(x, y) )
				{
					SDL_RenderClear(ui_renderer);
					DrawBG_Selec();
					DrawSetting();

					SDL_RenderPresent(ui_renderer);
					StartBar = false;
					RatingBar = false;
					SettingBar = true;
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
					for (int i = 0; i < 2; i++){
						if(BDI_setting[i].CheckEvent(x, y)){
							int n = BACKGROUND_PATH.size();
							BACKGROUND_PATH[n-5] = i + '1';
							SDL_DestroyTexture(bg_texture);
							bg_texture = IMG_LoadTexture( ui_renderer , BACKGROUND_PATH.c_str() );
							if (bg_texture == NULL) printf("Error: %s\n", SDL_GetError());
							SDL_RenderClear(ui_renderer);
							DrawSetting();
							SDL_RenderPresent(ui_renderer);
						}
						else if(BDM_setting[i].CheckEvent(x, y)){
							int n = MUSIC_BG_PATH.size();
							MUSIC_BG_PATH[n-5] = i + '1';
							Mix_FreeMusic(bg_music);
							bg_music = Mix_LoadMUS(MUSIC_BG_PATH.c_str());
							Mix_PlayMusic(bg_music, -1);
						}
						else if(color_setting[i].CheckEvent(x, y)){
							if (i == 0)
								for (int j = 0; j < 8; j++) SHAPE_COLOR[j] = SHAPE_COLOR_1[j];
							else
								for (int j = 0; j < 8; j++) SHAPE_COLOR[j] = SHAPE_COLOR_2[j];
							DrawSetting();
						}
					}
					if (row_input.Check(x, y)){
						SDL_StartTextInput();
						bool quit_input = false;
						while (SDL_PollEvent(&event) || !quit_input){
							if (event.type == SDL_MOUSEBUTTONDOWN){
								int tmp_x, tmp_y;
								SDL_GetMouseState(&tmp_x, &tmp_y);
								if (!row_input.Check(tmp_x, tmp_y)) {
									quit_input = true;
									break;
								}
							}
							else if(row_input.Input(event)){
								int tmp;
								if (row_input.GetText() != "")
									tmp = std::stoi(row_input.GetText());
								else tmp = 0;
								if (tmp > 0 && tmp < 91) PLAY_ROW = tmp;
								else PLAY_ROW = 10;
								DrawSetting();
								SDL_RenderPresent(ui_renderer);
							}
						}
						row_input.SetText(std::to_string(PLAY_ROW));
						DrawSetting();
						SDL_RenderPresent(ui_renderer);
						SDL_StopTextInput();
					}
					else if (line_input.Check(x, y)){
						SDL_StartTextInput();
						bool quit_input = false;
						while (SDL_PollEvent(&event) || !quit_input){
							if (event.type == SDL_MOUSEBUTTONDOWN){
								int tmp_x, tmp_y;
								SDL_GetMouseState(&tmp_x, &tmp_y);
								if (!line_input.Check(tmp_x, tmp_y)) {
									quit_input = true;
									break;
								}
							}
							else if(line_input.Input(event)){
								int tmp;
								if (line_input.GetText() != "")
									tmp = std::stoi(line_input.GetText());
								else tmp = 0;
								if (tmp > 0 && tmp < 41) PLAY_LINE = tmp;
								else PLAY_LINE = 20;
								DrawSetting();
								SDL_RenderPresent(ui_renderer);
							}
						}
						line_input.SetText(std::to_string(PLAY_LINE));
						DrawSetting();
						SDL_RenderPresent(ui_renderer);
						SDL_StopTextInput();
					}
					else if (delete_all_user.CheckEvent(x, y)){
						for (int i = 0; i < 9; i++){
							USER[i].name = "";
							remove(USER[i].data_path.c_str());
							USER[i].data_path = "";
							USER[i].best_score = 0;
							USER[i].score = 0;
							USER[i].size = 0;
							data_button[i].update("");
						}
					}
					for (int i = 0; i < 5; i++){
						if (press_change[i].Check(x, y)){
							bool quit_change = false;
							while (SDL_PollEvent(&event) || !quit_change){
								if (event.type == SDL_KEYDOWN){
									if(press_change[i].Change(event)){
									quit_change = true;
									break;
									}
								}
							}
							LEFT_PRESS = press_change[0].GetKey();
							RIGHT_PRESS = press_change[1].GetKey();
							DOWN_PRESS = press_change[2].GetKey();
							CHANGE_PRESS = press_change[3].GetKey();
							PAUSE_PRESS = press_change[4].GetKey();
							DrawSetting();
							SDL_RenderPresent(ui_renderer);
						}
					}
				}
				if (quit) break;
			};
		};
	};
	SDL_DestroyTexture(bg_texture);
	SDL_DestroyRenderer(ui_renderer);
	SDL_DestroyWindow(ui);

	//gaming window
	if(start_game){
		MainWindow *mainwindow = new MainWindow(PLAY_ROW, PLAY_LINE, USER[id]);
		if (!mainwindow->WindowInit()) printf("main window init error!");
		else printf("main window init sucess!");
		mainwindow->GameStart();
		USER[id] = mainwindow->getUser();
		mainwindow->Close();
		delete mainwindow;
		goto init_contract;
	}
	//save user data
	SaveUser();
	SaveSetting();
	//close SDL
	Mix_FreeMusic(bg_music);
	Mix_CloseAudio();
	TTF_CloseFont(FONT);
	Mix_Quit();
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}