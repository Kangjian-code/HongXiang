/**************************************************************
 * File Name   : configpage.cpp
 * Author      : ThreeDog 
 * Date        : Thu Jan 17 16:51:18 2019
 * Description : 配置窗体，继承自模态框，作为模板页面，需要配置页面的地方，
 * 可以参照此界面进行编写。
 *
 **************************************************************/

#include "configpage.h"

ConfigPage::ConfigPage(QWidget *parent)
    :TDModal("站点配置",parent)
{
    this->resize(610,773);
    QString stylesheet = "QLabel{\
    font-size:14px;\
    color:#262626;\
    font-family:Microsoft Yahei;\
    line-height:19px;\
    }";
    this->setStyleSheet(stylesheet);
    QHBoxLayout * h1 = new QHBoxLayout;
    QLabel * label1 = new QLabel("* 名称",this);
    QLineEdit *lineEdit1 = new QLineEdit(this);
    lineEdit1->setProperty("author","ThreeDog");
    h1->addWidget(label1,2);
    h1->addWidget(lineEdit1,8);
    this->m_pArticleVLayout->addLayout(h1);

    QHBoxLayout * h2 = new QHBoxLayout;
    QLabel * label2 = new QLabel("* 电压等级",this);
    QComboBox *combo = new QComboBox(this);
    combo->setProperty("author","ThreeDog");
    combo->addItem("500KV");
    combo->addItem("1000KV");
    combo->addItem("1500KV");
    combo->addItem("2000KV");
    h2->addWidget(label2,2);
    h2->addWidget(combo,2);
    h2->addStretch(6);
    this->m_pArticleVLayout->addLayout(h2);

    QHBoxLayout * h3 = new QHBoxLayout;
    QLabel * label3 = new QLabel("* IP地址",this);
    QLineEdit *lineEdit3 = new QLineEdit(this);
    lineEdit3->setProperty("author","ThreeDog");
    h3->addWidget(label3,2);
    h3->addWidget(lineEdit3,8);
    this->m_pArticleVLayout->addLayout(h3);

    QHBoxLayout * h4 = new QHBoxLayout;
    QLabel * label4 = new QLabel("* 端口号",this);
    QLineEdit *lineEdit4 = new QLineEdit(this);
    lineEdit4->setProperty("author","ThreeDog");
    h4->addWidget(label4,2);
    h4->addWidget(lineEdit4,8);
    this->m_pArticleVLayout->addLayout(h4);

    QHBoxLayout * h5 = new QHBoxLayout;
    QLabel * label5 = new QLabel("  站点概况",this);
    QLineEdit *lineEdit5 = new QLineEdit(this);
    lineEdit5->setProperty("author","ThreeDog");
    h5->addWidget(label5,2);
    h5->addWidget(lineEdit5,8);
    this->m_pArticleVLayout->addLayout(h5);

    QHBoxLayout * h6 = new QHBoxLayout;
    QLabel * label6 = new QLabel("* 站点图片（1660px*830px，jpg,png）",this);
    QPushButton *btn = new QPushButton("选择图片",this);
    btn->setObjectName("subButton");
    h6->addWidget(label6);
    h6->addStretch();
    h6->addWidget(btn);
    this->m_pArticleVLayout->addLayout(h6);

    QHBoxLayout * h7 = new QHBoxLayout;
    QWidget * w = new QWidget(this);
    h7->addStretch(2);
    h7->addWidget(w,8);
    w->setStyleSheet("border-radius:2px ; border:1px solid #DFDFDF;width:440px;height:220px");
    this->m_pArticleVLayout->addLayout(h7);
    this->m_pArticleVLayout->setSpacing(20);

    this->setButtonText("返回","保存");
    this->m_pOKBtn->setStyleSheet("width:145px;");
    this->m_pCancleBtn->setStyleSheet("width:145px;");
}

ConfigPage::~ConfigPage()
{

}
