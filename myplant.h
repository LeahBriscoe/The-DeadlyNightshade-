#ifndef MYPLANT
#define MYPLANT
#include "Terpene.h"
#include "Enemy.h"
#include "Insect.h"
#include "virus.h"
#include <QGraphicsRectItem>
#include<QGraphicsPixmapItem>
#include <QPaintEvent>
#include <QKeyEvent>
#include <QObject>

class GameBoard;
/*! Leah Briscoe PIC10C Spring 2015
 *
 *  @class MyPlant
 *  @brief A QGraphicsPixmapItem that is placed into the GraphicsView of the GameBoard. The plant can move
 * with Key Press events of the arrow keys and can shoot with spacebar. Keeps track of colliding graphics items.
 */
class MyPlant: public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    MyPlant(QGraphicsItem * parent, GameBoard* gb);
    void keyPressEvent(QKeyEvent *event);

public slots:
    void spawn();
    void viral_infection();
private:
    GameBoard* board;///< GameBoard pointer
    Virus* enemy3;///< Pointer to the virus
    bool can_defend; ///< Bool value that determines if player can move and shoot
};

#endif // MYPLANT

