#include "camera.h"

#include "setting_names.h"
#include <QDir>
#include <QTime>
#include <QCamera>
#include <QCameraImageCapture>
#include <QSettings>
#include <QDebug>

Camera::Camera(QObject *parent) : QObject(parent) {

	// Setup camera
	camera = new QCamera(QSettings().value(SETTINGS_CAMERA).toString().toLatin1(),
		this);
	camera->setCaptureMode(QCamera::CaptureStillImage);
	camera->start();

	// Setup capture
	capture = new QCameraImageCapture(camera, this);
	capture->setCaptureDestination(QCameraImageCapture::CaptureToFile);
	connect(capture, SIGNAL(error(int,QCameraImageCapture::Error,QString)), this, SLOT(handleCaptureError(int,QCameraImageCapture::Error,QString)));
	connect(capture, SIGNAL(imageSaved(int, QString)), this, SLOT(handleCapturedImage(int, QString)));

}

void Camera::setViewfinder(QVideoWidget* viewfinder) {
	camera->setViewfinder(viewfinder);
}

void Camera::captureImage() {

	QString filename = QString("%1/%2.jpg").arg(
				QDir::tempPath(),
				QTime::currentTime().toString("hhmmss"));

	capture->capture(filename);

}

void Camera::handleCapturedImage(int, const QString& filename) {
	lastCapturedFilename = filename;
	emit imageCaptured(filename);
}

void Camera::handleCaptureError(int, QCameraImageCapture::Error, const QString& errorString) {
	qDebug() << "ERROR" << errorString;
}

QString Camera::getLastCapturedFilename() const {
	return lastCapturedFilename;
}
