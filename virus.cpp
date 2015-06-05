#include "virus.h"
#include <QTimer>
#include <QList>
#include <QGraphicsScene>
#include<random>
#include<chrono>
unsigned seed4 = std::chrono::system_clock::now().time_since_epoch().count();
std::default_random_engine generator4 (seed4);

#include "gameboard.h"
/*! @brief Constructor for virus spawns virus on gameboard at random locations. Virus is a graphic image I created on Paint.
 */
Virus::Virus(QGraphicsItem* parent, GameBoard* gb):QObject(), QGraphicsPixmapItem(parent), board(gb)
{
    board->decreaseE();
    setPixmap(QPixmap(":/characters/Virus.png"));
    int random_number = generator4()%500;//generate random
    int random_number2 = generator4()%500;
    setPos(random_number, random_number2);

}



