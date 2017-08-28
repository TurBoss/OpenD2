#include "Diablo2.hpp"
#include <assert.h>

///////////////////////////////////////////////////////
//
//	Diablo II (OpenD2) Window Management Code

static SDL_Window* gpWindow;

/*
 *	Creates a window
 */
static SDL_Window* D2Win_CreateWindow(D2GameConfigStrc* pConfig, OpenD2ConfigStrc* pOpenConfig)
{
	SDL_Window* pWin = nullptr;
	DWORD dwWindowFlags = 0;

	if (!pConfig->bWindowed)
	{
		dwWindowFlags |= SDL_WINDOW_FULLSCREEN;
	}
	if (pOpenConfig->bBorderless)
	{
		dwWindowFlags |= SDL_WINDOW_BORDERLESS;
	}
	if (pConfig->bOpenGL)
	{
		dwWindowFlags |= SDL_WINDOW_OPENGL;
	}

	pWin = SDL_CreateWindow("Diablo II", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, dwWindowFlags);

	return pWin;
}

/*
 *	Inits SDL and creates a window
 */
void D2Win_InitSDL(D2GameConfigStrc* pConfig, OpenD2ConfigStrc* pOpenConfig)
{
	SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO|SDL_INIT_EVENTS|SDL_INIT_TIMER);

	gpWindow = D2Win_CreateWindow(pConfig, pOpenConfig);

	assert(gpWindow);

	Render_Init(pConfig, pOpenConfig, gpWindow);
}

/*
 *	Shuts down SDL and destroys the window
 */
void D2Win_ShutdownSDL()
{
	Render_Shutdown();
	SDL_DestroyWindow(gpWindow);
	SDL_Quit();
}