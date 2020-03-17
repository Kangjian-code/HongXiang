///**************************************************************
// * File Name   : EditSensorModal.cpp
// * Author      : ThreeDog
// * Date        : Thu Apr 11 16:43:16 2019
// * Description : 添加监测点
// *     2019/05/08 弃用
// *
// **************************************************************/

//#include "editsensormodal.h"

//EditSensorModal::EditSensorModal(QWidget * parent)
//    :TDModal("编辑监测点",parent)
//{
//    this->resize(1460,635);
//    this->setButtonText("保存","返回");
//    //添加下侧的几个按钮
//    m_pImportBtn = new QPushButton("导入",this);
//    m_pExportBtn = new QPushButton("导出",this);
//    m_pAddBtn = new QPushButton("添加",this);
//    this->m_pFooterHLayout->insertWidget(2,m_pAddBtn);
//    this->m_pFooterHLayout->insertWidget(2,m_pExportBtn);
//    this->m_pFooterHLayout->insertWidget(2,m_pImportBtn);

//    disconnect(m_pOKBtn,SIGNAL(clicked(bool)),this,SLOT(close()));
//    connect(m_pOKBtn,SIGNAL(clicked(bool)),this,SLOT(save()));
//    connect(m_pAddBtn,SIGNAL(clicked(bool)),this,SLOT(add()));
//    connect(m_pImportBtn,SIGNAL(clicked(bool)),this,SLOT(importConfig()));
//    connect(m_pExportBtn,SIGNAL(clicked(bool)),this,SLOT(exportConfig()));

//    initTable();
//}

//EditSensorModal::~EditSensorModal()
//{

//}

//void EditSensorModal::initTable()
//{
//    //初始化表格
//    m_pTableWidget = new QTableWidget(this);
//    m_pTableWidget->setMinimumHeight(475);
//    this->m_pArticleVLayout->addWidget(m_pTableWidget);

//    m_pTableWidget->setColumnCount(13);
//    m_pTableWidget->setColumnWidth(0, 120 );
//    m_pTableWidget->setColumnWidth(1, 120);
//    m_pTableWidget->setColumnWidth(2, 120 );
//    m_pTableWidget->setColumnWidth(3, 100);
//    m_pTableWidget->setColumnWidth(4, 100);
//    m_pTableWidget->setColumnWidth(5, 100);
//    m_pTableWidget->setColumnWidth(6, 120 );
//    m_pTableWidget->setColumnWidth(7, 120);
//    m_pTableWidget->setColumnWidth(8, 80);
//    m_pTableWidget->setColumnWidth(9, 80);
//    m_pTableWidget->setColumnWidth(10, 80);
//    m_pTableWidget->setColumnWidth(11, 80);
//    m_pTableWidget->setColumnWidth(12, 120);
//    m_pTableWidget->verticalHeader()->setDefaultSectionSize(40);

//    QStringList headText;
//    headText << "所属间隔" << "监测点名称"<< "所属采集单元" << "设备编号" << "通道号" << "类型" << "关联监测点" << "安装图片" << "报警阈值" << "脉冲数量阈值" << "频率" << "参考阈值" << "操作";
//    m_pTableWidget->setHorizontalHeaderLabels(headText);
//    m_pTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
//    m_pTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
//    m_pTableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
//    m_pTableWidget->setAlternatingRowColors(true);
//    m_pTableWidget->verticalHeader()->setVisible(false);
//    m_pTableWidget->horizontalHeader()->setStretchLastSection(true);
//}

//void EditSensorModal::addCellWidget(int row, int col,const QString text)
//{
//    QWidget * w = new QWidget(this);
//    QHBoxLayout * h = new QHBoxLayout;
//    h->setContentsMargins(5,3,5,3);
//    w->setLayout(h);
//    QLineEdit * edit = new QLineEdit(this);
//    edit->setObjectName(QString("line%1%2").arg(row,col));
//    edit->setPlaceholderText(QString("请输入%1").arg(text));
//    edit->setStyleSheet("background:transparent;border-width:0;border-style:outset");
//    h->addWidget(edit);
//    this->m_pTableWidget->setCellWidget(row,col,w);
//}

//void EditSensorModal::importConfig()
//{

//}

//void EditSensorModal::exportConfig()
//{

//}

//void EditSensorModal::connectSensor()
//{
//    //关联监测点操作

//}

//void EditSensorModal::downLoad()
//{
////    QLineEdit* edit = m_pTableWidget->findChild<QLineEdit *>(QString("line%1%2").arg(row,0));
//////    qDebug()<<((QLineEdit *)m_pTableWidget->cellWidget(row,0))->text();
////    QString text = QString("是否将 %1 的通道设置下放？").arg(edit->text());
////    int res = TDMessageBox::question(text,this);
////    if(res == QMessageBox::Yes){
////        TDMessageBox::information("下放成功");
////    }else if (res == QMessageBox::No){

////    }
//}

//void EditSensorModal::deleteRow()
//{

//}

////添加
//void EditSensorModal::add()
//{
//    //每次点击添加按钮，就添加一行内容，每一行内容全是LienEdit，可以由用户设置和修改
//    int row = this->m_pTableWidget->rowCount(); //获取行数
//    this->m_pTableWidget->insertRow(row);
//    //第一列 所属间隔
//    QWidget * w = new QWidget(this);
//    QHBoxLayout * h = new QHBoxLayout;
//    h->setContentsMargins(5,3,5,3);
//    w->setLayout(h);
//    QComboBox * combo = new QComboBox(this);
//    combo->setProperty("author","ThreeDog");
//    for(auto spacing : Dao::getInstance()->QuerySpacing()){
//        combo->addItem(spacing.name);
//    }
//    combo->setProperty("row",row);
//    combo->setCurrentIndex(0);
//    h->addWidget(combo);
//    this->m_pTableWidget->setCellWidget(row,0,w);

//    //第二列 监测点名称
//    this->addCellWidget(row,1,"监测点名称");

//    //第三列 所属采集单元
//    QWidget * w2 = new QWidget(this);
//    QHBoxLayout * h2 = new QHBoxLayout;
//    h2->setContentsMargins(20,3,20,3);
//    w2->setLayout(h2);
//    QComboBox * combo2 = new QComboBox(this);
//    combo2->setProperty("author","ThreeDog");
////    for(auto ied : Dao::getInstance()->QueryIED()){
////        combo2->addItem(ied.name);
////    }
//    combo2->addItem("采集单元1");
//    combo2->addItem("采集单元2");
//    combo2->addItem("采集单元3");
//    combo2->setProperty("row",row);
//    combo2->setCurrentIndex(0);
//    h2->addWidget(combo2);
//    this->m_pTableWidget->setCellWidget(row,2,w2);

//    //第四列 设备编号
//    this->addCellWidget(row,3,"设备编号");

//    //第五列 通道号
//    QWidget * w3 = new QWidget(this);
//    QHBoxLayout * h3 = new QHBoxLayout;
//    h3->setContentsMargins(20,3,20,3);
//    w3->setLayout(h3);
//    QComboBox * combo3 = new QComboBox(this);
//    combo3->setProperty("author","ThreeDog");
//    for(int i = 1; i <= 8; i++){
//        combo3->addItem(QString::number(i));
//    }
//    combo3->setProperty("row",row);
//    combo3->setCurrentIndex(0);
//    h3->addWidget(combo3);
//    this->m_pTableWidget->setCellWidget(row,4,w3);
//    this->addCellWidget(row,4,"通道数量");

//    //第六列 类型
//    QWidget * w4 = new QWidget(this);
//    QHBoxLayout * h4 = new QHBoxLayout;
//    h4->setContentsMargins(20,3,20,3);
//    w4->setLayout(h4);
//    QComboBox * combo4 = new QComboBox(this);
//    combo4->setProperty("author","ThreeDog");
//    combo4->setProperty("row",row);
//    combo4->addItem("UHF");
//    combo4->addItem("震动");
//    combo4->addItem("噪声");
//    combo->setCurrentIndex(0);
//    h4->addWidget(combo4);
//    this->m_pTableWidget->setCellWidget(row,5,w);

//    //第七列 关联监测点
//    QWidget * ww = new QWidget(this);
//    QHBoxLayout * hh = new QHBoxLayout;
//    hh->setContentsMargins(20,3,20,3);
//    ww->setLayout(hh);
//    QPushButton * m_pConnectSensroBtn = new QPushButton("关联监测点",this);
//    m_pConnectSensroBtn->setProperty("author","ThreeDog");
//    hh->addWidget(m_pConnectSensroBtn,4);
//    this->m_pTableWidget->setCellWidget(row,6,ww);

//    //第八列 安装图片
//    QWidget * w5 = new QWidget(this);
//    QHBoxLayout * h5 = new QHBoxLayout;
//    h5->setContentsMargins(20,3,20,3);
//    w5->setLayout(h5);
//    //l用于显示
//    QLabel *l = new QLabel(this);
//    h5->addWidget(l);
//    this->m_pTableWidget->setCellWidget(row,7,w5);

//    //第九列 报警阈值
//    this->addCellWidget(row,8,"报警阈值");

//    //第十列 脉冲数量阈值
//    this->addCellWidget(row,9,"脉冲数量阈值");

//    //第十一列 频率
//    this->addCellWidget(row,10,"频率");

//    //第十二列 参考阈值
//    this->addCellWidget(row,11,"参考阈值");

//    //第十三列 操作（下放和删除）
//    QWidget * w6 = new QWidget(this);
//    QHBoxLayout * h6 = new QHBoxLayout;
//    h6->setContentsMargins(20,3,20,3);
//    w6->setLayout(h6);
//    QPushButton * m_pDownLoad = new QPushButton("下放",this);
//    m_pDownLoad->setProperty("author","ThreeDog");
//    h6->addWidget(m_pDownLoad,6);
//    TDPushButton * m_pDeleteButton = new TDPushButton("delete_icon.png","delete_icon.png","delete_icon.png",this);
//    h6->addWidget(m_pDeleteButton,4);
//    this->m_pTableWidget->setCellWidget(row,12,w6);

//    connect(m_pConnectSensroBtn,SIGNAL(clicked()),this,SLOT(connectSensor()));
//    connect(m_pDownLoad,SIGNAL(clicked()),this,SLOT(downLoad()));
//    connect(m_pDeleteButton,SIGNAL(clicked()),this,SLOT(deleteRow()));

//}

//void EditSensorModal::save()
//{

//}

