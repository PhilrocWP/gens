#include "dbus-service.h"
#include "irc.hpp"

#include <dbus/dbus-glib.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct IrcReporter IrcReporter;
typedef struct IrcReporterClass IrcReporterClass;

GType irc_reporter_get_type (void);

struct IrcReporter
{
	GObject parent;
};

struct IrcReporterClass
{
	GObjectClass parent;
};

#define SOME_TYPE_OBJECT              (irc_reporter_get_type ())
#define SOME_OBJECT(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), SOME_TYPE_OBJECT, IrcReporter))
#define SOME_OBJECT_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), SOME_TYPE_OBJECT, IrcReporterClass))
#define SOME_IS_OBJECT(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), SOME_TYPE_OBJECT))
#define SOME_IS_OBJECT_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), SOME_TYPE_OBJECT))
#define SOME_OBJECT_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), SOME_TYPE_OBJECT, IrcReporterClass))

G_DEFINE_TYPE(IrcReporter, irc_reporter, G_TYPE_OBJECT)

#if 0
gboolean irc_reporter_hello_world(IrcReporter *obj, const char *hello_message, char ***ret, GError **error);
gboolean irc_reporter_get_tuple(IrcReporter *obj, GValueArray **ret, GError **error);
gboolean irc_reporter_get_dict(IrcReporter *obj, GHashTable **ret, GError **error);
#endif

gboolean irc_reporter_get_last_modified(IrcReporter *obj, unsigned int *ret, GError **error);
gboolean irc_reporter_is_rom_loaded(IrcReporter *obj, gboolean *ret, GError **error);
gboolean irc_reporter_get_rom_string(IrcReporter *obj, char **ret, GError **error);

#include "dbus-service-glue.h"

static void irc_reporter_init(IrcReporter *obj)
{
}

static void irc_reporter_class_init(IrcReporterClass *klass)
{
}

gboolean irc_reporter_get_last_modified(IrcReporter *obj, unsigned int *ret, GError **error)
{
	*ret = irc_last_modified;
	return TRUE;
}

gboolean irc_reporter_is_rom_loaded(IrcReporter *obj, gboolean *ret, GError **error)
{
	*ret = irc_is_rom_loaded;
	return TRUE;
}

gboolean irc_reporter_get_rom_string(IrcReporter *obj, char **ret, GError **error)
{
	*ret = g_strdup(irc_rom_string);
	return TRUE;
}


static DBusGConnection *bus = NULL;
static DBusGProxy *bus_proxy = NULL;
static IrcReporter *obj = NULL;


/**
 * irc_dbus_init(): Initialize D-Bus.
 * @return 0 on success; non-zero on error.
 */
int irc_dbus_init(void)
{
	GError *error = NULL;
	guint request_name_result;
	
	// TODO: If dbus_g_bus_get() is successful but we return immediately afterwards,
	// GTK+ fails initialization, resulting in a SIGSEGV.
	bus = dbus_g_bus_get(DBUS_BUS_SESSION, &error);
	if (!bus)
	{
		fprintf(stderr, "Couldn't connect to session bus: %s\n",
			(error != NULL ? error->message : "(unknown error)"));
		return -1;
	}
	
	bus_proxy = dbus_g_proxy_new_for_name(bus, "org.freedesktop.DBus",
						"/org/freedesktop/DBus",
						"org.freedesktop.DBus");
	
	if (!dbus_g_proxy_call(bus_proxy, "RequestName", &error,
				G_TYPE_STRING, "org.mdp.IrcService",
				G_TYPE_UINT, 0,
				G_TYPE_INVALID,
				G_TYPE_UINT, &request_name_result,
				G_TYPE_INVALID))
	{
		fprintf(stderr, "Failed to acquire org.mdp.IrcService: %s\n",
			(error != NULL ? error->message : "(unknown error)"));
		g_object_unref(bus_proxy);
		return -2;
	}
	
	dbus_g_object_type_install_info(SOME_TYPE_OBJECT, &dbus_glib_irc_reporter_object_info);
	obj = g_object_new(SOME_TYPE_OBJECT, NULL);
	
	dbus_g_connection_register_g_object(bus, "/IrcReporter", G_OBJECT(obj));
	
	printf("IRC Reporter D-Bus service running.\n");
	return 0;
}


/**
 * irc_dbus_end(): Shut down D-Bus.
 * @return 0 on success; non-zero on error.
 */
int irc_dbus_end(void)
{
	if (!bus)
		return 0;
	
	// Remove the object from D-Bus.
	g_object_unref(obj);
	g_object_unref(bus_proxy);
	
	// NULL out everything.
	bus = NULL;
	bus_proxy = NULL;
	obj = NULL;
	
	return 0;
}
