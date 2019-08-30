TEMPLATE = subdirs

SUBDIRS += \
    MotionDetect \
    FaceDetect \
    UseLinkIVE \
    UseHisiIVE \
    UseOpencv

contains(DEFINES,HI3519A){
SUBDIRS +=FaceRecognition \
    PedestrianDetect
}

DISTFILES += \
    build.pri
