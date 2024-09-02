#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "rosNode.h"

MainWindow::MainWindow(int argc,char** argv,QWidget *parent)
    : QMainWindow(parent)
    , ui_(new Ui::MainWindow)
    , ros_node_(argc, argv)
{
    ui_->setupUi(this);
    ros_node_.init();

    QObject::connect(ui_->pushButton_send,&QPushButton::clicked,this,&MainWindow::slot_btn_send);
    QObject::connect(this,&MainWindow::signal_send,this,&MainWindow::slot_send_textEdit);

    QObject::connect(this,&MainWindow::signal_rosPub,&ros_node_,&RosNode::slot_pubStrMsg);
    QObject::connect(&ros_node_,&RosNode::signal_strMsg,this,&MainWindow::slot_send_textEdit);
}

MainWindow::~MainWindow()
{
    delete ui_;
}

void MainWindow::slot_btn_send()
{
    QString send_msg = ui_->lineEdit_input->text();
    qDebug()<<send_msg;
    //emit signal_send(send_msg);
    emit signal_rosPub(send_msg);
}

void MainWindow::slot_send_textEdit(const QString& msg)
{
    ui_->textEdit_output->append(msg);
}