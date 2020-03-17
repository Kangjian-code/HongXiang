/**************************************************************
 * File Name   : argsconfig.cpp
 * Author      : ThreeDog
 * Date        : Sun Jan 27 15:40:00 2019
 * Description : 参数设置，放电参数设置、报警参数设置、其他参数设置
 *
 **************************************************************/

#include "argsconfig.h"

ArgsConfig::ArgsConfig(QWidget *parent)
    :TDModal("参数设置",parent)
{
    this->resize(830,570);
    m_pArticleVLayout->setContentsMargins(6,20,6,30);
    m_pWidget = new QWidget;
//    m_pWidget->setFixedWidth(820);
    m_pWidget->resize(820,1000);
    TDScrollArea * scrollArea = new TDScrollArea;
    this->m_pArticleVLayout->addWidget(scrollArea);
    scrollArea->setWidget(m_pWidget);
    scrollArea->setSliderColor(QColor("#FFFFFF"),QColor("#DFDFDF"));
    scrollArea->setSliderOpacity(255,255);
    m_pWidget->show();
    this->initArgs();
    id = 0;
    updateArgsConfig();
    connect(m_pOKBtn,SIGNAL(clicked()),this,SLOT(slot_okBtnClicked()));
}

//初始化参数配置
void ArgsConfig::initArgs()
{
    //整体的垂直布局
    m_pArgsLayout  = new QVBoxLayout();
    m_pArgsLayout->setContentsMargins(20,3,20,3);
    m_pArgsLayout->setSpacing(20);
    m_pWidget->setLayout(m_pArgsLayout);
    //放电参数设置
    QLabel * text1 = new QLabel("放电参数设置",m_pWidget);
    text1->setAlignment(Qt::AlignCenter);
    text1->setStyleSheet("width:98px;\
                         height:21px;\
                         font-size:16px;\
                         font-family:微软雅黑;\
                         color:rgba(38,38,38,1);\
                         line-height:21px;");
    m_pArgsLayout->addWidget(text1);

    //放电类型
    QHBoxLayout * h1 = new QHBoxLayout;
    QLabel * text2 = new QLabel("放电类型：",this);
    m_pTypeCombo = new QComboBox(m_pWidget);
    m_pTypeCombo->addItem("自由金属颗粒");
    m_pTypeCombo->addItem("其他");
    m_pTypeCombo->setProperty("author","ThreeDog");
    h1->addWidget(text2,2);
    h1->addWidget(m_pTypeCombo,3);
    h1->addStretch(10);
    m_pArgsLayout->addLayout(h1);

    //1档幅值
    QHBoxLayout * h2 = new QHBoxLayout;
    QLabel * text3 = new QLabel(" 1档幅值：",m_pWidget);
    m_pFirstMinEdit = new QLineEdit(m_pWidget);
    m_pFirstMaxEdit = new QLineEdit(m_pWidget);
    QLabel * text4 = new QLabel("dBm",m_pWidget);
    QLabel * text5 = new QLabel("档位描述：",m_pWidget);
    m_pFirstDescEdit = new QLineEdit(m_pWidget);
    QLabel * text6 = new QLabel("报警颜色：",m_pWidget);
    QWidget * w1 = new QWidget(m_pWidget);
    w1->setStyleSheet("background:#F8E71C;\
                      border:1px solid #DFDFDF;\
                      max-height:34px;\
                      max-width:68px;\
                      border-radius:2px;");
    w1->show();
    h2->addWidget(text3,2);
    h2->addWidget(m_pFirstMinEdit,2);
    h2->addWidget(m_pFirstMaxEdit,2);
    h2->addWidget(text4,2);
    h2->addWidget(text5,2);
    h2->addWidget(m_pFirstDescEdit,3);
    h2->addWidget(text6,1);
    h2->addWidget(w1,1);
    m_pArgsLayout->addLayout(h2);

    //2档幅值
    QHBoxLayout * h3 = new QHBoxLayout;
    QLabel * text7 = new QLabel(" 2档幅值：",m_pWidget);
    m_pSecondMinEdit = new QLineEdit(m_pWidget);
    m_pSecondMaxEdit = new QLineEdit(m_pWidget);
    QLabel * text8 = new QLabel("dBm",m_pWidget);
    QLabel * text9 = new QLabel("档位描述：",m_pWidget);
    m_pSecondDescEdit = new QLineEdit(m_pWidget);
    QLabel * text10 = new QLabel("报警颜色：",m_pWidget);
    QWidget * w2 = new QWidget(m_pWidget);
    w2->setStyleSheet("background:#F5A623;\
                      border:1px solid #DFDFDF;\
                        max-height:34px;\
                        max-width:68px;\
                        border-radius:2px;");
    h3->addWidget(text7,2);
    h3->addWidget(m_pSecondMinEdit,2);
    h3->addWidget(m_pSecondMaxEdit,2);
    h3->addWidget(text8,2);
    h3->addWidget(text9,2);
    h3->addWidget(m_pSecondDescEdit,3);
    h3->addWidget(text10,1);
    h3->addWidget(w2,1);
    m_pArgsLayout->addLayout(h3);

    //3档幅值
    QHBoxLayout * h4 = new QHBoxLayout;
    QLabel * text11 = new QLabel(" 3档幅值：",m_pWidget);
    m_pThirdMinEdit = new QLineEdit(m_pWidget);
    m_pThirdMaxEdit = new QLineEdit(m_pWidget);
    QLabel * text12 = new QLabel("dBm",m_pWidget);
    QLabel * text13 = new QLabel("档位描述：",m_pWidget);
    m_pThirdDescEdit = new QLineEdit(m_pWidget);
    QLabel * text14 = new QLabel("报警颜色：",m_pWidget);
    QWidget * w3 = new QWidget(m_pWidget);
    w3->setStyleSheet("background:#FF5E4D;\
                      border:1px solid #DFDFDF;\
                        max-height:34px;\
                        max-width:68px;\
                        border-radius:2px;");
    h4->addWidget(text11,2);
    h4->addWidget(m_pThirdMinEdit,2);
    h4->addWidget(m_pThirdMaxEdit,2);
    h4->addWidget(text12,2);
    h4->addWidget(text13,2);
    h4->addWidget(m_pThirdDescEdit,3);
    h4->addWidget(text14,1);
    h4->addWidget(w3,1);
    m_pArgsLayout->addLayout(h4);

    //4档幅值
    QHBoxLayout * h5 = new QHBoxLayout;
    QLabel * text15 = new QLabel(" 4档幅值：",m_pWidget);
    m_pFourthMinEdit = new QLineEdit(m_pWidget);
    m_pFourthMaxEdit = new QLineEdit(m_pWidget);
    QLabel * text16 = new QLabel("dBm",m_pWidget);
    QLabel * text17 = new QLabel("档位描述：",m_pWidget);
    m_pFourthDescEdit = new QLineEdit(m_pWidget);
    QLabel * text18 = new QLabel("报警颜色：",m_pWidget);
    QWidget * w4 = new QWidget(m_pWidget);
    w4->setStyleSheet("background:#D32010;\
                      border:1px solid #DFDFDF;\
                        max-height:34px;\
                        max-width:68px;\
                        border-radius:2px;");
    h5->addWidget(text15,2);
    h5->addWidget(m_pFourthMinEdit,2);
    h5->addWidget(m_pFourthMaxEdit,2);
    h5->addWidget(text16,2);
    h5->addWidget(text17,2);
    h5->addWidget(m_pFourthDescEdit,3);
    h5->addWidget(text18,1);
    h5->addWidget(w4,1);
    m_pArgsLayout->addLayout(h5);


    //报警参数设置
    QLabel * text19 = new QLabel("报警参数设置",m_pWidget);
    text19->setAlignment(Qt::AlignCenter);
    text19->setStyleSheet("width:98px;\
                         height:21px;\
                         font-size:16px;\
                         font-family:微软雅黑;\
                         color:rgba(38,38,38,1);\
                         line-height:21px;");

    m_pArgsLayout->addWidget(text19);
    m_pWarningConfigGroup = new QGroupBox(m_pWidget);
    m_pWarningConfigGroup->setTitle("设备局放报警设置");
    m_pArgsLayout->addWidget(m_pWarningConfigGroup);

    //设备局放报警设置
    QGridLayout * grid1 = new QGridLayout;
    grid1->setSpacing(20);
    m_pWarningConfigGroup->setLayout(grid1);
    grid1->setMargin(20);
    m_pArgsLayout->addWidget(m_pWarningConfigGroup);
    QLabel * label1 = new QLabel("报警观察时间：",this);
    QLabel * label2 = new QLabel("分钟",this);
    QLabel * label3 = new QLabel("报警次数阈值：",this);
    QLabel * label4 = new QLabel("装置故障次数阈值：",this);
    QLabel * label5 = new QLabel("报警时间间隔：",this);
    m_pWarningTimeEdit = new QLineEdit(m_pWarningConfigGroup);
    m_pWarningTimeEdit->setProperty("author","ThreeDog");
    m_pWarningTimesEdit = new QLineEdit(m_pWarningConfigGroup);
    m_pWarningTimesEdit->setProperty("author","ThreeDog");
    m_pBrokenTimeEdit = new QLineEdit(m_pWarningConfigGroup);
    m_pBrokenTimeEdit->setProperty("author","ThreeDog");
    m_pWarningIntervelEdit = new QLineEdit(m_pWarningConfigGroup);
    m_pWarningIntervelEdit->setProperty("author","ThreeDog");
    grid1->addWidget(label1,0,0);
    grid1->addWidget(m_pWarningTimeEdit,0,1);
    grid1->addWidget(label2,0,2);
    grid1->addWidget(label3,0,3);
    grid1->addWidget(m_pWarningTimesEdit,0,4);

    grid1->addWidget(label4,1,0);
    grid1->addWidget(m_pBrokenTimeEdit,1,1);
    grid1->addWidget(label5,1,3);
    grid1->addWidget(m_pWarningIntervelEdit,1,4);
    m_pArgsLayout->addWidget(m_pWarningConfigGroup);

    //报警信号节点设置
    QGridLayout * grid2 = new QGridLayout;
    grid2->setSpacing(20);
    m_pNodeConfigGroup = new QGroupBox(m_pWidget);
    m_pNodeConfigGroup->setTitle("报警信号节点设置");
    m_pNodeConfigGroup->setLayout(grid2);
    grid2->setMargin(20);
    m_pArgsLayout->addWidget(m_pNodeConfigGroup);
    QLabel * label6 = new QLabel("是否报警：",m_pWidget);
    QLabel * label7 = new QLabel("报警视察周期：",m_pWidget);
    QLabel * label8 = new QLabel("最大放电幅值阈值：",m_pWidget);
    QLabel * label9 = new QLabel("dBm",m_pWidget);
    QLabel * label10 = new QLabel("局放概率阈值：",m_pWidget);
    m_pIsWarningCheck = new QCheckBox(m_pNodeConfigGroup);
    m_pCheckIntervelCombo = new QComboBox(m_pNodeConfigGroup);
    m_pCheckIntervelCombo->setProperty("author","ThreeDog");
    m_pCheckIntervelCombo->addItem("一天");
    m_pCheckIntervelCombo->addItem("一周");
    m_pCheckIntervelCombo->addItem("一月");
    m_pCheckIntervelCombo->addItem("一年");
    m_pMaxChargeEdit = new QLineEdit(m_pNodeConfigGroup);
    m_pMaxChargeEdit->setProperty("author","ThreeDog");
    m_pChanceEdit = new QLineEdit(m_pNodeConfigGroup);
    m_pChanceEdit->setProperty("author","ThreeDog");

    grid2->addWidget(label6,0,0);
    grid2->addWidget(m_pIsWarningCheck,0,1);
    grid2->addWidget(label7,0,3);
    grid2->addWidget(m_pCheckIntervelCombo,0,4);

    grid2->addWidget(label8,1,0);
    grid2->addWidget(m_pMaxChargeEdit,1,1);
    grid2->addWidget(label9,1,2);
    grid2->addWidget(label10,1,3);
    grid2->addWidget(m_pChanceEdit,1,4);
    m_pArgsLayout->addWidget(m_pNodeConfigGroup);


    //其他参数设置
    QLabel * text20 = new QLabel("其他参数设置",m_pWidget);
    text20->setAlignment(Qt::AlignCenter);
    text20->setStyleSheet("width:98px;\
                         height:21px;\
                         font-size:16px;\
                         font-family:微软雅黑;\
                         color:rgba(38,38,38,1);\
                         line-height:21px;");

    m_pArgsLayout->addWidget(text20);

    QGridLayout * grid3 = new QGridLayout;
    grid3->setSpacing(20);
    grid3->setMargin(20);
    QLabel * label11 = new QLabel("高于平均放电平均水平值：",m_pWidget);
    QLabel * label12 = new QLabel("dBm",m_pWidget);
    QLabel * label13 = new QLabel("录波时间：",m_pWidget);
    QLabel * label14 = new QLabel("秒",m_pWidget);
    QLabel * label15 = new QLabel("采样间隔：",m_pWidget);
    QLabel * label16 = new QLabel("分钟",m_pWidget);
    QLabel * label17 = new QLabel("自检时间：",m_pWidget);
    QLabel * label18 = new QLabel("小时",m_pWidget);
    QLabel * label19 = new QLabel("（采样间隔时间设置不能低于五分钟）",m_pWidget);
    label19->setStyleSheet("width:200px;\
                           height:16px;\
                           font-size:12px;\
                           font-family:微软雅黑;\
                           color:rgba(151,151,151,1);\
                           line-height:16px;");
    m_pAVGChargeEdit = new QLineEdit(m_pWidget);
    m_pRecordTimeEdit = new QLineEdit(m_pWidget);
    m_pRecordIntervelEdit = new QLineEdit(m_pWidget);
    m_pSelfCheckEdit = new QLineEdit(m_pWidget);

    grid3->addWidget(label11,0,0);
    grid3->addWidget(m_pAVGChargeEdit,0,1);
    grid3->addWidget(label12,0,2);
    grid3->addWidget(label13,0,4);
    grid3->addWidget(m_pRecordTimeEdit,0,5);
    grid3->addWidget(label14,0,6);

    grid3->addWidget(label15,1,0);
    grid3->addWidget(m_pRecordIntervelEdit,1,1);
    grid3->addWidget(label16,1,2);
    grid3->addWidget(label17,1,4);
    grid3->addWidget(m_pSelfCheckEdit,1,5);
    grid3->addWidget(label18,1,6);
    m_pArgsLayout->addLayout(grid3);
    m_pArgsLayout->addWidget(label19);

    //给本页面所有的LienEdit加上ThreeDog属性
    foreach(QLineEdit * edit,this->findChildren<QLineEdit *>()){
        edit->setProperty("author","ThreeDog");
    }

}

void ArgsConfig::updateArgsConfig()
{
    QSqlQuery query;
    query.exec(QString("select * from hxdl.config where id = %1;").arg(Dao::getInstance()->getId()));
    while(query.next()){
        id = query.value("id").toInt();
        this->m_pTypeCombo->setCurrentText(query.value("dschType").toString());
        this->m_pFirstMinEdit->setText(query.value("lowerLimit1").toString());
        this->m_pSecondMinEdit->setText(query.value("lowerLimit2").toString());
        this->m_pThirdMinEdit->setText(query.value("lowerLimit3").toString());
        this->m_pFourthMinEdit->setText(query.value("lowerLimit4").toString());
        this->m_pFirstMaxEdit->setText(query.value("higherLimit1").toString());
        this->m_pSecondMaxEdit->setText(query.value("higherLimit2").toString());
        this->m_pThirdMaxEdit->setText(query.value("higherLimit3").toString());
        this->m_pFourthMaxEdit->setText(query.value("higherLimit4").toString());
        this->m_pFirstDescEdit->setText(query.value("desc1").toString());
        this->m_pSecondDescEdit->setText(query.value("desc2").toString());
        this->m_pThirdDescEdit->setText(query.value("desc3").toString());
        this->m_pFourthDescEdit->setText(query.value("desc4").toString());
        this->m_pWarningTimeEdit->setText(query.value("alarmObMin").toString());
        this->m_pWarningTimesEdit->setText(query.value("alarmTimesTd").toString());
        this->m_pBrokenTimeEdit->setText(query.value("deviceFaulThreshold").toString());
        this->m_pWarningIntervelEdit->setText(query.value("alarmDurationTime").toString());
        this->m_pCheckIntervelCombo->setCurrentText(query.value("alarmObservationDay").toString());
        this->m_pMaxChargeEdit->setText(query.value("maxAmplitude").toString());
        this->m_pChanceEdit->setText(query.value("dischargeProbabilityThreshold").toString());
        this->m_pAVGChargeEdit->setText(query.value("higherAverageLevel").toString());
        this->m_pRecordIntervelEdit->setText(query.value("samplingPeriod").toString());
        this->m_pRecordTimeEdit->setText(query.value("recordDuration").toString());
        this->m_pSelfCheckEdit->setText(query.value("selfCheckTime").toString());
        if(query.value("isAlarm").toInt() == 0)
            this->m_pIsWarningCheck->setChecked(false);
        else
            this->m_pIsWarningCheck->setChecked(true);
    }
}

ArgsConfig::~ArgsConfig()
{

}

//确认按钮被点击
void ArgsConfig::slot_okBtnClicked()
{
    emit okBtnClicked();
    //信息存入数据库
    Config config;
    config.id = Dao::getInstance()->getId();
    config.lastTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    config.alarmDurationTime = m_pWarningIntervelEdit->text().toInt();
    config.alarmObMin = m_pWarningTimeEdit->text().toInt();
    config.alarmObservationDay = m_pCheckIntervelCombo->currentText().toInt();
    config.alarmTimesTd = m_pWarningTimesEdit->text().toInt();
    config.color1 = "#F8E71C";
    config.color2 = "#F5A623";
    config.color3 = "#FF5E4D";
    config.color4 = "#DFDFDF";
    config.createTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    config.desc1 = m_pFirstDescEdit->text();
    config.desc2 = m_pSecondDescEdit->text();
    config.desc3 = m_pThirdDescEdit->text();
    config.desc4 = m_pFourthDescEdit->text();
    config.deviceFaulThreshold = m_pBrokenTimeEdit->text().toInt();
    config.dischargeNumThreshold = 20;
    config.dischargeProbabilityThreshold = m_pChanceEdit->text().toInt();
    config.dschType = m_pTypeCombo->currentText();
    config.higherAverageLevel = m_pAVGChargeEdit->text().toInt();
    config.higherLimit1 = m_pFirstMaxEdit->text().toFloat();
    config.higherLimit2 = m_pSecondMaxEdit->text().toFloat();
    config.higherLimit3 = m_pThirdMaxEdit->text().toFloat();
    config.higherLimit4 = m_pFourthMaxEdit->text().toFloat();
    config.isAlarm = m_pIsWarningCheck->isChecked();
    config.lowerLimit1 = m_pFirstMinEdit->text().toFloat();
    config.lowerLimit2 = m_pSecondMinEdit->text().toFloat();
    config.lowerLimit3 = m_pThirdMinEdit->text().toFloat();
    config.lowerLimit4 = m_pFourthMinEdit->text().toFloat();
    config.maxAmplitude = m_pMaxChargeEdit->text().toInt();
    config.numPerDuration = 20;
    config.recordDuration = m_pRecordTimeEdit->text().toInt();
    config.samplingPeriod = m_pRecordIntervelEdit->text().toInt();
    config.selfCheckTime = m_pSelfCheckEdit->text().toInt();
    //将数据插入或者将数据更新
    if(Dao::getInstance()->InsertOrUpdateConfig(config)){
        TDMessageBox::information("保存成功");
    }else{
        TDMessageBox::warning("保存失败");
    }
}
