/**************************************************************
 * File Name   : myqheaderview.cpp
 * Author      : ThreeDog 
 * Date        : Fri Feb 01 17:33:25 2019
 * Description : 自定义的表头，表头的第一格有一个复选框
 *
 **************************************************************/

#include "myqheaderview.h"

MyQHeaderView::MyQHeaderView(Qt::Orientation orientation, QWidget *parent)
    : QHeaderView(orientation, parent)
{
    isChecked = false;
}

/*
 *@brief:      获取复选框的状态
 *@return:     返回复选框的状态
 */
bool MyQHeaderView::boxIsChecked()
{
    return isChecked;
}

/*
 *@brief:      外部设置复选框的状态
 *@param:      checked:复选框的状态
 */
void MyQHeaderView::setChecked(bool checked)
{
    //如果设置复选框的状态与当前复选框状态不一致时
    if( checked != isChecked ) {
        //由于这个复选框是绘制出来的，所以通过模拟鼠标单击来改变复选框的状态
        QMouseEvent *event = new QMouseEvent(QEvent::MouseButtonPress,QPointF(0,0),Qt::LeftButton,Qt::NoButton,Qt::NoModifier);
        mousePressEvent(event);
    } else {    //一致时，发送个信号给外部使用
        emit signalStateTrange(isChecked);
    }
}

/*
 *@brief:      绘制复选框
 *@date:       2018.09.12
 */
void MyQHeaderView::paintSection(QPainter *painter, const QRect &rect, int logicalIndex) const
{
    painter->save();
    QHeaderView::paintSection(painter, rect, logicalIndex);
    painter->restore();
    if( logicalIndex == 0 ) {	//表头第一个位置绘制复选框
        QStyleOptionButton option;
        option.rect = QRect(10, 10, 10, 10);
        if ( isChecked ) {
            option.state = QStyle::State_On;
        } else {
            option.state = QStyle::State_Off;
        }
        QCheckBox checkBox;
        option.iconSize = QSize(20, 20);
        option.rect = rect;

        style()->drawPrimitive(QStyle::PE_IndicatorCheckBox, &option, painter, &checkBox);
    }
}

/*
 *@brief:      鼠标按下事件，改变复选框的状态
 *@date:       2018.09.12
 */
void MyQHeaderView::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        int index = logicalIndexAt(event->pos());
        if( index == 0 ) {
            if( isChecked ) {
                isChecked = false;
            } else {
                isChecked = true;
            }
            emit signalStateTrange(isChecked);
        }
    }
    this->update();
    QHeaderView::mousePressEvent(event);
}

/*
 *@brief:      鼠标双击事件，为提高复选框响应频率
 *@date:       2018.09.12
 */
void MyQHeaderView::mouseDoubleClickEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        //获取点击表头的标签号
        int index = logicalIndexAt(event->pos());
        if( index == 0 ) {
            if( isChecked ) {
                isChecked = false;
            } else {
                isChecked = true;
            }
            emit signalStateTrange(isChecked);
        }
    }
    this->update();
    QHeaderView::mouseDoubleClickEvent(event);
}
