#ifndef MTCNN_H
#define MTCNN_H

#include <QObject>
#include "LinkIVE.h"
#include <stdio.h>
#include <algorithm>
#include <vector>
#include <math.h>
#include <iostream>
#include "net.h"
#include "cpu.h"
#include <QFile>
#include <QDateTime>
#include <QDebug>
#include <sys/time.h>

using namespace std;
struct Bbox
{
    float score;
    int x1;
    int y1;
    int x2;
    int y2;
    float area;
    bool exist;
    float ppoint[10];
    float regreCoord[4];
};

struct orderScore
{
    float score;
    int oriOrder;
};



class MTCNN : public QObject
{
    Q_OBJECT
public:
    explicit MTCNN(QObject *parent = 0);

    void detect(IVEMem &rgb);

private:
    IVEMem mem;
    QThread *thread;

    void detect_net(ncnn::Mat& img_, std::vector<Bbox>& finalBbox);
    void generateBbox(ncnn::Mat score, ncnn::Mat location, vector<Bbox>& boundingBox_, vector<orderScore>& bboxScore_, float scale);
    void nms(vector<Bbox> &boundingBox_, std::vector<orderScore> &bboxScore_, const float overlap_threshold, string modelname="Union");
    void refineAndSquareBbox(vector<Bbox> &vecBbox, const int &height, const int &width);

    ncnn::Net Pnet, Rnet, Onet;
    ncnn::Mat img;

    const float nms_threshold[3] = {0.3, 0.6, 0.6};
    const float threshold[3] = {0.8, 0.8, 0.8};
    const float mean_vals[3] = {127.5, 127.5, 127.5};
    const float norm_vals[3] = {0.0078125, 0.0078125, 0.0078125};
    std::vector<Bbox> firstBbox_, secondBbox_,thirdBbox_;
    std::vector<orderScore> firstOrderScore_, secondBboxScore_, thirdBboxScore_;
    int img_w, img_h;
signals:
    void detectDone(QVariantList);

public slots:
    void doDetect();
};

#endif // MTCNN_H
