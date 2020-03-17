#ifndef TABLEOPERATEITEM_H
#define TABLEOPERATEITEM_H

#include <QWidget>
#include "ThreeDog/tdpushbutton.h"
namespace Ui {
class TableOperateItem;
}

class TableOperateItem : public QWidget
{
	Q_OBJECT

public:
	explicit TableOperateItem(int id,QWidget *parent = 0);
	~TableOperateItem();
signals:
	void alterIed(int id);
	void channelConfig(int id);
	void download(int id);
	void deleteRow(int id);

private slots:
	void on_pushButton_clicked();

	void on_pushButton_2_clicked();

	void deleteBtnClicked();

	void on_pushButton_3_clicked();

private:
	Ui::TableOperateItem *ui;
	int m_iId;
};

#endif // TABLEOPERATEITEM_H
