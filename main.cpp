/**************************************************************
 * File Name   : main.cpp
 * Author      : ThreeDog
 * Date        : Thu Jan 03 20:01:31 2019
 * Description : 红相电力、在线局部放电监测系统客户端
 * 项目git地址：https://git.dev.tencent.com/firstouch/hx-admin.git
 * 项目页面地址：https://lanhuapp.com/url/Luy5l
 * 项目页面地址：https://lanhuapp.com/url/AIYFP-ZUi3x
 * 数据库：106.12.204.187  密码：111111
 * 文件服务器：http://106.12.204.181/ put方式上传
 *
 **************************************************************/
#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#include "widget.h"
#include <QApplication>
#include "ThreeDog/appinit.h"

class CommonHelper
{
public:
	static void setStyle(const QString &style) {
		QFile qss(style);
		qss.open(QFile::ReadOnly);
		qApp->setStyleSheet(qss.readAll());
		qss.close();
	}
};
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	// 加载QSS样式
	CommonHelper::setStyle(":/qss/blue.qss");
	//通过事件过滤器控制鼠标拖动窗体
	AppInit::Instance()->start();

	//设置全局字体和颜色
	QPalette p;
	p.setColor(QPalette::WindowText,QColor("#262626"));
	QFont font;
	font.setFamily("Microsoft Yahei");
	font.setPixelSize(14);
	a.setPalette(p);
	a.setFont(font);

	Widget w;
	w.show();

	return a.exec();
}



