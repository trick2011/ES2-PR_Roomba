#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

#include "../file.h"

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
	const int UpdateSpeed = 2;
	Roomclass& room;
	Ui::MainWindow *ui;

	QTimer *timer;
	QTimer recievetimeout;
private slots:
	void TimerInterrupt(void);
};

#endif // MAINWINDOW_H
