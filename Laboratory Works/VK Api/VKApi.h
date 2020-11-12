#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_VKApi.h"

class VKApi : public QMainWindow
{
    Q_OBJECT

public:
    VKApi(QWidget *parent = Q_NULLPTR);

private:
    Ui::VKApiClass ui;
};
