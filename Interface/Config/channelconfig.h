/**************************************************************
 * File Name   : channelconfig.h
 * Author      : ThreeDog
 * Date        : Fri Jan 25 22:10:03 2019
 * Description : 通道配置
 *
 **************************************************************/
#ifndef _CHANNELCONFIG_H_
#define _CHANNELCONFIG_H_
#include "ThreeDog/tdmodal.h"
#include "ThreeDog/tdtoolbar.h"
#include <QComboBox>
#include <QTableWidget>
#include <QHeaderView>
#include <QDebug>
#include "dao.h"
#include "DataModal.h"

class ChannelConfig:public TDModal
{
	Q_OBJECT
public:
	explicit ChannelConfig(int no,QWidget * parent = 0);
	void initTable();
	void updateTable();
	QComboBox * getComboBox(int row);
	TDToolbar * getToolbar(int row);
	virtual ~ChannelConfig();
public slots:
	void slot_okBtnClicked();
private:
	Ied ied;//传入IED的ID,确定是哪个IED的通道设置
	QTableWidget * m_pTableWidget;
};

#endif  //CHANNELCONFIG
