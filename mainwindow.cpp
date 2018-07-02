#include "mainwindow.h"

#include "setting_names.h"
#include "camera.h"
#include "setupdialog.h"
#include "imagecarousel.h"
#include "cameraview.h"
#include "reviewView.h"

#include <QStackedWidget>
#include <QShortcut>
#include <QApplication>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QSettings>
#include <QTime>
#include <QMessageBox>
#include <QFile>
#include <QFileInfo>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
	setMinimumSize(1024, 768);

	applyStyleSheet();

	// Open dialog on startup
	//openSetupDialog();

	// Setup views
	imageCarousel = new ImageCarousel(this);
	reviewView = new ReviewView(this);
	cameraView = new CameraView(this);

	widgetStack = new QStackedWidget(this);
	widgetStack->addWidget(imageCarousel);
	widgetStack->addWidget(cameraView);
	widgetStack->addWidget(reviewView);
	setCentralWidget(widgetStack);

	// Setup camera
	camera = new Camera(this);
	camera->setViewfinder(cameraView);

	// Add connections
	connect(camera, SIGNAL(imageCaptured(QString)), this, SLOT(gotoReviewMode()));
	connect(reviewView, SIGNAL(imageAccepted()), this, SLOT(acceptPhoto()));
	connect(reviewView, SIGNAL(imageRejected()), this, SLOT(askForAnotherPicture()));
	connect(cameraView, SIGNAL(countDownFinished()), camera, SLOT(captureImage()));

	// Setup call to action
	setupCallToAction();
	callToActionWidget->hide();

	// Set fullscreen shortcut
	QShortcut* setupShortcut = new QShortcut(QKeySequence(tr("Ctrl+,")), this);
	setupShortcut->setContext(Qt::ApplicationShortcut);
	connect(setupShortcut, SIGNAL(activated()), this, SLOT(openSetupDialog()));

	// Set fullscreen shortcut
	QShortcut* toggleFullscreenShortcut = new QShortcut(QKeySequence(tr("Ctrl+F")), this);
	toggleFullscreenShortcut->setContext(Qt::ApplicationShortcut);
	connect(toggleFullscreenShortcut, SIGNAL(activated()), this, SLOT(toggleFullscreen()));

	// Set quit shortcut
	QShortcut* quitShortcut = new QShortcut(QKeySequence(tr("Ctrl+Shift+Q")), this);
	quitShortcut->setContext(Qt::ApplicationShortcut);
	connect(quitShortcut, SIGNAL(activated()), QApplication::instance(), SLOT(quit()));

	// Start idle
	gotoIdleMode();

}

MainWindow::~MainWindow() {}

void MainWindow::gotoIdleMode() {
	showView(imageCarousel);
	callToActionWidget->show();
}

void MainWindow::gotoPictureMode() {
	callToActionWidget->hide();
	showView(cameraView);
	cameraView->startCountDown();
}

void MainWindow::gotoReviewMode() {
	reviewView->setImage(camera->getLastCapturedFilename());
	showView(reviewView);
}

void MainWindow::acceptPhoto() {

	QFile file(camera->getLastCapturedFilename());

	if (file.exists()) {

		bool imageIsGood = true;
		if (imageIsGood) {

			// Rename file
			file.rename(QString("%1/%2.jpg").arg(QSettings().value(SETTINGS_IMAGE_PATH).toString(),
				QFileInfo(file.fileName()).fileName()));

		} else {

			// Delete file
			file.remove();
		}

	}

	askForAnotherPicture();
}

void MainWindow::askForAnotherPicture() {

	QMessageBox msgBox;
	msgBox.setText(tr("Would you like to take another picture?"));
	msgBox.addButton(tr("Yes"), QMessageBox::YesRole);
	msgBox.addButton(tr("No"), QMessageBox::NoRole);
	msgBox.setWindowFlags(Qt::Window | Qt::FramelessWindowHint);

	if (msgBox.exec() == 0) {
		gotoPictureMode();
	} else {
		gotoIdleMode();
	}
}

void MainWindow::showView(QWidget* widget) {
	int index = widgetStack->indexOf(widget);
	if (index != -1) {
		widgetStack->setCurrentIndex(index);
	}
}

void MainWindow::setupCallToAction() {

	// Call to action text
	QString content = "This is the camera booth<br />Take your picture here";

	QLabel* callToActionText = new QLabel(this);
	callToActionText->setTextFormat(Qt::RichText);
	callToActionText->setAlignment(Qt::AlignCenter);
	callToActionText->setText(content);

	// Button
	QPushButton* takePictureBtn = new QPushButton(tr("Take photo"), this);
	connect(takePictureBtn, SIGNAL(clicked()), this, SLOT(gotoPictureMode()));

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
	callToActionWidget->setObjectName("callToAction");
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

void MainWindow::applyStyleSheet() {

	if (QSettings().value(SETTINGS_QSS_PATH, 0).isNull()) {
		return;
	}

	QFile File(QSettings().value(SETTINGS_QSS_PATH).toString());
	File.open(QFile::ReadOnly);
	QString StyleSheet = QLatin1String(File.readAll());
	qApp->setStyleSheet(StyleSheet);
}

void MainWindow::resizeEvent(QResizeEvent*) {
	callToActionWidget->move((width() - callToActionWidget->width()) / 2,
							 (height() - callToActionWidget->height()) / 2);
}


