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

t_node *new_window(t_gmng *mng, t_wnd_opt *wnd_opt)
{
	t_wnd		*wnd;
	t_node		*node;
	SDL_Window	*win;

	wnd = (t_wnd*)ft_memalloc(sizeof(t_wnd));
	if (wnd)
	{
		win = SDL_CreateWindow(title, wnd_opt->size.x, wnd_opt->size.y,
			wnd_opt->size.w, wnd_opt->size.h, wnd_opt->flags);
    	if (win)
    	{
        	wnd->ren = SDL_CreateRenderer(wnd->wnd, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    	}
    	else 
    	{
    		return NULL;
    	}
    }
}

void del_win(t_win *wnd)
{
	if (wnd)
	{
		if(wnd->wnd)
			SDL_DestroyWindow(wnd->wnd);
	}
}
