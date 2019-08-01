#ifndef MOTIONDETECT_H
#define MOTIONDETECT_H

#include <QObject>
#include "LinkFrame.h"

class MotionDetect : public LinkFrame, public LinkIVE
{
    Q_OBJECT
public:
    explicit MotionDetect(QObject *parent = 0);
    void oneFrame();
signals:

public slots:
};

#endif // MOTIONDETECT_H
