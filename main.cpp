#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[]) {

	QApplication a(argc, argv);
	QApplication::setOrganizationName("Wilco Tomassen");
	QApplication::setOrganizationDomain("wilcotomassen.nl");
	QApplication::setApplicationName("CamBooth");

	MainWindow w;
	w.show();

	return a.exec();
}
