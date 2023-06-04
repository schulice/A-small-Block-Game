#include <stdio.h>
#include <cstdio>
#include "MainWindow.cpp"

int main( int, char ** ){
	bool sucess = true;
	if ( SDL_Init( SDL_INIT_VIDEO ) < 0 ) sucess = false;
    if ( !( IMG_Init( IMG_INIT_PNG ) & IMG_INIT_PNG ) ) sucess = false;
	std::printf("SDL_Init: %d\n", sucess);
	MainWindow mainwindow(42, 42);
	if (!mainwindow.WindowInit()) printf("window init error!");
	else printf("window init sucess!");
	mainwindow.GameStart();
	mainwindow.Close();
	IMG_Quit();
	SDL_Quit();
}