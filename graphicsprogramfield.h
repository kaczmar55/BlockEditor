#ifndef GRAPHICSPROGRAMFIELD_H
#define GRAPHICSPROGRAMFIELD_H

#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include "programfieldview.h"

class GraphicsProgramField : public QGraphicsScene
{
public:
    GraphicsProgramField(QSize iconSize, ProgramFieldView *view, QWidget *parent = nullptr);
    void clear();

protected:
    void dragEnterEvent(QGraphicsSceneDragDropEvent  *event) override;
    void dragLeaveEvent(QGraphicsSceneDragDropEvent  *event) override;
    void dragMoveEvent(QGraphicsSceneDragDropEvent  *event) override;
    void dropEvent(QGraphicsSceneDragDropEvent  *event) override;
//    void mousePressEvent(QMouseEvent *event) override;

private:
    const QRect targetSquare(const QPointF &position) const;

    QList<QRect> pieceRects;
    QList<QGraphicsPixmapItem*> items;
    QList<QString> pieceTexts;
    //QGraphicsRectItem *highlightedRect;
    QSize iconSize;
    QGraphicsView *view;
    QGraphicsItem* mainItem;
};

#endif // GRAPHICSPROGRAMFIELD_H
