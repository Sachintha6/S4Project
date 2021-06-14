#ifndef __SUPPORT_H__
#define __SUPPORT_H__

#include <gtk/gtk.h>

typedef struct {
    GtkWidget *window; 
    GtkWidget *drawing_area;
    GtkWidget *ride_area;
    GtkWidget *fixed;
    GtkWidget *input_labels;
    GtkWidget *lab[4];
    GtkWidget *inputdeparture;
    GtkWidget *inputarrival;
    GdkRGBA *newcolor;
    cairo_t *cr;
    cairo_surface_t *bg_image;
    cairo_t *cride;
    
    double zoom;
    struct map *map;
    struct mgraph *ride;
    int is_ride;
    int id_departure;
    int id_arrival;
} app_widgets;

void update_title(app_widgets *app_wdgts);
void on_key_press (GtkWidget *widget, GdkEventKey *event, app_widgets *app_wdgts);

#endif