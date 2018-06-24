#ifndef IMAGECAROUSEL_H
#define IMAGECAROUSEL_H

#include <QWidget>

class ImageCarousel : public QWidget {
	Q_OBJECT

public:
	explicit ImageCarousel(QWidget *parent = nullptr);

private slots:
	void handleContentChange(const QString& changedPath);
	void swapImages();

private:
	void paintEvent(QPaintEvent*);
	void reloadImages();

	bool			filesChanged;			//!< Flag that indicates that directory contents have changed
	QList<QImage>	images;					//!< All available images
	int				currentImageIndex;		//!< Current drawn image from images

};

#endif // IMAGECAROUSEL_H
