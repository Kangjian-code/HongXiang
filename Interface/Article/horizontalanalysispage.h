#ifndef HORIZONTALANALYSISPAGE_H
#define HORIZONTALANALYSISPAGE_H

#include <QWidget>
#include <QTreeWidget>
#include "ThreeDog/tdtreewidget.h"
#include "ThreeDog/tdtoolbar.h"
#include "dao.h"
#include <QDebug>
#include "Common/chartform.h"

namespace Ui {
class HorizontalAnalysisPage;
}

class HorizontalAnalysisPage : public QWidget
{
	Q_OBJECT

public:
	explicit HorizontalAnalysisPage(QWidget *parent = 0);
	void initTreeView();                 //初始化左侧树状菜单
	void initLeftTabs();                 //初始化左侧栏
	void initChart();					//初始化chart区域
	~HorizontalAnalysisPage();
public slots:
	void hideLeft();
private:
	Ui::HorizontalAnalysisPage *ui;
	QTreeWidget * m_pTreeWidget;
	TDToolbar * m_pHideLeftBtn;
};

#endif // HORIZONTALANALYSISPAGE_H
