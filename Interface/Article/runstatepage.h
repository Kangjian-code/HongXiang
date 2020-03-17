/**************************************************************
 * File Name   : runtatepage.h
 * Author      : ThreeDog
 * Date        : Thu Jan 10 17:00:07 2019
 * Description : 运行状态页面，包含左侧栏。
 *      用于显示一次接线图，报警信息等内容。
 *
 **************************************************************/
#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#ifndef RUNSTATEPAGE_H
#define RUNSTATEPAGE_H

#include <QWidget>
#include "ThreeDog/tdwidget.h"
#include "ThreeDog/tdscrollarea.h"
#include "ThreeDog/tdtoolbar.h"
#include "ThreeDog/tdmessagebox.h"
#include "ThreeDog/tdtreewidget.h"
#include "Config/editsensormodal.h"
#include "Common/configpage.h"
#include "Common/tablepage.h"
#include "Config/addspacermodal.h"
#include "Config/editsensormodal.h"
#include "Config/addsensormodal.h"
#include "imageindex.h"
#include <QHBoxLayout>
#include <QDebug>
#include <QLabel>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QTreeWidget>
#include <QMenu>
#include <QDebug>

namespace Ui {
class RunStatePage;
}

using namespace QtCharts;

class RunStatePage : public QWidget
{
    Q_OBJECT

public:
    explicit RunStatePage(QWidget *parent = 0);
    void initTabs();                        //初始化上侧的四个标签卡
    void initTab1();
    void initTab2();
    void initTab3();
    void initTab4();
    void initImageWidget();                 //初始化一次接线图的滚动区域
    void initTreeView();                    //初始化左侧树状菜单
    void initTables();                      //初始化下侧的两个表格
    void updateLeftTable();                 //更新左表数据
    void updateRightTable();                //更新右表数据
    void initLeftTabs();                    //初始化左侧栏

    ~RunStatePage();
public slots:
    void addSpacer();                       //新增间隔
    void importPosition();                  //导入监测点位置表
    void exportPosition();                  //导出监测点位置表
    void updateTreeWidget();                //更新树形菜单
    void updateImageWidget();               //更新一次接线图
    void addSensor(Sensor s);               //新添加一个监测点
    void slot_treeItemClicked(QTreeWidgetItem *item,int column);//树状列表中的控件被点击
    void slot_deleteSpacing();              //点击按钮删除间隔
    void slot_alterSpacing();               //点击按钮修改间隔
    void slot_addSensor();                  //点击按钮新增监测点
    void slot_alterSensor();				//点击按钮修改监测点
    void slot_deleteSensor();				//点击按钮删除检测点
    void hideLeft();                        //隐藏左侧栏

signals:
	void sig_alarmDesc();
	void sig_eventDesc();
	void sig_channelCompare();
	void sig_histroy();

private:
    Ui::RunStatePage *ui;
    QTreeWidget * m_pTreeWidget ;
    TDWidget * m_pEventCountWidget;
    TDWidget * m_pDataWarningWidget;
    TDWidget * m_pDeviceWarningEventWidget;
    TDWidget * m_pDeviceWarningRateWidget;
    TDScrollArea * m_pScrollArea;
    TDToolbar * m_pHideLeftBtn;
    QTableWidget * m_pTableWidget1;
    QTableWidget * m_pTableWidget2;
    ImageIndex * m_pImageImdex ;
};

#endif // RUNSTATEPAGE_H
