#include "Notifier.h"

#include <iostream>
#include <cassert>
#include <stdexcept>
#include <gio/gio.h>


using std::runtime_error;


void Notifier::init() {
    // Flag `G_APPLICATION_FLAGS_NONE` stops program for a long time before
    // it will throw error. Flag `G_APPLICATION_NON_UNIQUE` solves this problem.
	application = g_application_new("gongfu.tea.timer", G_APPLICATION_NON_UNIQUE);

    auto result = g_application_register(application, NULL, NULL);
    if (result == FALSE) {
        throw runtime_error("Error initializing notifications.");
    }

    _isInited = true;
}

void Notifier::destroy() {
    _isInited = false;

	g_object_unref (application);
}

void Notifier::notify() {
    assert(_isInited == true);

	GNotification *notification = g_notification_new("Tea is ready!");

	g_notification_set_body(notification, "Your tea is ready.");
	g_application_send_notification(application, NULL, notification);

	g_object_unref(notification);
}

bool Notifier::isInited() {
    return _isInited;
}

