#include <QCoreApplication>
#include "Link.h"
#include "Worker.h"
#include "maiaXmlRpcServer.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Link::init();

    Worker worker;
    worker.init();

    MaiaXmlRpcServer *rpcServer;

    rpcServer = new MaiaXmlRpcServer(8080);
    rpcServer->addMethod("addFace", &worker, "addFace");
    rpcServer->addMethod("faceBox", &worker, "faceBox");

    return a.exec();
}

