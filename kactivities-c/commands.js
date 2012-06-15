

Components.utils.import("resource://gre/modules/ctypes.jsm");
let kactivities_Library = ctypes.open("libkactivities-c.so");

let kactivities_Version = kactivities_Library.declare("kactivities_Version", ctypes.default_abi, ctypes.int32_t);

// actDes().readString()

let kactivities_ActivityName    = kactivities_Library.declare("kactivities_ActivityName",
        ctypes.default_abi, ctypes.char.ptr, ctypes.char.ptr);
let kactivities_CurrentActivity = kactivities_Library.declare("kactivities_CurrentActivity",
        ctypes.default_abi, ctypes.char.ptr);
let kactivities_ListActivities  = kactivities_Library.declare("kactivities_ListActivities",
        ctypes.default_abi, ctypes.char.ptr);

let kactivities_LinkResourceToActivity = kactivities_Library.declare("kactivities_LinkResourceToActivity",
        ctypes.default_abi, ctypes.void_t, ctypes.char.ptr, ctypes.char.ptr);
let kactivities_UnlinkResourceFromActivity = kactivities_Library.declare("kactivities_UnlinkResourceFromActivity",
        ctypes.default_abi, ctypes.void_t, ctypes.char.ptr, ctypes.char.ptr);
let kactivities_IsResourceLinkedToActivity = kactivities_Library.declare("kactivities_IsResourceLinkedToActivity",
        ctypes.default_abi, ctypes.bool, ctypes.char.ptr, ctypes.char.ptr);
