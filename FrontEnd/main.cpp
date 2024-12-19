#include "mainwindow.hpp"
#include <QDebug>
#include <QFile>
#include <QDir>

t_dim       dim;
inline namespace Global {
	Online online;  // Actual definition
}

int main(int argc, char *argv[])
{
	QFile file("../../../FrontEnd/styles.css");
	Logger::setLoggerFile("../../../FrontEnd/log.txt", true);
	if (!file.open(QFile::ReadOnly | QFile::Text)) {
		qDebug() << "Failed to open stylesheet file";
		return -1;
	}

	QString stylesheet = file.readAll();

	QApplication app(argc, argv);
	app.setStyleSheet(stylesheet);
	MainWindow window(nullptr);
	window.show();

	app.exec();
	return 0;
}
