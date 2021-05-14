/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_msg_y.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaron <vkaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 20:52:08 by vkaron            #+#    #+#             */
/*   Updated: 2020/02/18 21:23:01 by vkaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"

int	msg_yesno(t_wnd *wnd, const char *title, const char *msg)
{
	const SDL_MessageBoxButtonData	buttons[] = {{0, IDYES, "Да"},
	{0, IDNO, "Нет"}};
	const SDL_MessageBoxData		messageboxdata = {0, wnd->win, title, msg,
	SDL_arraysize(buttons), buttons, NULL};
	int								buttonid;

	if (SDL_ShowMessageBox(&messageboxdata, &buttonid) < 0)
		return (0);
	return (buttonid);
}

int	msg_yesnocancel(t_wnd *wnd, const char *title, const char *msg)
{
	const SDL_MessageBoxButtonData	buttons[] = {{0, IDYES, "Да"},
	{0, IDNO, "Нет"}, {0, IDCANCEL, "Отмена"}};
	const SDL_MessageBoxData		messageboxdata = {0, wnd->win, title, msg,
	SDL_arraysize(buttons), buttons, NULL};
	int								buttonid;

	if (SDL_ShowMessageBox(&messageboxdata, &buttonid) < 0)
		return (0);
	return (buttonid);
}


