/**************************************************************
 * File Name   : tdtreewidget.h
 * Author      : ThreeDog
 * Date        : Thu Apr 11 14:15:35 2019
 * Description : 重新封装一下树状列表，添加上右键菜单的逻辑
 *
 **************************************************************/
#ifndef _TDTREEWIDGET_H_ 
#define _TDTREEWIDGET_H_ 
#include <QTreeWidgetItem>

class TDTreeWidgetItem : public QTreeWidgetItem
{
public:
    explicit TDTreeWidgetItem(QTreeWidget *view, int type = Type);
    explicit TDTreeWidgetItem(QTreeWidgetItem *parent, int type = Type);
    void setType(const int t);
    void setId(const int id);
    int getId();
    int getType();
    ~TDTreeWidgetItem();
private:
    int id; //此item记录的数据库表中的id
    int type;//标识是间隔还是监测点、规定：0是间隔、1是检测点
};

#endif  //TDTREEWIDGET
