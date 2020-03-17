/**************************************************************
 * File Name   : dischargewarningform.h
 * Author      : ThreeDog
 * Date        : Fri Feb 15 22:01:42 2019
 * Description : 局放报警页面
 *  此页面报警信息分别为： 0:  正常
 *                      1：自由金属颗粒
 *                      2：尖端放电
 *                      3：悬浮放电
 *                      4：沿面放电
 *                      5：内部放电
 * 此页面报警等级：0：正常
 *              1：轻微放电
 *              2：放电明显
 **************************************************************/

#ifndef DISCHARGEWARNINGFORM_H
#define DISCHARGEWARNINGFORM_H

#include <QWidget>
#include <QDateTime>
#include <QTableWidget>
#include <QHeaderView>
#include "DataModal.h"
#include "dao.h"
#include "Common/myqheaderview.h"

namespace Ui {
class DischargeWarningForm;
}

class DischargeWarningForm : public QWidget
{
    Q_OBJECT

public:
    explicit DischargeWarningForm(QWidget *parent = 0);
    void initInterface();
    void initProperty();
    void initTable();
    ~DischargeWarningForm();

public slots:
    void updateTable();
    void checkBoxClicked(bool);

private:
    Ui::DischargeWarningForm *ui;
    QTableWidget * m_pTableWidget;
    QMap<int,QString> typeMap;
    QMap<int,QString> levelMap;

};

#endif // DISCHARGEWARNINGFORM_H
