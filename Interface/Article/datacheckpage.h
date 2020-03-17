#ifndef DATACHECKPAGE_H
#define DATACHECKPAGE_H

#include <QWidget>
#include <QTreeWidget>
#include "ThreeDog/tdtreewidget.h"
#include "ThreeDog/tdtoolbar.h"
#include "3D/base3dwidget.h"
#include "dao.h"
#include <QDebug>
#include <QChartView>
#include <QLineSeries>
#include <QSplineSeries>
#include <QPieSeries>
#include <QBarSet>
#include <QBarSeries>
#include <QBarCategoryAxis>
using namespace QtCharts;

namespace Ui {
class DataCheckPage;
}

class DataCheckPage : public QWidget
{
	Q_OBJECT

public:
	explicit DataCheckPage(QWidget *parent = 0);
	void initTreeView();                    //初始化左侧树状菜单
	void initLeftTabs();                 //初始化左侧栏
	void initChart();				//初始化主窗体部分
	void addSerial();
	void printSize();
	~DataCheckPage();
public slots:
	void hideLeft();
private:
	QList<QLineSeries *> m_series;
	QChart *chart;
	Ui::DataCheckPage *ui;
	QTreeWidget * m_pTreeWidget;
	TDToolbar * m_pHideLeftBtn;
};

#endif // DATACHECKPAGE_H
