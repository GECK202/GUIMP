/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_node.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaron <vkaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 20:52:08 by vkaron            #+#    #+#             */
/*   Updated: 2020/02/18 21:23:01 by vkaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"

static int	min_i(int v1, int v2)
{
	if (v1 < v2)
		return (v1);
	return (v2);
}

static int	max_i(int v1, int v2)
{
	if (v1 > v2)
		return (v1);
	return (v2);
}

static void	set_node_sizes(t_node *node)
{
	if (node->type == GUI_WDT)
	{
		node->g_s.x = node->size.x + node->pnt->g_s.x;
		node->g_s.y = node->size.y + node->pnt->g_s.y;
		node->g_s.w = node->size.w;
		node->g_s.h = node->size.h;
		node->r_s.x = max_i(node->g_s.x, node->pnt->r_s.x);
		node->r_s.y = max_i(node->g_s.y, node->pnt->r_s.y);
		node->r_s.w = max_i(0, min_i((node->g_s.x + node->g_s.w),
					(node->pnt->r_s.x + node->pnt->r_s.w)) - node->r_s.x);
		node->r_s.h = max_i(0, min_i((node->g_s.y + node->g_s.h),
					(node->pnt->r_s.y + node->pnt->r_s.h)) - node->r_s.y);
		node->l_s.x = 0 - min_i(0, node->size.x);
		node->l_s.y = 0 - min_i(0, node->size.y);
		node->l_s.w = min_i((node->size.w - node->l_s.x), node->r_s.w);
		node->l_s.h = min_i((node->size.h - node->l_s.y), node->r_s.h);
	}
	else
	{
		node->g_s = node->size;
		node->r_s = node->size;
		node->l_s = node->size;
	}
}

static t_node	*create_node(t_node_opt	*opt)
{
	t_node	*node;

	node = (t_node *)ft_memalloc(sizeof(t_node));
	if (node)
	{
		node->pnt = opt->pnt;
		node->nxt = NULL;
		node->prv = NULL;
		node->chd = NULL;
		node->name = opt->name;
		node->data = opt->data;
		node->del = opt->del;
		node->upd = opt->upd;
		node->drw = opt->drw;
		node->srf = opt->srf;
		node->type = opt->type;
		node->size = opt->size;
		set_node_sizes(node);
	}
	return (node);
}

t_node	*add_node(t_node_opt *opt)
{
	t_node	*node;
	t_node	*prv;

	node = create_node(opt);
	if (node)
	{
		if (!(opt->pnt->chd))
		{
			opt->pnt->chd = node;
		}
		else
		{
			prv = opt->pnt->chd;
			if (prv->nxt)
				while (prv->nxt)
					prv = prv->nxt;
			node->prv = prv;
			prv->nxt = node;
		}
	}
	return (node);
}

void	remove_node(t_node *node)
{
	if (node)
	{
		if (node->prv)
		{
			node->prv->nxt = node->nxt;
			if (node->nxt)
				node->nxt->prv = node->prv;
		}	
		else
			node->chd = node->nxt;
		if (node->data)
			node->del(node->data);
		free(node);
	}
}

void	act_node(t_node *node, void *data, act_node_fun anf)
{
	if (node)
	{
		anf(node, data);
		if (node->chd)
			act_node(node->chd, data, anf);
		if (node->nxt)
			act_node(node->nxt, data, anf);
	}
}

t_node	*find_event_node(t_node *node, t_node *cand, t_rect pos,
			unsigned int event)
{
	if (node)
	{
		if (pos.x >= node->r_s.x
			&& pos.x <= node->r_s.x + node->r_s.w
			&& pos.y >= node->r_s.y
			&& pos.y <= node->r_s.y + node->r_s.h)
		{
			if (node->events & event)
				cand = node;
			if (node->chd)
				cand = find_event_node(node->chd, cand, pos, event);
			if (node->nxt)
				cand = find_event_node(cand->nxt, cand, pos, event);
		}
	}
	return (cand);
}
