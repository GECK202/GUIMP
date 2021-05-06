/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tree.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabraham <vabraham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 20:52:08 by vkaron            #+#    #+#             */
/*   Updated: 2020/02/18 21:23:01 by vabraham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"

t_node	*create_node(t_node *parent, void *data)
{
	t_node *node;

	node = (t_node*)ft_memalloc(sizeof(t_node));
	if (node) {
		node->pnt = parent;
		node->nxt = NULL;
		node->prv = NULL;
		node->chd = NULL;
		node->data = data;
	}
	return (node);
}

t_node	*add_node(t_node *pnt, void *data)
{
	t_node *node;
	t_node *prv;

	node = create_node(pnt, data);
	if (node)
	{
		if (!(pnt->chd))
			pnt->chd = node;
		else
		{
			prv = pnt->chd;
			if (prv->nxt)
				while(prv->nxt)
					prv = prv->nxt;
			node->prv = prv;
			prv->nxt = node;
		}
	}
	return (node);
}

void	remove_node(t_node *node, void (*del_fun)(void *))
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
		{
			node->chd = node->nxt;
		}
		if (node->data)
			del_fun(node->data);
		free(node);	
	}
}

