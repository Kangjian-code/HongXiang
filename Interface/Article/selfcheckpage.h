/**************************************************************
 * File Name   : selfcheckpage.h
 * Author      : ThreeDog
 * Date        : Fri Jan 11 22:29:01 2019
 * Description : 自检
 *
 **************************************************************/
#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#ifndef SELFCHECKPAGE_H
#define SELFCHECKPAGE_H

#include <QWidget>
#include "ThreeDog/tdtoolbar.h"
#include <QTableWidget>
#include <QDateTime>

namespace Ui {
class SelfCheckPage;
}

class SelfCheckPage : public QWidget
{
    Q_OBJECT

public:
    explicit SelfCheckPage(QWidget *parent = 0);
    void initTable();
    void updateTable();
    ~SelfCheckPage();

private:
    QTableWidget * m_pTableWidget;
    Ui::SelfCheckPage *ui;
};

#endif // SELFCHECKPAGE_H
