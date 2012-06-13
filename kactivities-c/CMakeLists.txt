project(kactivities-c)

FIND_PACKAGE(KDE4 REQUIRED)
FIND_PACKAGE(KActivities 6.0.0 REQUIRED)

INCLUDE(KDE4Defaults)
INCLUDE(MacroLibrary)
INCLUDE(MacroOptionalAddSubdirectory)
INCLUDE(FindPackageHandleStandardArgs)

ADD_DEFINITIONS(
    ${QT_DEFINITIONS}
    ${QT_QTDBUS_DEFINITIONS}
    ${KDE4_DEFINITIONS}
    "-std=c++0x"
    )

INCLUDE_DIRECTORIES(
    ${QDBUS_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}
    ${KDE4_INCLUDES}
    ${KACTIVITIES_INCLUDE_DIRS}
    )

include_directories(
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}
    ${KDE4_INCLUDES}
    ${KDE4_KIO_INCLUDES}
    )

set(kactivities_c_LIB_SRCS
    kactivities_c.cpp
    )

# qt4_add_dbus_interface(
#     kactivities_LIB_SRCS
#
#     ../service/org.kde.ActivityManager.xml
#     activitymanager_interface
# )

kde4_add_library(
    kactivities-c SHARED
    ${kactivities_c_LIB_SRCS}
    )

set_target_properties(
   kactivities-c
   PROPERTIES
   VERSION "0.0.1"
   SOVERSION "1"
   )

target_link_libraries(
    kactivities-c
    ${KDE4_KDECORE_LIBS}
    ${KACTIVITIES_LIBRARY}
    )

install(
    TARGETS kactivities-c
    ${INSTALL_TARGETS_DEFAULT_ARGS}
    )

