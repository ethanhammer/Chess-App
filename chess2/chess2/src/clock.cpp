#include "clock.h"
#include "board.h"

// Constructor for Clock class
Clock::Clock(QSpinBox* input, QLabel* whiteOutput, QLabel* blackOutput, board& board)
    : _whiteOutput(whiteOutput),         // Output display for white player's time
    _blackOutput(blackOutput),         // Output display for black player's time
    _board(board),                     // Reference to the game board
    _whiteTime(600),
    _input(input),                     // SpinBox for setting initial timer value
    _blackTime(600),
    _whiteTimer(std::make_unique<QTimer>(this)),
    _blackTimer(std::make_unique<QTimer>(this)) {

    // Connect QTimer signals
    connect(_whiteTimer.get(), &QTimer::timeout, this, &Clock::updateWhiteTimer);
    connect(_blackTimer.get(), &QTimer::timeout, this, &Clock::updateBlackTimer);
}

// Starts the timer for the current player's turn
void Clock::startTimer(const std::string& currentTurn) {
    if (currentTurn == "white") {
        _blackTimer->stop();
        _whiteTimer->start(1000); // Start white's timer with 1-second interval
    } else {
        _whiteTimer->stop();
        _blackTimer->start(1000); // Start black's timer with 1-second interval
    }
}

// Resets both timers to the initial value set by the user
void Clock::resetTimers() {
    _whiteTimer->stop();
    _blackTimer->stop();

    // Set timers to the initial value (in seconds)
    _whiteTime = _input->value() * 60;
    _blackTime = _input->value() * 60;

    // Update display for both timers
    setTimerDisplay("white");
    setTimerDisplay("black");
}

// Updates the timer display based on the player's color
void Clock::setTimerDisplay(const std::string& color) {
    if (color == "white") {
        int minutes = _whiteTime / 60;
        int seconds = _whiteTime % 60;


        QString print = QString::number(minutes) + ":" + ((seconds < 10) ? "0" : "") + QString::number(seconds);
        _whiteOutput->setText(print);
    }
    if (color == "black") {
        int minutes = _blackTime / 60;
        int seconds = _blackTime % 60;


        QString print = QString::number(minutes) + ":" + ((seconds < 10) ? "0" : "") + QString::number(seconds);
        _blackOutput->setText(print);
    }
}

// Slot to update the white player's timer
void Clock::updateWhiteTimer() {
    _whiteTime--;
    if (_whiteTime == 0) {
        _board.endGame("black"); // End game if white's time runs out
        _whiteTimer->stop();
    }
    setTimerDisplay("white");
}

// Slot to update the black player's timer
void Clock::updateBlackTimer() {
    _blackTime--;
    if (_blackTime == 0) {
        _board.endGame("white"); // End game if black's time runs out
        _blackTimer->stop();
    }
    setTimerDisplay("black");
}
