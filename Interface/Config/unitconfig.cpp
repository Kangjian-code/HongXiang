/**************************************************************
 * File Name   : unitconfig.cpp
 * Author      : ThreeDog
 * Date        : Thu Jan 24 20:48:03 2019
 * Description : 单元配置，继承自TDModal模态框实现
 *
 **************************************************************/

#include "unitconfig.h"

UnitConfig::UnitConfig(QWidget *parent)
	:TDModal("单元配置",parent)
{
	this->resize(1460,635);
	this->setButtonText("保存","返回");
	//添加下侧的几个按钮
	m_pImportBtn = new QPushButton("导入",this);
	m_pExportBtn = new QPushButton("导出",this);
	m_pAddBtn = new QPushButton("添加",this);
	this->m_pFooterHLayout->insertWidget(2,m_pAddBtn);
	this->m_pFooterHLayout->insertWidget(2,m_pExportBtn);
	this->m_pFooterHLayout->insertWidget(2,m_pImportBtn);

	connect(m_pAddBtn,SIGNAL(clicked(bool)),this,SLOT(add()));
	connect(m_pImportBtn,SIGNAL(clicked(bool)),this,SLOT(importConfig()));
	connect(m_pExportBtn,SIGNAL(clicked(bool)),this,SLOT(exportConfig()));
	m_pTableWidget = nullptr;
	initTable();
}

void UnitConfig::initTable()
{
	//初始化表格
	if (m_pTableWidget == nullptr){
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
		m_pTableWidget->verticalHeader()->setDefaultSectionSize(40);
		m_pTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
		m_pTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
		m_pTableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
		m_pTableWidget->setAlternatingRowColors(true);
		m_pTableWidget->verticalHeader()->setVisible(false);
		m_pTableWidget->horizontalHeader()->setStretchLastSection(true);

	}
	QStringList headText;
	headText << "单元名称" << "设备编号"<< "IP地址" << "端口" << "通道数量" << "同步方式" << "内同步设置" << "设备状态" << "操作";
	m_pTableWidget->setHorizontalHeaderLabels(headText);

	updateTable();
}

void UnitConfig::updateTable()
{
	m_pTableWidget->setRowCount(0);
	m_pTableWidget->clearContents();
	QVector<Ied> vect = Dao::getInstance()->QueryIed();
	for(Ied ied : vect){
		int row = this->m_pTableWidget->rowCount(); //获取行数
		this->m_pTableWidget->insertRow(row);
		//第一列 单元名称
		QTableWidgetItem *item1 = new QTableWidgetItem(ied.name);
		item1->setTextAlignment(Qt::AlignCenter);
		m_pTableWidget->setItem(row, 0, item1);

		//第二列 设备编号
		QTableWidgetItem *item2 = new QTableWidgetItem(ied.sn);
		item2->setTextAlignment(Qt::AlignCenter);
		m_pTableWidget->setItem(row, 1, item2);

		//第三列 IP地址
		QTableWidgetItem *item3 = new QTableWidgetItem(ied.ip);
		item3->setTextAlignment(Qt::AlignCenter);
		m_pTableWidget->setItem(row, 2, item3);

		//第四列 端口号
		QTableWidgetItem *item4 = new QTableWidgetItem(QString::number(ied.port));
		item4->setTextAlignment(Qt::AlignCenter);
		m_pTableWidget->setItem(row, 3, item4);

		//第五列 通道数量
		QTableWidgetItem *item5 = new QTableWidgetItem(QString::number(ied.channelNum));
		item5->setTextAlignment(Qt::AlignCenter);
		m_pTableWidget->setItem(row, 4, item5);

		//第六列 同步方式
		if(AddUnitModal::s_mapTypes.isEmpty())
			AddUnitModal::initTypeMap();
		QTableWidgetItem *item6 = new QTableWidgetItem(AddUnitModal::s_mapTypes.value(ied.syncType));
		item6->setTextAlignment(Qt::AlignCenter);
		m_pTableWidget->setItem(row, 5, item6);

		//第七列 内同步设置
		QTableWidgetItem *item7 = new QTableWidgetItem(QString::number(ied.interSyncFreq));
		item7->setTextAlignment(Qt::AlignCenter);
		m_pTableWidget->setItem(row, 6, item7);

		//第八列 设备状态
		QWidget * w3 = new QWidget(this);
		QHBoxLayout * h3 = new QHBoxLayout;
		h3->setContentsMargins(20,3,20,3);
		w3->setLayout(h3);
		TDToolbar * t = new TDToolbar(":/img/index/switch_open.png",":/img/index/switch_close.png",this);
		t->setMouseChangeEnable(false);//不允许在表格中修改状态
		h3->addWidget(t);
		t->setChecked((bool)ied.status);
		this->m_pTableWidget->setCellWidget(row,7,w3);

		//第九列 操作
		TableOperateItem * toitem = new TableOperateItem(ied.id,this);
		connect(toitem,SIGNAL(alterIed(int)),this,SLOT(slot_alterIed(int)));
		connect(toitem,SIGNAL(channelConfig(int)),this,SLOT(channelConfig(int)));
		connect(toitem,SIGNAL(download(int)),this,SLOT(downLoad(int)));
		connect(toitem,SIGNAL(deleteRow(int)),this,SLOT(slot_deleteIed(int)));

		this->m_pTableWidget->setCellWidget(row,8,toitem);
	}
}

void UnitConfig::addCellWidget(int row, int col,const QString text)
{
	QWidget * w = new QWidget(this);
	QHBoxLayout * h = new QHBoxLayout;
	h->setContentsMargins(20,3,20,3);
	w->setLayout(h);
	QLineEdit * edit = new QLineEdit(this);
	edit->setObjectName(QString("line%1%2").arg(row,col));
	edit->setPlaceholderText(QString("请输入%1").arg(text));
	edit->setStyleSheet("background:transparent;border-width:0;border-style:outset");
	h->addWidget(edit);
	this->m_pTableWidget->setCellWidget(row,col,w);
}

UnitConfig::~UnitConfig()
{

}

void UnitConfig::importConfig()
{

}

void UnitConfig::exportConfig()
{

}

void UnitConfig::channelConfig(int row)
{
	ChannelConfig * cc = new ChannelConfig(row);
	cc->show();
}

void UnitConfig::downLoad(int id)
{
	//	QLineEdit* edit = m_pTableWidget->findChild<QLineEdit *>(QString("line%1%2").arg(row,0));
	//  qDebug()<<((QLineEdit *)m_pTableWidget->cellWidget(row,0))->text();
	QString text = Dao::getInstance()->GetIEDById(id).name;

	int res = TDMessageBox::question(QString("是否将 %1 的通道设置下放？").arg(text));
	if(res == QMessageBox::Yes){
		TDMessageBox::information("下放成功");
	}else if (res == QMessageBox::No){

	}
}

void UnitConfig::slot_deleteIed(const int &id)
{
	int res  = TDMessageBox::question("删除后会将此单元关联的所有监测点也全部删除，确定要删除吗？");
	if(res == QMessageBox::Yes){
		if(Dao::getInstance()->DeleteIED(id)){
			TDMessageBox::information("删除成功");
			this->updateTable();
		}else{
			TDMessageBox::warning("删除失败，请重试");
		}
	}else{

	}
}

void UnitConfig::slot_alterIed(const int &id)
{
	Ied ied = Dao::getInstance()->GetIEDById(id);
	AddUnitModal * aum = new AddUnitModal(ied);
	connect(aum,SIGNAL(sig_ok()),this,SLOT(updateTable()));
	aum->show();
}

//添加
void UnitConfig::add()
{
	//	TestForm * test = new TestForm();
	//	test->show();
	AddUnitModal * aum = new AddUnitModal();
	connect(aum,SIGNAL(sig_ok()),this,SLOT(updateTable()));
	aum->show();
	/* 2019-05-20 原先的逻辑全部注释
	//每次点击添加按钮，就添加一行内容，每一行内容全是LienEdit，可以由用户设置和修改
	int row = this->m_pTableWidget->rowCount(); //获取行数
	this->m_pTableWidget->insertRow(row);
	//第一列 单元名称
	this->addCellWidget(row,0,"单元名称");

	//第二列 设备编号
	this->addCellWidget(row,1,"设备编号");

	//第三列 IP地址
	this->addCellWidget(row,2,"IP地址");

	//第四列 端口号
	this->addCellWidget(row,3,"端口号");

	//第五列 通道数量
	this->addCellWidget(row,4,"通道数量");

	//第六列 同步方式
	QWidget * w = new QWidget(this);
	QHBoxLayout * h = new QHBoxLayout;
	h->setContentsMargins(20,3,20,3);
	w->setLayout(h);
	QComboBox * combo = new QComboBox(this);
	combo->setProperty("author","ThreeDog");
	combo->setProperty("row",row);
	combo->addItem("内同步");
	combo->addItem("PT同步");
	combo->addItem("工频同步");
	combo->addItem("外接调频同步");
	combo->setCurrentIndex(0);
	connect(combo,SIGNAL(currentTextChanged(QString)),this,SLOT(comboChange(QString)));
		//关联下拉框文字改变的事件，同步方式为内同步时，后面的LineEdit才可用
	h->addWidget(combo);
	this->m_pTableWidget->setCellWidget(row,5,w);

	//第七列 内同步设置
	QWidget * w2 = new QWidget(this);
	QHBoxLayout * h2 = new QHBoxLayout;
	h2->setContentsMargins(20,3,20,3);
	w2->setLayout(h2);
	m_pInnerSyncConfigEdit = new QLineEdit(this);
	m_pInnerSyncConfigEdit->setProperty("author","ThreeDog");
	m_pInnerSyncConfigEdit->setEnabled(true);
	h2->addWidget(m_pInnerSyncConfigEdit,8);
	QLabel *l = new QLabel("Hz",this);
	l->setStyleSheet("font-size:14px");
	h2->addWidget(l,2);
	this->m_pTableWidget->setCellWidget(row,6,w2);

	//第八列 设备状态
	QWidget * w3 = new QWidget(this);
	QHBoxLayout * h3 = new QHBoxLayout;
	h3->setContentsMargins(20,3,20,3);
	w3->setLayout(h3);
	TDToolbar * t = new TDToolbar(":/img/index/switch_open.png",":/img/index/switch_close.png",this);
	h3->addWidget(t);
	this->m_pTableWidget->setCellWidget(row,7,w3);

	//第九列 操作
	TableOperateItem * toitem = new TableOperateItem(row,this);
	connect(toitem,SIGNAL(channelConfig(int)),this,SLOT(channelConfig(int)));
	connect(toitem,SIGNAL(download(int)),this,SLOT(downLoad(int)));
	connect(toitem,SIGNAL(deleteRow(int)),this,SLOT(deleteRow(int)));

	this->m_pTableWidget->setCellWidget(row,8,toitem);
	*/
}

void UnitConfig::comboChange(QString text)
{
	//如果文字不是内同步，则后面的输入框不可用。
	int row = sender()->property("row").toInt();
	QLineEdit * line = (QLineEdit *)m_pTableWidget->cellWidget(row,6);

	if(text == "内同步"){
		line->setEnabled(true);
	}else{
		line->setEnabled(false);
	}

}
