#include "Enemy.h"
#include <QTimer>
#include <QList>
#include <QGraphicsScene>
#include <random>
#include <chrono>
unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
std::default_random_engine generator (seed);
#include "gameboard.h"
/*! @brief Enemy constructor with QGraphicsPixmapItem as parent. Adds Bacteria graphic to GameBoard graphic view.
 *  @param parent the QGraphicItem pointer
 *  @param gb the GameBoard pointer to allow Enemy to alter energy status of player
 */

Enemy::Enemy(QGraphicsItem* parent, GameBoard* gb): QObject(), QGraphicsPixmapItem(parent), board(gb)
{
    int random_number = generator()%700;//generate random
    setPos(random_number,0);
    setPixmap(QPixmap(":/characters/Bacteria.png"));

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));

    timer->start(50);
}

/*! @brief Move function determines direction and speed (5 units down every 50ms) of enemy bacteria movement.
 *  Once enemy goes out of gameboard area, player energy is decreased, and enemy is deleted
 */
void Enemy::move()
{
    setPos(x(),y()+5);

    if(pos().y() > 600){
        board->decreaseEmore();
        scene()->removeItem(this);
        delete this;
    }
}
