﻿#include "mainwindow.h"
#include <QFontDialog>
#include <sstream>
#include <QDialog>
#include "ui_mainwindow.h"

MainWindow::MainWindow(QApplication* parent) :
	QMainWindow(), ui(new Ui::MainWindow) {
	ui->setupUi(this);

	move(360, 50);

	help = new QDialog(this);

	fileMenu = menuBar()->addMenu(tr("&File"));
	editMenu = menuBar()->addMenu(tr("&Edit"));
	formatMenu = menuBar()->addMenu(tr("&Format"));
	viewMenu = menuBar()->addMenu(tr("&View"));

	findDialog = new QDialog(this);
	findDialog->setWindowTitle(tr("Find"));

	QGridLayout* grid = new QGridLayout(findDialog);
	word = new QLineEdit(findDialog);
	QPushButton* findButton = new QPushButton(tr("&Find"), findDialog);
	connect(findButton, SIGNAL(clicked()), this, SLOT(findAnother()));
	grid->addWidget(word, 0, 1);
	grid->addWidget(findButton, 0, 2);

	replaceDialog = new QDialog(this);
	replaceDialog->setWindowTitle(tr("Find and Replace"));

	QGridLayout* grid1 = new QGridLayout(replaceDialog);
	word2 = new QLineEdit(replaceDialog);
	word3 = new QLineEdit(replaceDialog);
	QLabel* FindingWord = new QLabel(tr("Find word"));
	QLabel* ReplaceOn = new QLabel(tr("Replace on"));
	QPushButton* findButton2 = new QPushButton(tr("&Find"), replaceDialog);
	QPushButton* replaceButton = new QPushButton(tr("&Replace"), replaceDialog);
	QPushButton* vypad = new QPushButton(tr("+"), findDialog);
	connect(vypad, SIGNAL(clicked()), this, SLOT(replace()));
	grid->addWidget(vypad, 0, 0);
	connect(findButton2, SIGNAL(clicked()), this, SLOT(findBut()));
	connect(replaceButton, SIGNAL(clicked()), this, SLOT(replaceBut()));
	grid1->addWidget(FindingWord, 0, 0);
	grid1->addWidget(word2, 0, 1);
	grid1->addWidget(findButton2, 0, 2);
	grid1->addWidget(ReplaceOn, 1, 0);
	grid1->addWidget(word3, 1, 1);
	grid1->addWidget(replaceButton, 1, 2);

	openAction = new QAction(tr("&Open"), this);
	connect(openAction, SIGNAL(triggered()), this, SLOT(open()));
	saveAsAction = new QAction(tr("&Save as"), this);
	connect(saveAsAction, SIGNAL(triggered()), this, SLOT(saveAs()));
	exitAction = new QAction(tr("&Quit"), this);
	connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));
	newAction = new QAction(tr("&New"), this);
	connect(newAction, SIGNAL(triggered()), this, SLOT(newFile()));
	saveAction = new QAction(tr("&Save"), this);
	connect(saveAction, SIGNAL(triggered()), this, SLOT(save()));
	aboutAction = new QAction(tr("&About"), this);
	connect(aboutAction, SIGNAL(triggered()), this, SLOT(about()));
	settingAction = new QAction(tr("&Save settings"), this);
	connect(settingAction, SIGNAL(triggered()), this, SLOT(saveSettings()));
	menuBar()->addAction(aboutAction);

	fileMenu->addAction(newAction);
	fileMenu->addAction(openAction);
	fileMenu->addAction(saveAction);
	fileMenu->addAction(saveAsAction);
	fileMenu->addSeparator();
	fileMenu->addAction(settingAction);
	fileMenu->addSeparator();
	fileMenu->addAction(exitAction);

	undoAction = new QAction(tr("&Undo"), this);
	connect(undoAction, SIGNAL(triggered()), this, SLOT(undo()));
	redoAction = new QAction(tr("&Redo"), this);
	connect(redoAction, SIGNAL(triggered()), this, SLOT(redo()));
	copyAction = new QAction(tr("&Copy"), this);
	connect(copyAction, SIGNAL(triggered()), this, SLOT(copy()));
	cutAction = new QAction(tr("&Cut"), this);
	connect(cutAction, SIGNAL(triggered()), this, SLOT(cut()));
	pasteAction = new QAction(tr("&Paste"), this);
	connect(pasteAction, SIGNAL(triggered()), this, SLOT(paste()));
	findAction = new QAction(tr("&Find"), this);
	connect(findAction, SIGNAL(triggered()), this, SLOT(find()));
	findAndReplaceAction = new QAction(tr("&Find and Replace"), this);
	connect(findAndReplaceAction, SIGNAL(triggered()), this, SLOT(replace()));
	selectAllAction = new QAction(tr("&Select all"), this);
	connect(selectAllAction, SIGNAL(triggered()), this, SLOT(selectAll()));

	editMenu->addAction(undoAction);
	editMenu->addAction(redoAction);
	editMenu->addAction(copyAction);
	editMenu->addAction(cutAction);
	editMenu->addAction(pasteAction);
	editMenu->addAction(findAction);
	editMenu->addAction(findAndReplaceAction);
	editMenu->addAction(selectAllAction);

	wrapAction = new QAction(tr("&Wrap"), this);
	wrapAction->setCheckable(true);
	connect(wrapAction, SIGNAL(triggered()), this, SLOT(changeWrap()));
	fontAction = new QAction(tr("&Font"), this);
	connect(fontAction, SIGNAL(triggered()), this, SLOT(changeFont()));

	formatMenu->addAction(wrapAction);
	formatMenu->addAction(fontAction);

	backgroundAction = new QAction(tr("&Background"), this);
	connect(backgroundAction, SIGNAL(triggered()), SLOT(changeBackColor()));
	colorAction = new QAction(tr("&Line color"), this);
	connect(colorAction, SIGNAL(triggered()), this, SLOT(changeRowColor()));
	numberAction = new QAction(tr("&Number"), this);
	numberAction->setCheckable(true);
	numberAction->setChecked(true);
	connect(numberAction, SIGNAL(triggered()), this, SLOT(numberVisible()));
	panelAction = new QAction(tr("&Panel"), this);
	panelAction->setCheckable(true);
	panelAction->setChecked(true);
	connect(panelAction, SIGNAL(triggered()), this, SLOT(panelVisible()));
	statusAction = new QAction(tr("&Status"), this);
	statusAction->setCheckable(true);
	statusAction->setChecked(true);
	connect(statusAction, SIGNAL(triggered()), this, SLOT(statusVisible()));
	highlightAction = new QAction(tr("&Highlight"), this);
	highlightAction->setCheckable(true);
	connect(highlightAction, SIGNAL(triggered()), this, SLOT(isHighlighted()));
	syntaxMenu = new QMenu(tr("&Syntax"), this);
	syntaxMenu->setEnabled(false);
	styleMenu = new QMenu(tr("&Style"), this);
	styleMenu->setEnabled(false);
	//chooseSyntax = syntaxMenu->addMenu(tr("&Choose syntax"));
	C11 = new QAction(tr("&C 11"));
	C11->setCheckable(true);
	C11->setChecked(true);
	connect(C11, SIGNAL(triggered()), this, SLOT(setC11()));
	CPP14 = new QAction(tr("&C++ 14"));
	CPP14->setCheckable(true);
	connect(CPP14, SIGNAL(triggered()), this, SLOT(setCPP14()));
	C18 = new QAction(tr("&C 18"));
	C18->setCheckable(true);
	connect(C18, SIGNAL(triggered()), this, SLOT(setC18()));
	CPP17 = new QAction(tr("&C++ 17"));
	CPP17->setCheckable(true);
	connect(CPP17, SIGNAL(triggered()), this, SLOT(setCPP17()));
	CPP20 = new QAction(tr("&C++ 20"));
	CPP20->setCheckable(true);
	connect(CPP14, SIGNAL(triggered()), this, SLOT(setCPP20()));
	QActionGroup* languages = new QActionGroup(this);
	languages->addAction(C11);
	languages->addAction(CPP14);
	languages->addAction(C18);
	languages->addAction(CPP17);
	languages->addAction(CPP20);
	syntaxMenu->addAction(C11);
	syntaxMenu->addAction(CPP14);
	syntaxMenu->addAction(C18);
	syntaxMenu->addAction(CPP17);
	syntaxMenu->addAction(CPP20);

	viewMenu->addAction(backgroundAction);
	viewMenu->addAction(colorAction);
	viewMenu->addAction(numberAction);
	viewMenu->addAction(panelAction);
	viewMenu->addAction(statusAction);
	viewMenu->addAction(highlightAction);
	viewMenu->addMenu(syntaxMenu);
	viewMenu->addMenu(styleMenu);

	stylesGroup = new QActionGroup(this);

	editStyle = new QAction(tr("&Edit style"), this);
	connect(editStyle, SIGNAL(triggered()), this, SLOT(editStyleFile()));
	openStyle = new QAction(tr("&Open style"), this);
	connect(openStyle, SIGNAL(triggered()), this, SLOT(openStyleFile()));
	defaultStyle = new QAction(tr("default"), this);
	defaultStyle->setCheckable(true);
	defaultStyle->setChecked(true);
	stylesGroup->addAction(defaultStyle);

	styleMenu->addAction(editStyle);
	styleMenu->addAction(openStyle);
	styleMenu->addSeparator();
	styleMenu->addAction(defaultStyle);
	connect(defaultStyle, SIGNAL(triggered()), this, SLOT(changeStyle()));

	newAction1 = new QAction(QPixmap("new.ico"), tr("&New"), this);
	connect(newAction1, SIGNAL(triggered()), this, SLOT(newFile()));
	openAction1 = new QAction(QPixmap("open.ico"), tr("&Open"), this);
	connect(openAction1, SIGNAL(triggered()), this, SLOT(open()));
	saveAction1 = new QAction(QPixmap("save.ico"), tr("&Save"), this);
	connect(saveAction1, SIGNAL(triggered()), this, SLOT(save()));
	undoAction1 = new QAction(QPixmap("cancel.ico"), tr("&Undo"), this);
	connect(undoAction1, SIGNAL(triggered()), this, SLOT(undo()));
	redoAction1 = new QAction(QPixmap("redo.ico"), tr("&Redo"), this);
	connect(redoAction1, SIGNAL(triggered()), this, SLOT(redo()));
	copyAction1 = new QAction(QPixmap("copy.ico"), tr("&Copy"), this);
	connect(copyAction1, SIGNAL(triggered()), this, SLOT(copy()));
	cutAction1 = new QAction(QPixmap("cut.ico"), tr("&Cut"), this);
	connect(cutAction1, SIGNAL(triggered()), this, SLOT(cut()));
	pasteAction1 = new QAction(QPixmap("insert.ico"), tr("&Paste"), this);
	connect(pasteAction1, SIGNAL(triggered()), this, SLOT(paste()));
	findAction1 = new QAction(QPixmap("find.ico"), tr("&Find"), this);
	connect(findAction1, SIGNAL(triggered()), this, SLOT(find()));
	findAndReplaceAction1 = new QAction(QPixmap("replace.ico"), 
		tr("&Find and Replace"), this);
	connect(findAndReplaceAction1, SIGNAL(triggered()), this, SLOT(replace()));

	ui->toolBar->addAction(newAction1);
	ui->toolBar->addAction(openAction1);
	ui->toolBar->addAction(saveAction1);
	ui->toolBar->addAction(undoAction1);
	ui->toolBar->addAction(redoAction1);
	ui->toolBar->addAction(copyAction1);
	ui->toolBar->addAction(cutAction1);
	ui->toolBar->addAction(pasteAction1);
	ui->toolBar->addAction(findAction1);

	textEdit = new CodeEditor(this);
	connect(textEdit, SIGNAL(textChanged()), this, SLOT(changedText()));
	connect(textEdit, SIGNAL(cursorPositionChanged()), SLOT(cursorPosChanged()));
	setCentralWidget(textEdit);

	cursorInfo = new QLabel(QString("Cursor position: ") + QString::number(0) + 
		" " + QString::number(0), this);
	lastInfo = new QLabel(tr("Last action: "), this);
	linesInfo = new QLabel(tr("Lines: 1"), this);
	wordInfo = new QLabel(tr("Words: 0"), this);
	charInfo = new QLabel(tr("Chars: 0"), this);
	sizeInfo = new QLabel(tr("Size: "), this);

	statusBar()->addWidget(cursorInfo);
	statusBar()->addWidget(lastInfo);
	statusBar()->addWidget(linesInfo);
	statusBar()->addWidget(wordInfo);
	statusBar()->addWidget(charInfo);
	statusBar()->addWidget(sizeInfo);

	QDir directory("./");
	QStringList styles = directory.entryList( 
		QStringList() << "*.style", QDir::Files);

	for (auto elem : styles)
	{
		QString nameF = elem.left(elem.size() - 6);
		QAction* newStyleAct = new QAction(nameF, this);
		stylesAction.push_back(newStyleAct);
		styleMenu->addAction(stylesAction[stylesAction.length() - 1]);
		stylesAction[stylesAction.length() - 1]->setCheckable(true);
		connect(stylesAction[stylesAction.length() - 1], SIGNAL(triggered()), this, SLOT(changeStyle()));
		stylesGroup->addAction(stylesAction[stylesAction.length() - 1]);
	}
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::open() {
	QString fileName = QFileDialog::getOpenFileName(this,
		tr("Open file"), "",
		tr("Text files (*.txt);;C/C++ files (*.c *.cpp *.h *.hpp)"));
	if (fileName != "") {
		QFile file(fileName);
		file.open(QIODevice::ReadOnly);
		QTextStream in(&file);
		textEdit->setPlainText(in.readAll());
		fileinfo = file;
		file.close();
		sizeInfo->setText("Size: " +
			QString::number(fileinfo.size() / 1024) + " KB");
		lastInfo->setText("Last action: " +
			fileinfo.lastModified().toString("hh:mm:ss dd.MM.yyyy"));
	}
	else fileName = "MainWindow";

	oldStr = textEdit->toPlainText();

	statusBar()->update();
	setWindowTitle(fileName);
}

void MainWindow::newFile()
{
	oldStr = "";
	textEdit->clear();
	sizeInfo->setText("Size: ");
	lastInfo->setText("Last action: ");
	statusBar()->update();
	setWindowTitle("MainWindow");
}

void MainWindow::saveAs() {
	QString fileName = QFileDialog::getSaveFileName(this,
		tr("Save file"), "",
		tr("Text files (*.txt);;C/C++ files (*.c *.cpp *.h *.hpp)"));

	if (fileName != "") {
		QFile file(fileName);
		file.open(QIODevice::WriteOnly);
		QTextStream stream(&file);
		stream << textEdit->toPlainText();
		stream.flush();
		fileinfo = file;
		sizeInfo->setText("Size: " + QString::number(fileinfo.size() / 1024)
			+ " KB");
		lastInfo->setText("Last action: "
			+ QDateTime::currentDateTime().toString(
				"hh:mm:ss dd.MM.yyyy"));

		file.close();
	}

	statusBar()->update();
	setWindowTitle(fileName);

	fileName = fileName.left(fileName.lastIndexOf("."));
	QFile log(fileName + ".log");

	if (log.exists())
	{
		if (log.open(QIODevice::Append))
		{
			QTextStream out(&log);
			out << QDateTime::currentDateTime().toString(
				"hh:mm:ss dd.MM.yyyy") << ": saved";
			log.close();
		}
	}
	else
	{
		if (log.open(QIODevice::WriteOnly))
		{
			QTextStream out(&log);
			out << QDateTime::currentDateTime().toString(
				"hh:mm:ss dd.MM.yyyy") << ": saved";
			log.close();
		}
	}
}

void MainWindow::save()
{
	QString filename = windowTitle();
	if (filename[0] == '*')
		filename.remove(0, 1);

	if (filename == "MainWindow")
		filename = QFileDialog::getSaveFileName(this, 
			tr("Save file"), "",
			tr("Text files (*.txt);;C/C++ files (*.c *.cpp *.h *.hpp)"));

	QFile file(filename);
	file.open(QIODevice::WriteOnly);
	QTextStream stream(&file);
	stream << textEdit->toPlainText();
	stream.flush();
	fileinfo = file;
	file.close();

	sizeInfo->setText("Size: " + QString::number(fileinfo.size() / 1024) + " KB");

	lastInfo->setText("Last action: " + QDateTime::currentDateTime().toString(
		"hh:mm:ss dd.MM.yyyy"));

	statusBar()->update();
	setWindowTitle(filename);

	filename = filename.left(filename.lastIndexOf("."));
	QFile log(filename + ".log");

	if (log.exists())
	{
		if (log.open(QIODevice::Append))
		{
			QTextStream out(&log);
			out << QDateTime::currentDateTime().toString(
				"hh:mm:ss dd.MM.yyyy") << ": saved\n";
			log.close();
		}
	}
	else
	{
		if (log.open(QIODevice::WriteOnly))
		{
			QTextStream out(&log);
			out << QDateTime::currentDateTime().toString(
				"hh:mm:ss dd.MM.yyyy") << ": saved\n";
			log.close();
		}
	}

}

void MainWindow::about()
{
	help->setWindowTitle(tr("About"));
	QGridLayout* grid = new QGridLayout(this);
	QGridLayout* subGrid = new QGridLayout(this);

	QPixmap* photo = new QPixmap("photo.JPG");
	QLabel* labelPhoto = new QLabel(this);
	labelPhoto->setPixmap(*photo);

	QLabel* name = new QLabel(tr("Zilbershtein Pavel"), this);

	QFont font = name->font();
	font.setPixelSize(20);
	font.setFamily("Times New Roman");
	name->setFont(font);

	QLabel* DateTime = new QLabel(QString(__DATE__) + " "
		+ QString(__TIME__), this);
	QLabel* buildVersion = new QLabel(QT_VERSION_STR, this);
	QLabel* launchVersion = new QLabel(qVersion(), this);
	QLabel* info1 = new QLabel("Date and time of the build: ", this);
	QLabel* info2 = new QLabel("QT Build Version: ", this);
	QLabel* info3 = new QLabel("QT Launch Version: ", this);
	QPushButton* closeBut = new QPushButton(tr("&Close"), this);
	connect(closeBut, SIGNAL(clicked()), this, SLOT(closeHelp()));

	subGrid->addWidget(info1, 0, 0, Qt::AlignCenter);
	subGrid->addWidget(info2, 1, 0, Qt::AlignCenter);
	subGrid->addWidget(info3, 2, 0, Qt::AlignCenter);
	subGrid->addWidget(DateTime, 0, 1, Qt::AlignCenter);
	subGrid->addWidget(buildVersion, 1, 1, Qt::AlignCenter);
	subGrid->addWidget(launchVersion, 2, 1, Qt::AlignCenter);

	grid->addWidget(labelPhoto, 0, 0, Qt::AlignCenter);
	grid->addWidget(name, 1, 0, Qt::AlignCenter);
	grid->addLayout(subGrid, 2, 0, Qt::AlignCenter);
	grid->addWidget(closeBut, 3, 0, Qt::AlignCenter);

	help->setLayout(grid);

	help->exec();
}

void MainWindow::undo()
{
	textEdit->undo();
}

void MainWindow::redo()
{
	textEdit->redo();
}

void MainWindow::selectAll()
{
	textEdit->selectAll();
}

void MainWindow::cut()
{
	textEdit->cut();
}

void MainWindow::copy()
{
	textEdit->copy();
}

void MainWindow::paste()
{
	textEdit->paste();
}

void MainWindow::changeWrap()
{
	wrapped = wrapAction->isChecked();

	if (wrapped)
		textEdit->setWordWrapMode(QTextOption::WordWrap);
	else
		textEdit->setWordWrapMode(QTextOption::WrapAtWordBoundaryOrAnywhere);
}

void MainWindow::changeFont()
{
	bool bOk;
	QFont fnt = QFontDialog::getFont(&bOk);
	if (bOk)
		textEdit->setFont(fnt);
}

void MainWindow::find()
{
	replaceDialog->hide();
	findDialog->show();
}

void MainWindow::replace()
{
	findDialog->hide();
	replaceDialog->show();
}

void MainWindow::findBut()
{
	QString str = word2->text();
	textEdit->find(str);
	replaceDialog->hide();
	replaceDialog->show();
}

void MainWindow::replaceBut()
{
	QString found = word2->text();

	textEdit->textCursor().insertText(word3->text());
}

void MainWindow::findAnother()
{
	QString str = word->text();
	textEdit->find(str);
	findDialog->hide();
	findDialog->show();
}

void MainWindow::changedText()
{
	if (windowTitle() != "MainWindow" && windowTitle()[0] != '*')
	{
		setWindowTitle("*" + windowTitle());
	}

	QString text = textEdit->toPlainText();

	std::stringstream ss(text.toStdString());

	std::string strbuf = ss.str();

	std::string word;

	std::size_t wordCount = 0;
	while (ss >> word)
		if (!(word.size() == 1 && (word[0] == '{' || word[0] == '}')))
			wordCount++;

	linesInfo->setText("Lines: " + QString::number(textEdit->blockCount()));
	wordInfo->setText("Words: " + QString::number(wordCount));
	charInfo->setText("Chars: " + 
		QString::number(textEdit->toPlainText().length()));
	lastInfo->setText("Last action: " + QDateTime::currentDateTime().toString(
		"hh:mm:ss dd.MM.yyyy"));
	statusBar()->update();

	if (windowTitle() != "MainWindow")
	{
		QString filename = windowTitle();

		if (filename[0] == '*')
			filename.remove(0, 1);

		filename = filename.left(filename.lastIndexOf("."));

		QString message = ": ";

		QFile log(filename + ".log");

		QString newStr = textEdit->toPlainText();

		QString diff;

		if (newStr.length() > oldStr.length())
		{
			message += "added %1";

			for (int i{ 0 }; i < newStr.length(); ++i)
			{
				if (oldStr[i] != newStr[i])
				{
					diff += newStr[i];
					newStr.remove(i, 1);
					--i;
				}
			}
		}
		else if (newStr.length() < oldStr.length())
		{
			message += "deleted %1";

			for (int i{ 0 }; i < oldStr.length(); ++i)
			{
				if (oldStr[i] != newStr[i])
				{
					diff += oldStr[i];
					oldStr.remove(i, 1);
					--i;
				}
			}
		}

		QChar symb = diff[0];

		if (!symb.isSpace())
			message = message.arg("\"");
		else
			message = message.arg("");

		if (diff == "\n")
			diff = "\\n";
		else if (diff == "\t")
			diff = "\\t";
		else if (diff == "\f")
			diff = "\\f";
		else if (diff == "\r")
			diff = "\\r";
		else if (diff == "\v")
			diff = "\\v";

		message += diff;

		if (!symb.isSpace())
			message += "\"\n";
		else
			message += '\n';
		
		if (log.exists())
		{
			if (log.open(QIODevice::Append))
			{
				QTextStream out(&log);
				out << QDateTime::currentDateTime().toString(
					"hh:mm:ss dd.MM.yyyy") << message;
				log.close();
			}
		}
		else
		{
			if (log.open(QIODevice::WriteOnly))
			{
				QTextStream out(&log);
				out << QDateTime::currentDateTime().toString(
					"hh:mm:ss dd.MM.yyyy") << message;
				log.close();
			}
		}
	}

	oldStr = textEdit->toPlainText();
}

void MainWindow::panelVisible()
{
	panelVis = panelAction->isChecked();
	ui->toolBar->setVisible(panelVis);
}

void MainWindow::statusVisible()
{
	statusVis = statusAction->isChecked();
	ui->statusBar->setVisible(statusVis);
}

void MainWindow::numberVisible()
{
	numberVis = numberAction->isChecked();
	textEdit->lineNumberArea->setVisible(numberVis);
}

void MainWindow::isHighlighted()
{
	QString curLang;
	if (isC11)
		curLang = "C11";
	else if (isCPP14)
		curLang = "C++14";
	else if (isC18)
		curLang = "C18";
	else if (isCPP17)
		curLang = "C++17";
	else if (isCPP20)
		curLang = "C++20";

	highlighted = highlightAction->isChecked();
	syntaxMenu->setEnabled(highlighted);
	styleMenu->setEnabled(highlighted);

	if (!highlighted)
		highlite->deleteLater();
	else
		highlite = new Highlighter(curLang, keywordColor, singleCommentColor, 
			multiCommentColor, quotationColor, 
			functionColor, textEdit->document());
}

void MainWindow::changeBackColor()
{
	QColor color = QColorDialog::getColor(Qt::white);
	QString str = "background-color: %1;";

	if (color.isValid()) {
		str = str.arg(color.name());
		textEdit->setStyleSheet(str);
		backColor = color;
	}
}

void MainWindow::changeRowColor()
{
	QColor color = QColorDialog::getColor(Qt::white);

	if (color.isValid())
		rowColor = color;

	emit textEdit->cursorPositionChanged();
}

void MainWindow::cursorPosChanged()
{
	QTextCursor cursor1 = textEdit->textCursor();
	int row = cursor1.blockNumber();

	QTextEdit::ExtraSelection selection;
	QTextCursor cursor = QTextCursor(textEdit->document());
	cursor.movePosition(QTextCursor::Start);
	cursor.movePosition(QTextCursor::Down, QTextCursor::MoveAnchor, row);
	cursor.select(QTextCursor::LineUnderCursor);
	QTextCharFormat format;
	QColor col = rowColor;
	format.setBackground(col);
	selection.cursor = cursor;
	selection.format = format;
	textEdit->setExtraSelections(QList<QTextEdit::ExtraSelection>() 
		<< selection);

	int lineCur = textEdit->textCursor().blockNumber();
	int colCur = textEdit->textCursor().positionInBlock();

	cursorInfo->setText(QString("Cursor position: ") + QString::number(lineCur)
		+ ":" + QString::number(colCur));

	statusBar()->update();
}

void MainWindow::setC11()
{
	isC11 = true;
	isCPP14 = false;
	isC18 = false;
	isCPP17 = false;
	isCPP20 = false;
	isHighlighted();
}

void MainWindow::setCPP14()
{
	isC11 = false;
	isCPP14 = true;
	isC18 = false;
	isCPP17 = false;
	isCPP20 = false;
	isHighlighted();
}

void MainWindow::setC18()
{
	isC11 = false;
	isCPP14 = false;
	isC18 = true;
	isCPP17 = false;
	isCPP20 = false;
	isHighlighted();
}

void MainWindow::setCPP17()
{
	isC11 = false;
	isCPP14 = false;
	isC18 = false;
	isCPP17 = true;
	isCPP20 = false;
	isHighlighted();
}

void MainWindow::setCPP20()
{
	isC11 = false;
	isCPP14 = false;
	isC18 = false;
	isCPP17 = false;
	isCPP20 = true;
	isHighlighted();
}

void MainWindow::closeHelp()
{
	help->close();
}

void MainWindow::saveSettings()
{
	QSettings settings("settings.ini", QSettings::IniFormat);

	settings.beginGroup("Settings");
	settings.setValue("geometry", geometry());
	settings.setValue("font", textEdit->font());
	settings.setValue("wrapped", wrapped);
	settings.setValue("highlighted", highlighted);
	settings.setValue("panelVis", panelVis);
	settings.setValue("statusVis", statusVis);
	settings.setValue("numberVis", numberVis);
	settings.setValue("isC11", isC11);
	settings.setValue("isC18", isC18);
	settings.setValue("isCPP14", isCPP14);
	settings.setValue("isCPP17", isCPP17);
	settings.setValue("isCPP20", isCPP20);
	settings.setValue("BackgroundColor", backColor);
	settings.setValue("LineColor", rowColor);
	settings.setValue("TimeOfFormationOfTheSettingsFile", 
		QDateTime::currentDateTime());
	settings.endGroup();
}

void MainWindow::openStyleFile()
{
	QString filename = QFileDialog::getOpenFileName(this,
		tr("Open file"), "",
		tr("Style files (*.style)"));

	if (filename != "") {
		QFile file(filename);
		file.open(QIODevice::ReadOnly);

		QSettings settings(filename, QSettings::IniFormat);
		settings.beginGroup("Colors");

		keywordColor.setNamedColor(settings.value("keyword").toString());
		singleCommentColor.setNamedColor(
			settings.value("singleComment").toString());
		multiCommentColor.setNamedColor(
			settings.value("multiComment").toString());
		quotationColor.setNamedColor(settings.value("quotation").toString());
		functionColor.setNamedColor(settings.value("function").toString());
		settings.endGroup();

		file.close();

		setWindowTitle(filename);

		isHighlighted();
	}
}

void MainWindow::editStyleFile()
{
	QDialog diag;
	QGridLayout* grid = new QGridLayout(this);
	QGridLayout* subgrid = new QGridLayout(this);
	QGridLayout* subgridButs = new QGridLayout(this);

	QLabel* StylenameLabel = new QLabel(tr("Name of style: "), this);
	QLabel* keywordColorLabel = new QLabel(tr("Color for keywords: "), this);
	QLabel* singleCommentColorLabel = new QLabel(tr(
		"Color for singleline comments: "), this);
	QLabel* multiCommentColorLabel = new QLabel(tr(
		"Color for multiline comments: "), this);
	QLabel* quotationColorLabel = new QLabel(tr("Color for quotations: "), this);
	QLabel* functionColorLabel = new QLabel(tr("Color for functions: "), this);

	QLineEdit* StylenameEdit = new QLineEdit(this);

	QLineEdit* keywordColorEdit = new QLineEdit(this);
	keywordColorEdit->setText(QColor(Qt::white).name());

	QLineEdit* singleCommentColorEdit = new QLineEdit(this);
	singleCommentColorEdit->setText(QColor(Qt::white).name());

	QLineEdit* multiCommentColorEdit = new QLineEdit(this);
	multiCommentColorEdit->setText(QColor(Qt::white).name());

	QLineEdit* quotationColorEdit = new QLineEdit(this);
	quotationColorEdit->setText(QColor(Qt::white).name());

	QLineEdit* functionColorEdit = new QLineEdit(this);
	functionColorEdit->setText(QColor(Qt::white).name());

	QPushButton* button = new QPushButton(tr("HTML of colors"), this);
	connect(button, SIGNAL(clicked()), this, SLOT(chooseColor()));

	QPushButton* acceptBut = new QPushButton(tr("&Accept"), this);
	connect(acceptBut, SIGNAL(clicked()), &diag, SLOT(accept()));

	subgrid->addWidget(StylenameLabel, 0, 0);
	subgrid->addWidget(keywordColorLabel, 1, 0);
	subgrid->addWidget(singleCommentColorLabel, 2, 0);
	subgrid->addWidget(multiCommentColorLabel, 3, 0);
	subgrid->addWidget(quotationColorLabel, 4, 0);
	subgrid->addWidget(functionColorLabel, 5, 0);
	subgrid->addWidget(StylenameEdit, 0, 1);
	subgrid->addWidget(keywordColorEdit, 1, 1);
	subgrid->addWidget(singleCommentColorEdit, 2, 1);
	subgrid->addWidget(multiCommentColorEdit, 3, 1);
	subgrid->addWidget(quotationColorEdit, 4, 1);
	subgrid->addWidget(functionColorEdit, 5, 1);

	subgridButs->addWidget(acceptBut, 0, 0);
	subgridButs->addWidget(button, 0, 1);

	grid->addLayout(subgrid, 0, 0);
	grid->addLayout(subgridButs, 1, 0);

	diag.setLayout(grid);

	if (diag.exec() == QDialog::Accepted)
	{
		if (QColor::isValidColor(keywordColorEdit->text()) &&
			QColor::isValidColor(singleCommentColorEdit->text()) &&
			QColor::isValidColor(multiCommentColorEdit->text()) &&
			QColor::isValidColor(quotationColorEdit->text()) &&
			QColor::isValidColor(functionColorEdit->text()) &&
			StylenameEdit->text().size() != 0)
		{
			keywordColor.setNamedColor(keywordColorEdit->text());
			singleCommentColor.setNamedColor(
				singleCommentColorEdit->text());
			multiCommentColor.
				setNamedColor(multiCommentColorEdit->text());
			quotationColor.setNamedColor(
				quotationColorEdit->text());
			functionColor.setNamedColor(functionColorEdit->text());

			QSettings settings(StylenameEdit->text() + ".style",
				QSettings::IniFormat);
			settings.beginGroup("Colors");
			settings.setValue("keyword", keywordColor.name());
			settings.setValue("singleComment", singleCommentColor.name());
			settings.setValue("multiComment", multiCommentColor.name());
			settings.setValue("quotation", quotationColor.name());
			settings.setValue("function", functionColor.name());
			settings.endGroup();

			QAction* newStyleAction = new QAction(
				StylenameEdit->text(), this);
			stylesAction.push_back(newStyleAction);
			styleMenu->addAction(stylesAction[stylesAction.length() - 1]);
			stylesAction[stylesAction.length() - 1]->
				setCheckable(true);
			stylesGroup->addAction(
				stylesAction[stylesAction.length() - 1]);
			connect(stylesAction[stylesAction.length() - 1], 
				SIGNAL(triggered()), this, SLOT((changeStyle())));
			isHighlighted();
		}
	}
}

void MainWindow::changeStyle()
{
	QAction* actionSender = static_cast<QAction*>(sender());
	QString filename = actionSender->text() + ".style";

	if (filename != "" && filename != "default.style") {
		QFile file(filename);
		file.open(QIODevice::ReadOnly);

		QSettings settings(filename, QSettings::IniFormat);
		settings.beginGroup("Colors");

		keywordColor.setNamedColor(settings.value("keyword").toString());
		singleCommentColor.setNamedColor(
			settings.value("singleComment").toString());
		multiCommentColor.setNamedColor(
			settings.value("multiComment").toString());
		quotationColor.setNamedColor(settings.value("quotation").toString());
		functionColor.setNamedColor(settings.value("function").toString());
		settings.endGroup();

		file.close();

		setWindowTitle(filename);

		isHighlighted();
	}

	if (filename == "default.style")
	{
		keywordColor = Qt::darkBlue;
		singleCommentColor = Qt::red;
		multiCommentColor = Qt::red;
		quotationColor = Qt::darkGreen;
		functionColor = Qt::blue;

		isHighlighted();

		setWindowTitle("default style");
	}
}

void MainWindow::chooseColor()
{
	QColorDialog::getColor(Qt::white);
}
