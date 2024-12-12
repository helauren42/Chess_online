#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "common.hpp"
#include "login.hpp"
#include "signup.hpp"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MStackedWidgets : public QStackedWidget {
public:
    login* loginWidget;
    signup* signupWidget;
    MStackedWidgets();
    ~MStackedWidgets();
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MStackedWidgets* stackedWidgets;
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onSigLogin();
    void onValidLogin();
    void onFaultyLogin();

    void onSigSignup();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
