/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libui.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaron <vkaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 17:12:02 by vkaron            #+#    #+#             */
/*   Updated: 2020/02/05 16:39:54 by vabraham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBUI_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include "libft.h"

# include <SDL.h>
# include <SDL_image.h>
# include <SDL_ttf.h>
# include <SDL_mixer.h>

typedef struct	s_rect
{
	int 		x;
	int 		y;
	int 		w;
	int 		h;
}				t_rect;

typedef struct 	s_gmng
{
	t_node		*root;
}				t_gmng;

typedef struct	s_wnd_opt
{
	const char	*title;
	t_rect		size;
	Uint32		flags;
}				t_wnd_opt;

typedef struct	s_wnd
{
	SDL_Window	*wnd;
	SDL_Sufface	*srf;
	SDL_Render	*ren;
	SDL_Texture	*txt;
	SDL_bool	is_enb;
}				t_wnd;

int start_gui();

#endif
