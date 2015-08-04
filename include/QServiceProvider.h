#ifndef QSERVICEPROVIDER
# define QSERVICEPROVIDER

# include <QQuickItem>
# include "IServiceProvider.hpp"

namespace ServiceProvider {

    class QmlWrapper: public QQuickItem {
        Q_OBJECT

    public:
        explicit QmlWrapper(QQuickItem *root = 0) : QQuickItem(root) { }

    private:
        Interface *_sp;

    };
}

#endif // QSERVICEPROVIDER
