#include <QtDebug>
#include <QDateTime>

#include "codereader.h"
#include "codereaderthread.h"

CodeReader::CodeReader(QObject *parent)
    : QObject(parent)
    , m_thread(new CodeReaderThread(this))
    , m_processing(false)
{
    connect(m_thread, SIGNAL(processingFinished(QImage, QString)),
            this, SLOT(imageProcessingFinished(QImage, QString)));

    m_thread->start();
}

CodeReader::~CodeReader()
{
    m_thread->exit();
}

void CodeReader::checkForCodes(const QImage &image)
{
    m_processing = true;

    m_thread->checkForCodes(image);
}

bool CodeReader::isProcessing() const
{
    return m_processing;
}

void CodeReader::imageProcessingFinished(const QImage &image, const QString &code)
{
    if (code.isEmpty()) {
        //qDebug("Code NOT found.");
    } else {
        qDebug() << QDateTime::currentDateTime() << " Code found: " << code;
        emit codeFound(code);
    }

    m_processing = false;
}
