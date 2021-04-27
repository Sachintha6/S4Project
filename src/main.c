#include <gtk/gtk.h>
#include <cairo.h>
#include <stdio.h>
#include "gui.h"

int main (int argc, char **argv)
{
    GtkBuilder *builder;
    GObject *window;
    GError *error = NULL;
    app_widgets *widgets = g_slice_new(app_widgets);

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
    widgets->w_dlg_file_choose = GTK_WIDGET( gtk_builder_get_object(builder, "dlg_file_choose"));
    widgets->w_drawing_area = GTK_WIDGET( gtk_builder_get_object(builder, "map_drawing"));
    widgets->bg_image = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, 10, 10);

    gtk_builder_connect_signals(builder, widgets);
    g_object_unref(builder);

    gtk_widget_show( GTK_WIDGET(window));
    gtk_main ();

    g_slice_free( app_widgets, widgets);
    return 0;
}