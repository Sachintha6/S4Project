#ifndef __SUPPORT_H__
#define __SUPPORT_H__

#include <gtk/gtk.h>

typedef struct {
    GtkWidget *window; 
    GtkWidget *drawing_area;
    GdkRGBA *newcolor;
    cairo_t *cr;
    cairo_surface_t *bg_image;
    
    double zoom;
    struct map *map;
    struct mgraph *ride;
} app_widgets;

void update_title(app_widgets *app_wdgts);
void on_key_press (GtkWidget *widget, GdkEventKey *event, app_widgets *app_wdgts);

#endif