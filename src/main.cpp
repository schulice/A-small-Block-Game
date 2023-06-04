#include <stdio.h>
#include "MainWindow.cpp"

int main( int, char ** ){
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
	}
	MainWindow mainwindow(12, 24);
	mainwindow.WindowInit();
	mainwindow.GameStart();
	mainwindow.Close();

}