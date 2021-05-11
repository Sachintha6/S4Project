#ifndef __SUPPORT_H__
#define __SUPPORT_H__

#include <gtk/gtk.h>

typedef struct {
    GtkWidget *dlg_file_choose;
    GtkWidget *dlg_save_as;   
    GtkWidget *drawing_area;
    GtkWidget *menuitm;
    GtkWidget *combo_lines;
    GdkRGBA *newcolor;
    cairo_t *cr;
    cairo_surface_t *bg_image;
    
    //general infos
    double zoom;
    int tool;
    int selected_sid;
    //struct mgraph *gm;
    struct line *current_line;
    struct map *map;
    //struct line *lines[];
} app_widgets;

#endif