#ifndef SIGNUP_HPP
#define SIGNUP_HPP

#include <QWidget>

namespace Ui {
class signup;
}

class signup : public QWidget
{
    Q_OBJECT

public:
    explicit signup(QWidget *parent = nullptr);
    ~signup();

private:
    Ui::signup *ui;
};

#endif // SIGNUP_HPP
