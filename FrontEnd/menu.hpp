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
    void getOnlinePlayers();
    void updateOnlinePlayers();
    void on_onlineInvite_clicked();

signals:
    void sigLauchGame();
    void sigLogOut();

private slots:
    void on_hotseat_clicked();

    void on_logOut_clicked();

private:
    Ui::Menu *ui;
    std::map<std::string, std::string> players;
};

#endif // MENU_H
