/**************************************************************
 * File Name   : quickwarningform.cpp
 * Author      : ThreeDog
 * Date        : Fri Feb 15 22:01:42 2019
 * Description : 震动报警页面
 *
 **************************************************************/
#include "quakewarningform.h"
#include "ui_quakewarningform.h"

QuakeWarningForm::QuakeWarningForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QuakeWarningForm)
{
    ui->setupUi(this);
    initInterface();
    initProperty();
    initTable();
    updateTable();
    connect(this->ui->queryBtn,SIGNAL(clicked(bool)),this,SLOT(updateTable()));

}

void QuakeWarningForm::initInterface()
{
    //初始化界面上的几个控件的内容
    //间隔
    for(Sensor s : Dao::getInstance()->QuerySensors()){
        ui->sensorCombo->addItem(s.name);
    }
    //监测点56
    for(Spacing s : Dao::getInstance()->QuerySpacing()){
        ui->spacingCombo->addItem(s.name);
    }
    typeMap.insert(0,"正常");
    typeMap.insert(1,"传感器未接入");
    typeMap.insert(2,"采集报警异常");
    typeMap.insert(3,"同步频率出错");
    typeMap.insert(4,"同步源未连接");
    typeMap.insert(5,"同步方式设置差异");
}

void QuakeWarningForm::initProperty()
{
    ui->spacingCombo->setProperty("author","ThreeDog");
    ui->sensorCombo->setProperty("author","ThreeDog");
    ui->alarmTypeCombo->setProperty("author","ThreeDog");
    ui->startTimeEdit->setProperty("author","ThreeDog");
    ui->startTimeEdit->setDateTime(QDateTime::currentDateTime());
    ui->startTimeEdit->setCalendarPopup(true);
    ui->endTimeEdit->setProperty("author","ThreeDog");
    ui->endTimeEdit->setDateTime(QDateTime::currentDateTime());
    ui->endTimeEdit->setCalendarPopup(true);
}

void QuakeWarningForm::initTable()
{
    m_pTableWidget = new QTableWidget(ui->mainWidget);
    ui->hLayout->addWidget(m_pTableWidget);

    m_pTableWidget->setColumnCount(8);

    QStringList headText;
    headText << "" << "间隔" << "监测点"<< "报警类型" << "报警时间" << "指标" << "故障描述" << "操作" ;
    m_pTableWidget->setHorizontalHeaderLabels(headText);
    //首先定义一个复选框表头
    MyQHeaderView *updateHeader = new MyQHeaderView(Qt::Horizontal,m_pTableWidget);
    //表头的复选框被点击的事件：
    connect(updateHeader,SIGNAL(signalStateTrange(bool)),this,SLOT(checkBoxClicked(bool)));
    //其次设置表格的表头
    m_pTableWidget->setHorizontalHeader(updateHeader);
    m_pTableWidget->setColumnWidth(0,88);
    m_pTableWidget->setColumnWidth(1,250);
    m_pTableWidget->setColumnWidth(2,250);
    m_pTableWidget->setColumnWidth(3,250);
    m_pTableWidget->setColumnWidth(4,250);
    m_pTableWidget->setColumnWidth(5,250);
    m_pTableWidget->setColumnWidth(6,250);
    m_pTableWidget->setColumnWidth(7,250);

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

void QuakeWarningForm::updateTable()
{
    //设备报警数据，根据条件从数据库查询结果，显示在界面上
    QString startTime = ui->startTimeEdit->dateTime().toString("yyyy-MM-dd hh:mm:ss");
    QString endTime   = ui->endTimeEdit->dateTime().toString("yyyy-MM-dd hh:mm:ss");
    QString spacing   = ui->spacingCombo->currentText();
    QString sensor    = ui->sensorCombo->currentText();
    int type      = ui->alarmTypeCombo->currentIndex();

    QVector<SensorDeviceAlarm> vect = Dao::getInstance()->QueryDeviceWarning(startTime,endTime,type,spacing,sensor);

    for(int i = 0 ; i < vect.count() ; i++){
        m_pTableWidget->setRowHeight(i, 40);
        SensorDeviceAlarm alarm = vect.at(i);

        QWidget * w = new QWidget(m_pTableWidget);
        QHBoxLayout * h = new QHBoxLayout;
        w->setLayout(h);
        h->setContentsMargins(10,3,10,3);
        h->addStretch();
        QCheckBox * check = new QCheckBox;
        check->setObjectName("QCheckBox");
        check->setProperty("id",alarm.id);
        h->addWidget(check);
        h->addStretch();

        this->m_pTableWidget->setCellWidget(i,0,w);
        Sensor s = Dao::getInstance()->GetSensorById(alarm.sensor_id);
        QString spacingName = Dao::getInstance()->GetSpacingById(s.spacing_id).name;
        QString sensorName  = s.name;

        QTableWidgetItem *item1 = new QTableWidgetItem(spacingName);
        QTableWidgetItem *item2 = new QTableWidgetItem(sensorName);
        QTableWidgetItem *item3 = new QTableWidgetItem(typeMap.value(alarm.alarmType));
        QTableWidgetItem *item4 = new QTableWidgetItem(alarm.alarmTime);
        QTableWidgetItem *item5 = new QTableWidgetItem("正常");
        QTableWidgetItem *item6 = new QTableWidgetItem(alarm.alarmDesc);

        QWidget * w2 = new QWidget(m_pTableWidget);
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
        btn->setProperty("id",alarm.id);
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

        btn2->setProperty("id",alarm.id);
        btn2->setProperty("action","上传");
        this->m_pTableWidget->setCellWidget(i,7,w2);

        item1->setTextAlignment(Qt::AlignCenter);
        item2->setTextAlignment(Qt::AlignCenter);
        item3->setTextAlignment(Qt::AlignCenter);
        item4->setTextAlignment(Qt::AlignCenter);
        item5->setTextAlignment(Qt::AlignCenter);
        item6->setTextAlignment(Qt::AlignCenter);

        m_pTableWidget->setItem(i, 1, item1);
        m_pTableWidget->setItem(i, 2, item2);
        m_pTableWidget->setItem(i, 3, item3);
        m_pTableWidget->setItem(i, 4, item4);
        m_pTableWidget->setItem(i, 5, item5);
        m_pTableWidget->setItem(i, 6, item6);
    }

}

QuakeWarningForm::~QuakeWarningForm()
{
    delete ui;
}

void QuakeWarningForm::checkBoxClicked(bool b)
{
    if(b){
        qDebug()<<"打开所有的复选框";
        foreach(QCheckBox * check,this->m_pTableWidget->findChildren<QCheckBox *>()){
            check->setChecked(true);
        }
    }else{
        qDebug()<<"关闭所有的复选框";
        foreach(QCheckBox * check,this->m_pTableWidget->findChildren<QCheckBox *>()){
            check->setChecked(false);
        }
    }
}

