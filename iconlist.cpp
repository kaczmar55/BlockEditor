#include "iconlist.h"
#include <QScrollBar>
#include <QMessageBox>
#include <QDrag>
#include <QDragEnterEvent>
#include <QMimeData>

IconList::IconList(QWidget *parent)
:QListWidget(parent) {
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    setDragEnabled(true);
    setDragDropMode(QAbstractItemView::DragOnly);
    setWrapping(false);
    setSpacing(10);
    setViewMode(QListView::IconMode);
}

bool IconList::loadIcons() {
    QPixmap newImage;
    if (!newImage.load(QStringLiteral(":/icon.png"))) {
        QMessageBox::warning(this, tr("Open Image"),
                             tr("The image file could not be loaded."),
                             QMessageBox::Close);
        return false;
    }
    iconImage = newImage;
    return true;
}

bool IconList::setupIconList() {
    if(loadIcons() == false)
        return false;

    //int scrollBarSize = qApp->style()->pixelMetric(QStyle::PM_ScrollBarExtent);
    //ui->iconList1->setFixedHeight(iconImage.height() + scrollBarSize);
    for(int i = 0; i < 30; i++) {
        QListWidgetItem *item = new QListWidgetItem();
        item->setIcon(QIcon(iconImage));
        item->setData(Qt::UserRole, QVariant(iconImage));
//        item->setData(Qt::UserRole+1, location);
        item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsDragEnabled);
        item->setText(tr("Text\njakiś"));
        addItem(item);
    }
    return true;
}

void IconList::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasFormat(IconList::mimeType()))
        event->accept();
    else
        event->ignore();
}

void IconList::dragMoveEvent(QDragMoveEvent *event)
{
    if (event->mimeData()->hasFormat(IconList::mimeType())) {
        event->setDropAction(Qt::MoveAction);
        event->accept();
    } else {
        event->ignore();
    }
}

void IconList::startDrag(Qt::DropActions /*supportedActions*/)
{
    QListWidgetItem *item = currentItem();

    QByteArray itemData;
    QDataStream dataStream(&itemData, QIODevice::WriteOnly);
    QPixmap pixmap = qvariant_cast<QPixmap>(item->data(Qt::UserRole));

    dataStream << pixmap << item->text();

    QMimeData *mimeData = new QMimeData;
    mimeData->setData(IconList::mimeType(), itemData);

    QDrag *drag = new QDrag(this);
    drag->setMimeData(mimeData);
    drag->setHotSpot(QPoint(pixmap.width()/2, pixmap.height()/2));
    drag->setPixmap(pixmap);

    drag->exec(Qt::MoveAction);
//    if (drag->exec(Qt::MoveAction) == Qt::MoveAction);
//        delete takeItem(row(item));
}

QSize IconList::iconSize() const {
    return iconImage.size();
}
