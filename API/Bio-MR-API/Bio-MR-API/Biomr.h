#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Biomr.h"

class Biomr : public QMainWindow
{
	Q_OBJECT

public:
	Biomr(QWidget *parent = Q_NULLPTR);

private:
	Ui::BiomrClass ui;
};
