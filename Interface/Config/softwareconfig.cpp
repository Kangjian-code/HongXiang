/**************************************************************
 * File Name   : softwareconfig.cpp
 * Author      : ThreeDog 
 * Date        : Sun Jan 27 21:49:58 2019
 * Description : 软件配置
 *
 **************************************************************/

#include "softwareconfig.h"

SoftwareConfig::SoftwareConfig(QWidget *parent)
    :TDModal("软件配置",parent)
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
    QLabel * label1 = new QLabel("公司名称：",this);
    m_pCompanyNameEdit = new QLineEdit(this);
    m_pCompanyNameEdit->setPlaceholderText("请输入公司名称");
    m_pCompanyNameEdit->setProperty("author","ThreeDog");
    h1->addWidget(label1,2);
    h1->addWidget(m_pCompanyNameEdit,8);
    this->m_pArticleVLayout->addLayout(h1);

    QHBoxLayout * h2 = new QHBoxLayout;
    QLabel * label2 = new QLabel("版本号：",this);
    m_pVersionNumEdit = new QLineEdit(this);
    m_pVersionNumEdit->setPlaceholderText("请输入版本号");
    m_pVersionNumEdit->setProperty("author","ThreeDog");
    h2->addWidget(label2,2);
    h2->addWidget(m_pVersionNumEdit,8);
    this->m_pArticleVLayout->addLayout(h2);

    QHBoxLayout * h3 = new QHBoxLayout;
    QLabel * label3 = new QLabel("软件名称:",this);
    m_pSoftwareNameEdit = new QLineEdit(this);
    m_pSoftwareNameEdit->setProperty("author","ThreeDog");
    m_pSoftwareNameEdit->setPlaceholderText("请输入软件名称");
    h3->addWidget(label3,2);
    h3->addWidget(m_pSoftwareNameEdit,8);
    this->m_pArticleVLayout->addLayout(h3);

    QHBoxLayout * h4 = new QHBoxLayout;
    QLabel * label4 = new QLabel("公司简介:",this);
    m_pCompanyIntroduceText = new QTextEdit(this);
    m_pCompanyIntroduceText->setPlaceholderText("请输入公司简介");
    m_pCompanyIntroduceText->setProperty("author","ThreeDog");
    m_pCompanyIntroduceText->setFixedHeight(72);
    h4->addWidget(label4,2);
    h4->addWidget(m_pCompanyIntroduceText,8);
    this->m_pArticleVLayout->addLayout(h4);

    QHBoxLayout * h5 = new QHBoxLayout;
    QLabel * label5 = new QLabel("LOGO图片（60px*60px，jpg,png）",this);
    m_pChoicePicBtn = new QPushButton("选择图片",this);
    m_pChoicePicBtn->setObjectName("subButton");
    connect(m_pChoicePicBtn,SIGNAL(clicked(bool)),this,SLOT(slot_choicePic()));
    h5->addWidget(label5);
    h5->addStretch();
    h5->addWidget(m_pChoicePicBtn);
    this->m_pArticleVLayout->addLayout(h5);

    QHBoxLayout * h6 = new QHBoxLayout;
    QWidget * w = new QWidget(this);
    h6->addStretch(2);
    h6->addWidget(w,1);
    h6->addStretch(7);
    w->setStyleSheet("border-radius:2px ; border:1px solid #DFDFDF;width:65px;height:65px");
    w->setFixedSize(100,100);
    QHBoxLayout * hh = new QHBoxLayout;
    w->setLayout(hh);
    m_pPicLabel = new QLabel(this);
    hh->addWidget(m_pPicLabel);

    this->m_pArticleVLayout->addLayout(h6);
    this->m_pArticleVLayout->setSpacing(20);
    this->m_pArticleVLayout->addStretch();

    this->setButtonText("返回","保存");
    this->m_pOKBtn->setStyleSheet("width:145px;");
    this->m_pCancleBtn->setStyleSheet("width:145px;");
    connect(m_pOKBtn,SIGNAL(clicked()),this,SLOT(slot_okBtnClicked()));

    id = 0;
    updateSoftwareConfig();

}

void SoftwareConfig::updateSoftwareConfig()
{
    QSqlQuery query;
    query.exec(QString("select * from hxdl.software where id = %1;").arg(Dao::getInstance()->getId()));
    while(query.next()){
        id = query.value("id").toInt();
        this->m_pCompanyNameEdit->setText(query.value("company").toString());
        this->m_pSoftwareNameEdit->setText(query.value("name").toString());
        //this->m_pPicLabel->setPixmap("");//图片
        this->m_pCompanyIntroduceText->setText(query.value("desc").toString());
        this->m_pVersionNumEdit->setText(query.value("swRev").toString());
    }
}

void SoftwareConfig::slot_choicePic()
{
    //加载图片
    QString picPath = QFileDialog::getOpenFileName(this,"选择图片",QDir::homePath(),"Images (*.png *.xpm *.jpg)");
    QPixmap pic;
    pic.load(picPath);
    pic = pic.scaled(this->m_pPicLabel->size(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    this->m_pPicLabel->setPixmap(pic);
}

void SoftwareConfig::slot_okBtnClicked()
{
    emit okBtnClicked();
    //信息存入数据库
    Software software;
    software.id = Dao::getInstance()->getId();
    software.company = this->m_pCompanyNameEdit->text();
    software.swRev = this->m_pVersionNumEdit->text();
    software.name = this->m_pSoftwareNameEdit->text();
    software.desc = this->m_pCompanyIntroduceText->toPlainText();
    software.logo = "http://106.12.204.181/logo.png";
    //将数据插入或者将数据更新
    if(Dao::getInstance()->InsertOrUpdateSoftware(software)){
        TDMessageBox::information("保存成功");
    }else{
        TDMessageBox::warning("保存失败");
    }
}

SoftwareConfig::~SoftwareConfig()
{

}


