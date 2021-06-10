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
		wdt->srf = NULL;
	}
	if (wdt->title)
	{
		free(wdt->title);
	}
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
			wdt->img = NULL;
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
	if (wnd && wnd->win)
	{
		if (prnt && prnt->srf)
			opt->srf = prnt->srf;
		else
			opt->srf = SDL_GetWindowSurface(wnd->win);
		//opt->size.w = opt->srf->w;
		//opt->size.h = opt->srf->h;
		return (GUI_OK);
	}
	return (GUI_ERROR);
}


t_widget	*new_widget(t_window *window, t_wdt_opt *opt, t_widget *prnt, const char *name)
{
	t_wdt		*wdt;
	t_wdt		*prn;
	t_node		*widget;
	t_node_opt	n_opt;
	
	if (window && window->data && window->chd && window->chd->data)
	{
		if (!prnt)
			prnt = window->chd;
		prn = (t_wdt*)(prnt->data);
		if ((wdt = create_widget(opt)))
		{
			n_opt.name = name;
			n_opt.size = *((SDL_Rect*)(&opt->size));
			printf("size=[%d, %d, %d, %d]\n", n_opt.size.x, n_opt.size.y, n_opt.size.w, n_opt.size.h);
			if ((GUI_OK == set_wdt_node_opt(&n_opt, prnt, window->data, wdt)) && (widget = add_node(&n_opt)))
			{
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
			if (!(wdt->img) && (wdt->img = IMG_Load(filename)))
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

	n = (int*)data;
	if (widget->pnt && (widget->pnt->type != GUI_WND))
		widget->srf = widget->pnt->srf;
	
	wdt = (t_wdt*)((t_widget*)(widget)->data);
	if (widget->pnt->type == GUI_WDT)
		set_node_sizes(widget);
	/*
	if (wdt->srf->w < wdt->size.w || wdt->srf->h < wdt->size.h)
	{
		SDL_FreeSurface(wdt->srf);
		if (!(wdt->srf = SDL_CreateRGBSurface(0, widget->srf->w, widget->srf->h, 32, 0, 0, 0, 0)))
		{
			SDL_Log("ERROR UPDATE WIDGET SURFASE!!!!");
			exit(-1);
		}
	}
	//*/
	fon = SDL_CreateRGBSurface(0, widget->srf->w, widget->srf->h, 32, 0, 0, 0, 0);
	//printf("color = %x\n", wdt->color);
	//printf("wdt->surf = %p\n", widget->srf);
	SDL_FillRect(fon, NULL, wdt->color);
	printf("%s:\n", widget->name);
	printf("size=[%d, %d, %d, %d]\n", widget->size.x, widget->size.y, widget->size.w, widget->size.h);
	printf("g_s=[%d, %d, %d, %d]\n", widget->g_s.x, widget->g_s.y, widget->g_s.w, widget->g_s.h);
	printf("r_s=[%d, %d, %d, %d]\n", widget->r_s.x, widget->r_s.y, widget->r_s.w, widget->r_s.h);
	printf("l_s=[%d, %d, %d, %d]\n", widget->l_s.x, widget->l_s.y, widget->l_s.w, widget->l_s.h);
	SDL_BlitSurface(fon, &(widget->l_s), widget->srf, &(widget->r_s));
	//printf("wdt img = %p\n", wdt->img);
	if (wdt->img)
	{
		SDL_BlitSurface(wdt->img, NULL, widget->srf, NULL);
	}
}

void	subscribe_widget(unsigned int event, t_widget *widget, evn_node_fun evn_f)
{
	int	index;

	widget->events = widget->events | event;
	index = 0;
	while (event)
	{
		event = event >> 1;
		++index;
	}
	widget->evn_f[index] = evn_f;
}

void	unsubscribe_widget(unsigned int event, t_widget *widget)
{
	int	index;

	widget->events = widget->events & (~event);
	index = 0;
	while (event)
	{
		event = event >> 1;
		++index;
	}
	widget->evn_f[index] = NULL;
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
		if (root_widget && root_widget->srf)
			SDL_FreeSurface(root_widget->srf);
		root_widget->srf = SDL_GetWindowSurface(wnd->win);
		root_widget->size.w = root_widget->srf->w;
		root_widget->size.h = root_widget->srf->h;
		root_widget->g_s = root_widget->size;
		root_widget->r_s = root_widget->size;
		root_widget->l_s = root_widget->size;
		root = (t_wdt*)(root_widget->data);
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

