#include <QCoreApplication>
#include "Link.h"
#include "MotionDetect.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Link::init();

    LinkObject *vi=Link::create("InputVi");
    QVariantMap dataVi;
    dataVi["interface"]="HDMI-A";
    vi->start(dataVi);

    MotionDetect *MD=new MotionDetect();
    QVariantMap dataMD;
    dataMD["framerate"]=4;
    MD->start(dataMD);

    LinkObject *vo=Link::create("OutputVo");
    QVariantMap dataVo;
    dataVo["type"]="hdmi";
    vo->start(dataVo);

    vi->linkV(MD)->linkV(vo);

    return a.exec();
}

