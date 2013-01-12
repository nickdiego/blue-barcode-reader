#include <QtGui/QApplication>

#include "declarativeview.h"

int main(int argc, char **argv)
{
    QApplication application(argc, argv);

    DeclarativeView view;

    view.load();

    return application.exec();
}
