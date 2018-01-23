#include "programfieldview.h"

ProgramFieldView::ProgramFieldView(QWidget *parent)
    :QGraphicsView(parent)
{

}

void ProgramFieldView::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
}
