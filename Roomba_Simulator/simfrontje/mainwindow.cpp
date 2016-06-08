#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(Roomclass& room,Inv_interpreter& peter,QWidget *parent) :QMainWindow(parent),room{room},peter{peter},ui(new Ui::MainWindow){
	ui->setupUi(this);
	//room.roomba->sensorref.get
	connect(&recievetimeout,SIGNAL(timeout()),this,SLOT(TimerInterrupt())); // nope not readdata but its fine
	recievetimeout.start(UpdateSpeed);

	//readthread = new std::thread(std::ref(peter));

	//ui->statusBar->sets
	counter = 0;

	//ui->lcdNumber->setPalette(Qt::red);
	ui->lcdNumber_lightbump->setPalette(Qt::darkGreen);
	ui->lcdNumber_lightbumpl->setPalette(Qt::darkGreen);
	ui->lcdNumber_lightbumpr->setPalette(Qt::darkGreen);

	ui->lcdNumber_angle->setPalette(Qt::darkGreen);
	ui->lcdNumber_speed->setPalette(Qt::darkGreen);

#ifndef TIMERDEBUG
	ui->textBrowser->hide();
#endif

}

MainWindow::~MainWindow(){
	delete ui;
}
void MainWindow::SetGreen(QLabel* in){
	in->setPixmap(QPixmap(QString::fromUtf8(":/led/green_led")));
	//setPixmap(QPixmap(QString::fromUtf8(":/led/green_led")));
}
void MainWindow::SetOrange(QLabel* in){
	in->setPixmap(QPixmap(QString::fromUtf8(":/led/orange_led")));
}
void MainWindow::SetRed(QLabel* in){
	in->setPixmap(QPixmap(QString::fromUtf8(":/led/red_led")));
}

void MainWindow::TimerInterrupt(void){
	recievetimeout.stop();
#ifdef TIMERDEBUG
	++counter;
	ui->textBrowser->append(QString(counter));
#endif

// bump
	if(room.roomba->sensorref.getbBumpLeft())
		SetGreen(ui->led_bumpl);
	else
		SetRed(ui->led_bumpl);

	if(room.roomba->sensorref.getbBumpRight())
		SetGreen(ui->led_bumpr);
	else
		SetRed(ui->led_bumpr);

// cliff
	if(room.roomba->sensorref.getCliffLeft())
		SetGreen(ui->led_cliffl);
	else
		SetRed(ui->led_cliffl);

	if(room.roomba->sensorref.getCliffFrontLeft())
		SetGreen(ui->led_clifffl);
	else
		SetRed(ui->led_clifffl);

	if(room.roomba->sensorref.getCliffRight())
		SetGreen(ui->led_cliffr);
	else
		SetRed(ui->led_cliffr);

	if(room.roomba->sensorref.getCliffLeft())
		SetGreen(ui->led_cliffr);
	else
		SetRed(ui->led_cliffr);
// speed
	ui->lcdNumber_speed->display(room.roomba->getspeed());
// angle
	ui->lcdNumber_angle->display(room.roomba->getangle());
// lightbump
	ui->lcdNumber_lightbumpl->display(room.roomba->sensorref.getLightBumpFrontLeft());
	ui->lcdNumber_lightbump->display(((room.roomba->sensorref.getLightBumpFrontLeft()+room.roomba->sensorref.getLightBumpRight())/2));
	ui->lcdNumber_lightbumpr->display(room.roomba->sensorref.getLightBumpFrontRight());

	recievetimeout.start(UpdateSpeed);
}

void MainWindow::on_actionExit_triggered(){
	exit(EXIT_SUCCESS);
}
