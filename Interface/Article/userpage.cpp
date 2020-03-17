/**************************************************************
 * File Name   : userpage.cpp
 * Author      : ThreeDog
 * Date        : Fri Jan 11 22:29:01 2019
 * Description : 用户页面、逻辑上所有的用户信息都是需要数据库检索，因此尽可能
 *      在增删改操作后，统一调用updateTable()接口更新表格数据。
 *
 **************************************************************/
#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#include "userpage.h"
#include "ui_userpage.h"

UserPage::UserPage(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::UserPage)
{
	ui->setupUi(this);
	m_mapLevel.insert(0,"管理员");
	m_mapLevel.insert(1,"普通用户");
	initTable();
	initProperty();
}

void UserPage::initTable()
{

	m_pTableWidget = new QTableWidget(ui->mainWidget);
	ui->hLayout->addWidget(m_pTableWidget);

	m_pTableWidget->setColumnCount(10);

	QStringList headText;
	headText << "" << "账户名" << "用户名称"<< "电话号码" << "邮箱" << "权限等级" << "所属部门" << "最近登录时间" << "备注" << "操作";
	m_pTableWidget->setHorizontalHeaderLabels(headText);
	//首先定义一个复选框表头
	MyQHeaderView *updateHeader = new MyQHeaderView(Qt::Horizontal,m_pTableWidget);
	//表头的复选框被点击的事件：
	connect(updateHeader,SIGNAL(signalStateTrange(bool)),this,SLOT(checkBoxClicked(bool)));
	//其次设置表格的表头
	m_pTableWidget->setHorizontalHeader(updateHeader);
	m_pTableWidget->setColumnWidth(0,90);
	m_pTableWidget->setColumnWidth(1,90);
	m_pTableWidget->setColumnWidth(2,180);
	m_pTableWidget->setColumnWidth(3,180);
	m_pTableWidget->setColumnWidth(4,180);
	m_pTableWidget->setColumnWidth(5,180);
	m_pTableWidget->setColumnWidth(6,180);
	m_pTableWidget->setColumnWidth(7,180);
	m_pTableWidget->setColumnWidth(8,180);
	m_pTableWidget->setColumnWidth(9,180);
	m_pTableWidget->verticalHeader()->setDefaultSectionSize(40);

	m_pTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
	m_pTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
	m_pTableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
	m_pTableWidget->setAlternatingRowColors(true);
	m_pTableWidget->verticalHeader()->setVisible(false);
	m_pTableWidget->horizontalHeader()->setStretchLastSection(true);

	//更新表格中的数据
	updateTable();

}

void UserPage::initProperty()
{
	foreach(QWidget * w,this->findChildren<QWidget *>()){
		w->setProperty("author","ThreeDog");
	}
}

void UserPage::updateTable()
{
	m_pTableWidget->setRowCount(0);
	m_pTableWidget->clearContents();

	for(User user : Dao::getInstance()->QueryUser()){

		int row = this->m_pTableWidget->rowCount(); //获取行数
		this->m_pTableWidget->insertRow(row);

		QWidget * w = new QWidget(m_pTableWidget);
		QHBoxLayout * h = new QHBoxLayout;
		w->setLayout(h);
		h->setContentsMargins(10,3,10,3);
		h->addStretch();
		QCheckBox * check = new QCheckBox;
		check->setObjectName("QCheckBox");
		check->setProperty("id",user.id);
		h->addWidget(check);
		h->addStretch();

		this->m_pTableWidget->setCellWidget(row,0,w);

		QTableWidgetItem *item1 = new QTableWidgetItem(user.loginName);
		QTableWidgetItem *item2 = new QTableWidgetItem(user.realName);
		QTableWidgetItem *item3 = new QTableWidgetItem(user.phone);
		QTableWidgetItem *item4 = new QTableWidgetItem(user.email);
		QTableWidgetItem *item5 = new QTableWidgetItem(m_mapLevel.value(user.level));
		QTableWidgetItem *item6 = new QTableWidgetItem(user.department);
		QTableWidgetItem *item7 = new QTableWidgetItem(user.lastTime);
		QTableWidgetItem *item8 = new QTableWidgetItem(user.remark);

		QWidget * w2 = new QWidget(m_pTableWidget);
		QHBoxLayout * h2 = new QHBoxLayout;
		w2->setLayout(h2);
		h2->setContentsMargins(10,3,10,3);
		h2->addStretch();
		QPushButton * btn = new QPushButton("修改",this);
		btn->setProperty("id",user.id);
		btn->setObjectName("subButton");
		btn->setStyleSheet("width:90px;\
						   height:30px;\
						   max-width:90px;\
						   max-height:30px;\
						   min-width:60px;\
						   min-height:30px;");
		h2->addWidget(btn);
		h2->addStretch();

		this->m_pTableWidget->setCellWidget(row,9,w2);
		connect(btn,SIGNAL(clicked(bool)),this,SLOT(slot_alterUser()));

		item1->setTextAlignment(Qt::AlignCenter);
		item2->setTextAlignment(Qt::AlignCenter);
		item3->setTextAlignment(Qt::AlignCenter);
		item4->setTextAlignment(Qt::AlignCenter);
		item5->setTextAlignment(Qt::AlignCenter);
		item6->setTextAlignment(Qt::AlignCenter);
		item7->setTextAlignment(Qt::AlignCenter);
		item8->setTextAlignment(Qt::AlignCenter);

		m_pTableWidget->setItem(row, 1, item1);
		m_pTableWidget->setItem(row, 2, item2);
		m_pTableWidget->setItem(row, 3, item3);
		m_pTableWidget->setItem(row, 4, item4);
		m_pTableWidget->setItem(row, 5, item5);
		m_pTableWidget->setItem(row, 6, item6);
		m_pTableWidget->setItem(row, 7, item7);
		m_pTableWidget->setItem(row, 8, item8);
	}
}

UserPage::~UserPage()
{
	delete ui;
}

void UserPage::checkBoxClicked(bool b)
{
	if(b){
		qDebug()<<"打开所有的复选框";
		foreach(QCheckBox * check,this->m_pTableWidget->findChildren<QCheckBox *>()){
			check->setChecked(true);
		}
	}else{
		qDebug()<<"关闭所有的复选框";
		foreach(QCheckBox * check,this->m_pTableWidget->findChildren<QCheckBox *>()){
			check->setChecked(false);
		}
	}
}

void UserPage::on_queryBtn_clicked()
{
	//查询按钮被点击
	updateTable();
}

void UserPage::on_addBtn_clicked()
{
	//添加按钮被点击
	//弹出模态框输入用户信息
	UserInfoModal * uim = new UserInfoModal();
	connect(uim,SIGNAL(sig_ok()),this,SLOT(updateTable()));
	uim->show();

}

void UserPage::on_deleteBtn_clicked()
{
	//删除按钮被点击
	//获取所有要删除的账号
	QVector<int> accounts ;
	for(QCheckBox * check : this->m_pTableWidget->findChildren<QCheckBox *>())
	{
		if(check->isChecked())
		{
			accounts.append(check->property("id").toInt());
		}
	}

	int res = TDMessageBox::question("是否将选中的信息全部删除？");
	if(res == QMessageBox::Yes)
	{
		if(accounts.isEmpty())
			return;
		for(int id : accounts)
		{
			if(!Dao::getInstance()->DeleteUser(id))
			{
				TDMessageBox::warning("删除失败");
				return ;
			}
		}
		TDMessageBox::information("删除成功");
		this->updateTable();
	}else
	{
		//pass
	}
}

void UserPage::slot_alterUser()
{
	//修改用户信息
	int id = sender()->property("id").toInt();
	User user = Dao::getInstance()->GetUserById(id);
	//通过账号查询用户，然后把用户信息传递给user并生成修改信息的模态框
	UserInfoModal * uim = new UserInfoModal(user);
	connect(uim,SIGNAL(sig_ok()),this,SLOT(updateTable()));
	uim->show();
}

UserInfoModal::UserInfoModal(QWidget *parent)
	:TDModal("添加用户",parent)
{
	initInterface();
	is_create = true;
}

UserInfoModal::UserInfoModal(User user, QWidget *parent)
	:TDModal("修改用户",parent)
{
	initInterface(user);
	is_create = false;
}

void UserInfoModal::initInterface()
{
	this->setModal(true);
	connect(m_pOKBtn,SIGNAL(clicked(bool)),this,SLOT(slot_okBtnClicked()));

	this->resize(610,773);
	QString stylesheet = "QLabel{\
			font-size:14px;\
			color:#262626;\
			font-family:Microsoft Yahei;\
			line-height:19px;\
	}";
	this->setStyleSheet(stylesheet);
	QHBoxLayout * h1 = new QHBoxLayout;
	QLabel * label1 = new QLabel("* 用户名：",this);
	m_pAccountEdit = new QLineEdit(this);
	m_pAccountEdit->setProperty("author","ThreeDog");
	m_pAccountEdit->setPlaceholderText("请输入用户账号");
	h1->addWidget(label1,2);
	h1->addWidget(m_pAccountEdit,8);
	this->m_pArticleVLayout->addLayout(h1);

	QHBoxLayout * h2 = new QHBoxLayout;
	QLabel * label2 = new QLabel("用户名称：",this);
	m_pNameEdit = new QLineEdit(this);
	m_pNameEdit->setProperty("author","ThreeDog");
	m_pNameEdit->setPlaceholderText("请输入用户名称");
	h2->addWidget(label2,2);
	h2->addWidget(m_pNameEdit,8);
	this->m_pArticleVLayout->addLayout(h2);

	QHBoxLayout * h3 = new QHBoxLayout;
	QLabel * label3 = new QLabel("* 密码：",this);
	m_pPasswordEdit = new QLineEdit(this);
	m_pPasswordEdit->setEchoMode(QLineEdit::Password);
	m_pPasswordEdit->setProperty("author","ThreeDog");
	m_pPasswordEdit->setPlaceholderText("请输入密码");
	h3->addWidget(label3,2);
	h3->addWidget(m_pPasswordEdit,8);
	this->m_pArticleVLayout->addLayout(h3);

	QHBoxLayout * h4 = new QHBoxLayout;
	QLabel * label4 = new QLabel("电话号码：",this);
	m_pTelEdit = new QLineEdit(this);
	m_pTelEdit->setProperty("author","ThreeDog");
	m_pTelEdit->setPlaceholderText("请输入电话号码");
	h4->addWidget(label4,2);
	h4->addWidget(m_pTelEdit,8);
	this->m_pArticleVLayout->addLayout(h4);

	QHBoxLayout * h5 = new QHBoxLayout;
	QLabel * label5 = new QLabel("邮箱：",this);
	m_pEmailEdit = new QLineEdit(this);
	m_pEmailEdit->setProperty("author","ThreeDog");
	m_pEmailEdit->setPlaceholderText("请输入邮箱");
	h5->addWidget(label5,2);
	h5->addWidget(m_pEmailEdit,8);
	this->m_pArticleVLayout->addLayout(h5);

	QHBoxLayout * h6 = new QHBoxLayout;
	QLabel * label6 = new QLabel("* 权限等级：",this);
	m_pPermissonCombo = new QComboBox(this);
	m_pPermissonCombo->addItem("管理员");
	m_pPermissonCombo->setProperty("author","ThreeDog");
	h6->addWidget(label6,2);
	h6->addWidget(m_pPermissonCombo,3);
	h6->addStretch(6);
	this->m_pArticleVLayout->addLayout(h6);

	QHBoxLayout * h7 = new QHBoxLayout;
	QLabel * label7 = new QLabel("所属部门：",this);
	m_pDeptEdit = new QLineEdit(this);
	m_pDeptEdit->setProperty("author","ThreeDog");
	m_pDeptEdit->setPlaceholderText("请输入所属部门");
	h7->addWidget(label7,2);
	h7->addWidget(m_pDeptEdit,8);
	this->m_pArticleVLayout->addLayout(h7);

	QHBoxLayout * h8 = new QHBoxLayout;
	QLabel * label8 = new QLabel("备注：",this);
	m_pDescEdit = new QLineEdit(this);
	m_pDescEdit->setProperty("author","ThreeDog");
	h8->addWidget(label8,2);
	h8->addWidget(m_pDescEdit,8);
	this->m_pArticleVLayout->addLayout(h8);

	this->m_pArticleVLayout->setSpacing(20);
	this->m_pArticleVLayout->addStretch();
	this->setButtonText("返回","保存");
	this->m_pOKBtn->setStyleSheet("width:145px;");
	this->m_pCancleBtn->setStyleSheet("width:145px;");
}

void UserInfoModal::initInterface(User user)
{
	initInterface();
	m_pAccountEdit->setText(user.loginName);
	m_pNameEdit->setText(user.realName);
	m_pPasswordEdit->setText(user.password);
	m_pTelEdit->setText(user.phone);
	m_pEmailEdit->setText(user.email);
	m_pDeptEdit->setText(user.department);
	m_pDescEdit->setText(user.remark);
	m_iID = user.id;
	if(!user.level){
		m_pPermissonCombo->setCurrentText("管理员");
	}else{
		m_pPermissonCombo->setCurrentText("用户");
	}
}

void UserInfoModal::slot_okBtnClicked()
{
	if(this->is_create){
		User user;
		user.loginName = this->m_pAccountEdit->text();
		user.realName = this->m_pNameEdit->text();
		user.creatTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
		user.lastTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
		user.email = this->m_pEmailEdit->text();
		user.level = this->m_pPermissonCombo->currentIndex();
		user.password = this->m_pPasswordEdit->text();
		user.phone = this->m_pTelEdit->text();
		user.remark = this->m_pDescEdit->text();
		user.department = this->m_pDeptEdit->text();
		user.status = 1;
		if(Dao::getInstance()->InsertUser(user)){
			TDMessageBox::information("添加成功");
			emit sig_ok();
		}else{
			TDMessageBox::warning("添加失败，请重试");
		}
		qDebug()<<"添加用户，执行添加用户的逻辑";
	}else{
		User user;
		user.loginName = this->m_pAccountEdit->text();
		user.realName = this->m_pNameEdit->text();
		user.creatTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
		user.lastTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
		user.email = this->m_pEmailEdit->text();
		user.level = this->m_pPermissonCombo->currentIndex();
		user.password = this->m_pPasswordEdit->text();
		user.phone = this->m_pTelEdit->text();
		user.remark = this->m_pDescEdit->text();
		user.department = this->m_pDeptEdit->text();
		user.status = 1;
		user.id = this->m_iID;
		if(Dao::getInstance()->UpdateUser(user)){
			TDMessageBox::information("修改成功");
			emit sig_ok();
		}else{
			TDMessageBox::warning("修改失败，请重试");
		}
		qDebug()<<"修改用户，执行修改用户的逻辑";
	}
}
