#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "instructions.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>
#include <QTimer>
#include<QPoint>
#include <QDebug>
/*! @brief Constructor of MainWindow that merely displays the UI and sets window title
 */
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("THE DEADLY NIGHTSHADE");
}
/*! @brief Destructor for MainWindow that deletes UI
 */
MainWindow::~MainWindow()
{
    delete ui;
    //qDebug() << "MainWindow Destructor called";
}
/*! @brief Function that ends game by first deleting game_timer. Resets the next_level to 1. Sets the parent of
 * MainWindow to null in order to delete all cleanly. Sets MainWindow to original size.
 */
void MainWindow::game_over(){
    delete game->game_timer;
    next_level = 1;
    QWidget* wid = this->centralWidget();
    wid->setParent(nullptr);
    ui->setupUi(this);
    this->setFixedSize(800,402);
}
/*! @brief Public slot function that shows instructions with button on gameboard is pushed. Freezes energy level. Records time left
 * in game, stops game_timer, LCD timer "clock", stops enemy_timer so that no other enemies spawn. Creates the Instructions
 * object on the heap and passes in stopping_point time left in game. Shows the Instructions window.
 */
void MainWindow::show_instructions(){ 
    game->freeze_energy = true;
    int stopping_point = game->game_timer->remainingTime();
    //qDebug() << stopping_point;
    game->game_timer->stop();
    game->clock->timer->stop();
    game->enemy_timer->stop();
    w = new Instructions(0, game, stopping_point);
    w->show(); //it worked once I changed the scope, and made it a private member on the heap instead of a local cariable
}
/*! @brief Public slot function called at the end of every game within the GameBoard constructor. Displays energy level of player
 * at end of game. States whether player won or lost based on energy level. Sets the next level or resets level if lost.
 *  Also deletes game same way as gameover and sets fized size of MainWindow again.
 */
void MainWindow::show_result()
{
    delete game->game_timer;
    result = new QWidget;
    QVBoxLayout* result_layout = new QVBoxLayout;
    bool win = false;
    next_level = game->level;
    if(game->getEnergyE()>0)
        win = true;
    QLabel* result_label;
    if(win && game->level<3){
         result_label = new QLabel("You had " + QString::number(game->getEnergyE()) + "% energy left. You win!!! \nClick Begin on Homescreen to Start Next Level!\n");
         next_level++;
    }

    else if(win && game->level==3){
        result_label = new QLabel("You had " + QString::number(game->getEnergyE()) + "% energy left. You have defended your homeland!\n");
        next_level = 1;
    }
    else{
        result_label = new QLabel("You had " + QString::number(game->getEnergyE()) + "% energy left. You lost!\n");
        next_level = 1;
    }
    QPushButton* hide_result = new QPushButton("OK");
    hide_result->setMaximumSize(70,20);
    hide_result->setMinimumSize(70,20);
    result_layout->addWidget(result_label);
    result_layout->addWidget(hide_result, 0, Qt::AlignCenter);
    result->setLayout(result_layout);
    result->show();
    QObject::connect(hide_result, SIGNAL(clicked()), result, SLOT(hide()));
    //change it to new window for the next level.
    //delete game;
    //game = nullptr;
    QWidget* wid = this->centralWidget();
    wid->setParent(nullptr);
    //delete game;
    ui->setupUi(this);
    this->setFixedSize(800,402);
}
/*! @brief Public slot function called when "Begin" PushButton is pressed from MainWindow. Creates the GameBoard onject
 * on the heap and sets GameBoard size. Sets GameBoard as the CentralWidget
 */
void MainWindow::easy_game_begin(){

    game = new GameBoard(this, next_level); //When one enemy dies, another will take it's place (there are three types of enemies)
    this->setFixedSize(900,600);//game size
    this->setCentralWidget(game);
}

/*
void MainWindow::medium_game_begin(){
    game = new GameBoard(this, 2); //Two enemies on the board at once
    //show_instructions(); //temporarily hide
    this->setFixedSize(900,600);//game size
    show_game(game);
}
void MainWindow::difficult_game_begin(){
    game = new GameBoard(this, 3); //Three enemies on the board at once
    //show_instructions(); //temporarily hide
    this->setFixedSize(900,600);
    show_game(game);
}
*/
