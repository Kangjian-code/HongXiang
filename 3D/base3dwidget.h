#ifndef BASE3DWIDGET_H
#define BASE3DWIDGET_H

#include "surfacegraph.h"

#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMessageBox>
#include <QtGui/QPainter>
#include <QtGui/QScreen>

class Base3DWidget : public QWidget
{
	Q_OBJECT
public:
	explicit Base3DWidget(bool showRight = true,QWidget *parent = nullptr);

signals:

public slots:
};

#endif // BASE3DWIDGET_H
