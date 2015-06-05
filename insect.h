#ifndef INSECT
#define INSECT
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QObject>
class GameBoard;
/*! Leah Briscoe PIC10C Spring 2015
 *
 *  @class Insect enemy of MyPlant for the graphics view of GameBoard
 *  @brief Creates a bug character that moves right to left across GameBoard.
 *         Added to board when MyPlant spawn function called, called only in game levels 2 and 3.
 */
class Insect: public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    Insect(QGraphicsItem* parent, GameBoard* gb);
public slots:
    void move();
private:
    GameBoard* board; ///<Pointer to the GameBoard
};
#endif // INSECT

