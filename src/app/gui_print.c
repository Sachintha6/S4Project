#include <gtk/gtk.h>
#include <cairo.h>
#include <stdio.h>
#include <math.h>
#include "gui.h"
#include "../../libs/map/mapGraph.h"
#include "../../libs/map/list.h"

void on_draw(GtkWidget *widget, cairo_t *cr, app_widgets *app_wdgts)
{
    //Get elements
    app_wdgts->drawing_area = widget;
    
    gtk_widget_add_events(app_wdgts->drawing_area, GDK_BUTTON_PRESS_MASK);
    gtk_widget_add_events(app_wdgts->drawing_area, GDK_BUTTON_RELEASE_MASK);
    app_wdgts->cr = cr;

    // Set zoom and adapt frame
    cairo_scale (cr, app_wdgts->zoom/100, app_wdgts->zoom/100);   
    gint width = cairo_image_surface_get_width(app_wdgts->bg_image);
    gint height = cairo_image_surface_get_height(app_wdgts->bg_image);
    gtk_widget_set_size_request (widget, width*app_wdgts->zoom/100, height*app_wdgts->zoom/100);

    // Apply background image
    cairo_set_source_surface(cr, app_wdgts->bg_image, 0, 0);
    cairo_rectangle (cr, 0, 0, width, height);
    cairo_fill(cr);
    
    // Draw sections
    for (int i = 0; i < app_wdgts->map->g->order; i++)
    {
        if (app_wdgts->map->g->stations[i]->state == 1)
        {
            double x = app_wdgts->map->g->stations[i]->x;
            double y = app_wdgts->map->g->stations[i]->y;
            struct list *list = app_wdgts->map->g->stations[i]->adjs;
            
            cairo_set_line_width(cr, 8.0);
            while (list->next != NULL)
            {
                gdk_rgba_parse(app_wdgts->newcolor, app_wdgts->map->lines[list->next->idline]->color);
                cairo_set_source_rgb(cr, 
                    app_wdgts->newcolor->red, 
                    app_wdgts->newcolor->green, 
                    app_wdgts->newcolor->blue);
                
                cairo_move_to(cr, x, y);
                cairo_line_to(cr, app_wdgts->map->g->stations[list->next->data]->x, 
                        app_wdgts->map->g->stations[list->next->data]->y);
                cairo_stroke (cr);

                list = list->next;
            }
        }
    }

    //Draw stations
    for (int i = 0; i < app_wdgts->map->g->order; i++)
    {
        if (app_wdgts->map->g->stations[i]->state == 1)
        {
            double x = app_wdgts->map->g->stations[i]->x;
            double y = app_wdgts->map->g->stations[i]->y;

            cairo_arc (cr, x, y, 10, 0.0, 2 * 3.1415);
            cairo_set_source_rgba (cr, 0.6, 0.8, 1.0, 1);
            cairo_set_line_width(cr, 2.0);
            cairo_fill_preserve (cr);
            cairo_set_source_rgb (cr, 0.5, 0.5, 0.5);

            cairo_set_source_rgb(cr, 0.1, 0.1, 0.1); 
            cairo_set_font_size(cr, 15);

            cairo_move_to(cr, x+20, y+5);
            cairo_show_text(cr, app_wdgts->map->g->stations[i]->name);
        }
    }
}

void on_ride_draw(GtkWidget *widget, cairo_t *cr, app_widgets *app_wdgts)
{
    if (app_wdgts->is_ride == 0)
        return;

    int x = 35;
    int y = 70;

    int current_line = app_wdgts->ride->stations[0]->adjs->next->idline;
    int station_cpt = 0;
    int iter_cpt = 0;
    char *texte = malloc(sizeof(char)*14);
    static const double dashed[] = {8.0, 8.0};
    //printf("Prendre %s à %s\n", app_wdgts->map->lines[app_wdgts->ride->stations[0]->adjs->next->idline]->name, app_wdgts->ride->stations[0]->name);

    cairo_set_font_size(cr, 12);
    cairo_select_font_face(cr, "Roboto Condensed",
      CAIRO_FONT_SLANT_NORMAL,
      CAIRO_FONT_WEIGHT_BOLD);
    gdk_rgba_parse(app_wdgts->newcolor, app_wdgts->map->lines[current_line]->color);
    cairo_set_source_rgb(cr, 
                    app_wdgts->newcolor->red, 
                    app_wdgts->newcolor->green, 
                    app_wdgts->newcolor->blue);
    cairo_arc (cr, x, y, 10, 0.0, 2 * 3.1415);
    cairo_set_line_width(cr, 2.0);
    cairo_fill_preserve (cr);
    cairo_stroke (cr);

    cairo_move_to(cr, x+20, y+5);
    cairo_set_source_rgba (cr, 0.3, 0.3, 0.3, 1);
    cairo_show_text(cr, app_wdgts->map->lines[current_line]->name);
    cairo_stroke (cr);

    for (int i = 0; i < app_wdgts->ride->order; i++)
    {
        if (i == app_wdgts->ride->order-1 || app_wdgts->ride->stations[i]->adjs->next->idline != current_line)
        {
            iter_cpt++;

            sprintf(texte, "%d stations", station_cpt);

            gdk_rgba_parse(app_wdgts->newcolor, app_wdgts->map->lines[current_line]->color);
            cairo_set_source_rgb(cr, 
                app_wdgts->newcolor->red, 
                app_wdgts->newcolor->green, 
                app_wdgts->newcolor->blue);

            cairo_arc(cr, x, y + iter_cpt*60, 10, 0.0, 2 * 3.1415);
            cairo_set_line_width(cr, 2.0);
            cairo_fill_preserve(cr);
            cairo_stroke(cr);

            cairo_move_to(cr, x, y + iter_cpt*60 - 60);
            cairo_line_to(cr, x, y + iter_cpt*60);
            cairo_set_line_width(cr, 5.0);
            cairo_stroke (cr);

            cairo_move_to(cr, x + 20, y + 5 + iter_cpt*60);
            cairo_set_source_rgba (cr, 0.2, 0.2, 0.2, 1);
            cairo_set_font_size(cr, 12);
            cairo_select_font_face(cr, "Roboto Condensed",
                CAIRO_FONT_SLANT_NORMAL,
                CAIRO_FONT_WEIGHT_BOLD);
            cairo_show_text(cr, app_wdgts->ride->stations[i]->name);
            cairo_set_source_rgba (cr, 0.5, 0.5, 0.5, 1);
            cairo_move_to(cr, x + 25, y - 25 + iter_cpt*60);
            cairo_set_font_size(cr, 11);
            cairo_select_font_face(cr, "Roboto Condensed",
                CAIRO_FONT_SLANT_NORMAL,
                CAIRO_FONT_WEIGHT_NORMAL);
            cairo_show_text(cr, texte);
            cairo_stroke (cr);

            if (i != app_wdgts->ride->order - 1)
            {
                current_line = app_wdgts->ride->stations[i]->adjs->next->idline;
            }

            iter_cpt++;

            //printf("Descendre à %s (%d stations)\n", app_wdgts->ride->stations[i]->name, station_cpt);
            gdk_rgba_parse(app_wdgts->newcolor, app_wdgts->map->lines[current_line]->color);
            cairo_set_source_rgb(cr, 
                app_wdgts->newcolor->red, 
                app_wdgts->newcolor->green, 
                app_wdgts->newcolor->blue);

            if (i == app_wdgts->ride->order-1)
            {
                cairo_set_source_rgba (cr, 0.5, 0.5, 0.5, 1);
                cairo_move_to(cr, x + 25, y - 25 + iter_cpt*60);
                cairo_set_font_size(cr, 11);
                cairo_select_font_face(cr, "Roboto Condensed",
                    CAIRO_FONT_SLANT_NORMAL,
                    CAIRO_FONT_WEIGHT_NORMAL);
                cairo_show_text(cr, "Marcher jusqu'à la destination");
                cairo_stroke (cr);
            }
            else 
            {
                cairo_arc(cr, x, y + iter_cpt*60, 10, 0.0, 2 * 3.1415);
                cairo_set_line_width(cr, 2.0);
                cairo_fill_preserve(cr);
                cairo_stroke(cr);
                cairo_set_source_rgba (cr, 0.2, 0.2, 0.2, 1);
                cairo_move_to(cr, x + 20, y + 5 + iter_cpt*60);
                cairo_set_font_size(cr, 12);
                cairo_select_font_face(cr, "Roboto Condensed",
                    CAIRO_FONT_SLANT_NORMAL,
                    CAIRO_FONT_WEIGHT_BOLD);
                cairo_show_text(cr, app_wdgts->map->lines[current_line]->name);
                cairo_set_source_rgba (cr, 0.5, 0.5, 0.5, 1);
                cairo_move_to(cr, x + 25, y - 25 + iter_cpt*60);
                cairo_set_font_size(cr, 11);
                cairo_select_font_face(cr, "Roboto Condensed",
                    CAIRO_FONT_SLANT_NORMAL,
                    CAIRO_FONT_WEIGHT_NORMAL);
                cairo_show_text(cr, "Changement de ligne");
                cairo_stroke (cr);
            }

            cairo_set_source_rgba (cr, 0.6, 0.6, 0.6, 1);
            cairo_set_dash(cr, dashed, 2, 0);
            cairo_move_to(cr, x, y + iter_cpt*60 - 50);
            cairo_line_to(cr, x, y + iter_cpt*60 - 10);
            cairo_set_line_width(cr, 4.0);
            cairo_stroke (cr);
            cairo_set_dash(cr, dashed, 0, 0);

            station_cpt = 0;
        }

        station_cpt++;
    }

    gint width = 300;
    gint height = 60*iter_cpt + 140;
    gtk_widget_set_size_request (widget, width, height);
}