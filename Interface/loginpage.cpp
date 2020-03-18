/**************************************************************
 * File Name   : loginpage.cpp
 * Author      : ThreeDog 
 * Date        : Thu Jan 03 20:25:45 2019
 * Description : 登录页面
 *
 **************************************************************/
#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#include "loginpage.h"

LoginPage::LoginPage(QWidget *parent)
    :TDWidget(":/img/login_bg.png",parent)
{
    this->setMoveEnable(false);
    //用户名、密码输入框
    m_pNameEdit = new QLineEdit(this);
    m_pNameEdit->setPlaceholderText("请输入账号");
    m_pNameEdit->move(775,466);
    //无边框且透明
    m_pNameEdit->setStyleSheet("font-size:22px;background:transparent;border-width:0;border-style:outset");
    m_pPsdEdit = new QLineEdit(this);
    m_pPsdEdit->setEchoMode(QLineEdit::Password);
    m_pPsdEdit->setPlaceholderText("请输入密码");
    m_pPsdEdit->move(775,561);
    m_pPsdEdit->setStyleSheet("font-size:22px;background:transparent;border-width:0;border-style:outset");
    //显示密码的小图标
    m_pShowPsdBtn = new TDToolbar(":/img/show_psd2.png",":/img/show_psd.png",this);
    m_pShowPsdBtn->move(1147,568);
    connect(m_pShowPsdBtn,SIGNAL(clicked()),this,SLOT(showPsdClicked()));
//    m_pShowPsdBtn->setCallback(this,my_selector(showPsdClicked));

    //记住密码checkbox
    //TDCheckbox
    m_pRemenberPsw = new QCheckBox("记住密码",this);
    m_pRemenberPsw->setStyleSheet("font-size:18px");
    m_pRemenberPsw->move(720,630);

    //登录按钮
    m_pLoginBtn = new TDPushButton(":/img/login_normal.png",":/img/login_hover.png",":/img/login_normal.png",this);
    m_pLoginBtn->move(700,720);
    connect(m_pLoginBtn,SIGNAL(clicked()),this,SLOT(loginBtnClicked()));
//    m_pLoginBtn->setCallback(this,my_selector(loginBtnClicked));

    //版权信息文字
    //帮助按钮
    m_pCopyrightLabel = new QLabel(this);
    m_pHelpLabel = new QLabel(this);
    QPalette p;
    p.setColor(QPalette::WindowText,Qt::white);
    QFont font;
    font.setFamily("Microsoft Yahei");
    font.setPixelSize(20);
    m_pCopyrightLabel->setPalette(p);
    m_pCopyrightLabel->setStyleSheet("color:#ffffff");
    m_pCopyrightLabel->setFont(font);
    m_pCopyrightLabel->setText("© 2018-2019 红相股份有限公司 版权所有");
    m_pHelpLabel->setPalette(p);
    m_pHelpLabel->setFont(font);
    m_pHelpLabel->setStyleSheet("color:#ffffff");
    m_pHelpLabel->setText("帮助手册");
    m_pCopyrightLabel->move(774,1022);
    m_pHelpLabel->move(1782,1022);
}

//点击登录
void LoginPage::loginBtnClicked()
{
    qDebug()<<"name:" << m_pNameEdit->text();
    qDebug()<<"pass:" << m_pPsdEdit->text();
    if(m_pNameEdit->text() == "admin" && m_pPsdEdit->text() == "admin"){
        emit LoginSuccess();
    }
}

//显示密码
void LoginPage::showPsdClicked()
{
    if(m_pShowPsdBtn->isChecked()){
        this->m_pPsdEdit->setEchoMode(QLineEdit::Normal);
    }else{
        this->m_pPsdEdit->setEchoMode(QLineEdit::Password);
    }
}

LoginPage::~LoginPage()
{

}
