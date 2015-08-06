#ifndef QSERVICEPROVIDER
# define QSERVICEPROVIDER

# include <QQuickItem>
# include "IServiceProvider.hpp"
# include "DlManager.hpp"

namespace ServiceProvider {

    class QmlWrapper: public QQuickItem {
        Q_OBJECT

        Q_PROPERTY(QString pluginDirectory READ getPluginDirectory WRITE setPluginDirectory NOTIFY pluginDirectoryChanged)

    public:
        explicit QmlWrapper(QQuickItem *root = 0);
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

        bool setPluginDirectory(const QString & path);
        const QString & getPluginDirectory() const;

        bool loadServiceProvider(const QString &);
        bool loadServiceProviders();

        Q_INVOKABLE bool refreshPluginList();

    signals:
        void pluginDirectoryChanged(void);
        void pluginLoadedSuccessfully(void);
        void errorOccured(const QString &);

    private:
        Interface *_sp;
        DlManager<const char *, Interface> _manager;
        QString _pluginDirectory;
        QString _lastError;
    };
}

#endif // QSERVICEPROVIDER
