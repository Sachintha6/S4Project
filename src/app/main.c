#include <gtk/gtk.h>
#include <cairo.h>
#include <stdio.h>
#include "gui.h"
#include "../../libs/map/mapGraph.h"
#include "../../libs/map/list.h"
#include "../ride/ride.h"

int main (int argc, char **argv)
{
    GtkBuilder *builder;
    GObject *window;
    GObject *da_obj;
    GObject *da_ride;
    GError *error = NULL;
    
    //Init struct
    app_widgets *widgets = g_slice_new(app_widgets);
    widgets->newcolor = (GdkRGBA*)malloc(sizeof(GdkRGBA));
    widgets->zoom = 30.0;
    widgets->is_ride = 0;
    widgets->id_arrival = 0;
    widgets->id_departure = 0;
    widgets->map = (struct map*)malloc(sizeof(struct map));
    widgets->map->g = mgraph_init(1, 0);
    widgets->ride = mgraph_init(0, 0);
    widgets->map->name = "MUTN - Any Map";

    gtk_init(&argc, &argv);

    builder = gtk_builder_new ();
    if (gtk_builder_add_from_file(builder, "../../files/graphics/app.glade", &error) == 0)
    {
        g_printerr("Error loading file: %s\n", error->message);
        g_clear_error(&error);
        return 1;
    }

    // Get objects from UI
    window = gtk_builder_get_object(builder, "Interface");
    widgets->window = GTK_WIDGET(window);
    widgets->input_labels = GTK_WIDGET(gtk_builder_get_object(builder, "input-labels"));
    
    widgets->lab[0] = GTK_WIDGET(gtk_builder_get_object(builder, "label1"));
    widgets->lab[1] = GTK_WIDGET(gtk_builder_get_object(builder, "label2"));
    widgets->lab[2] = GTK_WIDGET(gtk_builder_get_object(builder, "label3"));
    widgets->lab[3] = GTK_WIDGET(gtk_builder_get_object(builder, "label4"));
    //gtk_label_set_text(GTK_LABEL(widgets->lab1), "Blabla1");
    //gtk_label_set_text(GTK_LABEL(widgets->lab]), "Blabla4");

    widgets->inputdeparture = GTK_WIDGET(gtk_builder_get_object(builder, "entry1"));
    widgets->inputarrival = GTK_WIDGET(gtk_builder_get_object(builder, "entry2"));
    widgets->fixed = GTK_WIDGET(gtk_builder_get_object(builder, "fixed1"));

    da_obj = gtk_builder_get_object(builder, "map-drawing");
    widgets->drawing_area = GTK_WIDGET(da_obj);
    widgets->bg_image = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, 10, 10);
    da_ride = gtk_builder_get_object(builder, "ride-drawing");
    widgets->ride_area = GTK_WIDGET(da_ride);

    /*****CSS****/
    GtkCssProvider *provider = gtk_css_provider_new ();
    gtk_css_provider_load_from_path (provider, "../../files/css/app.css", NULL);
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(provider), 600);

    gtk_builder_connect_signals(builder, widgets);
    g_object_unref(builder);
    gtk_widget_show(GTK_WIDGET(window));
    gtk_widget_hide(GTK_WIDGET(widgets->input_labels));

    widgets->map = mgraph_load("../../files/data/paris.gra");
    mgraph_print(widgets->map->g);
    widgets->bg_image = cairo_image_surface_create_from_png(widgets->map->backgroundImg);

    gtk_main();

    g_slice_free(app_widgets, widgets);
    return 0;
}