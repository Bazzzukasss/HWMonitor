#include "mainwindow.h"
#include "ui_mainwindow.h"

#define DEFAULT_IP      "192.168.22.15"
#define DEFAULT_PORT    "9123"
#define REFRESH_TIME    250
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QString title,ip;
    int port;
    HWSession DefaultSession("","user","password",DEFAULT_IP,DEFAULT_PORT,"protocol");

    slotLoadSessions();

    if(!sessions.empty())
        currentSession=&sessions[0];
    else
        currentSession=&DefaultSession;

    ip=currentSession->getHost();
    port=currentSession->getPort().toInt();
    title=currentSession->getNameHostPort();

    monitor = new NetMonitor(*currentSession,new NetUDPClient_Linpack(ip,port,this),ui->frame_Monitor,3,8,false);
    timer =new QTimer(this);
    connect(timer,SIGNAL(timeout()),monitor,SLOT(slotRefresh()));
    connect(ui->pushButton_Connect,SIGNAL(clicked()),this,SLOT(slotReconnect()));
    connect(ui->pushButton_AddSession,SIGNAL(clicked()),this,SLOT(slotAddSession()));
    connect(ui->pushButton_DeleteSession,SIGNAL(clicked()),this,SLOT(slotDeleteSession()));
    timer->start(REFRESH_TIME);
}

MainWindow::~MainWindow()
{
    slotSaveSessions();
    delete ui;
}

void MainWindow::slotReconnect()
{
    if(!sessions.empty())
    {
        timer->stop();
        currentSession=&sessions[ui->comboBox_Sessions->currentIndex()];
        monitor->reconnect(*currentSession);
        timer->start(REFRESH_TIME);
    }
}
void MainWindow::showSessions()
{
    ui->comboBox_Sessions->clear();
    for(auto s: sessions)
        ui->comboBox_Sessions->addItem(s.getNameHostPort());
}

void MainWindow::slotAddSession()
{
    QString name(ui->lineEdit_Name->text());
    QString host(ui->lineEdit_Host->text());
    QString port(QString().number(ui->spinBox_Port->value()));
    sessions.push_back(HWSession(name,"user","password",host,port,"protocol"));
    showSessions();
}

void MainWindow::slotDeleteSession()
{
    int i=ui->comboBox_Sessions->currentIndex();
    if(i>=0)
    {
        sessions.erase(sessions.begin()+i);
        showSessions();
    }
}

void MainWindow::slotLoadSessions()
{
    ifstream f(QApplication::applicationDirPath().toStdString()+"/sessions.txt");

    copy(
                istream_iterator<HWSession>(f),
                istream_iterator<HWSession>(),
                back_inserter(sessions)
                );
    showSessions();
}
void MainWindow::slotSaveSessions()
{
    ofstream f(QApplication::applicationDirPath().toStdString()+"/sessions.txt");

    copy(
                sessions.begin(),
                sessions.end(),
                ostream_iterator<HWSession>(f,"\n")
                );
}

void MainWindow::mousePressEvent(QMouseEvent* event)
{
    position=event->pos();
}

void MainWindow::mouseReleaseEvent(QMouseEvent*)
{
    position=QPoint(-1,-1);
}

void MainWindow::mouseMoveEvent(QMouseEvent* event)
{
    if (position.x() >= 0 && event->buttons() == Qt::LeftButton)
        this->move(QPoint(this->pos() + event->pos() - position));
}
