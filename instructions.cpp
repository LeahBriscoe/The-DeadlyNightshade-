#include "instructions.h"
#include "ui_instructions.h"
#include "gameboard.h"
#include <QDebug>
#include <QTime>
/*! @brief Constructor for Instructions. Merely sets up the UI and uses intializer list.
 *  @param Parent is the QWidget pointer to the parent
 *  @param gb is the GameBoard pointer passed in by MainWindow
 *  @param stopping_point is the milliseconds left in game when it was paused.
 */
Instructions::Instructions(QWidget *parent, GameBoard* gb, int stopping_point) :
    QDialog(parent), ui(new Ui::Instructions), board(gb), time_paused(stopping_point)

{
    ui->setupUi(this);
}
/*! @brief Destructor for Instructions. Deletes UI.
 */
Instructions::~Instructions()
{
    delete ui;
}
/*! @brief Public slot function to restart_timers(). Hides instructions window. Starts game_timer at passed in time left in the game.
 * LCD timer is started again after instructions window is closed.
 * Enemy timer is started again so that enemy spawns continue
 */
void Instructions::restart_timers()
{
    this->hide();
    //qDebug()<<"Restart timers";
    board->freeze_energy = false;
    board->game_timer->start(time_paused);
    board->clock->timer->start(1000);
    board->enemy_timer->start(1600);
}
