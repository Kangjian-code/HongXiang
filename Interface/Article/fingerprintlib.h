/**************************************************************
 * File Name   : fingerprintlib.h
 * Author      : ThreeDog
 * Date        : Fri Jan 11 22:29:01 2019
 * Description : 指纹库
 *
 **************************************************************/
#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#ifndef FINGERPRINTLIB_H
#define FINGERPRINTLIB_H

#include <QWidget>
#include "ThreeDog/tdtoolbar.h"

namespace Ui {
class FingerprintLib;
}

class FingerprintLib : public QWidget
{
    Q_OBJECT

public:
    explicit FingerprintLib(QWidget *parent = 0);
    void initLeftTabs();    //初始化左侧栏
    ~FingerprintLib();
public slots:
    void hideLeft();        //隐藏左侧栏

private:
    Ui::FingerprintLib *ui;
    TDToolbar * m_pHideLeftBtn;
};

#endif // FINGERPRINTLIB_H
