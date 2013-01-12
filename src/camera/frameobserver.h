#ifndef FRAMEOBSERVER_H
#define FRAMEOBSERVER_H

#include <QVideoFrame>

class FrameObserver
{
public:
    virtual bool updateItem(const QVideoFrame &frame) = 0;
};

#endif
