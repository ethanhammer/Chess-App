
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "board.h"
#include "boardsquare.h"

QT_BEGIN_NAMESPACE

namespace Ui {

class MainWindow;
}

QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:

    Ui::MainWindow *ui;
    board _board;

    // creates these objects and gives a pointer to them to the _board class
    void createClock();
    void createBoardSquares();



public slots:

    // When reset button is pressed
    void restartGame();

};
#endif // MAINWINDOW_H
