#ifndef MENU_H
#define MENU_H

#include "common.hpp"
#include <QWidget>

namespace Ui {
class Menu;
}

class Menu : public QWidget
{
    Q_OBJECT

public:
    explicit Menu(QWidget *parent = nullptr);
    ~Menu();

signals:
    void sigLauchGame();
    void sigLogOut();

private slots:
    void on_hotseat_clicked();

    void on_logOut_clicked();

private:
    Ui::Menu *ui;
};

#endif // MENU_H
