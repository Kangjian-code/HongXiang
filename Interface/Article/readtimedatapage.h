/**************************************************************
 * File Name   : readtimedatapage.h
 * Author      : ThreeDog
 * Date        : Fri Jan 11 22:29:01 2019
 * Description : 实时数据
 *
 **************************************************************/
#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#ifndef READTIMEDATAPAGE_H
#define READTIMEDATAPAGE_H

#include <QWidget>
#include <QDateTime>
#include "ThreeDog/tdtoolbar.h"

namespace Ui {
class ReadTimeDataPage;
}

class ReadTimeDataPage : public QWidget
{
    Q_OBJECT

public:
    explicit ReadTimeDataPage(QWidget *parent = 0);
    void initProperty();
    void initTable1();
    void initTable2();
    void initTable3();
    void updateTable1();
    void updateTable2();
    void updateTable3();
    ~ReadTimeDataPage();

private:
    Ui::ReadTimeDataPage *ui;
};

#endif // READTIMEDATAPAGE_H
