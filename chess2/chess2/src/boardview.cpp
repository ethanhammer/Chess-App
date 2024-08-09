#include "boardview.h"
#include <QWidget>

boardView::boardView(QWidget *parent) : QGroupBox(parent) {}

//ensures the sides are all the same size.
void boardView::resizeEvent(QResizeEvent *event) {
    int sideLength = qMin(size().width(), size().height());
    resize(sideLength, sideLength);
}
