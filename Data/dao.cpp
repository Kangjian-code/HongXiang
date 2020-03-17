/**************************************************************
 * File Name   : dao.cpp
 * Author      : ThreeDog
 * Date        : Mon Mar 18 18:54:52 2019
 * Description : 数据库连接类，单例模式，全局使用一个数据库连接
 *
 **************************************************************/

#include "dao.h"
#if _MSC_BUILD
#pragma execution_character_set("utf-8")
#endif
#include "dao.h"

Dao * Dao::self = NULL;

Dao::Dao()
{
	if(initDatabases("hxdl")){
		qDebug() << "Database Connect Sucessfully!";
	}
	else{
		qDebug() << "Database Connect Failed!";
		TDMessageBox::warning("数据库连接失败");
	}
}

Dao *Dao::getInstance()
{
	if(self == NULL)
		self = new Dao();
	if(!self->db.isOpen()){
		self->db.open();
	}
	return self;
}

int Dao::getId()
{
	return this->m_iId;
}

Dao::~Dao()
{

}

bool Dao::initDatabases(const QString str)
{
//<<<<<<< HEAD
	if(QFile::exists(CONFIGFILE)){
		loadSettings();
	}else {
		//如果文件不存在，初始化并保存设置：
        m_sHostName = "122.51.166.80";
		m_iPort = 3306;
		m_sUserName = "root";
//<<<<<<< HEAD
        m_sPassword = "76LV2Bsf8WA0Jq1R^ny";
//=======
//		m_sPassword = "Roottoor";
//>>>>>>> dev
		m_sDatabaseName = str;
		db = QSqlDatabase::addDatabase("QMYSQL");
		db.setHostName(m_sHostName);
		db.setPort(m_iPort);
		db.setUserName(m_sUserName);
		db.setPassword(m_sPassword);
		db.setDatabaseName(m_sDatabaseName);
		if(!db.open()){
			qDebug()<<db.lastError();
			qDebug() << "Database Error!";
			return false;
		}
		//获取到id写入
		QSqlQuery query;
		query.exec("select max(id) as id from software;");
		while(query.next()){
			m_iId = query.value("id").toInt() + 1;
		}
		saveSettings();
		return true;
	}

	db = QSqlDatabase::addDatabase("QMYSQL");
	db.setHostName(m_sHostName);
	db.setPort(m_iPort);
	db.setUserName(m_sUserName);
	db.setPassword(m_sPassword);
	db.setDatabaseName(m_sDatabaseName);
	if(!db.open()){
		qDebug()<<db.lastError();
		qDebug() << "Database Error!";
		return false;
	}
	return true;
//=======

//	if(QFile::exists(CONFIGFILE)){
//		loadSettings();
//	}else {
//		//如果文件不存在，初始化并保存设置：
//		m_sHostName = "106.12.204.187";
//		m_iPort = 3306;
//		m_sUserName = "root";
//		m_sPassword = "toor";
//		m_sDatabaseName = str;
//		db = QSqlDatabase::addDatabase("QMYSQL");
//		db.setHostName(m_sHostName);
//		db.setPort(m_iPort);
//		db.setUserName(m_sUserName);
//		db.setPassword(m_sPassword);
//		db.setDatabaseName(m_sDatabaseName);
//		if(!db.open()){
//			qDebug()<<db.lastError();
//			qDebug() << "Database Error!";
//			saveSettings();
//			return false;
//		}
//		//获取到id写入
//		QSqlQuery query;
//		query.exec("select max(id) as id from software;");
//		while(query.next()){
//			m_iId = query.value("id").toInt() + 1;
//		}
//		saveSettings();
//		return true;
//	}

//	db = QSqlDatabase::addDatabase("QMYSQL");
//	db.setHostName(m_sHostName);
//	db.setPort(m_iPort);
//	db.setUserName(m_sUserName);
//	db.setPassword(m_sPassword);
//	db.setDatabaseName(m_sDatabaseName);
//	if(!db.open()){
//		qDebug()<<db.lastError();
//		qDebug() << "Database Error!";
//		return false;
//	}
//	return true;
//>>>>>>> dev
}

QString Dao::confuseName(int len)
{
	srand(time(NULL));
	QString str = "_";
	for(int i = 0; i < len ; i++){
		str += ((char)rand()%56 + 'a');
	}
	return str;
}

void Dao::close()
{
	if(db.isOpen())
		db.close();
}

//插入或者更新软件设置
bool Dao::InsertOrUpdateSoftware(Software &s)
{
	QVector<int> vect ;
	QSqlQuery query;
	query.exec(QString("select * from hxdl.software where id = %1;").arg(s.id));
	while(query.next()){
		vect.append(query.value("id").toInt());
	}
	QString sql;
	if(vect.size() == 0){
		//执行插入
		sql = QString("\
					  INSERT INTO `hxdl`.`software`(`id`,`company`,`name`,`logo`,`swRev`,`desc`) VALUES(%1,'%2','%3','%4','%5','%6');\
				").arg(QString::number(s.id),s.company,s.name,s.logo,s.swRev,s.desc);
	}else{
		//执行更新
		sql = QString("\
					  update `hxdl`.`software` set `company` = '%1', `name` = '%2',`logo` = '%3',`swRev` = '%4',`desc` = '%5' where id = 1;\
				").arg(s.company,s.name,s.logo,s.swRev,s.desc);
	}
	query.prepare(sql);
	qDebug() << sql;
	return query.exec();
}

//插入或者更新配置信息
bool Dao::InsertOrUpdateConfig(Config &c)
{
	QVector<int> vect ;
	QSqlQuery query;
	query.exec(QString("select * from hxdl.config where id = %1;").arg(c.id));
	while(query.next()){
		vect.append(query.value("id").toInt());
	}
	QString sql;
	if(vect.size() == 0){
		//执行插入
		sql = QString("\
					  INSERT INTO `hxdl`.`config`\
					  (`id`,`dschType`,`lowerLimit1`,`lowerLimit2`,\
					   `lowerLimit3`,`lowerLimit4`,`higherLimit1`,\
					   `higherLimit2`,`higherLimit3`,`higherLimit4`,`color1`,\
					   `color2`,`color3`,`color4`,`desc1`,`desc2`,\
					   `desc3`,`desc4`,`alarmObMin`,`alarmTimesTd`,\
					   `deviceFaulThreshold`,`alarmDurationTime`,\
					   `alarmObservationDay`,`maxAmplitude`,\
					   `dischargeProbabilityThreshold`,`dischargeNumThreshold`,\
					   `numPerDuration`,`higherAverageLevel`,\
					   `samplingPeriod`,`recordDuration`,\
					   `isAlarm`,`createTime`,`lastTime`,`selfCheckTime`)\
					  VALUES\
					  (%1,'%2','%3','%4','%5','%6','%7','%8','%9','%10','%11',\
					   '%12','%13','%14','%15','%16','%17','%18','%19','%20',\
					   '%21','%22','%23','%24','%25',%26,%27,'%28','%29',\
					   '%30',%31,'%32','%33',%34);\
				").arg(c.id).arg(c.dschType).arg(c.lowerLimit1).arg(c.lowerLimit2).arg(c.lowerLimit3)
				.arg(c.lowerLimit4).arg(c.higherLimit1).arg(c.higherLimit2).arg(c.higherLimit3).arg(c.higherLimit4).arg(c.color1)
				.arg(c.color2).arg(c.color3).arg(c.color4).arg(c.desc1).arg(c.desc2).arg(c.desc3).arg(c.desc4).arg(c.alarmObMin).arg(c.alarmTimesTd)
				.arg(c.deviceFaulThreshold).arg(c.alarmDurationTime).arg(c.alarmObservationDay).arg(c.maxAmplitude)
				.arg(c.dischargeProbabilityThreshold).arg(c.dischargeNumThreshold).arg(c.numPerDuration).arg(c.higherAverageLevel)
				.arg(c.samplingPeriod).arg(c.recordDuration).arg(c.isAlarm).arg(c.createTime).arg(c.lastTime).arg(c.selfCheckTime);
	}else{
		//执行更新  注意更新不更新创建时间
		sql = QString("\
					  UPDATE `hxdl`.`config`\
					  SET\
					  `id` = %1,`dschType` = '%2',`lowerLimit1` = %3,\
					  `lowerLimit2` = %4,`lowerLimit3` = %5,`lowerLimit4` = %6,\
					  `higherLimit1` = %7,`higherLimit2` = %8,`higherLimit3` = %9,\
					  `higherLimit4` = %10,`color1` = '%11',`color2` = '%12',\
					  `color3` = '%13',`color4` = '%14',`desc1` = '%15',\
					  `desc2` = '%16',`desc3` = '%17',`desc4` = '%18',\
					  `alarmObMin` = %19,`alarmTimesTd` = %20,\
					  `deviceFaulThreshold` = %21,`alarmDurationTime` = %22,\
					  `alarmObservationDay` = %23,`maxAmplitude` = %24,\
					  `dischargeProbabilityThreshold` = %25,\
					  `dischargeNumThreshold` = %26,\
					  `numPerDuration` = %27,`higherAverageLevel` = %28,\
					  `samplingPeriod` = %29,`recordDuration` = %30,\
					  `isAlarm` = %31,`lastTime` = '%32',`selfCheckTime` = %33 WHERE `id` = %34;"
				).arg(c.id).arg(c.dschType).arg(c.lowerLimit1).arg(c.lowerLimit2)
				.arg(c.lowerLimit3).arg(c.lowerLimit4).arg(c.higherLimit1)
				.arg(c.higherLimit2).arg(c.higherLimit3).arg(c.higherLimit4)
				.arg(c.color1).arg(c.color2).arg(c.color3).arg(c.color4)
				.arg(c.desc1).arg(c.desc2).arg(c.desc3).arg(c.desc4).arg(c.alarmObMin)
				.arg(c.alarmTimesTd).arg(c.deviceFaulThreshold).arg(c.alarmDurationTime)
				.arg(c.alarmObservationDay).arg(c.maxAmplitude).arg(c.dischargeProbabilityThreshold)
				.arg(c.dischargeNumThreshold)
				.arg(c.numPerDuration).arg(c.higherAverageLevel).arg(c.samplingPeriod)
				.arg(c.recordDuration).arg(c.isAlarm).arg(c.lastTime).arg(c.selfCheckTime).arg(c.id);
	}
	query.prepare(sql);
	qDebug() << sql;
	return query.exec();
}

//插入或者更新站点配置
bool Dao::InsertOrUpdateSite(Site &s)
{
	QVector<int> vect ;
	QSqlQuery query;
	query.exec(QString("select * from hxdl.site where id = %1;").arg(s.id));
	while(query.next()){
		vect.append(query.value("id").toInt());
	}
	QString sql;
	if(vect.size() == 0){
		//执行插入
		sql = QString("\
					  INSERT INTO `hxdl`.`site`(`id`,`name`,`intro`,`layoutPictureURL`,`level`,`ip`,`dbPort`,`fileViewPort`,`fileUploadPort`,`createTime`,`lastTime`)\
					  VALUES(%1,'%2','%3','%4','%5','%6',%7,%8,%9,'%10','%11');\
				").arg(s.id).arg(s.name).arg(s.intro).arg(s.layoutPictureURL).arg(s.level).arg(s.ip).arg(s.dbPort).arg(s.fileViewPort).arg(s.fileUploadPort).arg(s.createTime).arg(s.lastTime);
	}else{
		//执行更新 //注意更新不更新创建时间
		sql = QString("\
					  UPDATE `hxdl`.`site`\
					  SET\
					  `id` = %1,\
					  `name` = '%2',\
					  `intro` = '%3',\
					  `layoutPictureURL` = '%4',\
					  `level` = '%5',\
					  `ip` = '%6',\
					  `dbPort` = %7,\
					  `fileViewPort` = %8,\
					  `fileUploadPort` = %9,\
					  `lastTime` = '%10'\
				WHERE `id` = '%11';\
				").arg(s.id).arg(s.name).arg(s.intro).arg(s.layoutPictureURL).arg(s.level).arg(s.ip).arg(s.dbPort).arg(s.fileViewPort).arg(s.fileUploadPort).arg(s.lastTime).arg(s.id);
	}
	query.prepare(sql);
	qDebug() << sql;
	return query.exec();
}

bool Dao::InsertSpacing(Spacing &s)
{
	QString sql;

	sql = QString("\
				  INSERT INTO `hxdl`.`spacing`(`name`,`desc`,`producer`,`manDate`,`runDate`,\
											   `pictureURL`,`status`,`createTime`,`lastTime`,`isDelete`)\
				  VALUES('%1','%2','%3','%4',\
						 '%5', '%6',%7,'%8',\
						 '%9',%10);")
			.arg(s.name).arg(s.desc).arg(s.producer).arg(s.manDate).arg(s.runDate)
			.arg(s.pictureURL).arg(s.status).arg(s.createTime).arg(s.lastTime).arg(s.isDelete);
	QSqlQuery query;
	query.prepare(sql);
	qDebug() << sql;
	return query.exec();
}

bool Dao::UpdateSpacing(const int &id, Spacing s)
{
	QString sql;
	sql = QString("\
				  UPDATE `hxdl`.`spacing`SET `name` = '%1',`desc` = '%2',\
				  `producer` = '%3',`manDate` = '%4',`runDate` = '%5',\
				  `pictureURL` = '%6',`lastTime` = '%7' WHERE `id` = %8;")
			.arg(s.name).arg(s.desc).arg(s.producer).arg(s.manDate).arg(s.runDate)
			.arg(s.pictureURL).arg(s.lastTime).arg(id);
	QSqlQuery query;
	query.prepare(sql);
	qDebug() << sql;
	return query.exec();
}

bool Dao::InsertSensor(Sensor &s)
{
	QString sql;
	sql = QString("\
				  INSERT INTO `hxdl`.`sensor`(`ied1_id`,`ied2_id`,`spacing_id`,\
											  `type`,`name`,`sn`,`channel_no`,`pictureURL`,`alarmThreshold`,\
											  `pulseThreshold`,`freqBand`,`referToThreshold`,`site_x`,`site_y`,\
											  `spacing_x`,`spacing_y`,`lastConnectTime`,`noiseChannelNo`,`createTime`,\
											  `lastTime`,`isDelete`)VALUES(%1,%2,\
																		   %3,%4,'%5',%6,%7,\
																		   '%8',%9,%10,%11,\
																		   %12,%13,%14,%15,\
																		   %16,'%17',%18,'%19',\
																		   '%20',%21);\
			")
			.arg(s.ied1_id).arg(s.ied2_id).arg(s.spacing_id).arg(s.type).arg(s.name)
			.arg(s.sn).arg(s.channel_no).arg(s.pictureURL).arg(s.alarmThreshold)
			.arg(s.pulseThreshold).arg(s.freqBand).arg(s.referToThreshold).arg(s.site_x)
			.arg(s.site_y).arg(s.spacing_x).arg(s.spacing_y).arg(s.lastConnectTime).arg(s.noiseChannelNo)
			.arg(s.createTime).arg(s.lastTime).arg(s.isDelete);
	QSqlQuery query;
	query.prepare(sql);
	qDebug() << sql;
	return query.exec();
}

bool Dao::UpdateSensor(Sensor &s)
{
	QString sql;
	sql = QString("\
				  UPDATE `hxdl`.`sensor` SET\
				  `ied1_id` = %1,\
				  `ied2_id` = %2,\
				  `spacing_id` = %3,\
				  `type` = %4,\
				  `name` = '%5',\
				  `sn` = %6,\
				  `channel_no` = %7,\
				  `pictureURL` = '%8',\
				  `alarmThreshold` = %9,\
				  `pulseThreshold` = %10,\
				  `freqBand` = %11,\
				  `referToThreshold` = %12,\
				  `site_x` = %13,\
				  `site_y` = %14,\
				  `spacing_x` = %15,\
				  `spacing_y` = %16,\
				  `lastConnectTime` = '%17',\
				  `noiseChannelNo` = %18,\
				  `createTime` = '%19',\
				  `lastTime` = '%20',\
				  `isDelete` = %21\
			WHERE `id` = %22;\
			")
			.arg(s.ied1_id).arg(s.ied2_id).arg(s.spacing_id).arg(s.type).arg(s.name)
			.arg(s.sn).arg(s.channel_no).arg(s.pictureURL).arg(s.alarmThreshold)
			.arg(s.pulseThreshold).arg(s.freqBand).arg(s.referToThreshold).arg(s.site_x)
			.arg(s.site_y).arg(s.spacing_x).arg(s.spacing_y).arg(s.lastConnectTime).arg(s.noiseChannelNo)
			.arg(s.createTime).arg(s.lastTime).arg(s.isDelete).arg(s.id);
	QSqlQuery query;
	query.prepare(sql);
	qDebug() << sql;
	return query.exec();
}

bool Dao::deleteSpacing(const int & id)
{
	//删除间隔的时候，先删除间隔下的所有监测点
	for(Sensor sensor : this->QuerySensorBySpacing(id)){
		QString sql;
		sql = QString("UPDATE `hxdl`.`sensor` SET `name` = '%1',`isDelete` = 1\
					  WHERE `id` = %2;\
				")
				.arg(sensor.name + this->confuseName(6)).arg(sensor.id);

		QSqlQuery query;
		query.prepare(sql);
		if(!query.exec()){
			qDebug()<<sql;
			return false;
		}
	}

	Spacing spacing = this->GetSpacingById(id);
	QString sql;
	//删除数据是假删，删的时候把名字也改了
	sql = QString("UPDATE `hxdl`.`spacing`SET `name` = '%1',`isDelete` = 1\
				  WHERE `id` = %2;\
			")
			.arg(spacing.name + this->confuseName(6)).arg(id);
	QSqlQuery query;
	query.prepare(sql);
	qDebug() << sql;
	return query.exec();
}

bool Dao::deleteSensor(const int &id)
{
	//删除指定id的监测点
	Sensor sensor = this->GetSensorById(id);
	QString sql;
	//删除数据是假删，删的时候把名字也改了
	sql = QString("UPDATE `hxdl`.`sensor`SET `name` = '%1',`isDelete` = 1\
				  WHERE `id` = %2;\
			")
			.arg(sensor.name + this->confuseName(6)).arg(id);
	QSqlQuery query;
	query.prepare(sql);
	qDebug() << sql;
	return query.exec();
}

bool Dao::InsertUser(User &u)
{
	QString sql;

	sql = QString("\
				  INSERT INTO `hxdl`.`user`(`loginName`,`realName`,`password`,`phone`,`email`,\
											`level`,`department`,`remark`,`creatTime`,`lastTime`,status)\
				  VALUES('%1','%2','%3','%4',\
						 '%5', %6,'%7','%8',\
						 '%9','%10',%11);")
			.arg(u.loginName).arg(u.realName).arg(u.password).arg(u.phone).arg(u.email)
			.arg(u.level).arg(u.department).arg(u.remark).arg(u.creatTime).arg(u.lastTime).arg(u.status);
	QSqlQuery query;
	query.prepare(sql);
	qDebug() << sql;
	return query.exec();
}

bool Dao::UpdateUser(User &u)
{
	QString sql;
	sql = QString("\
				  UPDATE `hxdl`.`user` SET\
				  `loginName` = '%1',\
				  `realName` = '%2',\
				  `password` = '%3',\
				  `phone` = '%4',\
				  `email` = '%5',\
				  `level` = %6,\
				  `department` = '%7',\
				  `remark` = '%8',\
				  `creatTime` = '%9',\
				  `lastTime` = '%10',\
				  `status` = %11  \
			WHERE `id` = %12;\
			")
			.arg(u.loginName).arg(u.realName).arg(u.password).arg(u.phone).arg(u.email)
			.arg(u.level).arg(u.department).arg(u.remark).arg(u.creatTime)
			.arg(u.lastTime).arg(u.status).arg(u.id);
	QSqlQuery query;
	query.prepare(sql);
	qDebug() << sql;
	return query.exec();
}

bool Dao::DeleteUser(const int &id)
{
	//删除指定id的用户
	User user = this->GetUserById(id);
	QString sql;
	//删除数据是假删，删的时候把名字也改了
	sql = QString("UPDATE `hxdl`.`user` SET `loginName` = '%1',`status` = 0\
				  WHERE `id` = %2;\
			")
			.arg(user.loginName + this->confuseName(6)).arg(id);
	QSqlQuery query;
	query.prepare(sql);
	qDebug() << sql;
	return query.exec();
}

bool Dao::InsertIED(Ied &ied)
{
	QString sql;
	sql = QString("INSERT INTO `hxdl`.`ied`(`name`,`sn`,`ip`,`port`,`channelNum`,\
				  `syncType`,`interSyncFreq`,`status`,`createTime`,`lastTime`,`isDelete`\
				  )VALUES('%1','%2',\
											   '%3',%4,%5,%6,%7,\
											   %8,'%9','%10',%11);")
	.arg(ied.name).arg(ied.sn).arg(ied.ip).arg(ied.port).arg(ied.channelNum)
			.arg(ied.syncType).arg(ied.interSyncFreq).arg(ied.status).arg(ied.createTime)
			.arg(ied.lastTime).arg(ied.isDelete);
	QSqlQuery query;
	query.prepare(sql);
	qDebug() << sql;
	return query.exec();
}

bool Dao::UpdateIED(const int &id, Ied &ied)
{
	QString sql;
	sql = QString("\
				  UPDATE `hxdl`.`ied` SET\
				  `name` = '%1',\
				  `sn` = '%2',\
				  `ip` = '%3',\
				  `port` = %4,\
				  `channelNum` = %5,\
				  `syncType` = %6,\
				  `interSyncFreq` = %7,\
				  `status` = %8,\
				  `createTime` = '%9',\
				  `lastTime` = '%10',\
				  `isDelete` = %11,\
				  `channel1` = %12,\
				  `channel1Status` = %13,\
				  `channel2` = %14,\
				  `channel2Status` = %15,\
				  `channel3` = %16,\
				  `channel3Status` = %17,\
				  `channel4` = %18,\
				  `channel4Status` = %19,\
				  `channel5` = %20,\
				  `channel5Status` = %21,\
				  `channel6` = %22,\
				  `channel6Status` = %23,\
				  `channel7` = %24,\
				  `channel7Status` = %25,\
				  `channel8` = %26,\
				  `channel8Status` = %27\
				  WHERE `id` = %28;\
			")
			.arg(ied.name).arg(ied.sn).arg(ied.ip).arg(ied.port).arg(ied.channelNum)
			.arg(ied.syncType).arg(ied.interSyncFreq).arg(ied.status).arg(ied.createTime)
			.arg(ied.lastTime).arg(ied.isDelete)
			.arg(ied.channel1).arg(ied.channel1Status)
			.arg(ied.channel2).arg(ied.channel2Status)
			.arg(ied.channel3).arg(ied.channel3Status)
			.arg(ied.channel4).arg(ied.channel4Status)
			.arg(ied.channel5).arg(ied.channel5Status)
			.arg(ied.channel6).arg(ied.channel6Status)
			.arg(ied.channel7).arg(ied.channel7Status)
			.arg(ied.channel8).arg(ied.channel8Status)
			.arg(id);
	QSqlQuery query;
	query.prepare(sql);
	qDebug() << sql;
	return query.exec();
}

bool Dao::UpdateChannels(const int &id, QVector<QVector<int>> vect)
{
	QString sql;
	sql = QString("UPDATE `hxdl`.`ied` SET ");
	for(int i =0 ; i < vect.count(); i++){
		sql += QString(" channel%1 = %2 , channel%1Status = %3 , ").arg(i+1)
				.arg(vect.at(i)[0]).arg(vect.at(i)[1]);
	}
	sql += QString(" lastTime = '%1' where id = %2 ;").arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")).arg(id);
	QSqlQuery query;
	query.prepare(sql);
	qDebug() << sql;
	return query.exec();
}

bool Dao::DeleteIED(const int &id)
{
	//删除IED的时候，先删除采集单元下的所有监测点
	for(Sensor sensor : this->QuerySensorByIED(id)){
		QString sql;
		sql = QString("UPDATE `hxdl`.`sensor` SET `name` = '%1',`isDelete` = 1\
					  WHERE `id` = %2;\
				")
				.arg(sensor.name + this->confuseName(6)).arg(sensor.id);

		QSqlQuery query;
		query.prepare(sql);
		if(!query.exec()){
			qDebug()<<sql;
			return false;
		}
	}
	Ied ied = this->GetIEDById(id);
	QString sql;
	//删除数据是假删，删的时候把名字也改了
	sql = QString("UPDATE `hxdl`.`ied`SET `name` = '%1',`isDelete` = 1\
				  WHERE `id` = %2;\
			")
			.arg(ied.name + this->confuseName(6)).arg(id);
	QSqlQuery query;
	query.prepare(sql);
	qDebug() << sql;
	return query.exec();
}

User Dao::GetUserById(const int &id)
{
	User user;
	QSqlQuery query;
	QString sql = QString("select * from user where id = %1 and status = 1").arg(id);
	query.exec(sql);
	while(query.next()){
		user.id = id;
		user.loginName = query.value("loginName").toString();
		user.realName = query.value("realName").toString();
		user.password = query.value("password").toString();
		user.phone = query.value("phone").toString();
		user.email = query.value("email").toString();
		user.level = query.value("level").toInt();
		user.department = query.value("department").toString();
		user.remark = query.value("remark").toString();
		user.creatTime = query.value("creatTime").toString();
		user.lastTime = query.value("lastTime").toString();
		user.status = query.value("status").toInt();
	}
	return user;
}

User Dao::GetUserByName(const QString &name)
{
	User user;
	QSqlQuery query;
	QString sql = QString("select * from user where loginName = '%1' and status = 1").arg(name);
	query.exec(sql);
	while(query.next()){
		user.id = query.value("id").toInt();
		user.loginName = query.value("loginName").toString();
		user.realName = query.value("realName").toString();
		user.password = query.value("password").toString();
		user.phone = query.value("phone").toString();
		user.email = query.value("email").toString();
		user.level = query.value("level").toInt();
		user.department = query.value("department").toString();
		user.remark = query.value("remark").toString();
		user.creatTime = query.value("createTime").toString();
		user.lastTime = query.value("lastTime").toString();
		user.status = query.value("status").toInt();
	}
	return user;
}

Ied Dao::GetIEDByName(const QString &name)
{
	Ied ied;
	ied.id = -1;
	QSqlQuery query;
	QString sql = QString("select * from ied where name = '%1' and isDelete = 0").arg(name);
	query.exec(sql);
	while(query.next()){
		ied.id = query.value("id").toInt();
		ied.name = query.value("name").toString();
		ied.sn = query.value("sn").toString();
		ied.ip = query.value("ip").toString();
		ied.port = query.value("port").toInt();
		ied.channelNum = query.value("channelNum").toInt();
		ied.syncType = query.value("syncType").toInt();
		ied.interSyncFreq = query.value("interSyncFreq").toFloat();
		ied.status = query.value("status").toInt();
		ied.channel1 = query.value("channel1").toInt();
		ied.channel1Status = query.value("channel1Status").toInt();
		ied.channel2 = query.value("channel2").toInt();
		ied.channel2Status = query.value("channel2Status").toInt();
		ied.channel3 = query.value("channel3").toInt();
		ied.channel3Status = query.value("channel3Status").toInt();
		ied.channel4 = query.value("channel4").toInt();
		ied.channel4Status = query.value("channel4Status").toInt();
		ied.channel5 = query.value("channel5").toInt();
		ied.channel5Status = query.value("channel5Status").toInt();
		ied.channel6 = query.value("channel6").toInt();
		ied.channel6Status = query.value("channel6Status").toInt();
		ied.channel7 = query.value("channel7").toInt();
		ied.channel7Status = query.value("channel7Status").toInt();
		ied.channel8 = query.value("channel8").toInt();
		ied.channel8Status = query.value("channel8Status").toInt();
		ied.createTime = query.value("createTime").toString();
		ied.lastTime = query.value("lastTime").toString();
		ied.isDelete = query.value("isDelete").toInt();
	}
	return ied;
}

Ied Dao::GetIEDById(const int &id)
{
	Ied ied;
	QSqlQuery query;
	QString sql = QString("select * from ied where id = %1 and isDelete = 0").arg(id);
	query.exec(sql);
	while(query.next()){
		ied.id = query.value("id").toInt();
		ied.name = query.value("name").toString();
		ied.sn = query.value("sn").toString();
		ied.ip = query.value("ip").toString();
		ied.port = query.value("port").toInt();
		ied.channelNum = query.value("channelNum").toInt();
		ied.syncType = query.value("syncType").toInt();
		ied.interSyncFreq = query.value("interSyncFreq").toFloat();
		ied.status = query.value("status").toInt();
		ied.channel1 = query.value("channel1").toInt();
		ied.channel1Status = query.value("channel1Status").toInt();
		ied.channel2 = query.value("channel2").toInt();
		ied.channel2Status = query.value("channel2Status").toInt();
		ied.channel3 = query.value("channel3").toInt();
		ied.channel3Status = query.value("channel3Status").toInt();
		ied.channel4 = query.value("channel4").toInt();
		ied.channel4Status = query.value("channel4Status").toInt();
		ied.channel5 = query.value("channel5").toInt();
		ied.channel5Status = query.value("channel5Status").toInt();
		ied.channel6 = query.value("channel6").toInt();
		ied.channel6Status = query.value("channel6Status").toInt();
		ied.channel7 = query.value("channel7").toInt();
		ied.channel7Status = query.value("channel7Status").toInt();
		ied.channel8 = query.value("channel8").toInt();
		ied.channel8Status = query.value("channel8Status").toInt();
		ied.createTime = query.value("createTime").toString();
		ied.lastTime = query.value("lastTime").toString();
		ied.isDelete = query.value("isDelete").toInt();
	}
	return ied;
}

Spacing Dao::GetSpacingByName(const QString &name)
{
	Spacing spacing;
	spacing.id = -1;
	QSqlQuery query;
	QString sql = QString("select * from spacing where name = '%1' and isDelete = 0").arg(name);
	query.exec(sql);
	while(query.next()){
		spacing.id = query.value("id").toInt();
		spacing.name = query.value("name").toString();
		spacing.desc = query.value("desc").toString();
		spacing.producer = query.value("producer").toString();
		spacing.manDate = query.value("manDate").toString();
		spacing.runDate = query.value("runDate").toString();
		spacing.pictureURL = query.value("pictureURL").toString();
		spacing.status = query.value("status").toInt();
		spacing.createTime = query.value("createTime").toString();
		spacing.lastTime = query.value("lastTime").toString();
		spacing.isDelete = query.value("isDelete").toInt();
	}
	return spacing;
}

Spacing Dao::GetSpacingById(const int &id)
{
	Spacing spacing;
	spacing.id = -1;
	QSqlQuery query;
	QString sql = QString("select * from spacing where id = %1 and isDelete = 0").arg(id);
	query.exec(sql);
	while(query.next()){
		spacing.id = query.value("id").toInt();
		spacing.name = query.value("name").toString();
		spacing.desc = query.value("desc").toString();
		spacing.producer = query.value("producer").toString();
		spacing.manDate = query.value("manDate").toString();
		spacing.runDate = query.value("runDate").toString();
		spacing.pictureURL = query.value("pictureURL").toString();
		spacing.status = query.value("status").toInt();
		spacing.createTime = query.value("createTime").toString();
		spacing.lastTime = query.value("lastTime").toString();
		spacing.isDelete = query.value("isDelete").toInt();
	}
	return spacing;
}

Sensor Dao::GetSensorByName(const QString &name)
{
	QSqlQuery query;
	QString sql = QString("select * from sensor where name = '%1' and isDelete = 0").arg(name);
	query.exec(sql);
	while(query.next()){
		Sensor s;
		s.id = query.value("id").toInt();
		s.ied1_id = query.value("ied1_id").toInt();
		s.ied2_id = query.value("ied2_id").toInt();
		s.spacing_id = query.value("spacing_id").toInt();
		s.type = query.value("type").toInt();//'类型，0:UHF' 1、噪声 2、
		s.name = query.value("name").toString();      //'监测点名称',
		s.sn = query.value("sn").toString();                 //'设备编号',
		s.channel_no = query.value("channel_no").toInt();//'通道号',
		s.pictureURL = query.value("pictureURL").toString();//'安装图片url',
		s.alarmThreshold = query.value("alarmThreshold").toInt();//'报警阀值-80 ~-10',
		s.pulseThreshold = query.value("pulseThreshold").toInt();     //'脉冲数量阀值',
		s.freqBand = query.value("freqBand").toInt();           //'频带',
		s.referToThreshold = query.value("referToThreshold").toInt();   //'参考阀值',
		s.site_x = query.value("site_x").toFloat();             //'站点图片相对X坐标',
		s.site_y = query.value("site_y").toFloat();             //'站点图片相对y坐标',
		s.spacing_x = query.value("spacing_x").toFloat();          //'间隔图片相对X坐标',
		s.spacing_y = query.value("spacing_y").toFloat();          //'间隔图片相对Y坐标',
		s.lastConnectTime = query.value("lastConnectTime").toString();    //'最后通信时间',
		s.noiseChannelNo = query.value("noiseChannelNo").toInt();     //'关联噪声通道',
		s.createTime = query.value("createTime").toString();         //'创建时间',
		s.lastTime = query.value("lastTime").toString();          //'最后修改时间',
		s.isDelete = query.value("isDelete").toInt();
		return s;
	}
}

Sensor Dao::GetSensorById(const int &id)
{
	Sensor s ;
	s.id = -1;
	QSqlQuery query;
	QString sql = QString("select * from sensor where id = %1 and isDelete = 0").arg(id);
	query.exec(sql);
	while(query.next()){
		s.id = query.value("id").toInt();
		s.ied1_id = query.value("ied1_id").toInt();
		s.ied2_id = query.value("ied2_id").toInt();
		s.spacing_id = query.value("spacing_id").toInt();
		s.type = query.value("type").toInt();//'类型，0:UHF' 1、噪声 2、
		s.name = query.value("name").toString();      //'监测点名称',
		s.sn = query.value("sn").toString();                 //'设备编号',
		s.channel_no = query.value("channel_no").toInt();//'通道号',
		s.pictureURL = query.value("pictureURL").toString();//'安装图片url',
		s.alarmThreshold = query.value("alarmThreshold").toInt();//'报警阀值-80 ~-10',
		s.pulseThreshold = query.value("pulseThreshold").toInt();     //'脉冲数量阀值',
		s.freqBand = query.value("freqBand").toInt();           //'频带',
		s.referToThreshold = query.value("referToThreshold").toInt();   //'参考阀值',
		s.site_x = query.value("site_x").toFloat();             //'站点图片相对X坐标',
		s.site_y = query.value("site_y").toFloat();             //'站点图片相对y坐标',
		s.spacing_x = query.value("spacing_x").toFloat();          //'间隔图片相对X坐标',
		s.spacing_y = query.value("spacing_y").toFloat();          //'间隔图片相对Y坐标',
		s.lastConnectTime = query.value("lastConnectTime").toString();    //'最后通信时间',
		s.noiseChannelNo = query.value("noiseChannelNo").toInt();     //'关联噪声通道',
		s.createTime = query.value("createTime").toString();         //'创建时间',
		s.lastTime = query.value("lastTime").toString();          //'最后修改时间',
		s.isDelete = query.value("isDelete").toInt();
		return s;
	}
}

QVector<User> Dao::QueryUser()
{
	QVector<User> vect;
	QSqlQuery query;
	QString sql = "select * from user where status = 1;";
	if(!query.exec(sql)){
		qDebug()<<db.lastError();
	}
	while(query.next()){
		User user;
		user.id = query.value("id").toInt();
		user.loginName = query.value("loginName").toString();
		user.realName = query.value("realName").toString();
		user.password = query.value("password").toString();
		user.phone = query.value("phone").toString();
		user.email = query.value("email").toString();
		user.level = query.value("level").toInt();
		user.department = query.value("department").toString();
		user.remark = query.value("remark").toString();
		user.creatTime = query.value("creatTime").toString();
		user.lastTime = query.value("lastTime").toString();
		user.status = query.value("status").toInt();
		vect.append(user);
	}
	return vect;
}

QVector<Spacing> Dao::QuerySpacing()
{
	QVector<Spacing> vect;
	QSqlQuery query;
	QString sql = "select * from spacing where isDelete = 0";
	if(!query.exec(sql)){
		qDebug()<<db.lastError();
	}
	while(query.next()){
		Spacing s;
		s.id = query.value("id").toInt();
		s.name = query.value("name").toString();
		s.desc = query.value("desc").toString();
		s.producer = query.value("producer").toString();
		s.manDate = query.value("manDate").toString();
		s.runDate = query.value("runDate").toString();
		s.pictureURL = query.value("pictureURL").toString();
		s.status = query.value("status").toInt();
		s.createTime = query.value("createTime").toString();
		s.lastTime = query.value("lastTime").toString();
		s.isDelete = query.value("isDelete").toInt();
		vect.append(s);
	}
	return vect;
}

QVector<Ied> Dao::QueryIed()
{
	QVector<Ied> vect;
	QSqlQuery query;
	QString sql = QString("select * from ied where isDelete = 0");
	query.exec(sql);
	while(query.next()){
		Ied ied;
		ied.id = query.value("id").toInt();
		ied.name = query.value("name").toString();
		ied.sn = query.value("sn").toString();
		ied.ip = query.value("ip").toString();
		ied.port = query.value("port").toInt();
		ied.channelNum = query.value("channelNum").toInt();
		ied.syncType = query.value("syncType").toInt();
		ied.interSyncFreq = query.value("interSyncFreq").toFloat();
		ied.status = query.value("status").toInt();
		ied.channel1 = query.value("channel1").toInt();
		ied.channel1Status = query.value("channel1Status").toInt();
		ied.channel2 = query.value("channel2").toInt();
		ied.channel2Status = query.value("channel2Status").toInt();
		ied.channel3 = query.value("channel3").toInt();
		ied.channel3Status = query.value("channel3Status").toInt();
		ied.channel4 = query.value("channel4").toInt();
		ied.channel4Status = query.value("channel4Status").toInt();
		ied.channel5 = query.value("channel5").toInt();
		ied.channel5Status = query.value("channel5Status").toInt();
		ied.channel6 = query.value("channel6").toInt();
		ied.channel6Status = query.value("channel6Status").toInt();
		ied.channel7 = query.value("channel7").toInt();
		ied.channel7Status = query.value("channel7Status").toInt();
		ied.channel8 = query.value("channel8").toInt();
		ied.channel8Status = query.value("channel8Status").toInt();
		ied.createTime = query.value("createTime").toString();
		ied.lastTime = query.value("lastTime").toString();
		ied.isDelete = query.value("isDelete").toInt();
		vect.append(ied);
	}
	return vect;
}

QVector<Sensor> Dao::QuerySensors()
{
	QVector<Sensor> vect;
	QSqlQuery query;
	QString sql = QString("select * from sensor where isDelete = 0");
	query.exec(sql);
	while(query.next()){
		Sensor s;
		s.id = query.value("id").toInt();
		s.ied1_id = query.value("ied1_id").toInt();
		s.ied2_id = query.value("ied2_id").toInt();
		s.spacing_id = query.value("spacing_id").toInt();
		s.type = query.value("type").toInt();//'类型，0:UHF' 1、噪声 2、
		s.name = query.value("name").toString();      //'监测点名称',
		s.sn = query.value("sn").toString();                 //'设备编号',
		s.channel_no = query.value("channel_no").toInt();//'通道号',
		s.pictureURL = query.value("pictureURL").toString();//'安装图片url',
		s.alarmThreshold = query.value("alarmThreshold").toInt();//'报警阀值-80 ~-10',
		s.pulseThreshold = query.value("pulseThreshold").toInt();     //'脉冲数量阀值',
		s.freqBand = query.value("freqBand").toInt();           //'频带',
		s.referToThreshold = query.value("referToThreshold").toInt();   //'参考阀值',
		s.site_x = query.value("site_x").toFloat();             //'站点图片相对X坐标',
		s.site_y = query.value("site_y").toFloat();             //'站点图片相对y坐标',
		s.spacing_x = query.value("spacing_x").toFloat();          //'间隔图片相对X坐标',
		s.spacing_y = query.value("spacing_y").toFloat();          //'间隔图片相对Y坐标',
		s.lastConnectTime = query.value("lastConnectTime").toString();    //'最后通信时间',
		s.noiseChannelNo = query.value("noiseChannelNo").toInt();     //'关联噪声通道',
		s.createTime = query.value("createTime").toString();         //'创建时间',
		s.lastTime = query.value("lastTime").toString();          //'最后修改时间',
		s.isDelete = query.value("isDelete").toInt();
		vect.append(s);
	}
	return vect;
}

QVector<Sensor> Dao::QuerySensorBySpacing(const int spacing_id)
{
	QVector<Sensor> vect;
	QSqlQuery query;
	QString sql = QString("select * from sensor where spacing_id = %1 and isDelete = 0").arg(spacing_id);
	query.exec(sql);
	while(query.next()){
		Sensor s;
		s.id = query.value("id").toInt();
		s.ied1_id = query.value("ied1_id").toInt();
		s.ied2_id = query.value("ied2_id").toInt();
		s.spacing_id = query.value("spacing_id").toInt();
		s.type = query.value("type").toInt();//'类型，0:UHF' 1、噪声 2、
		s.name = query.value("name").toString();      //'监测点名称',
		s.sn = query.value("sn").toString();                 //'设备编号',
		s.channel_no = query.value("channel_no").toInt();//'通道号',
		s.pictureURL = query.value("pictureURL").toString();//'安装图片url',
		s.alarmThreshold = query.value("alarmThreshold").toInt();//'报警阀值-80 ~-10',
		s.pulseThreshold = query.value("pulseThreshold").toInt();     //'脉冲数量阀值',
		s.freqBand = query.value("freqBand").toInt();           //'频带',
		s.referToThreshold = query.value("referToThreshold").toInt();   //'参考阀值',
		s.site_x = query.value("site_x").toFloat();             //'站点图片相对X坐标',
		s.site_y = query.value("site_y").toFloat();             //'站点图片相对y坐标',
		s.spacing_x = query.value("spacing_x").toFloat();          //'间隔图片相对X坐标',
		s.spacing_y = query.value("spacing_y").toFloat();          //'间隔图片相对Y坐标',
		s.lastConnectTime = query.value("lastConnectTime").toString();    //'最后通信时间',
		s.noiseChannelNo = query.value("noiseChannelNo").toInt();     //'关联噪声通道',
		s.createTime = query.value("createTime").toString();         //'创建时间',
		s.lastTime = query.value("lastTime").toString();          //'最后修改时间',
		s.isDelete = query.value("isDelete").toInt();
		vect.append(s);
	}
	return vect;
}

QVector<Sensor> Dao::QuerySensorByIED(const int & ied_id)
{
	QVector<Sensor> vect;
	QSqlQuery query;
	QString sql = QString("select * from sensor where ied1_id = %1 and isDelete = 0").arg(ied_id);
	query.exec(sql);
	while(query.next()){
		Sensor s;
		s.id = query.value("id").toInt();
		s.ied1_id = query.value("ied1_id").toInt();
		s.ied2_id = query.value("ied2_id").toInt();
		s.spacing_id = query.value("spacing_id").toInt();
		s.type = query.value("type").toInt();//'类型，0:UHF' 1、噪声 2、
		s.name = query.value("name").toString();      //'监测点名称',
		s.sn = query.value("sn").toString();                 //'设备编号',
		s.channel_no = query.value("channel_no").toInt();//'通道号',
		s.pictureURL = query.value("pictureURL").toString();//'安装图片url',
		s.alarmThreshold = query.value("alarmThreshold").toInt();//'报警阀值-80 ~-10',
		s.pulseThreshold = query.value("pulseThreshold").toInt();     //'脉冲数量阀值',
		s.freqBand = query.value("freqBand").toInt();           //'频带',
		s.referToThreshold = query.value("referToThreshold").toInt();   //'参考阀值',
		s.site_x = query.value("site_x").toFloat();             //'站点图片相对X坐标',
		s.site_y = query.value("site_y").toFloat();             //'站点图片相对y坐标',
		s.spacing_x = query.value("spacing_x").toFloat();          //'间隔图片相对X坐标',
		s.spacing_y = query.value("spacing_y").toFloat();          //'间隔图片相对Y坐标',
		s.lastConnectTime = query.value("lastConnectTime").toString();    //'最后通信时间',
		s.noiseChannelNo = query.value("noiseChannelNo").toInt();     //'关联噪声通道',
		s.createTime = query.value("createTime").toString();         //'创建时间',
		s.lastTime = query.value("lastTime").toString();          //'最后修改时间',
		s.isDelete = query.value("isDelete").toInt();
		vect.append(s);
	}
	return vect;
}

QVector<SensorDeviceAlarm> Dao::QueryDeviceWarning(const QString startTime, const QString endTime, const int type, const QString spacing, const QString sensor)
{
	QString sql = QString("select * from sensor_device_alarm where alarmTime > '%1' and alarmTime < '%2' and alarmType = %3 ")
			.arg(startTime).arg(endTime).arg(type);
	if (spacing != "不限"){
		sql += QString("and sensor_id in (select id from sensor where spacing_id = (select id from spacing where name = '%1' ))").arg(spacing);
	}
	if (sensor != "不限"){ //报警的sensor 不为ID
		sql += QString("and sensor_id = (select id from sensor where name = '%1') ").arg(sensor);
	}
	//动态参数：间隔、监测点、报警类型、时间范围
	QVector<SensorDeviceAlarm> vect;
	QSqlQuery query;
	qDebug()<<sql;
	query.exec(sql);
	while(query.next()){
		SensorDeviceAlarm a;
		a.id = query.value("id").toInt();
		a.sensor_id = query.value("sensor_id").toInt();
		a.alarmType = query.value("alarmType").toInt();
		a.alarmLevel = query.value("alarmLevel").toInt();
		a.alarmTime = query.value("alarmTime").toString();
		a.alarmDesc = query.value("alarmDesc").toString();
		a.alarmPictureURL = query.value("alarmPictureURL").toString();
		a.isUpload = query.value("isUpload").toInt();
		a.isReset = query.value("isReset").toInt();
		a.createTime = query.value("createTime").toString();
		vect.append(a);
	}
	return vect;
}

bool Dao::updateSensorPos(int id, int x, int y)
{
	QString sql;
	sql = QString("\
				  update `hxdl`.`sensor` set `site_x` = %1 , `site_y` = %2 where `id`= %3;\
			").arg(x).arg(y).arg(id);
			QSqlQuery query;
	query.prepare(sql);
	qDebug() << sql;
	return query.exec();
}

void Dao::loadSettings()
{
	QString val;
	QFile file;
	file.setFileName(CONFIGFILE);
	file.open(QIODevice::ReadOnly | QIODevice::Text);
	val = file.readAll();
	file.close();
	qDebug()<<"val:"<<val;
	//如果读到的配置少于5个字节，说明读取配置文件失败
	if(val.size() <= 0){
		TDMessageBox::warning("读取数据库配置文件失败，请删除database.json后重新启动该程序");
		qApp->exit(0);
	}

	QJsonDocument jsonDoc = QJsonDocument::fromJson(val.toUtf8());
	QJsonObject jsonObj = jsonDoc.object();
	if(jsonObj.contains("host")){
		m_sHostName = jsonObj.value("host").toString();
	}
	if(jsonObj.contains("port")){
		m_iPort = jsonObj.value("port").toInt();
	}
	if(jsonObj.contains("user")){
		m_sUserName = jsonObj.value("user").toString();
	}
	if(jsonObj.contains("password")){
		m_sPassword = jsonObj.value("password").toString();
	}
	if(jsonObj.contains("name")){
		m_sDatabaseName = jsonObj.value("name").toString();
	}
	if(jsonObj.contains("id")){
		m_iId = jsonObj.value("id").toInt();
	}
}

void Dao::saveSettings()
{
	QFile file;
	file.setFileName(CONFIGFILE);
	if(QFile::exists(CONFIGFILE))
		file.open(QIODevice::ReadWrite | QIODevice::Text |QIODevice::Truncate);
	else
		file.open(QIODevice::ReadWrite | QIODevice::Text);
	//创建Json类并写入文件
	QJsonObject json;
	json.insert("host",this->m_sHostName);
	json.insert("port",this->m_iPort);
	json.insert("user",this->m_sUserName);
	json.insert("password",this->m_sPassword);
	json.insert("name",this->m_sDatabaseName);
	json.insert("id",this->m_iId);
	//构建Json文档
	QJsonDocument jsonDoc;
	jsonDoc.setObject(json);
	QByteArray jsonData = jsonDoc.toJson();

	file.write(jsonData);
	qDebug()<<"write successfully!!";
	file.close();

}
