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

# define L_M_DOWN	0x00000001
# define L_M_UP		0x00000002
# define R_M_DOWN	0x00000004
# define R_M_UP		0x00000008
# define M_M_DOWN	0x00000010
# define M_M_UP		0x00000020
# define M_MOVE		0x00000040
# define M_M_SCROLL	0x00000080



typedef enum		e_n_type
{
	GUI_MNG,
	GUI_WND,
	GUI_WDT
}					t_n_type;

typedef void (*act_f)(void*);

//typedef void (*draw_func)(void*);

typedef struct		s_node
{
	struct s_node	*pnt;
	struct s_node	*chd;
	struct s_node	*nxt;
	struct s_node	*prv;
	void			*data;
	const char		*name;
	act_f			del;
	act_f			upd;
	act_f			drw;
	t_n_type		type;
	SDL_Surface		*srf;
	SDL_Rect		size;
	SDL_Rect		g_s;
	SDL_Rect		r_s;
	SDL_Rect		l_s;
	unsigned int	events;
}					t_node;

typedef struct		s_node_opt
{
	t_node			*pnt;
	void			*data;
	const char		*name;
	act_f			del;
	act_f			upd;
	act_f			drw;
	t_n_type		type;
	SDL_Surface		*srf;
	SDL_Rect		size;
}					t_node_opt;

typedef void (*act_node_fun)(t_node*, void*);
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
//	SDL_Surface		*img;
//	Uint32			color;
	SDL_bool		is_exist;
}					t_wnd;

typedef struct		s_wdt_opt
{
	char			*title;
//	SDL_Surface		*win_srf;
	unsigned int	color;
	t_rect			size;
//	t_rect			g_s;
}					t_wdt_opt;

typedef struct		s_fnt
{
	const char		*file;
	int				size;
//	TTF_Font		*font;
}					t_fnt;

typedef struct		s_wdt
{
	SDL_Surface		*srf;
	SDL_Surface		*img;
//	SDL_Surface		*win_srf;
	t_rect			size;
//	t_rect			g_s;
	//draw_func		draw;
	char			*title;
	//t_fnt			*font;
	unsigned int	color;
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

//t_node				*create_node(t_node *parent, void *data, del_func del);
t_node				*add_node(t_node_opt *opt);
//t_node				*add_node(t_node_opt *opt, t_node *pnt);
void				remove_node(t_node *node);
void				act_node(t_node *node, void *data, act_node_fun anf);
t_node				*find_event_node(t_node *node, t_node *cand, t_rect pos, unsigned int event);

t_window			*new_window(t_gui *mng, t_wnd_opt *opt);
int					set_window_image(t_window *window, char *filename);
void				redraw_window(t_window *window);
void				update_window(t_window *window);
void				remove_window(t_window *window);
void 				find_click(t_window *window, int x, int y);

t_widget			*new_widget(t_window *window, t_wdt_opt *opt, t_widget *prnt, const char *name);
t_widget			*new_root(t_window *window);

t_wdt				*create_widget(t_wdt_opt *opt);
int					set_widget_image(t_widget *widget, char *filename);
void				destroy_widget(void *wdt);
void				subscribe_widget(unsigned int event, t_widget *widget);
void				unsubscribe_widget(unsigned int event, t_widget *widget);

void				redraw_widget(t_node *widget, void *data);
void				remove_widget(t_widget *widget);
void				update_widget(t_widget *widget);
void				update_root(t_window *window);

int					set_wdt_node_opt(t_node_opt *opt, t_node *prnt, t_wnd *wnd, t_wdt *wdt);

int					gui_msg(t_wnd *wnd, int btn_scheme, const char *title,
					const char *msg);
int					msg_yesno(t_wnd *wnd, const char *title, const char *msg);
int					msg_yesnocancel(t_wnd *wnd, const char *title, const char *msg);
#endif
