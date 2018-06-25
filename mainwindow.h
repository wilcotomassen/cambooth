#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class ImageCarousel;

class MainWindow : public QMainWindow {
	Q_OBJECT

public:
	MainWindow(QWidget *parent = nullptr);
	~MainWindow();

private slots:
	void toggleFullscreen();
	void openSetupDialog();

private:
	void setupCallToAction();
	void resizeEvent(QResizeEvent *);

	QWidget*		callToActionWidget;
	ImageCarousel*	imageCarousel;


};

#endif // MAINWINDOW_H
