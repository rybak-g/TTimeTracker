#ifndef PHABRICATORSERVICEPPROVIDER_H
# define PHABRICATORSERVICEPPROVIDER_H

# include <QNetworkAccessManager>
# include <QNetworkReply>
# include "QmlWrapper.h"
# include "PhabricatorSettings.h"

namespace Providers
{
    namespace Phabricator
    {
        class ServiceProvider: public QObject
        {
            Q_OBJECT

            Q_PROPERTY(QJsonArray currentTasks READ currentTasks NOTIFY currentTasksChanged)
            enum ReponseType {
                PhabricatorTasksResponse,
                PhabricatorUserInfosResponse,
                PhabricatorTimerStartResponse,
                PhabricatorTimerStopResponse
            };
            Q_ENUMS(ResponseType)

        public:
            ServiceProvider();

        public:
            bool init();
            bool cleanup();

        public:
            Q_INVOKABLE void getTasksAsync();
            Q_INVOKABLE void getUserInfosAsync();
            Q_INVOKABLE bool timerStarted();
            Q_INVOKABLE bool timerStopped();

        public:
            const QJsonArray & currentTasks(void) const { return m_currentTasks; }

        protected:
            void onTaskListReceived(QByteArray &);
            void onCurrentUserInformationsReceived(QByteArray &);

        protected:
            void onReadyRead(QNetworkReply *, int);
            void onError(QNetworkReply::NetworkError, int);
            void onSslErrors(QNetworkReply *, const QList<QSslError> &);

        signals:
            void taskListReady(QVariant tasks);
            void currentTasksChanged();
            void currentUserChanged();
            void error(QString error);

        private:
            Phabricator::Settings m_settings;
            QNetworkAccessManager m_manager;
            QString m_currentUserPHID;
            QJsonArray m_currentTasks;
        };
    }
}

#endif // PHABRICATORSERVICEPPROVIDER_H
