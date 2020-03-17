/**************************************************************
 * File Name   : sensoritem.h
 * Author      : ThreeDog
 * Date        : Mon Apr 08 16:30:09 2019
 * Description : 监测点条目类
 * 需求：
 * 1、左边圆圈30*30像素颜色可配置
 * 2、圆圈上文字可设置
 * 3、圆角矩形，半径为15
 * 4、描边为蓝色2像素
 * 5、根据文字长度可伸缩
 * 6、设置固定长度，文字一旦超出此长度，点击后才显示
 * 7、用一个变量存储图片路径、鼠标进行某种操作时显示图片
 * 8、要能根据外部图的变化自动移动，即实现autoMove
 *
 **************************************************************/
#ifndef _SENSORITEM_H_ 
#define _SENSORITEM_H_

#include <QWidget>
#include <QDebug>
#include <QDialog>
#include <QPainter>
#include "DataModal.h"
#include "ThreeDog/tdpushbutton.h"
#include "ThreeDog/appinit.h"
#include "dao.h"
#include <QDebug>

//窗体上的每一个检测点
class SensorItem : public QWidget
{
    Q_OBJECT
public :
    explicit SensorItem(QSize size, QPoint pos,Sensor & s ,QWidget * parent = 0);
    void autoMove();                    //自动移动，调整自己的坐标位置
    void initInterface();
    void setMoveEnabel(bool enable);
    //预留外部接口：
    void setCircleColor(const QColor color);          //设置小圆点颜色
    void setCircleText(const QString text);           //设置圆圈文字
    void setMsgText(const QString text);              //设置显示的文字
    void setPos();
    ~SensorItem();
protected:
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    //在鼠标抬起事件中实现调用
    void mouseReleaseEvent(QMouseEvent *e);
private:
    TDPushButton * m_pPushButton;
    QLabel * m_pLabel;                   //底层label
    QLabel * m_pLeftCircle;             //左侧圆圈
    QLabel * m_pLeftText;               //左侧的文字：U | 噪 | 振
    QLabel * m_pMsg;                    //监测点的文字描述
    QString m_sSiteName;                //检测点名称
    QString m_sSpacingName;             //所属间隔名称
    QPixmap m_picPhoto;                 //监测点照片
    QPoint m_pointInitPos;              //检测点的初始坐标
    QSize m_sizeParentOriginalSize;     //父控件的初始大小
    int m_iAlarmLevel;                  //报警级别
    bool m_bMoveEnable;                 //是否可移动
    QPoint old_pos;
    bool is_press;
    Sensor m_sensor;                           //保存监测点的对象

};

#endif  //SENSORITEM
