#ifndef ICONLIST_H
#define ICONLIST_H

#include <QListWidget>
#include <QPixmap>

class IconList : public QListWidget
{
    Q_OBJECT

public:
    IconList(QWidget *parent);
    bool setupIconList();
    QSize iconSize() const;

    static QString mimeType() { return QStringLiteral("image/x-program-icon"); }

private:
    QPixmap iconImage;
    bool loadIcons();

    void dragEnterEvent(QDragEnterEvent *event) override;
    void dragMoveEvent(QDragMoveEvent *event) override;
    void startDrag(Qt::DropActions supportedActions) override;
};

#endif // ICONLIST_H
