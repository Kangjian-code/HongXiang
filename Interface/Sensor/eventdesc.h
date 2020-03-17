#ifndef EVENTDESC_H
#define EVENTDESC_H

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
#include "3D/base3dwidget.h"
using namespace QtCharts;
namespace Ui {
class eventDesc;
}

class eventDesc : public QWidget
{
	Q_OBJECT

public:
	explicit eventDesc(QWidget *parent = nullptr);
	void initTable();
	void addSerial();
	void initChart();
	~eventDesc();

public slots:
	void checkBoxClicked(bool b);
	void updateTable();

private:
	Ui::eventDesc *ui;
	QTableWidget * m_pTableWidget;
	QChart *chart;
	QList<QLineSeries *> m_series;
};

#endif // EVENTDESC_H
