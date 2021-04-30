#include <gtk/gtk.h>
#include <stdio.h>
#include <string.h>
#include "gui.h"
#include "../libs/map/mapGraph.h"
#include "../libs/map/list.h"

void on_menuitm_open_activate(GtkMenuItem *menuitem, app_widgets *app_wdgts)
{
    gchar *file_name = NULL;
    gtk_widget_show(app_wdgts->dlg_file_choose);
    
    if (gtk_dialog_run(GTK_DIALOG (app_wdgts->dlg_file_choose)) == GTK_RESPONSE_OK) {
        
        file_name = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(app_wdgts->dlg_file_choose));
        if (file_name != NULL) {
            app_wdgts->bg_image = cairo_image_surface_create_from_png(file_name);
            gtk_widget_queue_draw(GTK_WIDGET(app_wdgts->drawing_area));
        }

	    g_free(file_name);
    }

    gtk_widget_hide(app_wdgts->dlg_file_choose);
}


void on_menuitm_close_activate(GtkMenuItem *menuitem, app_widgets *app_wdgts)
{
    gtk_main_quit();
}


void on_window_main_destroy()
{
    gtk_main_quit();
}

/*Navigation */

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

void on_da_click(GtkWidget *widget, GdkEventButton *event, app_widgets *app_wdgts)
{
    double x = event->x / app_wdgts->zoom * 100;
    double y = event->y / app_wdgts->zoom * 100;
    //printf("click: %4.0f.%4.0f \n", x, y);
    
    if (app_wdgts->tool == 1)
    {
        // Add station
        if (mgraph_get_station_by_position(app_wdgts->gm, x, y, 10) == -1)
        {
            app_wdgts->gm = mgraph_add_vertex(app_wdgts->gm, "New", x, y);
        }
    }

    if (app_wdgts->tool == 2)
    {
        int id = mgraph_get_station_by_position(app_wdgts->gm, x, y, 10);
        
        if (id != -1)
        {
            if (app_wdgts->selected_sid == -1)
            {
                app_wdgts->selected_sid = id;
            }
            else
            {
                mgraph_add_edge(app_wdgts->gm, app_wdgts->selected_sid, id);
                app_wdgts->selected_sid = -1;
            }
        }
    }

    if (app_wdgts->tool == 3)
    {
        int id = mgraph_get_station_by_position(app_wdgts->gm, x, y, 10);
        
        if (id != -1)
        {
            if (app_wdgts->selected_sid == -1)
            {
                app_wdgts->selected_sid = id;
            }
        }
        else
        {
            //deselect si reclique + verif que deja select
            app_wdgts->gm->stations[app_wdgts->selected_sid]->x = x;
            app_wdgts->gm->stations[app_wdgts->selected_sid]->y = y;
            app_wdgts->selected_sid = -1;
        }
    }

    if (app_wdgts->tool == 4)
    {
        // Remove station
        int id = mgraph_get_station_by_position(app_wdgts->gm, x, y, 10);
        if (id != -1)
        {
            mgraph_remove_vertex(app_wdgts->gm, id);
        }
    }

    if (app_wdgts->tool == 5)
    {
        int id = mgraph_get_station_by_position(app_wdgts->gm, x, y, 10);
        
        if (id != -1)
        {
            if (app_wdgts->selected_sid == -1)
            {
                app_wdgts->selected_sid = id;
            }
            else
            {
                mgraph_remove_edge(app_wdgts->gm, app_wdgts->selected_sid, id);
                app_wdgts->selected_sid = -1;
            }
        }
    }

    mgraph_print(app_wdgts->gm);
    gtk_widget_queue_draw(GTK_WIDGET(app_wdgts->drawing_area));
}

void on_da_release_mouse(GtkWidget *widget, GdkEventButton *event, app_widgets *app_wdgts)
{
    //printf("---Released\n");
}

void on_tool_clicked(GtkToolButton *button, app_widgets *app_wdgts)
{
    if(strcmp(gtk_tool_button_get_label(button), "Add Station") == 0){
        app_wdgts->tool = 1;
    }
    if(strcmp(gtk_tool_button_get_label(button), "Add Section") == 0){
        app_wdgts->tool = 2;
    }
    if(strcmp(gtk_tool_button_get_label(button), "Moove Station") == 0){
        app_wdgts->tool = 3;
    }
    if(strcmp(gtk_tool_button_get_label(button), "Remove Station") == 0){
        app_wdgts->tool = 4;
    }
    if(strcmp(gtk_tool_button_get_label(button), "Remove Section") == 0){
        app_wdgts->tool = 5;
    }
}
