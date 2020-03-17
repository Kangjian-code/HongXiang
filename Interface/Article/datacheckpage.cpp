#include "datacheckpage.h"
#include "ui_datacheckpage.h"

DataCheckPage::DataCheckPage(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::DataCheckPage)
{
	m_pTreeWidget = nullptr;
	ui->setupUi(this);
	initLeftTabs();
	initTreeView();
	initChart();
}

void DataCheckPage::initTreeView()
{
	if(m_pTreeWidget == nullptr){
		m_pTreeWidget = new QTreeWidget(ui->leftWidget);
		//        connect(m_pTreeWidget,SIGNAL(itemPressed(QTreeWidgetItem*,int)),this,SLOT(slot_treeItemClicked(QTreeWidgetItem*,int)));
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
			//            subItem11->setFlags(Qt::ItemIsUserCheckable /*| Qt::ItemIsEnabled | Qt::ItemIsSelectable*/);
			subItem11->setText(0,sensor.name);
			subItem11->setCheckState(0, Qt::Checked);
		}
	}
	//临时测试用例
	//获取并遍历所有的间隔
	m_pTreeWidget->expandAll();
}

void DataCheckPage::initLeftTabs()
{
	m_pHideLeftBtn = new TDToolbar(":/img/index/left_open.png",":/img/index/left_close.png",this);
	m_pHideLeftBtn->move(154,472);
	connect(m_pHideLeftBtn,SIGNAL(clicked()),this,SLOT(hideLeft()));
}

void DataCheckPage::initChart()
{
	ui->startTimeEidt->setProperty("author","ThreeDog");
	ui->endTimeEdit->setProperty("author","ThreeDog");
	ui->comboBox->setProperty("author","ThreeDog");



	// 初始化图表
	chart = new QChart();
	addSerial();
	addSerial();
	addSerial();
	addSerial();
//	//构建折现系列对象
//	QSplineSeries *series = new QSplineSeries();
//	for (quint32 i = 0; i < 100; i++) {
//		series->append(i, sin(0.6f*i));
//	}
//	//将一系列折现点添加到图表中
//	chart->addSeries(series);
//	chart->createDefaultAxes();        // 基于已添加到图表的 series 来创建默认的坐标轴
//	//将图表绑定到视图
	ui->chartView1->setChart(chart);


	//饼图
	/*
	QPieSeries *series = new QPieSeries();
	series->append("10%", 1);
	series->append("20%", 2);
	series->append("70%", 7);
	series->setLabelsVisible();

	QPieSlice *slice_red =series->slices().at(0);
	QPieSlice *slice_green =series->slices().at(1);
	QPieSlice *slice_blue =series->slices().at(2);
	slice_red->setColor(QColor(255,0,0,255));
	slice_green->setColor(QColor(0,255,0,255));
	slice_blue->setColor(QColor(0,0,255,255));

	QChart *chart2 = new QChart();
	chart2->addSeries(series);
	chart2->setTitle("PieChart Example");
	chart2->legend()->hide();
	*/

	Base3DWidget * base3D = new Base3DWidget(true,ui->chart2);
	base3D->setFixedSize(863,429);
	base3D->show();
	base3D->resize(ui->chart2->size());
	base3D->move(0,0);

	QBarSet *set0 = new QBarSet("Jane");
	QBarSet *set1 = new QBarSet("John");
	QBarSet *set2 = new QBarSet("Axel");
	QBarSet *set3 = new QBarSet("Mary");
	QBarSet *set4 = new QBarSet("Samantha");

	*set0 << 1 << 2 << 3 << 4 << 5 << 6;// 名字为 Jane 竖条的 6个值 （分别代表6个月的值）
	*set1 << 5 << 0 << 0 << 4 << 0 << 7;
	*set2 << 3 << 5 << 8 << 19<< 8 << 5;
	*set3 << 5 << 6 << 7 << 3 << 4 << 5;
	*set4 << 9 << 7 << 5 << 3 << 1 << 2;


	QBarSeries *series2 = new QBarSeries();
	series2->append(set0);
	series2->append(set1);
	series2->append(set2);
	series2->append(set3);
	series2->append(set4);
	//把上面5个人的 6个月的值放到 series 待会显示

	QChart *chart3 = new QChart();
	chart3->addSeries(series2);
	chart3->setTitle("Simple barchart example");
	chart3->setAnimationOptions(QChart::SeriesAnimations);
	//![3] //![4]
	QStringList categories;
	categories << "Jan" << "Feb" << "Mar" << "Apr" << "May" << "Jun";
	QBarCategoryAxis *axis = new QBarCategoryAxis();
	axis->append(categories);
	chart3->createDefaultAxes();//创建默认的左侧的坐标轴（根据 QBarSet 设置的值）
	chart3->setAxisX(axis, series2);//设置坐标轴 //![4] //![5]
	chart3->legend()->setVisible(true); //设置图例为显示状态
	chart3->legend()->setAlignment(Qt::AlignBottom);//设置图例的显示位置在底部
	ui->chartView3->setChart(chart3);
	ui->chartView3->setRenderHint(QPainter::Antialiasing);

}

void DataCheckPage::addSerial()
{

	QLineSeries *series = new QLineSeries();
	m_series.append(series);

	series->setName(QString("line " + QString::number(m_series.count())));

	// Make some sine wave for data
	QList<QPointF> data;
	int offset = chart->series().count();
	for (int i = 0; i < 360; i++) {
		qreal x = offset * 20 + i;
		data.append(QPointF(i, qSin(2.0 * 3.141592 * x / 360.0)));
	}

	series->append(data);
	chart->addSeries(series);

	if (m_series.count() == 1) {
		chart->createDefaultAxes();
	}
}

void DataCheckPage::printSize()
{
	qDebug()<<this->ui->chart2->size();
}

DataCheckPage::~DataCheckPage()
{
	delete ui;
}

void DataCheckPage::hideLeft()
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
