#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QCoreApplication>
#include <QMainWindow>
#include <QWidget>
#include "gameboard.h"
#include "instructions.h"
#include "ui_instructions.h"
class GameBoard;
/*! Leah Briscoe PIC10C Spring 2015
 *
 *  @class MainWindow
 *  @brief Uses the UI to display the main window for the game. Contains QLabels and a single QPushButton to begin game de
 * depending on game level achieved by player. Same MainWindow used at the end of every level of game.
 */
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void game_over();
    void show_instructions();
    void show_result();
    void easy_game_begin();

private:
    QWidget* result; ///< A widget to display whether player moves on to next level at the end of the 1-minute games
    Ui::MainWindow *ui; ///< UI pointer for the MainWindow
    QWidget* instructionsWindow; ///< A widget that helps display the instructions, a UI
    Instructions* w; ///< A Instructions pointer to show instructions widget
    size_t next_level = 1; ///< A size_t variable that keeps track of game level
    GameBoard* game; ///< A pointer to the GameBoard

};

#endif // MAINWINDOW_H
