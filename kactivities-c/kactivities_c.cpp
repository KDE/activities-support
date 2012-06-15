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

#define ka(Method) kactivities_##Method
#define KACTIVITIES_C_EXPORT    __attribute__ ((visibility("default")))
#define KACTIVITIES_C_NO_EXPORT __attribute__ ((visibility("hidden")))

#include <KActivities/Consumer>
#include <KActivities/Info>
#include <KActivities/ResourceInstance>

#include <map>
#include <memory>
#include <mutex>

#include "utils.h"

typedef std::unique_ptr<KActivities::ResourceInstance> ResourceInstancePtr;

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

    mutable std::mutex resourceInstanceMutex;
    unsigned int resourceInstanceLastIndex;
    std::map<uint32_t, ResourceInstancePtr> resourceInstances;

    uint32_t createResourceInstance(
            WId wid,
            const QString & application,
            const QString & resource = QString(),
            const QString & mimetype = QString(),
            const QString & title = QString()
        )
    {
        std::lock_guard<std::mutex> lock { resourceInstanceMutex };

        resourceInstanceLastIndex++;
        resourceInstances[resourceInstanceLastIndex] = make_unique<KActivities::ResourceInstance> (
                wid, resource, mimetype, title, KActivities::ResourceInstance::User, application
            );

        return resourceInstanceLastIndex;
    }

    void freeResourceInstance(uint32_t id)
    {
        std::lock_guard<std::mutex> lock { resourceInstanceMutex };
        resourceInstances.erase(id);
    }

    template <typename T>
    void callOnResourceInstance(uint32_t id, T function)
    {
        std::lock_guard<std::mutex> lock { resourceInstanceMutex };

        if (resourceInstances.count(id) > 0) {
            function(resourceInstances.at(id));
        }
    }

private:
    static
    KActivityC * s_instance;

    KActivityC() {}
    ~KActivityC() {}

};

KActivityC * KActivityC::s_instance = 0;


extern "C" {

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
    uint32_t ka(ResourceInstance_Create2)(WId wid, char * application)
    {
        return KActivityC::self()->createResourceInstance(
                wid,
                QString::fromUtf8(application)
            );
    }

    KACTIVITIES_C_EXPORT
    uint32_t ka(ResourceInstance_Create3)(WId wid, char * application, char * resource)
    {
        return KActivityC::self()->createResourceInstance(
                wid,
                QString::fromUtf8(application),
                QString::fromUtf8(resource)
            );
    }

    KACTIVITIES_C_EXPORT
    uint32_t ka(ResourceInstance_Create4)(WId wid, char * application, char * resource, char * mimetype)
    {
        return KActivityC::self()->createResourceInstance(
                wid,
                QString::fromUtf8(application),
                QString::fromUtf8(resource),
                QString::fromUtf8(mimetype)
            );
    }

    KACTIVITIES_C_EXPORT
    uint32_t ka(ResourceInstance_Create5)(WId wid, char * application, char * resource, char * mimetype, char * title)
    {
        return KActivityC::self()->createResourceInstance(
                wid,
                QString::fromUtf8(application),
                QString::fromUtf8(resource),
                QString::fromUtf8(mimetype),
                QString::fromUtf8(title)
            );
    }

    KACTIVITIES_C_EXPORT
    void ka(ResourceInstance_Free)(uint32_t id)
    {
        KActivityC::self()->freeResourceInstance(id);
    }

    #define CallOnResourceInstance(Method)                     \
        KActivityC::self()->callOnResourceInstance(resource,   \
            [=] (ResourceInstancePtr & _) { Method ;}          \
        )

    KACTIVITIES_C_EXPORT
    void ka(ResourceInstance_NotifyModified)(uint32_t resource)
    {
        CallOnResourceInstance( _->notifyModified() );
    }

    KACTIVITIES_C_EXPORT
    void ka(ResourceInstance_NotifyFocusedIn)(uint32_t resource)
    {
        CallOnResourceInstance( _->notifyFocusedIn() );
    }

    KACTIVITIES_C_EXPORT
    void ka(ResourceInstance_NotifyFocusedOut)(uint32_t resource)
    {
        CallOnResourceInstance( _->notifyFocusedOut() );
    }

    KACTIVITIES_C_EXPORT
    void ka(ResourceInstance_SetUri)(uint32_t resource, char * uri)
    {
        CallOnResourceInstance( _->setUri(QString::fromUtf8(uri)) );
    }

    KACTIVITIES_C_EXPORT
    void ka(ResourceInstance_SetMimeType)(uint32_t resource, char * mimetype)
    {
        CallOnResourceInstance( _->setMimetype(QString::fromUtf8(mimetype)) );
    }

    KACTIVITIES_C_EXPORT
    void ka(ResourceInstance_SetTitle)(uint32_t resource, char * title)
    {
        CallOnResourceInstance( _->setTitle(QString::fromUtf8(title)) );
    }

    #undef CallOnResourceInstance

    // Q_SIGNALS:
    // void currentActivityChanged(const QString & id);
    // void serviceStatusChanged(KActivities::Consumer::ServiceStatus status);
    // void activityAdded(const QString & id);
    // void activityRemoved(const QString & id);

}
