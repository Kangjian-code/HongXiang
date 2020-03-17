/**************************************************************
 * File Name   : sensoritem.cpp
 * Author      : ThreeDog
 * Date        : Mon Apr 08 16:30:09 2019
 * Description : 监测点当前信息
 *
 **************************************************************/

#include "sensoritem.h"
SensorItem::SensorItem(QSize size, QPoint pos, Sensor & s, QWidget *parent)
    :QWidget(parent)
{
    this->m_sensor = s;
    //在底层铺一个Label
    this->m_pLabel = new QLabel(this);
    m_pLabel->resize(96,32);
    m_pLabel->move(0,0);
    m_pLabel->setStyleSheet("background: #FFFFFF ;border:2px solid #189AFF; border-radius:16px");
    this->resize(96,32);
    m_pLeftCircle = new QLabel(m_pLabel);
    m_pLeftCircle->resize(28,28);
    m_pLeftCircle->move(2,2);
    m_pLeftCircle->setStyleSheet("background:#6FD55C ; border-radius:14px;border:0px;");

    // 小圆圈上的文字
    if(s.type == 0){
        m_pLeftText = new QLabel("U",m_pLeftCircle);
        m_pLeftText->move(6,2);
    }else if(s.type == 1){
        m_pLeftText = new QLabel("噪",m_pLeftCircle);
        m_pLeftText->move(4,0);
    }else if(s.type == 2){
        m_pLeftText = new QLabel("振",m_pLeftCircle);
        m_pLeftText->move(4,0);
    }

    m_pMsg = new QLabel(s.name,m_pLabel);
    m_pMsg->move(35,4);
    m_pLeftText->setStyleSheet("background:none;color:#FFFFFF;font-size:20px;border:none");
    m_pMsg->setStyleSheet("background:none;font-size:14px;color:#262626;border:none");

    this->m_sizeParentOriginalSize = size;
    this->m_pointInitPos = pos;
    this->installEventFilter(AppInit::Instance());
    this->m_bMoveEnable = true;
}

void SensorItem::autoMove()
{
    double rate = (double)((double)this->parentWidget()->width() /(double)this->m_sizeParentOriginalSize.width());
    int x = this->m_pointInitPos.x() * rate;
    int y = this->m_pointInitPos.y() * rate;
    this->move(x,y);
}

void SensorItem::setMoveEnabel(bool enable)
{
    this->m_bMoveEnable = enable;
}

void SensorItem::setCircleColor(const QColor color)
{
    QString style = QString("background:%1 ; border-radius:14px;border:0px;").arg(color.name());
    this->m_pLeftCircle->setStyleSheet(style);
}

void SensorItem::setCircleText(const QString text)
{
    this->m_pLeftText->setText(text);
}

void SensorItem::setMsgText(const QString text)
{
    this->m_pMsg->setText(text);
    this->m_sensor.name = text;
}

void SensorItem::setPos()
{
    Dao::getInstance()->updateSensorPos(this->m_sensor.id, m_pointInitPos.x(), m_pointInitPos.y());//数据库中更新节点的信息
}

void SensorItem::mousePressEvent(QMouseEvent *e)
{
    //在可用状态下才触发
    if(this->isEnabled()){
        //旧的鼠标相对于本窗体的位置
        if(m_bMoveEnable){
            old_pos = e->pos();
            is_press = true;
        }
    }
}

void SensorItem::mouseMoveEvent(QMouseEvent *e)
{
    if(is_press && m_bMoveEnable && this->isEnabled()){
        //窗体之前的位置，加上鼠标相对于本窗体的位置，再减去鼠标按下之前相对于本窗体的位置。
        this->move(this->pos() + e->pos() - old_pos);
    }
}

void SensorItem ::mouseReleaseEvent(QMouseEvent *e)
{
    if(this->isEnabled()){
        //在鼠标抬起事件中实现调用（caller 和 func_ptr不能为空）
        if(m_bMoveEnable){
            is_press = false;
            m_pointInitPos = this->pos();
        }
    }
}

SensorItem::~SensorItem()
{

}
