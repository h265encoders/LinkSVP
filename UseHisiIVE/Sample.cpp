#include "Sample.h"

Sample::Sample(QObject *parent) : LinkFrame(parent)
{
    data["framerate"]=10;
    data["width"]=1280;
    data["height"]=720;
}

void Sample::oneFrame()
{
    IVE_HANDLE handle;
    IVE_THRESH_CTRL_S ctrlThresh;
    ctrlThresh.u8LowThr=128;
    ctrlThresh.u8HighThr=0;
    ctrlThresh.enMode=IVE_THRESH_MODE_BINARY;
    ctrlThresh.u8MaxVal=255;
    ctrlThresh.u8MinVal=0;

    IVE_SRC_IMAGE_S *memSrc=mem["in"].toImage(IVE_IMAGE_TYPE_U8C1);
    IVE_SRC_IMAGE_S *memDst=mem["out"].toImage(IVE_IMAGE_TYPE_U8C1);

    HI_S32 ret=HI_MPI_IVE_Thresh(&handle,memSrc, memDst, &ctrlThresh, HI_TRUE);
    if(ret!=HI_SUCCESS)
    {
        qDebug("iveThresh error %#x",ret);
        return;
    }


    HI_BOOL ff;
    if(HI_ERR_IVE_SYS_TIMEOUT==HI_MPI_IVE_Query(handle, &ff, HI_TRUE))
        qDebug("HI_MPI_IVE_Query HI_ERR_IVE_SYS_TIMEOUT");
}
