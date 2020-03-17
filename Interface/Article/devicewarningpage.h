/**************************************************************
 * File Name   : devicewarningpage.h
 * Author      : ThreeDog
 * Date        : Fri Feb 15 22:01:42 2019
 * Description : 设备报警页面
 *  此页面报警信息分别为：  0:  正常
 *                      1：传感器未接入
 *                      2：采集报警异常
 *                      3：同步频率出错
 *                      4：同步源未连接
 *                      5：同步源连接但是与用户设置同步方式的不同
 * 此页面报警等级：不关心
 **************************************************************/

#ifndef DEVICEWARNINGPAGE_H
#define DEVICEWARNINGPAGE_H

#include <QWidget>
#include <QDateTime>
#include <QTableWidget>
#include <QHeaderView>
#include "Common/myqheaderview.h"
#include "dao.h"


namespace Ui {
class DeviceWarningPage;
}

class DeviceWarningPage : public QWidget
{
    Q_OBJECT

public:
    explicit DeviceWarningPage(QWidget *parent = 0);
    void initInterface();
    void initProperty();
    void initTable();
    ~DeviceWarningPage();

public slots:
    void checkBoxClicked(bool b);
    void updateTable();

private slots:
    void on_queryBtn_clicked();

private:
    Ui::DeviceWarningPage *ui;
    QTableWidget * m_pTableWidget;
    QMap<int,QString> typeMap;
};

#endif // DEVICEWARNINGPAGE_H
