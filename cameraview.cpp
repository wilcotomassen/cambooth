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

	flashTimer = new QTimer(this);
	flashTimer->setInterval(20);
	connect(flashTimer, SIGNAL(timeout()), this, SLOT(updateFlash()));

}

void CameraView::startCountDown() {
	countdownState = 3;
	flashState = 0;
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
		emit(countDownFinished());

		// Start flash
		flashState = 1;
		flashTimer->start();

	}

}

void CameraView::updateFlash() {

	flashState *= 0.999f;
	if (flashState < 0.00000001) {
		flashTimer->stop();
	}

	update();

}

void CameraView::paintEvent(QPaintEvent* event) {

	QCameraViewfinder::paintEvent(event);
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing, true);

	painter.setPen(Qt::white);
	QPen pen = painter.pen();
	pen.setWidth(4);
	painter.setPen(pen);

	// Draw lines
	int r = height() / 3;
	painter.drawEllipse(QPoint(width() / 2, height() / 2), r, r);

	int rectHeight = height() * 0.6;
	int rectWidth = rectHeight * 0.25;
	int rectMargin = (height() - rectHeight) / 2;

	// Left bracket
	painter.drawLine(rectMargin, rectMargin, rectMargin, rectMargin + rectHeight);
	painter.drawLine(rectMargin, rectMargin, rectMargin + rectWidth, rectMargin);
	painter.drawLine(rectMargin, rectMargin + rectHeight, rectMargin + rectWidth, rectMargin + rectHeight);

	// Right bracket
	painter.drawLine(width() - rectMargin, rectMargin, width() - rectMargin, rectMargin + rectHeight);
	painter.drawLine(width() - rectMargin, rectMargin, width() - rectMargin * 2, rectMargin);
	painter.drawLine(width() - rectMargin, rectMargin + rectHeight, width() - rectMargin * 2, rectMargin + rectHeight);

	if (countdownState > 0)  {

		// Countdown
		QFont font;
		font.setPixelSize(48);
		font.setBold(true);
		painter.setFont(font);

		painter.drawText(QRect(width() / 2 - r / 2, height() / 2, r, r), Qt::AlignCenter, QString::number(countdownState));

	} else {

		// Flash
		painter.setBrush(QColor(255, 255, 255, (int) (255.0 * flashState)));
		painter.drawRect(rect());

	}

}
