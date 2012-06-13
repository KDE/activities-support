/*
 *   Copyright (C) 2012 Ivan Cukic <ivan.cukic(at)kde.org>
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License version 2,
 *   or (at your option) any later version, as published by the Free
 *   Software Foundation
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details
 *
 *   You should have received a copy of the GNU General Public
 *   License along with this program; if not, write to the
 *   Free Software Foundation, Inc.,
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#define ka(Method) kactivities##Method
#define KACTIVITIES_C_EXPORT    __attribute__ ((visibility("default")))
#define KACTIVITIES_C_NO_EXPORT __attribute__ ((visibility("hidden")))

#include <KActivities/Consumer>
#include <KActivities/Info>
#include <KActivities/ResourceInstance>

#include <memory>
#include <mutex>

class KACTIVITIES_C_NO_EXPORT KActivityC {
public:
    static
    KActivityC * self()
    {
        if (!s_instance) {
            s_instance = new KActivityC();
        }

        return s_instance;
    }

    static
    void deinit()
    {
        delete s_instance;
    }

    KActivities::Consumer activities;

    std::mutex resourceInstanceMutex;
    unsigned int resourceInstanceLastIndex;
    std::map < unsigned long, std::unique_ptr<ResourceInstance> > resourceInstances;

private:
    static
    KActivityC * s_instance;

    KActivityC() {}
    ~KActivityC() {}

};

KActivityC * KActivityC::s_instance = 0;


extern "C" {
    auto ka(name) = "KActivity C\0";

    KACTIVITIES_C_EXPORT
    int ka(Version)(void)
    {
        return 1;
    }

    KACTIVITIES_C_EXPORT
    void ka(Init)(void)
    {
        KActivityC::self();
    }

    KACTIVITIES_C_EXPORT
    void ka(Deinit)(void)
    {
        KActivityC::deinit();
    }

    KACTIVITIES_C_EXPORT
    const char * ka(CurrentActivity)(void)
    {
        return KActivityC::self()->activities.currentActivity().toUtf8().data();
    }

    KACTIVITIES_C_EXPORT
    const char * ka(ListActivities)(void)
    {
        return KActivityC::self()->activities.listActivities().join(",").toUtf8().data();
    }

    KACTIVITIES_C_EXPORT
    void ka(LinkResourceToActivity)(char * uri, char * activity)
    {
        // TODO
        Q_UNUSED(uri)
        Q_UNUSED(activity)
    }

    KACTIVITIES_C_EXPORT
    void ka(UnlinkResourceFromActivity)(char * uri, char * activity)
    {
        // TODO
        Q_UNUSED(uri)
        Q_UNUSED(activity)
    }

    KACTIVITIES_C_EXPORT
    bool ka(IsResourceLinkedToActivity)(char * uri, char * activity)
    {
        // TODO
        Q_UNUSED(uri)
        Q_UNUSED(activity)
        return true;
    }

    KACTIVITIES_C_EXPORT
    const char * ka(ActivityName)(char * activity)
    {
        return KActivities::Info::name(activity).toUtf8().data();
    }

    KACTIVITIES_C_EXPORT
    unsigned long ka(ResourceInstance_Create2)(WId wid, char * application)
    {
        return 0;
    }

    KACTIVITIES_C_EXPORT
    unsigned long ka(ResourceInstance_Create3)(WId wid, char * application, char * resource)
    {
        return 0;
    }

    KACTIVITIES_C_EXPORT
    unsigned long ka(ResourceInstance_Create4)(WId wid, char * application, char * resource, char * mimetype)
    {
        return 0;
    }

    KACTIVITIES_C_EXPORT
    unsigned long ka(ResourceInstance_Create5)(WId wid, char * application, char * resource, char * mimetype, char * title)
    {
        return 0;
    }

    KACTIVITIES_C_EXPORT
    void ka(ResourceInstance_NotifyModified)(unsigned long resoource)
    {
    }

    KACTIVITIES_C_EXPORT
    void ka(ResourceInstance_NotifyFocussedIn)(unsigned long resoource)
    {
    }

    KACTIVITIES_C_EXPORT
    void ka(ResourceInstance_NotifyFocussedOut)(unsigned long resoource)
    {
    }

    KACTIVITIES_C_EXPORT
    void ka(ResourceInstance_SetUri)(unsigned long resoource, char * uri)
    {
    }

    KACTIVITIES_C_EXPORT
    void ka(ResourceInstance_SetMimeType)(unsigned long resoource, char * mimetype)
    {
    }

    KACTIVITIES_C_EXPORT
    void ka(ResourceInstance_SetTitle)(unsigned long resoource, char * title)
    {
    }


    // Q_SIGNALS:
    // void currentActivityChanged(const QString & id);
    // void serviceStatusChanged(KActivities::Consumer::ServiceStatus status);
    // void activityAdded(const QString & id);
    // void activityRemoved(const QString & id);

}
