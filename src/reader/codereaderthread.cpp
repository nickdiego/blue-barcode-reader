#include "codereaderthread.h"

CodeReaderThread::CodeReaderThread(QObject *parent)
    : QThread(parent)
    , m_quit(false)
{
}

CodeReaderThread::~CodeReaderThread()
{
    m_mutex.lock();

    m_quit = true;
    m_condition.wakeOne();

    m_mutex.unlock();

    wait();
}

void CodeReaderThread::checkForCodes(const QImage &image)
{
    QMutexLocker mutexLocker(&m_mutex);

    m_image = QImage(image);

    if (!isRunning())
        start();
    else
        m_condition.wakeOne();
}

void CodeReaderThread::run()
{
    m_mutex.lock();

    QImage processingImage = QImage(m_image);

    m_mutex.unlock();

    while (!m_quit) {
        // Image Processing: searching for codes
        QString code = processImage(processingImage);

        m_mutex.lock();

        QImage image;

        if (!code.isEmpty())
            image = processingImage.copy();

        // Notify that the image processing is done
        emit processingFinished(image, code);

        m_condition.wait(&m_mutex);

        processingImage = QImage(m_image);

        m_mutex.unlock();
    }
}

QString CodeReaderThread::processImage(const QImage &image) const
{
    // TODO: Replace with actual image code processor

    QString code("");

    if (!image.isNull())
        code = "123456789";

    return code;
}
