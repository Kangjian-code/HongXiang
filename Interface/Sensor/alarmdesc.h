#ifndef ALARMDESC_H
#define ALARMDESC_H
#include <QWidget>
#include <QTreeWidget>
#include "ThreeDog/tdtreewidget.h"
#include "ThreeDog/tdtoolbar.h"
#include "Common/myqheaderview.h"
#include "dao.h"
#include <QDebug>
#include <QChart>
#include <QChartView>
#include <QLineSeries>
#include <QSplineSeries>
#include <QPieSeries>
#include <QBarSet>
#include <QBarSeries>
#include <QBarCategoryAxis>
#include <QTableWidget>
#include <QHBoxLayout>
#include <QWidget>
#include "3D/base3dwidget.h"
using namespace QtCharts;
namespace Ui {
class AlarmDesc;
}

class AlarmDesc : public QWidget
{
	Q_OBJECT

public:
	explicit AlarmDesc(QWidget *parent = nullptr);
	void initTable();
	void initChart();
		void addSerial();
	~AlarmDesc();
public slots:
	void checkBoxClicked(bool b);
	void updateTable();

private:
	Ui::AlarmDesc *ui;
	QTableWidget * m_pTableWidget;
	QChart *chart;
	QList<QLineSeries *> m_series;
};

#endif // ALARMDESC_H
