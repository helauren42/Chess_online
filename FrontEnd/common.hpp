#ifndef COMMON_HPP
#define COMMON_HPP

#include <QMainWindow>
#include <QApplication>
#include <QScreen>
#include <QWindow>
#include <QWidget>
#include <QStackedWidget>

#include <memory>

inline enum GameMode {
	HOTSEAT,
	AI,
	ONLINE
};

struct t_dim {
	short board;
	short x_mid;

	~t_dim() {}
};



#endif
