#include "Core.h"
Core::Core(QObject *parent) : QTcpServer(parent){
  Write("Server Started!");
}

void Core::incomingConnection(int Socket){
    QTcpSocket *client = new QTcpSocket(this);
    client->setSocketDescriptor(Socket);
    Clients.insert(client);
    connect(client, SIGNAL(readyRead()), this, SLOT(ReadyRead()));
    connect(client, SIGNAL(disconnected()), this, SLOT(Disconnected()));
}

void Core::Write(QString Data){
    QString format = "HH:mm / dd.MM.yyyy";
    QDateTime time = QDateTime::currentDateTime();
    QString newdata = "["+ time.toString(format) + "] " + Data;
    qDebug() << (const char *)newdata.toStdString().c_str();
}


void Core::SendReplay(QString User, QString Data){
    foreach(QTcpSocket *client, Clients){
        client->write(QString("Server-Replay | (" + User +  ") : " + Data + "\n").toUtf8());
    }
}

void Core::CheckCommand(QString Line)
{
    QList<QString> Commands;
    Commands << "say";
    for(int x = 0; x < Commands.count(); x++){
        if(Line.lastIndexOf(Commands[x]) > 0){
            QString ReplaceCommand = Line.replace("/" + Commands[x] + ":" , "");
            QString FindUser = ReplaceCommand.replace("|","\n");
            QList<int> list; QStringList slist; slist = FindUser.split("\n");
            for (int x = 0; x <= slist.count()-1; x++) {
            list.append(slist.at(x).toInt());
            }
            QString UserName = slist[0];
            QString Message = slist[1];
            if(Commands[x] == "say")
            {
                Write("New Request: Command-" + Commands[x] + " [UserName: " + UserName + "]");
                SendReplay(UserName, Message);
            }

        }
    }
}

void Core::ReadyRead(){
    QTcpSocket *client = (QTcpSocket*)sender();
    while(client->canReadLine())
    {
        QString line = QString::fromUtf8(client->readLine()).trimmed();
        CheckCommand(line);
    }
}

void Core::Disconnected(){
    QTcpSocket *client = (QTcpSocket*)sender();
    Clients.remove(client);
}
