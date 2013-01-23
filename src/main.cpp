#include <QtGui/QApplication>

#include "declarativeview.h"

int main(int argc, char **argv)
{
    QScopedPointer<QApplication> application(new QApplication(argc, argv));
    QScopedPointer<DeclarativeView> view(new DeclarativeView);

    view->load();
    return application->exec();
}
