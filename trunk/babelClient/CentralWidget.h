#ifndef CENTRALWIDGET_H
#define CENTRALWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPixmap>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QListWidget>
#include <CustomButton.h>

class CentralWidget : public QWidget
{
public:
    CentralWidget();
    ~CentralWidget();

private:

    QGridLayout _layout;
    CustomButton    _callButton;
    CustomButton    _hangUpButton;

};

#endif // CENTRALWIDGET_H
