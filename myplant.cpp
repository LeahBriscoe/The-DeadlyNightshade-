#include "myplant.h"
#include "gameboard.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include<random>
#include<chrono>
unsigned seed3 = std::chrono::system_clock::now().time_since_epoch().count();
std::default_random_engine generator3 (seed3);

#include <QDebug>
/*! @brief Constructor for MyPlant activates mobility and poison of player. Sets the graphic of a belladonna plant, I created on Paintbrush.
 *  @param parent a pointer to the QGraphicsItem
 *  @param gb A pointer to the GameBoard passed in.
 */

MyPlant::MyPlant(QGraphicsItem* parent, GameBoard* gb): QGraphicsPixmapItem(parent), board(gb)
{
    can_defend = true;
    setPixmap(QPixmap(":/characters/BelladonnaFinal.png"));
}
/*! @brief Overloads KeyPressEvent so that player responds to keyboard events.
 *  @details Creates QList for all colliding QGraphicsItems
 * Checks if Insect collides, then removes insect from scene and deletes. Check if Enemy bacteria or Virus collides and reduces energy.
 * Arrow keys to move plant and space to create bullets on the four corners or charge when photosynthesis is activated. X key to begin photosynthesis. Z key to exit
 * photosynthesis. This function determines starting location of bullets. The function also changes the Pixmap item to represent photosynthesis, the bullets also change to
 * bolts and only shoot out from the top two corners to represent charging from solar energy.
 *  @param event is the QKeyEvent pointer
 */
void MyPlant::keyPressEvent(QKeyEvent *event)
{
    //qDebug() << "MyPlant knows that you pressed a key";
    QList <QGraphicsItem*> colliding_items = collidingItems();
    for(auto i: colliding_items){
        //By ramming into the bug, the plant destroys the bug
        if(typeid(*i) == typeid(Insect)){
            //remove them both
            scene() -> removeItem(i);
            //remove them from the heap
            delete i;
        }

        if(typeid(*i) == typeid(Enemy)){
            board->decreaseE();
        }
        if(typeid(*i) == typeid(Virus)){
            board->decreaseE();
        }
    }

    if(event->key() == Qt::Key_Left && can_defend == true){
        if(pos().x() > 0)
            setPos(x()-20, y());
    }
    else if(event->key() == Qt::Key_Right && can_defend == true){
        if(pos().x()+150 < 750)
            setPos(x()+20, y());
    }
    else if(event->key() == Qt::Key_Up && can_defend == true){
        if(pos().y() > 100)
            setPos(x(), y()-20);
    }
    else if(event->key() == Qt::Key_Down && can_defend == true){
        if(pos().y()+120 < 600)
            setPos(x(), y()+20);
    }
    else if(event->key() == Qt::Key_Space && can_defend == true){
        //Create 8 terpene objects in total
        board->decreaseE();
        //create a Northwest Terpene
        Terpene* terpene_nw = new Terpene(1);
        terpene_nw->setPos(x(), y());
        scene()->addItem(terpene_nw);
        /*create a North Terpene
        Terpene* terpene_n = new Terpene(2);
        terpene_n->setPos(x()+45, y());
        scene()->addItem(terpene_n);*/
        //create a Northeast Terpene
        Terpene* terpene_ne = new Terpene(3);
        terpene_ne->setPos(x()+90, y());
        scene()->addItem(terpene_ne);
        /*create a East Terpene
        Terpene* terpene_e = new Terpene(4);
        terpene_e->setPos(x()+90, y()+45);
        scene()->addItem(terpene_e);*/
        //create a Southeast Terpene
        Terpene* terpene_se = new Terpene(5);
        terpene_se->setPos(x()+90, y()+90);
        scene()->addItem(terpene_se);
        /*create a South Terpene
        Terpene* terpene_s = new Terpene(6);
        terpene_s->setPos(x()+45, y()+90);
        scene()->addItem(terpene_s);*/
        //create a Southwest Terpene
        Terpene* terpene_sw = new Terpene(7);
        terpene_sw->setPos(x(), y()+90);
        scene()->addItem(terpene_sw);
        /*create a West Terpene
        Terpene* terpene_w = new Terpene(8);
        terpene_w->setPos(x(), y()+45);
        scene()->addItem(terpene_w);*/

    }
    //Start photosynthesis
    else if(event->key() == Qt::Key_X && can_defend == true){
        setPixmap(QPixmap(":/characters/BelladonnaEnergize.png"));
        can_defend = false;

    }
    else if(event->key() == Qt::Key_Space && can_defend == false){
        board->increaseE();
        Terpene* bolt = new Terpene(9);
        bolt->setPos(x(), y());
        scene()->addItem(bolt);
        Terpene* bolt_two = new Terpene(10);
        bolt_two->setPos(x()+90, y());
        scene()->addItem(bolt_two);

    }
    else if(event->key() == Qt::Key_Z){
        can_defend = true;
        setPixmap(QPixmap(":/characters/BelladonnaFinal.png"));
        this->setFocus();

    }
}
/*! @brief Spawn function creates enemies of various types depending on game level.
 *  @details For level 1, creates two bacteria Enemies each timeout. For level 2, creates bacteria Enemy and Insect enemy for each timeout.
 *  For level 3, creates one bacteria Enemy, one Insect, and calls special Virus spawn function that spawns viruses at every 10 seconds.
 *  Timer within timer for Virus spawning results in increasingly greater numbers of Virus appearing on the board.
 */
void MyPlant::spawn()
{
    if(board->level==1){
        Enemy* enemy = new Enemy(0, board);
        scene()->addItem(enemy);
        Enemy* enemy2 = new Enemy(0, board);
        scene()->addItem(enemy2);
    }
    if(board->level==2){
        Enemy* enemy1 = new Enemy(0, board);
        scene()->addItem(enemy1);
        Insect* enemy2 = new Insect(0, board);
        scene()->addItem(enemy2);
    }
    if(board->level==3){
        Enemy* enemy1 = new Enemy(0, board);
        scene()->addItem(enemy1);

        Insect* enemy2 = new Insect(0, board);
        scene()->addItem(enemy2);

        QTimer *timer = new QTimer(this);
        connect(timer, SIGNAL(timeout()), this, SLOT(viral_infection()));
        timer->start(10000);
    }
}
/*! Function viral_infection spawns the viruses for each 10 second timeout.
 */
void MyPlant::viral_infection()
{
    enemy3 = new Virus(0, board);
    scene()->addItem(enemy3);

}



