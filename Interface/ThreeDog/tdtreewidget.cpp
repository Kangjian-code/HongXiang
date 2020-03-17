/**************************************************************
 * File Name   : tdtreewidget.cpp
 * Author      : ThreeDog 
 * Date        : Thu Apr 11 14:15:35 2019
 * Description : 重新封装一下树状列表，添加上右键菜单的逻辑
 *
 **************************************************************/

#include "tdtreewidget.h"

TDTreeWidgetItem::TDTreeWidgetItem(QTreeWidget *view, int type)
    :QTreeWidgetItem(view,type)
{
    this->id = 0;
    this->type = 0;
}

TDTreeWidgetItem::TDTreeWidgetItem(QTreeWidgetItem *parent, int type)
    :QTreeWidgetItem(parent,type)
{
    this->id = 0;
    this->type = 0;
}

TDTreeWidgetItem::~TDTreeWidgetItem()
{

}


void TDTreeWidgetItem::setType(const int t)
{
    this->type = t;
}

void TDTreeWidgetItem::setId(const int id)
{
    this->id = id ;
}

int TDTreeWidgetItem::getId()
{
    return this->id;
}

int TDTreeWidgetItem::getType()
{
    return this->type;
}
