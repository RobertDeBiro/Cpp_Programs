#pragma once

#include <gtk/gtk.h>
#include <string>

#define RTKGOBJECT_TYPE (rtkgobject_get_type())
G_DECLARE_FINAL_TYPE(RtkGObject, rtkgobject, RTKG, OBJECT, GObject)

struct _RtkGObject {
	GObject parent_instance;
	int id;
    int frame;
    gpointer t_obj;
};

inline static void rtkgobject_class_init(RtkGObjectClass *klass) {
	// Class initialization
}

inline static void rtkgobject_init(RtkGObject *self) {
	// Instance initialization
}

inline static RtkGObject* create_rtkgobject(int id) {
	RtkGObject *obj = (RtkGObject*)g_object_new(RTKGOBJECT_TYPE, NULL);
	obj->id = id;
	return obj;
}

inline static void rtkgobject_set_timestamp(RtkGObject* rtk_obj, int frame) {
    rtk_obj->frame = frame;
}

inline static void rtkgobject_set_type_object(RtkGObject* rtk_obj, gpointer obj) {
    rtk_obj->t_obj = obj;







#include "rtkcommon/utils/RtkGObject.h"

G_DEFINE_TYPE(RtkGObject, rtkgobject, G_TYPE_OBJECT)
