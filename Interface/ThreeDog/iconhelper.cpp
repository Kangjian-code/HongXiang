#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#include "iconhelper.h"

IconHelper *IconHelper::self = 0;
IconHelper::IconHelper(QObject *) : QObject(qApp)
{
    int fontId = QFontDatabase::addApplicationFont(":/img/fontawesome-webfont.ttf");
    QStringList fontName = QFontDatabase::applicationFontFamilies(fontId);

    if (fontName.count() > 0) {
        iconFont = QFont(fontName.at(0));
    } else {
        qDebug() << "load fontawesome-webfont.ttf error";
    }
}

void IconHelper::setIcon(QLabel *lab, QChar c, quint32 size)
{
    iconFont.setPointSize(size);
    lab->setFont(iconFont);
    lab->setText(c);
}

void IconHelper::setIcon(QAbstractButton *btn, QChar c, quint32 size)
{
    iconFont.setPointSize(size);
    btn->setFont(iconFont);
    btn->setText(c);
}

QPixmap IconHelper::getPixmap(const QString &color, QChar c, quint32 size,
                              quint32 pixWidth, quint32 pixHeight)
{
    QPixmap pix(pixWidth, pixHeight);
    pix.fill(Qt::transparent);

    QPainter painter;
    painter.begin(&pix);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    painter.setPen(QColor(color));
    painter.setBrush(QColor(color));

    iconFont.setPointSize(size);
    painter.setFont(iconFont);
    painter.drawText(pix.rect(), Qt::AlignCenter, c);
    painter.end();

    return pix;
}

QPixmap IconHelper::getPixmap(QToolButton *btn, bool normal)
{
    QPixmap pix;
    int index = btns.indexOf(btn);

    if (index >= 0) {
        if (normal) {
            pix = pixNormal.at(index);
        } else {
            pix = pixDark.at(index);
        }
    }

    return pix;
}

void IconHelper::setStyle(QWidget *widget, const QString &type, int borderWidth, const QString &borderColor,
                          const QString &normalBgColor, const QString &darkBgColor,
                          const QString &normalTextColor, const QString &darkTextColor)
{
    QString strBorder;
    if (type == "top") {
        strBorder = QString("border-width:%1px 0px 0px 0px;padding:%1px %2px %2px %2px;")
                .arg(borderWidth).arg(borderWidth * 2);
    } else if (type == "right") {
        strBorder = QString("border-width:0px %1px 0px 0px;padding:%2px %1px %2px %2px;")
                .arg(borderWidth).arg(borderWidth * 2);
    } else if (type == "bottom") {
        strBorder = QString("border-width:0px 0px %1px 0px;padding:%2px %2px %1px %2px;")
                .arg(borderWidth).arg(borderWidth * 2);
    } else if (type == "left") {
        strBorder = QString("border-width:0px 0px 0px %1px;padding:%2px %2px %2px %1px;")
                .arg(borderWidth).arg(borderWidth * 2);
    }

    QStringList qss;
    qss.append(QString("QWidget[flag=\"%1\"] QAbstractButton{border-style:none;border-radius:0px;padding:5px;color:%2;background:%3;}")
               .arg(type).arg(normalTextColor).arg(normalBgColor));

    qss.append(QString("QWidget[flag=\"%1\"] QAbstractButton:hover,"
                       "QWidget[flag=\"%1\"] QAbstractButton:pressed,"
                       "QWidget[flag=\"%1\"] QAbstractButton:checked{"
                       "border-style:solid;%2border-color:%3;color:%4;background:%5;}")
               .arg(type).arg(strBorder).arg(borderColor).arg(darkTextColor).arg(darkBgColor));

    widget->setStyleSheet(qss.join(""));
}

void IconHelper::setStyle(QWidget *widget, QList<QToolButton *> btns, QList<int> pixChar,
                          quint32 iconSize, quint32 iconWidth, quint32 iconHeight,
                          const QString &type, int borderWidth, const QString &borderColor,
                          const QString &normalBgColor, const QString &darkBgColor,
                          const QString &normalTextColor, const QString &darkTextColor)
{
    int btnCount = btns.count();
    int charCount = pixChar.count();
    if (btnCount <= 0 || charCount <= 0 || btnCount != charCount) {
        return;
    }

    QString strBorder;
    if (type == "top") {
        strBorder = QString("border-width:%1px 0px 0px 0px;padding:%1px %2px %2px %2px;")
                .arg(borderWidth).arg(borderWidth * 2);
    } else if (type == "right") {
        strBorder = QString("border-width:0px %1px 0px 0px;padding:%2px %1px %2px %2px;")
                .arg(borderWidth).arg(borderWidth * 2);
    } else if (type == "bottom") {
        strBorder = QString("border-width:0px 0px %1px 0px;padding:%2px %2px %1px %2px;")
                .arg(borderWidth).arg(borderWidth * 2);
    } else if (type == "left") {
        strBorder = QString("border-width:0px 0px 0px %1px;padding:%2px %2px %2px %1px;")
                .arg(borderWidth).arg(borderWidth * 2);
    }

    //如果图标是左侧显示则需要让没有选中的按钮左侧也有加深的边框,颜色为背景颜色
    QStringList qss;
    if (btns.at(0)->toolButtonStyle() == Qt::ToolButtonTextBesideIcon) {
        qss.append(QString("QWidget[flag=\"%1\"] QAbstractButton{border-style:solid;border-radius:0px;%2border-color:%3;color:%4;background:%5;}")
                   .arg(type).arg(strBorder).arg(normalBgColor).arg(normalTextColor).arg(normalBgColor));
    } else {
        qss.append(QString("QWidget[flag=\"%1\"] QAbstractButton{border-style:none;border-radius:0px;padding:5px;color:%2;background:%3;}")
                   .arg(type).arg(normalTextColor).arg(normalBgColor));
    }

    qss.append(QString("QWidget[flag=\"%1\"] QAbstractButton:hover,"
                       "QWidget[flag=\"%1\"] QAbstractButton:pressed,"
                       "QWidget[flag=\"%1\"] QAbstractButton:checked{"
                       "border-style:solid;%2border-color:%3;color:%4;background:%5;}")
               .arg(type).arg(strBorder).arg(borderColor).arg(darkTextColor).arg(darkBgColor));

    qss.append(QString("QWidget#%1{background:%2;}").arg(widget->objectName()).arg(normalBgColor));

    qss.append(QString("QWidget>QToolButton{border-width:0px;}"));
    qss.append(QString("QWidget>QToolButton{background-color:%1;color:%2;}")
               .arg(normalBgColor).arg(normalTextColor));
    qss.append(QString("QWidget>QToolButton:hover,QWidget>QToolButton:pressed,QWidget>QToolButton:checked{background-color:%1;color:%2;}")
               .arg(darkBgColor).arg(darkTextColor));

    widget->setStyleSheet(qss.join(""));

    for (int i = 0; i < btnCount; i++) {
        //存储对应按钮对象,方便鼠标移上去的时候切换图片
        QPixmap pixNormal = getPixmap(normalTextColor, QChar(pixChar.at(i)), iconSize, iconWidth, iconHeight);
        QPixmap pixDark = getPixmap(darkTextColor, QChar(pixChar.at(i)), iconSize, iconWidth, iconHeight);

        btns.at(i)->setIcon(QIcon(pixNormal));
        btns.at(i)->setIconSize(QSize(iconWidth, iconHeight));
        btns.at(i)->installEventFilter(this);

        this->btns.append(btns.at(i));
        this->pixNormal.append(pixNormal);
        this->pixDark.append(pixDark);
    }
}

void IconHelper::setStyle(QFrame *frame, QList<QToolButton *> btns, QList<int> pixChar,
                          quint32 iconSize, quint32 iconWidth, quint32 iconHeight,
                          const QString &normalBgColor, const QString &darkBgColor,
                          const QString &normalTextColor, const QString &darkTextColor)
{
    int btnCount = btns.count();
    int charCount = pixChar.count();
    if (btnCount <= 0 || charCount <= 0 || btnCount != charCount) {
        return;
    }

    QStringList qss;
    qss.append(QString("QFrame>QToolButton{border-style:none;border-width:0px;}"));
    qss.append(QString("QFrame>QToolButton{background-color:%1;color:%2;}")
               .arg(normalBgColor).arg(normalTextColor));
    qss.append(QString("QFrame>QToolButton:hover,QFrame>QToolButton:pressed,QFrame>QToolButton:checked{background-color:%1;color:%2;}")
               .arg(darkBgColor).arg(darkTextColor));

    frame->setStyleSheet(qss.join(""));

    for (int i = 0; i < btnCount; i++) {
        //存储对应按钮对象,方便鼠标移上去的时候切换图片
        QPixmap pixNormal = getPixmap(normalTextColor, QChar(pixChar.at(i)), iconSize, iconWidth, iconHeight);
        QPixmap pixDark = getPixmap(darkTextColor, QChar(pixChar.at(i)), iconSize, iconWidth, iconHeight);

        btns.at(i)->setIcon(QIcon(pixNormal));
        btns.at(i)->setIconSize(QSize(iconWidth, iconHeight));
        btns.at(i)->installEventFilter(this);

        this->btns.append(btns.at(i));
        this->pixNormal.append(pixNormal);
        this->pixDark.append(pixDark);
    }
}

bool IconHelper::eventFilter(QObject *watched, QEvent *event)
{
    if (watched->inherits("QToolButton")) {
        QToolButton *btn = (QToolButton *)watched;
        int index = btns.indexOf(btn);
        if (index >= 0) {
            if (event->type() == QEvent::Enter) {
                btn->setIcon(QIcon(pixDark.at(index)));
            } else if (event->type() == QEvent::Leave) {
                if (btn->isChecked()) {
                    btn->setIcon(QIcon(pixDark.at(index)));
                } else {
                    btn->setIcon(QIcon(pixNormal.at(index)));
                }
            }
        }
    }

    return QObject::eventFilter(watched, event);
}




QUIMessageBox *QUIMessageBox::self = 0;
QUIMessageBox::QUIMessageBox(QWidget *parent) : QDialog(parent)
{
    this->initControl();
    this->initForm();
}

QUIMessageBox::~QUIMessageBox()
{
    delete widgetMain;
}

void QUIMessageBox::initControl()
{
    this->setObjectName(QString::fromUtf8("QUIMessageBox"));

    verticalLayout1 = new QVBoxLayout(this);
    verticalLayout1->setSpacing(0);
    verticalLayout1->setObjectName(QString::fromUtf8("verticalLayout1"));
    verticalLayout1->setContentsMargins(1, 1, 1, 1);
    widgetTitle = new QWidget(this);
    widgetTitle->setObjectName(QString::fromUtf8("widgetTitle"));
    QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(widgetTitle->sizePolicy().hasHeightForWidth());
    widgetTitle->setSizePolicy(sizePolicy);
    widgetTitle->setMinimumSize(QSize(0, TitleMinSize));
    horizontalLayout3 = new QHBoxLayout(widgetTitle);
    horizontalLayout3->setSpacing(0);
    horizontalLayout3->setObjectName(QString::fromUtf8("horizontalLayout3"));
    horizontalLayout3->setContentsMargins(0, 0, 0, 0);
    labIco = new QLabel(widgetTitle);
    labIco->setObjectName(QString::fromUtf8("labIco"));
    QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Preferred);
    sizePolicy1.setHorizontalStretch(0);
    sizePolicy1.setVerticalStretch(0);
    sizePolicy1.setHeightForWidth(labIco->sizePolicy().hasHeightForWidth());
    labIco->setSizePolicy(sizePolicy1);
    labIco->setMinimumSize(QSize(TitleMinSize, 0));
    labIco->setAlignment(Qt::AlignCenter);

    horizontalLayout3->addWidget(labIco);

    labTitle = new QLabel(widgetTitle);
    labTitle->setObjectName(QString::fromUtf8("labTitle"));
    labTitle->setStyleSheet(QString::fromUtf8(""));
    labTitle->setAlignment(Qt::AlignLeading | Qt::AlignLeft | Qt::AlignVCenter);

    horizontalLayout3->addWidget(labTitle);

    labTime = new QLabel(widgetTitle);
    labTime->setObjectName(QString::fromUtf8("labTime"));
    QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Preferred);
    sizePolicy2.setHorizontalStretch(0);
    sizePolicy2.setVerticalStretch(0);
    sizePolicy2.setHeightForWidth(labTime->sizePolicy().hasHeightForWidth());
    labTime->setSizePolicy(sizePolicy2);
    labTime->setAlignment(Qt::AlignCenter);

    horizontalLayout3->addWidget(labTime);

    widgetMenu = new QWidget(widgetTitle);
    widgetMenu->setObjectName(QString::fromUtf8("widgetMenu"));
    sizePolicy1.setHeightForWidth(widgetMenu->sizePolicy().hasHeightForWidth());
    widgetMenu->setSizePolicy(sizePolicy1);
    horizontalLayout4 = new QHBoxLayout(widgetMenu);
    horizontalLayout4->setSpacing(0);
    horizontalLayout4->setObjectName(QString::fromUtf8("horizontalLayout4"));
    horizontalLayout4->setContentsMargins(0, 0, 0, 0);
    btnMenu_Close = new QPushButton(widgetMenu);
    btnMenu_Close->setObjectName(QString::fromUtf8("btnMenu_Close"));
    QSizePolicy sizePolicy3(QSizePolicy::Minimum, QSizePolicy::Expanding);
    sizePolicy3.setHorizontalStretch(0);
    sizePolicy3.setVerticalStretch(0);
    sizePolicy3.setHeightForWidth(btnMenu_Close->sizePolicy().hasHeightForWidth());
    btnMenu_Close->setSizePolicy(sizePolicy3);
    btnMenu_Close->setMinimumSize(QSize(TitleMinSize, 0));
    btnMenu_Close->setMaximumSize(QSize(TitleMinSize, 16777215));
    btnMenu_Close->setCursor(QCursor(Qt::ArrowCursor));
    btnMenu_Close->setFocusPolicy(Qt::NoFocus);
    btnMenu_Close->setFlat(true);

    horizontalLayout4->addWidget(btnMenu_Close);
    horizontalLayout3->addWidget(widgetMenu);
    verticalLayout1->addWidget(widgetTitle);

    widgetMain = new QWidget(this);
    widgetMain->setObjectName(QString::fromUtf8("widgetMain"));
    widgetMain->setStyleSheet(QString::fromUtf8(""));
    verticalLayout2 = new QVBoxLayout(widgetMain);
    verticalLayout2->setSpacing(5);
    verticalLayout2->setObjectName(QString::fromUtf8("verticalLayout2"));
    verticalLayout2->setContentsMargins(5, 5, 5, 5);
    frame = new QFrame(widgetMain);
    frame->setObjectName(QString::fromUtf8("frame"));
    frame->setFrameShape(QFrame::Box);
    frame->setFrameShadow(QFrame::Sunken);
    verticalLayout4 = new QVBoxLayout(frame);
    verticalLayout4->setObjectName(QString::fromUtf8("verticalLayout4"));
    verticalLayout4->setContentsMargins(-1, 9, -1, -1);
    horizontalLayout1 = new QHBoxLayout();
    horizontalLayout1->setObjectName(QString::fromUtf8("horizontalLayout1"));
    labIcoMain = new QLabel(frame);
    labIcoMain->setObjectName(QString::fromUtf8("labIcoMain"));
    labIcoMain->setStyleSheet(QString::fromUtf8("border-image: url(:/img/msg_info.png);"));
    horizontalLayout1->addWidget(labIcoMain);
    horizontalSpacer1 = new QSpacerItem(5, 0, QSizePolicy::Minimum, QSizePolicy::Minimum);
    horizontalLayout1->addItem(horizontalSpacer1);

    labInfo = new QLabel(frame);
    labInfo->setObjectName(QString::fromUtf8("labInfo"));
    QSizePolicy sizePolicy4(QSizePolicy::Expanding, QSizePolicy::Expanding);
    sizePolicy4.setHorizontalStretch(0);
    sizePolicy4.setVerticalStretch(0);
    sizePolicy4.setHeightForWidth(labInfo->sizePolicy().hasHeightForWidth());
    labInfo->setSizePolicy(sizePolicy4);
    labInfo->setMinimumSize(QSize(0, TitleMinSize));
    labInfo->setScaledContents(false);
    labInfo->setWordWrap(true);
    horizontalLayout1->addWidget(labInfo);
    verticalLayout4->addLayout(horizontalLayout1);

    horizontalLayout2 = new QHBoxLayout();
    horizontalLayout2->setObjectName(QString::fromUtf8("horizontalLayout2"));
    horizontalSpacer2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
    horizontalLayout2->addItem(horizontalSpacer2);

    btnOk = new QPushButton(frame);
    btnOk->setObjectName(QString::fromUtf8("btnOk"));
    btnOk->setMinimumSize(QSize(85, 0));
    btnOk->setFocusPolicy(Qt::StrongFocus);
    btnOk->setStyleSheet(QString::fromUtf8(""));
    btnOk->setIcon(QIcon(":/img/btn_ok.png"));
    horizontalLayout2->addWidget(btnOk);

    btnCancel = new QPushButton(frame);
    btnCancel->setObjectName(QString::fromUtf8("btnCancel"));
    btnCancel->setMinimumSize(QSize(85, 0));
    btnCancel->setFocusPolicy(Qt::StrongFocus);
    btnCancel->setStyleSheet(QString::fromUtf8(""));
    btnCancel->setIcon(QIcon(":/img/btn_close.png"));
    horizontalLayout2->addWidget(btnCancel);

    verticalLayout4->addLayout(horizontalLayout2);
    verticalLayout2->addWidget(frame);
    verticalLayout1->addWidget(widgetMain);

    widgetTitle->raise();
    widgetMain->raise();
    frame->raise();

    btnOk->setText("确定");
    btnCancel->setText("取消");

    connect(btnOk, SIGNAL(clicked()), this, SLOT(on_btnOk_clicked()));
    connect(btnMenu_Close, SIGNAL(clicked()), this, SLOT(on_btnMenu_Close_clicked()));
    connect(btnCancel, SIGNAL(clicked()), this, SLOT(on_btnMenu_Close_clicked()));
}

void QUIMessageBox::initForm()
{
    IconHelper::Instance()->setIcon(labIco, QChar(0xf072), 11);
    IconHelper::Instance()->setIcon(btnMenu_Close, QChar(0xf00d), 9);

    this->setProperty("form", true);
    this->widgetTitle->setProperty("form", "title");
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint | Qt::WindowStaysOnTopHint);
    this->setWindowTitle(this->labTitle->text());

#ifdef __arm__
    int width = 90;
    int iconWidth = 22;
    int iconHeight = 22;
    this->setFixedSize(350, 180);
    labIcoMain->setFixedSize(40, 40);
#else
    int width = 80;
    int iconWidth = 18;
    int iconHeight = 18;
    this->setFixedSize(280, 150);
    labIcoMain->setFixedSize(30, 30);
#endif

    QList<QPushButton *> btns = this->frame->findChildren<QPushButton *>();

    foreach (QPushButton *btn, btns) {
        btn->setMinimumWidth(width);
        btn->setIconSize(QSize(iconWidth, iconHeight));
    }

    closeSec = 0;
    currentSec = 0;

    QTimer *timer = new QTimer(this);
    timer->setInterval(1000);
    connect(timer, SIGNAL(timeout()), this, SLOT(checkSec()));
    timer->start();

    this->installEventFilter(this);
}

void QUIMessageBox::checkSec()
{
    if (closeSec == 0) {
        return;
    }

    if (currentSec < closeSec) {
        currentSec++;
    } else {
        this->close();
    }

    QString str = QString("关闭倒计时 %1 s").arg(closeSec - currentSec + 1);
    this->labTime->setText(str);
}

void QUIMessageBox::setMessage(const QString &msg, int type, int closeSec)
{
    this->closeSec = closeSec;
    this->currentSec = 0;
    this->labTime->clear();

    checkSec();

    if (type == 0) {
        this->labIcoMain->setStyleSheet("border-image: url(:/img/msg_info.png);");
        this->btnCancel->setVisible(false);
        this->labTitle->setText("提示");
    } else if (type == 1) {
        this->labIcoMain->setStyleSheet("border-image: url(:/img/msg_question.png);");
        this->labTitle->setText("询问");
    } else if (type == 2) {
        this->labIcoMain->setStyleSheet("border-image: url(:/img/msg_error.png);");
        this->btnCancel->setVisible(false);
        this->labTitle->setText("错误");
    }

    labInfo->setStyleSheet("color:#353535");
    this->labInfo->setText(msg);
    this->setWindowTitle(this->labTitle->text());
}

void QUIMessageBox::closeEvent(QCloseEvent *)
{
    closeSec = 0;
    currentSec = 0;
}

bool QUIMessageBox::eventFilter(QObject *obj, QEvent *evt)
{
    static QPoint mousePoint;
    static bool mousePressed = false;

    QMouseEvent *event = static_cast<QMouseEvent *>(evt);
    if (event->type() == QEvent::MouseButtonPress) {
        if (event->button() == Qt::LeftButton) {
            mousePressed = true;
            mousePoint = event->globalPos() - this->pos();
            return true;
        }
    } else if (event->type() == QEvent::MouseButtonRelease) {
        mousePressed = false;
        return true;
    } else if (event->type() == QEvent::MouseMove) {
        if (mousePressed && (event->buttons() && Qt::LeftButton)) {
            this->move(event->globalPos() - mousePoint);
            return true;
        }
    }

    return QWidget::eventFilter(obj, evt);
}

void QUIMessageBox::on_btnOk_clicked()
{
    done(QMessageBox::Yes);
    close();
}

void QUIMessageBox::on_btnMenu_Close_clicked()
{
    done(QMessageBox::No);
    close();
}

void QUIMessageBox::setIconMain(QChar str, quint32 size)
{
    IconHelper::Instance()->setIcon(this->labIco, str, size);
}

