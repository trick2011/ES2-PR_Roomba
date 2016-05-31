#include <iostream>
#include <string>
#include <fstream>
#include <thread>

#include "../test.h"

#include "mainwindow.h"
#include <QApplication>
#include <QIcon>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	Roomclass room;
	Inv_interpreter* interpeter = new Inv_interpreter(room);
	testinitBIG(room);

	thread tempthread(ref(*interpeter));


	MainWindow w(room);
	w.setWindowIcon(QIcon(QString::fromUtf8(":/led/pile_of_poo")));
	w.show();

	return a.exec();
}
