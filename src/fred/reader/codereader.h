#ifndef CODEREADER_H
#define CODEREADER_H

#include <QtCore/QObject>
#include <QtGui/QImage>

class CodeReaderThread;

class CodeReader : public QObject
{
    Q_OBJECT

public:
    CodeReader(QObject *parent = 0);
    ~CodeReader();

    void checkForCodes(const QImage &image);

    bool isProcessing() const;

signals:
    void codeFound(const QString &code);

private slots:
    void imageProcessingFinished(const QImage &image, const QString &code);

private:
    CodeReaderThread *m_thread;
    bool m_processing;
};

#endif
