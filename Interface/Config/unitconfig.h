/**************************************************************
 * File Name   : unitconfig.h
 * Author      : ThreeDog
 * Date        : Thu Jan 24 20:48:03 2019
 * Description : 单元配置，继承自TDModal模态框实现
 *
 **************************************************************/
#ifndef _UNITCONFIG_H_
#define _UNITCONFIG_H_
#include "ThreeDog/tdmodal.h"
#include "ThreeDog/tdtoolbar.h"
#include "Common/tableoperateitem.h"
#include "ThreeDog/tdmessagebox.h"
#include <QPushButton>
#include <QHeaderView>
#include <QTableWidget>
#include <QLineEdit>
#include <QComboBox>
#include "channelconfig.h"
#include "DataModal.h"
#include "dao.h"
#include "addunitmodal.h"

class UnitConfig : public TDModal
{
	Q_OBJECT
public:
	explicit UnitConfig(QWidget * parent = 0);
	void addCellWidget(int row,int col,const QString text);
	virtual ~UnitConfig();
public slots:
	void importConfig();    //导入配置
	void exportConfig();    //导出配置
	void channelConfig(int id);   //通道配置
	void downLoad(int row);        //下传按钮
	void slot_deleteIed(const int & id);//删除 点击删除小图标
	void slot_alterIed(const int &id );	//修改IED设置
	void add();             //添加
	void comboChange(QString text);
	void initTable();
	void updateTable();//更新列表信息
private :
	QPushButton * m_pImportBtn;
	QPushButton * m_pExportBtn;
	QPushButton * m_pAddBtn;
	QTableWidget * m_pTableWidget;
	QLineEdit * m_pInnerSyncConfigEdit;
};

#endif  //UNITCONFIG
