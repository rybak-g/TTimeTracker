
#include <iostream>
#include <QJsonArray>
#include <QJsonObject>
#include "QServiceProvider.h"

namespace ServiceProvider {

    QmlWrapper::QmlWrapper(QQuickItem *root)
        : QQuickItem(root), _sp(0) {
    }

    QmlWrapper::QmlWrapper(const QmlWrapper & other)
        : QQuickItem(other.parentItem()){
        this->_sp = other._sp;
        setPluginDirectory(other._pluginDirectory);
    }

    QmlWrapper::~QmlWrapper() {
        _manager.clear();
    }

    Interface * QmlWrapper::getServiceProvider() {
        return _sp;
    }

    QmlWrapper & QmlWrapper::operator=(const QmlWrapper & other) {
        this->_sp = other._sp;
        setPluginDirectory(other._pluginDirectory);
        return *this;
    }

    bool QmlWrapper::init() {
        if (this->_sp) {
            return this->_sp->init();
        }
        return true;
    }

    bool QmlWrapper::cleanup() {
        if (this->_sp) {
            return this->_sp->cleanup();
        }
        return true;
    }

    QJsonArray QmlWrapper::getTasks() {
        QJsonArray qmlList;
        if (this->_sp) {
            Interface::TaskListPtr taskList = _sp->getTasks();

            for (Task task: *taskList) {
                QJsonObject qmlTask;
                qmlTask["name"] = QJsonValue(task.getName());
                qmlList.push_back(qmlTask);
                std::cout << task.getName().toStdString() << std::endl;
            }
        }
        return qmlList;
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

    bool QmlWrapper::loadServiceProvider(const QString & providerId) {
        if (_sp) {
            _sp->cleanup();
        }
        if (!(_sp = _manager.getInstance<ServiceProvider::Interface>(providerId.toStdString().c_str()))) {
            return false;
        }
        return true;
    }

    bool QmlWrapper::setPluginDirectory(const QString & path) {
        if (_pluginDirectory != path) {
            this->_pluginDirectory = path;
            qDebug() << "setPluginDirectory(): " << path;
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
