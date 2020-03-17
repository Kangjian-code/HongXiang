/**************************************************************
 * File Name   : tablepage.h
 * Author      : ThreeDog
 * Date        : Fri Jan 18 18:02:51 2019
 * Description : 表格窗体，继承自模态框，作为模板页面，需要表格页面的地方，
 * 可以参照此界面进行编写。
 *
 **************************************************************/
#ifndef _TABLEPAGE_H_ 
#define _TABLEPAGE_H_ 
#include <QTableWidget>
#include <QHeaderView>
#include <QComboBox>
#include <QLineEdit>
#include "ThreeDog/tdmodal.h"
#include "ThreeDog/tdtoolbar.h"
#include "tableoperateitem.h"

class TablePage : public TDModal
{
public:
    explicit TablePage(QWidget * parent = 0);
    void initTable();
    void updateTable();
    ~TablePage();
private:
    QTableWidget * m_pTableWidget;
};

#endif  //TABLEPAGE
