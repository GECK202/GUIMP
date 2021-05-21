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

static void delete_widget(t_wdt *wdt)
{
	if (wdt->img)
	{
		SDL_FreeSurface(wdt->img);
		wdt->img = NULL;
	}
	if (wdt->srf)
	{
		SDL_FreeSurface(wdt->srf);
		wdt->img = NULL;
	}
	if (wdt->title)
	{
		free(wdt->title);
	}
	//wdt->draw_func = NULL;
}


static void destroy_widget(void *wdt)
{
	if (wdt)
	{
		delete_widget(wdt);
		free(wdt);
	}
}

static t_wdt *create_widget(t_wdt_opt *opt)
{
	t_wdt		*wdt;
	SDL_Surface	*srf;

	if ((wdt = (t_wdt*)ft_memalloc(sizeof(t_wdt))))
	{
		if ((wdt->srf = SDL_CreateRGBSurface(0, opt->size.w, opt->size.h, 32, 0, 0, 0, 0)))
		{
			wdt->size = opt->size;
			wdt->color = opt->color;
			wdt->title = opt->title;
			wdt->win_srf = opt->win_srf;
			wdt->img = NULL;
			return (wdt);
		}
		free(wdt);
	}
	return (NULL);
}

static		void set_root_opt(t_wdt_opt	*opt, SDL_Window *win)
{
	int			width;
	int			height;	
	
	opt->title = NULL;
	opt->color = 0xffff0000;
	opt->size.x = 30;
	opt->size.y = 30;
	SDL_GetWindowSize(win, &width, &height);
	opt->size.w = width - 60;
	opt->size.h = height - 60;
	opt->g_size = opt->size;
	opt->win_srf = SDL_GetWindowSurface(win);
}

t_widget	*new_root(t_window *window)
{
	t_wnd		*wnd;
	t_wdt		*root;
	t_node		*node;
	t_wdt_opt	opt;


	if (window && window->data)
	{
		
		wnd = (t_wnd*)(window->data);
		set_root_opt(&opt, wnd->win);
		if ((root = create_widget(&opt)))
		{
			ft_putstr("START ROOT OK!\n");
			if ((node = add_node(window, root, destroy_widget)))
			{
				return (node);
			}
			destroy_widget(root);
		}
	}
	return (NULL);
}

t_widget	*new_widget(t_widget *prnt, t_wdt_opt *opt)
{
	t_wdt		*wdt;
	t_wdt		*prn;
	t_node		*node;
	
	if (prnt)
	{
		prn = (t_wdt*)(prnt->data);
		opt->g_size = prn->g_size;
		opt->win_srf = prn->win_srf;
		if ((wdt = create_widget(opt)))
		{	
			if ((node = add_node(prnt, wdt, destroy_widget)))
				return (node);
			destroy_widget(wdt);
		}
	}
	return (NULL);
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

void redraw_widget(t_node *widget, void *data)
{
	SDL_Surface	*fon;
	t_rect		trans;
	t_wdt		*wdt;
	int			*n;
	
	n = (int*)data;
	wdt = (t_wdt*)((t_widget*)(widget)->data);
	if (wdt->srf->w < wdt->size.w || wdt->srf->h < wdt->size.h)
	{
		SDL_FreeSurface(wdt->srf);
		if (!(wdt->srf = SDL_CreateRGBSurface(0, wdt->size.w, wdt->size.h, 32, 0, 0, 0, 0)))
		{
			SDL_Log("ERROR UPDATE WIDGET SURFASE!!!!");
			exit(-1);
		}
	}
	fon = SDL_CreateRGBSurface(0, wdt->size.w, wdt->size.h, 32, 0, 0, 0, 0);
	SDL_FillRect(fon, NULL, wdt->color);
	SDL_BlitSurface(fon, NULL, wdt->srf, NULL);
	SDL_BlitSurface(wdt->img, NULL, wdt->srf, NULL);
	SDL_FreeSurface(fon);
	SDL_BlitSurface(wdt->srf, (SDL_Rect*)&(wdt->g_size), wdt->win_srf, (SDL_Rect*)&(wdt->g_size));
}

void	update_root(t_window *window)
{
	t_wnd	*wnd;
	t_wdt	*root;
	SDL_Surface	*s;
	int		width;
	int		height;	

	wnd = (t_wnd*)(window->data);
	root = (t_wdt*)(wnd->root->data);
	s = SDL_GetWindowSurface(wnd->win);
	root->size.w = s->w - 60;
	root->size.h = s->h - 60;
	root->g_size = root->size;
	root->win_srf = SDL_GetWindowSurface(wnd->win);
	act_node(wnd->root, NULL, redraw_widget);
}

void	update_widget(t_widget *widget)
{
	act_node(widget, NULL, redraw_widget);
}

void	remove_widget(t_widget *widget)
{
	remove_node(widget);
}

