#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "iconlist.h"
#include "programfield.h"
#include "graphicsprogramfield.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    IconList *iconList1;
    GraphicsProgramField *graphicProgramField;
    QTabWidget *iconTabs;
    bool loadIcons();
    void setupIconList();
};

#endif // MAINWINDOW_H
