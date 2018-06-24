#include "mainwindow.h"

#include "setupdialog.h"
#include "imagecarousel.h"

#include <QShortcut>
#include <QDebug>


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {

	imageCarousel = new ImageCarousel(this);
	setCentralWidget(imageCarousel);


	// Set fullscreen shortcut
	QShortcut* toggleFullscreenShortcut = new QShortcut(QKeySequence(tr("Ctrl+F")), this);
	toggleFullscreenShortcut->setContext(Qt::ApplicationShortcut);
	connect(toggleFullscreenShortcut, SIGNAL(activated()), this, SLOT(toggleFullscreen()));

	// Open dialog on startup
	openSetupDialog();

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
	if (d.exec()) {
		qDebug() << "OK";
	}

}
