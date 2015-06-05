#include "Terpene.h"
#include "enemy.h"
#include "virus.h"
#include <QTimer>
#include <QList>
#include <QGraphicsScene>

/*! @brief Constructor for Terpene, established ID number in the initializer list. Moves every 50 ms. ID under 9 means
 * poison bullet represented by Biohazard symbol. ID above 9 represented by Bolt symbol.
 */
Terpene::Terpene(size_t id): QObject(), QGraphicsPixmapItem(), terpene_id(id)
{
    if(terpene_id<9){
        setPixmap(QPixmap(":/characters/BiohazardSmall.png"));
    }
    else{
        setPixmap(QPixmap(":/characters/Bolt.png"));
    }
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));

    timer->start(50);
}

/*! @brief Public slot Function that moves the poison bullet in a specified direction (northwest, northeast, southeast, southwest).
 *  @details If bullet collides with an Enemy bacteria or Virus, then both items are removed from scene and deleted from the heap. When the plant
 * is undergoing photosynthesis, two different kind of bullets are produced in the form of bolts that only appear at the top corner of the plant,
 * and they move much faster. When bullet is out of play area it is removed from scene and destroyed.
 */

void Terpene::move()
{

    //if terpene hits enemy kill both, every Graphics item has colliding function
    QList <QGraphicsItem*> colliding_items = collidingItems();
    for(auto i: colliding_items){
        if(terpene_id < 9){
            if(typeid(*i) == typeid(Enemy) || typeid(*i) == typeid(Virus)){
                //remove them both
                scene() -> removeItem(i);
                scene()->removeItem(this);
                //remove them from the heap
                delete i;
                delete this;
                return;// so the following code isn't run
            }
        }
    }
    if(terpene_id == 1){
        setPos(x()-7, y()-7);
    }
    if(terpene_id == 2){
        setPos(x(), y()-10);
    }
    if(terpene_id == 3){
        setPos(x()+7, y()-7);
    }
    if(terpene_id == 4){
        setPos(x()+10, y());
    }
    if(terpene_id == 5){
        setPos(x()+7, y()+7);
    }
    if(terpene_id == 6){
        setPos(x(), y()+10);
    }
    if(terpene_id == 7){
        setPos(x()-7, y()+7);
    }
    if(terpene_id == 8){
        setPos(x()-10, y());
    }
    if(terpene_id == 9){
        setPos(x()-100, y()-100);
    }
    if(terpene_id == 10){
        setPos(x()+100, y()-100);
    }
    //remove terpene bullet if it goes out of the play area
    if(pos().y() < 0 || pos().y()>600 || pos().x() < 0 || pos().x()>750){
        scene()->removeItem(this);
        delete this;
    }

}
