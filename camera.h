#ifndef CAMERA_H
#define CAMERA_H

#include <QObject>
#include <QVideoFrame>
#include <QCameraImageCapture>

class QCamera;
class QVideoWidget;

class Camera : public QObject {
	Q_OBJECT

public:
	explicit Camera(QObject *parent = nullptr);

	void setViewfinder(QVideoWidget* viewfinder);

	QString getLastCapturedFilename() const;

signals:
	void imageCaptured(const QString& filename);

public slots:
	void captureImage();

private slots:
	void handleCapturedImage(int, const QString& filename);
	void handleCaptureError(int, QCameraImageCapture::Error, const QString& errorString);

private:
	QCamera*				camera;
	QCameraImageCapture*	capture;
	QString					lastCapturedFilename;

};

#endif // CAMERA_H
