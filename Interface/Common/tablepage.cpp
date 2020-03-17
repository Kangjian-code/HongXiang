/**************************************************************
 * File Name   : tablepage.cpp
 * Author      : ThreeDog
 * Date        : Fri Jan 18 18:02:51 2019
 * Description : 表格窗体，继承自模态框，作为模板页面，需要表格页面的地方，
 * 可以参照此界面进行编写。
 *
 **************************************************************/

#include "tablepage.h"

TablePage::TablePage(QWidget *parent)
    :TDModal("",parent)
{
    this->setTitle("单元配置");
    this->resize(1460,635);
    this->setButtonText("保存","返回");
    //添加下侧的几个按钮
    QPushButton * btn1 = new QPushButton("导入",this);
    QPushButton * btn2 = new QPushButton("导出",this);
    QPushButton * btn3 = new QPushButton("添加",this);
    this->m_pFooterHLayout->insertWidget(2,btn3);
    this->m_pFooterHLayout->insertWidget(2,btn2);
    this->m_pFooterHLayout->insertWidget(2,btn1);

    initTable();
}

void TablePage::initTable()
{

    m_pTableWidget = new QTableWidget(this);
    m_pTableWidget->setMinimumHeight(475);
    this->m_pArticleVLayout->addWidget(m_pTableWidget);

    m_pTableWidget->setColumnCount(9);
    m_pTableWidget->setColumnWidth(0, 140 );
    m_pTableWidget->setColumnWidth(1, 140);
    m_pTableWidget->setColumnWidth(2, 140 );
    m_pTableWidget->setColumnWidth(3, 140);
    m_pTableWidget->setColumnWidth(4, 140);
    m_pTableWidget->setColumnWidth(5, 140);
    m_pTableWidget->setColumnWidth(6, 140 );
    m_pTableWidget->setColumnWidth(7, 100);
    m_pTableWidget->setColumnWidth(8, 230);
    //    m_pTableWidget->setColumnWidth(2, 100);
    m_pTableWidget->verticalHeader()->setDefaultSectionSize(40);


    QStringList headText;
    headText << "单元名称" << "设备编号"<< "IP地址" << "端口" << "通道数量" << "同步方式" << "内同步设置" << "设备状态" << "操作";
    m_pTableWidget->setHorizontalHeaderLabels(headText);
    m_pTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_pTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_pTableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    m_pTableWidget->setAlternatingRowColors(true);
    m_pTableWidget->verticalHeader()->setVisible(false);
    m_pTableWidget->horizontalHeader()->setStretchLastSection(true);

    //更新表格中的数据
    updateTable();

}

void TablePage::updateTable()
{
    m_pTableWidget->setRowCount(4);
    for(int i = 0; i < 4; i++){
        m_pTableWidget->setRowHeight(i, 40);

        QTableWidgetItem *item1 = new QTableWidgetItem(QString("采集单元%1").arg(i+1));
        QTableWidgetItem *item2 = new QTableWidgetItem(QString("%1").arg(50010058+i));
        QTableWidgetItem *item3 = new QTableWidgetItem(QString("192.168.1.%1").arg(i));
        QTableWidgetItem *item4 = new QTableWidgetItem("1188");
        QTableWidgetItem *item5 = new QTableWidgetItem("8");

        QWidget * w = new QWidget(this);
        QHBoxLayout * h = new QHBoxLayout;
        h->setContentsMargins(20,3,20,3);
        QWidget * w2 = new QWidget(this);
        QHBoxLayout * h2 = new QHBoxLayout;
        h2->setContentsMargins(20,3,20,3);
        h2->setSpacing(10);
        QWidget * w3 = new QWidget(this);
        QHBoxLayout * h3 = new QHBoxLayout;
        h3->setContentsMargins(20,3,20,3);

        w->setLayout(h);
        w2->setLayout(h2);
        w3->setLayout(h3);

        //为表格添加下拉框
        QComboBox * combo = new QComboBox(this);
        combo->setProperty("author","ThreeDog");
        combo->addItem("内同步");
        combo->addItem("PT同步");
        combo->addItem("工频同步");
        h->addWidget(combo);
        this->m_pTableWidget->setCellWidget(i,5,w);

        QLineEdit *line = new QLineEdit(this);
        line->setProperty("author","ThreeDog");
        h2->addWidget(line,8);
        QLabel *l = new QLabel("Hz",this);
        l->setStyleSheet("font-size:14px");
        h2->addWidget(l,2);
        this->m_pTableWidget->setCellWidget(i,6,w2);

        TDToolbar * t = new TDToolbar(":/img/index/switch_open.png",":/img/index/switch_close.png",this);
        h3->addWidget(t);

        this->m_pTableWidget->setCellWidget(i,7,w3);
        TableOperateItem * toitem = new TableOperateItem(1,this);
        this->m_pTableWidget->setCellWidget(i,8,toitem);


        item1->setTextAlignment(Qt::AlignCenter);
        item2->setTextAlignment(Qt::AlignCenter);
        item3->setTextAlignment(Qt::AlignCenter);
        item4->setTextAlignment(Qt::AlignCenter);
        item5->setTextAlignment(Qt::AlignCenter);

        m_pTableWidget->setItem(i, 0, item1);
        m_pTableWidget->setItem(i, 1, item2);
        m_pTableWidget->setItem(i, 2, item3);
        m_pTableWidget->setItem(i, 3, item4);
        m_pTableWidget->setItem(i, 4, item5);


    }
}

TablePage::~TablePage()
{

}
