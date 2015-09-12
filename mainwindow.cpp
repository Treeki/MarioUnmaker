#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsScene>
#include <QFile>
#include <QDataStream>
#include <QGraphicsRectItem>

enum ObjType {
    OT_Brick = 4,
    OT_Question = 5,
    OT_WoodBlock = 6,
    OT_Ground = 7,
    OT_Coin = 8,
    OT_Platform = 11,
    OT_Flamethrower = 54,
    OT_Door = 55,
    OT_Wrench = 58,
    OT_ChainChomp = 61,
    OT_IceBlock = 63,
    // 16 = Mystery!
    // 38 = Entrance? Or Sign?
};

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(m_scene);
    ui->graphicsView->setDragMode(QGraphicsView::RubberBandDrag);

    connect(m_scene, SIGNAL(selectionChanged()), this, SLOT(handleSceneSelectionChanged()));

    QHash<int, QString> names;
    names[OT_Brick] = "Brick";
    names[OT_Question] = "Question Block";
    names[OT_WoodBlock] = "Wood Block";
    names[OT_Ground] = "Ground";
    names[OT_Coin] = "Coin";
    names[OT_Flamethrower] = "Flamethrower";
    names[OT_Door] = "Door";
    names[OT_Wrench] = "Wrench";
    names[OT_ChainChomp] = "Chain Chomp";
    names[OT_IceBlock] = "Ice Block";

    QHash<int, QColor> colours;
    colours[OT_Brick] = QColor(158, 95, 25);
    colours[OT_Question] = Qt::yellow;
    colours[OT_WoodBlock] = QColor(212, 162, 103);
    colours[OT_Ground] = QColor(75, 202, 13);
    colours[OT_IceBlock] = Qt::cyan;


    QFile f("D:\\crap\\wiiu\\smm\\sample_course_data_01.cdt");
    f.open(QFile::ReadOnly);
    QDataStream ds(&f);

    f.seek(0xEC);
    quint32 objCount;
    ds >> objCount;

    ui->objectList->setRowCount(objCount);
    ui->objectList->setColumnCount(7);
    ui->objectList->setHorizontalHeaderItem(0, new QTableWidgetItem("Type"));
    ui->objectList->setHorizontalHeaderItem(1, new QTableWidgetItem("Name"));
    ui->objectList->setHorizontalHeaderItem(2, new QTableWidgetItem("X"));
    ui->objectList->setHorizontalHeaderItem(3, new QTableWidgetItem("Y"));
    ui->objectList->setHorizontalHeaderItem(4, new QTableWidgetItem("Unk1"));
    ui->objectList->setHorizontalHeaderItem(5, new QTableWidgetItem("Unk2"));
    ui->objectList->setHorizontalHeaderItem(6, new QTableWidgetItem("Unk3"));

    for (int i = 0; i < objCount; i++) {
        quint16 x, y;
        qint32 unk1;
        QByteArray unkblob2, unkblob3;
        quint8 objType;

        ds.skipRawData(2);
        ds >> x;
        ds >> unk1;
        ds >> y;
        unkblob2 = f.read(14);
        ds >> objType;
        unkblob3 = f.read(7);

        qreal rx = x / 10, ry = -y / 10;
        QGraphicsItem *item;

        switch (objType) {
        case OT_Coin:
        {
            auto ei = new QGraphicsEllipseItem(rx + 1, ry, 14, 16);
            ei->setBrush(Qt::yellow);
            item = ei;
            break;
        }
        case OT_Wrench:
        {
            auto ri = new QGraphicsRectItem(rx, ry + 12, 16, 4);
            ri->setBrush(QColor(64, 64, 64));
            item = ri;
            break;
        }
        case OT_Door:
        {
            auto ri = new QGraphicsRectItem(rx, ry - 16, 16, 32);
            ri->setBrush(QColor(192, 187, 65));
            item = ri;
            break;
        }
        case OT_Platform:
        {
            auto ri = new QGraphicsRectItem(rx, ry, 16, 4);
            ri->setBrush(QColor(192, 187, 65));
            item = ri;
            break;
        }
        default:
        {
            auto ri = new QGraphicsRectItem(rx, ry, 16, 16);
            if (colours.contains(objType))
                ri->setBrush(colours[objType]);
            else
                ri->setBrush(Qt::magenta);
            item = ri;
            break;
        }
        }
        QString tooltip = QString::number(objType);
        item->setToolTip(tooltip);

        item->setFlag(QGraphicsItem::ItemIsMovable);
        item->setFlag(QGraphicsItem::ItemIsSelectable);
        m_scene->addItem(item);
        m_items.push_back(item);

        ui->objectList->setItem(i, 0, new QTableWidgetItem(QString::number(objType)));
        ui->objectList->setItem(i, 1, new QTableWidgetItem(names[objType]));
        ui->objectList->setItem(i, 2, new QTableWidgetItem(QString::number(x)));
        ui->objectList->setItem(i, 3, new QTableWidgetItem(QString::number(y)));
        ui->objectList->setItem(i, 4, new QTableWidgetItem(QString::number(unk1)));
        ui->objectList->setItem(i, 5, new QTableWidgetItem(QString(unkblob2.toHex())));
        ui->objectList->setItem(i, 6, new QTableWidgetItem(QString(unkblob3.toHex())));
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::handleSceneSelectionChanged()
{
    auto items = m_scene->selectedItems();
    if (items.size() == 1) {
        int index = m_items.indexOf(items[0]);
        //ui->objectList->setCurrentRow(index);
        ui->objectList->setCurrentCell(index, 0);
    }
}

void MainWindow::on_objectList_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn)
{
    if (currentRow != previousRow) {
        m_scene->clearSelection();
        m_items[currentRow]->setSelected(true);
    }
}
