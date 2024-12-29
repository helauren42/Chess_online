#include "mainwindow.hpp"
#include "session.hpp"
#include <QDebug>
#include <QFile>
#include <QDir>

t_dim       dim;

inline namespace Global {
	SessionManager session;
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
    // session.window = &window;
	window.show();

	app.exec();
    session.logout();
	return 0;
}
