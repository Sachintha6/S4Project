#include <gtk/gtk.h>
#include "gui.h"

void on_menuitm_open_activate(GtkMenuItem *menuitem, app_widgets *app_wdgts)
{
    gchar *file_name = NULL;
    gtk_widget_show(app_wdgts->w_dlg_file_choose);
    
    if (gtk_dialog_run(GTK_DIALOG (app_wdgts->w_dlg_file_choose)) == GTK_RESPONSE_OK) {
        
        file_name = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(app_wdgts->w_dlg_file_choose));
        if (file_name != NULL) {
            app_wdgts->bg_image = cairo_image_surface_create_from_png(file_name);
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