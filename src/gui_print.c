#include <gtk/gtk.h>
#include <cairo.h>
#include <stdio.h>
#include <math.h>
#include "gui.h"

gfloat f (gfloat x)
{
    return 0.2 * x;
}

void on_draw( GtkWidget *widget, cairo_t *cr, app_widgets *app_wdgts)
{
    GdkRectangle da;

    gdouble dx = 5.0, dy = 5.0;
    gdouble clip_x1 = 0.0, clip_y1 = 0.0, clip_x2 = 0.0, clip_y2 = 0.0;
    
    GdkWindow *window = gtk_widget_get_window(widget);

    gdk_window_get_geometry (window,
            &da.x,
            &da.y,
            &da.width,
            &da.height); 

    cairo_scale (cr, ZOOM_X/100, ZOOM_Y/100);
    //RM: cairo_translate (cr, -da.width / 2, -da.height / 2);
    gtk_widget_set_size_request (widget, 2500, 2500);

    // Background image
    gint width = cairo_image_surface_get_width(app_wdgts->bg_image);
    gint height = cairo_image_surface_get_height(app_wdgts->bg_image);
    cairo_set_source_surface(cr, app_wdgts->bg_image, 0, 0);
    cairo_rectangle (cr, 0, 0, width, height);
    cairo_fill(cr);

    cairo_device_to_user_distance (cr, &dx, &dy);
    cairo_clip_extents (cr, &clip_x1, &clip_y1, &clip_x2, &clip_y2);
    cairo_set_line_width (cr, dx);

    printf("dim x: %f %f y: %f %f \n", clip_x1, clip_x2, clip_y1, clip_y2);

    /* Draw a circle*/
    cairo_arc (cr, 500, 500, 25, 0.0, 2 * 3.1415);
    cairo_set_source_rgba (cr, 0.6, 0.8, 1.0, 0.6);
    cairo_fill_preserve (cr);
    cairo_set_source_rgb (cr, 0.0, 0.0, 0.0);
    cairo_stroke (cr);

    //return FALSE;
}