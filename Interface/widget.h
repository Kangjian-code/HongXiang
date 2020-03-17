/**************************************************************
 * File Name   : newclass.cpp
 * Author      : ThreeDog
 * Date        : Thu Jan 03 20:01:31 2019
 * Description : 页面主文件，采用滚动窗体实现。先显示LoginPage,登录成功后显示MainPage
 * 项目git地址：https://git.dev.tencent.com/firstouch/hx-admin.git
 * 项目页面地址：https://lanhuapp.com/url/Luy5l
 *
 **************************************************************/
#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#ifndef WIDGET_H
#define WIDGET_H

#include <QDesktopWidget>
#include <QApplication>
#include "ThreeDog/tdscrollarea.h"
#include "loginpage.h"
#include "mainpage.h"
#include "dao.h"

//继承自滚动窗体，自动出现滚动条
class Widget : public TDScrollArea
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();
protected:
    void resizeEvent(QResizeEvent *e);
    void closeEvent(QCloseEvent *event);
public slots:
    void slot_loginSuccess();//登陆成功
};

#endif // WIDGET_H
