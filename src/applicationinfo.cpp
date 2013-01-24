#include <QDeclarativeView>
#include <QFocusEvent>
#include <QApplication>
#include <QDebug>

#include "applicationinfo.h"


ApplicationInfo::ApplicationInfo(QApplication *app):
    m_app(app)
{
    connect(m_app, SIGNAL(focusChanged(QWidget*,QWidget*)), this, SLOT(onFocusChange(QWidget*,QWidget*)));
}


void ApplicationInfo::onFocusChange(QWidget *old, QWidget *now)
{
    if(now && !old){
        emit focusGot();
    }
    if(old && !now){
        emit focusLost();
    }
}

