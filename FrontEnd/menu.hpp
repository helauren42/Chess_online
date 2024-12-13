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

private slots:
    void on_hotseat_clicked();

private:
    Ui::Menu *ui;
};

#endif // MENU_H
