#include "Sample.h"

Sample::Sample(QObject *parent) : LinkFrame(parent)
{
    data["framerate"]=10;
    data["width"]=1280;
    data["height"]=720;

    //建议使用如下方法把内存映射到cache再进行CPU操作，否则速度很慢
    mem["cache"]=IVEMem(1280,720,3,true);
}

void Sample::oneFrame()
{
    copy(mem["in"],mem["cache"]);
    wait();

    Mat mat=Mat(data["height"].toInt(), data["width"].toInt(), CV_8UC1, (void*)mem["cache"].data());

    threshold(mat, mat, 128, 255, CV_THRESH_BINARY);

    mem["cache"].flush();
    copy(mem["cache"],mem["out"]);
    wait();
}

