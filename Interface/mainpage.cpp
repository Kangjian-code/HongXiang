/**************************************************************
 * File Name   : mainpage.h
 * Author      : ThreeDog
 * Date        : Fri Jan 04 16:03:47 2019
 * Description : 软件主页面，包括上侧导航栏以及左侧的列表等， 所有的子模块都将作为子窗体加载在本页面中。
 *
 **************************************************************/
#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#include "mainpage.h"
#include "ui_mainpage.h"

MainPage::MainPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainPage)
{
    ui->setupUi(this);
    //初始化导航栏
    initTitle();
    //初始化菜单栏
    initMenu();
    //初始化内容区域
    initArticle();
}

void MainPage::initTitle()
{
    //初始化顶部导航栏
    this->setProperty("form", true);
    this->setProperty("canMove", false);

    ui->widgetTitle->setProperty("form", "title");
    ui->widgetTop->setProperty("nav", "top");

    QSize icoSize(28, 28);
    int icoWidth = 96;

    //设置顶部导航按钮
    QList<QToolButton *> tbtns = ui->widgetTop->findChildren<QToolButton *>();
    foreach (QToolButton *btn, tbtns) {
        btn->setIconSize(icoSize);
        btn->setMinimumWidth(icoWidth);
    }

    //顶部Logo
    TDWidget * logo = new TDWidget(":/img/index/logo.png",ui->logoWidget);
    logo->move(52,18);

    this->startTimer(1);//一秒一次定时器触发，更新时间显示
}

//初始化菜单栏
void MainPage::initMenu()
{
    //系统配置菜单
    QMenu *sysConfMenu = new QMenu(this);
    sysConfMenu->addAction("单元配置", this, SLOT(slot_unitConfig()));
    sysConfMenu->addAction("站点配置", this, SLOT(slot_siteConfig()));
    sysConfMenu->addAction("参数配置", this, SLOT(slot_argsConfig()));
    sysConfMenu->addAction("软件配置", this, SLOT(slot_softwareConfig()));

    ui->configBtn->setPopupMode(QToolButton::InstantPopup);
    ui->configBtn->setMenu(sysConfMenu);

    //历史数据菜单
    QMenu *hisDataMenu = new QMenu(this);
    hisDataMenu->addAction("数据诊断",this,SLOT(slot_dataCheck()));
    hisDataMenu->addAction("历史趋势",this,SLOT(slot_historyTrending()));
    hisDataMenu->addAction("横向分析",this,SLOT(slot_horizontalAnalysis()));

    ui->historyDataBtn->setPopupMode(QToolButton::InstantPopup);
    ui->historyDataBtn->setMenu(hisDataMenu);

    //报警信息
    QMenu * alarmMenu = new QMenu(this);
    alarmMenu->addAction("设备报警",this,SLOT(slot_deviceWarning()));
    alarmMenu->addAction("局放报警",this,SLOT(slot_dischargeWarning()));
    alarmMenu->addAction("震动报警",this,SLOT(slot_quakeWarning()));

    ui->alarmBtn->setPopupMode(QToolButton::InstantPopup);
    ui->alarmBtn->setMenu(alarmMenu);

    //系统帮助
    QMenu *helpMenu = new QMenu(this);
    helpMenu->addAction("系统信息",this,SLOT(slot_systemInfo()));
    helpMenu->addAction("使用说明",this,SLOT(slot_usage()));

    ui->helpBtn->setPopupMode(QToolButton::InstantPopup);
    ui->helpBtn->setMenu(helpMenu);
}

void MainPage::initArticle()
{
    //将内容区域放入堆叠窗体当中，内容区域所有的子窗体，都由Article类来统一控制
    m_pArticle = new Article(ui->articleWidget);
    m_pArticle->resize(ui->articleWidget->size());
    m_pArticle->show();
}

MainPage::~MainPage()
{
    delete ui;
}

void MainPage::slot_unitConfig()
{
    UnitConfig * uc = new UnitConfig();

    uc->show();
}

void MainPage::slot_siteConfig()
{
    SiteConfig * sc = new SiteConfig();
    sc->show();
}

void MainPage::slot_argsConfig()
{
    ArgsConfig * as = new ArgsConfig();
    as->show();
}

void MainPage::slot_softwareConfig()
{
    SoftwareConfig * sc = new SoftwareConfig();
    connect(sc,SIGNAL(okBtnClicked()),this,SLOT(slot_softwareConfigEffective()));
    sc->show();
}

void MainPage::slot_dataCheck()
{
    //数据诊断
    m_pArticle->changePage(9);
}

void MainPage::slot_historyTrending()
{
    //历史趋势
    m_pArticle->changePage(10);
}

void MainPage::slot_horizontalAnalysis()
{
    //横向分析
    m_pArticle->changePage(11);
}

void MainPage::slot_systemInfo()
{

}

void MainPage::slot_usage()
{

}

void MainPage::slot_deviceWarning()
{
    m_pArticle->changePage(3);
}

void MainPage::slot_dischargeWarning()
{
    m_pArticle->changePage(4);
}

void MainPage::slot_quakeWarning()
{
    m_pArticle->changePage(5);
}

void MainPage::slot_softwareConfigEffective()
{
    //站点配置生效
}

void MainPage::timerEvent(QTimerEvent *e)
{
    Q_UNUSED(e)
    QString timeStr = QDateTime::currentDateTime().toString("yyyy年MM月dd日 hh:mm:ss");
    ui->timeLabel->setText(timeStr);
}

void MainPage::on_statuBtn_clicked()
{
    m_pArticle->changePage(0);
}

void MainPage::on_currentDataBtn_clicked()
{
    m_pArticle->changePage(1);
}

void MainPage::on_historyDataBtn_clicked()
{
    m_pArticle->changePage(2);
}

void MainPage::on_alarmBtn_clicked()
{
    m_pArticle->changePage(3);
}

void MainPage::on_fingurePrintBtn_clicked()
{
    m_pArticle->changePage(6);
}

void MainPage::on_selfCheckBtn_clicked()
{
    m_pArticle->changePage(7);
}

void MainPage::on_userAdminBtn_clicked()
{
    m_pArticle->changePage(8);
}
