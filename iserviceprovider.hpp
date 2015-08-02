#ifndef ISERVICEPROVIDER_HPP
# define ISERVICEPROVIDER_HPP

# include <string>
# include <list>
# include <memory>

# include "Task.h"
# include "StringSetting.h"

class IServiceProvider {
public:
    typedef Settings::StringSetting Setting;
    typedef std::unique_ptr<Setting> SettingPtr;
    typedef std::list<Setting> SettingList;
    typedef std::unique_ptr<SettingsList> SettingListPtr;
    typedef std::list<Task> TaskList;
    typedef std::unique_ptr<TaskList> TaskListPtr;

public:
    virtual ~IServiceProvider() {}

public:
    virtual bool init() = 0;
    virtual bool cleanup() = 0;

    virtual bool setTasks(std::unique_ptr<TaskList>) = 0;
    virtual std::unique_ptr<TaskList> getTasks() = 0;

    virtual bool setSettings(SettingListPtr) = 0;
    virtual std::unique_ptr<SettingList> getSettings() = 0;

    virtual bool timerStarted() = 0;
};

#endif // ISERVICEPROVIDER_HPP

