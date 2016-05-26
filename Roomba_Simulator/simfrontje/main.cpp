#include <iostream>
#include <string>
#include <fstream>
#include <thread>

#include "../test.h"

#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	Roomclass room;
	Inv_interpreter* interpeter = new Inv_interpreter(room);
	testinitBIG(room);

	thread tempthread(ref(*interpeter));


	MainWindow w(room);
	w.show();

	return a.exec();
}
