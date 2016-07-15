#ifndef PHABRICATOR_SETTINGS_H
# define PHABRICATOR_SETTINGS_H

# include <QString>
# include <QUrl>

namespace Providers
{
    namespace Phabricator
    {
        class Settings
        {
        public:
            Settings(): m_userTokenApi(""), m_phabricatorHost(""), m_ignoreSslErrors(true) {}
            ~Settings() {}

        public:
            const QString & userTokenApi() const { return m_userTokenApi; }
            const QString & phabricatorHost() const { return m_phabricatorHost; }
            const QString & userPhid() const { return m_userPhid; }
            bool ignoreSslErrors() const {return m_ignoreSslErrors; }

        public:
            const QUrl & getTaskUri() const { return m_getTasksUri; }
            const QUrl & whoAmIUri() const { return m_whoAmIUri; }
            const QUrl & startTimerUri() const { return m_startTimerUri; }
            const QUrl & stopTimerUri() const { return m_stopTimerUri; }

        public:
            void setUserTokenApi(const QString & userToken)
            {
                m_userTokenApi = userToken;
                updateUris();
            }
            void setPhabricatorHost(const QString & host)
            {
                m_phabricatorHost = host;
                updateUris();
            }
            void ignoreSslErrors(bool ignore)
            { m_ignoreSslErrors = ignore; }

            void setUserPhid(const QString &userPhid)
            {
                m_userPhid = userPhid;
                updateGetTasksUri();
            }

        protected:
            void updateUris()
            {
                updateGetTasksUri();
                updateStartTimerUri();
                updateStopTimerUri();
                updateWhoAmIUri();
            }

            void updateGetTasksUri()
            { m_getTasksUri = m_phabricatorHost + "/api/maniphest.query?ccPHIDs[0]=" + m_userPhid + "&status=status-open&order=order-modified&api.token=" + m_userTokenApi; }

            void updateStartTimerUri()
            { m_startTimerUri = m_phabricatorHost + "/api/maniphest.query?api.token=" + m_userTokenApi; }

            void updateStopTimerUri()
            { m_stopTimerUri = m_phabricatorHost + "/api/maniphest.query?api.token=" + m_userTokenApi; }

            void updateWhoAmIUri()
            { m_whoAmIUri = m_phabricatorHost + "/api/user.whoami?api.token=" + m_userTokenApi; }

        private:
            QString m_userTokenApi;
            QString m_phabricatorHost;
            QString m_userPhid;
            bool m_ignoreSslErrors;

        private:
            QUrl m_getTasksUri;
            QUrl m_startTimerUri;
            QUrl m_stopTimerUri;
            QUrl m_whoAmIUri;
        };
    }
}

#endif // SETTINGS_H
