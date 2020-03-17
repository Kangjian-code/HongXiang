#include "chartform.h"
#include "ui_chartform.h"

ChartForm::ChartForm(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::ChartForm)
{
	ui->setupUi(this);
	ui->avgBox->setProperty("author","ThreeDog");
	ui->chargeBox->setProperty("author","ThreeDog");
	ui->maxBox->setProperty("author","ThreeDog");
	ui->maxButton->setProperty("author","ThreeDog");
	ui->minButton->setProperty("author","ThreeDog");
	ui->moveButton->setProperty("author","ThreeDog");
	ui->reportButton->setProperty("author","ThreeDog");
	this->initChart();
}

void ChartForm::initChart()
{
	// 初始化图表
	chart = new QChart();
	addSerial();
	addSerial();
	addSerial();
	addSerial();
	ui->chartView->setChart(chart);
}

void ChartForm::addSerial()
{
	QLineSeries *series = new QLineSeries();
	m_series.append(series);

	series->setName(QString("line " + QString::number(m_series.count())));

	// Make some sine wave for data
	QList<QPointF> data;
	int offset = chart->series().count();
	for (int i = 0; i < 3600; i++) {
		qreal x = offset * 20 + i;
		data.append(QPointF(i, qSin(2.0 * 3.141592 * x / 360.0)));
	}

	series->append(data);
	chart->addSeries(series);

	if (m_series.count() == 1) {
		chart->createDefaultAxes();
	}
}

ChartForm::~ChartForm()
{
	delete ui;
}
