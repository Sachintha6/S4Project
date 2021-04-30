#ifndef __SUPPORT_H__
#define __SUPPORT_H__

#include <gtk/gtk.h>

typedef struct {
    GtkWidget *dlg_file_choose;       
    GtkWidget *drawing_area;
    GtkWidget *menuitm;
    cairo_t *cr;
    cairo_surface_t *bg_image;
    
    //general infos
    double zoom;
    int tool;
    int selected_sid;
    struct mgraph *gm;
} app_widgets;

#endif