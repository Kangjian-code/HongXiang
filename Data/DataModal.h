/**************************************************************
 * File Name   : DataModal.h
 * Author      : ThreeDog
 * Date        : Fri Feb 01 20:43:41 2019
 * Description : 数据模型定义， 数据库中一个表对应一个类， 所有的数据模型都在此定义
 *
 **************************************************************/
#ifndef _DATAMODAL_H_ 
#define _DATAMODAL_H_ 
#include <QString>
#include <QDateTime>

//参数配置
class Config{
public :
    int id;
    QString dschType;
    float lowerLimit1;
    float lowerLimit2;
    float lowerLimit3;
    float lowerLimit4;
    float higherLimit1;//'一档幅值上限',
    float higherLimit2;
    float higherLimit3;
    float higherLimit4;
    QString color1;//一档报警颜色值',
    QString color2;
    QString color3;
    QString color4;
    QString desc1;//'一档描述',
    QString desc2;//
    QString desc3;
    QString desc4;
    int alarmObMin;//'报警观察时间',
    int alarmTimesTd;//'报警次数阀值',
    int deviceFaulThreshold;//'装置故障次数阀值',
    int alarmDurationTime;//'报警时间间隔',
    int alarmObservationDay;//'报警观察周期',
    int maxAmplitude;//'最大放电幅阀值',
    int dischargeProbabilityThreshold;//'局放概率阀值',
    int dischargeNumThreshold;//'局放次数阀值',
    int numPerDuration;//'持续出现次数',
    int higherAverageLevel;// '高于平均放电水平值',
    int samplingPeriod;//'采样间隔（分）',
    int recordDuration;//'录波时间',
    int isAlarm;// '是否报警',
    QString createTime;//'创建时间',
    QString lastTime;//'最后修改时间',
    int selfCheckTime;//自检时间
};

//站点设置
class Site{
public :
    int id;//'主键ID',
    QString name;//'站点名称',
    QString intro;// '站点概况',
    QString layoutPictureURL;//'站点接线图',
    QString level;// '电压等级',
    QString ip;//'IP地址',
    int dbPort;//'数据库端口号',
    int fileViewPort;//'文件访问端口号',
    int fileUploadPort;//'文件上传端口号',
    QString  createTime;//'创建时间',
    QString  lastTime;//'最后修改时间',
};

//软件设置
class Software{
public:
    int id;
    QString company;//'公司名称',
    QString name;//'软件名称',
    QString logo;//'logo URL',
    QString swRev;//'版本号',
    QString desc;//'简介',
};

//用户
class User{
public :
    int id;
    QString loginName;      //'登录名',
    QString realName;       //'真实姓名',
    QString password;       //'密码',
    QString phone;          //'电话号码',
    QString email;          //'邮箱',
    int level;              //'权限等级，0：admin,1:normal',
    QString department;     //'所属部门',
    QString remark;         //'备注',
    QString creatTime;      //'创建时间',
    QString lastTime;       //'最后修改时间',
    int status;             //'启用状态，0：禁止；1：启用',
};

//采集单元信息表
class Ied{
public:
    int id;
    QString name;//'单元名称'
    QString sn;//设备编号'
    QString ip;//ip地址'
    int port;//'端口',
    int channelNum;//'通道数量',
    int syncType;//'同步方式',
    float interSyncFreq;//'内同步频率',
    int status;//启用状态',
    int channel1;//'通道1类型',
    int channel1Status;//'通道1状态',
    int channel2;
    int channel2Status;
    int channel3;
    int channel3Status;
    int channel4;
    int channel4Status;
    int channel5;
    int channel5Status;
    int channel6;
    int channel6Status;
    int channel7;
    int channel7Status;
    int channel8;
    int channel8Status;
    QString createTime;//创建时间
    QString lastTime;//最近修改时间
    int isDelete;//是否删除
};

//IED定时采集记录
class IedRecord{
public:
    int id;
    int ied_id;//关联的ied的id',
    QString channelConfig;//通道配置',
    QString samplingAlarm;//'采集报警',
    QString sensorAlarm;//'传感器报警',
    QString externalSyncStatus;//'外同步报错',
    QString syncSign;//'内外同步标志',
    QString externalSyncFreq;//'外同步频率',
    QString samplingTime;//'请求采集时间',
    QString createTime;//创建时间',
};

//间隔
class Spacing{
public:
    int     id;
    QString name;       //'间隔名称',
    QString desc;       //'间隔描述',
    QString producer;   //'制造商',
    QString manDate;    //'生产日期',
    QString runDate;    //'投运日期',
    QString pictureURL; //'间隔图片URL',
    int     status;     //'启用状态',
    QString createTime; //'创建时间',
    QString lastTime;   //'修改时间',
    int     isDelete;   //'是否删除，1：是，0：否',
};

//监测点信息表
class Sensor{
public:
     int            id;
     int            ied1_id;
     int            ied2_id;
     int            spacing_id;
     int            type;               //'类型，0:UHF' 1、噪声 2、震动,
     QString        name ;              //'监测点名称',
     QString        sn;                 //'设备编号',
     int            channel_no;         //'通道号',
     QString        pictureURL;         //'安装图片url',
     int            alarmThreshold;     //'报警阀值-80 ~-10',
     int            pulseThreshold;     //'脉冲数量阀值',
     int            freqBand;           //'频带',
     int            referToThreshold;   //'参考阀值',
     float          site_x;             //'站点图片相对X坐标',
     float          site_y;             //'站点图片相对y坐标',
     float          spacing_x;          //'间隔图片相对X坐标',
     float          spacing_y;          //'间隔图片相对Y坐标',
     QString        lastConnectTime;    //'最后通信时间',
     int            noiseChannelNo;     //'关联噪声通道',
     QString        createTime;         //'创建时间',
     QString        lastTime;           //'最后修改时间',
     int            isDelete ;
};

//监测点采集数据表
class SensorData{
public:
     int        id;
     int        ied_record_id;
     int        sensor_id;
     QString    collectTime;
     QString    data;           //  mediumblob NOT NULL COMMENT '采集数据',
     float      max;            //'最大值',
     float      min;            //'最小值',
     float      average;        //'平均值',
     float      freq;           //'放电频次',
     float      phase;          //'放电相位',
     int        alarmLevel ;    //'报警等级',
     int        dschType;       //'局放类型',
     QString    alarmDesc;      //'缺陷描述',
     QString    alarmPictureURL;//'缺陷照片',
     int        isDiagnose;     //'是否诊断',
     int        isUpload;       //'是否上传',
     int        isReset;        //'是否复归',
     QString    createTime;     //'创建时间',
};

//监测点报警表
class SensorDeviceAlarm{
public:
     int id ;
     int sensor_id;
     int alarmType ;//'故障类型',
     int alarmLevel ;//'报警等级',
     QString alarmTime;//'报警时间（毫秒）',
     QString alarmDesc;//故障描述
     QString alarmPictureURL;//'缺陷照片',
     bool isUpload;
     bool isReset;
     QString createTime;
};

//监测点频段
class SensorFreqband{
public:
    int id;//
    QString value;//
};

//指纹库
class fingerprint{
public:
    int id;
    int fileType ;//'文件类型',
    int dschType;//'局放类型',
    QString  name;//'名称',
    QString  desc;//'描述',
    QString  fileURL;//'文件地址',
    QString  createTime;
    QString  lastTime ;//'最后修改时间',
};

#endif  //DATAMODAL
