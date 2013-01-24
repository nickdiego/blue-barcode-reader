#include <QtGui/QApplication>

#ifdef HARMATTAN_BOOSTER
#include <MDeclarativeCache>
#endif

#include "declarativeview.h"
#include "applicationinfo.h"

QApplication *createApplication(int &argc, char **argv)
{
#ifdef HARMATTAN_BOOSTER
    return MDeclarativeCache::qApplication(argc, argv);
#else
    return new QApplication(argc, argv);
#endif
}

Q_DECL_EXPORT int main(int argc, char **argv)
{
    QScopedPointer<QApplication> application(createApplication(argc, argv));
    ApplicationInfo appInfo(application.data());

    QScopedPointer<DeclarativeView> view(new DeclarativeView(&appInfo));

    view->load();
    return application->exec();
}
