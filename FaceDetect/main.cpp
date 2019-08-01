#include <QCoreApplication>
#include "Link.h"
#include "FaceDetect.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Link::init();

    LinkObject *vi=Link::create("InputVi");
    QVariantMap dataVi;
    dataVi["interface"]="HDMI-A";
    vi->start(dataVi);

    FaceDetect *FD=new FaceDetect();
    QVariantMap dataFD;
    dataFD["framerate"]=5;
    FD->start(dataFD);

    LinkObject *vo=Link::create("OutputVo");
    QVariantMap dataVo;
    dataVo["type"]="hdmi";
    vo->start(dataVo);

    vi->linkV(FD)->linkV(vo);

    return a.exec();
}

