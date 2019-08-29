#include "Worker.h"

Worker::Worker(QObject *parent) : QObject(parent)
{

}

void Worker::init()
{
    input=Link::create("InputIsp");
    input->start();

    detect=Link::create("FaceDetect");
    detect->start();

    recognition=Link::create("FaceRecognition");
    recognition->start();

    crop=Link::create("Crop");
    crop->start();

    encV=Link::create("EncodeV");
    QVariantMap dataEnc;
    dataEnc["width"]=1920;
    dataEnc["height"]=1080;
    dataEnc["bitrate"]=4096;
    dataEnc["rcmode"]="avbr";
    encV->start(dataEnc);

    mux=Link::create("Mux");
    QVariantMap dataMux;
    dataMux["path"]="rtmp://127.0.0.1/live/test";
    dataMux["mute"]=true;
    mux->start(dataMux);

    vo=Link::create("OutputVo");
    vo->start();

    input->linkV(detect);
    input->linkV(encV)->linkV(mux);
    input->linkV(recognition)->linkV(vo);
    detect->linkE(recognition);

    connect(recognition,SIGNAL(newEvent(QString,QVariant)),this,SLOT(onNewEvent(QString,QVariant)));
}

bool Worker::addFace(QString name)
{
    recognition->invoke("addFace",name);
    return true;
}

QVariantList Worker::faceBox()
{
    return faceList;
}

void Worker::onNewEvent(QString type, QVariant info)
{
    if(type=="face")
    {
        faceList=info.toList();
//        qDebug()<<faceList;
    }
}

