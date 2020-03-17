/**************************************************************
 * File Name   : userpage.h
 * Author      : ThreeDog
 * Date        : Fri Jan 11 22:29:01 2019
 * Description : 用户页面、逻辑上所有的用户信息都是需要数据库检索，因此尽可能
 *      在增删改操作后，统一调用updateTable()接口更新表格数据。
 *
 **************************************************************/
#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#ifndef USERPAGE_H
#define USERPAGE_H

#include <QWidget>
#include "Common/myqheaderview.h"
#include <QTableWidget>
#include "ThreeDog/tdmodal.h"
#include "ThreeDog/tdmessagebox.h"
#include "DataModal.h"
#include <dao.h>
//添加&修改用户页面的类定义
class UserInfoModal : public TDModal
{
	Q_OBJECT
public:
	explicit UserInfoModal(QWidget * parent = 0);
	explicit UserInfoModal(User user,QWidget * parent = 0);
	void initInterface();
	void initInterface(User user);
signals:
	void sig_ok();
public slots:
	void slot_okBtnClicked();       //添加&修改信息
private:
	QLineEdit * m_pAccountEdit;
	QLineEdit * m_pNameEdit;
	QLineEdit * m_pPasswordEdit;
	QLineEdit * m_pTelEdit;
	QLineEdit * m_pEmailEdit;
	QLineEdit * m_pDeptEdit;
	QLineEdit * m_pDescEdit;
	QComboBox * m_pPermissonCombo;
	int m_iID;
	bool is_create;

};


//用户页面类定义
namespace Ui {
class UserPage;
}

class UserPage : public QWidget
{
	Q_OBJECT

public:
	explicit UserPage(QWidget *parent = 0);
	void initTable();           //初始化表格
	void initProperty();        //给所有的控件加上ThreeDog属性
	~UserPage();
private slots:
	//查询按钮
	void on_queryBtn_clicked();
	//添加按钮
	void on_addBtn_clicked();
	//删除按钮
	void on_deleteBtn_clicked();
	//修改用户
	void slot_alterUser();
	//头部复选框被点击
	void checkBoxClicked(bool b);

	void updateTable();         //更新表格数据

private:
	Ui::UserPage *ui;
	QTableWidget * m_pTableWidget;
	QMap<int ,QString> m_mapLevel;
};

#endif // USERPAGE_H
