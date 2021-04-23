/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaron <vkaron@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 14:24:16 by vkaron            #+#    #+#             */
/*   Updated: 2020/09/15 11:09:21 by vkaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "guimp.h"
/*
void	main_selector(t_game *game)
{
	double		*z_buffer;
	int			size;

	size = sizeof(double);
	game->z_buffer = 0;
	if (!(z_buffer = (double*)ft_memalloc(size * S_W * S_H)))
		return ;
	game->z_buffer = z_buffer;
	while (game->status > 0)
	{

		if (game->status == 1)
			sdl_cycle(game);
		//else if (game->status == 2)
		//	map_editor(game);
		//else if (game->status == 3)
		//	main_menu(game);
		else if (game->status == 4)
			game->status = 3;

	}
	if (z_buffer)
		free(z_buffer);
	game->z_buffer = 0;
}


void	def_icon(t_game *game, int shift_x, int shift_y)
{
	SDL_Surface		*icon;
	int				*icon_img;
	int				i;
	int				pixel;

	if (!(icon = SDL_CreateRGBSurfaceWithFormat(0, 64, 64, 32,
		SDL_PIXELFORMAT_BGRA32)))
		ft_exit("Memory was not allocated!");
	icon_img = (int *)icon->pixels;
	i = -1;
	while (++i < 64 * 64)
	{
		pixel = i % 64 + (shift_x * 65) + 1039 * (i / 64 + (shift_y * 65));
		if (game->data_img[pixel] == 0x980088)
			icon_img[i] = 0;
		else
			icon_img[i] = 0xFF000000 | game->data_img[pixel];
	}
	SDL_SetWindowIcon(game->win, icon);
	SDL_FreeSurface(icon);
}

void	set_cheat(t_game *game, char *av[])
{
	if (!ft_strcmp(av[1], "editor"))
	{
		game->status = 2;
		game->level_edit = ft_atoi(av[2]);
		if (game->level_edit > 99 || game->level_edit <= 0)
			game->level_edit = 1;
		game->cheat = 1;
	}
	if (!ft_strcmp(av[1], "cheat"))
	{
		game->status = 1;
		game->level.num = ft_atoi(av[2]);
		if (game->level.num > MAX_LEVEL || game->level.num <= 0)
			game->level.num = 1;
	}
}

int		main(void)//int ac, char *av[])
{
	
	t_game		*game;

	if (S_W < 640 || S_H < 480)
		ft_exit("Bad resolution! Use from 640x480 to 1200x800!");
	if (!check_res())
		exit(0);

	if (!(game = (t_game*)ft_memalloc(sizeof(t_game))))
		ft_exit("Memory was not allocated!");
	init_player(game);
	


	if (!init_sdl(game))
		return (free_init_sdl(game));
	game->status = 1;
	//def_icon(game, 3, 42);
	//if (ac == 3)
	//	set_cheat(game, av);
	main_selector(game);
	//close_sdl(game);
	//if (game)
	//	free(game);

	write(1, "HELLO WORD!\n", 12);
	return (0);
}
*/


//#include <iostream>

//#include <SDL2/SDL.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Window *win = NULL;
SDL_Surface *scr = NULL;
SDL_Surface *smile = NULL;
SDL_Window *win2 = NULL;
SDL_Surface *scr2 = NULL;
SDL_Surface *smile2 = NULL;
int win1_is_exist = 1;
int win2_is_exist = 1;

void PrintEvent(const SDL_Event * event)
{
    if (event->type == SDL_WINDOWEVENT) {
        switch (event->window.event) {
        case SDL_WINDOWEVENT_SHOWN:
            SDL_Log("Window %d shown", event->window.windowID);
            break;
        case SDL_WINDOWEVENT_HIDDEN:
            SDL_Log("Window %d hidden", event->window.windowID);
            break;
        case SDL_WINDOWEVENT_EXPOSED:
            SDL_Log("Window %d exposed", event->window.windowID);
            break;
        case SDL_WINDOWEVENT_MOVED:
            SDL_Log("Window %d moved to %d,%d",
                    event->window.windowID, event->window.data1,
                    event->window.data2);
            break;
        case SDL_WINDOWEVENT_RESIZED:
            SDL_Log("Window %d resized to %dx%d",
                    event->window.windowID, event->window.data1,
                    event->window.data2);
            break;
        case SDL_WINDOWEVENT_SIZE_CHANGED:
            SDL_Log("Window %d size changed to %dx%d",
                    event->window.windowID, event->window.data1,
                    event->window.data2);
            break;
        case SDL_WINDOWEVENT_MINIMIZED:
            SDL_Log("Window %d minimized", event->window.windowID);
            break;
        case SDL_WINDOWEVENT_MAXIMIZED:
            SDL_Log("Window %d maximized", event->window.windowID);
            break;
        case SDL_WINDOWEVENT_RESTORED:
            SDL_Log("Window %d restored", event->window.windowID);
            break;
        case SDL_WINDOWEVENT_ENTER:
            SDL_Log("Mouse entered window %d",
                    event->window.windowID);
            break;
        case SDL_WINDOWEVENT_LEAVE:
            SDL_Log("Mouse left window %d", event->window.windowID);
            break;
        case SDL_WINDOWEVENT_FOCUS_GAINED:
            SDL_Log("Window %d gained keyboard focus",
                    event->window.windowID);
            break;
        case SDL_WINDOWEVENT_FOCUS_LOST:
            SDL_Log("Window %d lost keyboard focus",
                    event->window.windowID);
            break;
        case SDL_WINDOWEVENT_CLOSE:
            SDL_Log("Window %d closed", event->window.windowID);
            break;
#if SDL_VERSION_ATLEAST(2, 0, 5)
        case SDL_WINDOWEVENT_TAKE_FOCUS:
            SDL_Log("Window %d is offered a focus", event->window.windowID);
            break;
        case SDL_WINDOWEVENT_HIT_TEST:
            SDL_Log("Window %d has a special hit test", event->window.windowID);
            break;
#endif
        default:
            SDL_Log("Window %d got unknown event %d",
                    event->window.windowID, event->window.event);
            break;
        }
    }
}

int init() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        return 1;
    }
    
    win = SDL_CreateWindow("win1", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (win == NULL) {
        return 1;
    }
    
    win2 = SDL_CreateWindow("win2", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (win2 == NULL) {
        return 1;
    }
    
    scr = SDL_GetWindowSurface(win);
    scr2 = SDL_GetWindowSurface(win2);
    
    return 0;
}

int load() {
    smile = IMG_Load("res/im1.png");
    smile2 = IMG_Load("res/im2.jpeg");
    if (smile == NULL) {
        return 1;
    }
    if (smile2 == NULL) {
        return 1;
    }
    return 0;
}

void quit() {
    SDL_FreeSurface(smile);
    SDL_FreeSurface(smile2);
    smile = NULL;
    smile2 = NULL;
    
    if (win1_is_exist)
	    SDL_DestroyWindow(win);
    
    if (win2_is_exist)
	    SDL_DestroyWindow(win2);
    
    SDL_Quit();
}

void cls_win(SDL_Window *window)
{
    /* Declaring the surface. */
    SDL_Surface *s;

    int width;
    int height;

    Uint32 ID;

    SDL_Surface *win_scr = SDL_GetWindowSurface(window);

    SDL_GetWindowSize(window, &width, &height);

    /* Creating the surface. */
    s = SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0);

    /* Filling the surface with red color. */
    SDL_FillRect(s, NULL, SDL_MapRGB(s->format, 255, 0, 0));

    SDL_BlitSurface(s, NULL, win_scr, NULL);

    ID = SDL_GetWindowID(window);

    if (ID == 1)
    {
        SDL_BlitSurface(smile, NULL, scr, NULL);
        SDL_UpdateWindowSurface(win);
    }
    else if (ID == 2)
    {
        SDL_BlitSurface(smile2, NULL, scr2, NULL);
        SDL_UpdateWindowSurface(win2);
    }

}

int main (void) {//int argc, char ** args) {
    if (init() == 1) {
        return 1;
    }
    write(1,"1\n",2);
    if (load() == 1) {
        return 1;
    }
    write(1,"2\n",2);
    SDL_BlitSurface(smile, NULL, scr, NULL);
    SDL_BlitSurface(smile2, NULL, scr2, NULL);
    write(1,"3\n",2);
    SDL_UpdateWindowSurface(win);
    SDL_UpdateWindowSurface(win2);
    write(1,"4\n",2);
    SDL_Delay(2000);
    SDL_Event windowEvent;
    
    while ( 1 )
    {
        if ( SDL_PollEvent( &windowEvent ) )
        {
        	PrintEvent(&windowEvent);
        	if (SDL_WINDOWEVENT_CLOSE == windowEvent.window.event)
        	{
        		if (windowEvent.window.windowID == 1)
        		{
        			SDL_DestroyWindow(win);
        			win1_is_exist = 0;
        		}
        		if (windowEvent.window.windowID == 2)
        		{
        			SDL_DestroyWindow(win2);
        			win2_is_exist = 0;
        		}
        		if (win1_is_exist == 0 && win2_is_exist == 0)
	        		break;
        	}

            //if ( SDL_WINDOWEVENT_SIZE_CHANGED == windowEvent.window.event)
            //{
            //    if (windowEvent.window.windowID == 1)
            //        cls_win(win);
            //    else if (windowEvent.window.windowID == 2)
            //        cls_win(win2);
            //}

        	if ( SDL_TEXTINPUT == windowEvent.text.type)
        	{
        		SDL_Log("Window %d get text:[%s]\n", windowEvent.window.windowID, windowEvent.text.text);
        	}

        	if ( SDL_MOUSEBUTTONDOWN == windowEvent.button.type )
        	{
        		SDL_MouseButtonEvent m_ev;
        		m_ev = windowEvent.button;

        		SDL_Log("Window %d mouse button %d down in coord[%d:%d] clicks=%d", windowEvent.window.windowID, m_ev.button, m_ev.x, m_ev.y, m_ev.clicks);
        	}
            if ( SDL_QUIT == windowEvent.type )
            {
                break;
            }
        }
    }
    write(1,"5\n",2);
    quit();
    write(1,"6\n",2);
    return 0;
}