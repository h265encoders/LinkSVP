#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include "Link.h"

class Worker : public QObject
{
    Q_OBJECT
public:
    explicit Worker(QObject *parent = 0);
    void init();
    LinkObject *input;
    LinkObject *detect;
    LinkObject *recognition;
    LinkObject *encV;
    LinkObject *mux;
    LinkObject *crop;
    LinkObject *snap;
    LinkObject *vo;
    QVariantList faceList;
signals:

public slots:
    bool addFace(QString name);
    QVariantList faceBox();

    void onNewEvent(QString type, QVariant info);
};

#endif // WORKER_H
