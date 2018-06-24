#include "imagecarousel.h"

#include "setting_names.h"
#include <QSettings>
#include <QFileSystemWatcher>
#include <QPainter>
#include <QDir>
#include <QTimer>
#include <QDebug>

ImageCarousel::ImageCarousel(QWidget *parent) : QWidget(parent) {

	QSettings settings;

	// Trigger image reload
	filesChanged = true;
	swapImages();

	// Attach directory watcher for new/changed content
	QFileSystemWatcher* watcher = new QFileSystemWatcher(this);
	watcher->addPath(settings.value(SETTINGS_IMAGE_PATH).toString());
	QObject::connect(watcher, SIGNAL(directoryChanged(QString)), this, SLOT(handleContentChange(QString)));

	// Swap timer
	QTimer* imageSwapIimer = new QTimer(this);
	connect(imageSwapIimer, SIGNAL(timeout()), this, SLOT(swapImages()));
	imageSwapIimer->start(1000);

}

void ImageCarousel::handleContentChange(const QString& changedPath) {
	Q_UNUSED(changedPath);
	filesChanged = true;
}

void ImageCarousel::reloadImages() {

	// Clear current content
	images.clear();

	// Load all images in image dir
	QSettings settings;
	QDir directory(settings.value(SETTINGS_IMAGE_PATH).toString());
	foreach (QFileInfo info, directory.entryInfoList(QStringList() << "*.jpg", QDir::Files)) {
		QImage loadedImage(info.absoluteFilePath());
		images.append(loadedImage);
	}

	filesChanged = false;

}

void ImageCarousel::swapImages() {

	// Reload images if needed
	if (filesChanged) {

		reloadImages();

		// Start current image at random index
		currentImageIndex = rand() % images.size();

	} else {

		// Update current image
		currentImageIndex = (currentImageIndex == images.size() - 1)
			? 0
			: (currentImageIndex + 1);
	}

}

void ImageCarousel::paintEvent(QPaintEvent*) {

	QPainter painter(this);

	// Black background
	painter.setBrush(Qt::black);
	painter.drawRect(rect());

	// Draw current image
	if (images.size() > currentImageIndex) {

		QImage drawImage = images.at(currentImageIndex).scaled(size(), Qt::KeepAspectRatio);
		int x = (width() - drawImage.width()) / 2;
		int y = (height() - drawImage.height()) / 2;
		painter.drawImage(x, y, drawImage);

	}

	update();
}

