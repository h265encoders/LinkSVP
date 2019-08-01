#include "MotionDetect.h"

MotionDetect::MotionDetect(QObject *parent) : LinkFrame(parent)
{
    data["framerate"]=4;
    data["width"]=640;
    data["height"]=360;
    data["thresh"]=30;
    data["area"]=800;

    mem["pre"]=IVEMem(640,360);
    mem["ccl"]=IVEMem(640,360);
}

void MotionDetect::oneFrame()
{

    Sub(mem["in"],mem["pre"],mem["out"]);
    thresh(mem["out"],mem["out"],data["thresh"].toInt());
    erode(mem["out"],mem["out"],3);
    dilate(mem["out"],mem["out"],5);
    copy(mem["out"],mem["ccl"]);
    wait();
    QVariantList list=CCL(mem["ccl"],data["area"].toInt());

    copy(mem["in"],mem["pre"]);
    wait();

    if(list.count()>0)
    {
        qDebug("######################################");
        for(int i=0;i<list.count();i++)
        {
            qDebug()<<list[i];
        }
    }
}

