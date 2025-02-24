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
    void sigSendChallenge(const QString& challenger, const QString& challenged);

public slots:
    void onUpdateOnlinePlayers(QString text);
    void on_onlineInvite_clicked();

private slots:
    void on_hotseat_clicked();
    void on_logOut_clicked();

private:
    Ui::Menu *ui;
    std::map<std::string, std::string> players;
};

#endif // MENU_H
