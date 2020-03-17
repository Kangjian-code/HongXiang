/**************************************************************
 * File Name   : historydatapage.h
 * Author      : ThreeDog
 * Date        : Fri Jan 11 22:29:01 2019
 * Description : 历史数据
 *
 **************************************************************/
#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#ifndef HISTORYDATAPAGE_H
#define HISTORYDATAPAGE_H

#include <QWidget>
#include "ThreeDog/tdtoolbar.h"

namespace Ui {
class HistoryDataPage;
}

class HistoryDataPage : public QWidget
{
    Q_OBJECT

public:
    explicit HistoryDataPage(QWidget *parent = 0);
    void initLeftTabs();    //初始化左侧栏

    ~HistoryDataPage();
public slots:
    void hideLeft();        //隐藏左侧栏
private:
    Ui::HistoryDataPage *ui;
    TDToolbar * m_pHideLeftBtn;
};

#endif // HISTORYDATAPAGE_H
