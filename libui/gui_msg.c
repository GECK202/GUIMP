/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_msg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaron <vkaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 20:52:08 by vkaron            #+#    #+#             */
/*   Updated: 2020/02/18 21:23:01 by vkaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"

int	msg_abortretryignore(t_wnd *wnd, const char *title, const char *msg)
{
	const SDL_MessageBoxButtonData	buttons[] = {{0, IDABORT, "Прекратить"},
		{0, IDRETRY, "Повторить"}, {0, IDIGNORE, "Игнорировать"}};
	const SDL_MessageBoxData		messageboxdata = {0,
	wnd->win, title, msg, SDL_arraysize(buttons), buttons, NULL};
	int								buttonid;

	if (SDL_ShowMessageBox(&messageboxdata, &buttonid) < 0)
		return (0);
	return (buttonid);
}

int	msg_ok(t_wnd *wnd, const char *title, const char *msg)
{
	const SDL_MessageBoxButtonData	buttons[] = {{0, IDOK, "ОК"}};
	const SDL_MessageBoxData		messageboxdata = {0, wnd->win, title, msg,
	SDL_arraysize(buttons), buttons, NULL};
	int								buttonid;

	if (SDL_ShowMessageBox(&messageboxdata, &buttonid) < 0)
		return (0);
	return (buttonid);
}

int	msg_okcancel(t_wnd *wnd, const char *title, const char *msg)
{
	const SDL_MessageBoxButtonData	buttons[] = {{0, IDOK, "ОК"},
	{0, IDCANCEL, "Отмена"}};
	const SDL_MessageBoxData		messageboxdata = {0, wnd->win, title, msg,
	SDL_arraysize(buttons), buttons, NULL};
	int								buttonid;

	if (SDL_ShowMessageBox(&messageboxdata, &buttonid) < 0)
		return (0);
	return (buttonid);
}

int	msg_retrycancel(t_wnd *wnd, const char *title, const char *msg)
{
	const SDL_MessageBoxButtonData	buttons[] = {{0, IDRETRY, "Повторить"},
	{0, IDCANCEL, "Отмена"}};
	const SDL_MessageBoxData		messageboxdata = {0, wnd->win, title, msg,
	SDL_arraysize(buttons), buttons, NULL};
	int								buttonid;

	if (SDL_ShowMessageBox(&messageboxdata, &buttonid) < 0)
		return (0);
	return (buttonid);
}

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

int	gui_msg(t_wnd *wnd, int btn_schema,
	const char *title, const char *msg)
{
	if (btn_schema == MB_ABORTRETRYIGNORE)
		return (msg_abortretryignore(wnd, title, msg));
	else if (btn_schema == MB_OK)
		return (msg_ok(wnd, title, msg));
	else if (btn_schema == MB_OKCANCEL)
		return (msg_okcancel(wnd, title, msg));
	else if (btn_schema == MB_RETRYCANCEL)
		return (msg_retrycancel(wnd, title, msg));
	else if (btn_schema == MB_YESNO)
		return (msg_yesno(wnd, title, msg));
	else if (btn_schema == MB_YESNOCANCEL)
		return (msg_yesnocancel(wnd, title, msg));
	else
		return (0);
}
