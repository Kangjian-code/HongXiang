/**************************************************************
 * File Name   : addsensormodal.cpp
 * Author      : ThreeDog 
 * Date        : Thu Apr 11 22:56:43 2019
 * Description : 新增监测点
 *
 **************************************************************/

#include "addsensormodal.h"

AddSensorModal::AddSensorModal(QWidget *parent)
    :TDModal("新增监测点",parent)
{
	this->initInterface();
}

AddSensorModal::AddSensorModal(const Sensor &s, QWidget *parent)
	:TDModal("修改监测点",parent)
{
	this->initInterface();
	this->m_iId = s.id;
	this->m_pNameEdit->setText(s.name);
	QString spacingName = Dao::getInstance()->GetSpacingById(s.spacing_id).name;
    this->m_pSpacingCombo->setCurrentText(spacingName);
	QString IEDName = Dao::getInstance()->GetIEDById(s.ied1_id).name;
    this->m_pIEDCombo->setCurrentText(IEDName);
	this->m_pDeviceNoEdit->setText(s.sn);
	this->m_pChannelNo->setCurrentIndex(s.channel_no);
	this->m_pTypeCombo->setCurrentIndex(s.type);
    this->m_pAlarmThresholdEdit->setText(QString::number(s.alarmThreshold));
    this->m_pPulseThresholdEdit->setText(QString::number(s.pulseThreshold));
    this->m_pFreqBandEdit->setText(QString::number(s.freqBand));
    this->m_pReferToThreshold->setText(QString::number(s.referToThreshold));
	this->m_pNoiseChannelNo->setText(QString::number(s.noiseChannelNo));
}

void AddSensorModal::initInterface()
{
	this->m_iId = -1;
	this->resize(610,773);
	//监测点名称一行
	QHBoxLayout * h1 = new QHBoxLayout;
	QLabel * label1 = new QLabel("监测点名称",this);
	m_pNameEdit = new QLineEdit(this);
	m_pNameEdit->setPlaceholderText("请输入监测点名称");
	m_pNameEdit->setProperty("author","ThreeDog");
	h1->addWidget(label1,2);
	h1->addWidget(m_pNameEdit,8);
	this->m_pArticleVLayout->addLayout(h1);

	//所属间隔一行
	QHBoxLayout * h2 = new QHBoxLayout;
	QLabel * label2 = new QLabel("所属间隔",this);
	m_pSpacingCombo = new QComboBox(this);
	for(auto spacing : Dao::getInstance()->QuerySpacing()){
		m_pSpacingCombo->addItem(spacing.name);
	}
	m_pSpacingCombo->setProperty("author","ThreeDog");
	h2->addWidget(label2,2);
	h2->addWidget(m_pSpacingCombo,2);
	h2->addStretch(6);
	this->m_pArticleVLayout->addLayout(h2);

	//所属采集单元
	QHBoxLayout * h3 = new QHBoxLayout;
	QLabel * label3 = new QLabel("所属采集单元",this);
	m_pIEDCombo = new QComboBox(this);
	for(auto ied : Dao::getInstance()->QueryIed()){
		m_pIEDCombo->addItem(ied.name);
	}
	m_pIEDCombo->setProperty("author","ThreeDog");
	h3->addWidget(label3,2);
	h3->addWidget(m_pIEDCombo,2);
	h3->addStretch(6);
	this->m_pArticleVLayout->addLayout(h3);


	//设备编号
	QHBoxLayout * h4 = new QHBoxLayout;
	QLabel * label4 = new QLabel("设备编号",this);
	m_pDeviceNoEdit = new QLineEdit(this);
	m_pDeviceNoEdit->setProperty("author","ThreeDog");
	h4->addWidget(label4,2);
	h4->addWidget(m_pDeviceNoEdit,8);
	this->m_pArticleVLayout->addLayout(h4);

	//通道号
	QHBoxLayout * h5 = new QHBoxLayout;
	QLabel * label5 = new QLabel("通道号",this);
	m_pChannelNo = new QComboBox(this);
	for(int i = 1; i <= 8; i++){
		m_pChannelNo->addItem(QString::number(i));
	}
	m_pChannelNo->setProperty("author","ThreeDog");
	h5->addWidget(label5,2);
	h5->addWidget(m_pChannelNo,2);
	h5->addStretch(6);
	this->m_pArticleVLayout->addLayout(h5);

	//类型
	QHBoxLayout * h6 = new QHBoxLayout;
	QLabel * label6 = new QLabel("类型",this);
	m_pTypeCombo = new QComboBox(this);
	m_pTypeCombo->addItem("UHF");
	m_pTypeCombo->addItem("振动");
	m_pTypeCombo->addItem("噪声");
	m_pTypeCombo->setProperty("author","ThreeDog");
	h6->addWidget(label6,2);
	h6->addWidget(m_pTypeCombo,2);
	h6->addStretch(6);
	this->m_pArticleVLayout->addLayout(h6);

	//站点图片文字&按钮
	QHBoxLayout * h7 = new QHBoxLayout;
	QLabel * label7 = new QLabel("* 安装图片（400px*200px，jpg,png）",this);
	m_pChoicePicBtn = new QPushButton("选择图片",this);
	m_pChoicePicBtn->setObjectName("subButton");
	connect(m_pChoicePicBtn,SIGNAL(clicked(bool)),this,SLOT(slot_addPic()));
	h7->addWidget(label7);
	h7->addStretch();
	h7->addWidget(m_pChoicePicBtn);
	this->m_pArticleVLayout->addLayout(h7);

	//最下面显示图片的区域
	QHBoxLayout * h8 = new QHBoxLayout;
	m_pPicWidget = new QWidget(this);
	h8->addStretch(2);
	h8->addWidget(m_pPicWidget,6);
	h8->addStretch(2);
	m_pPicWidget->setStyleSheet("border-radius:2px ; border:1px solid #DFDFDF;width:440px;height:220px");
	//在窗体中加一个label用于显示图片
	QHBoxLayout * hh = new QHBoxLayout;
	m_pPicWidget->setLayout(hh);
	hh->setMargin(3);
	m_pPicLabel = new QLabel(this);
	m_pPicLabel->setStyleSheet(" border:none;");
	m_pPicLabel->setFixedSize(200,100);
	m_pPicWidget->setFixedSize(210,110);
	hh->addWidget(m_pPicLabel);

	this->m_pArticleVLayout->addLayout(h8);

	//报警阈值
	QHBoxLayout * h9 = new QHBoxLayout;
	QLabel * label9 = new QLabel("报警阈值",this);
	m_pAlarmThresholdEdit = new QLineEdit(this);
	m_pAlarmThresholdEdit->setProperty("author","ThreeDog");
	h9->addWidget(label9,2);
	h9->addWidget(m_pAlarmThresholdEdit,8);
	this->m_pArticleVLayout->addLayout(h9);

	//脉冲数量阈值
	QHBoxLayout * h10 = new QHBoxLayout;
	QLabel * label10 = new QLabel("脉冲数量阈值",this);
	m_pPulseThresholdEdit = new QLineEdit(this);
	m_pPulseThresholdEdit->setProperty("author","ThreeDog");
	h10->addWidget(label10,2);
	h10->addWidget(m_pPulseThresholdEdit,8);
	this->m_pArticleVLayout->addLayout(h10);

	//频带
	QHBoxLayout * h11 = new QHBoxLayout;
	QLabel * label11 = new QLabel("频带",this);
	m_pFreqBandEdit = new QLineEdit(this);
	m_pFreqBandEdit->setProperty("author","ThreeDog");
	h11->addWidget(label11,2);
	h11->addWidget(m_pFreqBandEdit,8);
	this->m_pArticleVLayout->addLayout(h11);

	//参考阈值
	QHBoxLayout * h12 = new QHBoxLayout;
	QLabel * label12 = new QLabel("参考阈值",this);
	m_pReferToThreshold = new QLineEdit(this);
	m_pReferToThreshold->setProperty("author","ThreeDog");
	h12->addWidget(label12,2);
	h12->addWidget(m_pReferToThreshold,8);
	this->m_pArticleVLayout->addLayout(h12);

	//关联噪声通道
	QHBoxLayout * h13 = new QHBoxLayout;
	QLabel * label13 = new QLabel("关联噪声通道",this);
	m_pNoiseChannelNo = new QLineEdit(this);
	m_pNoiseChannelNo->setProperty("author","ThreeDog");
	h13->addWidget(label13,2);
	h13->addWidget(m_pNoiseChannelNo,8);
	this->m_pArticleVLayout->addLayout(h13);

	this->m_pArticleVLayout->setSpacing(20);

	this->setButtonText("返回","保存");
	this->m_pOKBtn->setStyleSheet("width:145px;");
	this->m_pCancleBtn->setStyleSheet("width:145px;");
	connect(m_pOKBtn,SIGNAL(clicked(bool)),this,SLOT(slot_okBtnClicked()));

	QString stylesheet = "QLabel{\
						font-size:14px;\
						color:#262626;\
						font-family:Microsoft Yahei;\
						line-height:19px;\
						}\
						";
this->setStyleSheet(stylesheet);
}

AddSensorModal::~AddSensorModal()
{

}

//点击确认按钮
void AddSensorModal::slot_okBtnClicked()
{
    //生成一个新的监测点对象、通过接口插入数据库
    Sensor s;
    s.ied1_id = Dao::getInstance()->GetIEDByName(this->m_pIEDCombo->currentText()).id;//注意这里未做容错校验、
    s.ied2_id = Dao::getInstance()->GetIEDByName(this->m_pIEDCombo->currentText()).id;//注意这里未做容错校验、
    s.spacing_id = Dao::getInstance()->GetSpacingByName(this->m_pSpacingCombo->currentText()).id;//注意这里未做容错校验、
    s.type = this->m_pTypeCombo->currentIndex();
    s.name = this->m_pNameEdit->text();
    s.sn = this->m_pDeviceNoEdit->text();
    s.channel_no = this->m_pChannelNo->currentText().toInt();
    s.alarmThreshold = this->m_pAlarmThresholdEdit->text().toInt();
    s.pulseThreshold = this->m_pPulseThresholdEdit->text().toInt();
    s.freqBand = this->m_pFreqBandEdit->text().toInt();
    s.referToThreshold = this->m_pReferToThreshold->text().toInt();
    s.lastConnectTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    s.noiseChannelNo = this->m_pNoiseChannelNo->text().toInt();
    s.createTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    s.lastTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    s.isDelete = 0;
	//如果id是-1，执行插入的逻辑
	if(m_iId == -1){
		s.site_x = 100.0;
		s.site_y = 100.0;
		s.spacing_x = 100.0;
		s.spacing_y = 100.0;
		s.pictureURL = "http://192.16.8.1.1/test.png";
		//执行插入逻辑
		if(Dao::getInstance()->InsertSensor(s)){
			TDMessageBox::information("添加成功");
			//获取到完整的Sensor发射出去
			s = Dao::getInstance()->GetSensorByName(this->m_pNameEdit->text());
			emit sig_ok(s);
		}else{
			TDMessageBox::warning("添加失败，请重试");
		}
	}else{
		//执行修改逻辑，修改
        s.id = this->m_iId;
        if(Dao::getInstance()->UpdateSensor(s)){
            TDMessageBox::information("修改成功");
			//获取到完整的Sensor发射出去
			s = Dao::getInstance()->GetSensorByName(this->m_pNameEdit->text());
			emit sig_ok(s);
		}else{
            TDMessageBox::warning("修改失败，请重试");
		}
	}


}

//选择图片
void AddSensorModal::slot_addPic()
{
    //加载图片
    QString picPath = QFileDialog::getOpenFileName(this,"选择图片",QDir::homePath(),"Images (*.png *.xpm *.jpg)");
    QPixmap pic;
    pic.load(picPath);
    pic = pic.scaled(this->m_pPicLabel->size(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    this->m_pPicLabel->setPixmap(pic);
}

void AddSensorModal::slot_editPosition()
{
    //监测点位置编辑
}

