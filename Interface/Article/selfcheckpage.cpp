/**************************************************************
 * File Name   : selfcheckpage.cpp
 * Author      : ThreeDog
 * Date        : Fri Jan 11 22:29:01 2019
 * Description : 自检
 *
 **************************************************************/
#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#include "selfcheckpage.h"
#include "ui_selfcheckpage.h"

SelfCheckPage::SelfCheckPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SelfCheckPage)
{
    ui->setupUi(this);
    initTable();
    updateTable();
}

void SelfCheckPage::initTable()
{
    m_pTableWidget = new QTableWidget(ui->mainWidget);
    ui->hLayout->addWidget(m_pTableWidget);

    m_pTableWidget->setColumnCount(12);

    QStringList headText;
    headText << "序号" << "设备编号"<< "通道" << "监测点" << "通讯状态" << "传感器连接状态" << "采集时间" << "最大放电赋值" << "平均放电赋值" << "放电次数" << "更新时间" << "最新状态 ";
    m_pTableWidget->setHorizontalHeaderLabels(headText);
    m_pTableWidget->setColumnWidth(0,90);
    m_pTableWidget->setColumnWidth(1,90);
    m_pTableWidget->setColumnWidth(2,90);
    m_pTableWidget->setColumnWidth(3,180);
    m_pTableWidget->setColumnWidth(4,90);
    m_pTableWidget->setColumnWidth(5,180);
    m_pTableWidget->setColumnWidth(6,270);
    m_pTableWidget->setColumnWidth(7,180);
    m_pTableWidget->setColumnWidth(8,180);
    m_pTableWidget->setColumnWidth(9,90);
    m_pTableWidget->setColumnWidth(10,270);
    m_pTableWidget->setColumnWidth(11,90);
    m_pTableWidget->verticalHeader()->setDefaultSectionSize(40);

    m_pTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_pTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_pTableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    m_pTableWidget->setAlternatingRowColors(true);
    m_pTableWidget->verticalHeader()->setVisible(false);
    m_pTableWidget->horizontalHeader()->setStretchLastSection(true);

    //更新表格中的数据
    updateTable();
}

void SelfCheckPage::updateTable()
{
    m_pTableWidget->setRowCount(40);
    for(int i = 0; i < 40; i++){
        m_pTableWidget->setRowHeight(i, 40);

        QTableWidgetItem *item1 = new QTableWidgetItem(QString::number(i));
        QTableWidgetItem *item2 = new QTableWidgetItem(QString::number(50100200+i));
        QTableWidgetItem *item3 = new QTableWidgetItem(QString::number(i % 5));
        QTableWidgetItem *item4 = new QTableWidgetItem(QString("监测点%1").arg(i));

        QWidget * w = new QWidget(m_pTableWidget);
        QHBoxLayout * h = new QHBoxLayout;
        w->setLayout(h);
        h->setContentsMargins(10,10,10,10);
        h->addStretch();
        TDToolbar * status = new TDToolbar(":/img/index/status_dis.png",":/img/index/status_normal.png");
        status->setMouseChangeEnable(false);
        status->setObjectName("TDToolbar");
        status->setProperty("row",QString::number(i));
        h->addWidget(status);
        h->addStretch();

        this->m_pTableWidget->setCellWidget(i,4,w);

        QTableWidgetItem *item5 = new QTableWidgetItem("正常");
        QTableWidgetItem *item6 = new QTableWidgetItem(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
        QTableWidgetItem *item7 = new QTableWidgetItem("-100");
        QTableWidgetItem *item8 = new QTableWidgetItem("-100");
        QTableWidgetItem *item9 = new QTableWidgetItem("0");
        QTableWidgetItem *item10 = new QTableWidgetItem(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
        QTableWidgetItem *item11 = new QTableWidgetItem("运行正常");

        item1->setTextAlignment(Qt::AlignCenter);
        item2->setTextAlignment(Qt::AlignCenter);
        item3->setTextAlignment(Qt::AlignCenter);
        item4->setTextAlignment(Qt::AlignCenter);
        item5->setTextAlignment(Qt::AlignCenter);
        item6->setTextAlignment(Qt::AlignCenter);
        item7->setTextAlignment(Qt::AlignCenter);
        item8->setTextAlignment(Qt::AlignCenter);
        item9->setTextAlignment(Qt::AlignCenter);
        item10->setTextAlignment(Qt::AlignCenter);
        item11->setTextAlignment(Qt::AlignCenter);

        m_pTableWidget->setItem(i, 0, item1);
        m_pTableWidget->setItem(i, 1, item2);
        m_pTableWidget->setItem(i, 2, item3);
        m_pTableWidget->setItem(i, 3, item4);
        m_pTableWidget->setItem(i, 5, item5);
        m_pTableWidget->setItem(i, 6, item6);
        m_pTableWidget->setItem(i, 7, item7);
        m_pTableWidget->setItem(i, 8, item8);
        m_pTableWidget->setItem(i, 9, item9);
        m_pTableWidget->setItem(i, 10, item10);
        m_pTableWidget->setItem(i, 11, item11);
    }
}

SelfCheckPage::~SelfCheckPage()
{
    delete ui;
}
