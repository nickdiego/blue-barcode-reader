#ifndef CODEREADERTHREAD_H
#define CODEREADERTHREAD_H

#include <QtCore/QThread>
#include <QtCore/QMutex>
#include <QtCore/QWaitCondition>
#include <QtGui/QImage>

class CodeReaderThread : public QThread
{
    Q_OBJECT

public:
    CodeReaderThread(QObject *parent = 0);
    ~CodeReaderThread();

    void checkForCodes(const QImage &image);

    void run();

signals:
    void processingFinished(const QImage &image, const QString &code);

private:
    QString processImage(const QImage &image) const;

    QImage m_image;
    QMutex m_mutex;
    QWaitCondition m_condition;
    bool m_quit;
};

#endif
