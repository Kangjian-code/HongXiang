#include "histroytrending.h"
#include "ui_histroytrending.h"

HistroyTrending::HistroyTrending(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::HistroyTrending)
{
	m_pTreeWidget = nullptr;
	ui->setupUi(this);

	ui->autoCheck->setProperty("author","ThreeDog");
	ui->anyTimeBox->setProperty("author","ThreeDog");
	ui->dateCombo->setProperty("author","ThreeDog");
	ui->dateEdit1->setProperty("author","ThreeDog");
	ui->searchBtn->setProperty("author","ThreeDog");
	ui->queryBtn->setProperty("author","ThreeDog");
	ui->searchEdit->setProperty("author","ThreeDog");
	ui->dateEdit2->setProperty("author","ThreeDog");

	initLeftTabs();
	initTreeView();
	initCharts();
}

void HistroyTrending::initTreeView()
{
	if(m_pTreeWidget == nullptr){
		m_pTreeWidget = new QTreeWidget(ui->leftWidget);
		m_pTreeWidget->setStyleSheet("background:rgba(81,149,202,1);color:#FFFFFF");
		m_pTreeWidget->setFixedSize(138,1005);
		m_pTreeWidget->header()->setStyleSheet("background:rgba(81,149,202,1);min-height:0px;max-height:0px");//重新编辑树状列表表头的样式
		m_pTreeWidget->setHeaderLabel("");
		m_pTreeWidget->setHeaderItem(nullptr);
	}
	m_pTreeWidget->clear();

	//获取并遍历所有的间隔
	for(auto spacing : Dao::getInstance()->QuerySpacing()){
		TDTreeWidgetItem *group = new TDTreeWidgetItem(m_pTreeWidget);
		group->setText(0, spacing.name);
		group->setId(spacing.id);
		group->setType(0);      //类型为0，间隔点
		//遍历此间隔下的所有监测点
		for(auto sensor : Dao::getInstance()->QuerySensorBySpacing(spacing.id)){
			TDTreeWidgetItem *subItem11 = new TDTreeWidgetItem(group);
			qDebug()<<"sensor_id:" << sensor.id;
			subItem11->setId(sensor.id);
			subItem11->setType(1);//类型为1，监测点
			subItem11->setText(0,sensor.name);
			subItem11->setCheckState(0, Qt::Checked);
		}
	}
	//临时测试用例
	//获取并遍历所有的间隔
	m_pTreeWidget->expandAll();
}

void HistroyTrending::initLeftTabs()
{
	m_pHideLeftBtn = new TDToolbar(":/img/index/left_open.png",":/img/index/left_close.png",this);
	m_pHideLeftBtn->move(154,472);
	connect(m_pHideLeftBtn,SIGNAL(clicked()),this,SLOT(hideLeft()));
}

void HistroyTrending::initCharts()
{
	QVBoxLayout *v = new QVBoxLayout;
	ui->chartArea->setLayout(v);

	ChartForm * cf = new ChartForm(this);
	v->addWidget(cf);
	ChartForm * cf2 = new ChartForm(this);
	v->addWidget(cf2);
	ChartForm * cf3 = new ChartForm(this);
	v->addWidget(cf3);

}

HistroyTrending::~HistroyTrending()
{

}

void HistroyTrending::hideLeft()
{
	//显示
	if(ui->leftWidget->isHidden()){
		ui->leftWidget->show();
		m_pHideLeftBtn->move(154,472);
		m_pHideLeftBtn->raise();
	}else{
		//隐藏
		ui->leftWidget->hide();
		m_pHideLeftBtn->move(0,472);
		m_pHideLeftBtn->raise();
	}
}
