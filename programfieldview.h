#ifndef PROGRAMFIELDVIEW_H
#define PROGRAMFIELDVIEW_H

#include <QGraphicsView>

class ProgramFieldView : public QGraphicsView
{
protected:
    void resizeEvent(QResizeEvent *event) override;
public:
    ProgramFieldView(QWidget *parent = nullptr);
};

#endif // PROGRAMFIELDVIEW_H
