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
#include "imageindex.h"
#include <QDebug>

ImageIndex::ImageIndex(QWidget * parent)
    :TDScrollArea(parent)
{
    m_pImageView = new ImageViewWidget("123",this);
    this->setWidget(m_pImageView);

    posBtn = new TDToolbar(":/img/index/position_close.png",":/img/index/position_open.png",this);
    connect(posBtn,SIGNAL(clicked()),this,SLOT(posClicked()));
//    posBtn->setCallback(this,my_selector(posClicked));
    posBtn->move(1650,480);
    posBtn->show();
    btn1 = new TDPushButton(":/img/index/scale_add.png",":/img/index/scale_add.png",":/img/index/scale_add.png",this);
    connect(btn1,SIGNAL(clicked()),this,SLOT(scaleAddClicked()));
//    btn1->setCallback(this,my_selector(scaleAddClicked));
    btn1->move(1650,520);
    btn1->show();
    btn2 = new TDPushButton(":/img/index/scale_sub.png",":/img/index/scale_sub.png",":/img/index/scale_sub.png",this);
    connect(btn2,SIGNAL(clicked()),this,SLOT(scaleSubClicked()));
//    btn2->setCallback(this,my_selector(scaleSubClicked));
    btn2->move(1650,552);
    btn2->show();
}

void ImageIndex::posClicked()
{
    //设置窗体可移动，先把底层一次接线图重置为原大小
    this->m_pImageView->resttingScale();

    if(this->posBtn->isChecked()){
        this->m_pImageView->setSensorMoveEnable(true);
    }else{
        this->m_pImageView->setSensorMoveEnable(false);
    }
}

void ImageIndex::scaleAddClicked()
{
    this->scaleWidget(true);
}

void ImageIndex::scaleSubClicked()
{
    this->scaleWidget(false);
}

void ImageIndex::addSensor(Sensor s)
{
    this->m_pImageView->addNewSensor(s);
}

void ImageIndex::setSensorsMoveEnable(bool b)
{
    //改变左下角编辑位置按钮的状态
    posBtn->setChecked(b);
    this->m_pImageView->setSensorMoveEnable(b);
}

void ImageIndex::updateSensors()
{
    this->m_pImageView->generateSensor(Dao::getInstance()->QuerySensors());
}

ImageIndex::~ImageIndex()
{

}

void ImageIndex::slot_treeItemClicked(QTreeWidgetItem *item, int column)
{
//    qDebug()<<item->text(column);
    //在这里实现新添加对应坐标点的代码
}

void ImageIndex::wheelEvent(QWheelEvent *e)
{
    TDScrollArea::wheelEvent(e);
////    2019/3/17:采用按钮缩放而非滚轮缩放。
//    scaleWidget((e->delta() > 0));
}

void ImageIndex::scaleWidget(bool b)
{
    this->m_pImageView->scaleWidget(b);
    this->refreshSlider();
}

ImageViewWidget::ImageViewWidget(QString pic ,QWidget *parent)
    :QWidget(parent)
{
    if(pic == ""){
//        m_pic.load(":/img/gb.jpg");
        // m_pic.load(pic);
        centerLabel = new QLabel(this);
//        this->m_sizeOriginalSize = m_pic.size();
        centerLabel->resize(100,100);
//        centerLabel->setPixmap(m_pic);
        this->resize(centerLabel->size());
    }else{
        m_pic.load(":/img/gb.jpg");
        // m_pic.load(pic);
        centerLabel = new QLabel(this);
        this->m_sizeOriginalSize = m_pic.size();
        centerLabel->resize(m_pic.size());
        centerLabel->setPixmap(m_pic);
        this->resize(centerLabel->size());
    }
    generateSensor(Dao::getInstance()->QuerySensors());
}

ImageViewWidget::~ImageViewWidget()
{
    if(!m_vecMonitors.isEmpty()){
        for(auto * item : m_vecMonitors){
            item -> close();
            delete item;
        }
        m_vecMonitors.clear();
    }
}

void ImageViewWidget::moveMonitors()
{
    foreach(SensorItem * item,m_vecMonitors){
        item->autoMove();
    }
}

void ImageViewWidget::scaleWidget(bool b)
{
    if(this->m_pic.isNull())
        return ;
    if(b){//放大
        if( this->width() >= m_sizeOriginalSize.width() &&
                 this->height() >= m_sizeOriginalSize.height()){
            return ;
        }
        else{
            if(this->width() * 1.1 > this->m_sizeOriginalSize.width())
                this->resize(this->m_sizeOriginalSize);
            else
                this->resize(this->width() * 1.1,this->height() * 1.1);
            QPixmap pic = m_pic.scaled(this->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation);
            centerLabel->resize(pic.size());
            centerLabel->setPixmap(pic);
            moveMonitors();//调节完图像大小，调节所有监测点位置
        }

    }else{
        //小于0 是缩小
        int w = this->width();
        int h = this->height();
        this->resize(w * 0.9,h * 0.9);
        QPixmap pic;
        pic = m_pic.scaled(this->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation);
        centerLabel->resize(pic.size());
        centerLabel->setPixmap(pic);
        moveMonitors();
    }
}

void ImageViewWidget::addNewSensor(Sensor s)
{
    QPoint pos(s.site_x,s.site_y);
    //在屏幕上生成监测点
    SensorItem * item = new SensorItem(this->m_sizeOriginalSize,pos,s,this);
    item->setMoveEnabel(false);
    item->move(pos);
    item->show();
    m_vecMonitors.append(item);
}

void ImageViewWidget::generateSensor(QVector<Sensor> vect)
{
    if(vect.isEmpty())
        return ;
    //先把现有的点全部删除，然后再添加
    if(!m_vecMonitors.isEmpty()){
        for(auto * item : m_vecMonitors){
            item -> close();
            delete item;
        }
        m_vecMonitors.clear();
    }
    this->resttingScale();
    //添加监测点
    for(Sensor s : vect){
        this->addNewSensor(s);
    }
}

void ImageViewWidget::setSensorMoveEnable(bool b)
{
    for(SensorItem *sensor : m_vecMonitors){
        if(!b){
            //设置所有的小控件不可移动，在此之前更新所有控件的位置信息
            sensor->setPos();//更新控件的位置信息，位置由控件自己获取
        }
        sensor->setMoveEnabel(b);
    }
}

void ImageViewWidget::resttingScale()
{
    this->resize(this->m_sizeOriginalSize);
    centerLabel->resize(m_pic.size());
    centerLabel->setPixmap(m_pic);
    moveMonitors();//调节完图像大小，调节所有监测点位置
}

void ImageViewWidget::mouseReleaseEvent(QMouseEvent *e)
{
//    SensorItem * item = new SensorItem(this->m_sizeOriginalSize,e->pos(),this);
//    item->move(e->x()-15,e->y()-15);
//    item->show();
//    m_vecMonitors.append(item);
}
