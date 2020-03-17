/**************************************************************
 * File Name   : softwareconfig.h
 * Author      : ThreeDog
 * Date        : Sun Jan 27 21:49:58 2019
 * Description : 软件配置
 *
 **************************************************************/
#ifndef _SOFTWARECONFIG_H_ 
#define _SOFTWARECONFIG_H_ 

#include "ThreeDog/tdmodal.h"
#include "dao.h"
#include "DataModal.h"
#include <QLineEdit>
#include <QTextEdit>
#include <QComboBox>
#include <QFileDialog>
#include <QDir>

class SoftwareConfig : public TDModal
{
    Q_OBJECT
public:
    SoftwareConfig(QWidget * parent = 0);
    void updateSoftwareConfig();
    virtual ~SoftwareConfig();
signals:
    void okBtnClicked();
public slots:
    void slot_choicePic();
    void slot_okBtnClicked();
private:
    QLineEdit * m_pCompanyNameEdit;
    QLineEdit * m_pVersionNumEdit;
    QLineEdit * m_pSoftwareNameEdit;
    QTextEdit * m_pCompanyIntroduceText;
    QPushButton * m_pChoicePicBtn;
    QLabel * m_pPicLabel;
    int id ;
};

#endif  //SOFTWARECONFIG
