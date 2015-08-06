
#include <iostream>
#include <QJsonArray>
#include <QJsonObject>
#include "QServiceProvider.h"

namespace ServiceProvider {

    QmlWrapper::QmlWrapper(QQuickItem *root)
        : QQuickItem(root), _sp(sp) {
        if (_sp) {
            throw std::runtime_error("the service profider interface provided to the qmlwrapper cannot be null");
        }
        _manager.loadFromDir((QCoreApplication::applicationDirPath()+"/plugins").toStdString());
        init();
    }

    QmlWrapper::~QmlWrapper() {
        cleanup();
    }

    Interface * QmlWrapper::getServiceProvider() {
        return _sp;
    }

    QmlWrapper::QmlWrapper(const QmlWrapper & other)
        : QQuickItem(other.parentItem()){
        this->_sp = other._sp;
    }

    QmlWrapper & QmlWrapper::operator=(const QmlWrapper & other) {
        this->_sp = other._sp;
        return *this;
    }

    bool QmlWrapper::init() {
        return this->_sp->init();
    }

    bool QmlWrapper::cleanup() {
        return this->_sp->cleanup();
    }

    QJsonArray QmlWrapper::getTasks() {
        Interface::TaskListPtr taskList = _sp->getTasks();
        QJsonArray qmlList;

        for (Task task: *taskList) {
            QJsonObject qmlTask;
            qmlTask["name"] = QJsonValue(task.getName());
            qmlList.push_back(qmlTask);
            std::cout << task.getName().toStdString() << std::endl;
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

}

