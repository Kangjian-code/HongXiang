/**************************************************************
 * File Name   : dao.h
 * Author      : ThreeDog
 * Date        : Mon Mar 18 18:54:52 2019
 * Description : 数据库连接类，单例模式，全局使用一个数据库连接
 *
 **************************************************************/
#ifndef _DAO_H_
#define _DAO_H_
#if _MSC_BUILD
#pragma execution_character_set("utf-8")
#endif

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
#include <QDateTime>
#include <QDateTime>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <ctime>
#include <QApplication>
#include "ThreeDog/tdmessagebox.h"
#include "DataModal.h"
#define CONFIGFILE "database.json"
class Dao
{
public:
	static Dao * getInstance();
	static Dao * self;
	int getId();
	~Dao();
	bool initDatabases(const QString str); //如果存在配置文件就读取，如果不存在就创建，通过数据库获取到软件id。
	QString confuseName(int len);          //返回指定长度的随机字符串
	void close();

	//数据库操作接口：
	bool InsertOrUpdateSoftware(Software & s);  //保存软件配置
	bool InsertOrUpdateConfig(Config & c);      //保存参数配置
	bool InsertOrUpdateSite(Site & s);          //保存站点配置
	bool InsertSpacing(Spacing & s);            //新增间隔
	bool UpdateSpacing(const int &id,Spacing s);//修改间隔
	bool InsertSensor(Sensor & s);              //新增监测点
	bool UpdateSensor(Sensor & s);				//修改监测点
	bool deleteSpacing(const int & id);         //删除间隔
	bool deleteSensor(const int & id);          //删除监测点
	bool InsertUser(User & u);					//添加用户
	bool UpdateUser(User & u);					//更新用户
	bool DeleteUser(const int & id);			//删除用户
	bool InsertIED(Ied & ied);					//插入IED单元
	bool UpdateIED(const int & id , Ied & ied); //更新IED单元
	bool UpdateChannels(const int &id,QVector<QVector<int>> vect );//更新通道设置接口
	bool DeleteIED(const int & id);				//删除IED单元
	User GetUserById(const int & id);			//通过ID获取用户
	User GetUserByName(const QString & name);	//通过名称获取用户
	Ied  GetIEDByName(const QString  & name);   //通过名称获取对象
	Ied  GetIEDById(const int & id);			//通过ID获取对象
	Spacing GetSpacingByName(const QString & name);//通过名称获取间隔
	Spacing GetSpacingById(const int & id);     //通过ID获取间隔
	Sensor GetSensorByName(const QString &name);//通过名称获取Sensor
	Sensor GetSensorById(const int & id);       //通过ID获取Sensor
	QVector<User>	 QueryUser();				//获取所有用户
	QVector<Spacing> QuerySpacing();            //获取全部间隔
	QVector<Ied>     QueryIed();                //获取采集单元
	QVector<Sensor>  QuerySensors();            //获取全部监测点
	QVector<Sensor>  QuerySensorBySpacing(const int spacing_id);    //获取属于这个间隔的所有监测点
	QVector<Sensor>  QuerySensorByIED(const int & ied_id);	//获取属于这个IED的所有监测点
	QVector<SensorDeviceAlarm> QueryDeviceWarning(const QString startTime,const QString endTime,const int type,const QString spacing = "不限", const QString sensor = "不限");//查询设备报警信息
	bool updateSensorPos(int id, int x, int y);//更新节点的位置信息

private:
	void loadSettings();
	void saveSettings();
	QSqlDatabase db ;
	Dao();
	int     m_iId;
	QString m_sHostName;
	int     m_iPort;
	QString m_sUserName;
	QString m_sPassword;
	QString m_sDatabaseName;
};

#endif  //DAO
