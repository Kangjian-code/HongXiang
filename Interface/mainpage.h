/**************************************************************
 * File Name   : mainpage.h
 * Author      : ThreeDog
 * Date        : Fri Jan 04 16:03:47 2019
 * Description : 软件主页面，包括上侧导航栏以及左侧的列表等， 所有的子模块都将作为子窗体加载在本页面中。
 * 此界面的实现不单纯使用TDWidget，将结合ui界面组合使用
 **************************************************************/
#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#ifndef MAINPAGE_H
#define MAINPAGE_H

#include "ThreeDog/tdwidget.h"
#include "Article/article.h"
#include "Config/unitconfig.h"
#include "Config/siteconfig.h"
#include "Config/argsconfig.h"
#include "Config/softwareconfig.h"
#include <QWidget>
#include <QDateTime>
#include <QMenu>

namespace Ui {
class MainPage;
}

class MainPage : public QWidget
{
    Q_OBJECT

public:
    explicit MainPage(QWidget *parent = 0);
    void initTitle();               //初始化顶部导航栏
    void initMenu();                //初始化菜单
    void initArticle();             //初始化内容区域
    ~MainPage();
public slots:
    void slot_unitConfig();         //单元配置
    void slot_siteConfig();         //站点配置
    void slot_argsConfig();         //参数配置
    void slot_softwareConfig();     //软件配置
    void slot_dataCheck();          //数据诊断
    void slot_historyTrending();    //历史趋势
    void slot_horizontalAnalysis(); //横向分析
    void slot_systemInfo();         //系统信息
    void slot_usage();              //使用说明
    void slot_deviceWarning();      //设备报警
    void slot_dischargeWarning();   //局放报警
    void slot_quakeWarning();       //震动报警

    void slot_softwareConfigEffective();//站点配置生效

protected:
    void timerEvent(QTimerEvent * e);

private slots:
    void on_statuBtn_clicked();

    void on_currentDataBtn_clicked();

    void on_historyDataBtn_clicked();

    void on_alarmBtn_clicked();

    void on_fingurePrintBtn_clicked();

    void on_selfCheckBtn_clicked();

    void on_userAdminBtn_clicked();

private:
    Ui::MainPage *ui;
    Article * m_pArticle;
};

#endif // MAINPAGE_H
