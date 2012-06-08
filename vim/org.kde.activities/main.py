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

kde_activities_resourceinstance = None

def kde_activities_ResourceInstance():
    global kde_activities_resourceinstance

    if kde_activities_resourceinstance is None:
        kde_activities_resourceinstance = KActivities.ResourceInstance(_getWindowId(), "gvim")

    return kde_activities_resourceinstance

def kde_activities_FocussedIn():
    document = _urlForCurrentDocument()

    if document is None:
        return;

    kde_activities_ResourceInstance().setUri(document)

def kde_activities_Link():
    document = _urlForCurrentDocument()

    if document is not None:
        KActivities.LinkResourceToActivity(document)

def kde_activities_Unlink():
    document = _urlForCurrentDocument()

    if document is not None:
        KActivities.UnlinkResourceFromActivity(document)

