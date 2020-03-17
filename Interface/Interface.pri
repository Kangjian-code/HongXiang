
INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

FORMS += \
	$$PWD/Sensor/alarmdesc.ui \
	$$PWD/Sensor/channelcompare.ui \
	$$PWD/Sensor/eventdesc.ui \
	$$PWD/mainpage.ui \
	$$PWD/Article/runstatepage.ui \
	$$PWD/Article/readtimedatapage.ui \
	$$PWD/Article/historydatapage.ui \
#    $$PWD/Article/warninginfopage.ui \
	$$PWD/Article/fingerprintlib.ui \
	$$PWD/Article/selfcheckpage.ui \
	$$PWD/Article/userpage.ui \
	$$PWD/Common/tableoperateitem.ui \
	$$PWD/Article/devicewarningpage.ui \
	$$PWD/Article/dischargewarningform.ui \
	$$PWD/Article/quakewarningform.ui \
	$$PWD/Article/datacheckpage.ui \
	$$PWD/Article/historytrendingpage.ui \
	$$PWD/Article/horizontalanalysispage.ui \
    $$PWD/Common/chartform.ui \
    $$PWD/Sensor/histroytrending.ui

HEADERS += \
	$$PWD/Sensor/alarmdesc.h \
	$$PWD/Sensor/channelcompare.h \
	$$PWD/Sensor/eventdesc.h \
	$$PWD/loginpage.h \
	$$PWD/mainpage.h \
	$$PWD/widget.h \
	$$PWD/ThreeDog/appinit.h \
	$$PWD/ThreeDog/iconhelper.h \
	$$PWD/ThreeDog/tdabstractbutton.h \
	$$PWD/ThreeDog/tdcheckbox.h \
	$$PWD/ThreeDog/tdfadeoutwidget.h \
	$$PWD/ThreeDog/tdlistwidget.h \
	$$PWD/ThreeDog/tdmenubutton.h \
	$$PWD/ThreeDog/tdpushbutton.h \
	$$PWD/ThreeDog/tdradiobutton.h \
	$$PWD/ThreeDog/tdradiobuttongroup.h \
	$$PWD/ThreeDog/tdscrollarea.h \
	$$PWD/ThreeDog/tdslider.h \
	$$PWD/ThreeDog/tdstackbutton.h \
	$$PWD/ThreeDog/tdtoolbar.h \
	$$PWD/ThreeDog/tdwidget.h \
	$$PWD/Article/article.h \
	$$PWD/Article/runstatepage.h \
	$$PWD/Article/readtimedatapage.h \
	$$PWD/Article/historydatapage.h \
#    $$PWD/Article/warninginfopage.h \
	$$PWD/Article/fingerprintlib.h \
	$$PWD/Article/selfcheckpage.h \
	$$PWD/Article/userpage.h \
	$$PWD/ThreeDog/tdmodal.h \
	$$PWD/ThreeDog/tdmessagebox.h \
	$$PWD/Common/configpage.h \
	$$PWD/Common/tablepage.h \
	$$PWD/Common/tableoperateitem.h \
	$$PWD/Config/unitconfig.h \
	$$PWD/Config/channelconfig.h \
	$$PWD/Config/siteconfig.h \
	$$PWD/Config/argsconfig.h \
	$$PWD/Config/softwareconfig.h \
	$$PWD/Common/myqheaderview.h \
	$$PWD/Article/devicewarningpage.h \
	$$PWD/Article/dischargewarningform.h \
	$$PWD/Article/quakewarningform.h \
	$$PWD/Config/addspacermodal.h \
	$$PWD/Article/imageindex.h \
	$$PWD/Common/sensoritem.h \
	$$PWD/ThreeDog/tdtreewidget.h \
	$$PWD/Config/editsensormodal.h \
	$$PWD/Config/addsensormodal.h \
	$$PWD/Config/addunitmodal.h \
	$$PWD/Article/datacheckpage.h \
	$$PWD/Article/historytrendingpage.h \
	$$PWD/Article/horizontalanalysispage.h \
    $$PWD/Common/chartform.h \
    $$PWD/Sensor/histroytrending.h

SOURCES += \
	$$PWD/Sensor/alarmdesc.cpp \
	$$PWD/Sensor/channelcompare.cpp \
	$$PWD/Sensor/eventdesc.cpp \
	$$PWD/loginpage.cpp \
	$$PWD/mainpage.cpp \
	$$PWD/widget.cpp \
	$$PWD/ThreeDog/appinit.cpp \
	$$PWD/ThreeDog/iconhelper.cpp \
	$$PWD/ThreeDog/tdabstractbutton.cpp \
	$$PWD/ThreeDog/tdcheckbox.cpp \
	$$PWD/ThreeDog/tdfadeoutwidget.cpp \
	$$PWD/ThreeDog/tdlistwidget.cpp \
	$$PWD/ThreeDog/tdmenubutton.cpp \
	$$PWD/ThreeDog/tdpushbutton.cpp \
	$$PWD/ThreeDog/tdradiobutton.cpp \
	$$PWD/ThreeDog/tdradiobuttongroup.cpp \
	$$PWD/ThreeDog/tdscrollarea.cpp \
	$$PWD/ThreeDog/tdslider.cpp \
	$$PWD/ThreeDog/tdstackbutton.cpp \
	$$PWD/ThreeDog/tdtoolbar.cpp \
	$$PWD/ThreeDog/tdwidget.cpp \
	$$PWD/Article/article.cpp \
	$$PWD/Article/runstatepage.cpp \
	$$PWD/Article/readtimedatapage.cpp \
	$$PWD/Article/historydatapage.cpp \
#    $$PWD/Article/warninginfopage.cpp \
	$$PWD/Article/fingerprintlib.cpp \
	$$PWD/Article/selfcheckpage.cpp \
	$$PWD/Article/userpage.cpp \
	$$PWD/ThreeDog/tdmodal.cpp \
	$$PWD/ThreeDog/tdmessagebox.cpp \
	$$PWD/Common/configpage.cpp \
	$$PWD/Common/tablepage.cpp \
	$$PWD/Common/tableoperateitem.cpp \
	$$PWD/Config/unitconfig.cpp \
	$$PWD/Config/channelconfig.cpp \
	$$PWD/Config/siteconfig.cpp \
	$$PWD/Config/argsconfig.cpp \
	$$PWD/Config/softwareconfig.cpp \
	$$PWD/Common/myqheaderview.cpp \
	$$PWD/Article/devicewarningpage.cpp \
	$$PWD/Article/dischargewarningform.cpp \
	$$PWD/Article/quakewarningform.cpp \
	$$PWD/Article/imageindex.cpp \
	$$PWD/Common/sensoritem.cpp \
	$$PWD/ThreeDog/tdtreewidget.cpp \
	$$PWD/Config/editsensormodal.cpp \
	$$PWD/Config/addspacermodal.cpp \
	$$PWD/Config/addsensormodal.cpp \
	$$PWD/Config/addunitmodal.cpp \
	$$PWD/Article/datacheckpage.cpp \
	$$PWD/Article/historytrendingpage.cpp \
	$$PWD/Article/horizontalanalysispage.cpp \
    $$PWD/Common/chartform.cpp \
    $$PWD/Sensor/histroytrending.cpp
