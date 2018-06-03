#include "Notifier.h"

#include <gio/gio.h>


Notifier::Notifier() {
	application = g_application_new("gongfu.tea.timer", G_APPLICATION_FLAGS_NONE);
    g_application_register(application, NULL, NULL);
}

Notifier::~Notifier() {
	g_object_unref (application);
}

void Notifier::notify() {
	GNotification *notification = g_notification_new("Tea is ready!");

	g_notification_set_body(notification, "Your tea is ready.");
	g_application_send_notification(application, NULL, notification);

	g_object_unref(notification);
}

