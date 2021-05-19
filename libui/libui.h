/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libui.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaron <vkaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 17:12:02 by vkaron            #+#    #+#             */
/*   Updated: 2020/02/05 16:39:54 by vkaron           ###   ########.fr       */
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

# define SCREEN_WIDTH 640
# define SCREEN_HEIGHT 480

# define MB_ABORTRETRYIGNORE 1
# define MB_OK 2
# define MB_OKCANCEL 3
# define MB_RETRYCANCEL 4
# define MB_YESNO 5
# define MB_YESNOCANCEL 6

# define IDOK 1
# define IDCANCEL 2
# define IDABORT 3
# define IDRETRY 4
# define IDIGNORE 5
# define IDYES 6
# define IDNO 7


typedef void (*del_func)(void*);

typedef void (*draw_func)(void*);

typedef struct		s_node
{
	struct s_node	*pnt;
	struct s_node	*chd;
	struct s_node	*nxt;
	struct s_node	*prv;
	void			*data;
	del_func		del;
}					t_node;

typedef t_node		t_window;
typedef t_node		t_widget;

typedef struct		s_rect
{
	int 			x;
	int 			y;
	int 			w;
	int 			h;
}					t_rect;

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

typedef struct		s_wdt_opt
{
	char			*caption;
	t_rect			size;
	Uint32			flags;
}					t_wdt_opt;

typedef struct		s_fnt
{
	const char		*file;
	int				size;
}					t_fnt;

typedef struct		s_wdt
{
	SDL_Surface		*srf;
	SDL_Surface		*img;
	t_rect			size;
	draw_func		draw;
	char			*cap;
	t_fnt			*fnt;
}					t_wdt;

typedef struct 		s_gui
{
	t_node			wdws;
	t_wnd_opt		opt;
	t_wnd			fwnd;
	t_fnt			def_fnt;
}					t_gui;



int					start_gui();
//void				delete_window(t_wnd *wnd);
//void				destroy_window(void *wnd);
t_node				*create_node(t_node *parent, void *data, del_func del);
t_node				*add_node(t_node *pnt, void *data, del_func del);
void				remove_node(t_node *node);
void				act_node(t_node *node, void(*f)(void*));
t_window			*new_window(t_gui *mng, t_wnd_opt *opt);
int					set_window_image(t_window *window, char *filename);
void				redraw_window(t_window *window);
void				remove_window(t_window *window);
int					gui_msg(t_wnd *wnd, int btn_scheme, const char *title,
					const char *msg);
int					msg_yesno(t_wnd *wnd, const char *title, const char *msg);
int					msg_yesnocancel(t_wnd *wnd, const char *title, const char *msg);
#endif
