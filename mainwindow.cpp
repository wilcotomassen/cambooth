#include "mainwindow.h"

#include "setupdialog.h"
#include "imagecarousel.h"
#include "cameradialog.h"
//#include "picturereviewdialog.h"

#include <QShortcut>
#include <QApplication>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {

	// Open dialog on startup
	openSetupDialog();

	// Setup image carousel
	imageCarousel = new ImageCarousel(this);
	setCentralWidget(imageCarousel);

	// Setup call to action
	setupCallToAction();

	// Set fullscreen shortcut
	QShortcut* toggleFullscreenShortcut = new QShortcut(QKeySequence(tr("Ctrl+F")), this);
	toggleFullscreenShortcut->setContext(Qt::ApplicationShortcut);
	connect(toggleFullscreenShortcut, SIGNAL(activated()), this, SLOT(toggleFullscreen()));

	// Set quit shortcut
	QShortcut* quitShortcut = new QShortcut(QKeySequence(tr("Ctrl+Shift+Q")), this);
	quitShortcut->setContext(Qt::ApplicationShortcut);
	connect(quitShortcut, SIGNAL(activated()), QApplication::instance(), SLOT(quit()));

	// Go fullscreen
	this->setWindowState(Qt::WindowFullScreen);

}

MainWindow::~MainWindow() {}

void MainWindow::setupCallToAction() {

	QFont uiFont;
	uiFont.setPixelSize(16);

	// Call to action text
	QString content = "Hello<br />Foo bar baz";

	QLabel* callToActionText = new QLabel(this);
	callToActionText->setTextFormat(Qt::RichText);
	callToActionText->setFont(uiFont);
	callToActionText->setAlignment(Qt::AlignCenter);
	callToActionText->setText(content);

	// Button
	QPushButton* takePictureBtn = new QPushButton(tr("Take picture"), this);
	takePictureBtn->setFont(uiFont);
	takePictureBtn->setStyleSheet("padding: 20px;");

	QHBoxLayout* btnLayout = new QHBoxLayout();
	btnLayout->addStretch();
	btnLayout->addWidget(takePictureBtn);
	btnLayout->addStretch();

	// Create widget
	QVBoxLayout* callToActionLayout = new QVBoxLayout();
	callToActionLayout->setMargin(40);
	callToActionLayout->addWidget(callToActionText);
	callToActionLayout->addLayout(btnLayout);

	callToActionWidget = new QWidget(this);
	callToActionWidget->setMinimumSize(640, 380);
	callToActionWidget->setLayout(callToActionLayout);
	callToActionWidget->move((width() - callToActionWidget->width()) / 2,
							 (height() - callToActionWidget->height()) / 2);

	// Apply palette (white background)
	QPalette pal = palette();
	pal.setColor(QPalette::Background, QColor(255, 255, 255, 180));
	callToActionWidget->setAutoFillBackground(true);
	callToActionWidget->setPalette(pal);

}

void MainWindow::toggleFullscreen() {
	if(isFullScreen()) {
		this->setWindowState(Qt::WindowMaximized);
	} else {
		this->setWindowState(Qt::WindowFullScreen);
	}
}

void MainWindow::openSetupDialog() {
	SetupDialog d(this);
	d.exec();
}

void MainWindow::resizeEvent(QResizeEvent*) {
	callToActionWidget->move((width() - callToActionWidget->width()) / 2,
							 (height() - callToActionWidget->height()) / 2);
}
