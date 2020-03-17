#include "tableoperateitem.h"
#include "ui_tableoperateitem.h"

TableOperateItem::TableOperateItem(int id, QWidget *parent) :
	QWidget(parent),
	ui(new Ui::TableOperateItem)
{
	ui->setupUi(this);
	this->m_iId = id;
	TDPushButton * btn = new TDPushButton(":/img/index/delete.png",":/img/index/delete.png",":/img/index/delete.png",this);
//    btn->setAutoMask();
	this->ui->horizontalLayout->addWidget(btn,1);
	ui->pushButton->setObjectName("subButton");
	ui->pushButton_2->setObjectName("subButton");
	ui->pushButton_3->setObjectName("subButton");
//    btn->setCallback(this,my_selector(deleteBtnClicked));
	connect(btn,SIGNAL(clicked()),this,SLOT(deleteBtnClicked()));
}

TableOperateItem::~TableOperateItem()
{
	delete ui;
}

void TableOperateItem::on_pushButton_clicked()
{
	emit channelConfig(m_iId);
}

void TableOperateItem::on_pushButton_2_clicked()
{
	emit download(m_iId);
}

void TableOperateItem::deleteBtnClicked()
{
	emit deleteRow(m_iId);
}

void TableOperateItem::on_pushButton_3_clicked()
{
	emit alterIed(m_iId);
}
