
#include <QDebug>
#include <QJsonArray>
#include <QJsonObject>

#include "QmlWrapper.h"
#include "Phabricator.h"

namespace Providers {

    QmlWrapper::QmlWrapper(QObject *root)
        : QObject(root)
        , _sp(0)
        , _qmlList(nullptr)
    {
    }

    QmlWrapper::QmlWrapper(const QmlWrapper & other)
        : QObject(other.parent())
    {
        this->_sp = other._sp;
        setPluginDirectory(other._pluginDirectory);
    }

    QmlWrapper::~QmlWrapper()
    {
        _manager.clear();
    }

    Interface * QmlWrapper::getServiceProvider()
    {
        return _sp;
    }

    QmlWrapper & QmlWrapper::operator=(const QmlWrapper & other)
    {
        this->_sp = other._sp;
        setPluginDirectory(other._pluginDirectory);
        return *this;
    }

    bool QmlWrapper::init()
    {
        if (this->_sp) {
            return this->_sp->init();
        }
        return true;
    }

    bool QmlWrapper::cleanup()
    {
        if (this->_sp) {
            return this->_sp->cleanup();
        }
        return true;
    }

    QJsonArray QmlWrapper::getTasks()
    {
        QJsonArray qmlList;
        if (this->_sp) {
            Interface::TaskListPtr taskList = _sp->getTasks();

            for (Task task: *taskList) {
                QJsonObject qmlTask;
                qmlTask["name"] = QJsonValue(task.getName());
                qmlList.push_back(qmlTask);
                qDebug() << task.getName();
            }
        }
        return qmlList;
    }

    void QmlWrapper::onTaskListReady(Interface::TaskListPtr p) {
        Q_UNUSED(p);
        qDebug() << "onTaskListReady";
        if (_qmlList) {
            delete _qmlList;
            _qmlList = new QJsonArray;
        }
        for (Task task: *p) {
            QJsonObject qmlTask;
            qmlTask["name"] = QJsonValue(task.getName());
            _qmlList->append(qmlTask);
            qDebug() << task.getName();
        }
        emit taskListChanged();
    }

    void QmlWrapper::getTasksAsync() {
        if (_sp) {
            qDebug("calling async tasks getter");
            _sp->getTasksAsync(this);
        }
    }

    bool QmlWrapper::setSettings(QJsonArray) {
        return true;
    }

    QJsonArray QmlWrapper::getSettings() {
        return QJsonArray();
    }

    bool QmlWrapper::timerStarted(QJsonObject) {
        return true;
    }

    bool QmlWrapper::timerStopped(QJsonObject) {
        return true;
    }

    const QString & QmlWrapper::getPluginDirectory() const {
        return this->_pluginDirectory;
    }

    bool QmlWrapper::loadServiceProvider(const QString & /* providerId */) {
//        if (_sp) {
//            _sp->cleanup();
//        }
//        if (!(_sp = _manager.getInstance<ServiceProvider::Interface>(providerId.toStdString().c_str()))) {
//            return false;
//        }
        return true;
    }

    bool QmlWrapper::setPluginDirectory(const QString & path) {
        qDebug() << "setPluginDirectory(): " << path;
        if (_pluginDirectory != path) {
            this->_pluginDirectory = path;
            emit pluginDirectoryChanged();
        }
        return true;
    }

    bool QmlWrapper::refreshPluginList() {
        qDebug() << "refreshPluginList()";
        if (this->_sp) {
            _sp->cleanup();
        }
        _manager.clear();
        if (!_manager.loadFromDir(this->_pluginDirectory.toStdString())) {
            return false;
        }
        return true;
    }
}

