#include "Biomr.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Biomr w;
	w.show();
	return a.exec();
}
