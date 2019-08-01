#include "FaceDetect.h"

FaceDetect::FaceDetect(QObject *parent) : LinkFrame(parent)
{
    data["framerate"]=5;
    data["width"]=1920;
    data["height"]=1080;
    mem["rgb"]=IVEMem(1920,1080,3,true);
    mem["rect"]=IVEMem(1920,1080,1,true);
    mem["mat"]=IVEMem(1920/8,1080/8,1,true);
    mem["mat2"]=IVEMem(1920/8,1080/8,1,true);
    trackers=NULL;
    connect(&detector,SIGNAL(detectDone(QVariantList)),this,SLOT(onDetect(QVariantList)));
}


void FaceDetect::oneFrame()
{
    int scale=8;
    static int ccc=-1;
    ccc=(ccc+1)%5;
    if(ccc==0)
    {

        IVE_CSC_CTRL_S ctrlCSC;
        ctrlCSC.enMode=IVE_CSC_MODE_PIC_BT709_YUV2RGB;
        HI_S32 ret=HI_MPI_IVE_CSC(&handle, mem["in"].toImage(IVE_IMAGE_TYPE_YUV420SP), mem["rgb"].toImage(IVE_IMAGE_TYPE_U8C3_PACKAGE), &ctrlCSC, HI_TRUE);
        if(ret!=HI_SUCCESS)
        {
            qDebug("HI_MPI_IVE_CSC failed %#x",ret);
        }
        copySmall(mem["in"],mem["mat"]);
        wait();
        detector.detect(mem["rgb"]);
    }

    {
        if(trackers==NULL)
            return;
        copySmall(mem["in"],mem["mat2"]);
        wait();
        mat2=Mat(1080/scale, 1920/scale, CV_8UC1, (void*)mem["mat2"].data());

        struct timeval tpstart,tpend;
        gettimeofday(&tpstart,NULL);
        trackers->update(mat2);

        gettimeofday(&tpend,NULL);

        copy(mem["in"],mem["rect"]);
        IVEMem UVin=mem["in"].toUV();
        IVEMem UVout=mem["out"].toUV();
        copy(UVin,UVout);
        wait();

        matout=Mat(1080, 1920, CV_8UC1, (void*)mem["rect"].data());

        QVariantList ret;
        for(int i=0;i<trackers->getObjects().size();i++)
        {
            Rect rt1=trackers->getObjects()[i];
            Rect rt2;
            rt2.x=rt1.x*scale;//-0.33*rt1.width*scale;
            rt2.y=rt1.y*scale;//-0.33*rt1.height*scale;
            rt2.width=rt1.width*scale;//+0.66*rt1.width*scale;
            rt2.height=rt1.height*scale;//+0.66*rt1.height*scale;
           rectangle( matout, rt2, Scalar( 255, 0, 0 ), 4, 1 );

           QVariantMap rect;
           rect["x"]=(double)rt2.x/1920.0;
           rect["y"]=(double)rt2.y/1080.0;
           rect["w"]=(double)rt2.width/1920.0;
           rect["h"]=(double)rt2.height/1080.0;

           ret.push_back(rect);
        }

        emit this->newEvent("FD",ret);

        mem["rect"].flush();
        copy(mem["rect"],mem["out"]);

        wait();

    }



}

void FaceDetect::drawRect(QRect rect)
{
    char *data=mem["rect"].data();
    for(int i=0;i<5;i++)
    {
        memset(data+1920*(rect.top()+i)+rect.left(),255,rect.width());
        memset(data+1920*(rect.bottom()-i)+rect.left(),255,rect.width());
    }

    for(int i=0;i<rect.height();i++)
    {
        memset(data+1920*(rect.top()+i)+rect.left(),255,5);
        memset(data+1920*(rect.top()+i)+rect.right()-5,255,5);
    }

}

void FaceDetect::onDetect(QVariantList list)
{
    int scale=8;
    if(trackers!=NULL)
    {
        delete trackers;
        trackers=NULL;
    }


    wait();
    mat=Mat(1080/scale, 1920/scale, CV_8UC1, (void*)mem["mat"].data());

    trackers=new MultiTracker();
    std::vector<Ptr<Tracker> > algorithms;
    vector<Rect2d> objects;
    for(int i=0;i<list.count();i++)
    {
        Rect rt;
        QRect rect=list[i].toRect();
        rt.x=rect.x()/scale;//+0.2*rect.width()/scale;
        rt.y=rect.y()/scale;//+0.2*rect.height()/scale;
        rt.width=rect.width()/scale;//-0.4*rect.width()/scale;
        rt.height=rect.height()/scale;//-0.4*rect.height()/scale;
        objects.push_back(rt);
        algorithms.push_back(TrackerKCF::create());

    }
    trackers->add(algorithms,mat,objects);
}
