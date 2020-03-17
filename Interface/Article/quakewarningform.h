/**************************************************************
 * File Name   : quakewarningform.h
 * Author      : ThreeDog
 * Date        : Fri Feb 15 22:01:42 2019
 * Description : 震动报警页面
 *  此页面报警信息分别为： 0:  正常
 *                      1：传感器未接入
 *                      2：采集报警异常
 *                      3：同步频率出错
 *                      4：同步源未连接
 *                      5：同步源连接但是与用户设置同步方式的不同
 * 此页面报警等级：不关心
 **************************************************************/
#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif
#ifndef QUAKEWARNINGFORM_H
#define QUAKEWARNINGFORM_H

#include <QWidget>
#include <QDateTime>
#include <QTableWidget>
#include <QHeaderView>
#include "DataModal.h"
#include "dao.h"
#include "Common/myqheaderview.h"

namespace Ui {
class QuakeWarningForm;
}

class QuakeWarningForm : public QWidget
{
    Q_OBJECT

public:
    explicit QuakeWarningForm(QWidget *parent = 0);
    void initInterface();
    void initProperty();
    void initTable();
    ~QuakeWarningForm();

public slots:
    void updateTable();
    void checkBoxClicked(bool);

private:
    Ui::QuakeWarningForm *ui;
    QTableWidget * m_pTableWidget;
    QMap<int,QString> typeMap;
};

#endif // QUAKEWARNINGFORM_H
