# This class is modified from gnome-lirc-properties project
# the original file is gnome_lirc_properties/backend.py
# GPL v2+
# Copyright (C) 2008 Fluendo Embedded S.L.
# Copyright (C) 2010 TualatriX <tualatrix@gmail.com>
# Copyright (C) 2013 National University of Defense Technology(NUDT) & Kylin Ltd

import dbus.service

class AccessDeniedException(dbus.DBusException):
    '''This exception is raised when some operation is not permitted.'''

    _dbus_error_name = 'com.ubuntukylin.IhuSession.AccessDeniedException'


class PolicyKitService(dbus.service.Object):
    '''A D-BUS service that uses PolicyKit for authorization.'''

    def _check_policykit(self, sender):
        if not sender: raise ValueError('sender == None')
        bus = dbus.SystemBus()
        proxy = bus.get_object('org.freedesktop.PolicyKit1', '/org/freedesktop/PolicyKit1/Authority')
        authority = dbus.Interface(proxy, dbus_interface='org.freedesktop.PolicyKit1.Authority')
        subject = ('system-bus-name', {'name' : sender})
        action_id = DBUS_IFACE
        details = {}
        flags = 1            # AllowUserInteraction flag
        cancellation_id = '' # No cancellation id
        (granted, _, details) = authority.CheckAuthorization(subject, action_id, details, flags, cancellation_id, timeout=600)
        return granted

    def _check_permission(self, sender, action):
        '''
        Verifies if the specified action is permitted, and raises
        an AccessDeniedException if not.

        The caller should use ObtainAuthorization() to get permission.
        '''

        try:
            if sender:
                kit = dbus.SystemBus().get_object('org.freedesktop.PolicyKit1', '/org/freedesktop/PolicyKit1/Authority')
                kit = dbus.Interface(kit, 'org.freedesktop.PolicyKit1.Authority')

                # Note that we don't use CheckAuthorization with bus name
                # details because we have no ways to get the PID of the
                # front-end, so we're left with checking that its bus name
                # is authorised instead
                # See http://bugzilla.gnome.org/show_bug.cgi?id=540912
                (granted, _, details) = kit.CheckAuthorization(
                                ('system-bus-name', {'name': sender}),
                                action, {}, dbus.UInt32(1), '', timeout=600)

                if not granted:
                    raise AccessDeniedException('Session not authorized by PolicyKit')

        except AccessDeniedException:
            raise

        except dbus.DBusException, ex:
            raise AccessDeniedException(ex.message)
