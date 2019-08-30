TEMPLATE = subdirs

SUBDIRS += \
    MotionDetect \
    FaceDetect \
    UseLinkIVE \
    UseHisiIVE \
    UseOpencv \
    PedestrianDetect

contains(DEFINES,HI3519A){
SUBDIRS +=FaceRecognition
}

DISTFILES += \
    build.pri
