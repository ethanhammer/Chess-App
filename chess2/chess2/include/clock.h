#ifndef CLOCK_H
#define CLOCK_H

#include <QSpinBox>
#include <QLabel>
#include <QTimer>
#include <QObject>
#include <memory>
#include <string>

class board;

class Clock : public QObject {
    Q_OBJECT

public:

    Clock(QSpinBox* input, QLabel* whiteOutput, QLabel* blackOutput, board& board);

    void startTimer(const std::string& currentTurn);
    void resetTimers();
    void setTimerDisplay(const std::string& color);

private:

    // Reference to the board
    board& _board;

    // Timer values in seconds
    int _whiteTime;
    int _blackTime;

    // UI elements
    QSpinBox* _input;
    QLabel* _whiteOutput;
    QLabel* _blackOutput;

    // Timers for each player
    std::unique_ptr<QTimer> _whiteTimer;
    std::unique_ptr<QTimer> _blackTimer;

private slots:

    // Slot functions to update timers
    void updateWhiteTimer();
    void updateBlackTimer();
};

#endif // CLOCK_H
