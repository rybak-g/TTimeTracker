#ifndef QSERVICEPROVIDER
# define QSERVICEPROVIDER

# include <QQuickItem>
# include "IServiceProvider.hpp"

namespace ServiceProvider {

    class QmlWrapper: public QQuickItem {
        Q_OBJECT

    public:
        explicit QmlWrapper(Interface *sp, QQuickItem *root = 0);
        Interface * getServiceProvider();
        QmlWrapper(const QmlWrapper & other);
        QmlWrapper &operator=(const QmlWrapper & other);
        virtual ~QmlWrapper();

    public:
        bool init();
        bool cleanup();

        QJsonArray getTasks();

        bool setSettings(QJsonArray);
        QJsonArray getSettings();

        bool timerStarted(QJsonObject);
        bool timerStopped(QJsonObject);

    private:
        Interface *_sp;
    };
}

#endif // QSERVICEPROVIDER
