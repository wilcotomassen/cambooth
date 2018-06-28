#ifndef REVIEWVIEW_H
#define REVIEWVIEW_H

#include <QWidget>

class QLabel;
class QPushButton;

class ReviewView : public QWidget {
	Q_OBJECT

public:
	ReviewView(QWidget* parent = nullptr);

signals:
	void imageAccepted();
	void imageRejected();

public slots:
	void setImage(const QString& filename);

private:
	QLabel*			imageContainer;

};

#endif // REVIEWVIEW_H
