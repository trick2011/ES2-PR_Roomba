#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QLabel>

#include "../file.h"

//#define TIMERDEBUG

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT
public:
	explicit MainWindow(Roomclass& room,QWidget *parent = 0);
	~MainWindow();

private:
	int counter;
	const int UpdateSpeed = 50;
	Roomclass& room;
	Ui::MainWindow *ui;

	QTimer *timer;
	QTimer recievetimeout;

	void SetGreen(QLabel* in);
	void SetOrange(QLabel* in);
	void SetRed(QLabel* in);

private slots:
	void TimerInterrupt(void);
	void on_actionExit_triggered();
};

#endif // MAINWINDOW_H
