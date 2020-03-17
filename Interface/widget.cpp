/**************************************************************
 * File Name   : newclass.cpp
 * Author      : ThreeDog
 * Date        : Thu Jan 03 20:01:31 2019
 * Description : 页面主文件。采用滚动窗体实现。先显示LoginPage,登录成功后显示MainPage
 * 项目git地址：https://git.dev.tencent.com/firstouch/hx-admin.git
 * 项目页面地址：https://lanhuapp.com/url/Luy5l
 *
 **************************************************************/
#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#include "widget.h"

Widget::Widget(QWidget *parent)
    : TDScrollArea(parent)
{
    //重设窗体大小为全屏幕大小
    QRect rect = QApplication::desktop()->availableGeometry();
    this->resize(rect.width(),rect.height());
    //显示登录页面
    LoginPage * loginPage = new LoginPage();
    connect(loginPage,SIGNAL(LoginSuccess()),this,SLOT(slot_loginSuccess()));
    this->setWidget(loginPage);
    //重设滚动条颜色
    this->setSliderColor(QColor("#ffffff"),QColor("#D8D8D8"));
    this->setSliderOpacity(255,255);
    this->setSliderRadius(0,5);
    //初始化数据库
    Dao::getInstance();

}

Widget::~Widget()
{

}

void Widget::resizeEvent(QResizeEvent *e)
{
    // 在窗体大小改变时，手动判断，如果超出1920*1080,则强制修正回1920*1080
    if(this->width() > 1920 )
        this->resize(1920,this->height());
    if(this->height() > 1080)
        this->resize(this->width(),1080);
    TDScrollArea::resizeEvent(e);
}

void Widget::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event)
    Dao::getInstance()->close();
}

void Widget::slot_loginSuccess()
{
    //登录成功后界面切换
    MainPage * w = new MainPage();
    this->setWidget(w);//重设中心窗体会自动销毁之前的窗体
    //重设滚动条颜色
    this->setSliderColor(QColor("#ffffff"),QColor("#D8D8D8"));
    this->setSliderOpacity(255,255);
    this->setSliderRadius(0,0);
//    this->setMaximumSize(1920,1080);
}
