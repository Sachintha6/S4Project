#include <gtk/gtk.h>
#include <stdio.h>
#include <string.h>
#include <err.h>
#include "gui.h"
#include "../../libs/map/mapGraph.h"
#include "../../libs/map/list.h"

void on_menuitm_close_activate(GtkMenuItem *menuitem, app_widgets *app_wdgts)
{
    gtk_main_quit();
}

void on_window_main_destroy()
{
    printf("Close\n");
    gtk_main_quit();
}

void on_zoomIn_clicked(GtkToolButton *button, app_widgets *app_wdgts)
{
    if (app_wdgts->zoom <= 300)
    {
        app_wdgts->zoom += 10.0;
    }
    gtk_widget_queue_draw(GTK_WIDGET(app_wdgts->drawing_area));
}

void on_zoomOut_clicked(GtkToolButton *button, app_widgets *app_wdgts)
{
    if (app_wdgts->zoom >= 10.0)
    {
        app_wdgts->zoom -= 10.0;
    }
    
    gtk_widget_queue_draw(GTK_WIDGET(app_wdgts->drawing_area));
}

/*
void on_key_press (GtkWidget *widget, GdkEventKey *event, app_widgets *app_wdgts)
{
    printf("hvejhve\n");
    switch (event->keyval)
    {
        case 65451:
            if (app_wdgts->zoom <= 300)
            {
                app_wdgts->zoom += 10.0;
                gtk_widget_queue_draw(GTK_WIDGET(app_wdgts->drawing_area));
            }
        break;
        case 65453:
            if (app_wdgts->zoom >= 10)
            {
                app_wdgts->zoom -= 10.0;
                gtk_widget_queue_draw(GTK_WIDGET(app_wdgts->drawing_area));
            }
        break;
        default:
        break;
    }
}*/