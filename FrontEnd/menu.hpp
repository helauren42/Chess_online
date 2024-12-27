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
    void on_onlineInvite_clicked();

signals:
    void getOnlinePlayers();
    void sigLauchGame();
    void sigLogOut();

public slots:
    void onUpdateOnlinePlayers(QString text);

private slots:
    void on_hotseat_clicked();
    void on_logOut_clicked();

private:
    Ui::Menu *ui;
    std::map<std::string, std::string> players;
};

#endif // MENU_H
