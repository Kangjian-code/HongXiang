/**************************************************************
 * File Name   : addsensormodal.h
 * Author      : ThreeDog
 * Date        : Thu Apr 11 22:56:43 2019
 * Description : 新增监测点
 *
 **************************************************************/
#ifndef _ADDSENSORMODAL_H_ 
#define _ADDSENSORMODAL_H_ 
#include "ThreeDog/tdmodal.h"
#include "DataModal.h"
#include "dao.h"
#include <QLineEdit>
#include <QTextEdit>
#include <QComboBox>
#include <QDateEdit>
#include <QFileDialog>
#include <QDir>

class AddSensorModal : public TDModal
{
    Q_OBJECT
public:
    explicit AddSensorModal(QWidget * parent = 0);
	AddSensorModal(const Sensor & s,QWidget * parent = 0);
	void initInterface();
    virtual ~AddSensorModal();
public slots:
    void slot_okBtnClicked();
    void slot_addPic();
    void slot_editPosition();
signals:
    void sig_ok(Sensor s);          //点击ok成功添加后发出一个信号，主界面刷新左侧列表
private:
    QLineEdit * m_pNameEdit;
    QComboBox * m_pSpacingCombo;        //所属间隔
    QComboBox * m_pIEDCombo;            //所属采集单元
    QComboBox * m_pChannelNo;           //通道号
    QComboBox * m_pTypeCombo;           //类型
    QLineEdit * m_pDeviceNoEdit;        //设备编号
    QLineEdit * m_pAlarmThresholdEdit;  //报警阈值
    QLineEdit * m_pPulseThresholdEdit;  //脉冲数量阈值
    QLineEdit * m_pFreqBandEdit;        //频带
    QLineEdit * m_pReferToThreshold;    //参考阈值
    QLineEdit * m_pNoiseChannelNo;      //关联噪声通道
    QPushButton * m_pChoicePicBtn;
    QWidget * m_pPicWidget;
    QLabel * m_pPicLabel;
	int			m_iId;				//id
};

#endif  //ADDSENSORMODAL
