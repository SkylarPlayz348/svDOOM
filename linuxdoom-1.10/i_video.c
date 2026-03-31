#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#include <stdarg.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>
#include <errno.h>
#include <signal.h>
#include <stdint.h>

#include <SDL3/SDL.h>

#include "doomstat.h"
#include "i_system.h"
#include "v_video.h"
#include "m_argv.h"
#include "d_main.h"

#include "doomdef.h"

SDL_Window *window;
SDL_Renderer *renderer;
SDL_Texture *framebuffer;
SDL_Color rgb_palette[256];
uint32_t rgba_buffer[SCREENWIDTH * SCREENHEIGHT];

void I_ShutdownGraphics(void)
{
}

//
// I_StartFrame
//
void I_StartFrame(void)
{
	// er?
}

void I_GetEvent(void)
{
}

//
// I_StartTic
//
void I_StartTic(void)
{
	SDL_Event e;
	event_t doom_event;
	while (SDL_PollEvent(&e))
	{
		switch (e.type)
		{
		case SDL_EVENT_QUIT:
			I_Quit();
			break;
		case SDL_EVENT_KEY_DOWN:
			doom_event.type = ev_keydown;
			doom_event.data1 = e.key.scancode;
			D_PostEvent(&doom_event);
			break;
		case SDL_EVENT_KEY_UP:
			doom_event.type = ev_keyup;
			doom_event.data1 = e.key.scancode;
			D_PostEvent(&doom_event);
			break;
		default:
			break;
		}
	}
}

//
// I_UpdateNoBlit
//
void I_UpdateNoBlit(void)
{
	// what is this?
}

//
// I_FinishUpdate
//
void I_FinishUpdate(void)
{
	for (int i = 0; i < SCREENWIDTH * SCREENHEIGHT; i++)
	{
		SDL_Color c = rgb_palette[screens[0][i]];
		rgba_buffer[i] = ((uint32_t)c.r << 24) | ((uint32_t)c.g << 16) | ((uint32_t)c.b << 8) | 0xff;
	}
	SDL_SetTextureScaleMode(framebuffer, SDL_SCALEMODE_NEAREST);
	SDL_UpdateTexture(framebuffer, NULL, rgba_buffer, SCREENWIDTH * sizeof(uint32_t));
	SDL_RenderClear(renderer);
	SDL_RenderTexture(renderer, framebuffer, NULL, NULL);
	SDL_RenderPresent(renderer);
}

//
// I_ReadScreen
//
void I_ReadScreen(byte *scr)
{
	memcpy(scr, screens[0], SCREENWIDTH * SCREENHEIGHT);
}

//
// I_SetPalette
//
void I_SetPalette(byte *palette)
{
	for (int i = 0; i < 256; i++)
	{
		rgb_palette[i].r = gammatable[usegamma][palette[i * 3 + 0]];
		rgb_palette[i].g = gammatable[usegamma][palette[i * 3 + 1]];
		rgb_palette[i].b = gammatable[usegamma][palette[i * 3 + 2]];
		rgb_palette[i].a = 255;
	}
}

void I_InitGraphics(void)
{
	static int firsttime = 1;

	if (!firsttime)
		return;
	firsttime = 0;

	signal(SIGINT, (void (*)(int))I_Quit);

	screens[0] = (unsigned char *)malloc(SCREENWIDTH * SCREENHEIGHT);

	SDL_CreateWindowAndRenderer("svDOOM", SCREENWIDTH, SCREENHEIGHT, SDL_WINDOW_MOUSE_GRABBED | SDL_WINDOW_KEYBOARD_GRABBED | SDL_WINDOW_FULLSCREEN, &window, &renderer);

	framebuffer = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, SCREENWIDTH, SCREENHEIGHT);
}
