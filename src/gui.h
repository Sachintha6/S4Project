#ifndef __SUPPORT_H__
#define __SUPPORT_H__

#include <gtk/gtk.h>

typedef struct {
    GtkWidget *window; 
    GtkWidget *drawing_area;  
    GtkWidget *menuitm;
    GtkWidget *combo_lines;
    GtkWidget *dlg_file_choose;
    GtkWidget *dlg_save_as;
    GtkWidget *entry_save_as;
    GtkWidget *dlg_rename;
    GtkWidget *entry_rename;
    GdkRGBA *newcolor;
    cairo_t *cr;
    cairo_surface_t *bg_image;
    
    //general infos
    double zoom;
    int tool;
    int selected_sid;
    //struct mgraph *gm;
    struct map *map;
    //struct line *lines[];
} app_widgets;

void update_title(app_widgets *app_wdgts);

#endif