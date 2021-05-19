/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_widget.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaron <vkaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 20:52:08 by vkaron            #+#    #+#             */
/*   Updated: 2020/02/18 21:23:01 by vkaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"

static void delete_widget(t_wtd *wdt)
{
	if (wdt->img)
	{
		SDL_FreeSurface(wdt->img);
		wdt->img = NULL;
	}
	if(wdt->srf)
	{
		SDL_FreeSurface(wdt->srf);
		wdt->img = NULL;
	}
	wdt->draw_func = NULL;
}


static void destroy_widget(void *wdt)
{
	if (wdt)
	{
		delete_widget(wdt);
		free(wdt);
	}
}

static t_wdt *create_window(t_wdt_opt *opt)
{
	t_wdt		*wdt;
	SDL_Surface	*srf;

	if ((wdt = (t_wdt*)ft_memalloc(sizeof(t_wdt))))
	{
		if ((wdt->srf = SDL_CreateRGBSurface(0, opt->size.w, opt->size.h, 32, 0, 0, 0, 0)))
		{
			wdt->size = opt->size;
			wdt->img = NULL;
			wdt->flags = 0;
			return (wnd);
		}
		free(wnd);
	}
	return (NULL);
}

t_widget    *new_widget(t_widget *prnt, t_wdt_opt *opt)
{
	t_wdt		*wdt;
	t_node		*node;

	if ((wdt = create_widget(opt)))
	{
		if ((node = add_node(prnt, wnd, destroy_widget)))
			return (node);
		destroy_window(wnd);
	}
	return NULL;
}

int set_widget_image(t_widget *widget, char *filename)
{
	t_wdt		*wdt;
	
	if (widget)
		if ((wdt = (t_wdt*)(widget->data)))
			if (!(wdt->img) && (wdt->img = IMG_Load(filename)))
				return (GUI_OK);
	return (GUI_ERROR);
}

void redraw_widget(t_window *window, t_widget *widget, t_rect area)
{
	SDL_Surface	*fon;
	SDL_Surface	*srf;
	t_rect		trans;
	t_wdt		*wdt;
	
	wdt = (t_wdt*)(widget->data);
	
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

