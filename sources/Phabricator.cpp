#include <QJsonDocument>
#include "Phabricator.h"

static const QString taks = "{\"result\":[{\"authorPHID\":\"PHID-USER-mchcwv7gcw25vnfpk5wz\",\"auxiliary\":[],\"ccPHIDs\":[\"PHID-USER-enhmg74lh7xuxfsskonn\",\"PHID-USER-mchcwv7gcw25vnfpk5wz\"],\"dateCreated\":\"1412435370\",\"dateModified\":\"1412435431\",\"dependsOnTaskPHIDs\":[],\"description\":\"COUCOCU\",\"id\":\"8\",\"isClosed\":true,\"objectName\":\"T8\",\"ownerPHID\":\"PHID-USER-mchcwv7gcw25vnfpk5wz\",\"phid\":\"PHID-TASK-dekomf252cyt6tay2ans\",\"priority\":\"Wishlist\",\"priorityColor\":\"sky\",\"projectPHIDs\":[\"PHID-PROJ-n4h6ccsinm3fefzfd2yg\"],\"status\":\"resolved\",\"statusName\":\"Resolved\",\"title\":\"Read document\",\"uri\":\"https://phabricator.episeed.com/T8\"}]}";

namespace Providers
{
    namespace Phabricator
    {
        ServiceProvider::ServiceProvider()
        {
            m_settings.setUserTokenApi("");
            m_settings.setUserPhid("PHID-USER-cwgpa2lcuroz4ejzol4p");
            m_settings.setPhabricatorHost("");
        }

        bool ServiceProvider::init()
        {
            return true;
        }

        bool ServiceProvider::cleanup()
        {
            return true;
        }

        void ServiceProvider::onTaskListReceived(QByteArray & response)
        {
            QJsonDocument r = QJsonDocument::fromJson(response);
            QJsonObject & o = r.object();
            QJsonObject & result = o["result"].toObject();

            m_currentTasks = QJsonArray();
            foreach(const QString & key, result.keys()) {
                m_currentTasks.append(result[key]);
            }
            emit currentTasksChanged();
        }

        void ServiceProvider::onCurrentUserInformationsReceived(QByteArray & response)
        {
            QJsonDocument r = QJsonDocument::fromJson(response);
            QJsonObject & o = r.object();
            QJsonObject & result = o["result"].toObject();

            m_settings.setUserPhid(result["phid"].toString());
            emit currentUserChanged();
        }

        void ServiceProvider::onReadyRead(QNetworkReply * nr, int type)
        {
            switch (type) {
                case PhabricatorTasksResponse: onTaskListReceived(nr->readAll()); break;
                case PhabricatorUserInfosResponse: onCurrentUserInformationsReceived(nr->readAll()); break;
                default: break;
            }
            nr->deleteLater();
        }

        void ServiceProvider::onError(QNetworkReply::NetworkError e, int)
        {
            qCritical() << e;
            emit error(QString::number(e));
        }

        void ServiceProvider::onSslErrors(QNetworkReply * r, const QList<QSslError> & e)
        {
            qCritical() << e;
            if (m_settings.ignoreSslErrors()) {
                r->ignoreSslErrors();
            }
        }

        void ServiceProvider::getUserInfosAsync()
        {
            QNetworkReply * r = m_manager.get(QNetworkRequest(m_settings.whoAmIUri()));

            connect(r, &QNetworkReply::downloadProgress, [this, r](qint64 bytesReceived, qint64 bytesTotal) {
                if (bytesTotal == bytesReceived && bytesReceived != 0) {
                    this->onReadyRead(r, ServiceProvider::PhabricatorUserInfosResponse);
                }
            });
            connect(r, static_cast<void (QNetworkReply::*)(QNetworkReply::NetworkError)>(&QNetworkReply::error), [this](QNetworkReply::NetworkError e) {
                this->onError(e, ServiceProvider::PhabricatorUserInfosResponse);
            });
            connect(r, &QNetworkReply::sslErrors, [this, r](const QList<QSslError> & e) {
                this->onSslErrors(r, e);
            });
        }

        void ServiceProvider::getTasksAsync()
        {
            QNetworkReply * r = m_manager.get(QNetworkRequest(m_settings.getTaskUri()));

            connect(r, &QNetworkReply::downloadProgress, [this, r](qint64 bytesReceived, qint64 bytesTotal) {
                if (bytesTotal == bytesReceived && bytesReceived != 0) {
                    this->onReadyRead(r, ServiceProvider::PhabricatorTasksResponse);
                }
            });
            connect(r, static_cast<void (QNetworkReply::*)(QNetworkReply::NetworkError)>(&QNetworkReply::error), [this](QNetworkReply::NetworkError e) {
                this->onError(e, ServiceProvider::PhabricatorTasksResponse);
            });
            connect(r, &QNetworkReply::sslErrors, [this, r](const QList<QSslError> & e) {
                this->onSslErrors(r, e);
            });
        }

        bool ServiceProvider::timerStarted()
        {
            return true;
        }

        bool ServiceProvider::timerStopped()
        {
            return true;
        }
    }
}
