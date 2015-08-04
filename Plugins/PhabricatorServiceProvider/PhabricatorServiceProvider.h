#ifndef PHABRICATORSERVICEPPROVIDER_H
# define PHABRICATORSERVICEPPROVIDER_H

# include "../../include/IServiceProvider.hpp"

namespace ServiceProvider {
    class Phabricator: public Interface
    {
    public:
        Phabricator();

        virtual bool init();
        virtual bool cleanup();

        virtual bool setTasks(TaskListPtr);
        virtual TaskListPtr getTasks();

        virtual bool setSettings(SettingListPtr);
        virtual SettingListPtr getSettings();

        virtual bool timerStarted(Timer::EventPtr);
        virtual bool timerStopped(Timer::EventPtr);
    };
}

#endif // PHABRICATORSERVICEPPROVIDER_H
