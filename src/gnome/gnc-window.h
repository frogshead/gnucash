/* 
 * gnc-window.h -- structure which represents a GnuCash window.
 *
 * Copyright (C) 2003 Jan Arne Petersen <jpetersen@uni-bonn.de>
 * Copyright (C) 2003 David Hampton <hampton@employees.org>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, contact:
 *
 * Free Software Foundation           Voice:  +1-617-542-5942
 * 59 Temple Place - Suite 330        Fax:    +1-617-542-2652
 * Boston, MA  02111-1307,  USA       gnu@gnu.org
 */

#ifndef __GNC_WINDOW_H
#define __GNC_WINDOW_H

#include <gtk/gtkwindow.h>
#include "gnc-plugin-page.h"

G_BEGIN_DECLS

#define PLUGIN_PAGE_LABEL "plugin-page"

/* type macros */
#define GNC_TYPE_WINDOW            (gnc_window_get_type ())
#define GNC_WINDOW(o)            (G_TYPE_CHECK_INSTANCE_CAST ((o), GNC_TYPE_WINDOW, GncWindow))
#define GNC_IS_WINDOW(o)         (G_TYPE_CHECK_INSTANCE_TYPE ((o), GNC_TYPE_WINDOW))
#define GNC_WINDOW_GET_IFACE(o)  (G_TYPE_INSTANCE_GET_INTERFACE ((o), GNC_TYPE_WINDOW, GncWindowIface))

/* typedefs & structures */
typedef struct GncWindow GncWindow; /* dummy typedef */

typedef struct {
	GTypeInterface parent;

	/* Virtual Table */
	GtkWidget * (* get_statusbar) (GncWindow *window);
	GtkWidget * (* get_progressbar) (GncWindow *window);
} GncWindowIface;

/* function prototypes */
GType          gnc_window_get_type (void);

void           gnc_window_update_status (GncWindow *window, GncPluginPage *page);
void           gnc_window_set_status (GncWindow *window, GncPluginPage *page, const gchar *message);

void           gnc_window_set_progressbar_window (GncWindow *window);
void           gnc_window_show_progress (const char *message, double percentage);

G_END_DECLS

#endif /* __GNC_WINDOW_H */
