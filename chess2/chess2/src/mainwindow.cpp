#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "constants.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow), _board(board())
{

ui->setupUi(this);
createBoardSquares();
createClock();

connect(ui->resetButton, &QPushButton::clicked, this, &MainWindow::restartGame);

}

MainWindow::~MainWindow()
{
    delete ui;
}

// Creates the clock object for the board to use
void MainWindow::createClock() {

    _board.recieveClock(std::make_unique<Clock>(ui->spinBox, ui->whiteClock, ui->blackClock, _board));

}

void MainWindow::restartGame() {
    _board.restartGame();
}

// Creates the board squares (double vector) to be used by the board class
void MainWindow::createBoardSquares() {

    std::vector<std::vector<boardSquare*>> boardSquares(boardSize);
    QSizePolicy policy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    for (int i = 0; i < boardSize; ++i) {
        boardSquares[i].resize(boardSize);
        for (int j = 0; j < boardSize; ++j) {
            auto newBoardSquare = new boardSquare(ui->groupBox, _board, coord(i, j));
            newBoardSquare->setSizePolicy(policy);
            if ((i + j) % 2 == 0) {
                newBoardSquare->setStyleSheet("background-color: white;");
            } else {
                newBoardSquare->setStyleSheet("background-color: grey;");
            }
            ui->gridLayout->addWidget(newBoardSquare, i, j);
            boardSquares[i][j] = newBoardSquare;
        }
    }

    for (int i = 0; i < boardSize; ++i) {
        ui->gridLayout->setRowStretch(i, 1);
    }

    // Hands over the boardSquares
    _board.recieveBoardSquares(std::move(boardSquares));
}


