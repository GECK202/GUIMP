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

static t_node	*create_node(t_node_opt	*opt)
{
	t_node *node;

	node = (t_node*)ft_memalloc(sizeof(t_node));
	if (node) {
		node->pnt = opt->pnt;
		node->nxt = NULL;
		node->prv = NULL;
		node->chd = NULL;
		node->data = opt->data;
		node->del = opt->del;
		node->upd = opt->upd;
		node->drw = opt->drw;
		node->srf = opt->srf;
		node->type = opt->type;
		node->size = opt->size;
	}
	return (node);
}

t_node	*add_node(t_node_opt *opt)
{
	t_node *node;
	t_node *prv;

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
				while(prv->nxt)
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
		if (node->nxt)
			act_node(node->nxt, data, anf);
		if (node->chd)
			act_node(node->chd, data, anf);
	}
}
