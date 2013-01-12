#ifndef DECLARATIVEVIEW_H
#define DECLARATIVEVIEW_H

#include <QtDeclarative/QDeclarativeView>

#include "settings.h"

class DeclarativeView : public QDeclarativeView
{
    Q_OBJECT

public:
    DeclarativeView(QWidget *parent = 0);

    void load();

#if defined(Q_OS_SYMBIAN)
private slots:
    void changeOrientation();
#endif

private:
    void registerTypes();

    Settings m_settings;
};

#endif
