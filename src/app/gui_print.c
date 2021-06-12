#include <gtk/gtk.h>
#include <cairo.h>
#include <stdio.h>
#include <math.h>
#include "gui.h"
#include "../libs/map/mapGraph.h"
#include "../libs/map/list.h"

void on_draw(GtkWidget *widget, cairo_t *cr, app_widgets *app_wdgts)
{
    //Get elements
    app_wdgts->drawing_area = widget;
    
    gtk_widget_add_events(app_wdgts->drawing_area, GDK_BUTTON_PRESS_MASK);
    gtk_widget_add_events(app_wdgts->drawing_area, GDK_BUTTON_RELEASE_MASK);
    app_wdgts->cr = cr;

    // Set zoom and adapt frame
    cairo_scale (cr, app_wdgts->zoom/100, app_wdgts->zoom/100);   
    gint width = cairo_image_surface_get_width(app_wdgts->bg_image);
    gint height = cairo_image_surface_get_height(app_wdgts->bg_image);
    gtk_widget_set_size_request (widget, width*app_wdgts->zoom/100, height*app_wdgts->zoom/100);

    // Apply background image
    cairo_set_source_surface(cr, app_wdgts->bg_image, 0, 0);
    cairo_rectangle (cr, 0, 0, width, height);
    cairo_fill(cr);
    
    // Draw sections
    for (int i = 0; i < app_wdgts->map->g->order; i++)
    {
        if (app_wdgts->map->g->stations[i]->state == 1)
        {
            double x = app_wdgts->map->g->stations[i]->x;
            double y = app_wdgts->map->g->stations[i]->y;
            struct list *list = app_wdgts->map->g->stations[i]->adjs;
            
            cairo_set_line_width(cr, 8.0);
            while (list->next != NULL)
            {
                gdk_rgba_parse(app_wdgts->newcolor, app_wdgts->map->lines[list->next->idline]->color);
                cairo_set_source_rgb(cr, 
                    app_wdgts->newcolor->red, 
                    app_wdgts->newcolor->green, 
                    app_wdgts->newcolor->blue);
                
                cairo_move_to(cr, x, y);
                cairo_line_to(cr, app_wdgts->map->g->stations[list->next->data]->x, 
                        app_wdgts->map->g->stations[list->next->data]->y);
                cairo_stroke (cr);

                list = list->next;
            }
        }
    }

    //Draw stations
    for (int i = 0; i < app_wdgts->map->g->order; i++)
    {
        if (app_wdgts->map->g->stations[i]->state == 1)
        {
            double x = app_wdgts->map->g->stations[i]->x;
            double y = app_wdgts->map->g->stations[i]->y;

            cairo_arc (cr, x, y, 10, 0.0, 2 * 3.1415);
            cairo_set_source_rgba (cr, 0.6, 0.8, 1.0, 1);
            cairo_set_line_width(cr, 2.0);
            cairo_fill_preserve (cr);
            cairo_set_source_rgb (cr, 0.5, 0.5, 0.5);

            cairo_set_source_rgb(cr, 0.1, 0.1, 0.1); 
            cairo_set_font_size(cr, 15);

            cairo_move_to(cr, x+20, y+5);
            cairo_show_text(cr, app_wdgts->map->g->stations[i]->name);
        }
    }
}

void on_ride_draw(GtkWidget *widget, cairo_t *cr, app_widgets *app_wdgts)
{
    
}