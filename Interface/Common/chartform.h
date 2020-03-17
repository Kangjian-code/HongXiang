#ifndef CHARTFORM_H
#define CHARTFORM_H

#include <QWidget>
#include <QChartView>
#include <QLineSeries>
#include <QtMath>
namespace Ui {
class ChartForm;
}
using namespace QtCharts;
class ChartForm : public QWidget
{
	Q_OBJECT

public:
	explicit ChartForm(QWidget *parent = 0);
	void initChart();//初始化图表
	void addSerial();//添加一条线
	~ChartForm();

private:
	Ui::ChartForm *ui;
	QChart * chart;
	QList<QLineSeries *> m_series;
};

#endif // CHARTFORM_H
