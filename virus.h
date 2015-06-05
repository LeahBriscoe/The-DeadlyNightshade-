#ifndef VIRUS
#define VIRUS

#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QObject>
class GameBoard;
/*! Leah Briscoe PIC10C Spring 2015
 *
 *  @class Virus
 *  @brief A QGraphicsPixmapItem that is placed into the GraphicsView of the GameBoard. Virus doesn't move
 * but appears in random locations.
 */
class Virus: public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    Virus(QGraphicsItem* parent, GameBoard* gb);
private:
    GameBoard* board; ///<Pointer to the GameBoard
};

#endif // VIRUS

