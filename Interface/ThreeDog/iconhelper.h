#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#ifndef ICONHELPER_H
#define ICONHELPER_H

#include <QtCore>
#include <QtGui>
#include <QFrame>
#include <QSpacerItem>
#define TitleMinSize 30

#if (QT_VERSION > QT_VERSION_CHECK(5,0,0))
#include <QtWidgets>
#endif

#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

//图形字体处理类
class IconHelper : public QObject
{
    Q_OBJECT

public:
    explicit IconHelper(QObject *parent = 0);
    static IconHelper *Instance()
    {
        static QMutex mutex;

        if (!self) {
            QMutexLocker locker(&mutex);

            if (!self) {
                self = new IconHelper;
            }
        }

        return self;
    }

    void setIcon(QLabel *lab, QChar c, quint32 size = 9);
    void setIcon(QAbstractButton *btn, QChar c, quint32 size = 9);
    QPixmap getPixmap(const QString &color, QChar c, quint32 size = 9,
                      quint32 pixWidth = 10, quint32 pixHeight = 10);

    //根据按钮获取该按钮对应的图标
    QPixmap getPixmap(QToolButton *btn, bool normal);

    //指定导航面板样式,不带图标
    static void setStyle(QWidget *widget, const QString &type = "left", int borderWidth = 3,
                         const QString &borderColor = "#029FEA",
                         const QString &normalBgColor = "#292F38",
                         const QString &darkBgColor = "#1D2025",
                         const QString &normalTextColor = "#54626F",
                         const QString &darkTextColor = "#FDFDFD");

    //指定导航面板样式,带图标和效果切换
    void setStyle(QWidget *widget, QList<QToolButton *> btns, QList<int> pixChar,
                  quint32 iconSize = 9, quint32 iconWidth = 10, quint32 iconHeight = 10,
                  const QString &type = "left", int borderWidth = 3,
                  const QString &borderColor = "#029FEA",
                  const QString &normalBgColor = "#292F38",
                  const QString &darkBgColor = "#1D2025",
                  const QString &normalTextColor = "#54626F",
                  const QString &darkTextColor = "#FDFDFD");

    //指定导航按钮样式,带图标和效果切换
    void setStyle(QFrame *frame, QList<QToolButton *> btns, QList<int> pixChar,
                  quint32 iconSize = 9, quint32 iconWidth = 10, quint32 iconHeight = 10,
                  const QString &normalBgColor = "#2FC5A2",
                  const QString &darkBgColor = "#3EA7E9",
                  const QString &normalTextColor = "#EEEEEE",
                  const QString &darkTextColor = "#FFFFFF");

protected:
    bool eventFilter(QObject *watched, QEvent *event);

private:
    static IconHelper *self;    //对象自身
    QFont iconFont;             //图形字体
    QList<QToolButton *> btns;  //按钮队列
    QList<QPixmap> pixNormal;   //正常图片队列
    QList<QPixmap> pixDark;     //加深图片队列
};

//弹出信息框类
class QUIMessageBox : public QDialog
{
    Q_OBJECT

public:
    explicit QUIMessageBox(QWidget *parent = 0);
    ~QUIMessageBox();

    static QUIMessageBox *Instance()
    {
        static QMutex mutex;

        if (!self) {
            QMutexLocker locker(&mutex);

            if (!self) {
                self = new QUIMessageBox;
            }
        }

        return self;
    }

protected:
    void closeEvent(QCloseEvent *);
    bool eventFilter(QObject *obj, QEvent *evt);

private:
    static QUIMessageBox *self;

    QVBoxLayout *verticalLayout1;
    QWidget *widgetTitle;
    QHBoxLayout *horizontalLayout3;
    QLabel *labIco;
    QLabel *labTitle;
    QLabel *labTime;
    QWidget *widgetMenu;
    QHBoxLayout *horizontalLayout4;
    QPushButton *btnMenu_Close;
    QWidget *widgetMain;
    QVBoxLayout *verticalLayout2;
    QFrame *frame;
    QVBoxLayout *verticalLayout4;
    QHBoxLayout *horizontalLayout1;
    QLabel *labIcoMain;
    QSpacerItem *horizontalSpacer1;
    QLabel *labInfo;
    QHBoxLayout *horizontalLayout2;
    QSpacerItem *horizontalSpacer2;
    QPushButton *btnOk;
    QPushButton *btnCancel;

private:
    int closeSec;                   //总显示时间
    int currentSec;                 //当前已显示时间

private slots:
    void initControl();             //初始化控件
    void initForm();                //初始化窗体
    void checkSec();                //校验倒计时

private slots:
    void on_btnOk_clicked();
    void on_btnMenu_Close_clicked();

public Q_SLOTS:
    void setIconMain(QChar str, quint32 size = 9);
    void setMessage(const QString &msg, int type, int closeSec = 0);
};

#endif // ICONHELPER_H
