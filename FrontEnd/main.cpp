#include "mainwindow.hpp"
#include "online.hpp"
#include <QDebug>
#include <QFile>
#include <QDir>

t_dim       dim;

inline namespace Global {
	Online online;
}

int main(int argc, char *argv[])
{
    QDir dir = dir.current();
    qDebug() << dir.absolutePath();
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
    // online.window = &window;
	window.show();

	app.exec();
    online.logout();
	return 0;
}
