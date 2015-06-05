#ifndef GAMEBOARD
#define GAMEBOARD
#include "myplant.h"
#include "lcdnumber.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTimer>
#include <QTime>
#include <QWidget>
#include <QLabel>
class Virus;
class Insect;
class Enemy;
class MyPlant;
/*! Leah Briscoe PIC10C Spring 2015
 *  @class GameBoard is a QGraphicsView object that manages the game play
 *  @brief Establishes background graphic, which changes per level. Creates player.
 *  Displays quit and instructions buttons. Displays energy and LCD timer.
 */
class GameBoard: public QGraphicsView{
friend class Virus;
friend class Insect;
friend class Enemy;
friend class MyPlant;
friend class MainWindow;
friend class Instructions;
public:
    explicit GameBoard(QWidget* parent=0, size_t level_num=1);
    ~GameBoard();
    void showEvent(QShowEvent *e);
    QGraphicsScene* scene; ///<Pointer to the scene
    MyPlant* player;///<Pointer to the player MyPlant
    void decreaseE();
    void decreaseEmore();
    void increaseE();
    double getEnergyE();
    size_t level; ///<Level of type size_t to record game level, three in all.


private:
    bool freeze_energy = false; ///<Boolean value to prevent reduction in energy during pausing of the game for instructions
    LCDNumber* clock; ///<LCD clock to display time left for game
    QLabel* energyE_display; ///<Label to display energy level
    double energyE = 100.0; ///<Energy of player established at 100%
    QTimer* game_timer; ///<Actual timer of game
    QTimer* enemy_timer; ///<Timer to determine spawning of enemies
    void drawPanel(int x, int y, int width, int height, QColor color, double opacity);
    void drawGUI();
};

#endif // GAMEBOARD

