#ifndef SAMPLE_H
#define SAMPLE_H

#include <QObject>
#include "LinkFrame.h"
#include <opencv2/core/utility.hpp>
#include <opencv2/tracking.hpp>
using namespace cv;

class Sample : public LinkFrame, public LinkIVE
{
    Q_OBJECT
public:
    explicit Sample(QObject *parent = 0);
    void oneFrame();

signals:

public slots:
};

#endif // SAMPLE_H
