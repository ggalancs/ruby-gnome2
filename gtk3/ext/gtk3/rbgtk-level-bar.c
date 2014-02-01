/* -*- c-file-style: "ruby"; indent-tabs-mode: nil -*- */
/*
 *  Copyright (C) 2014 Ruby-GNOME2 Project Team
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 *  MA  02110-1301  USA
 */

#include "rbgtk3private.h"

#if GTK_CHECK_VERSION(3, 6, 0)

#define RG_TARGET_NAMESPACE cLevelBar
#define _SELF(self) (RVAL2GTKLEVELBAR(self))

static VALUE
rg_initialize(VALUE self)
{
    RBGTK_INITIALIZE(self, gtk_level_bar_new());
    return Qnil;
}

static VALUE
rg_add_offset_value(VALUE self, VALUE name, VALUE value)
{
    gtk_level_bar_add_offset_value(_SELF(self),
                                   RVAL2CSTR(name), NUM2DBL(value));
    return self;
}

static VALUE
rg_remove_offset_value(VALUE self, VALUE name)
{
    gtk_level_bar_remove_offset_value(_SELF(self), RVAL2CSTR(name));
    return self;
}

static VALUE
rg_has_offset_value_p(VALUE self, VALUE name, VALUE value)
{
    long n;
    gdouble *gvalue = RVAL2GDOUBLES(value, n);
    return CBOOL2RVAL(gtk_level_bar_get_offset_value(_SELF(self),
                                                     RVAL2CSTR(name),
                                                     gvalue));
}

void
Init_gtk_level_bar(VALUE mGtk)
{
    VALUE RG_TARGET_NAMESPACE = G_DEF_CLASS(GTK_TYPE_LEVEL_BAR, "LevelBar", mGtk);

    rb_define_const(RG_TARGET_NAMESPACE, "CONTINUOUS", GTK_LEVEL_BAR_MODE_CONTINUOUS);
    rb_define_const(RG_TARGET_NAMESPACE, "DISCRETE", GTK_LEVEL_BAR_MODE_DISCRETE);
    rb_define_const(RG_TARGET_NAMESPACE, "OFFSET_LOW", CSTR2RVAL(GTK_LEVEL_BAR_OFFSET_LOW));
    rb_define_const(RG_TARGET_NAMESPACE, "OFFSET_HIGH", CSTR2RVAL(GTK_LEVEL_BAR_OFFSET_HIGH));
    RG_DEF_METHOD(initialize, 0);
    RG_DEF_METHOD(add_offset_value, 2);
    RG_DEF_METHOD(remove_offset_value, 1);
    RG_DEF_METHOD_P(has_offset_value, 2);
}
#endif
