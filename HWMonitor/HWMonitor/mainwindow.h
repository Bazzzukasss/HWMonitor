#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QMouseEvent>
#include "NetMonitor.h"
#include "HWConnection.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <QDir>

using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void showSessions();
private slots:
    void slotReconnect();
    void slotAddSession();
    void slotDeleteSession();
    void slotLoadSessions();
    void slotSaveSessions();
private:
    Ui::MainWindow *ui;
    QPoint position{QPoint(-1,-1)};
    QTimer* timer;
    NetMonitor* monitor;
    vector<HWSession> sessions;
    HWSession* currentSession{nullptr};
    void build();

protected:
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent*);
    void mouseMoveEvent(QMouseEvent* event);
};

#endif // MAINWINDOW_H
