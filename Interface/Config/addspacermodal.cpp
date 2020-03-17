/**************************************************************
 * File Name   : addspacermodal.cpp
 * Author      : ThreeDog 
 * Date        : Sat Mar 02 22:18:26 2019
 * Description : 新增间隔点
 *
 **************************************************************/

#include "addspacermodal.h"

AddSpacerModal::AddSpacerModal(QWidget *parent)
    :TDModal("新增间隔",parent)
{
    initInterface();
}

AddSpacerModal::AddSpacerModal(Spacing spacing, QWidget *parent)
    :TDModal("修改间隔",parent)
{
    initInterface();
    this->m_iId = spacing.id;
    this->m_pNameEdit->setText(spacing.name);
    this->m_pDescEdit->setText(spacing.desc);
    this->m_pMakerEdit->setText(spacing.producer);
    this->m_pProduceDate->setDate(QDate::fromString(spacing.manDate,"yyyy-MM-dd"));
    qDebug()<<spacing.runDate;
    this->m_pRunDate->setDate(QDate::fromString(spacing.runDate,"yyyy-MM-dd"));
    //从远程服务器获取图片
    /*
    QPixmap pic = getImage(spacing.pictureURL);
    m_pPicLabel->setPixmap(pic);
    */
}

void AddSpacerModal::initInterface()
{
    this->m_iId = -1;
    this->resize(610,773);
    //间隔名称一行
    QHBoxLayout * h1 = new QHBoxLayout;
    QLabel * label1 = new QLabel("间隔名称",this);
    m_pNameEdit = new QLineEdit(this);
    m_pNameEdit->setPlaceholderText("请输入间隔名称");
    m_pNameEdit->setProperty("author","ThreeDog");
    h1->addWidget(label1,2);
    h1->addWidget(m_pNameEdit,8);
    this->m_pArticleVLayout->addLayout(h1);

    //间隔描述一行
    QHBoxLayout * h2 = new QHBoxLayout;
    QLabel * label2 = new QLabel("间隔描述",this);
    m_pDescEdit = new QLineEdit(this);
    m_pDescEdit->setPlaceholderText("请输入间隔描述");
    m_pDescEdit->setProperty("author","ThreeDog");
    h2->addWidget(label2,2);
    h2->addWidget(m_pDescEdit,2);
    h2->addStretch(6);
    this->m_pArticleVLayout->addLayout(h2);

    //制造商一行
    QHBoxLayout * h3 = new QHBoxLayout;
    QLabel * label3 = new QLabel("制造商",this);
    m_pMakerEdit = new QLineEdit(this);
    m_pMakerEdit->setProperty("author","ThreeDog");
    m_pMakerEdit->setPlaceholderText("请输入制造商");
    h3->addWidget(label3,2);
    h3->addWidget(m_pMakerEdit,8);
    this->m_pArticleVLayout->addLayout(h3);

    //生产日期
    QHBoxLayout * h4 = new QHBoxLayout;
    QLabel * label4 = new QLabel("生产日期",this);
    m_pProduceDate = new QDateEdit(this);
    m_pProduceDate->setProperty("author","ThreeDog");
    m_pProduceDate->setDate(QDate(2018,1,1));
    m_pProduceDate->setCalendarPopup(true);
    h4->addWidget(label4,2);
    h4->addWidget(m_pProduceDate,8);
    this->m_pArticleVLayout->addLayout(h4);

    //投运日期
    QHBoxLayout * h5 = new QHBoxLayout;
    QLabel * label5 = new QLabel("投运日期",this);
    m_pRunDate = new QDateEdit(this);
    m_pRunDate->setProperty("author","ThreeDog");
    m_pRunDate->setDate(QDate(2018,1,1));
    m_pRunDate->setCalendarPopup(true);
    h5->addWidget(label5,2);
    h5->addWidget(m_pRunDate,8);
    this->m_pArticleVLayout->addLayout(h5);

    //站点图片文字&按钮
    QHBoxLayout * h6 = new QHBoxLayout;
    QLabel * label6 = new QLabel("* 间隔图片（800px*400px，jpg,png）",this);
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
    m_pPicLabel->setFixedSize(800,400);
    hh->addWidget(m_pPicLabel);

    this->m_pArticleVLayout->addLayout(h7);

    QHBoxLayout * h8 = new QHBoxLayout;
    m_pEditPositionBtn = new QPushButton("监测点位置编辑",this);
    m_pEditPositionBtn->setObjectName("subButton");
    connect(m_pEditPositionBtn,SIGNAL(clicked(bool)),this,SLOT(slot_editPosition()));
    h8->addStretch();
    h8->addWidget(m_pEditPositionBtn);
    this->m_pArticleVLayout->addLayout(h8);

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

}

void AddSpacerModal::generateSensors()
{
    //随机摆放检测单的位置
}

AddSpacerModal::~AddSpacerModal()
{

}

//点击确认按钮
void AddSpacerModal::slot_okBtnClicked()
{
    //生成一个新的间隔对象、通过接口插入数据库
    Spacing s;
    s.name = m_pNameEdit->text();
    s.desc =  m_pDescEdit->text();
    s.producer = m_pMakerEdit->text();
    s.manDate =  m_pProduceDate->date().toString("yyyy-MM-dd");
    s.runDate = m_pRunDate->date().toString("yyyy-MM-dd");
    s.pictureURL = "xxx.png";
    s.status = 1;
    s.lastTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    s.isDelete = 0;
    //如果id是-1，执行插入的逻辑
    if(m_iId == -1){
        s.createTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
        if(Dao::getInstance()->InsertSpacing(s)){
            TDMessageBox::information("添加成功");
            emit sig_ok();
        }else{
            TDMessageBox::warning("添加失败，请重试");
        }
    }else{
    //否则执行修改，更新的逻辑
        if(Dao::getInstance()->UpdateSpacing(m_iId,s)){
            TDMessageBox::information("修改成功");
            emit sig_ok();
        }else{
            TDMessageBox::warning("修改失败，请重试");
        }
    }
}

//选择图片
void AddSpacerModal::slot_addPic()
{
    //加载图片
    QString picPath = QFileDialog::getOpenFileName(this,"选择图片",QDir::homePath(),"Images (*.png *.xpm *.jpg)");
    QPixmap pic;
    pic.load(picPath);
    pic = pic.scaled(this->m_pPicLabel->size(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    this->m_pPicLabel->setPixmap(pic);
}

void AddSpacerModal::slot_editPosition()
{
    //监测点位置编辑
}
