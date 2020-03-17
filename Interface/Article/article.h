/**************************************************************
 * File Name   : article.h
 * Author      : ThreeDog
 * Date        : Wed Jan 09 15:52:18 2019
 * Description :
 *   用一个堆叠窗体，直接预加载所有的页面，并且在槽函数中实现界面切换的逻辑
 *      1、RunningStatePage：运行状态界面
 *      2、ReadTimeDataPage：实时数据界面
 *      3、HistoryDataPage ：历史数据界面
 *      4、WarningInfoPage ：报警信息界面
 *      5、FingerprintLib  ：指纹库
 *      6、SelfCheckPage   ：自检页面
 *      7、UserPage        ：用户管理界面
 *      8、 系统信息和使用说明：用模态框形式展示
 *      9、 系统配置         ：用模态框形式展示
 *      10、注销            ：弹出模态框确认退出
 *
 **************************************************************/
#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#ifndef _ARTICLE_H_
#define _ARTICLE_H_
#include <QWidget>
#include <QDebug>
#include <QStackedWidget>
#include "ThreeDog/tdwidget.h"
#include "ThreeDog/tdscrollarea.h"
#include "runstatepage.h"
#include "readtimedatapage.h"
#include "historydatapage.h"
//#include "warninginfopage.h"
#include "fingerprintlib.h"
#include "selfcheckpage.h"
#include "userpage.h"
#include "devicewarningpage.h"
#include "dischargewarningform.h"
#include "quakewarningform.h"
#include "datacheckpage.h"
#include "historytrendingpage.h"
#include "horizontalanalysispage.h"
#include "Sensor/alarmdesc.h"
#include "Sensor/eventdesc.h"
#include "Sensor/channelcompare.h"
#include "Sensor/histroytrending.h"

class Article : public QWidget
{
	Q_OBJECT
public:
	explicit Article(QWidget * parent = 0);
	~Article();
public slots:
	void changePage(int i);//界面切换

	void slot_alarmDesc();
	void slot_eventDesc();
	void slot_channelCompare();
	void slot_histroy();


private:
	QStackedWidget * m_pStackedWidget;
	AlarmDesc * ad;
	eventDesc * ed;
	ChannelCompare *cc;
	HistroyTrending *ht;

};

#endif  //ARTICLE
