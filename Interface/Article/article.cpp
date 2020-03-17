/**************************************************************
 * File Name   : article.cpp
 * Author      : ThreeDog
 * Date        : Wed Jan 09 15:52:18 2019
 * Description :
 *  用一个堆叠窗体，直接预加载所有的页面，并且在槽函数中实现界面切换的逻辑
 *      1、RunStatePage    ：运行状态界面（有左侧栏）
 *      2、ReadTimeDataPage：实时数据界面（有左侧栏）
 *      3、HistoryDataPage ：历史数据界面（有左侧栏）
 *      4、WarningInfoPage ：报警信息界面
 *      5、FingerprintLib  ：指纹库     （有左侧栏）
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

#include "article.h"

Article::Article(QWidget *parent)
	:QWidget(parent)
{
	m_pStackedWidget = new QStackedWidget(this);
	m_pStackedWidget->resize(parent->size());

	//加载所有的页面
	RunStatePage * rsp = new RunStatePage(this);
	ReadTimeDataPage * rtdp = new ReadTimeDataPage(this);
	HistoryDataPage * hdp = new HistoryDataPage(this);
	DeviceWarningPage * dwp = new DeviceWarningPage(this);
	DischargeWarningForm * dwf = new DischargeWarningForm(this);
	QuakeWarningForm * qwf = new QuakeWarningForm(this);
	FingerprintLib  * fl  = new FingerprintLib(this);
	SelfCheckPage   * scp = new SelfCheckPage(this);
	UserPage        * up  = new UserPage(this);

	DataCheckPage   * dcp = new DataCheckPage();//数据诊断
	HistoryTrendingPage * htp = new HistoryTrendingPage();//历史趋势
	HorizontalAnalysisPage * hap = new HorizontalAnalysisPage();//横向分析

	ad	= new AlarmDesc();				//间隔--》报警描述
	ed	= new eventDesc();				//间隔--》事件描述
	cc	= new ChannelCompare();			//间隔--》通道对比
	ht	= new HistroyTrending();		//间隔--》历史趋势

	m_pStackedWidget->addWidget(rsp);
	m_pStackedWidget->addWidget(rtdp);
	m_pStackedWidget->addWidget(hdp);
	m_pStackedWidget->addWidget(dwp);
	m_pStackedWidget->addWidget(dwf);
	m_pStackedWidget->addWidget(qwf);
	m_pStackedWidget->addWidget(fl);
	m_pStackedWidget->addWidget(scp);
	m_pStackedWidget->addWidget(up);
	m_pStackedWidget->addWidget(dcp);
	m_pStackedWidget->addWidget(htp);
	m_pStackedWidget->addWidget(hap);
	m_pStackedWidget->addWidget(ad);
	m_pStackedWidget->addWidget(ed);
	m_pStackedWidget->addWidget(cc);
	m_pStackedWidget->addWidget(ht);

	//运行页面监测点上右击选择报警描述、时间描述等等的效果
	connect(rsp,SIGNAL(sig_alarmDesc()),this,SLOT(slot_alarmDesc()));
	connect(rsp,SIGNAL(sig_eventDesc()),this,SLOT(slot_eventDesc()));
	connect(rsp,SIGNAL(sig_channelCompare()),this,SLOT(slot_channelCompare()));
	connect(rsp,SIGNAL(sig_histroy()),this,SLOT(slot_histroy()));

	m_pStackedWidget->setCurrentIndex(0);
}

Article::~Article()
{

}

//将界面切换下标指定的页面
void Article::changePage(int i)
{
	this->m_pStackedWidget->setCurrentIndex(i);
}

void Article::slot_alarmDesc()
{
	this->m_pStackedWidget->setCurrentIndex(12);
	int id = sender()->property("id").toInt();
//	ad->init(id);
}

void Article::slot_eventDesc()
{
	this->m_pStackedWidget->setCurrentIndex(13);
	int id = sender()->property("id").toInt();
//	ed->init(id);
}

void Article::slot_channelCompare()
{
	this->m_pStackedWidget->setCurrentIndex(14);
	int id = sender()->property("id").toInt();
//	cc->init(id);
}

void Article::slot_histroy()
{
	this->m_pStackedWidget->setCurrentIndex(15);
	int id = sender()->property("id").toInt();
//	ht->init(id);
}
