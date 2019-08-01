#ifndef FACEDETECT_H
#define FACEDETECT_H

#include <QObject>
#include "LinkFrame.h"
#include "MTCNN.h"
#include <opencv2/core/utility.hpp>
#include <opencv2/tracking.hpp>
#include "hi_comm_ive.h"
#include "mpi_ive.h"
using namespace cv;

class FaceDetect : public LinkFrame, public LinkIVE
{
    Q_OBJECT
public:
    explicit FaceDetect(QObject *parent = 0);
    void oneFrame();
    void drawRect(QRect rect);
    MTCNN detector;
    MultiTracker *trackers;
    QVariantList list;
    Mat mat;
    Mat mat2;
    Mat matout;
    Mat matoutUV;
signals:

public slots:
    void onDetect(QVariantList list);
};

#endif // FACEDETECT_H
