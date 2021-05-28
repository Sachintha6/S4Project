#include <gtk/gtk.h>
#include <stdio.h>
#include <string.h>
#include <err.h>
#include "gui.h"
#include "../libs/map/mapGraph.h"
#include "../libs/map/list.h"

void on_menuitm_close_activate(GtkMenuItem *menuitem, app_widgets *app_wdgts)
{
    gtk_main_quit();
}

void on_window_main_destroy()
{
    gtk_main_quit();
}