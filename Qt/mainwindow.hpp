#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QApplication>
#include <QScreen>
#include <QWindow>

struct t_dim {
    QRect screenGeometry;
    short board;

    t_dim() {
        QScreen *screen = QGuiApplication::primaryScreen();
        screenGeometry = screen->geometry();
        board = screenGeometry.height();
    }
    ~t_dim() {}
};

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_submit_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
