#include "alarmdesc.h"
#include "ui_alarmdesc.h"

AlarmDesc::AlarmDesc(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::AlarmDesc)
{
	ui->setupUi(this);


	ui->startTimeEdit->setProperty("author","ThreeDog");
	ui->endTimeEdit->setProperty("author","ThreeDog");
	ui->queryBtn->setProperty("author","ThreeDog");
	ui->exportBtn->setProperty("author","ThreeDog");
	ui->resetBtn->setProperty("author","ThreeDog");

	this->initTable();
	this->initChart();
}

void AlarmDesc::initTable()
{
	m_pTableWidget = new QTableWidget(ui->tableArea);
	QHBoxLayout *hLayout = new QHBoxLayout;
	ui->tableArea->setLayout(hLayout);
	hLayout->addWidget(m_pTableWidget);

	m_pTableWidget->setColumnCount(4);

	QStringList headText;
	headText << "" << "报警时间" << "报警描述" << "操作" ;
	m_pTableWidget->setHorizontalHeaderLabels(headText);
	//首先定义一个复选框表头
	MyQHeaderView *updateHeader = new MyQHeaderView(Qt::Horizontal,m_pTableWidget);
	//表头的复选框被点击的事件：
	connect(updateHeader,SIGNAL(signalStateTrange(bool)),this,SLOT(checkBoxClicked(bool)));
	//其次设置表格的表头
	m_pTableWidget->setHorizontalHeader(updateHeader);
	m_pTableWidget->setColumnWidth(0,88);
	m_pTableWidget->setColumnWidth(1,230);
	m_pTableWidget->setColumnWidth(2,230);
	m_pTableWidget->setColumnWidth(3,230);


	m_pTableWidget->verticalHeader()->setDefaultSectionSize(40);

	m_pTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
	m_pTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
	m_pTableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
	m_pTableWidget->setAlternatingRowColors(true);
	m_pTableWidget->verticalHeader()->setVisible(false);
	m_pTableWidget->horizontalHeader()->setStretchLastSection(true);

	//更新表格中的数据
	updateTable();
}

void AlarmDesc::initChart()
{


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

	Base3DWidget * base3D = new Base3DWidget(false,ui->chart2);
	base3D->setFixedSize(423,457);
	base3D->show();
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

void AlarmDesc::addSerial()
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

AlarmDesc::~AlarmDesc()
{
	delete ui;
}

void AlarmDesc::checkBoxClicked(bool b)
{
	if(b){
		qDebug()<<"打开所有的复选框";
		foreach(QCheckBox * check,this->m_pTableWidget->findChildren<QCheckBox *>()){
			check->setChecked(true);
		}
	}else{
		qDebug()<<"关闭所有的复选框";
		foreach(QCheckBox * check,this->m_pTableWidget->findChildren<QCheckBox *>()){
			check->setChecked(false);
		}
	}
}

void AlarmDesc::updateTable()
{
	//设备报警数据，根据条件从数据库查询结果，显示在界面上
	QString startTime = ui->startTimeEdit->dateTime().toString("yyyy-MM-dd hh:mm:ss");
	QString endTime   = ui->endTimeEdit->dateTime().toString("yyyy-MM-dd hh:mm:ss");

	QVector<SensorDeviceAlarm> vect = Dao::getInstance()->QueryDeviceWarning(startTime,endTime,0);
	for(int i = 0 ; i < vect.count() ; i++){
		m_pTableWidget->setRowHeight(i, 40);
		SensorDeviceAlarm alarm = vect.at(i);
		QWidget * w = new QWidget(m_pTableWidget);
		QHBoxLayout * h = new QHBoxLayout;
		w->setLayout(h);
		h->setContentsMargins(10,3,10,3);
		h->addStretch();
		QCheckBox * check = new QCheckBox;
		check->setObjectName("QCheckBox");
		check->setProperty("id",vect.at(i).id);
		h->addWidget(check);
		h->addStretch();

		this->m_pTableWidget->setCellWidget(i,0,w);

		QTableWidgetItem *item1 = new QTableWidgetItem(alarm.alarmTime);
		QTableWidgetItem *item2 = new QTableWidgetItem(alarm.alarmDesc);

		QWidget * w2 = new QWidget(m_pTableWidget);
		QHBoxLayout * h2 = new QHBoxLayout;
		w2->setLayout(h2);
		h2->setContentsMargins(10,3,10,3);
		h2->addStretch();
		QPushButton * btn = new QPushButton("复归",this);

		btn->setObjectName("subButton");
		btn->setStyleSheet("width:90px;\
						   height:30px;\
						   max-width:90px;\
						   max-height:30px;\
						   min-width:60px;\
						   min-height:30px;");
		h2->addWidget(btn);
		h2->addStretch();
		btn->setProperty("id",vect.at(i).id);
		btn->setProperty("action","复归");

		QPushButton * btn2 = new QPushButton("上传",this);
		btn2->setObjectName("subButton");
		btn2->setStyleSheet("width:90px;\
							height:30px;\
							max-width:90px;\
							max-height:30px;\
							min-width:60px;\
							min-height:30px;");
		h2->addWidget(btn2);
		h2->addStretch();

		btn2->setProperty("id",vect.at(i).id);
		btn2->setProperty("action","上传");
		this->m_pTableWidget->setCellWidget(i,3,w2);

		item1->setTextAlignment(Qt::AlignCenter);
		item2->setTextAlignment(Qt::AlignCenter);

		m_pTableWidget->setItem(i, 1, item1);
		m_pTableWidget->setItem(i, 2, item2);
	}

}
