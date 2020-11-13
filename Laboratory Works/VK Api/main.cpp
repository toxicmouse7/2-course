#include <iostream>
#include <QtWidgets/QMainWindow>
#include <QApplication>
#include "VKApi.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	VKApi w;
	w.show();    

    return a.exec();
}