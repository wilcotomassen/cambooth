#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class Camera;
class ImageCarousel;
class CameraView;
class ReviewView;
class QStackedWidget;

class MainWindow : public QMainWindow {
	Q_OBJECT

public:
	MainWindow(QWidget *parent = nullptr);
	~MainWindow();

private slots:
	void toggleFullscreen();
	void openSetupDialog();
	void gotoIdleMode();
	void gotoPictureMode();
	void acceptPhoto();
	void gotoReviewMode();
	void askForAnotherPicture();

private:
	void showView(QWidget* widget);
	void setupCallToAction();
	void resizeEvent(QResizeEvent *);

	// Camera
	Camera*			camera;

	// Main views
	QStackedWidget*	widgetStack;
	ImageCarousel*	imageCarousel;
	CameraView*		cameraView;
	ReviewView*		reviewView;

	// Other widgets
	QWidget*		callToActionWidget;

};

#endif // MAINWINDOW_H
