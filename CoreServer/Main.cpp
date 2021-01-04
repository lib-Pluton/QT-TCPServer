#include <QCoreApplication>
#include "Core.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Core *server = new Core();
    server->listen(QHostAddress::Any, 1234);
    return a.exec();
}
