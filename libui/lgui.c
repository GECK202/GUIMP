/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lgui.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaron <vkaron@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 14:24:16 by vkaron            #+#    #+#             */
/*   Updated: 2020/09/15 11:09:21 by vkaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"
#include <stdio.h>

//t_wnd *wnd = NULL;
//t_wnd *wnd2 = NULL;

t_window *wnd = NULL;
t_window *wnd2 = NULL;

//t_gui gui;

void PrintEvent(const SDL_Event * event)
{
    if (event->type == SDL_WINDOWEVENT) {
        switch (event->window.event) {
        case SDL_WINDOWEVENT_SHOWN:
            SDL_Log("%d Window %d shown",SDL_WINDOWEVENT_SHOWN, event->window.windowID);
            break;
        case SDL_WINDOWEVENT_HIDDEN:
            SDL_Log("%d Window %d hidden",SDL_WINDOWEVENT_HIDDEN, event->window.windowID);
            break;
        case SDL_WINDOWEVENT_EXPOSED:
            SDL_Log("%d Window %d exposed",SDL_WINDOWEVENT_EXPOSED, event->window.windowID);
            break;
        case SDL_WINDOWEVENT_MOVED:
            SDL_Log("%d Window %d moved to %d,%d", SDL_WINDOWEVENT_MOVED,
                    event->window.windowID, event->window.data1,
                    event->window.data2);
            break;
        case SDL_WINDOWEVENT_RESIZED:
            SDL_Log("%d Window %d resized to %dx%d", SDL_WINDOWEVENT_RESIZED,
                    event->window.windowID, event->window.data1,
                    event->window.data2);
            break;
        case SDL_WINDOWEVENT_SIZE_CHANGED:
            SDL_Log("%d Window %d size changed to %dx%d",SDL_WINDOWEVENT_SIZE_CHANGED,
                    event->window.windowID, event->window.data1,
                    event->window.data2);
            break;
        case SDL_WINDOWEVENT_MINIMIZED:
            SDL_Log("%d Window %d minimized", SDL_WINDOWEVENT_MINIMIZED, event->window.windowID);
            break;
        case SDL_WINDOWEVENT_MAXIMIZED:
            SDL_Log("%d Window %d maximized",SDL_WINDOWEVENT_MAXIMIZED, event->window.windowID);
            break;
        case SDL_WINDOWEVENT_RESTORED:
            SDL_Log("%d Window %d restored",SDL_WINDOWEVENT_RESTORED, event->window.windowID);
            break;
        case SDL_WINDOWEVENT_ENTER:
            SDL_Log("%d Mouse entered window %d", SDL_WINDOWEVENT_ENTER,
                    event->window.windowID);
            break;
        case SDL_WINDOWEVENT_LEAVE:
            SDL_Log("%d Mouse left window %d",SDL_WINDOWEVENT_LEAVE, event->window.windowID);
            break;
        case SDL_WINDOWEVENT_FOCUS_GAINED:
            SDL_Log("%d Window %d gained keyboard focus", SDL_WINDOWEVENT_FOCUS_GAINED,
                    event->window.windowID);
            break;
        case SDL_WINDOWEVENT_FOCUS_LOST:
            SDL_Log("%d Window %d lost keyboard focus", SDL_WINDOWEVENT_FOCUS_LOST,
                    event->window.windowID);
            break;
        case SDL_WINDOWEVENT_CLOSE:
            SDL_Log("%d Window %d closed",SDL_WINDOWEVENT_CLOSE, event->window.windowID);
            break;
#if SDL_VERSION_ATLEAST(2, 0, 5)
        case SDL_WINDOWEVENT_TAKE_FOCUS:
            SDL_Log("%d Window %d is offered a focus",SDL_WINDOWEVENT_TAKE_FOCUS, event->window.windowID);
            break;
        case SDL_WINDOWEVENT_HIT_TEST:
            SDL_Log("%d Window %d has a special hit test",SDL_WINDOWEVENT_HIT_TEST, event->window.windowID);
            break;
#endif
        default:
            SDL_Log("Window %d got unknown event %d",
                    event->window.windowID, event->window.event);
            break;
        }
    }
}

t_gui *init() {
    t_gui *gui;

    if(!(gui = (t_gui*)ft_memalloc(sizeof(t_gui))))
    	return (NULL);
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
    	free(gui);
    	SDL_Quit();
    	IMG_Quit();
        return (NULL);
    }
	gui->opt.title = "window default";
	gui->opt.size.x = SDL_WINDOWPOS_UNDEFINED;
	gui->opt.size.y = SDL_WINDOWPOS_UNDEFINED;
	gui->opt.size.w = SCREEN_WIDTH;
	gui->opt.size.h = SCREEN_HEIGHT;
	gui->opt.flags = SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE;
	if (!(wnd = new_window(gui, &(gui->opt))))
	{
		free(gui);
		SDL_Quit();
    	IMG_Quit();
		return (NULL);
	}
    return (gui);
}

int load()
{
	if (set_window_image(wnd, "res/im1.png") == GUI_ERROR)
		return (GUI_ERROR);
	//if (set_window_image(wnd2, "res/im2.jpeg") == GUI_ERROR)
	//	return (GUI_ERROR);
	return (GUI_OK);
}

void quit(t_gui *gui) {
		
	if (wnd)
	   	remove_window(wnd);
   	wnd = NULL;
    if (wnd2)
	    remove_window(wnd2);
    wnd2 = NULL;
    if (gui)
	    free(gui);
    SDL_Quit();
    IMG_Quit();
}


static int resizingEventWatcher(void *data, SDL_Event *event) {
	t_gui		*mng;
	t_window	*w;
	
    if (event->type == SDL_WINDOWEVENT && event->window.event == SDL_WINDOWEVENT_EXPOSED)
    {
		mng = (t_gui*)data;
		w = mng->wdws.chd;
		while(w)
		{
			if (w->data && (event->window.windowID == ((t_wnd*)(w->data))->id))
			//{
				//if (wnd)
				//{
					//if (w)
					//	w = w->nxt;
					//remove_window(wnd);
					//wnd = NULL;
					redraw_window(w);
				//}
				
			//}
			//if (w)
				w = w->nxt;
		}
    }
    return 0;
}

int show()
{
	const SDL_MessageBoxButtonData buttons[] = {
        { /* .flags, .buttonid, .text */        0, 0, "no" },
        { SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 1, "yes" },
        { SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, 2, "cancel" },
    };
    const SDL_MessageBoxColorScheme colorScheme = {
        { /* .colors (.r, .g, .b) */
            /* [SDL_MESSAGEBOX_COLOR_BACKGROUND] */
            { 255,   0,   0 },
            /* [SDL_MESSAGEBOX_COLOR_TEXT] */
            {   0, 255,   0 },
            /* [SDL_MESSAGEBOX_COLOR_BUTTON_BORDER] */
            { 255, 255,   0 },
            /* [SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND] */
            {   0,   0, 255 },
            /* [SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED] */
            { 255,   0, 255 }
        }
    };
    const SDL_MessageBoxData messageboxdata = {
        SDL_MESSAGEBOX_INFORMATION, /* .flags */
        ((t_wnd*)wnd->data)->win, /* .window */
        "example message box", /* .title */
        "select a button", /* .message */
        SDL_arraysize(buttons), /* .numbuttons */
        buttons, /* .buttons */
        NULL//&colorScheme /* .colorScheme */
    };
    int buttonid;
    if (SDL_ShowMessageBox(&messageboxdata, &buttonid) < 0) {
        SDL_Log("error displaying message box");
        return 1;
    }
    if (buttonid == -1) {
        SDL_Log("no selection");
    } else {
        SDL_Log("selection was %s", buttons[buttonid].text);
    }
    return 0;
}

int start_gui()
{
	t_gui *gui;
	
    if (!(gui = init()) || load() == GUI_ERROR)
        return (GUI_ERROR);
    SDL_AddEventWatch(resizingEventWatcher, &gui);
    //show();
    //SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING,
    //                     "Missing file",
    //                     "File is missing. Please reinstall the program.",
    //                     ((t_wnd*)wnd2->data)->win);
    SDL_Event windowEvent;
    while ( 1 )
    {
        if ( SDL_PollEvent( &windowEvent ) )
        {
        	PrintEvent(&windowEvent);
        	if (SDL_WINDOWEVENT_CLOSE == windowEvent.window.event)
        	{
        		t_wnd	*w1 = NULL;
        		t_wnd	*w2 = NULL;
        		if (wnd)
        			w1 = (t_wnd*)(wnd->data);
        		if (wnd2)
        			w2 = (t_wnd*)(wnd2->data);
        		
        		
        		if (wnd && windowEvent.window.windowID == w1->id)
        		{
        			remove_window(wnd);
        			//w1->is_exist = SDL_FALSE;
        			wnd = NULL;
        		}
        		else if (wnd2 && windowEvent.window.windowID == w2->id)
        		{
        			remove_window(wnd2);
        			//w2->is_exist = SDL_FALSE;
        			wnd2 = NULL;
        		}
        		else//if (!(w1->is_exist || w2->is_exist))
	        		break;
        	}
/*
            if ( SDL_WINDOWEVENT_SIZE_CHANGED == windowEvent.window.event)
            {
                if (windowEvent.window.windowID == 1)
                    cls_win(win);
                else if (windowEvent.window.windowID == 2)
                    cls_win(win2);
            }

            if ( SDL_WINDOWEVENT_RESIZED == windowEvent.window.event)
            {
                if (windowEvent.window.windowID == 1)
                    cls_win(win);
                else if (windowEvent.window.windowID == 2)
                    cls_win(win2);
            }
            //*/

        	if ( SDL_TEXTINPUT == windowEvent.text.type)
        	{
                printf("TEXT = [%s]\n", windowEvent.text.text);

        		SDL_Log("Window %d get text:[%04x][%04x]\n", windowEvent.window.windowID, windowEvent.text.text[0], windowEvent.text.text[1]);
        	}

        	if ( SDL_MOUSEBUTTONDOWN == windowEvent.button.type )
        	{
        		SDL_MouseButtonEvent m_ev;
        		m_ev = windowEvent.button;

                SDL_Log("Window %d mouse button %d down in coord[%d:%d] clicks=%d", windowEvent.window.windowID, m_ev.button, m_ev.x, m_ev.y, m_ev.clicks);
        	}


            if ( SDL_QUIT == windowEvent.type )
            {
                break;
            }
        }

    	SDL_Delay(10);
    }
    ft_putstr("6 Loop end\n");
    quit(gui);
    ft_putstr("7 All destroy\n");

    return (GUI_OK);
}

