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
	//if (wnd->img)
	//{
	//	SDL_FreeSurface(wnd->img);
	//	wnd->img = NULL;
	//}
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

/*
static	int	add_root_wdt(t_window *window)
{
	t_wnd	*wnd;

	if (window && window->data)
	{
		
		wnd = (t_wnd*)(window->data);
		if (!(wnd->root))
		{
			if (!(wnd->root = new_root(window)))
				return (GUI_ERROR);
		}
		return (GUI_OK);
	}
	return (GUI_ERROR);
}
//*/

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
	int			width;
	int			height;	
	
	opt->title = NULL;
	opt->color = 0xffff0000;
	opt->size.x = 0;
	opt->size.y = 0;
//	opt->win_srf = SDL_GetWindowSurface(win);
//	opt->size.w = opt->win_srf->w - 60;
//	opt->size.h = opt->win_srf->h - 60;
//	opt->g_size = opt->size;
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
			ft_putstr("START ROOT OK!\n");
			if ((GUI_OK == set_wdt_node_opt(&n_opt, NULL, wnd, root)) && (node = add_node(&n_opt)))
			//if ((node = add_node(window, root, destroy_widget)))
			{
				SDL_Log("root\t\t = %p",node);
				return (node);
			}
			destroy_widget(root);
		}
	}
	return (NULL);
}

t_window *new_window(t_gui *mng, t_wnd_opt *opt)
{
	t_wnd		*wnd;
	t_node		*window;
	t_node_opt	n_opt;

	if ((wnd = create_window(opt)))
	{
		if ((GUI_OK == set_node_opt(&n_opt, &(mng->wdws), wnd)) && (window = add_node(&n_opt)))
		{
			if (!(add_root(window)))
			{
				remove_node(window);
				window = NULL;
			}
			SDL_Log("window->chd\t = %p", window->chd);
			return (window);
		}
		destroy_window(wnd);
	}
	return NULL;
}

//int set_window_image(t_window *window, char *filename)
//{
//	t_wnd		*wnd;
	
//	if (window)
//		if ((wnd = (t_wnd*)(window->data)))
//			if (!(wnd->img) && (wnd->img = IMG_Load(filename)))
//				return (GUI_OK);
//	return (GUI_ERROR);
//}

void redraw_window(t_window *window)
{
	//SDL_Surface	*fon;
	//SDL_Surface	*srf;
	//int			width;
	//int			height;
	//t_wnd		*wnd;
	
	//wnd = (t_wnd*)(window->data);
	//SDL_GetWindowSize(wnd->win, &width, &height);
	//srf = SDL_GetWindowSurface(wnd->win);
	//fon = SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0);
	//SDL_FillRect(fon, NULL, wnd->color);
	//SDL_BlitSurface(fon, NULL, srf, NULL);
	//SDL_BlitSurface(wnd->img, NULL, srf, NULL);
	//SDL_FreeSurface(fon);
	update_root(window);
	update_window(window);
}

void update_window(t_window *window)
{
	t_wnd		*wnd;
	
	wnd = (t_wnd*)(window->data);
	SDL_UpdateWindowSurface(wnd->win);
}

void	remove_window(t_window *window)
{
	remove_node(window);
}

