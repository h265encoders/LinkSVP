TEMPLATE = subdirs

SUBDIRS += \
    MotionDetect \
    UseLinkIVE \
    UseHisiIVE \
    UseOpencv \
    FaceDetect

include(build.pri)
contains(DEFINES,HI3519A){
SUBDIRS +=FaceRecognition \
    PedestrianDetect
}

DISTFILES += \
    build.pri
