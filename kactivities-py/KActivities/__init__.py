
import dbus

class Event:
    Accessed = 0    # resource was accessed, but we don't know for how long it will be open/used

    Opened = 1      # resource was opened
    Modified = 2    # previously opened resource was modified
    Closed = 3      # previously opened resource was closed

    FocussedIn = 4  # resource get the keyboard focus
    FocussedOut = 5 # resource lost the focus

ActivityManager = dbus.SessionBus().get_object('org.kde.ActivityManager', '/ActivityManager')

RegisterResourceEvent      = ActivityManager.get_dbus_method('RegisterResourceEvent',      'org.kde.ActivityManager')
RegisterResourceMimeType   = ActivityManager.get_dbus_method('RegisterResourceMimeType',   'org.kde.ActivityManager')
RegisterResourceTitle      = ActivityManager.get_dbus_method('RegisterResourceTitle',      'org.kde.ActivityManager')
LinkResourceToActivity     = ActivityManager.get_dbus_method('LinkResourceToActivity',     'org.kde.ActivityManager')
UnlinkResourceFromActivity = ActivityManager.get_dbus_method('UnlinkResourceFromActivity', 'org.kde.ActivityManager')


class ResourceInstance:
    _wid         = None
    _application = None
    _resourceUri = None
    _mimetype    = None
    _title       = None

    def __init__(self, wid, application, resourceUri = None, mimetype = None, title = None):
        self._wid         = wid
        self._application = application
        self._resourceUri = resourceUri
        self._mimetype    = mimetype
        self._title       = title

        if (resourceUri != None):
            RegisterResourceEvent(application, wid, resourceUri, Event.Opened, 0)

        if (title != None):
            self.setTitle(title)

        if (mimetype != None):
            self.setMimetype(mimetype)


    def __del__(self):
        RegisterResourceEvent(self._application, self._wid, self._resourceUri, Event.Closed, 0)

    def notifyModified(self):
        RegisterResourceEvent(self._application, self._wid, self._resourceUri, Event.Modified, 0)

    def notifyFocusedIn(self):
        RegisterResourceEvent(self._application, self._wid, self._resourceUri, Event.FocussedIn, 0)

    def notifyFocusedOut(self):
        RegisterResourceEvent(self._application, self._wid, self._resourceUri, Event.FocussedOut, 0)

    def setUri(self, newUri):
        if self._resourceUri is not None:
            RegisterResourceEvent(self._application, self._wid, self._resourceUri, Event.Closed, 0)

        self._resourceUri = newUri

        if self._resourceUri is not None:
            RegisterResourceEvent(self._application, self._wid, self._resourceUri, Event.Opened, 0)

    def setMimetype(self, mimeType):
        RegisterResourceMimeType(self._resourceUri, self._mimetype)

    def setTitle(self, title):
        RegisterResourceTitle(self._resourceUri, self._title)

    def uri(self):
        return self._resourceUri

    def mimetype(self):
        return self._mimetype

    def title(self):
        return self._title

    def winId(self):
        return seld._wid


    # static void  notifyAccessed(const QUrl &uri, const QString &application = QString());

