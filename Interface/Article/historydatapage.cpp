/**************************************************************
 * File Name   : historydatapage.cpp
 * Author      : ThreeDog
 * Date        : Fri Jan 11 22:29:01 2019
 * Description : 历史数据
 *
 **************************************************************/
#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#include "historydatapage.h"
#include "ui_historydatapage.h"

HistoryDataPage::HistoryDataPage(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::HistoryDataPage)
{
	ui->setupUi(this);
	initLeftTabs();
}

void HistoryDataPage::initLeftTabs()
{
	m_pHideLeftBtn = new TDToolbar(":/img/index/left_open.png",":/img/index/left_close.png",this);
	m_pHideLeftBtn->move(154,472);
    connect(m_pHideLeftBtn,SIGNAL(clicked()),this,SLOT(hideLeft()));
//	m_pHideLeftBtn->setCallback(this,my_selector(hideLeft));
}

//点击隐藏左侧栏的按钮触发
void HistoryDataPage::hideLeft()
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

HistoryDataPage::~HistoryDataPage()
{
	delete ui;
}


