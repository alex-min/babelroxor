#include "CentralWidget.h"
#include <CustomButton.h>

CentralWidget::CentralWidget()
{
    _callButton.setShape(CustomButton::ROUND);
    _hangUpButton.setShape(CustomButton::ROUND);

    _callButton.setText("Call");
    _hangUpButton.setText("Hang Up");

    _callButton.setRadius(8.0, 8.0);
    _hangUpButton.setRadius(8.0, 8.0);

    _callButton.setIcon(QPixmap("./call.png"));
    _hangUpButton.setIcon(QPixmap("./hang_up.png"));

    _callButton.setBold(true);
    _hangUpButton.setBold(true);

    _layout.addWidget(&_callButton, 0, 0, Qt::AlignTop);
    _layout.addWidget(&_hangUpButton, 0, 1, Qt::AlignTop);

    setLayout(&_layout);
}

CentralWidget::~CentralWidget()
{

}
