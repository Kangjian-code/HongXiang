/**************************************************************
 * File Name   : loginpage.h
 * Author      : ThreeDog
 * Date        : Thu Jan 03 20:25:45 2019
 * Description : 登录页面
 *
 **************************************************************/
#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#ifndef _LOGINPAGE_H_
#define _LOGINPAGE_H_
#include "ThreeDog/tdwidget.h"
#include "ThreeDog/tdpushbutton.h"
#include "ThreeDog/tdtoolbar.h"
#include <QLineEdit>
#include <QLabel>
#include <QDebug>

class LoginPage :public TDWidget
{
    Q_OBJECT
public:
    explicit LoginPage(QWidget * parent = 0);

    ~LoginPage();
public slots:
    void loginBtnClicked();
    void showPsdClicked();
signals:
    void LoginSuccess();
private:
    QLineEdit * m_pNameEdit;
    QLineEdit * m_pPsdEdit;
    TDPushButton * m_pLoginBtn;
    TDToolbar * m_pShowPsdBtn;
    QLabel *    m_pCopyrightLabel;
    QLabel *    m_pHelpLabel;

};

#endif  //LOGINPAGE
