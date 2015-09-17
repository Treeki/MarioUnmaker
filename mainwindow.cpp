#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsScene>
#include <QFile>
#include <QDataStream>
#include <QGraphicsRectItem>

enum ObjType {
    OT_Goomba = 0,
    OT_Koopa = 1,
    OT_Piranha = 2,
    OT_HammerBro = 3,
    OT_Brick = 4,
    OT_Question = 5,
    OT_WoodBlock = 6,
    OT_Ground = 7,
    OT_Coin = 8,
    OT_Pipe = 9,
    OT_Springboard = 10,
    OT_Platform = 11,
    OT_Thwomp = 12,
    OT_BulletBillLauncher = 13,
    OT_MushroomPlatform = 14,
    OT_BobOmb = 15,
    OT_TreePlatform = 16,
    OT_Cloud = 22,
    OT_NoteBlock = 23,
    OT_Firebar = 24,
    OT_BuzzyBeetle = 28,
    OT_RideableCloud = 31,
    OT_ClownCar = 42,
    OT_SpikyThing = 43,
    OT_ShoedGoomba = 45,
    OT_DryBones = 46,
    OT_Blooper = 48,
    OT_Wiggler = 52,
    OT_Conveyor = 53,
    OT_Flamethrower = 54,
    OT_Door = 55,
    OT_Wrench = 58,
    OT_TrackPiece = 59,
    OT_Podoboo = 60,
    OT_ChainChomp = 61,
    OT_IceBlock = 63,
    OT_Vine = 64,
    OT_ArrowSign = 66,
    OT_Grinder = 68,
    // 16 = Mystery!
    // 38 = Entrance? Or Sign?
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

    QHash<int, QString> names;
    names[OT_Goomba] = "Goomba";
    names[OT_Koopa] = "Koopa";
    names[OT_Piranha] = "Piranha Plant";
    names[OT_HammerBro] = "Hammer Brother";
    names[OT_Brick] = "Brick";
    names[OT_Question] = "Question Block";
    names[OT_WoodBlock] = "Wood Block";
    names[OT_Ground] = "Ground";
    names[OT_Coin] = "Coin";
    names[OT_Pipe] = "Pipe";
    names[OT_Springboard] = "Springboard";
    names[OT_Platform] = "Platform";
    names[OT_Thwomp] = "Thwomp";
    names[OT_BulletBillLauncher] = "Bullet Bill Launcher";
    names[OT_MushroomPlatform] = "Mushroom Platform";
    names[OT_BobOmb] = "Bob-Omb";
    names[OT_TreePlatform] = "Tree Platform";
    names[OT_Cloud] = "Cloud";
    names[OT_NoteBlock] = "Note Block";
    names[OT_Firebar] = "Firebar";
    names[OT_BuzzyBeetle] = "Buzzy Beetle";
    names[OT_RideableCloud] = "Rideable Cloud";
    names[OT_ClownCar] = "Clown Car";
    names[OT_SpikyThing] = "Spiky Thing";
    names[OT_ShoedGoomba] = "Shoed Goomba";
    names[OT_DryBones] = "Dry Bones";
    names[OT_Blooper] = "Blooper";
    names[OT_Wiggler] = "Wiggler";
    names[OT_Conveyor] = "Conveyor Belt";
    names[OT_Flamethrower] = "Flamethrower";
    names[OT_Door] = "Door";
    names[OT_Wrench] = "Wrench";
    names[OT_TrackPiece] = "Track Piece";
    names[OT_Podoboo] = "Podoboo";
    names[OT_ChainChomp] = "Chain Chomp";
    names[OT_IceBlock] = "Ice Block";
    names[OT_Vine] = "Vine";
    names[OT_ArrowSign] = "Arrow Sign";
    names[OT_Grinder] = "Grinder";

    QHash<int, QColor> colours;
    colours[OT_Brick] = QColor(158, 95, 25);
    colours[OT_Question] = Qt::yellow;
    colours[OT_WoodBlock] = QColor(212, 162, 103);
    colours[OT_Cloud] = QColor(255, 252, 255);
    colours[OT_Goomba] = QColor(158, 95, 25);
    colours[OT_Pipe] = QColor(182, 237, 57);
    colours[OT_Ground] = QColor(75, 202, 13);
    colours[OT_IceBlock] = Qt::cyan;
    colours[OT_Vine] = QColor(52, 190, 48);
    colours[OT_Grinder] = QColor(155, 183, 175);


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
    ui->objectList->setHorizontalHeaderItem(4, new QTableWidgetItem("Width"));
    ui->objectList->setHorizontalHeaderItem(5, new QTableWidgetItem("Height"));
    ui->objectList->setHorizontalHeaderItem(6, new QTableWidgetItem("Unk1"));
    ui->objectList->setHorizontalHeaderItem(7, new QTableWidgetItem("Unk2"));
    ui->objectList->setHorizontalHeaderItem(8, new QTableWidgetItem("Unk3"));

    for (int i = 0; i < objCount; i++) {
        quint16 x, y;
        qint32 unk1;
        QByteArray unkblob2, unkblob3;
        quint8 objType, w, h;

        ds.skipRawData(2);
        ds >> x;
        ds >> unk1;
        ds >> y;
        ds >> w >> h;
        unkblob2 = f.read(12);
        ds >> objType;
        unkblob3 = f.read(7);

        qreal rx = x / 10, ry = -y / 10;
        ry -= (h - 1) * 16;
        qreal rw = w * 16, rh = h * 16;
        QGraphicsItem *item;

        switch (objType) {
        case OT_Coin:
        {
            auto ei = new QGraphicsEllipseItem(rx + 1, ry, rw - 2, rh);
            ei->setBrush(Qt::yellow);
            item = ei;
            break;
        }
        case OT_Goomba:
        {
            auto ei = new QGraphicsEllipseItem(rx, ry, rw, rh);
            ei->setBrush(colours[OT_Goomba]);
            item = ei;
            break;
        }
        case OT_Grinder:
        {
            auto ei = new QGraphicsEllipseItem(rx, ry, rw, rh);
            ei->setBrush(colours[OT_Grinder]);
            item = ei;
            break;
        }
        case OT_Vine:
        {
            auto ri = new QGraphicsRectItem(rx + 6, ry, rw - 12, rh);
            ri->setBrush(colours[OT_Vine]);
            item = ri;
            break;
        }
        case OT_Wrench:
        {
            auto ri = new QGraphicsRectItem(rx, ry + 12, rw, rh - 12);
            ri->setBrush(QColor(64, 64, 64));
            item = ri;
            break;
        }
        case OT_Door:
        {
            auto ri = new QGraphicsRectItem(rx, ry - 16, rw, rh);
            ri->setBrush(QColor(192, 187, 65));
            item = ri;
            break;
        }
        case OT_Platform:
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
        ui->objectList->setItem(i, 1, new QTableWidgetItem(names[objType]));
        ui->objectList->setItem(i, 2, new QTableWidgetItem(QString::number(x)));
        ui->objectList->setItem(i, 3, new QTableWidgetItem(QString::number(y)));
        ui->objectList->setItem(i, 4, new QTableWidgetItem(QString::number(w)));
        ui->objectList->setItem(i, 5, new QTableWidgetItem(QString::number(h)));
        ui->objectList->setItem(i, 6, new QTableWidgetItem(QString::number(unk1)));
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
