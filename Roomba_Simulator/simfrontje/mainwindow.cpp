#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(Roomclass& room,QWidget *parent) :QMainWindow(parent),room{room},ui(new Ui::MainWindow){
	ui->setupUi(this);
	//room.roomba->sensorref.get
	connect(&recievetimeout,SIGNAL(timeout()),this,SLOT(TimerInterrupt())); // nope not readdata but its fine
	recievetimeout.start(UpdateSpeed);
}

MainWindow::~MainWindow(){
	delete ui;
}

void MainWindow::TimerInterrupt(void){
	recievetimeout.stop();

	//room.roomba->sensorref.getbBumpLeft();

	recievetimeout.start(TimerInterrupt);
}
