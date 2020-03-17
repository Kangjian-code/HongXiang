/**************************************************************
 * File Name   : runtatepage.cpp
 * Author      : ThreeDog
 * Date        : Thu Jan 10 17:00:07 2019
 * Description : 运行状态页面，包含左侧栏。
 *      用于显示一次接线图，报警信息等内容。
 *
 **************************************************************/
#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#include "runstatepage.h"
#include "ui_runstatepage.h"
#include <QPushButton>

RunStatePage::RunStatePage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RunStatePage)
{
    m_pTreeWidget = nullptr;
    ui->setupUi(this);
    initImageWidget();      //初始化一次接线图的滚动区域
    initTabs();             //初始化上侧的四个标签卡
    initLeftTabs();         //初始化左侧栏
    initTables();           //初始化下侧的两个表格
    initTreeView();         //初始化左侧树状列表
}

void RunStatePage::initTabs()
{
    initTab1();
    initTab2();
    initTab3();
    initTab4();
}

void RunStatePage::initTab1()
{
    //初始化上侧的四个标签卡
    //注意这里的父控件全部都是右侧的子窗体
    m_pEventCountWidget = new TDWidget(":/img/index/tab_1.png",ui->rightWidget);
    m_pEventCountWidget->move(15,8);
    m_pEventCountWidget->setMoveEnable(false);

    QLabel * label1 = new QLabel("局放报警事件统计",m_pEventCountWidget);//局放报警事件统计
    label1->move(30,11);
    label1->setStyleSheet("width:144px;\
                          height:24px;\
            font-size:18px;\
    font-family:微软雅黑;\
    font-weight:bold;\
color:rgba(38,38,38,1);\
    line-height:24px;");

    QLabel * label2 = new QLabel("正常",m_pEventCountWidget);
    label2->resize(90,14);
    label2->setAlignment(Qt::AlignCenter);
    label2->setStyleSheet("\
                          font-size:10px;\
            background:rgba(102,160,225,1);\
color:#FFFFFF;\
    border-radius:1px;");
    label2->move(30,48);
    QLabel * label3 = new QLabel("干扰",m_pEventCountWidget);
    label3->resize(90,14);
    label3->setAlignment(Qt::AlignCenter);
    label3->setStyleSheet("\
                          font-size:10px;\
            background:rgba(128,199,255,1);\
color:#FFFFFF;\
    border-radius:1px;");
    label3->move(30,66);

    QLabel * label4 = new QLabel("其他",m_pEventCountWidget);
    label4->setAlignment(Qt::AlignCenter);
    label4->resize(90,14);
    label4->setStyleSheet("\
                          font-size:10px;\
            background:rgba(165,131,243,1);\
color:#FFFFFF;\
    border-radius:1px;");
    label4->move(30,84);

    QLabel * label5 = new QLabel("尖端放电",m_pEventCountWidget);
    label5->setAlignment(Qt::AlignCenter);
    label5->resize(90,14);
    label5->setStyleSheet("\
                          font-size:10px;\
            background:rgba(173,66,66,1);\
color:#FFFFFF;\
    border-radius:1px;");
    label5->move(140,48);
    QLabel * label6 = new QLabel("悬浮放电",m_pEventCountWidget);
    label6->setAlignment(Qt::AlignCenter);
    label6->resize(90,14);
    label6->setStyleSheet("\
                          font-size:10px;\
            background:rgba(132,159,201,1);\
color:#FFFFFF;\
    border-radius:1px;");
    label6->move(140,66);
    QLabel * label7 = new QLabel("沿面放电",m_pEventCountWidget);
    label7->setAlignment(Qt::AlignCenter);
    label7->resize(90,14);
    label7->setStyleSheet("\
                          font-size:10px;\
            background:rgba(242,192,68,1);\
color:#FFFFFF;\
    border-radius:1px;");
    label7->move(140,84);
    QLabel * label8 = new QLabel("内部放电",m_pEventCountWidget);
    label8->setAlignment(Qt::AlignCenter);
    label8->resize(90,14);
    label8->setStyleSheet("\
                          font-size:10px;\
            background:rgba(122,205,90,1);\
color:#FFFFFF;\
    border-radius:1px;");
    label8->move(140,102);
    QLabel * label9 = new QLabel("自由金属颗粒",m_pEventCountWidget);
    label9->resize(90,14);
    label9->setAlignment(Qt::AlignCenter);
    label9->setStyleSheet("\
                          font-size:10px;\
            background:rgba(76,153,205,1);\
color:#FFFFFF;\
    border-radius:1px;");
    label9->move(140,120);

    QWidget * w1 = new QWidget(m_pEventCountWidget);
    w1->move(240,5);
    w1->resize(170,148);

    QPieSeries *series = new QPieSeries();
    series->append("35%", 35);
    series->append("12%", 12);
    series->append("12%", 12);
    series->append("12%", 12);
    series->append("10%", 10);
    series->append("10%", 10);
    series->append("5%", 5);
    series->append("4%", 4);
    series->setLabelsVisible(false);    //设置旁标可见
    //后期可通过setValue重新设置大小
    series->slices().at(0)->setColor(QColor("#66A0E1"));
    series->slices().at(1)->setColor(QColor("#6A7CFE"));
    series->slices().at(2)->setColor(QColor("#A583F3"));
    series->slices().at(3)->setColor(QColor("#AD6363"));
    series->slices().at(4)->setColor(QColor("#ADB8C9"));
    series->slices().at(5)->setColor(QColor("#F2C044"));
    series->slices().at(6)->setColor(QColor("#7ACD5A"));
    series->slices().at(7)->setColor(QColor("#4C99CD"));

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("");
    chart->legend()->hide();
    chart->show();

    QChartView *chartview = new QChartView(chart,w1);
    chartview->setRenderHint(QPainter::Antialiasing);
    chartview->resize(30,30);
    chartview->move(-10,-20);
}

void RunStatePage::initTab2()
{
    m_pDataWarningWidget = new TDWidget(":/img/index/tab_2.png",ui->rightWidget);
    m_pDataWarningWidget->move(443,8);
    m_pDataWarningWidget->setMoveEnable(false);

    QLabel * label1 = new QLabel("数据报警率",m_pDataWarningWidget);//局放报警事件统计
    label1->move(30,11);
    label1->setStyleSheet("\
                          font-size:18px;\
            font-family:微软雅黑;\
    font-weight:bold;\
color:rgba(38,38,38,1);\
    line-height:24px;");

    QLabel * label2 = new QLabel("5%",m_pDataWarningWidget);
    //    label2->resize(72,76);
    label2->setAlignment(Qt::AlignCenter);
    label2->setStyleSheet("\
                          font-size:64px;\
            font-family:微软雅黑;\
    font-weight:bold;\
color:rgba(223,60,46,1);\
    line-height:78px;");
    label2->move(30,60);

    QWidget * w1 = new QWidget(m_pDataWarningWidget);
    w1->move(240,5);
    w1->resize(170,148);

    QPieSeries *series = new QPieSeries();
    series->append("5%", 5);
    series->append("95%", 95);
    series->setLabelsVisible(false);    //设置旁标可见
    //后期可通过setValue重新设置大小
    series->slices().at(0)->setColor(QColor("#DF3C2E"));
    series->slices().at(1)->setColor(QColor(204,224,239));

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("");
    chart->legend()->hide();
    chart->show();

    QChartView *chartview = new QChartView(chart,w1);
    chartview->setRenderHint(QPainter::Antialiasing);
    chartview->resize(30,30);
    chartview->move(-10,-20);
}

void RunStatePage::initTab3()
{
    //设备报警时间统计
    m_pDeviceWarningEventWidget = new TDWidget(":/img/index/tab_3.png",ui->rightWidget);
    m_pDeviceWarningEventWidget->move(871,8);
    m_pDeviceWarningEventWidget->setMoveEnable(false);

    QLabel * label1 = new QLabel("设备报警事件统计",m_pDeviceWarningEventWidget);
    label1->move(30,11);
    label1->setStyleSheet("\
                          font-size:18px;\
            font-family:微软雅黑;\
    font-weight:bold;\
color:rgba(38,38,38,1);\
    line-height:24px;");

    QLabel * label2 = new QLabel("通信故障",m_pDeviceWarningEventWidget);
    label2->resize(90,14);
    label2->setAlignment(Qt::AlignCenter);
    label2->setStyleSheet("\
                          font-size:10px;\
            background:rgba(102,160,225,1);\
color:#FFFFFF;\
    border-radius:1px;");
    label2->move(30,46);
    QLabel * label3 = new QLabel("空气节点故障",m_pDeviceWarningEventWidget);
    label3->resize(90,14);
    label3->setAlignment(Qt::AlignCenter);
    label3->setStyleSheet("\
                          font-size:10px;\
            background:rgba(106,124,254,1);\
color:#FFFFFF;\
    border-radius:1px;");
    label3->move(30,66);

    QLabel * label4 = new QLabel("传感器故障",m_pDeviceWarningEventWidget);
    label4->setAlignment(Qt::AlignCenter);
    label4->resize(90,14);
    label4->setStyleSheet("\
                          font-size:10px;\
            background:rgba(165,131,243,1);\
color:#FFFFFF;\
    border-radius:1px;");
    label4->move(30,84);

    QLabel * label5 = new QLabel("采集模块故障",m_pDeviceWarningEventWidget);
    label5->setAlignment(Qt::AlignCenter);
    label5->resize(90,14);
    label5->setStyleSheet("\
                          font-size:10px;\
            background:rgba(198,122,122,1);\
color:#FFFFFF;\
    border-radius:1px;");
    label5->move(30,100);
    QLabel * label6 = new QLabel("工频同步信号丢失",m_pDeviceWarningEventWidget);
    label6->setAlignment(Qt::AlignCenter);
    label6->resize(90,14);
    label6->setStyleSheet("\
                          font-size:10px;\
            background:rgba(132,159,201,1);\
color:#FFFFFF;\
    border-radius:1px;");
    label6->move(30,118);

    QWidget * w1 = new QWidget(m_pDeviceWarningEventWidget);
    w1->move(240,5);
    w1->resize(170,148);

    QPieSeries *series = new QPieSeries();
    series->append("10%", 10);
    series->append("15%", 15);
    series->append("25%", 25);
    series->append("30%", 30);
    series->append("20%", 20);
    series->setLabelsVisible(false);    //设置旁标可见
    //后期可通过setValue重新设置大小
    series->slices().at(0)->setColor(QColor("#66A0E1"));
    series->slices().at(1)->setColor(QColor("#6A7CFE"));
    series->slices().at(2)->setColor(QColor("#A583F3"));
    series->slices().at(3)->setColor(QColor("#AD6363"));
    series->slices().at(4)->setColor(QColor("#ADB8C9"));


    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("");
    chart->legend()->hide();
    chart->show();

    QChartView *chartview = new QChartView(chart,w1);
    chartview->setRenderHint(QPainter::Antialiasing);
    chartview->resize(30,30);
    chartview->move(-10,-20);


}

void RunStatePage::initTab4()
{
    m_pDeviceWarningRateWidget = new TDWidget(":/img/index/tab_4.png",ui->rightWidget);
    m_pDeviceWarningRateWidget->move(1300,8);
    m_pDeviceWarningRateWidget->setMoveEnable(false);

    QLabel * label1 = new QLabel("设备报警率",m_pDeviceWarningRateWidget);//局放报警事件统计
    label1->move(30,11);
    label1->setStyleSheet("\
                          font-size:18px;\
            font-family:微软雅黑;\
    font-weight:bold;\
color:rgba(38,38,38,1);\
    line-height:24px;");

    QLabel * label2 = new QLabel("5%",m_pDeviceWarningRateWidget);
    //    label2->resize(72,76);
    label2->setAlignment(Qt::AlignCenter);
    label2->setStyleSheet("\
                          font-size:64px;\
            font-family:微软雅黑;\
    font-weight:bold;\
color:rgba(223,60,46,1);\
    line-height:78px;");
    label2->move(30,60);

    QWidget * w1 = new QWidget(m_pDeviceWarningRateWidget);
    w1->move(240,5);
    w1->resize(170,148);

    QPieSeries *series = new QPieSeries();
    series->append("5%", 5);
    series->append("95%", 95);
    series->setLabelsVisible(false);    //设置旁标可见
    //后期可通过setValue重新设置大小
    series->slices().at(0)->setColor(QColor("#DF3C2E"));
    series->slices().at(1)->setColor(QColor(239,225,204));

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("");
    chart->legend()->hide();
    chart->show();

    QChartView *chartview = new QChartView(chart,w1);
    chartview->setRenderHint(QPainter::Antialiasing);
    chartview->resize(30,30);
    chartview->move(-10,-20);
}

void RunStatePage::initImageWidget()
{
    //初始化一次接线图的区域
    m_pImageImdex = new ImageIndex(this);
    m_pImageImdex->show();
    //    w->resize(3000,3000);
    //    connect(this,SIGNAL(treeItemClicked(QTreeWidgetItem*,int)),
    //            w,SLOT(slot_treeItemClicked(QTreeWidgetItem*,int)));
    QHBoxLayout * h = new QHBoxLayout;
    ui->rightWidget->setLayout(h);
    h->setContentsMargins(15,182,15,210);
    h->addWidget(m_pImageImdex);
    //注意设置滑槽的属性之前，必须先设置中心窗体
    m_pImageImdex->setSliderColor(QColor("#ffffff"),QColor("#D8D8D8"));
    m_pImageImdex->setSliderOpacity(255,255);
    m_pImageImdex->setSliderRadius(0,6);
    m_pImageImdex->setSliderWidth(20);
    m_pImageImdex->setSliderPadding(4);

}

//初始化树状列表
void RunStatePage::initTreeView()
{
    qDebug()<<"init Tree Widget";
    if(m_pTreeWidget == nullptr){
        m_pTreeWidget = new QTreeWidget(ui->leftWidget);
        connect(m_pTreeWidget,SIGNAL(itemPressed(QTreeWidgetItem*,int)),this,SLOT(slot_treeItemClicked(QTreeWidgetItem*,int)));
        m_pTreeWidget->setStyleSheet("background:rgba(81,149,202,1);color:#FFFFFF");
        m_pTreeWidget->setFixedSize(138,1005);
        m_pTreeWidget->header()->setStyleSheet("background:rgba(81,149,202,1);min-height:0px;max-height:0px");//重新编辑树状列表表头的样式
        m_pTreeWidget->setHeaderLabel("");
        m_pTreeWidget->setHeaderItem(nullptr);
    }
    m_pTreeWidget->clear();


    //获取并遍历所有的间隔
    for(auto spacing : Dao::getInstance()->QuerySpacing()){
        TDTreeWidgetItem *group = new TDTreeWidgetItem(m_pTreeWidget);
        group->setText(0, spacing.name);
        group->setId(spacing.id);
        group->setType(0);      //类型为0，间隔点
        //遍历此间隔下的所有监测点
        for(auto sensor : Dao::getInstance()->QuerySensorBySpacing(spacing.id)){
            TDTreeWidgetItem *subItem11 = new TDTreeWidgetItem(group);
            qDebug()<<"sensor_id:" << sensor.id;
            subItem11->setId(sensor.id);
            subItem11->setType(1);//类型为1，监测点
//            subItem11->setFlags(Qt::ItemIsUserCheckable /*| Qt::ItemIsEnabled | Qt::ItemIsSelectable*/);
            subItem11->setText(0,sensor.name);
            subItem11->setCheckState(0, Qt::Checked);
        }
    }
    //临时测试用例
    //获取并遍历所有的间隔
    m_pTreeWidget->expandAll();
}

void RunStatePage::initTables()
{
    TDWidget * left = new TDWidget(":/img/index/table_bg.png",ui->rightWidget);
    left->move(15,795);
    left->setMoveEnable(false);
    left->show();
    TDWidget * right = new TDWidget(":/img/index/table_bg.png",ui->rightWidget);
    right->move(887,795);
    right->setMoveEnable(false);
    right->show();

    m_pTableWidget1 = new QTableWidget(left);
    m_pTableWidget1->setFixedSize(810,160);
    m_pTableWidget1->move(20,10);

    m_pTableWidget1->setColumnCount(5);
    m_pTableWidget1->setColumnWidth(0, 165);
    m_pTableWidget1->setColumnWidth(1, 94);
    m_pTableWidget1->setColumnWidth(2, 88);
    m_pTableWidget1->setColumnWidth(3, 124);
    m_pTableWidget1->setColumnWidth(4, 325);
    m_pTableWidget1->verticalHeader()->setDefaultSectionSize(40);

    QStringList headText;
    headText << "最近通讯时间" << "设备编号"<< "通讯状态" << "连接器连接状态" << "备注" ;
    m_pTableWidget1->setHorizontalHeaderLabels(headText);
    m_pTableWidget1->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_pTableWidget1->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_pTableWidget1->setSelectionMode(QAbstractItemView::SingleSelection);
    m_pTableWidget1->setAlternatingRowColors(true);
    m_pTableWidget1->verticalHeader()->setVisible(false);
    m_pTableWidget1->horizontalHeader()->setStretchLastSection(true);


    m_pTableWidget2 = new QTableWidget(right);
    m_pTableWidget2->setFixedSize(810,160);
    m_pTableWidget2->move(20,10);

    m_pTableWidget2->setColumnCount(6);
    m_pTableWidget2->setColumnWidth(0, 160);
    m_pTableWidget2->setColumnWidth(1, 85);
    m_pTableWidget2->setColumnWidth(2, 85);
    m_pTableWidget2->setColumnWidth(3, 175);
    m_pTableWidget2->setColumnWidth(4, 88);
    m_pTableWidget2->setColumnWidth(5, 200);
    m_pTableWidget2->verticalHeader()->setDefaultSectionSize(40);


    QStringList headText2;
    headText2 << "报警时间" << "间隔"<< "监测点" << "报警内容" << "报警等级" << "操作" ;
    m_pTableWidget2->setHorizontalHeaderLabels(headText2);
    m_pTableWidget2->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_pTableWidget2->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_pTableWidget2->setSelectionMode(QAbstractItemView::SingleSelection);
    m_pTableWidget2->setAlternatingRowColors(true);
    m_pTableWidget2->verticalHeader()->setVisible(false);
    m_pTableWidget2->horizontalHeader()->setStretchLastSection(true);

    updateLeftTable();
    updateRightTable();
}

void RunStatePage::updateLeftTable()
{
    m_pTableWidget1->setRowCount(4);
    for(int i = 0; i < 4; i++){
        m_pTableWidget1->setRowHeight(i, 40);

        QTableWidgetItem *item1 = new QTableWidgetItem(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
        QTableWidgetItem *item2 = new QTableWidgetItem("50100163");

        QWidget * w = new QWidget(m_pTableWidget1);
        QHBoxLayout * h = new QHBoxLayout;
        w->setLayout(h);
        h->setContentsMargins(10,10,10,10);
        h->addStretch();
        TDToolbar * status = new TDToolbar(":/img/index/status_normal.png",":/img/index/status_dis.png");
        status->setObjectName("TDToolbar");
        status->setMouseChangeEnable(false);
        status->setProperty("row",QString::number(i));
        h->addWidget(status);
        h->addStretch();

        this->m_pTableWidget1->setCellWidget(i,2,w);

        QWidget * w2 = new QWidget(m_pTableWidget1);
        QHBoxLayout * h2 = new QHBoxLayout;
        w2->setLayout(h2);
        h2->setContentsMargins(10,10,10,10);
        h2->addStretch();
        TDToolbar * status2 = new TDToolbar(":/img/index/status_normal.png",":/img/index/status_dis.png");
        status2->setObjectName("TDToolbar");
        status2->setMouseChangeEnable(false);
        status2->setProperty("row",QString::number(i));
        h2->addWidget(status2);
        h2->addStretch();

        this->m_pTableWidget1->setCellWidget(i,3,w2);

        QTableWidgetItem *item5 = new QTableWidgetItem("asddefasdfead");

        item1->setTextAlignment(Qt::AlignCenter);
        item2->setTextAlignment(Qt::AlignCenter);
        item5->setTextAlignment(Qt::AlignCenter);

        m_pTableWidget1->setItem(i, 0, item1);
        m_pTableWidget1->setItem(i, 1, item2);
        m_pTableWidget1->setItem(i, 4, item5);
    }
}

void RunStatePage::updateRightTable()
{
    m_pTableWidget2->setRowCount(4);
    for(int i = 0; i < 4; i++){
        m_pTableWidget2->setRowHeight(i, 40);

        QTableWidgetItem *item1 = new QTableWidgetItem(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
        QTableWidgetItem *item2 = new QTableWidgetItem("PT间隔1");
        QTableWidgetItem *item3 = new QTableWidgetItem("监测点1");
        QTableWidgetItem *item4 = new QTableWidgetItem("自由金属颗粒，识别率88%");
        QTableWidgetItem *item5 = new QTableWidgetItem("存在放电");

        item1->setTextAlignment(Qt::AlignCenter);
        item2->setTextAlignment(Qt::AlignCenter);
        item3->setTextAlignment(Qt::AlignCenter);
        item4->setTextAlignment(Qt::AlignCenter);
        item5->setTextAlignment(Qt::AlignCenter);

        m_pTableWidget2->setItem(i, 0, item1);
        m_pTableWidget2->setItem(i, 1, item2);
        m_pTableWidget2->setItem(i, 2, item3);
        m_pTableWidget2->setItem(i, 3, item4);
        m_pTableWidget2->setItem(i, 4, item5);

        QWidget * w2 = new QWidget(m_pTableWidget2);
        QHBoxLayout * h2 = new QHBoxLayout;
        w2->setLayout(h2);
        h2->setContentsMargins(10,3,10,3);
        h2->addStretch();
        QPushButton * btn = new QPushButton("复归",this);
        btn->setObjectName("subButton");
        btn->setStyleSheet("width:90px;\
                           height:30px;\
                max-width:90px;\
        max-height:30px;\
        min-width:60px;\
        min-height:30px;");
        h2->addWidget(btn);
        h2->addStretch();
        btn->setProperty("row",QString::number(i));
        btn->setProperty("action","复归");

        QPushButton * btn2 = new QPushButton("上传",this);
        btn2->setObjectName("subButton");
        btn2->setStyleSheet("width:90px;\
                            height:30px;\
                max-width:90px;\
        max-height:30px;\
        min-width:60px;\
        min-height:30px;");
        h2->addWidget(btn2);
        h2->addStretch();

        btn2->setProperty("row",QString::number(i));
        btn2->setProperty("action","上传");
        this->m_pTableWidget2->setCellWidget(i,5,w2);

    }
}

void RunStatePage::initLeftTabs()
{
    m_pHideLeftBtn = new TDToolbar(":/img/index/left_open.png",":/img/index/left_close.png",this);
    m_pHideLeftBtn->move(154,472);
    connect(m_pHideLeftBtn,SIGNAL(clicked()),this,SLOT(hideLeft()));

    //设置左侧栏右键菜单
    ui->leftWidget->setContextMenuPolicy(Qt::ActionsContextMenu);
    QAction * act1 = new QAction("新增间隔");
    QAction * act2 = new QAction("导入监测点位表");
    QAction * act3 = new QAction("导出监测点位表");
    QAction * act4 = new QAction("刷新");
    ui->leftWidget->addAction(act1);
    ui->leftWidget->addAction(act2);
    ui->leftWidget->addAction(act3);
    ui->leftWidget->addAction(act4);
    connect(act1,SIGNAL(triggered(bool)),this,SLOT(addSpacer()));
    connect(act2,SIGNAL(triggered(bool)),this,SLOT(importPosition()));
    connect(act3,SIGNAL(triggered(bool)),this,SLOT(exportPosition()));
    connect(act4,SIGNAL(triggered(bool)),this,SLOT(updateTreeWidget()));
}

//点击隐藏左侧栏的按钮触发
void RunStatePage::hideLeft()
{
    //显示
    if(ui->leftWidget->isHidden()){
        ui->leftWidget->show();
        m_pHideLeftBtn->move(154,472);
        m_pHideLeftBtn->raise();
    }else{
        //隐藏
        ui->leftWidget->hide();
        m_pHideLeftBtn->move(0,472);
        m_pHideLeftBtn->raise();
    }

}

RunStatePage::~RunStatePage()
{
    delete ui;
}

//新增间隔
void RunStatePage::addSpacer()
{
    AddSpacerModal * modal = new AddSpacerModal();
    connect(modal,SIGNAL(sig_ok()),this,SLOT(updateTreeWidget()));
    modal->show();
}

//导入监测点位置表
void RunStatePage::importPosition()
{

}

//导出监测点位置表
void RunStatePage::exportPosition()
{

}

void RunStatePage::updateTreeWidget()
{
    this->initTreeView();
}

void RunStatePage::updateImageWidget()
{
    this->m_pImageImdex->updateSensors();
}

//成功添加了一测监测点之后
void RunStatePage::addSensor(Sensor s)
{
    //左上角出现新的监测点
    this->m_pImageImdex->addSensor(s);
    //刷新左侧树状列表
    this->updateTreeWidget();
    //所有坐标点可移动 && 右下角位置编辑按钮
    this->m_pImageImdex->setSensorsMoveEnable(true);

}

//树状列表中的控件被点击
void RunStatePage::slot_treeItemClicked(QTreeWidgetItem *item, int column)
{
    if(!(qApp->mouseButtons() == Qt::RightButton)){
        return ;//不是右键直接返回
    }

    TDTreeWidgetItem * it = (TDTreeWidgetItem *)item;
    if(it->getType() == 1)//如果类型为1则是二级目录
    {
        QMenu * menu = new QMenu(this->m_pTreeWidget);
        QAction * act1 = new QAction("新增监测点");
        QAction * act2 = new QAction("修改监测点");
        QAction * act3 = new QAction("删除监测点");
		QAction * act4 = new QAction("报警描述");
		QAction * act5 = new QAction("事件描述");
		QAction * act6 = new QAction("通道对比");
		QAction * act7 = new QAction("历史趋势");
        //将id存入act通过信号和槽一起传递到槽函数
        act1->setProperty("id",it->getId());
        act2->setProperty("id",it->getId());
        act3->setProperty("id",it->getId());
		act4->setProperty("id",it->getId());
		act5->setProperty("id",it->getId());
		act6->setProperty("id",it->getId());
		act7->setProperty("id",it->getId());
        menu->addAction(act1);
        menu->addAction(act2);
        menu->addAction(act3);
		menu->addAction(act4);
		menu->addAction(act5);
		menu->addAction(act6);
		menu->addAction(act7);
        menu->setStyleSheet("background:#FFFFFF;color:#262626;");
        //监测点部分修改删除的实现！！
        connect(act1,SIGNAL(triggered(bool)),this,SLOT(slot_addSensor()));
        connect(act2,SIGNAL(triggered(bool)),this,SLOT(slot_alterSensor()));
        connect(act3,SIGNAL(triggered(bool)),this,SLOT(slot_deleteSensor()));
		connect(act4,SIGNAL(triggered(bool)),this,SIGNAL(sig_alarmDesc()));
		connect(act5,SIGNAL(triggered(bool)),this,SIGNAL(sig_eventDesc()));
		connect(act6,SIGNAL(triggered(bool)),this,SIGNAL(sig_channelCompare()));
		connect(act7,SIGNAL(triggered(bool)),this,SIGNAL(sig_histroy()));
        menu->exec(QCursor::pos());   //菜单弹出位置为鼠标点击位置
    }
    else   //类型不为1，一级目录
    {
        QMenu * menu = new QMenu(this->m_pTreeWidget);
        QAction * act1 = new QAction("删除间隔");
        QAction * act2 = new QAction("修改间隔");
        QAction * act3 = new QAction("新增监测点");
        //        QAction * act4 = new QAction("编辑监测点");
        //将id存入act通过信号和槽一起传递到槽函数
        act1->setProperty("id",it->getId());
        act2->setProperty("id",it->getId());
        act3->setProperty("id",it->getId());
        //        act4->setProperty("id",it->getId());
        menu->addAction(act1);
        menu->addAction(act2);
        menu->addAction(act3);
        //        menu->addAction(act4);
        menu->setStyleSheet("background:#FFFFFF;color:#262626;");
        connect(act1,SIGNAL(triggered(bool)),this,SLOT(slot_deleteSpacing()));
        connect(act2,SIGNAL(triggered(bool)),this,SLOT(slot_alterSpacing()));
        connect(act3,SIGNAL(triggered(bool)),this,SLOT(slot_addSensor()));
        //        connect(act4,SIGNAL(triggered(bool)),this,SLOT(slot_editSensor()));
        menu->exec(QCursor::pos());   //菜单弹出位置为鼠标点击位置
    }
}

void RunStatePage::slot_deleteSpacing()
{
    int id = sender()->property("id").toInt();
    int result = TDMessageBox::question("确定要删除此间隔吗？此操作将连同间隔下的所有监测点一起删除。");
    if(result == QMessageBox::Yes){
        //执行删除操作
        qDebug()<<"删除间隔，删除的id："<<id;
        if(Dao::getInstance()->deleteSpacing(id)){
            TDMessageBox::information("删除成功");
            this->updateTreeWidget();           //更新树形菜单
            this->updateImageWidget();          //更新一次接线图
        }else{
            TDMessageBox::warning("删除失败，请重试");
        }
    }

}

void RunStatePage::slot_alterSpacing()
{
    //获取要修改的间隔
    int id = sender()->property("id").toInt();
    Spacing spacing = Dao::getInstance()->GetSpacingById(id);
    //把间隔传入窗体进行修改
    AddSpacerModal * modal = new AddSpacerModal(spacing);
    connect(modal,SIGNAL(sig_ok()),this,SLOT(updateTreeWidget()));
    modal->show();

}

void RunStatePage::slot_addSensor()
{
    AddSensorModal * modal = new AddSensorModal();
    connect(modal,SIGNAL(sig_ok(Sensor)),this,SLOT(addSensor(Sensor)));
    modal->show();
    int id = sender()->property("id").toInt();
    qDebug()<<"添加监测点，所属间隔的id是："<<id;
}

void RunStatePage::slot_alterSensor()
{
    //获取要修改的监测点
    int id = sender()->property("id").toInt();
    Sensor sensor = Dao::getInstance()->GetSensorById(id);
    //把间隔传入窗体进行修改
    AddSensorModal * modal = new AddSensorModal(sensor);
    connect(modal,SIGNAL(sig_ok(Sensor s)),this,SLOT(updateTreeWidget()));
    modal->show();
}

void RunStatePage::slot_deleteSensor()
{
    int id = sender()->property("id").toInt();
    int result = TDMessageBox::question("确定要删除此监测点吗？此操作将删除此监测点及其所有数据。");
    if(result == QMessageBox::Yes){
        //执行删除操作
        qDebug()<<"删除监测点，删除的id："<<id;
        if(Dao::getInstance()->deleteSensor(id)){
            TDMessageBox::information("删除成功");
            this->updateTreeWidget();           //更新树形菜单
            this->updateImageWidget();          //更新一次接线图
        }else{
            TDMessageBox::warning("删除失败，请重试");
        }
    }
}
