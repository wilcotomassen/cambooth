#include "cameraview.h"

#include "camera.h"

#include <QTimer>
#include <QLabel>
#include <QHBoxLayout>
#include <QCameraViewfinder>
#include <QPainter>
#include <QDebug>

CameraView::CameraView(QWidget* parent) : QCameraViewfinder(parent) {

	QPalette pal = palette();
	pal.setColor(QPalette::Background, Qt::black);
	setAutoFillBackground(true);
	setPalette(pal);

	// Setup countdown timer
	countdownTimer = new QTimer(this);
	countdownTimer->setInterval(1000);
	connect(countdownTimer, SIGNAL(timeout()), this, SLOT(updateCountdown()));

}

void CameraView::startCountDown() {
	countdownState = 0;
	countdownTimer->start();
}

void CameraView::updateCountdown() {

	if (countdownState > 0) {

		// Update state and restart timer
		countdownState--;
		update();

	} else {

		// Stop the countdown timer
		countdownTimer->stop();
		emit countDownFinished();

	}

}

void CameraView::paintEvent(QPaintEvent* event) {

	QCameraViewfinder::paintEvent(event);
	QPainter painter(this);

	painter.setPen(Qt::white);
	QFont font;
	font.setPixelSize(48);
	font.setBold(true);
	painter.setFont(font);
	painter.drawText(geometry(), Qt::AlignCenter, QString::number(countdownState));

}
