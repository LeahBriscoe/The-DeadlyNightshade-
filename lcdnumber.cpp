#include "lcdnumber.h"
/*! @brief Constructor for the LCDNumber. Connect timer, a SIGNAL, that goes off every second to the SLOT that changes the display
 *  @param parent the QWidget pointer.
 *  @param minutes is the minutes desired for the clock
 *  @param seconds is the seconds desired for the clock
 */
LCDNumber::LCDNumber(QWidget* parent, int minutes, int seconds)
{
    timer = new QTimer();
    timeValue = new QTime(0, minutes, seconds);
    this->setParent(parent);
    this->display(timeValue->toString());
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(setDisplay()));
}

/*! @brief An empty destructor
 */
LCDNumber::~LCDNumber(){}

/*! @brief A public slot function that changes the display every second by decreasing displayed minutes and displayed
 * seconds by one second
 */
void LCDNumber::setDisplay(){
    this->timeValue->setHMS(0,this->timeValue->addSecs(-1).minute(), this->timeValue->addSecs(-1).second());
    this->display(this->timeValue->toString());
}
