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

#include "libft.h"

t_node *create_node(t_node *parent, void *data)
{
	t_node *node;

	node = (t_node*)ft_memalloc(sizeof(t_node));
	if (node) {
		node->pnt = parent;
		node->nxt = NULL;
		node->chd = NULL;
		node->data = data;
	}
	return node;
}

int		add_child(t_node *node, void *data)
{
	t_node *chd;
	t_node *tmp;

	chd = create_node(node, data);
	if (chd)
	{
		tmp = node->next;
		if (tmp)
		{
			while(tmp->next)
				tmp = tmp->next;
		}
		tmp->next = chd;
	}
}
