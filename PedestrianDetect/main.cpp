#include <QCoreApplication>
#include "Link.h"
int main(int argc, char *argv[])
{
    Link::init();

    QCoreApplication a(argc, argv);

    LinkObject *input=Link::create("InputIsp");
    input->start();

    LinkObject *detect=Link::create("PedestrianDetect");
    detect->start();

    LinkObject *vo=Link::create("OutputVo");
    vo->start();

    input->linkV(detect)->linkV(vo);

    QObject::connect(detect,&LinkObject::newEvent,[=](QString type,QVariant info){
        QVariantList list=info.toList();
        if(list.isEmpty())
            return;
        qDebug()<<"#################";
        for(int i=0;i<list.count();i++)
        {
            qDebug()<<list[i];
        }
    });

    return a.exec();
}

