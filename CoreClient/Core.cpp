#include "Core.h"
Core::Core(QObject *parent) : QObject(parent){
  Write("Client Started!");
}

void Core::Write(QString Data){
    QString format = "HH:mm / dd.MM.yyyy";
    QDateTime time = QDateTime::currentDateTime();
    QString newdata = "["+ time.toString(format) + "] " + Data;
    qDebug() << (const char *)newdata.toStdString().c_str();
}

void Core::Connect(QString IP, int Port){
    Socket = new QTcpSocket(this);
    Socket->connectToHost(IP, Port);
    Socket->waitForConnected();
}

QString Core::SendCommand(QString Command, QString Message){
    Socket->write(QString(" /" + Command + ":" + "Client" + "|"+ Message + "\n").toUtf8());
    Socket->waitForBytesWritten();
    Socket->waitForReadyRead();
    QString waitreturn;
    if(Socket->canReadLine())
    {
        QString line = QString::fromUtf8(Socket->readLine()).trimmed();
        QString ReplayReplace = line.replace("Server-Replay | (" , "").replace(") : ","\n");
        QList<int> list; QStringList slist; slist = ReplayReplace.split("\n");
        for (int x = 0; x <= slist.count()-1; x++) {
        list.append(slist.at(x).toInt());
        }
        if(slist[0] == "Client"){
           waitreturn = slist[1];
        }
    }
    return waitreturn;
}
