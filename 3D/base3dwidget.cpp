#include "base3dwidget.h"

Base3DWidget::Base3DWidget(bool showRight,QWidget *parent) : QWidget(parent)
{
	Q3DSurface *graph = new Q3DSurface();
	QWidget *container = QWidget::createWindowContainer(graph);

	if (!graph->hasContext()) {
		QMessageBox msgBox;
		msgBox.setText("Couldn't initialize the OpenGL context.");
		msgBox.exec();
		return ;
	}
//	QSize screenSize(863,429);

//	container->setMinimumSize(QSize(screenSize.width() / 1.2, screenSize.height() / 1.2));
//	container->setMaximumSize(screenSize);
	container->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	container->setFocusPolicy(Qt::StrongFocus);

	QHBoxLayout *hLayout = new QHBoxLayout();
	this->setLayout(hLayout);

	SurfaceGraph *modifier = new SurfaceGraph(graph);

	if(showRight)
	{
		QVBoxLayout *vLayout = new QVBoxLayout();
		hLayout->addWidget(container, 8);
		hLayout->addLayout(vLayout,2);
		vLayout->setAlignment(Qt::AlignTop);

		QGroupBox *selectionGroupBox = new QGroupBox(QStringLiteral("Selection Mode"));
		selectionGroupBox->show();

		QRadioButton *modeNoneRB = new QRadioButton(this);
		modeNoneRB->setText(QStringLiteral("No selection"));
		modeNoneRB->setChecked(false);

		QRadioButton *modeItemRB = new QRadioButton(this);
		modeItemRB->setText(QStringLiteral("Item"));
		modeItemRB->setChecked(false);

		QRadioButton *modeSliceRowRB = new QRadioButton(this);
		modeSliceRowRB->setText(QStringLiteral("Row Slice"));
		modeSliceRowRB->setChecked(false);

		QRadioButton *modeSliceColumnRB = new QRadioButton(this);
		modeSliceColumnRB->setText(QStringLiteral("Column Slice"));
		modeSliceColumnRB->setChecked(false);

		QVBoxLayout *selectionVBox = new QVBoxLayout;
		selectionVBox->addWidget(modeNoneRB);
		selectionVBox->addWidget(modeItemRB);
		selectionVBox->addWidget(modeSliceRowRB);
		selectionVBox->addWidget(modeSliceColumnRB);
		selectionGroupBox->setLayout(selectionVBox);

		QSlider *axisMinSliderX = new QSlider(Qt::Horizontal, this);
		axisMinSliderX->setMinimum(0);
		axisMinSliderX->setTickInterval(1);
		axisMinSliderX->setEnabled(true);
		QSlider *axisMaxSliderX = new QSlider(Qt::Horizontal, this);
		axisMaxSliderX->setMinimum(1);
		axisMaxSliderX->setTickInterval(1);
		axisMaxSliderX->setEnabled(true);
		QSlider *axisMinSliderZ = new QSlider(Qt::Horizontal, this);
		axisMinSliderZ->setMinimum(0);
		axisMinSliderZ->setTickInterval(1);
		axisMinSliderZ->setEnabled(true);
		QSlider *axisMaxSliderZ = new QSlider(Qt::Horizontal, this);
		axisMaxSliderZ->setMinimum(1);
		axisMaxSliderZ->setTickInterval(1);
		axisMaxSliderZ->setEnabled(true);

		QComboBox *themeList = new QComboBox(this);
		themeList->addItem(QStringLiteral("Qt"));
		themeList->addItem(QStringLiteral("Primary Colors"));
		themeList->addItem(QStringLiteral("Digia"));
		themeList->addItem(QStringLiteral("Stone Moss"));
		themeList->addItem(QStringLiteral("Army Blue"));
		themeList->addItem(QStringLiteral("Retro"));
		themeList->addItem(QStringLiteral("Ebony"));
		themeList->addItem(QStringLiteral("Isabelle"));

		QGroupBox *colorGroupBox = new QGroupBox(QStringLiteral("Custom gradient"));

		QLinearGradient grBtoY(0, 0, 1, 100);
		grBtoY.setColorAt(1.0, Qt::black);
		grBtoY.setColorAt(0.67, Qt::blue);
		grBtoY.setColorAt(0.33, Qt::red);
		grBtoY.setColorAt(0.0, Qt::yellow);
		QPixmap pm(24, 100);
		QPainter pmp(&pm);
		pmp.setBrush(QBrush(grBtoY));
		pmp.setPen(Qt::NoPen);
		pmp.drawRect(0, 0, 24, 100);
		QPushButton *gradientBtoYPB = new QPushButton(this);
		gradientBtoYPB->setIcon(QIcon(pm));
		gradientBtoYPB->setIconSize(QSize(24, 100));

		QLinearGradient grGtoR(0, 0, 1, 100);
		grGtoR.setColorAt(1.0, Qt::darkGreen);
		grGtoR.setColorAt(0.5, Qt::yellow);
		grGtoR.setColorAt(0.2, Qt::red);
		grGtoR.setColorAt(0.0, Qt::darkRed);
		pmp.setBrush(QBrush(grGtoR));
		pmp.drawRect(0, 0, 24, 100);
		QPushButton *gradientGtoRPB = new QPushButton(this);
		gradientGtoRPB->setIcon(QIcon(pm));
		gradientGtoRPB->setIconSize(QSize(24, 100));

		QHBoxLayout *colorHBox = new QHBoxLayout;
		colorHBox->addWidget(gradientBtoYPB);
		colorHBox->addWidget(gradientGtoRPB);
		colorGroupBox->setLayout(colorHBox);

	//	vLayout->addWidget(modelGroupBox);
		vLayout->addWidget(selectionGroupBox);
		vLayout->addWidget(new QLabel(QStringLiteral("Column range")));
		vLayout->addWidget(axisMinSliderX);
		vLayout->addWidget(axisMaxSliderX);
		vLayout->addWidget(new QLabel(QStringLiteral("Row range")));
		vLayout->addWidget(axisMinSliderZ);
		vLayout->addWidget(axisMaxSliderZ);
		vLayout->addWidget(new QLabel(QStringLiteral("Theme")));
		vLayout->addWidget(themeList);
		vLayout->addWidget(colorGroupBox);
		colorGroupBox->show();


		QObject::connect(modeNoneRB, &QRadioButton::toggled,
						 modifier, &SurfaceGraph::toggleModeNone);
		QObject::connect(modeItemRB,  &QRadioButton::toggled,
						 modifier, &SurfaceGraph::toggleModeItem);
		QObject::connect(modeSliceRowRB,  &QRadioButton::toggled,
						 modifier, &SurfaceGraph::toggleModeSliceRow);
		QObject::connect(modeSliceColumnRB,  &QRadioButton::toggled,
						 modifier, &SurfaceGraph::toggleModeSliceColumn);
		QObject::connect(axisMinSliderX, &QSlider::valueChanged,
						 modifier, &SurfaceGraph::adjustXMin);
		QObject::connect(axisMaxSliderX, &QSlider::valueChanged,
						 modifier, &SurfaceGraph::adjustXMax);
		QObject::connect(axisMinSliderZ, &QSlider::valueChanged,
						 modifier, &SurfaceGraph::adjustZMin);
		QObject::connect(axisMaxSliderZ, &QSlider::valueChanged,
						 modifier, &SurfaceGraph::adjustZMax);
		QObject::connect(themeList, SIGNAL(currentIndexChanged(int)),
						 modifier, SLOT(changeTheme(int)));
		QObject::connect(gradientBtoYPB, &QPushButton::pressed,
						 modifier, &SurfaceGraph::setBlackToYellowGradient);
		QObject::connect(gradientGtoRPB, &QPushButton::pressed,
						 modifier, &SurfaceGraph::setGreenToRedGradient);

		modifier->setAxisMinSliderX(axisMinSliderX);
		modifier->setAxisMaxSliderX(axisMaxSliderX);
		modifier->setAxisMinSliderZ(axisMinSliderZ);
		modifier->setAxisMaxSliderZ(axisMaxSliderZ);

		modeItemRB->setChecked(true);
		themeList->setCurrentIndex(2);
		modifier->enableSqrtSinModel(true);
	}
	else
	{
		hLayout->addWidget(container);
		QSlider *axisMinSliderX = new QSlider(Qt::Horizontal, this);
		axisMinSliderX->setMinimum(0);
		axisMinSliderX->setTickInterval(1);
		axisMinSliderX->setEnabled(true);
		QSlider *axisMaxSliderX = new QSlider(Qt::Horizontal, this);
		axisMaxSliderX->setMinimum(1);
		axisMaxSliderX->setTickInterval(1);
		axisMaxSliderX->setEnabled(true);
		QSlider *axisMinSliderZ = new QSlider(Qt::Horizontal, this);
		axisMinSliderZ->setMinimum(0);
		axisMinSliderZ->setTickInterval(1);
		axisMinSliderZ->setEnabled(true);
		QSlider *axisMaxSliderZ = new QSlider(Qt::Horizontal, this);
		axisMaxSliderZ->setMinimum(1);
		axisMaxSliderZ->setTickInterval(1);
		axisMaxSliderZ->setEnabled(true);

		axisMinSliderX->hide();
		axisMaxSliderX->hide();
		axisMinSliderZ->hide();
		axisMaxSliderZ->hide();

		modifier->setAxisMinSliderX(axisMinSliderX);
		modifier->setAxisMaxSliderX(axisMaxSliderX);
		modifier->setAxisMinSliderZ(axisMinSliderZ);
		modifier->setAxisMaxSliderZ(axisMaxSliderZ);

		modifier->enableSqrtSinModel(true);
	}
	this->setWindowTitle(QStringLiteral("Surface example"));

//	QGroupBox *modelGroupBox = new QGroupBox(QStringLiteral("Model"));

//	QRadioButton *sqrtSinModelRB = new QRadioButton(this);
//	sqrtSinModelRB->setText(QStringLiteral("Sqrt && Sin"));
//	sqrtSinModelRB->setChecked(false);

//	QRadioButton *heightMapModelRB = new QRadioButton(this);
//	heightMapModelRB->setText(QStringLiteral("Height Map"));
//	heightMapModelRB->setChecked(false);

//	QVBoxLayout *modelVBox = new QVBoxLayout;
//	modelVBox->addWidget(sqrtSinModelRB);
//	modelVBox->addWidget(heightMapModelRB);
//	modelGroupBox->setLayout(modelVBox);
	this->show();



//	QObject::connect(heightMapModelRB, &QRadioButton::toggled,
//					 modifier, &SurfaceGraph::enableHeightMapModel);
//	QObject::connect(sqrtSinModelRB, &QRadioButton::toggled,
//					 modifier, &SurfaceGraph::enableSqrtSinModel);



//	sqrtSinModelRB->setChecked(true);

}
