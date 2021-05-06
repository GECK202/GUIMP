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

# define GUI_ERROR 1
# define GUI_OK 0



typedef struct		s_node
{
	struct s_node	*pnt;
	struct s_node	*chd;
	struct s_node	*nxt;
	struct s_node	*prv;
	void			*data;
}					t_node;

typedef t_node		t_window;

typedef struct		s_rect
{
	int 			x;
	int 			y;
	int 			w;
	int 			h;
}					t_rect;

typedef struct 		s_gui
{
	t_node			wdws;
}					t_gui;

typedef struct		s_wnd_opt
{
	const char		*title;
	t_rect			size;
	Uint32			flags;
}					t_wnd_opt;

typedef struct		s_wnd
{
	SDL_Window		*win;
	Uint32			id;
	SDL_Surface		*img;
	Uint32			color;
	SDL_bool		is_exist;
}					t_wnd;

int					start_gui();
void				delete_window(t_wnd *wnd);
void				destroy_window(void *wnd);
t_node				*create_node(t_node *parent, void *data);
t_node				*add_node(t_node *pnt, void *data);
void				remove_node(t_node *node, void (*del_fun)(void *));
t_window			*new_window(t_gui *mng, t_wnd_opt *opt);
int					set_window_image(t_window *window, char *filename);
void				redraw_window(t_window *window);
void				remove_window(t_window *window);

#endif
