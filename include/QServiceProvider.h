#ifndef QSERVICEPROVIDER
# define QSERVICEPROVIDER

# include <QJsonArray>
# include <QJsonObject>

# include "IServiceProvider.hpp"
# include "DlManager.hpp"

namespace ServiceProvider {

    class QmlWrapper: public QObject {
        Q_OBJECT

        Q_PROPERTY(QString pluginDirectory READ getPluginDirectory WRITE setPluginDirectory NOTIFY pluginDirectoryChanged)

    public:
        explicit QmlWrapper(QObject *root = 0);
        QmlWrapper(const QmlWrapper & other);
        QmlWrapper &operator=(const QmlWrapper & other);
        virtual ~QmlWrapper();

    public:
        bool init();
        bool cleanup();

        Interface * getServiceProvider();
        bool setPluginDirectory(const QString & path);
        const QString & getPluginDirectory() const;
        Q_INVOKABLE QJsonArray getTasks();
        Q_INVOKABLE void getTasksAsync();
        Q_INVOKABLE bool setSettings(QJsonArray);
        Q_INVOKABLE QJsonArray getSettings();
        Q_INVOKABLE bool timerStarted(QJsonObject);
        Q_INVOKABLE bool timerStopped(QJsonObject);
        Q_INVOKABLE bool loadServiceProvider(const QString &);
        Q_INVOKABLE bool refreshPluginList();

    public slots:
        void onTaskListReady(Interface::TaskListPtr);

    signals:
        void taskListChanged(void);
        void pluginDirectoryChanged(void);
        void pluginLoadedSuccessfully(void);
        void errorOccured(const QString &);

    private:
        Interface *_sp;
        DlManager<std::string, Interface> _manager;
        QString _pluginDirectory;
        QString _lastError;
        QJsonArray * _qmlList;
    };
}

#endif // QSERVICEPROVIDER
