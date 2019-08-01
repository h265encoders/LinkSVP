#ifndef SAMPLE_H
#define SAMPLE_H

#include <QObject>
#include "LinkFrame.h"
#include "hi_comm_ive.h"
#include "mpi_ive.h"

class Sample : public LinkFrame
{
    Q_OBJECT
public:
    explicit Sample(QObject *parent = 0);
    void oneFrame();

signals:

public slots:
};

#endif // SAMPLE_H
