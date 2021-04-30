#include <gtk/gtk.h>
#include <cairo.h>
#include <stdio.h>
#include <math.h>
#include "gui.h"
#include "../libs/map/mapGraph.h"
#include "../libs/map/list.h"

gfloat f (gfloat x)
{
    return 0.2 * x;
}

void on_draw( GtkWidget *widget, cairo_t *cr, app_widgets *app_wdgts)
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
    
    // Draw a circle
    for (int i = 0; i < app_wdgts->gm->order; i++)
    {
        if (app_wdgts->gm->stations[i]->state == 1)
        {
            double x = app_wdgts->gm->stations[i]->x;
            double y = app_wdgts->gm->stations[i]->y;

            // Print lines
            struct list *list = app_wdgts->gm->stations[i]->adjs;
            
            while (list->next != NULL)
            {
                cairo_move_to(cr, x, y);
                cairo_set_source_rgb (cr, 0.0, 1.0, 0.0);
                cairo_set_line_width(cr, 8.0);
                cairo_line_to(cr, app_wdgts->gm->stations[list->next->data]->x, 
                        app_wdgts->gm->stations[list->next->data]->y);
                cairo_stroke (cr);

                list = list->next;
            }

            // Print station
            cairo_arc (cr, x, y, 10, 0.0, 2 * 3.1415);
            cairo_set_source_rgba (cr, 0.6, 0.8, 1.0, 1);
                cairo_set_line_width(cr, 2.0);
            cairo_fill_preserve (cr);
            cairo_set_source_rgb (cr, 0.5, 0.5, 0.5);

            if (app_wdgts->selected_sid == i){
                cairo_set_source_rgb (cr, 1.0, 0.0, 0.0);
            }

            cairo_stroke (cr);
        }
    }
}