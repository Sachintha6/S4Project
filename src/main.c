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
    widgets->map->name = "MUTN - Any Map";

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
    widgets->window = GTK_WIDGET(window);
    widgets->dlg_file_choose = GTK_WIDGET( gtk_builder_get_object(builder, "dlg_file_choose"));
    widgets->dlg_save_as = GTK_WIDGET( gtk_builder_get_object(builder, "dlg_save_as"));
    widgets->dlg_rename = GTK_WIDGET( gtk_builder_get_object(builder, "dlg_rename"));
    widgets->dlg_new_line = GTK_WIDGET( gtk_builder_get_object(builder, "dlg_new_line"));
    widgets->entry_rename = GTK_WIDGET( gtk_builder_get_object(builder, "entry_rename"));
    widgets->entry_newline = GTK_WIDGET( gtk_builder_get_object(builder, "entry_newline"));
    widgets->color_newline = GTK_WIDGET( gtk_builder_get_object(builder, "color_newline"));
    widgets->entry_save_as = GTK_WIDGET( gtk_builder_get_object(builder, "entry_save_as"));
    widgets->drawing_area = GTK_WIDGET( gtk_builder_get_object(builder, "map_drawing"));
    widgets->bg_image = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, 10, 10);
    widgets->combo_lines = GTK_WIDGET(gtk_builder_get_object(builder, "comboboxlines"));
    gtk_color_chooser_set_use_alpha(GTK_COLOR_CHOOSER(widgets->color_newline), TRUE);

    gtk_builder_connect_signals(builder, widgets);
    g_object_unref(builder);

    gtk_widget_show(GTK_WIDGET(window));
    update_title(widgets);
    gtk_main();

    g_slice_free(app_widgets, widgets);
    return 0;
}