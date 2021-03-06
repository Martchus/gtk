/* GDK - The GIMP Drawing Kit
 * Copyright (C) 2010 Red Hat, Inc.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __GDK_SCREEN_PRIVATE_H__
#define __GDK_SCREEN_PRIVATE_H__

#include "gdkscreen.h"
#include "gdkvisual.h"

G_BEGIN_DECLS

#define GDK_SCREEN_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), GDK_TYPE_SCREEN, GdkScreenClass))
#define GDK_IS_SCREEN_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), GDK_TYPE_SCREEN))
#define GDK_SCREEN_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), GDK_TYPE_SCREEN, GdkScreenClass))

typedef struct _GdkScreenClass GdkScreenClass;

struct _GdkScreen
{
  GObject parent_instance;

  gdouble resolution; /* pixels/points scale factor for fonts */
  guint resolution_set : 1; /* resolution set through public API */
  guint closed : 1;
};

struct _GdkScreenClass
{
  GObjectClass parent_class;

  GdkDisplay * (* get_display)           (GdkScreen *screen);
  GdkWindow *  (* get_root_window)       (GdkScreen *screen);
  gint         (* get_n_monitors)        (GdkScreen *screen);
  gint         (* get_primary_monitor)   (GdkScreen *screen);
  gint         (* get_monitor_width_mm)  (GdkScreen *screen,
                                          gint       monitor_num);
  gint         (* get_monitor_height_mm) (GdkScreen *screen,
                                          gint       monitor_num);
  gchar *      (* get_monitor_plug_name) (GdkScreen *screen,
                                          gint       monitor_num);
  void         (* get_monitor_geometry)  (GdkScreen    *screen,
                                          gint          monitor_num,
                                          GdkRectangle *dest);
  void         (* get_monitor_workarea)  (GdkScreen    *screen,
                                          gint          monitor_num,
                                          GdkRectangle *dest);
  GList *      (* list_visuals)          (GdkScreen *screen);
  GdkVisual *  (* get_system_visual)     (GdkScreen *screen);
  GdkVisual *  (* get_rgba_visual)       (GdkScreen *screen);
  gboolean     (* is_composited)         (GdkScreen *screen);
  gboolean     (* get_setting)           (GdkScreen   *screen,
                                          const gchar *name,
                                          GValue      *value);
  gint         (* get_monitor_scale_factor) (GdkScreen *screen,
                                             gint       monitor_num);

  /* Signals: */
  void (*size_changed) (GdkScreen *screen);
  void (*composited_changed) (GdkScreen *screen);
  void (*monitors_changed) (GdkScreen *screen);
};

G_END_DECLS

#endif /* __GDK_SCREEN_PRIVATE_H__ */
