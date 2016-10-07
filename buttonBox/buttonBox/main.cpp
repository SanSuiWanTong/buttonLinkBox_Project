#include "buttonbox.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	buttonBox w;
	w.show();
	return a.exec();
}
