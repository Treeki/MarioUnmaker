#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsScene>
#include <QFile>
#include <QDataStream>
#include <QGraphicsRectItem>

enum ObjType {
#define MM_OBJECT(id, name) name = id,
#include "objecttypes.h"
#undef MM_OBJECT
};

const char *objectNames[] = {
#define MM_OBJECT(id, name) #name,
#include "objecttypes.h"
#undef MM_OBJECT
};

MainWindow::MainWindow(const QString &path, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(m_scene);
    ui->graphicsView->setDragMode(QGraphicsView::RubberBandDrag);

    connect(m_scene, SIGNAL(selectionChanged()), this, SLOT(handleSceneSelectionChanged()));

    QHash<int, QColor> colours;
    colours[EditRengaBlock] = QColor(158, 95, 25);
    colours[EditHatenaBlock] = Qt::yellow;
    colours[EditHardBlock] = QColor(212, 162, 103);
    colours[EditKumoBlock] = QColor(255, 252, 255); // cloud
    colours[EditKuribo] = QColor(158, 95, 25);
    colours[EditDokan] = QColor(182, 237, 57);
    colours[EditGround] = QColor(75, 202, 13);
    colours[EditIceBlock] = Qt::cyan;
    colours[EditTsuta] = QColor(52, 190, 48); // vine
    colours[EditSaw] = QColor(155, 183, 175);


    QFile f(path);
    f.open(QFile::ReadOnly);
    QDataStream ds(&f);

    f.seek(0xEC);
    quint32 objCount;
    ds >> objCount;

    ui->objectList->setRowCount(objCount);
    ui->objectList->setColumnCount(9);
    ui->objectList->setHorizontalHeaderItem(0, new QTableWidgetItem("Type"));
    ui->objectList->setHorizontalHeaderItem(1, new QTableWidgetItem("Name"));
    ui->objectList->setHorizontalHeaderItem(2, new QTableWidgetItem("X"));
    ui->objectList->setHorizontalHeaderItem(3, new QTableWidgetItem("Y"));
    ui->objectList->setHorizontalHeaderItem(4, new QTableWidgetItem("Z"));
    ui->objectList->setHorizontalHeaderItem(5, new QTableWidgetItem("Width"));
    ui->objectList->setHorizontalHeaderItem(6, new QTableWidgetItem("Height"));
    ui->objectList->setHorizontalHeaderItem(7, new QTableWidgetItem("Unk2"));
    ui->objectList->setHorizontalHeaderItem(8, new QTableWidgetItem("Unk3"));

    for (int i = 0; i < objCount; i++) {
        quint16 x, y;
        qint32 z;
        QByteArray unkblob2, unkblob3;
        quint8 objType, w, h;

        ds.skipRawData(2);
        ds >> x;
        ds >> z;
        ds >> y;
        ds >> w >> h;
        unkblob2 = f.read(12);
        ds >> objType;
        unkblob3 = f.read(7);

        qreal rx = x / 10, ry = -y / 10, rz = z / 10;
        ry -= (h - 1) * 16;
        qreal rw = w * 16, rh = h * 16;
        QGraphicsItem *item;

        switch (objType) {
        case EditCoin:
        {
            auto ei = new QGraphicsEllipseItem(rx + 1, ry, rw - 2, rh);
            ei->setBrush(Qt::yellow);
            item = ei;
            break;
        }
        case EditKuribo:
        {
            auto ei = new QGraphicsEllipseItem(rx, ry, rw, rh);
            ei->setBrush(colours[EditKuribo]);
            item = ei;
            break;
        }
        case EditSaw:
        {
            auto ei = new QGraphicsEllipseItem(rx, ry, rw, rh);
            ei->setBrush(colours[EditSaw]);
            item = ei;
            break;
        }
        case EditTsuta:
        {
            auto ri = new QGraphicsRectItem(rx + 6, ry, rw - 12, rh);
            ri->setBrush(colours[EditTsuta]);
            item = ri;
            break;
        }
        case EditPoo: // wrench
        {
            auto ri = new QGraphicsRectItem(rx, ry + 12, rw, rh - 12);
            ri->setBrush(QColor(64, 64, 64));
            item = ri;
            break;
        }
        case EditDoor:
        {
            auto ri = new QGraphicsRectItem(rx, ry - 16, rw, rh);
            ri->setBrush(QColor(192, 187, 65));
            item = ri;
            break;
        }
        case EditLift:
        {
            auto ri = new QGraphicsRectItem(rx, ry, rw, rh - 12);
            ri->setBrush(QColor(192, 187, 65));
            item = ri;
            break;
        }
        default:
        {
            auto ri = new QGraphicsRectItem(rx, ry, rw, rh);
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
        ui->objectList->setItem(i, 1, new QTableWidgetItem(objectNames[objType]));
        ui->objectList->setItem(i, 2, new QTableWidgetItem(QString::number(x)));
        ui->objectList->setItem(i, 3, new QTableWidgetItem(QString::number(y)));
        ui->objectList->setItem(i, 4, new QTableWidgetItem(QString::number(rz)));
        ui->objectList->setItem(i, 5, new QTableWidgetItem(QString::number(w)));
        ui->objectList->setItem(i, 6, new QTableWidgetItem(QString::number(h)));
        ui->objectList->setItem(i, 7, new QTableWidgetItem(QString(unkblob2.toHex())));
        ui->objectList->setItem(i, 8, new QTableWidgetItem(QString(unkblob3.toHex())));
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
