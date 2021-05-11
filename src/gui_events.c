#include <gtk/gtk.h>
#include <stdio.h>
#include <string.h>
#include "gui.h"
#include "../libs/map/mapGraph.h"
#include "../libs/map/list.h"

void on_menuitm_open_activate(GtkMenuItem *menuitem, app_widgets *app_wdgts)
{
    gchar *filename = NULL;
    // Next line have an issue
    gtk_widget_show(GTK_WIDGET(app_wdgts->dlg_file_choose));
    
    if (gtk_dialog_run(GTK_DIALOG (app_wdgts->dlg_file_choose)) == GTK_RESPONSE_OK) {
       
        filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(app_wdgts->dlg_file_choose));
        
        if (filename != NULL) {
            app_wdgts->map = mgraph_load(filename);
            mgraph_print(app_wdgts->map->g);
            printf("===>%s<==\n", app_wdgts->map->backgroundImg);
            app_wdgts->bg_image = cairo_image_surface_create_from_png(app_wdgts->map->backgroundImg);
                //"/home/nathan/s4/S4Project/files/graphics/map.png");
            gtk_widget_queue_draw(GTK_WIDGET(app_wdgts->drawing_area));

            for (int c = 0; c < app_wdgts->map->nblines; c++)
            {
                printf("line %d \n", c);
                printf("--%s--%s\n", app_wdgts->map->lines[0]->name, app_wdgts->map->lines[0]->color);
            }
        }

	    g_free(filename);
    }

    gtk_widget_hide(app_wdgts->dlg_file_choose);
}

void on_menuitm_import_activate(GtkMenuItem *menuitem, app_widgets *app_wdgts)
{
    gchar *filename = NULL;
    gtk_widget_show(app_wdgts->dlg_file_choose);
    
    if (gtk_dialog_run(GTK_DIALOG (app_wdgts->dlg_file_choose)) == GTK_RESPONSE_OK) {
        
        filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(app_wdgts->dlg_file_choose));
        if (filename != NULL) {
            printf("%s\n", filename);
            app_wdgts->bg_image = cairo_image_surface_create_from_png(filename);
            gtk_widget_queue_draw(GTK_WIDGET(app_wdgts->drawing_area));
            //app_wdgts->gm = mgraph_load(filename);
            //mgraph_print(app_wdgts->gm);
        }

	    g_free(filename);
    }

    gtk_widget_hide(app_wdgts->dlg_file_choose);
}

void on_menuitm_save_activate(GtkMenuItem *menuitem, app_widgets *app_wdgts)
{
    printf("=== SAVING ===\n");
    mgraph_save("../files/data/mtest.gra", app_wdgts->map->g, app_wdgts->map->lines);
    printf("=== SAVED ===\n");
}

void on_menuitm_saveas_activate(GtkMenuItem *menuitem, app_widgets *app_wdgts)
{
    printf("=== SAVE AS ===\n");
    gchar *filename = NULL;
    gtk_widget_show(app_wdgts->dlg_save_as);
    
    if (gtk_dialog_run( GTK_DIALOG(app_wdgts->dlg_save_as)) == GTK_RESPONSE_OK) {
        
        filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(app_wdgts->dlg_save_as));
        if (filename != NULL) {
            
            printf("--%s\n", filename);
        }

	    g_free(filename);
    }

    gtk_widget_hide(app_wdgts->dlg_save_as);

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

    if(event->type == GDK_DOUBLE_BUTTON_PRESS)
    {
        int id = mgraph_get_station_by_position(app_wdgts->map->g, x, y, 10);
        
        if (id != -1)
        {
            printf("Rename Station n°%d\n", id);
        }
    }
    else if (app_wdgts->tool == 1)
    {
        // Add station
        if (mgraph_get_station_by_position(app_wdgts->map->g, x, y, 10) == -1)
        {
            app_wdgts->map->g = mgraph_add_vertex(app_wdgts->map->g, "New", x, y);
        }
    }
    else if (app_wdgts->tool == 2)
    {
        //add section between 2 stations
        int id = mgraph_get_station_by_position(app_wdgts->map->g, x, y, 10);
        
        if (id != -1)
        {
            if (app_wdgts->selected_sid == -1)
            {
                app_wdgts->selected_sid = id;
            }
            else
            {
                //verify src != dst
                mgraph_add_edge(app_wdgts->map->g, app_wdgts->selected_sid, id, app_wdgts->current_line->idline);
                app_wdgts->selected_sid = -1;
            }
        }
    }
    else if (app_wdgts->tool == 3)
    {
        int id = mgraph_get_station_by_position(app_wdgts->map->g, x, y, 10);
        
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
            app_wdgts->map->g->stations[app_wdgts->selected_sid]->x = x;
            app_wdgts->map->g->stations[app_wdgts->selected_sid]->y = y;
            app_wdgts->selected_sid = -1;
        }
    }
    else if (app_wdgts->tool == 4)
    {
        // Remove station
        int id = mgraph_get_station_by_position(app_wdgts->map->g, x, y, 10);
        if (id != -1)
        {
            mgraph_remove_vertex(app_wdgts->map->g, id);
        }
    }
    else if (app_wdgts->tool == 5)
    {
        int id = mgraph_get_station_by_position(app_wdgts->map->g, x, y, 10);
        
        if (id != -1)
        {
            if (app_wdgts->selected_sid == -1)
            {
                app_wdgts->selected_sid = id;
            }
            else
            {
                mgraph_remove_edge(app_wdgts->map->g, app_wdgts->selected_sid, id);
                app_wdgts->selected_sid = -1;
            }
        }
    }

    mgraph_print(app_wdgts->map->g);
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

void on_combo_change( GtkWidget *widget, app_widgets *app_wdgts)
{
    int idline = atoi(gtk_combo_box_get_active_id(GTK_COMBO_BOX(widget)));

    app_wdgts->current_line->idline = idline;
    app_wdgts->current_line->name = app_wdgts->map->lines[idline]->name;
    app_wdgts->current_line->color = app_wdgts->map->lines[idline]->color;
}
