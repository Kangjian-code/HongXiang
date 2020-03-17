/**************************************************************
 * File Name   : addspacermodal.h
 * Author      : ThreeDog
 * Date        : Sat Mar 02 22:18:26 2019
 * Description : 新增间隔点
 *
 **************************************************************/
#ifndef _ADDSPACERMODAL_H_
#define _ADDSPACERMODAL_H_
#include "ThreeDog/tdmodal.h"
#include "DataModal.h"
#include "dao.h"
#include <QLineEdit>
#include <QTextEdit>
#include <QComboBox>
#include <QDateEdit>
#include <QFileDialog>
#include <QDir>

class AddSpacerModal : public TDModal
{
    Q_OBJECT
public:
    explicit AddSpacerModal(QWidget * parent = 0);
    AddSpacerModal(Spacing spacing , QWidget * parent = nullptr);
    void initInterface();
    void generateSensors(); //  随机生成监测点
    virtual ~AddSpacerModal();
public slots:
    void slot_okBtnClicked();
    void slot_addPic();
    void slot_editPosition();
signals:
    void sig_ok();          //点击ok成功添加后发出一个信号，主界面刷新左侧列表
private:
    QLineEdit * m_pNameEdit;
    QLineEdit * m_pDescEdit;
    QLineEdit * m_pMakerEdit;
    QDateEdit * m_pProduceDate;         //生产日期
    QDateEdit * m_pRunDate;             //投运日期
    QPushButton * m_pChoicePicBtn;
    QWidget * m_pPicWidget;
    QPushButton * m_pEditPositionBtn;
    QLabel * m_pPicLabel;
    int m_iId;  //间隔id，用于修改间隔的时候用
};

#endif  //ADDSPACERMODAL
