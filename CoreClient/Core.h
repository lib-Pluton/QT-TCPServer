#include <QStringList>
#include <QTcpServer>
#include <QTcpSocket>
#include <QDateTime>
#include <QMap>
#include <QSet>
#include <windows.h>

class Core : public QObject
{
    Q_OBJECT
public:
    Core(QObject *parent=0);
    void Connect(QString IP, int Port);
    void Write(QString Data);
    QString SendCommand(QString Command, QString Message);
    QString ClientData();
    QTcpSocket *Socket;
};
