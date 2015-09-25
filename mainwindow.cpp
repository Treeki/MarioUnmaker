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
    ui->objectList->setColumnCount(14);
    ui->objectList->setHorizontalHeaderItem(0, new QTableWidgetItem("X"));
    ui->objectList->setHorizontalHeaderItem(1, new QTableWidgetItem("Y"));
    ui->objectList->setHorizontalHeaderItem(2, new QTableWidgetItem("Z"));
    ui->objectList->setHorizontalHeaderItem(3, new QTableWidgetItem("Width"));
    ui->objectList->setHorizontalHeaderItem(4, new QTableWidgetItem("Height"));
    ui->objectList->setHorizontalHeaderItem(5, new QTableWidgetItem("Parent Name"));
    ui->objectList->setHorizontalHeaderItem(6, new QTableWidgetItem("Parent Flags"));
    ui->objectList->setHorizontalHeaderItem(7, new QTableWidgetItem("Child Object"));
    ui->objectList->setHorizontalHeaderItem(8, new QTableWidgetItem("Child Flags"));
    ui->objectList->setHorizontalHeaderItem(9, new QTableWidgetItem("_14"));
    ui->objectList->setHorizontalHeaderItem(10, new QTableWidgetItem("Pipe Link ID"));
    ui->objectList->setHorizontalHeaderItem(11, new QTableWidgetItem("_1C"));
    ui->objectList->setHorizontalHeaderItem(12, new QTableWidgetItem("_1E"));
    ui->objectList->setHorizontalHeaderItem(13, new QTableWidgetItem("_1F"));

    for (int i = 0; i < objCount; i++) {
        quint16 x, y;
        qint16 linkID, _1C;
        qint32 z;
        quint32 parentFlags, childFlags, _14;
        quint8 _1E, _1F;
        qint8 w, h, objType, childType;

        ds.skipRawData(2);
        ds >> x >> z >> y;
        ds >> w >> h;
        ds >> parentFlags >> childFlags >> _14;
        ds >> objType >> childType >> linkID >> _1C >> _1E >> _1F;

        qreal rx = x / 10, ry = -y / 10, rz = z / 10;
        ry -= (h - 1) * 16;
        qreal rw = w * 16, rh = h * 16;
        QGraphicsItem *item;

        switch (objType) {
        case EditGround:
        {
            auto ri = new QGraphicsRectItem(rx, ry, rw, rh);
            ri->setBrush(colours[EditGround]);
            item = ri;
            auto text = new QGraphicsSimpleTextItem(QString::number(_14, 10), ri);
            text->setPos(rx + 2, ry + 2);
            break;
        }
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

        ui->objectList->setItem(i, 0, new QTableWidgetItem(QString::number(x/10)));
        ui->objectList->setItem(i, 1, new QTableWidgetItem(QString::number(y/10)));
        ui->objectList->setItem(i, 2, new QTableWidgetItem(QString::number(z/10)));
        ui->objectList->setItem(i, 3, new QTableWidgetItem(QString::number(w)));
        ui->objectList->setItem(i, 4, new QTableWidgetItem(QString::number(h)));
        ui->objectList->setItem(i, 5, new QTableWidgetItem(objectNames[objType]));
        ui->objectList->setItem(i, 6, new QTableWidgetItem(QString::number(parentFlags, 16)));
        ui->objectList->setItem(i, 7, new QTableWidgetItem((childType == -1) ? "" : objectNames[childType]));
        ui->objectList->setItem(i, 8, new QTableWidgetItem(QString::number(childFlags, 16)));
        ui->objectList->setItem(i, 9, new QTableWidgetItem(QString::number(_14, 16)));
        ui->objectList->setItem(i, 10, new QTableWidgetItem(QString::number(linkID)));
        ui->objectList->setItem(i, 11, new QTableWidgetItem(QString::number(_1C)));
        ui->objectList->setItem(i, 12, new QTableWidgetItem(QString::number(_1E)));
        ui->objectList->setItem(i, 13, new QTableWidgetItem(QString::number(_1F)));
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
