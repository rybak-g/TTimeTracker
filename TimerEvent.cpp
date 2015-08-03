#include "TimerEvent.h"

namespace Timer {

    Event::Event(Task::TaskPtr task, Timer::TimerEventType eventType, const TimeStamp & startedTime, const TimeStamp & stopedTime)
        : task(task), eventType(eventType), startedTimeStamp(startedTime), stoppedTimeStamp(stopedTime) {

    }

    const TimeStamp & Event::getStartedTimeStamp() const {
        return this->startedTimeStamp;
    }

    const TimeStamp & Event::getStoppedTimeStamp() const {
        return this-> stoppedTimeStamp;
    }

    TimerEventType Event::getEventType() const {
        return this->eventType;
    }

    const Task::TaskPtr getTask() const {
        return this->task;
    }
}

