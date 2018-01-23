#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QScrollBar>
#include <QFrame>
#include <QVBoxLayout>
#include "programfieldview.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    iconTabs = new QTabWidget;
    iconTabs->setSizePolicy(QSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed));
    QWidget *tab = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout();
    iconList1 = new IconList(nullptr);
    layout->addWidget(iconList1);
    tab->setLayout(layout);
    iconTabs->addTab(tab, tr("tab1"));
    if(iconList1->setupIconList() == true) {
        iconList1->updateGeometry();
        int scrollBarSize = iconList1->horizontalScrollBar()->height();
        iconList1->setFixedHeight(iconList1->sizeHintForRow(0) + scrollBarSize + 10);
        iconTabs->adjustSize();
    }

    ProgramFieldView *view = new ProgramFieldView();
    graphicProgramField = new GraphicsProgramField(iconList1->iconSize(), view);
    view->setScene(graphicProgramField);

    QWidget *widget = new QWidget;
    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addWidget(iconTabs);
    mainLayout->addWidget(view);
    widget->setLayout(mainLayout);
    setCentralWidget(widget);
}

MainWindow::~MainWindow()
{
    delete ui;
}
