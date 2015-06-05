#ifndef TERPENE
#define TERPENE
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QObject>
/*! Leah Briscoe PIC10C Spring 2015
 *
 *  @class Terpene
 *  @brief A QGraphicsPixmapItem that serves as the poison bullet of the plant. It is represented by a biohazard graphic. Used
 * to kill bacteria Enemy and Virus. When plant is in photosynthesis, the bullet is replaced by Bolt graphic.
 */
class Terpene: public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    Terpene(size_t id);
public slots:
    void move();
private:
    size_t terpene_id;///< ID to determine movement direction of poison bullet and its impact on enemies.
};

#endif // TERPENE

