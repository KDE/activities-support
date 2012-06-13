
Components.utils.import("resource://gre/modules/ctypes.jsm");
let library = ctypes.open("libkactivities-c.so");

let version = library.declare("kactivitiesVersion", ctypes.default_abi, ctypes.int32_t);

// actDes().readString()

let activityName    = library.declare("kactivitiesActivityName", ctypes.default_abi, ctypes.char.ptr, ctypes.char.ptr);
let currentActivity = library.declare("kactivitiesCurrentActivity", ctypes.default_abi, ctypes.char.ptr);
let listActivities  = library.declare("kactivitiesListActivities",  ctypes.default_abi, ctypes.char.ptr);

let linkResourceToActivity = library.declare("kactivitiesLinkResourceToActivity",
        ctypes.default_abi, ctypes.void_t, ctypes.char.ptr, ctypes.char.ptr);
let unlinkResourceFromActivity = library.declare("kactivitiesUnlinkResourceFromActivity",
        ctypes.default_abi, ctypes.void_t, ctypes.char.ptr, ctypes.char.ptr);
let isResourceLinkedToActivity = library.declare("kactivitiesIsResourceLinkedToActivity",
        ctypes.default_abi, ctypes.bool, ctypes.char.ptr, ctypes.char.ptr);
