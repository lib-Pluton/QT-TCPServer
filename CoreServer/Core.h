#include <QStringList>
#include <QTcpServer>
#include <QTcpSocket>
#include <QMap>
#include <QSet>
#include <QRegExp>
#include <QEventLoop>
#include <QDateTime>

class Core : public QTcpServer
{
    Q_OBJECT
    public:
        Core(QObject *parent=0);
    private slots:
        void ReadyRead();
        void Disconnected();
        void CheckCommand(QString Line);
        void SendReplay(QString User, QString Data);
    protected:
        void incomingConnection(int Socket);
    private:
        QSet<QTcpSocket*> Clients;
        void Write(QString Data);
};
