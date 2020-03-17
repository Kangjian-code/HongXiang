/**************************************************************
 * File Name   : imageindex.h
 * Author      : ThreeDog
 * Date        : Mon Nov 05 21:11:08 2018
 * Description : 首页一次连接图的Demo版本， 需求：
 * 1、 图片放在滚动窗体中， 可以进行缩放
 * 2、 超出外窗体大小自动出现滚动条
 * 3、 滚轮进行图片的缩放
 * 4、 可以动态在图中添加坐标点
 * 5、 坐标点根据图像关系， 如果过于集中，则隐藏几个，只显示一个
 *
 **************************************************************/
#ifndef _IMAGEINDEX_H_
#define _IMAGEINDEX_H_
#include "ThreeDog/tdscrollarea.h"
#include "ThreeDog/tdpushbutton.h"
#include "ThreeDog/tdtoolbar.h"
#include "Common/sensoritem.h"
#include "DataModal.h"
#include "dao.h"
#include <QLabel>
#include <QWheelEvent>
#include <QTreeWidgetItem>

//滚动区域显示的的中心窗体
class ImageViewWidget : public QWidget
{
    Q_OBJECT
public :
    explicit ImageViewWidget(QString pic ,QWidget * parent = 0);
    ~ImageViewWidget();
    void moveMonitors();//缩放图片的同时，移动所有监测点的对应位置
    void scaleWidget(bool b = true);
    void addNewSensor(Sensor s);
    void generateSensor(QVector<Sensor> vect);  //通过数据库的查询结果生成监测点
    void setSensorMoveEnable(bool b);// 设置所有监测点是否可被鼠标拖动
    void resttingScale();//重置内部窗体的大小
protected:
    void mouseReleaseEvent(QMouseEvent *e);
private:
    QPixmap m_pic;
    QSize m_sizeOriginalSize;        //中心窗体的初始大小
    QLabel * centerLabel;
    QVector<SensorItem *> m_vecMonitors; //存放所有的监测点
};

//滚动区域
class ImageIndex : public TDScrollArea
{
    Q_OBJECT
public:
    explicit ImageIndex(QWidget * parent = 0);


    void addSensor(Sensor s);
    void setSensorsMoveEnable(bool b);        //设置所有监测点可被鼠标拖动
    void updateSensors();               //更新所有的监测点
    ~ImageIndex();
public slots:
    void slot_treeItemClicked(QTreeWidgetItem *item,int column);
    void scaleSubClicked();

    void scaleAddClicked();
    void posClicked();
protected:
    void wheelEvent(QWheelEvent * e);
private:
    void scaleWidget(bool b = true); //缩放图片,true为放大， false为缩小
    //    void calculImpact();             //检测碰撞。如果两个
    ImageViewWidget * m_pImageView;
    TDToolbar       * posBtn;
    TDPushButton    * btn1  ;
    TDPushButton    * btn2  ;

};

#endif  //IMAGEINDEX
