#ifndef TIMEREVENT_H
# define TIMEREVENT_H

# include "Task.h"

namespace Timer {
    typedef unsigned long TimeStamp;

    typedef enum {
        Started,
        Stopped
    } TimerEventType;

    class Event
    {
    public:
        explicit Event(Task::TaskPtr task, Timer::TimerEventType eventType, TimeStamp startedTime, TimeStamp stopedTime = (TimeStamp)-1);

        const TimeStamp & getStartedTimeStamp() const;
        const TimeStamp & getStoppedTimeStamp() const;
        const Task * getTask() const;
        TimerEventType getEventType() const;

    private:
        Task::TaskPtr task;
        Timer::TimerEventType eventType;
        TimeStamp startedTimeStamp;
        TimeStamp stoppedTimeStamp;
    };
}


#endif // TIMEREVENT_H
