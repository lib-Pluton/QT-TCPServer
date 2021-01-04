#include <QCoreApplication>
#include "Core.h"

Core core;
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    core.Connect("localhost", 1234);
    core.Write(core.SendCommand("say","Hello Word"));
    return a.exec();
}
