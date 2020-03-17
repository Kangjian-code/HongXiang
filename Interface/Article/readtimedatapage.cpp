/**************************************************************
 * File Name   : readtimedatapage.cpp
 * Author      : ThreeDog
 * Date        : Fri Jan 11 22:29:01 2019
 * Description : 实时数据
 *
 **************************************************************/
#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#include "readtimedatapage.h"
#include "ui_readtimedatapage.h"

ReadTimeDataPage::ReadTimeDataPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ReadTimeDataPage)
{
    ui->setupUi(this);
    this->ui->tabWidget->setProperty("author","ThreeDog");
    this->initProperty();
    this->initTable1();
    this->initTable2();
    this->initTable3();
}

void ReadTimeDataPage::initProperty()
{
    foreach(QComboBox * combo,this->ui->tabWidget->findChildren<QComboBox *>() ){
        combo->setProperty("author","ThreeDog");
    }
}

void ReadTimeDataPage::initTable1()
{
    ui->m_pTableWidget->setColumnCount(8);

    QStringList headText;
    headText << "间隔" << "监测点"<< "采集时间" << "最大放电幅值" << "平均放电幅值" << "放电次数" << "通讯状态" << "局部报警";
    ui->m_pTableWidget->setHorizontalHeaderLabels(headText);
    ui->m_pTableWidget->setColumnWidth(0,220);
    ui->m_pTableWidget->setColumnWidth(1,220);
    ui->m_pTableWidget->setColumnWidth(2,220);
    ui->m_pTableWidget->setColumnWidth(3,220);
    ui->m_pTableWidget->setColumnWidth(4,220);
    ui->m_pTableWidget->setColumnWidth(5,220);
    ui->m_pTableWidget->setColumnWidth(6,220);
    ui->m_pTableWidget->setColumnWidth(7,220);
    ui->m_pTableWidget->verticalHeader()->setDefaultSectionSize(40);

    ui->m_pTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->m_pTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->m_pTableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->m_pTableWidget->setAlternatingRowColors(true);
    ui->m_pTableWidget->verticalHeader()->setVisible(false);
    ui->m_pTableWidget->horizontalHeader()->setStretchLastSection(true);

    //更新表格中的数据
    updateTable1();
}

void ReadTimeDataPage::initTable2()
{
    ui->m_pTableWidget2->setColumnCount(7);

    QStringList headText;
    headText << "间隔" << "监测点"<< "采集时间" << "最大放电幅值" << "平均放电幅值" << "放电次数" << "通讯状态" ;
    ui->m_pTableWidget2->setHorizontalHeaderLabels(headText);
    ui->m_pTableWidget2->setColumnWidth(0,220);
    ui->m_pTableWidget2->setColumnWidth(1,220);
    ui->m_pTableWidget2->setColumnWidth(2,220);
    ui->m_pTableWidget2->setColumnWidth(3,220);
    ui->m_pTableWidget2->setColumnWidth(4,220);
    ui->m_pTableWidget2->setColumnWidth(5,220);
    ui->m_pTableWidget2->setColumnWidth(6,220);
    ui->m_pTableWidget2->setColumnWidth(7,220);
    ui->m_pTableWidget2->verticalHeader()->setDefaultSectionSize(40);

    ui->m_pTableWidget2->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->m_pTableWidget2->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->m_pTableWidget2->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->m_pTableWidget2->setAlternatingRowColors(true);
    ui->m_pTableWidget2->verticalHeader()->setVisible(false);
    ui->m_pTableWidget2->horizontalHeader()->setStretchLastSection(true);

    //更新表格中的数据
    updateTable2();
}

void ReadTimeDataPage::initTable3()
{
    ui->m_pTableWidget3->setColumnCount(7);

    QStringList headText;
    headText << "间隔" << "监测点"<< "采集时间" << "最大放电幅值" << "平均放电幅值" << "通讯状态" << "震动报警";
    ui->m_pTableWidget3->setHorizontalHeaderLabels(headText);
    ui->m_pTableWidget3->setColumnWidth(0,220);
    ui->m_pTableWidget3->setColumnWidth(1,220);
    ui->m_pTableWidget3->setColumnWidth(2,220);
    ui->m_pTableWidget3->setColumnWidth(3,220);
    ui->m_pTableWidget3->setColumnWidth(4,220);
    ui->m_pTableWidget3->setColumnWidth(5,220);
    ui->m_pTableWidget3->setColumnWidth(6,220);
    ui->m_pTableWidget3->setColumnWidth(7,220);
    ui->m_pTableWidget3->verticalHeader()->setDefaultSectionSize(40);

    ui->m_pTableWidget3->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->m_pTableWidget3->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->m_pTableWidget3->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->m_pTableWidget3->setAlternatingRowColors(true);
    ui->m_pTableWidget3->verticalHeader()->setVisible(false);
    ui->m_pTableWidget3->horizontalHeader()->setStretchLastSection(true);

    //更新表格中的数据
    updateTable3();
}

void ReadTimeDataPage::updateTable1()
{
    ui->m_pTableWidget->setRowCount(40);
    for(int i = 0; i < 40; i++){
        ui->m_pTableWidget->setRowHeight(i, 40);

        QTableWidgetItem *item1 = new QTableWidgetItem(QString("PT间隔")+QString::number(i));
        QTableWidgetItem *item2 = new QTableWidgetItem(QString("监测点")+QString::number(i));
        QTableWidgetItem *item3 = new QTableWidgetItem(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
        QTableWidgetItem *item4 = new QTableWidgetItem("-100");
        QTableWidgetItem *item5 = new QTableWidgetItem("-100");
        QTableWidgetItem *item6 = new QTableWidgetItem("0");

        QWidget * w = new QWidget(ui->m_pTableWidget);
        QHBoxLayout * h = new QHBoxLayout;
        w->setLayout(h);
        h->setContentsMargins(10,10,10,10);
        h->addStretch();
        TDToolbar * status = new TDToolbar(":/img/index/status_dis.png",":/img/index/status_normal.png");
        status->setObjectName("TDToolbar");
        status->setMouseChangeEnable(false);
        status->setProperty("row",QString::number(i));
        h->addWidget(status);
        h->addStretch();

        ui->m_pTableWidget->setCellWidget(i,6,w);


        QWidget * w2 = new QWidget(ui->m_pTableWidget);
        QHBoxLayout * h2 = new QHBoxLayout;
        w2->setLayout(h2);
        h2->setContentsMargins(10,10,10,10);
        h2->addStretch();
        TDToolbar * status2 = new TDToolbar(":/img/index/status_dis.png",":/img/index/status_normal.png");
        status2->setObjectName("TDToolbar");
        status2->setMouseChangeEnable(false);
        status2->setProperty("row",QString::number(i));
        h2->addWidget(status2);
        h2->addStretch();

        ui->m_pTableWidget->setCellWidget(i,7,w2);

        item1->setTextAlignment(Qt::AlignCenter);
        item2->setTextAlignment(Qt::AlignCenter);
        item3->setTextAlignment(Qt::AlignCenter);
        item4->setTextAlignment(Qt::AlignCenter);
        item5->setTextAlignment(Qt::AlignCenter);
        item6->setTextAlignment(Qt::AlignCenter);

        ui->m_pTableWidget->setItem(i, 0, item1);
        ui->m_pTableWidget->setItem(i, 1, item2);
        ui->m_pTableWidget->setItem(i, 2, item3);
        ui->m_pTableWidget->setItem(i, 3, item4);
        ui->m_pTableWidget->setItem(i, 4, item5);
        ui->m_pTableWidget->setItem(i, 5, item6);
    }
}

void ReadTimeDataPage::updateTable2()
{
    ui->m_pTableWidget2->setRowCount(40);
    for(int i = 0; i < 40; i++){
        ui->m_pTableWidget2->setRowHeight(i, 40);

        QTableWidgetItem *item1 = new QTableWidgetItem(QString("PT间隔")+QString::number(i));
        QTableWidgetItem *item2 = new QTableWidgetItem(QString("监测点")+QString::number(i));
        QTableWidgetItem *item3 = new QTableWidgetItem(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
        QTableWidgetItem *item4 = new QTableWidgetItem("-100");
        QTableWidgetItem *item5 = new QTableWidgetItem("-100");
        QTableWidgetItem *item6 = new QTableWidgetItem("0");

        QWidget * w = new QWidget(ui->m_pTableWidget2);
        QHBoxLayout * h = new QHBoxLayout;
        w->setLayout(h);
        h->setContentsMargins(10,10,10,10);
        h->addStretch();
        TDToolbar * status = new TDToolbar(":/img/index/status_dis.png",":/img/index/status_normal.png");
        status->setObjectName("TDToolbar");
        status->setMouseChangeEnable(false);
        status->setProperty("row",QString::number(i));
        h->addWidget(status);
        h->addStretch();

        ui->m_pTableWidget2->setCellWidget(i,6,w);

        item1->setTextAlignment(Qt::AlignCenter);
        item2->setTextAlignment(Qt::AlignCenter);
        item3->setTextAlignment(Qt::AlignCenter);
        item4->setTextAlignment(Qt::AlignCenter);
        item5->setTextAlignment(Qt::AlignCenter);
        item6->setTextAlignment(Qt::AlignCenter);

        ui->m_pTableWidget2->setItem(i, 0, item1);
        ui->m_pTableWidget2->setItem(i, 1, item2);
        ui->m_pTableWidget2->setItem(i, 2, item3);
        ui->m_pTableWidget2->setItem(i, 3, item4);
        ui->m_pTableWidget2->setItem(i, 4, item5);
        ui->m_pTableWidget2->setItem(i, 5, item6);
    }
}

void ReadTimeDataPage::updateTable3()
{
    ui->m_pTableWidget3->setRowCount(40);
    for(int i = 0; i < 40; i++){
        ui->m_pTableWidget3->setRowHeight(i, 40);

        QTableWidgetItem *item1 = new QTableWidgetItem(QString("PT间隔")+QString::number(i));
        QTableWidgetItem *item2 = new QTableWidgetItem(QString("监测点")+QString::number(i));
        QTableWidgetItem *item3 = new QTableWidgetItem(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
        QTableWidgetItem *item4 = new QTableWidgetItem("-100");
        QTableWidgetItem *item5 = new QTableWidgetItem("-100");
        QTableWidgetItem *item6 = new QTableWidgetItem("0");

        QWidget * w = new QWidget(ui->m_pTableWidget3);
        QHBoxLayout * h = new QHBoxLayout;
        w->setLayout(h);
        h->setContentsMargins(10,10,10,10);
        h->addStretch();
        TDToolbar * status = new TDToolbar(":/img/index/status_dis.png",":/img/index/status_normal.png");
        status->setObjectName("TDToolbar");
        status->setProperty("row",QString::number(i));
        h->addWidget(status);
        h->addStretch();

        ui->m_pTableWidget3->setCellWidget(i,6,w);

        QWidget * w2 = new QWidget(ui->m_pTableWidget3);
        QHBoxLayout * h2 = new QHBoxLayout;
        w2->setLayout(h);
        h2->setContentsMargins(10,10,10,10);
        h2->addStretch();
        TDToolbar * status2 = new TDToolbar(":/img/index/status_dis.png",":/img/index/status_normal.png");
        status2->setObjectName("TDToolbar");
        status2->setMouseChangeEnable(false);
        status2->setProperty("row",QString::number(i));
        h2->addWidget(status2);
        h2->addStretch();

        ui->m_pTableWidget3->setCellWidget(i,6,w2);

        item1->setTextAlignment(Qt::AlignCenter);
        item2->setTextAlignment(Qt::AlignCenter);
        item3->setTextAlignment(Qt::AlignCenter);
        item4->setTextAlignment(Qt::AlignCenter);
        item5->setTextAlignment(Qt::AlignCenter);
        item6->setTextAlignment(Qt::AlignCenter);

        ui->m_pTableWidget3->setItem(i, 0, item1);
        ui->m_pTableWidget3->setItem(i, 1, item2);
        ui->m_pTableWidget3->setItem(i, 2, item3);
        ui->m_pTableWidget3->setItem(i, 3, item4);
        ui->m_pTableWidget3->setItem(i, 4, item5);
        ui->m_pTableWidget3->setItem(i, 5, item6);
    }
}

ReadTimeDataPage::~ReadTimeDataPage()
{
    delete ui;
}
