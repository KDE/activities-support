import os
import dbus
import XlibGetWindowId
import KActivities

#######################################################################
# Function returns the window id for the current window               #
#######################################################################

def _getWindowId():
    # Getting the window id for the current process - GVIM
    for wid in XlibGetWindowId.getWindowIdsForCurrentProcess():
        return wid

    return 0

    # Falling back to testing the environment vatiable
    # if we are in a terminal - normal VIM
    try:
        wid = int(os.getenv("WINDOWID"))
        return wid

    # Otherwise, we must go without the window id
    except ValueError:
        return 0


#######################################################################
# Returns the url for the current file                                #
#######################################################################

def _urlForCurrentDocument():
    try:
        document = vim.eval('expand("<afile>:p")')

        if document is None:
            document = vim.eval('expand("%:p")')

        # print("file: ", document)

        if os.path.exists("/" + document):
            return "file://" + document

        return None
    except:
        return None



#######################################################################
# Activities related methods                                          #
#######################################################################

def kde_activities_Opened():
    pass
    wid = _getWindowId()
    document = _urlForCurrentDocument()

    if document is not None:
        KActivities.RegisterResourceEvent("vim", wid, document, KActivities.Event.Opened, 0)


def kde_activities_Closed():
    pass
    wid = _getWindowId()
    document = _urlForCurrentDocument()

    if document is not None:
        KActivities.RegisterResourceEvent("vim", wid, document, KActivities.Event.Closed, 0)


def kde_activities_FocussedIn():
    wid = _getWindowId()
    document = _urlForCurrentDocument()

    if document is not None:
        KActivities.RegisterResourceEvent("vim", wid, document, KActivities.Event.Opened, 0)

def kde_activities_FocussedOut():
    wid = _getWindowId()
    document = _urlForCurrentDocument()

    if document is not None:
        KActivities.RegisterResourceEvent("vim", wid, document, KActivities.Event.Closed, 0)

def kde_activities_Link():
    document = _urlForCurrentDocument()
    # print("linking...", document)

    if document is not None:
        KActivities.LinkResourceToActivity(document)

def kde_activities_Unlink():
    document = _urlForCurrentDocument()

    if document is not None:
        KActivities.UnlinkResourceFromActivity(document)

