/**************************************************************
 * File Name   : siteconfig.cpp
 * Author      : ThreeDog
 * Date        : Sat Jan 26 22:37:22 2019
 * Description : 站点配置页面
 *
 **************************************************************/

#include "siteconfig.h"

SiteConfig::SiteConfig(QWidget *parent)
    :TDModal("站点配置",parent)
{
    this->resize(610,773);
    //站点名称一行
    QHBoxLayout * h1 = new QHBoxLayout;
    QLabel * label1 = new QLabel("* 名称",this);
    m_pNameEdit = new QLineEdit(this);
    m_pNameEdit->setPlaceholderText("请输入站点名称");
    m_pNameEdit->setProperty("author","ThreeDog");
    h1->addWidget(label1,2);
    h1->addWidget(m_pNameEdit,8);
    this->m_pArticleVLayout->addLayout(h1);

    //电压等级一行
    QHBoxLayout * h2 = new QHBoxLayout;
    QLabel * label2 = new QLabel("* 电压等级",this);
    m_pVoltageCombo = new QComboBox(this);
    m_pVoltageCombo->setProperty("author","ThreeDog");
    m_pVoltageCombo->addItem("500KV");
    m_pVoltageCombo->addItem("1000KV");
    m_pVoltageCombo->addItem("1500KV");
    m_pVoltageCombo->addItem("2000KV");
    h2->addWidget(label2,2);
    h2->addWidget(m_pVoltageCombo,2);
    h2->addStretch(6);
    this->m_pArticleVLayout->addLayout(h2);

    //IP地址一行
    QHBoxLayout * h3 = new QHBoxLayout;
    QLabel * label3 = new QLabel("* IP地址",this);
    m_pIPEdit = new QLineEdit(this);
    m_pIPEdit->setProperty("author","ThreeDog");
    m_pIPEdit->setPlaceholderText("请输入IP地址");
    h3->addWidget(label3,2);
    h3->addWidget(m_pIPEdit,8);
    this->m_pArticleVLayout->addLayout(h3);

    //端口号一行
    QHBoxLayout * h4 = new QHBoxLayout;
    QLabel * label4 = new QLabel("* 端口号",this);
    m_pPortEdit = new QLineEdit(this);
    m_pPortEdit->setProperty("author","ThreeDog");
    m_pPortEdit->setPlaceholderText("请输入端口号");
    h4->addWidget(label4,2);
    h4->addWidget(m_pPortEdit,8);
    this->m_pArticleVLayout->addLayout(h4);

    //站点概况一行
    QHBoxLayout * h5 = new QHBoxLayout;
    QLabel * label5 = new QLabel("  站点概况",this);
    m_pSiteText = new QTextEdit(this);
    m_pSiteText->setProperty("author","ThreeDog");
    m_pSiteText->setPlaceholderText("请输入站点概况");
    m_pSiteText->setMaximumHeight(72);
    h5->addWidget(label5,2);
    h5->addWidget(m_pSiteText,8);
    this->m_pArticleVLayout->addLayout(h5);

    //站点图片文字&按钮
    QHBoxLayout * h6 = new QHBoxLayout;
    QLabel * label6 = new QLabel("* 站点图片（1660px*830px，jpg,png）",this);
    m_pChoicePicBtn = new QPushButton("选择图片",this);
    m_pChoicePicBtn->setObjectName("subButton");
    connect(m_pChoicePicBtn,SIGNAL(clicked(bool)),this,SLOT(slot_addPic()));
    h6->addWidget(label6);
    h6->addStretch();
    h6->addWidget(m_pChoicePicBtn);
    this->m_pArticleVLayout->addLayout(h6);

    //最下面显示图片的区域
    QHBoxLayout * h7 = new QHBoxLayout;
    m_pPicWidget = new QWidget(this);
    h7->addStretch(2);
    h7->addWidget(m_pPicWidget,8);
    m_pPicWidget->setStyleSheet("border-radius:2px ; border:1px solid #DFDFDF;width:440px;height:220px");
    //在窗体中加一个label用于显示图片
    QHBoxLayout * hh = new QHBoxLayout;
    m_pPicWidget->setLayout(hh);
    hh->setMargin(3);
    m_pPicLabel = new QLabel(this);
    m_pPicLabel->setStyleSheet(" border:none;");
    hh->addWidget(m_pPicLabel);

    this->m_pArticleVLayout->addLayout(h7);
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

    id = 0;
    updateSiteConfig();
}

void SiteConfig::updateSiteConfig()
{
    QSqlQuery query;
    query.exec(QString("select * from hxdl.site where id = %1;").arg(Dao::getInstance()->getId()));
    while(query.next()){
        id = query.value("id").toInt();
        this->m_pNameEdit->setText(query.value("name").toString());
        this->m_pSiteText->setText(query.value("intro").toString());
        this->m_sPicPath = query.value("layoutPictureURL").toString();
        this->m_pVoltageCombo->setCurrentText(query.value("level").toString());
        this->m_pIPEdit->setText(query.value("ip").toString());
        this->m_pPortEdit->setText(query.value("dbPort").toString());
//        this->m_fileViewPort = 80;
//        this->m_pfileUploadPort = 80;
    }
}

SiteConfig::~SiteConfig()
{

}

void SiteConfig::slot_okBtnClicked()
{
    //保存设置
    emit okBtnClicked();
    //信息存入数据库
    Site site;
    site.id = Dao::getInstance()->getId();
    site.name = this->m_pNameEdit->text();
    site.intro = this->m_pSiteText->toPlainText();
    site.ip = this->m_pIPEdit->text();
    site.dbPort = this->m_pPortEdit->text().toInt();
    site.lastTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    site.createTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    site.fileUploadPort = 80;
    site.fileViewPort = 80;
    site.level = this->m_pVoltageCombo->currentText();
    site.layoutPictureURL = "http://106.12.204.181/site.png";

    //将数据插入或者将数据更新
    if(Dao::getInstance()->InsertOrUpdateSite(site)){
        TDMessageBox::information("保存成功");
    }else{
        TDMessageBox::warning("保存失败");
    }
}

void SiteConfig::slot_addPic()
{
    //加载图片
    QString picPath = QFileDialog::getOpenFileName(this,"选择图片",QDir::homePath(),"Images (*.png *.xpm *.jpg)");
    QPixmap pic;
    pic.load(picPath);
    pic = pic.scaled(this->m_pPicLabel->size(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    this->m_pPicLabel->setPixmap(pic);
}
