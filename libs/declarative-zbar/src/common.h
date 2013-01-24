#ifndef COMMON_H
#define COMMON_H

#ifndef WANT_DEBUG
#define TRACE
#else
#include <QDebug>
#define TRACE qDebug()<<QString("[%1] %2(): %3").arg(__FILE__).arg(__func__).arg(__LINE__);
#endif

#include <QDebug>
#define DEBUGX qDebug() << QDateTime::currentDateTime().toString("[hh:mm:ss:zzz] ")

#endif // COMMON_H
