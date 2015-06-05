#ifndef ENEMY
#define ENEMY
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QObject>
class GameBoard;
/*! Leah Briscoe PIC10C Spring 2015
 *
 *  @class Enemy of MyPlant for the graphics view of GameBoard
 *  @brief Creates a Bacteria character that moves down the GameBoard.
 *         Added to board when MyPlant spawn function called.
 */
class Enemy: public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    Enemy(QGraphicsItem* parent, GameBoard* gb);
public slots:
    void move();
private:
    GameBoard* board;

};

#endif // ENEMY

