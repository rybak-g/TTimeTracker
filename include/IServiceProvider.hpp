#ifndef ISERVICEPROVIDER_HPP
# define ISERVICEPROVIDER_HPP

# include <string>
# include <list>
# include <memory>

# include "Task.h"
# include "StringSetting.h"
# include "TimerEvent.h"

namespace ServiceProvider {
    class Interface {
    public:
        typedef Settings::StringSetting Setting;
        typedef std::unique_ptr<Setting> SettingPtr;
        typedef std::list<Setting> SettingList;
        typedef std::unique_ptr<SettingList> SettingListPtr;
        typedef std::list<Task> TaskList;
        typedef std::unique_ptr<TaskList> TaskListPtr;

    public:
        virtual ~Interface() {}

    public:
        virtual bool init() = 0;
        virtual bool cleanup() = 0;

        virtual bool setTasks(TaskListPtr) = 0;
        virtual TaskListPtr getTasks() = 0;

        virtual bool setSettings(SettingListPtr) = 0;
        virtual SettingListPtr getSettings() = 0;

        virtual bool timerStarted(Timer::EventPtr) = 0;
        virtual bool timerStopped(Timer::EventPtr) = 0;
    };
}

#endif // ISERVICEPROVIDER_HPP

