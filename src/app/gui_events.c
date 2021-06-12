#include <gtk/gtk.h>
#include <stdio.h>
#include <string.h>
#include <err.h>
#include "gui.h"
#include "../../libs/map/mapGraph.h"
#include "../../libs/map/list.h"
#include "../ride/ride.h"

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

void on_search_clicked(GtkToolButton *button, app_widgets *app_wdgts)
{
    app_wdgts->ride = shortest_ride(app_wdgts->map->g, 26, 8);
    printf("\n\n-- RIDE GRAPH --\n");
    mgraph_print(app_wdgts->ride);
    app_wdgts->is_ride = 1;
   
    gtk_widget_queue_draw(GTK_WIDGET(app_wdgts->ride_area));
}

void on_arrival_changed(GtkEntry *entry, app_widgets *app_wdgts)
{
    gchar *val = (gchar *)gtk_entry_get_text(GTK_ENTRY(entry));
    /*app_wdgts->map->name = (char *)realloc((void *)app_wdgts->map->name, 
                strlen(entry) * sizeof(char) + 2);
    strcpy((char *)app_wdgts->map->name, entry);*/
    int *stations = calloc(4, sizeof(int));
    for (int i = 0 ; i < 3; i++)
        stations[i] = -1;
    
    get_stations(stations, val, app_wdgts->map->g);

    printf("Entry: %s\n", val);
    for (int i = 0 ; i < 3; i++)
    {
        if (stations[i] != -1)
            printf("     ->%s\n", app_wdgts->map->g->stations[stations[i]]->name);
    }
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