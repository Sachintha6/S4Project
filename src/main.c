#include <gtk/gtk.h>
#include <cairo.h>
#include <stdio.h>
#include "gui.h"
#include "../libs/map/mapGraph.h"
#include "../libs/map/list.h"

int main (int argc, char **argv)
{
    GtkBuilder *builder;
    GObject *window;
    GError *error = NULL;
    
    //Init struct
    app_widgets *widgets = g_slice_new(app_widgets);
    widgets->newcolor = (GdkRGBA*)malloc(sizeof(GdkRGBA));
    widgets->zoom = 100.0;
    widgets->tool = 1;
    widgets->selected_sid = -1;
    widgets->map = (struct map*)malloc(sizeof(struct map));
    widgets->map->g = mgraph_init(1, 0);

    /*widgets->map = mgraph_load("../files/data/mtest.gra");
    mgraph_print(widgets->map->g);*/

    gtk_init(&argc, &argv);

    builder = gtk_builder_new ();
    if (gtk_builder_add_from_file(builder, "../files/graphics/gui.glade", &error) == 0)
    {
        g_printerr("Error loading file: %s\n", error->message);
        g_clear_error(&error);
        return 1;
    }

    window = gtk_builder_get_object(builder, "Interface");

    // Get objects from UI
    widgets->dlg_file_choose = GTK_WIDGET( gtk_builder_get_object(builder, "dlg_file_choose"));
    widgets->dlg_save_as = GTK_WIDGET( gtk_builder_get_object(builder, "dlg_save_as"));
    widgets->drawing_area = GTK_WIDGET( gtk_builder_get_object(builder, "map_drawing"));
    widgets->bg_image = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, 10, 10);

    widgets->combo_lines = GTK_WIDGET(gtk_builder_get_object(builder, "comboboxlines"));

    /*gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(widgets->combo_lines), "7", "Ligne 7");
    gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(widgets->combo_lines), "8", "Ligne 8");
    gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(widgets->combo_lines), "9", "Ligne 9");
    gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(widgets->combo_lines), "10", "Ligne 10");
    gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(widgets->combo_lines), "11", "Ligne 11");
    gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(widgets->combo_lines), "12", "Ligne 12");
    gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(widgets->combo_lines), "13", "Ligne 13");
    gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(widgets->combo_lines), "14", "Ligne 14");

    printf("here pi \n");
    widgets->current_line = (struct line*) malloc(sizeof(struct line));
    for (int i = 0; i < 15; i++)
    {
        widgets->lines[i] = (struct line*) malloc(sizeof(struct line));
        widgets->lines[i]->name = "NoName";
        widgets->lines[i]->color = "#000000";
    }
    
    widgets->lines[7]->name = "Ligne 7";
    widgets->lines[8]->name = "Ligne 8";
    widgets->lines[9]->name = "Ligne 9";
    widgets->lines[10]->name = "Ligne 10";
    widgets->lines[11]->name = "Ligne 11";
    widgets->lines[12]->name = "Ligne 12";
    widgets->lines[13]->name = "Ligne 13";
    widgets->lines[14]->name = "Ligne 14";

    widgets->lines[7]->color = "#f6a6bd";
    widgets->lines[8]->color = "#ceadd5";
    widgets->lines[9]->color = "#d6cd00";
    widgets->lines[10]->color = "#ffb301";
    widgets->lines[11]->color = "#ad612d";
    widgets->lines[12]->color = "#03854c";
    widgets->lines[13]->color = "#6ec4e8";
    widgets->lines[14]->color = "#642284";*/

    gtk_builder_connect_signals(builder, widgets);
    g_object_unref(builder);

    gtk_widget_show(GTK_WIDGET(window));

    gtk_main();

    //Free and exit
    g_slice_free(app_widgets, widgets);
    return 0;
}