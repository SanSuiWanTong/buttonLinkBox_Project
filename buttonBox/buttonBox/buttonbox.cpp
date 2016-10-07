#include "buttonbox.h"

//
urlBtn::urlBtn(QWidget *parent)
	: QPushButton(parent)
	,m_Title("")
	,m_Url("")
{
	connect(this, SIGNAL(clicked()), this, SLOT(on_openUrl()));
}

urlBtn::~urlBtn()
{

}
void urlBtn::on_openUrl()
{
	if (m_Url.isEmpty()) return;
	QDesktopServices::openUrl(QUrl(m_Url));
}

////
buttonBox::buttonBox(QWidget *parent)
	: QMainWindow(parent)
{
	//
	createCenterWidget();

	//
	importFile("urlCfg.txt");

	//
	ui.setupUi(this);	
}

buttonBox::~buttonBox()
{

}

void    buttonBox::createCenterWidget()
{
	auto centerWidget = new QTabWidget(this);
	this->setCentralWidget(centerWidget);
}

QGridLayout*   buttonBox::createLayout(QWidget* w)
{
	return new QGridLayout(w);	
}

bool    buttonBox::importFile(const QString& filePath)
{
	QFile file(filePath);
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
		return false;

	QTextStream in(&file);
	while (!in.atEnd()) {
		QString line = in.readLine();
		analyLine(line);
	}
	
	return true;
}

/* --  ×¢ÊÍ */
void	buttonBox::analyLine(const QString& line)
{	
	auto lineStr = line.trimmed();
	auto optCode = lineStr.left(2);
	
	//jump invalid line
	if (lineStr.isEmpty() || ("--" == optCode))	return;

	//tabTitle
	static QString		st_tabTitle   = "";
	static int          st_lineNum    = 0;
	static QGridLayout*	st_gridLayOut = nullptr;

	if (optCode == "%T")
	{
		st_lineNum = 0;
		st_tabTitle = lineStr.split(" ").at(1).trimmed();		
		
		//
		auto w = new QWidget();
		st_gridLayOut = this->createLayout(w);
		dynamic_cast<QTabWidget*>(this->centralWidget())->addTab(w, st_tabTitle);
		
		return;
	}

	//generate btn
	QStringList matchList = lineStr.split(QRegExp("\\s{1,}"));
	auto btnTitle = matchList.at(0);
	auto btnUrl   = matchList.at(1);
	
	auto tBtn = createBtn();
	tBtn->_setTitle(btnTitle);
	tBtn->_setUrl(btnUrl);
	
	const int col = 10;
	st_gridLayOut->addWidget(tBtn, st_lineNum / col, st_lineNum % col);	

	st_lineNum++;
}

urlBtn* buttonBox::createBtn()
{
	return new urlBtn(this);
}