#include "reviewView.h"

#include "dictionary.h"
#include <QImage>
#include <QLabel>
#include <QPushButton>
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <QHBoxLayout>

ReviewView::ReviewView(QWidget *parent) : QWidget(parent) {

	QPalette pal = palette();
	pal.setColor(QPalette::Background, Qt::black);
	setAutoFillBackground(true);
	setPalette(pal);

	// Setup photo
	imageContainer = new QLabel(this);
	QHBoxLayout* photoLayout = new QHBoxLayout();
	photoLayout->setAlignment(Qt::AlignCenter);
	photoLayout->addWidget(imageContainer);

	// Question
	QLabel* questionLabel = new QLabel(TR("Would you like to keep this photo?"), this);
	questionLabel->setAlignment(Qt::AlignCenter);
	questionLabel->setObjectName("reviewQuestion");
	QHBoxLayout* questionLayout = new QHBoxLayout();
	questionLayout->addStretch();
	questionLayout->addWidget(questionLabel);
	questionLayout->addStretch();

	// Buttons
	QPushButton* acceptButton = new QPushButton(TR("Yes"), this);
	connect(acceptButton, SIGNAL(clicked()), this, SIGNAL(imageAccepted()));

	QPushButton* rejectButton = new QPushButton(TR("No"), this);
	connect(rejectButton, SIGNAL(clicked()), this, SIGNAL(imageRejected()));

	QHBoxLayout* buttonLayout = new QHBoxLayout();
	buttonLayout->addStretch();
	buttonLayout->addWidget(acceptButton);
	buttonLayout->addWidget(rejectButton);
	buttonLayout->addStretch();

	// Main layout
	QVBoxLayout* layout = new QVBoxLayout();
	layout->addStretch();
	layout->addLayout(photoLayout);
	layout->addLayout(questionLayout);
	layout->addLayout(buttonLayout);
	layout->addStretch();
	setLayout(layout);

}

void ReviewView::setImage(const QString& filename) {
	QPixmap pixmap;
	if (pixmap.load(filename)) {
		imageContainer->setPixmap(pixmap);
	}
}
