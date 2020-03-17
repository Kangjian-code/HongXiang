/**************************************************************
 * File Name   : siteconfig.h
 * Author      : ThreeDog
 * Date        : Sat Jan 26 22:37:22 2019
 * Description : 站点配置
 *
 **************************************************************/
#ifndef _SITECONFIG_H_ 
#define _SITECONFIG_H_ 
#include "ThreeDog/tdmodal.h"
#include "DataModal.h"
#include "dao.h"
#include <QLineEdit>
#include <QComboBox>
#include <QTextEdit>
#include <QDebug>
#include <QFileDialog>
#include <QDir>
#include <QSqlQuery>
#include "ThreeDog/tdmessagebox.h"

class SiteConfig : public TDModal
{
    Q_OBJECT
public:
    explicit SiteConfig(QWidget * parent = 0);
    void updateSiteConfig();
    virtual ~SiteConfig();
signals:
    void okBtnClicked();
public slots:
    void slot_okBtnClicked();
    void slot_addPic();
private:
    int id ;
    QLineEdit * m_pNameEdit;
    QComboBox * m_pVoltageCombo;    //电压等级
    QLineEdit * m_pIPEdit;
    QLineEdit * m_pPortEdit;
    QTextEdit * m_pSiteText;
    QPushButton * m_pChoicePicBtn;
    QWidget *   m_pPicWidget;
    QLabel *    m_pPicLabel;
    QString  m_sPicPath;

};

#endif  //SITECONFIG
