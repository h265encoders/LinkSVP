TEMPLATE = subdirs

SUBDIRS += \
    MotionDetect \
    UseLinkIVE \
    UseHisiIVE \
    UseOpencv

include(build.pri)

contains(DEFINES,HI3519A){
SUBDIRS +=FaceRecognition \
    PedestrianDetect
}

if(!contains(DEFINES,HI3516E)){
SUBDIRS += FaceDetect

}

DISTFILES += \
    build.pri
