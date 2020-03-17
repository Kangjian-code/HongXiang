/**************************************************************
 * File Name   : addunitmodal.cpp
 * Author      : ThreeDog
 * Date        : Fri May 17 21:03:44 2019
 * Description : 单元配置的添加、修改模态框
 *		通道设置被默认初始化,只能在界面上进行修改,新增时一律采用默认设置
 **************************************************************/

#include "addunitmodal.h"

AddUnitModal::AddUnitModal(QWidget *parent)
	:TDModal("添加单元",parent)
{
	initInterface();
}

AddUnitModal::AddUnitModal(const Ied &ied, QWidget *parent)
	:TDModal("修改单元",parent)
{
	initInterface();
	this->m_iId = ied.id;
	this->ied = ied;
	m_pUnitNameEdit->setText(ied.name);
	m_pDeviceNoEdit->setText(ied.sn);
	m_pIPEdit->setText(ied.ip);
	m_pPortEdit->setText(QString::number(ied.port));
	m_pChannelNumberCombo->setCurrentText(QString::number(ied.channelNum));
	m_pSyncTypeCombo->setCurrentText(s_mapTypes.value(ied.syncType));
	m_pInnserSettingEdit->setText(QString::number(ied.interSyncFreq,'f',3));
	m_pDeviceStatus->setChecked((bool)ied.status);
}

QMap<int,QString> AddUnitModal::s_mapTypes;

void AddUnitModal::initInterface()
{
	m_iId = -1;
	this->resize(610,600);
	//初始化类型


	//单元名称
	QHBoxLayout * h1 = new QHBoxLayout;
	QLabel * label1 = new QLabel("单元名称",this);
	m_pUnitNameEdit = new QLineEdit(this);
	m_pUnitNameEdit->setPlaceholderText("请输入单元名称");
	m_pUnitNameEdit->setProperty("author","ThreeDog");
	h1->addWidget(label1,2);
	h1->addWidget(m_pUnitNameEdit,8);
	this->m_pArticleVLayout->addLayout(h1);

	//设备编号
	QHBoxLayout * h2 = new QHBoxLayout;
	QLabel * label2 = new QLabel("设备编号",this);
	m_pDeviceNoEdit = new QLineEdit(this);
	m_pDeviceNoEdit->setPlaceholderText("请输入设备编号");
	m_pDeviceNoEdit->setProperty("author","ThreeDog");
	h2->addWidget(label2,2);
	h2->addWidget(m_pDeviceNoEdit,8);
	this->m_pArticleVLayout->addLayout(h2);

	//IP地址
	QHBoxLayout * h3 = new QHBoxLayout;
	QLabel * label3 = new QLabel("IP地址",this);
	m_pIPEdit = new QLineEdit(this);
	m_pIPEdit->setPlaceholderText("请输入IP地址");
	m_pIPEdit->setProperty("author","ThreeDog");
	h3->addWidget(label3,2);
	h3->addWidget(m_pIPEdit,8);
	this->m_pArticleVLayout->addLayout(h3);

	//端口
	QHBoxLayout * h4 = new QHBoxLayout;
	QLabel * label4 = new QLabel("端口",this);
	m_pPortEdit = new QLineEdit(this);
	m_pPortEdit->setPlaceholderText("请输入端口");
	m_pPortEdit->setProperty("author","ThreeDog");
	h4->addWidget(label4,2);
	h4->addWidget(m_pPortEdit,8);
	this->m_pArticleVLayout->addLayout(h4);

	//通道数量
	QHBoxLayout * h5 = new QHBoxLayout;
	QLabel * label5 = new QLabel("通道数量",this);
	m_pChannelNumberCombo = new QComboBox(this);
	for(int i = 1; i <=8 ; i++){
		m_pChannelNumberCombo->addItem(QString::number(i));
	}
	m_pChannelNumberCombo->setCurrentIndex(7);
	m_pChannelNumberCombo->setProperty("author","ThreeDog");
	h5->addWidget(label5,2);
	h5->addWidget(m_pChannelNumberCombo,2);
	h5->addStretch(6);
	this->m_pArticleVLayout->addLayout(h5);

	//同步方式
	QHBoxLayout * h8 = new QHBoxLayout;
	QLabel * label8 = new QLabel("同步方式",this);
	m_pSyncTypeCombo = new QComboBox(this);
	m_pSyncTypeCombo->addItem("内同步");
	m_pSyncTypeCombo->addItem("PT同步");
	m_pSyncTypeCombo->addItem("工频同步");
	m_pSyncTypeCombo->addItem("外界调频同步");
	m_pSyncTypeCombo->setProperty("author","ThreeDog");
	h8->addWidget(label8,2);
	h8->addWidget(m_pSyncTypeCombo,2);
	h8->addStretch(6);
	this->m_pArticleVLayout->addLayout(h8);

	//内同步设置
	QHBoxLayout * h9 = new QHBoxLayout;
	QLabel * label9 = new QLabel("内同步设置",this);
	m_pInnserSettingEdit = new QLineEdit(this);
	m_pInnserSettingEdit->setProperty("author","ThreeDog");
	h9->addWidget(label9,2);
	h9->addWidget(m_pInnserSettingEdit,8);
	this->m_pArticleVLayout->addLayout(h9);

	//设备状态按钮
	QHBoxLayout * h10 = new QHBoxLayout;
	QLabel * label10 = new QLabel("设备状态",this);
	m_pDeviceStatus = new TDToolbar(":/img/index/switch_open.png",":/img/index/switch_close.png",this);
	m_pDeviceStatus->setObjectName("subButton");
	m_pDeviceStatus->setChecked(true);
	//	connect(m_pDeviceStatus,SIGNAL(clicked()),this,SLOT(slot_changeStatus()));

	//添加的时候,不添加通道设置了,用默认方式初始化
	//	m_pChannelConfigBtn = new QPushButton("通道设置",this);
	//	m_pChannelConfigBtn->setObjectName("subButton");
	//	connect(m_pChannelConfigBtn,SIGNAL(clicked(bool)),this,SLOT(slot_channelSlots()));

	h10->addWidget(label10);
	h10->addStretch();
	h10->addWidget(m_pDeviceStatus);
	h10->addStretch();
	//	h10->addWidget(m_pChannelConfigBtn);
	this->m_pArticleVLayout->addLayout(h10);

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
	}";
	this->setStyleSheet(stylesheet);

}

AddUnitModal::~AddUnitModal()
{

}

void AddUnitModal::initTypeMap()
{
	if(s_mapTypes.isEmpty()){
		s_mapTypes.insert(0,"内同步");
		s_mapTypes.insert(1,"PT同步");
		s_mapTypes.insert(2,"工频同步");
		s_mapTypes.insert(3,"外界调频同步");
	}
}

//void AddUnitModal::slot_channelSlots()
//{
//	//通道设置
//	m_iId = 1;
//}

void AddUnitModal::slot_okBtnClicked()
{
	//ok按钮被点击
	//执行添加的逻辑,注意通道设置被默认初始化
	if(-1 == m_iId){
		//执行添加逻辑
		Ied t_ied;
		t_ied.name = m_pUnitNameEdit->text();
		t_ied.channelNum = m_pChannelNumberCombo->currentText().toInt();
		t_ied.sn = m_pDeviceNoEdit->text();
		t_ied.ip = m_pIPEdit->text();
		t_ied.port = m_pPortEdit->text().toInt();
		t_ied.syncType = m_pSyncTypeCombo->currentIndex();
		t_ied.interSyncFreq = m_pInnserSettingEdit->text().toFloat();
		t_ied.status = m_pDeviceStatus->isChecked();
		t_ied.createTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
		t_ied.lastTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
		t_ied.isDelete = 0;
		//通道和通道状态，由数据库提供默认值
		if(Dao::getInstance()->InsertIED(t_ied)){
			TDMessageBox::information("添加成功");
			emit sig_ok();
		}else{
			TDMessageBox::warning("添加失败，请重试");
		}

	}else{
		//执行修改逻辑
		this->ied.name = m_pUnitNameEdit->text();
		this->ied.channelNum = m_pChannelNumberCombo->currentText().toInt();
		this->ied.sn = m_pDeviceNoEdit->text();
		this->ied.ip = m_pIPEdit->text();
		this->ied.port = m_pPortEdit->text().toInt();
		this->ied.syncType = m_pSyncTypeCombo->currentIndex();
		this->ied.interSyncFreq = m_pInnserSettingEdit->text().toFloat();
		this->ied.status = m_pDeviceStatus->isChecked();
		//		this->ied.createTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
		this->ied.lastTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
		//		this->ied.isDelete = 0;
		if(Dao::getInstance()->UpdateIED(this->m_iId,ied)){
			TDMessageBox::information("修改成功");
			emit sig_ok();
		}else{
			TDMessageBox::warning("修改失败，请重试");
		}

	}
}

