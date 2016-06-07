#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QLabel>
#include <thread>

#include "../file.h"
#include "../inv_interpreter.h"

//#define TIMERDEBUG

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT
public:
	explicit MainWindow(Roomclass& room,Inv_interpreter& peter,QWidget *parent = 0);
	~MainWindow();

private:
	int counter;
	const int UpdateSpeed = 50;
	Roomclass& room;
	Inv_interpreter& peter;
	Ui::MainWindow *ui;

	QTimer *timer;
	QTimer recievetimeout;
	std::thread* readthread;

	void SetGreen(QLabel* in);
	void SetOrange(QLabel* in);
	void SetRed(QLabel* in);

private slots:
	void TimerInterrupt(void);
	void on_actionExit_triggered();
};

#endif // MAINWINDOW_H
