import os
import Xlib
from Xlib import X,display,Xatom

display = Xlib.display.Display()
screen = display.screen()

def _processWindow(win, atom, processId, level = 0):
    result = set()

    # print win.get_wm_name(),
    response = win.get_full_property(atom, Xatom.CARDINAL);

    found = False

    # Testing whether the response was valid
    # and whether we found a proper process id
    if response != None:
        for pid in response.value:
            if pid == processId:
                result.add(win.id)
                found = True

    # If we have found the window, we don't
    # search its children
    if not found:
        for child in win.query_tree().children:
            result |= _processWindow(child, atom, processId, level + 1)

    return result

# Gets the window IDs that belong to the specified process
def getWindowIds(processId):

    root = screen.root;
    tree = root.query_tree();
    wins = tree.children;
    atom = display.intern_atom("_NET_WM_PID", 1);

    # recursively searches the window tree
    # for the one that has a desired pid
    result = set()

    for win in wins:
        result |= _processWindow(win, atom, processId)

    return result

# Gets the window IDs that belong to the current process
def getWindowIdsForCurrentProcess():
    return getWindowIds(os.getpid())

# winidspec = getWindowIds(5168)
# winidcurr = getWindowIdsForCurrentProcess()
# print winidspec, winidcurr

