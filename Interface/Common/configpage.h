/**************************************************************
 * File Name   : configpage.h
 * Author      : ThreeDog
 * Date        : Thu Jan 17 16:51:18 2019
 * Description : 配置窗体，继承自模态框，作为模板页面，需要配置页面的地方，
 * 可以参照此界面进行编写。
 *
 **************************************************************/
#ifndef _CONFIGPAGE_H_ 
#define _CONFIGPAGE_H_ 
#include "ThreeDog/tdmodal.h"
#include <QLineEdit>
#include <QComboBox>

class ConfigPage : public TDModal
{
public:
    explicit ConfigPage(QWidget * parent = 0);
    ~ConfigPage();
};

#endif  //CONFIGPAGE
