/**************************************************************
 * File Name   : argsconfig.h
 * Author      : ThreeDog
 * Date        : Sun Jan 27 15:40:00 2019
 * Description : 参数设置，放电参数设置、报警参数设置、其他参数设置
 *
 **************************************************************/
#ifndef _ARGSETTINGS_H_
#define _ARGSETTINGS_H_
#include <QWidget>
#include <QComboBox>
#include <QLineEdit>
#include <QGroupBox>
#include <QGridLayout>
#include <QCheckBox>
#include <QSqlQuery>
#include "ThreeDog/tdmodal.h"
#include "DataModal.h"
#include "dao.h"
#include "ThreeDog/tdscrollarea.h"

class ArgsConfig:public TDModal
{
    Q_OBJECT
public:
    explicit ArgsConfig(QWidget * parent = 0);
    void initArgs();
    void updateArgsConfig();
    virtual ~ArgsConfig();
signals:
    void okBtnClicked();
public slots:
    void slot_okBtnClicked();
private:
    int id ;
    QWidget * m_pWidget;
    QVBoxLayout * m_pArgsLayout;
    QComboBox * m_pTypeCombo;
    QLineEdit * m_pFirstMinEdit;        //一档幅值最小值
    QLineEdit * m_pFirstMaxEdit;        //一档幅值最大值
    QLineEdit * m_pFirstDescEdit;       //一档档位描述

    QLineEdit * m_pSecondMinEdit;       //二档幅值最小值
    QLineEdit * m_pSecondMaxEdit;       //二档幅值最大值
    QLineEdit * m_pSecondDescEdit;      //二档档位描述

    QLineEdit * m_pThirdMinEdit;        //三档幅值最小值
    QLineEdit * m_pThirdMaxEdit;        //三档幅值最大值
    QLineEdit * m_pThirdDescEdit;       //三档档位描述

    QLineEdit * m_pFourthMinEdit;       //四档幅值最小值
    QLineEdit * m_pFourthMaxEdit;       //四档幅值最大值
    QLineEdit * m_pFourthDescEdit;      //四档档位描述

    QGroupBox * m_pWarningConfigGroup;  //设备局放报警设置
    QGroupBox * m_pNodeConfigGroup;     //报警信号节点设置

    QLineEdit * m_pWarningTimeEdit;     //报警观察时间
    QLineEdit * m_pWarningTimesEdit;    //报警次数阈值
    QLineEdit * m_pBrokenTimeEdit;      //装置故障次数阈值
    QLineEdit * m_pWarningIntervelEdit; //报警时间间隔

    QLineEdit * m_pAVGChargeEdit;       //高于平均放电水平值
    QLineEdit * m_pRecordTimeEdit;      //录波时间
    QLineEdit * m_pRecordIntervelEdit;  //采样间隔
    QLineEdit * m_pSelfCheckEdit;       //自检时间

    QCheckBox * m_pIsWarningCheck;      //是否报警
    QComboBox * m_pCheckIntervelCombo;  //报警视察周期
    QLineEdit * m_pMaxChargeEdit;       //最大放电赋值阈值
    QLineEdit * m_pChanceEdit;          //局放概率阈值

};

#endif  //ARGSCONFIG
