#include <SDL2/SDL_ttf.h>
#include "constant.cpp"
#include "Shape.cpp"
#include "MainWindow.cpp"

extern std::string USER_DATA_PATH;
extern std::string FONT_PATH;
extern User USER[9];
extern TTF_Font* FONT;

int main( int, char ** ){
	bool sucess = true;
	if ( SDL_Init( SDL_INIT_VIDEO ) < 0 ) sucess = false;
    if ( !( IMG_Init( IMG_INIT_PNG ) & IMG_INIT_PNG ) ) sucess = false;
	if ( TTF_Init() < 0 ) sucess = false;
	std::printf("SDL_Init: %d\n", sucess);
	FONT = TTF_OpenFont(FONT_PATH.c_str(), 24);


	SDL_RWops* user_data_file = SDL_RWFromFile( "data/user_data.dat", "r+b" );
	SDL_RWread(user_data_file, &USER, sizeof(User),9);
	SDL_RWclose( user_data_file );

	int id = 0;

	MainWindow mainwindow(10, 20, USER[id]);
	if (!mainwindow.WindowInit()) printf("main window init error!");
	else printf("main window init sucess!");
	mainwindow.GameStart();
	USER[id] = mainwindow.getUser();
	mainwindow.Close();

	user_data_file = SDL_RWFromFile( "data/user_data.dat", "r+b" );
	SDL_RWwrite(user_data_file, &USER, sizeof(User),9);
	SDL_RWclose( user_data_file );


	exit:;
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}