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
    app_wdgts->ride = shortest_ride(app_wdgts->map->g, app_wdgts->id_departure, app_wdgts->id_arrival);
    printf("\n\n-- RIDE GRAPH --\n");
    mgraph_print(app_wdgts->ride);
    app_wdgts->is_ride = 1;

    gtk_widget_hide(GTK_WIDGET(app_wdgts->input_labels));
    gtk_widget_queue_draw(GTK_WIDGET(app_wdgts->ride_area));
}

void on_arrival_changed(GtkEntry *entry, app_widgets *app_wdgts)
{
    gchar *value = (gchar*)gtk_entry_get_text(GTK_ENTRY(entry));

    int *stations = calloc(4, sizeof(int));
    for (int i = 0 ; i < 4; i++)
        stations[i] = -1;
    
    get_stations(stations, value, app_wdgts->map->g);

    if (stations[0] != -1)
        gtk_widget_show(GTK_WIDGET(app_wdgts->input_labels));
    else
        gtk_widget_hide(GTK_WIDGET(app_wdgts->input_labels));

    gtk_fixed_move (GTK_FIXED(app_wdgts->fixed), app_wdgts->input_labels, 90, 450);

    for (int i = 0 ; i < 4; i++)
    {
        if (stations[i] != -1)
        {
            gtk_label_set_text(GTK_LABEL(app_wdgts->lab[i]), app_wdgts->map->g->stations[stations[i]]->name);
            gtk_widget_show(GTK_WIDGET(app_wdgts->lab[i]));
        }
        else
        {
            gtk_widget_hide(GTK_WIDGET(app_wdgts->lab[i]));
        }
    }

    app_wdgts->id_arrival = stations[0];
}

void on_departure_changed(GtkEntry *entry, app_widgets *app_wdgts)
{
    gchar *value = (gchar*)gtk_entry_get_text(GTK_ENTRY(entry));

    int *stations = calloc(4, sizeof(int));
    for (int i = 0 ; i < 4; i++)
        stations[i] = -1;
    
    get_stations(stations, value, app_wdgts->map->g);

    if (stations[0] != -1)
        gtk_widget_show(GTK_WIDGET(app_wdgts->input_labels));
    else
        gtk_widget_hide(GTK_WIDGET(app_wdgts->input_labels));

    gtk_fixed_move (GTK_FIXED(app_wdgts->fixed), app_wdgts->input_labels, 90, 390);

    for (int i = 0 ; i < 4; i++)
    {
        if (stations[i] != -1)
        {
            gtk_label_set_text(GTK_LABEL(app_wdgts->lab[i]), app_wdgts->map->g->stations[stations[i]]->name);
            gtk_widget_show(GTK_WIDGET(app_wdgts->lab[i]));
        }
        else
        {
            gtk_widget_hide(GTK_WIDGET(app_wdgts->lab[i]));
        }
    }

    app_wdgts->id_departure = stations[0];
}

void on_label_clicked(GtkEventBox *label, app_widgets *app_wdgts)
{
    /*GList *children = gtk_container_get_children(GTK_CONTAINER(label));
    children = g_list_next(children);

    //for (int i = 0 ; i < 4; i++)
    //{
        const char* val = gtk_label_get_text(GTK_LABEL(app_wdgts->lab[3]));
        printf("%s\n", val);
    //}
    //const char *name = gtk_tool_button_get_label(GTK_WIDGET(label));  
    //printf("%s\n", name);*/

    //const char *value = malloc(sizeof(char)*100);
    //value = gtk_label_get_text(GTK_LABEL(app_wdgts->lab[2]));
    /*const char *value2 = gtk_widget_get_name(GTK_WIDGET(label));
    printf("%s\n", value2);*/
}

void on_label4_clicked(GtkEventBox *label, app_widgets *app_wdgts)
{
    //sprintf("Curr2: %s\n", app_wdgts->current_search);
    //gchar *val = (gchar *)gtk_entry_get_text(GTK_ENTRY(app_wdgts->inputdeparture));
    /*int *stations = calloc(4, sizeof(int));
    printf("ll\n");
    const char *value = malloc(sizeof(char)*100);
    value = gtk_label_get_text(GTK_LABEL(app_wdgts->lab[3]));*/
    
    //Sprintf("%s\n", val);

    //for (int i = 0 ; i < 4; i++)
    //    printf("%d\n", *app_wdgts->sel_stat);
    
    //get_stations(stations, app_wdgts->current_search, app_wdgts->map->g);*/
    //printf("4: %s\n", app_wdgts->map->g->stations[app_wdgts->sel_stat[3]]->name);
}

void on_label3_clicked(GtkEventBox *label, app_widgets *app_wdgts)
{
    /*gchar *val = (gchar *)gtk_entry_get_text(app_wdgts->entry);
    int *stations = calloc(4, sizeof(int));
    
    get_stations(stations, val, app_wdgts->map->g);
    printf("%s\n", app_wdgts->map->g->stations[stations[2]]->name);*/
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