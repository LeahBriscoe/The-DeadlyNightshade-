#include <gameboard.h>
#include <QGraphicsItem>
#include <QBrush>
#include <QImage>
#include <QPushButton>
#include<QVBoxLayout>
#include<QHBoxLayout>
#include <QGraphicsTextItem>
#include <QDebug>
/*! @brief GameBoard constructor to create QGraphicsScene on the heap
 *  @details Sets background, fixes scene size, Set scene as rectangle of size 900x600.
 * Turns off scroll bars, creates rightside panel to display pushbuttons for Quit and Instructions, labels
 * for game level and energy, LCD clock to display game time leftover. When 61 sec. timer runs out, the game ends and
 * the result is shown.
 *  @param parent the QWidget parent.
 *  @param level_num A size_t value to keep track of game level
 */
GameBoard::GameBoard(QWidget *parent, size_t level_num): level(level_num)
{
    double energyE = 100.0;
    scene = new QGraphicsScene();
    if(level ==1)
        setBackgroundBrush(QBrush(QImage(":/characters/cave_entrance.bmp")));

    if(level== 2)
        setBackgroundBrush(QBrush(QImage(":/characters/Forest-04.png")));
    if(level== 3)
        setBackgroundBrush(QBrush(QImage(":/characters/forest_with_mushroom.bmp")));

    scene->setSceneRect(0,0,900,600);
    setScene(scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(900,600);
    QGraphicsTextItem* brief = new QGraphicsTextItem;
    brief->setPlainText(QString("View Instructions to PAUSE game. [Arrows] to move, [SPACE] to shoot"));
    brief->setDefaultTextColor(Qt::white);
    brief->setFont(QFont("times", 17));
    brief->setPos(10, 0);
    scene->addItem(brief);
    QGraphicsTextItem* warning = new QGraphicsTextItem;
    warning->setPlainText(QString("Click on the Plant to Activate if it Becomes Unresponsive"));
    warning->setDefaultTextColor(Qt::white);
    warning->setFont(QFont("times", 17));
    warning->setPos(10, 20);
    scene->addItem(warning);
    QGraphicsTextItem* warning2 = new QGraphicsTextItem;
    warning2->setPlainText(QString("When energy is low, [X] to activate photosynthesis, [SPACE] to charge up, [Z] to exit photosynthesis"));
    warning2->setDefaultTextColor(Qt::white);
    warning2->setFont(QFont("times", 17));
    warning2->setPos(10, 40);
    scene->addItem(warning2);

    drawGUI();
    QVBoxLayout* right_panel = new QVBoxLayout;
    QPushButton* quit_button = new QPushButton("Quit Now");
    QObject::connect(quit_button, SIGNAL(clicked()), parent, SLOT(game_over()));
    right_panel->addWidget(quit_button, 0, Qt::AlignRight);
    QPushButton* instructions_button = new QPushButton("Instructions");
    QObject::connect(instructions_button, SIGNAL(clicked()), parent, SLOT(show_instructions()));
    right_panel->addWidget(instructions_button, 0, Qt::AlignRight);
    QLabel* level_display = new QLabel(QString("Level: ") + QString::number(level));
    level_display->setStyleSheet("QLabel {background-color: black; color: white;}");
    level_display->setFrameStyle(3);
    level_display->setMaximumSize(65,50);
    level_display->setMinimumSize(65,50);
    right_panel->addWidget(level_display, 0, Qt::AlignRight);
    energyE_display = new QLabel(QString("Energy: ") + QString::number(energyE) + QString("%"));
    energyE_display->setStyleSheet("QLabel {background-color: yellow; color: black;}");
    energyE_display->setFrameStyle(3);
    energyE_display->setMaximumSize(100,50);
    energyE_display->setMinimumSize(100,50);
    right_panel->addWidget(energyE_display, 0, Qt::AlignRight);

    QWidget* countdown= new QWidget(this);
    clock = new LCDNumber(countdown, 1, 0);//Got rid of architecture error by deleting semicolons in header
    clock->setFixedSize(100,100);
    right_panel->addWidget(clock, 0, Qt::AlignRight);
    clock->timer->start(1000);
    this->setLayout(right_panel);
    //start_timer();
    game_timer = new QTimer();
     //previously 61000
    QWidget::connect(game_timer, SIGNAL(timeout()), parent, SLOT(show_result()));
    game_timer->start(62000);
}
/*! @brief GameBoard destructor. Clears scene.
 */
GameBoard::~GameBoard(){

    scene->clear();
    //qDebug()<<"GameBoard Destructor called."
}
/*! @brief Calls drawPanel to create a light blue panel on the right side
 */
void GameBoard::drawGUI()
{
    //draw left Panel
    drawPanel(750,0, 150, 600, Qt::darkCyan, 0.5);
}
/*! @brief Creates player on the heap and adds to the scene. Also creates enemy_timer on the heap
 * so that enemies spawn every 1.6 seconds
 *  @param QShowEvent pointer
 */
void GameBoard::showEvent(QShowEvent *e){

    player = new MyPlant(0, this);
    player->setPos((width()/2)-50, height()/2-50);
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    scene->addItem(player);

    //spawn enemies
    enemy_timer = new QTimer();
    QWidget::connect(enemy_timer, SIGNAL(timeout()), player, SLOT(spawn()));
    enemy_timer->start(1600);
    player->setFocus();

    show();
    this->activateWindow();
    this->setFocus();
    QWidget::showEvent(e);
}
/*! @brief Creates the panel by establishing dimensions passed in by drawGUI. Adds panel to the scene
 *  @param x the x-coordinate of panel
 *  @param y the y-coordinate of panel
 *  @param width the width of panel
 *  @param height the height of panel
 *  @param color the color of the panel according to html
 *  @param opacity the opacity of panel
 */
void GameBoard::drawPanel(int x, int y, int width, int height, QColor color, double opacity)
{
   //draws a panel at specified location with specified properties
    QGraphicsRectItem* panel = new QGraphicsRectItem(x, y, width, height);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(color);
    panel->setBrush(brush);
    panel->setOpacity(opacity);
    scene->addItem(panel);
}
/*! @brief Decreases the energy level of player by 1 unit. Function is called in player function upon collision with Virus.
 * Called when player uses shoots bullets. Must redisplay energy level by setting text
 */
void GameBoard::decreaseE(){
    if(freeze_energy == false){ //if game not paused can act
        energyE--;
    }
    energyE_display->setText(QString("Energy: ") + QString::number(energyE) + QString("%"));
}
/*! @brief Decreases the energy level of player by 5 units. Called by each enemy when it leaves the screen without being destroyed.
 * Must redisplay energy level by setting text.
 */
void GameBoard::decreaseEmore()
{
    if(freeze_energy == false){
        energyE-=5;
    }
    energyE_display->setText(QString("Energy: ") + QString::number(energyE) + QString("%"));
}
/*! @brief Increases energy by 1 unit. Called when plant is photosynthesizing, by spacebar key event,
 */
void GameBoard::increaseE()
{
    if(energyE < 100)
        energyE++;
    energyE_display->setText(QString("Energy: ") + QString::number(energyE) + QString("%"));
}
/*! @brief Getter function to return energy level for classes without friendship access.
 */
double GameBoard::getEnergyE(){
    return energyE;
}

