#include <gtk/gtk.h>
#include <cairo.h>
#include <stdio.h>
#include <math.h>

#define WIDTH   640
#define HEIGHT  480

#define ZOOM_X  50.0
#define ZOOM_Y  50.0

typedef struct {
    GtkWidget *w_dlg_file_choose;       
    GtkWidget *w_drawing_area;
    GtkWidget *w_menuitm;
    cairo_t *w_cairo_context;
} app_widgets;

int main (int argc, char **argv)
{
    GObject *window;
    //GtkWidget *da;
    GtkBuilder *builder;
    GError *error = NULL;

    app_widgets *widgets = g_slice_new(app_widgets);

    gtk_init(&argc, &argv);

    builder = gtk_builder_new ();
    if (gtk_builder_add_from_file(builder, "old.glade", &error) == 0)
    {
        g_printerr("Error loading file: %s\n", error->message);
        g_clear_error(&error);
        return 1;
    }

    window = gtk_builder_get_object(builder, "Interface");
    // Get objects from UI
    widgets->w_dlg_file_choose = GTK_WIDGET( gtk_builder_get_object(builder, "dlg_file_choose"));
    widgets->w_drawing_area = GTK_WIDGET( gtk_builder_get_object(builder, "map_drawing"));

    gtk_builder_connect_signals(builder, widgets);
    g_object_unref(builder);

    gtk_widget_show( GTK_WIDGET(window));
    gtk_main ();

    g_slice_free( app_widgets, widgets);
    return 0;
}

gfloat f (gfloat x)
{
    return 0.2 * x;
}

void on_draw (GtkWidget *widget, cairo_t *cr, gpointer user_data)
{
    GdkRectangle da;
    cairo_surface_t *image;

    gdouble dx = 5.0, dy = 5.0;
    gdouble i, clip_x1 = 0.0, clip_y1 = 0.0, clip_x2 = 0.0, clip_y2 = 0.0;
    
    GdkWindow *window = gtk_widget_get_window(widget);

    gdk_window_get_geometry (window,
            &da.x,
            &da.y,
            &da.width,
            &da.height); 

    cairo_scale (cr, ZOOM_X/100, ZOOM_Y/100);
    cairo_translate (cr, -da.width / 2, -da.height / 2);

    // Background image
    image = cairo_image_surface_create_from_png("map.png");

    gint width = cairo_image_surface_get_width(image);
    gint height = cairo_image_surface_get_height(image);
    //da.width = width;
    //da.height = height;
    printf("img width: %d surface width: %d \n", width, da.width);

    cairo_set_source_surface(cr, image, 0, 0);
    cairo_rectangle (cr, 0, 0, width, height);
    cairo_fill(cr);
 
    /* Determine the data points to calculate (ie. those in the clipping zone */
    cairo_device_to_user_distance (cr, &dx, &dy);
    cairo_clip_extents (cr, &clip_x1, &clip_y1, &clip_x2, &clip_y2);
    cairo_set_line_width (cr, dx);

    printf("dim x: %f %f y: %f %f \n", clip_x1, clip_x2, clip_y1, clip_y2);

    /* Draws x and y axis */
    cairo_set_source_rgb (cr, 0.0, 1.0, 0.0);
    cairo_move_to (cr, clip_x1, 0.0);
    cairo_line_to (cr, clip_x2, 0.0);
    cairo_move_to (cr, 0.0, clip_y1);
    cairo_line_to (cr, 0.0, clip_y2);
    cairo_stroke (cr);

    for (i = clip_x1; i < clip_x2; i += dx)
        cairo_line_to (cr, i, f (i));

    cairo_set_source_rgba (cr, 1, 0.2, 0.2, 0.6);
    cairo_stroke (cr);

    //return FALSE;
}

void on_menuitm_open_activate(GtkMenuItem *menuitem, app_widgets *app_wdgts)
{
    gchar *file_name = NULL;
    gtk_widget_show(app_wdgts->w_dlg_file_choose);
    
    if (gtk_dialog_run(GTK_DIALOG (app_wdgts->w_dlg_file_choose)) == GTK_RESPONSE_OK) {
        
        file_name = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(app_wdgts->w_dlg_file_choose));
        if (file_name != NULL) {
            //gtk_image_set_from_file(GTK_IMAGE(app_wdgts->w_drawing_area), file_name);
        }

	    g_free(file_name);
    }

    gtk_widget_hide(app_wdgts->w_dlg_file_choose);
}


void on_menuitm_close_activate(GtkMenuItem *menuitem, app_widgets *app_wdgts)
{
    gtk_main_quit();
}


void on_window_main_destroy()
{
    gtk_main_quit();
}