#include "setupdialog.h"

#include "setting_names.h"
#include <QGridLayout>
#include <QSettings>
#include <QDir>
#include <QFileDialog>
#include <QDebug>

SetupDialog::SetupDialog(QWidget* parent) : QDialog(parent, Qt::WindowTitleHint) {

	setMinimumSize(320, 160);
	setWindowTitle(tr("Settings"));
	setModal(true);

	QSettings settings;
	QGridLayout* gridLayout = new QGridLayout();

	// Camera
	gridLayout->addWidget(new QLabel(tr("Camera")), 0, 0);

	cameraComboBox = new QComboBox();
	//@TODO LIST CAMERAS

	gridLayout->addWidget(cameraComboBox, 0, 1, 1, 2);

	// Image path
	gridLayout->addWidget(new QLabel(tr("Image path")), 1, 0);

	pathLabel = new QLabel(settings.value(SETTINGS_IMAGE_PATH, QDir::homePath()).toString());
	gridLayout->addWidget(pathLabel, 1, 1);

	pathSelectBtn = new QPushButton(tr("Change"));
	connect(pathSelectBtn, SIGNAL(clicked()), this, SLOT(changeImagePath()));
	gridLayout->addWidget(pathSelectBtn, 1, 2);

	// Accept button
	QPushButton* acceptButton = new QPushButton(tr("Accept"), this);
	connect(acceptButton, SIGNAL(clicked()), this, SLOT(accept()));
	gridLayout->addWidget(acceptButton, 3, 0, 1, 3, Qt::AlignCenter);

	// Set layout
	setLayout(gridLayout);

}

void SetupDialog::accept() {

	// Store settings
	QSettings settings;

	//@TODO STORE CAMERA
	settings.setValue(SETTINGS_IMAGE_PATH, pathLabel->text());


	QDialog::accept();
}

void SetupDialog::changeImagePath() {
	QSettings settings;
	QString currentPath = settings.value(SETTINGS_IMAGE_PATH, QDir::homePath()).toString();
	QString newPath = QFileDialog::getExistingDirectory(this, tr("Select image path"), currentPath, QFileDialog::ShowDirsOnly);
	if (newPath != 0) {
		pathLabel->setText(newPath);
	}
}
