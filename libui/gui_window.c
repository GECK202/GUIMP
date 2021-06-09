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
	if (wnd->win)
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

	if ((wnd = (t_wnd*)ft_memalloc(sizeof(t_wnd))))
	{
		if ((wnd->win = SDL_CreateWindow(opt->title, opt->size.x, opt->size.y,
			opt->size.w, opt->size.h, opt->flags)))
		{
			wnd->id = SDL_GetWindowID(wnd->win);
			wnd->is_exist = SDL_TRUE;
			return (wnd);
		}
		free(wnd);
	}
	return (NULL);
}

int		set_node_opt(t_node_opt *opt, t_node *prnt, t_wnd *wnd)
{
	opt->pnt = prnt;
	opt->data = wnd;
	opt->del = destroy_window;
	opt->upd = NULL;
	opt->drw = NULL;
	opt->type = GUI_WND;
	opt->srf = NULL;
	opt->size.x = 0;
	opt->size.y = 0;
	opt->size.h = 0;
	opt->size.w = 0;
	
	if (wnd && wnd->win)
	{
		opt->srf = SDL_GetWindowSurface(wnd->win);
		opt->size.w = opt->srf->w;
		opt->size.h = opt->srf->h;
		return (GUI_OK);
	}
	return (GUI_ERROR);
}

static void		set_root_opt(t_wdt_opt *opt, SDL_Window *win)
{	
	SDL_Surface *screen;

	opt->title = NULL;
	opt->color = 0xfff0f0f0;
	opt->size.x = 0;
	opt->size.y = 0;
	screen = SDL_GetWindowSurface(win);
	opt->size.w = screen->w;
	opt->size.h = screen->h;
}

static t_widget	*add_root(t_window *window)
{
	t_wnd		*wnd;
	t_wdt		*root;
	t_node		*node;
	t_wdt_opt	opt;
	t_node_opt	n_opt;

	if (window && window->data)
	{
		wnd = (t_wnd*)(window->data);
		set_root_opt(&opt, wnd->win);
		if ((root = create_widget(&opt)))
		{
			n_opt.name = "root";
			if ((GUI_OK == set_wdt_node_opt(&n_opt, window, wnd, root)) && (node = add_node(&n_opt)))
			{
				node->size = window->size;
				node->r_size = window->size;
				node->g_size = window->size;
				node->l_size = window->size;
				return (node);
			}
			destroy_widget(root);
		}
	}
	return (NULL);
}

int	set_window_image(t_window *window, char *filename)
{
	if (window && window->chd)
		return (set_widget_image(window->chd, filename));
	return (GUI_ERROR);

}

t_window *new_window(t_gui *mng, t_wnd_opt *opt)
{
	t_wnd		*wnd;
	t_node		*window;
	t_node_opt	n_opt;

	if ((wnd = create_window(opt)))
	{
		n_opt.name = opt->title;
		if ((GUI_OK == set_node_opt(&n_opt, &(mng->wdws), wnd)) && (window = add_node(&n_opt)))
		{
			window->srf = SDL_GetWindowSurface(wnd->win);
			if (!(add_root(window)))
			{
				remove_node(window);
				window = NULL;
			}
			return (window);
		}
		destroy_window(wnd);
	}
	return NULL;
}

void redraw_window(t_window *window)
{
	update_root(window);
	update_window(window);
}

void update_window(t_window *window)
{
	t_wnd *wnd;

	wnd = (t_wnd*)(window->data);
	//printf("update win %p\n", wnd->win);
	SDL_UpdateWindowSurface(wnd->win);
}

void	remove_window(t_window *window)
{
	remove_node(window);
}

