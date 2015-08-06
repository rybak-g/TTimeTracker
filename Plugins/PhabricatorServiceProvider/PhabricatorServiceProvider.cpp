#include "PhabricatorServiceProvider.h"

namespace ServiceProvider {

    Phabricator::Phabricator()
    {
    }

    bool Phabricator::init() {
        return true;
    }

    bool Phabricator::cleanup() {
        return true;
    }

    bool Phabricator::setTasks(TaskListPtr) {
        return true;
    }

    Phabricator::TaskListPtr Phabricator::getTasks() {
        TaskListPtr tlp(new TaskList { Task("3565", "T3565", "Task 3565 Description"), Task("3615", "T3615", "Task 3615 Description") });
        return tlp;
    }

    bool Phabricator::setSettings(Phabricator::SettingListPtr) {
        return true;
    }

    Phabricator::SettingListPtr Phabricator::getSettings() {
        return SettingListPtr();
    }

    bool Phabricator::timerStarted(Timer::EventPtr) {
        return true;
    }

    bool Phabricator::timerStopped(Timer::EventPtr) {
        return true;
    }

}
