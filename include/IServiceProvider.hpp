#ifndef ISERVICEPROVIDER_HPP
# define ISERVICEPROVIDER_HPP

# include <string>
# include <list>
# include <memory>
# include <QObject>

# include "Task.h"
# include "StringSetting.h"
# include "TimerEvent.h"

namespace ServiceProvider {
    class QmlWrapper;

    class Interface {

    public:
        typedef Settings::StringSetting Setting;
        typedef std::shared_ptr<Setting> SettingPtr;
        typedef std::list<Setting> SettingList;
        typedef std::shared_ptr<SettingList> SettingListPtr;
        typedef std::list<Task> TaskList;
        typedef std::shared_ptr<TaskList> TaskListPtr;

        typedef void (*getTasksCallback)(TaskListPtr);

    public:
        virtual ~Interface() {}

    public:
        virtual bool init() = 0;
        virtual bool cleanup() = 0;

        virtual bool setTasks(TaskListPtr) = 0;
        virtual TaskListPtr getTasks() = 0;
        virtual void getTasksAsync(ServiceProvider::QmlWrapper *) = 0;

        virtual bool setSettings(SettingListPtr) = 0;
        virtual SettingListPtr getSettings() = 0;

        virtual bool timerStarted(Timer::EventPtr) = 0;
        virtual bool timerStopped(Timer::EventPtr) = 0;
    };
}

#endif // ISERVICEPROVIDER_HPP

