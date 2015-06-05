#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H
#include <QDialog>
class GameBoard;
/*! Leah Briscoe PIC10C Spring 2015
 *
 *  @class Instructions
 *  @brief Uses the UI to display the instructions for the game. Game will pause when instructions are accessed from
 * GameBoard. PushButton OK will continue the game where it left off. Contains specfic slot to restart these game timers.
 */
namespace Ui {
class Instructions;
}

class Instructions : public QDialog
{
    Q_OBJECT

public:
    explicit Instructions(QWidget *parent, GameBoard* gb, int stopping_point);
    ~Instructions();
public slots:
    void restart_timers();
private:
    Ui::Instructions *ui; ///<Pointer to the UI
    GameBoard* board; ///<GameBoard pointer
    int time_paused; ///<Integer for the time left in milliseconds when the game was paused.
};

#endif // INSTRUCTIONS_H
