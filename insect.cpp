#include "insect.h"
#include <QTimer>
#include <QList>
#include <QGraphicsScene>
#include<random>
#include<chrono>
unsigned seed2 = std::chrono::system_clock::now().time_since_epoch().count();
std::default_random_engine generator2 (seed2);
#include "gameboard.h"
/*! @brief Insect Constructor to create insect with GraphicsPixmapItem I created on Paint. Moves right to left. Randomized y coordinates. Moves every 50 ms.
 *  @param parent is a QGraphicsItem pointer
 *  @param gb is the GameBoard pointer
 */
Insect::Insect(QGraphicsItem* parent, GameBoard* gb):QObject(), QGraphicsPixmapItem(parent), board(gb)
{
    int random_number = generator2()%450;//generate random
    setPos(700, random_number);
    setPixmap(QPixmap(":/characters/Insect.png"));
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));

    timer->start(50);
}

/*! @brief Move function moves insect by 5 units to the left every 50 ms.
 * Once the insect Pixmap item moves too far to the left, it is deletes and removed from the scene.
 */
void Insect::move()
{
    setPos(x()-5,y());

    if(pos().x() + 100 < 0){
        board->decreaseEmore();
        scene()->removeItem(this);
        delete this;
    }
}
