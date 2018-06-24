#include "mainwindow.h"

#include "setupdialog.h"
#include "imagecarousel.h"

#include <QShortcut>
#include <QApplication>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {

	// Open dialog on startup
	openSetupDialog();

	// Setup image carousel
	imageCarousel = new ImageCarousel(this);
	setCentralWidget(imageCarousel);

	// Set fullscreen shortcut
	QShortcut* toggleFullscreenShortcut = new QShortcut(QKeySequence(tr("Ctrl+F")), this);
	toggleFullscreenShortcut->setContext(Qt::ApplicationShortcut);
	connect(toggleFullscreenShortcut, SIGNAL(activated()), this, SLOT(toggleFullscreen()));

	// Set quit shortcut
	QShortcut* quitShortcut = new QShortcut(QKeySequence(tr("Ctrl+Shift+Q")), this);
	quitShortcut->setContext(Qt::ApplicationShortcut);
	connect(quitShortcut, SIGNAL(activated()), QApplication::instance(), SLOT(quit()));

	this->setWindowState(Qt::WindowFullScreen);
}

MainWindow::~MainWindow() {

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
