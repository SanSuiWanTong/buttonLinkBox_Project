#ifndef BUTTONBOX_H
#define BUTTONBOX_H

#include <QtWidgets/QMainWindow>
#include <QPushButton>
#include <QDesktopServices>
#include <QUrl>
#include <QGridLayout>
#include <QTabWidget>
#include <QFile>
#include <QTextStream>

#include "ui_buttonbox.h"

class urlBtn :public QPushButton
{
	Q_OBJECT

public:
	urlBtn(QWidget *parent = 0);
	~urlBtn();
	
	void _setTitle(const QString& str){ m_Title = str; setText(m_Title); }
	void _setUrl(const QString& str)  { m_Url   = str; }

public slots:
	void on_openUrl();

private:
	QString m_Title;
	QString m_Url;
}; 


class buttonBox : public QMainWindow
{
	Q_OBJECT

public:
	buttonBox(QWidget *parent = 0);
	~buttonBox();
	
private:
	void          createCenterWidget();
	bool          importFile(const QString& filePath);
	void          analyLine(const QString& line);
	QGridLayout*  createLayout(QWidget*);	
	urlBtn*       createBtn();

private:
	Ui::buttonBoxClass ui;	
};

#endif // BUTTONBOX_H
