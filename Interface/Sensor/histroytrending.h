#ifndef HISTROYTRENDING_H
#define HISTROYTRENDING_H

#include <QWidget>
#include <QTreeWidget>
#include "ThreeDog/tdtreewidget.h"
#include "ThreeDog/tdtoolbar.h"
#include "Common/chartform.h"
#include "dao.h"
#include <QDebug>

namespace Ui {
class HistroyTrending;
}

class HistroyTrending : public QWidget
{
	Q_OBJECT

public:
	explicit HistroyTrending(QWidget *parent = 0);
	void initTreeView();                    //初始化左侧树状菜单
	void initLeftTabs();					//初始化左侧栏
	void initCharts();						//初始化图表
	~HistroyTrending();

public slots:
	void hideLeft();

private:
	Ui::HistroyTrending *ui;
	QTreeWidget * m_pTreeWidget;
	TDToolbar * m_pHideLeftBtn;
};

#endif // HISTROYTRENDING_H
