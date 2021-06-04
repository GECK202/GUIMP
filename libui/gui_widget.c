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
	//if (wdt->img)
	//{
	//	SDL_FreeSurface(wdt->img);
	//	wdt->img = NULL;
	//}
	if (wdt->srf)
	{
		SDL_FreeSurface(wdt->srf);
		wdt->srf = NULL;
	}
	if (wdt->title)
	{
		free(wdt->title);
	}
	//wdt->draw_func = NULL;
}


void destroy_widget(void *wdt)
{
	if (wdt)
	{
		delete_widget(wdt);
		free(wdt);
	}
}

t_wdt *create_widget(t_wdt_opt *opt)
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
//			wdt->win_srf = opt->win_srf;
//			wdt->img = NULL;
			return (wdt);
		}
		free(wdt);
	}
	return (NULL);
}

int			set_wdt_node_opt(t_node_opt *opt, t_node *prnt, t_wnd *wnd, t_wdt *wdt)
{
	opt->pnt = prnt;
	opt->data = wdt;
	opt->del = destroy_widget;
	opt->upd = NULL;
	opt->drw = NULL;
	opt->type = GUI_WDT;
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


t_widget	*new_widget(t_window *window, t_wdt_opt *opt, t_widget *prnt)
{
	t_wdt		*wdt;
	t_wdt		*prn;
	t_node		*widget;
	t_node_opt	n_opt;
	
	if (window && window->data && window->chd && window->chd->data)
	{
		if (!prnt)
			prnt = window->chd;
		SDL_Log("new widget parent\t = %p", prnt);
		prn = (t_wdt*)(prnt->data);
//		opt->g_size.x = prn->g_size.x + opt->size.x;
//		opt->g_size.y = prn->g_size.y + opt->size.y;
//		opt->g_size.w = (int)(fmin(opt->size.w + opt->g_size.x, prn->g_size.w + prn->g_size.x)) - opt->g_size.x;
//		opt->g_size.h = (int)(fmin(opt->size.h + opt->g_size.y, prn->g_size.h + prn->g_size.y)) - opt->g_size.y;
//		opt->win_srf = prn->win_srf;
		if ((wdt = create_widget(opt)))
		{	
			if ((GUI_OK == set_wdt_node_opt(&n_opt, prnt, window->data, wdt)) && (widget = add_node(&n_opt)))
			{
				SDL_Log("widget\t\t = %p", widget);
				return (widget);
			}
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
//			if (!(wdt->img) && (wdt->img = IMG_Load(filename)))
				return (GUI_OK);
	return (GUI_ERROR);
}

void resize_widget(t_widget *widget, void *data)
{
	
	
}

void redraw_widget(t_node *widget, void *data)
{
	SDL_Surface	*fon;
	t_rect		trans;
	t_wdt		*wdt;
	int			*n;

	SDL_Log("redraw widget\t = %p", widget);	
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
//	SDL_BlitSurface(wdt->img, NULL, wdt->srf, NULL);
//	SDL_FreeSurface(fon);
//	SDL_BlitSurface(wdt->srf, NULL, wdt->win_srf, (SDL_Rect*)&(wdt->g_size));
}

void	update_root(t_window *window)
{
	t_wnd		*wnd;
	t_wdt		*root;
	t_widget	*root_widget;

	if (window && window->data && window->chd && window->chd->data)
	{
		wnd = (t_wnd*)(window->data);
		root_widget = window->chd;
		root = (t_wdt*)(root_widget->data);
//		root->win_srf = SDL_GetWindowSurface(wnd->win);
//		root->size.w = root->win_srf->w - 60;
//		root->size.h = root->win_srf->h - 60;
//		root->g_size = root->size;
		act_node(root_widget, NULL, redraw_widget);
	}
}

void	update_widget(t_widget *widget)
{
	act_node(widget, NULL, redraw_widget);
}

void	remove_widget(t_widget *widget)
{
	remove_node(widget);
}

