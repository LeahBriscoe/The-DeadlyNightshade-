#ifndef LCDNUMBER
#define LCDNUMBER
#include <QLCDNumber>
#include <QTimer>
#include<QTime>
/*! Leah Briscoe PIC10C Spring 2015
 *
 *  @class LCDNumber
 *  @brief Purely visual timer for the appearance of a digital timer on the right side panel of the GameBoard
 */
class LCDNumber: public QLCDNumber
{
    Q_OBJECT

public:
    QTimer* timer; ///< timer that activates the LCD timer
    QTime* timeValue; ///< the QTime object that contains the actual time.

public:
    LCDNumber(QWidget* parent, int minutes, int seconds);
    ~LCDNumber();
public slots:
    void setDisplay();

};

#endif // LCDNUMBER

