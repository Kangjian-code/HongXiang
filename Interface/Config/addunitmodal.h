/**************************************************************
 * File Name   : addunitmodal.h
 * Author      : ThreeDog
 * Date        : Fri May 17 21:03:58 2019
 * Description : 单元配置的添加、修改模态框
 *
 **************************************************************/

#ifndef _ADDUNITMODAL_H_
#define _ADDUNITMODAL_H_
#include "ThreeDog/tdmodal.h"
#include "DataModal.h"
#include <QLineEdit>
#include <QComboBox>
#include "ThreeDog/tdtoolbar.h"
#include "dao.h"

class AddUnitModal : public TDModal
{
	Q_OBJECT
public :
	explicit AddUnitModal(QWidget * parent = nullptr);
	AddUnitModal(const Ied & ied, QWidget *parent = nullptr);
	void initInterface();
	virtual ~AddUnitModal();

public:
	static QMap<int,QString> s_mapTypes;
	static void initTypeMap();
signals:
	void sig_ok();
protected:

public slots:
//	void slot_channelSlots();
	void slot_okBtnClicked();
private:
	QLineEdit *			m_pUnitNameEdit;
	QLineEdit *			m_pDeviceNoEdit;
	QLineEdit *			m_pIPEdit;
	QLineEdit *			m_pPortEdit;
	QComboBox *			m_pChannelNumberCombo;
	QComboBox *			m_pSyncTypeCombo;
	QLineEdit *			m_pInnserSettingEdit;
	TDToolbar *			m_pDeviceStatus;
	QPushButton  *		m_pChannelConfigBtn;
	int m_iId;
	Ied ied;
	//用一个变量保存通道设置
};




#endif
