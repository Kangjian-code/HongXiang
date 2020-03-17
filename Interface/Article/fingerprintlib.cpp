/**************************************************************
 * File Name   : fingerprintlib.cpp
 * Author      : ThreeDog
 * Date        : Fri Jan 11 22:29:01 2019
 * Description : 指纹库
 *
 **************************************************************/
#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#include "fingerprintlib.h"
#include "ui_fingerprintlib.h"

FingerprintLib::FingerprintLib(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FingerprintLib)
{
    ui->setupUi(this);
    initLeftTabs();
}

void FingerprintLib::initLeftTabs()
{
    m_pHideLeftBtn = new TDToolbar(":/img/index/left_open.png",":/img/index/left_close.png",this);
    m_pHideLeftBtn->move(154,472);
    connect(m_pHideLeftBtn,SIGNAL(clicked()),this,SLOT(hideLeft()));
//    m_pHideLeftBtn->setCallback(this,my_selector(hideLeft));
}

//点击隐藏左侧栏的按钮触发
void FingerprintLib::hideLeft()
{
    //显示
    if(ui->leftWidget->isHidden()){
        ui->leftWidget->show();
        m_pHideLeftBtn->move(154,472);
        m_pHideLeftBtn->raise();
    }else{
    //隐藏
        ui->leftWidget->hide();
        m_pHideLeftBtn->move(8,472);
        m_pHideLeftBtn->raise();
    }

}

FingerprintLib::~FingerprintLib()
{
    delete ui;
}
