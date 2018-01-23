#include "graphicsprogramfield.h"
#include "iconlist.h"

#include <QDrag>
#include <QGraphicsSceneDragDropEvent>
#include <QMimeData>
#include <QPainter>
#include <QGraphicsPixmapItem>
#include <QtMath>
#include <QCheckBox>
#include <QGraphicsProxyWidget>

GraphicsProgramField::GraphicsProgramField(QSize iconSize, ProgramFieldView *view, QWidget *parent)
    : QGraphicsScene(parent), iconSize(iconSize), view(view)
{
    setSceneRect(-10, 0, 500, 100);
    mainItem = addRect(0, iconSize.height(), iconSize.width(), iconSize.height());
   // items.append(mainItem);
//    highlightedRect = new QGraphicsRectItem(0, 0, iconSize.width(), iconSize.height());
//    addItem(highlightedRect);
//    highlightedRect->setVisible(false);
//    highlightedRect->setBrush(QColor("#ffcccc"));
//    highlightedRect->setPen(Qt::NoPen);
}

void GraphicsProgramField::clear()
{
    pieceTexts.clear();
    pieceRects.clear();
    items.clear();
    //items.append(mainItem);
 //   highlightedRect->setVisible(false);
//    update();
}

void GraphicsProgramField::dragEnterEvent(QGraphicsSceneDragDropEvent  *event)
{
    if (event->mimeData()->hasFormat(IconList::mimeType()))
        event->accept();
    else
        event->ignore();
}

void GraphicsProgramField::dragLeaveEvent(QGraphicsSceneDragDropEvent  *event)
{
//    QRect updateRect = highlightedRect;
//    highlightedRect->setVisible(false);
//    update(updateRect);
    event->accept();
}

void GraphicsProgramField::dragMoveEvent(QGraphicsSceneDragDropEvent  *event)
{
//    QRect updateRect = highlightedRect.united(targetSquare(event->scenePos()));

    if (event->mimeData()->hasFormat(IconList::mimeType())
        //&& pieceRects.indexOf(targetSquare(event->scenePos())) == -1) {
         && (itemAt(event->scenePos(), QTransform()) == nullptr)) {

//        QRect rect = targetSquare(event->scenePos());
//        highlightedRect->setX(rect.x());
//        highlightedRect->setY(rect.y());
//        highlightedRect->setVisible(true);
        event->setDropAction(Qt::MoveAction);
        event->accept();
    } else {
//        highlightedRect->setVisible(false);
        event->ignore();
    }

//    update(updateRect);
}

void GraphicsProgramField::dropEvent(QGraphicsSceneDragDropEvent  *event)
{
    if (event->mimeData()->hasFormat(IconList::mimeType())
        && pieceRects.indexOf(targetSquare(event->scenePos())) == -1) {

        QByteArray pieceData = event->mimeData()->data(IconList::mimeType());
        QDataStream dataStream(&pieceData, QIODevice::ReadOnly);
        QRect square = targetSquare(event->scenePos());
        QPixmap pixmap;
        QString text;
        dataStream >> pixmap >> text;

        if((itemAt(event->scenePos(), QTransform()) != nullptr)
                || (itemAt(event->scenePos().x() - iconSize.width(), event->scenePos().y(), QTransform()) != nullptr)) {
            pieceTexts.append(text);
            pieceRects.append(square);

    //        highlightedRect->setVisible(false);
    //        update(square);

            event->setDropAction(Qt::MoveAction);
            event->accept();

            QGraphicsPixmapItem *item = new QGraphicsPixmapItem(pixmap);
            item->setPos(square.x(), square.y());
            item->setCacheMode(QGraphicsItem::DeviceCoordinateCache);
            addItem(item);
            items.append(item);
     /*       QRectF rect = sceneRect();
            if(qAbs(rect.x()) > qAbs(rect.x() + rect.width()))
                rect.setWidth(rect.width() + qAbs(rect.x() - qAbs(rect.x() + rect.width())));
            else {
                rect.setWidth(rect.width() + qAbs(rect.x() + rect.width()) - qAbs(rect.x()));
                rect.setX(rect.x() - qAbs(rect.x() + rect.width()) + qAbs(rect.x()));
            }
            setSceneRect(rect);
            view->ensureVisible(item);*/
            //view->centerOn(0, 0);
        } else {
            event->ignore();
        }
    } else {
//        highlightedRect->setVisible(false);
        event->ignore();
    }
}

/*void GraphicsProgramField::mousePressEvent(QMouseEvent *event)
{
    QRect square = targetSquare(event->scenePos());
    int found = pieceRects.indexOf(square);

    if (found == -1)
        return;

    QString text = pieceTexts[found];
    pieceTexts.removeAt(found);
    pieceRects.removeAt(found);

    update(square);

    QByteArray itemData;
    QDataStream dataStream(&itemData, QIODevice::WriteOnly);

    dataStream << pixmap << text;

    QMimeData *mimeData = new QMimeData;
    mimeData->setData(IconList::mimeType(), itemData);

    QDrag *drag = new QDrag(this);
    drag->setMimeData(mimeData);
    drag->setHotSpot(event->scenePos() - square.topLeft());
    drag->setPixmap(pixmap);

    if (!(drag->exec(Qt::MoveAction) == Qt::MoveAction)) {
        pieceTexts.insert(found, text);
        pieceRects.insert(found, square);
        update(targetSquare(event->scenePos()));
    }
}*/

const QRect GraphicsProgramField::targetSquare(const QPointF &position) const
{
    QRect rect((int)position.x()/iconSize.width() * iconSize.width(), (int)position.y()/iconSize.height() * iconSize.height(), iconSize.width(), iconSize.height());
    if(position.x() < 0)
        rect.setX(rect.x() - iconSize.width());
    if(position.y() < 0)
        rect.setY(rect.y() - iconSize.height());
    return rect;
}
