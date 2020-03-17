/**************************************************************
 * File Name   : channelconfig.cpp
 * Author      : ThreeDog
 * Date        : Fri Jan 25 22:10:03 2019
 * Description : 通道配置、
 *
 **************************************************************/

#include "channelconfig.h"

ChannelConfig::ChannelConfig(int no, QWidget *parent)
	:TDModal("通道设置",parent)
{
	this->setModal(true);
	this->resize(485,570);
	this->setButtonText("返回","保存");
	this->ied = Dao::getInstance()->GetIEDById(no);
	initTable();
	updateTable();
	disconnect(this->m_pOKBtn,SIGNAL(clicked(bool)),this,SLOT(close()));
	connect(this->m_pOKBtn,SIGNAL(clicked(bool)),this,SLOT(slot_okBtnClicked()));
}

void ChannelConfig::initTable()
{
	//初始化表格
	m_pTableWidget = new QTableWidget(this);
	m_pTableWidget->setMinimumHeight(360);
	this->m_pArticleVLayout->addWidget(m_pTableWidget);

	m_pTableWidget->setColumnCount(3);
	m_pTableWidget->setColumnWidth(0, 160 );
	m_pTableWidget->setColumnWidth(1, 140);
	m_pTableWidget->setColumnWidth(2, 100 );
	m_pTableWidget->verticalHeader()->setDefaultSectionSize(40);
	m_pTableWidget->verticalHeader()->setStyleSheet("min-height:40px;");

	QStringList headText;
	headText << "通道编号" << "通道类型"<< "通道状态";
	m_pTableWidget->setHorizontalHeaderLabels(headText);
	m_pTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
	m_pTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
	m_pTableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
	m_pTableWidget->setAlternatingRowColors(true);
	m_pTableWidget->verticalHeader()->setVisible(false);
	m_pTableWidget->horizontalHeader()->setStretchLastSection(true);
}

void ChannelConfig::updateTable()
{
	int count = ied.channelNum;
	m_pTableWidget->setRowCount(count);
	for(int i = 0; i < count; i++){
		m_pTableWidget->setRowHeight(i, 40);
		//第一列
		QTableWidgetItem *item1 = new QTableWidgetItem(QString("通道%1").arg(i+1));
		item1->setTextAlignment(Qt::AlignCenter);
		m_pTableWidget->setItem(i, 0, item1);
		//第二列 除了第8列为表格添加下拉框

		QWidget * w = new QWidget(this);
		QHBoxLayout * h = new QHBoxLayout;
		h->setContentsMargins(20,3,20,3);
		w->setLayout(h);
		QComboBox * combo = new QComboBox(this);
		combo->setProperty("author","ThreeDog");
		combo->setProperty("row",i);
		combo->addItem("UHF");
		combo->addItem("噪声通道");
		combo->addItem("振动通道");
		h->addWidget(combo);
		this->m_pTableWidget->setCellWidget(i,1,w);

		//第三列
		QWidget * w3 = new QWidget(this);
		QHBoxLayout * h3 = new QHBoxLayout;
		h3->setContentsMargins(20,3,20,3);

		w3->setLayout(h3);

		TDToolbar * t = new TDToolbar(":/img/index/switch_open.png",":/img/index/switch_close.png",this);
		t->setProperty("row",i);
		h3->addWidget(t);

		this->m_pTableWidget->setCellWidget(i,2,w3);

		//根据数据库内容对设置进行初始化
		//没想下更好的办法，只能switch case了
		switch (i) {
		case 0:
			combo->setCurrentIndex(ied.channel1);
			t->setChecked((bool)ied.channel1Status);
		break;
		case 1:
			combo->setCurrentIndex(ied.channel2);
			t->setChecked((bool)ied.channel2Status);
		break;
		case 2:
			combo->setCurrentIndex(ied.channel3);
			t->setChecked((bool)ied.channel3Status);
		break;
		case 3:
			combo->setCurrentIndex(ied.channel4);
			t->setChecked((bool)ied.channel4Status);
		break;
		case 4:
			combo->setCurrentIndex(ied.channel5);
			t->setChecked((bool)ied.channel5Status);
		break;
		case 5:
			combo->setCurrentIndex(ied.channel6);
			t->setChecked((bool)ied.channel6Status);
		break;
		case 6:
			combo->setCurrentIndex(ied.channel7);
			t->setChecked((bool)ied.channel7Status);
		break;
		case 7:
			combo->setCurrentIndex(ied.channel8);
			t->setChecked((bool)ied.channel8Status);
		break;
		}
	}
}

ChannelConfig::~ChannelConfig()
{

}

QComboBox *  ChannelConfig::getComboBox(int row){
	for(QComboBox * combo : m_pTableWidget->findChildren<QComboBox *>()){
		if(combo->property("row") == row)
			return combo;
	}
	return nullptr;
}

TDToolbar * ChannelConfig::getToolbar(int row){
	for(TDToolbar * tool : m_pTableWidget->findChildren<TDToolbar *>()){
		if(tool->property("row") == row)
			return tool;
	}
	return nullptr;
}

void ChannelConfig::slot_okBtnClicked()
{
	//将设置通道设置保存到数据库
	for(auto * combo : m_pTableWidget->findChildren<QComboBox *>()){
		qDebug()<< combo->currentText();
	}
	QVector<QVector<int>> vect;
	for(int i = 0; i < this->m_pTableWidget->rowCount(); i++){
		QVector<int> t;
		t.append(this->getComboBox(i)->currentIndex());
		t.append((int)this->getToolbar(i)->isChecked());
		vect.append(t);
	}
	if(Dao::getInstance()->UpdateChannels(this->ied.id,vect)){
		TDMessageBox::information("修改成功");
		this->close();
	}else{
		TDMessageBox::question("修改失败，请重试");
	}
}
