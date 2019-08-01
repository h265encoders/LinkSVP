#include "Sample.h"

Sample::Sample(QObject *parent) : LinkFrame(parent)
{
    data["framerate"]=10;
    data["width"]=1280;
    data["height"]=720;
}

void Sample::oneFrame()
{
    thresh(mem["in"],mem["out"],128);
    wait();
}

