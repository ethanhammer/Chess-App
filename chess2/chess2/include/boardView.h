#ifndef BOARDVIEW_H
#define BOARDVIEW_H

#include <QGroupBox>

//whole board view. Goal was to keep it in a square. Unusually hard
class boardView : public QGroupBox
{

public:

    boardView(QWidget *parent = nullptr);
    void resizeEvent(QResizeEvent *event) override;

    ~boardView() = default;
};

#endif // BOARDVIEW_H
