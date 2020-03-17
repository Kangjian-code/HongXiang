/**************************************************************
 * File Name   : myqheaderview.h
 * Author      : ThreeDog
 * Date        : Fri Feb 01 17:33:25 2019
 * Description : 自定义的表头，表头的第一格有一个复选框
 *
 **************************************************************/
#ifndef _MYQHEADERVIEW_H_ 
#define _MYQHEADERVIEW_H_ 

#include<QtWidgets>

class MyQHeaderView : public QHeaderView
{
    Q_OBJECT
public:
    MyQHeaderView(Qt::Orientation orientation, QWidget * parent = 0);
    bool boxIsChecked();//判断复选框是否被选中
    void setChecked(bool checked);//设置复选框的状态

signals:
    void signalStateTrange(bool isChecked);	//复选框状态改变信号

protected:
    void paintSection(QPainter *painter, const QRect &rect, int logicalIndex) const;	//绘制复选框
    void mousePressEvent(QMouseEvent *event);	//重写鼠标按下方法，改变复选框状态
    void mouseDoubleClickEvent(QMouseEvent *event);	//增加对鼠标双击事件处理，增加对复选框状态改变的响应速度

private:
    bool isChecked;	//记录复选框的状态


};

#endif // _MYQHEADERVIEW_H_
