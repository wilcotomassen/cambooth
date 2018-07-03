#ifndef CAMERAVIEW_H
#define CAMERAVIEW_H

#include <QCameraViewfinder>

class QTimer;

class CameraView : public QCameraViewfinder {
	Q_OBJECT

public:
	CameraView(QWidget* parent = nullptr);

signals:
	void countDownFinished();

public slots:
	void startCountDown();

private slots:
	void updateCountdown();
	void updateFlash();

private:
	void paintEvent(QPaintEvent*event);

	QTimer*		countdownTimer;
	int			countdownState;

	QTimer*		flashTimer;
	float		flashState;

};

#endif // CAMERAVIEW_H
