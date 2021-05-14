/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaron <vkaron@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 14:24:16 by vkaron            #+#    #+#             */
/*   Updated: 2020/09/15 11:09:21 by vkaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"
#include <stdio.h>

static void delete_window(t_wnd *wnd)
{
	if (wnd->img)
	{
		SDL_FreeSurface(wnd->img);
		wnd->img = NULL;
	}
	if(wnd->win)
	{
		SDL_DestroyWindow(wnd->win);
		wnd->win = NULL;
	}
}


static void destroy_window(void *wnd)
{
	if (wnd)
	{
		delete_window(wnd);
		free(wnd);
	}
}

static t_wnd *create_window(t_wnd_opt *opt)
{
	t_wnd		*wnd;
	SDL_Surface	*srf;

	if (wnd = (t_wnd*)ft_memalloc(sizeof(t_wnd)))
	{
		if (!(wnd->win = SDL_CreateWindow(opt->title, opt->size.x, opt->size.y,
			opt->size.w, opt->size.h, opt->flags)))
		{
			free(wnd);
        	return (NULL);
    	}
    	wnd->id = SDL_GetWindowID(wnd->win);
    	srf = SDL_GetWindowSurface(wnd->win);
    	wnd->color = SDL_MapRGBA(srf->format, 255, 255, 255, 255);
    	wnd->is_exist = SDL_TRUE;
    	wnd->img = NULL;
    	return (wnd);
    }
    return (NULL);
}

t_window *new_window(t_gui *mng, t_wnd_opt *opt)
{
	t_wnd		*wnd;
	t_node		*node;

	if (wnd = create_window(opt))
	{
		if (!(node = add_node(&(mng->wdws), wnd, destroy_window)))
		{
			destroy_window(wnd);
			return (NULL);
		}
		return (node);
    }
    return NULL;
}

int set_window_image(t_window *window, char *filename)
{
	t_wnd		*wnd;
	
	if (window)
		if ((wnd = (t_wnd*)(window->data)))
			if ((wnd->img = IMG_Load(filename)))
				return (GUI_OK);
	return (GUI_ERROR);
}

void redraw_window(t_window *window)
{
	SDL_Surface	*fon;
	SDL_Surface	*srf;
	int 		width;
    int			height;
	t_wnd		*wnd;
	
	wnd = (t_wnd*)(window->data);
    SDL_GetWindowSize(wnd->win, &width, &height);
    srf = SDL_GetWindowSurface(wnd->win);
    fon = SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0);
    SDL_FillRect(fon, NULL, wnd->color);
    SDL_BlitSurface(fon, NULL, srf, NULL);
    SDL_BlitSurface(wnd->img, NULL, srf, NULL);
    SDL_FreeSurface(fon);
    SDL_UpdateWindowSurface(wnd->win);
}

void	remove_window(t_window *window)
{
	remove_node(window);
}





