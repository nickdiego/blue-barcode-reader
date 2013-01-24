#ifndef APPLICATIONINFO_H
#define APPLICATIONINFO_H

#include <QObject>

class QApplication;
class QWidget;

class ApplicationInfo: public QObject
{
    Q_OBJECT
public:
    explicit ApplicationInfo(QApplication *app = 0);

signals:
    void focusGot();
    void focusLost();

private slots:
    void onFocusChange(QWidget *old, QWidget *now);

private:
    QApplication *m_app;

};

#endif // APPLICATIONINFO_H

