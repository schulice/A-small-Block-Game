#include "MainWindow.cpp"


int main(){
	bool sucess = true;
	if ( SDL_Init( SDL_INIT_VIDEO ) < 0 ) sucess = false;
    if ( !( IMG_Init( IMG_INIT_PNG ) & IMG_INIT_PNG ) ) sucess = false;
	if ( TTF_Init() < 0 ) sucess = false;
	SDL_Log("SDL_Init: %d\n", sucess);
	FONT = TTF_OpenFont(FONT_PATH.c_str(), 8);


	User user = {"", "", 0, 0, 0};
	MainWindow *w = new MainWindow(10, 20, user);
	w->WindowInit();
	w->GameStart();
	w->Close();

	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}