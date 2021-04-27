#ifndef __SUPPORT_H__
#define __SUPPORT_H__

#include <gtk/gtk.h>

typedef struct {
    GtkWidget *w_dlg_file_choose;       
    GtkWidget *w_drawing_area;
    GtkWidget *w_menuitm;
    cairo_surface_t *bg_image;
} app_widgets;

#define ZOOM_X 50.0
#define ZOOM_Y 50.0

#endif