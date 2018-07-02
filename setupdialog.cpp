#include "setupdialog.h"

#include "setting_names.h"
#include <QGridLayout>
#include <QSettings>
#include <QDir>
#include <QFileDialog>
#include <QCameraInfo>
#include <QDebug>

SetupDialog::SetupDialog(QWidget* parent) : QDialog(parent) {

	setMinimumSize(320, 160);
	setWindowTitle(tr("Settings"));
	setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
	setModal(true);

	QSettings settings;
	QGridLayout* gridLayout = new QGridLayout();

	// Camera combobox
	gridLayout->addWidget(new QLabel(tr("Camera")), 0, 0);
	int currentGridRow = 0;

	cameraComboBox = new QComboBox();
	QList<QCameraInfo> cameras = QCameraInfo::availableCameras();
	foreach (const QCameraInfo &cameraInfo, cameras) {
		cameraComboBox->addItem(cameraInfo.description(), cameraInfo.deviceName());
	}

	cameraComboBox->addItem("No camera", "");

	int selectedIndex = cameraComboBox->findData(settings.value(SETTINGS_CAMERA, ""));
	cameraComboBox->setCurrentIndex(selectedIndex);

	gridLayout->addWidget(cameraComboBox, currentGridRow++, 1, 1, 2);

	// Image path
	gridLayout->addWidget(new QLabel(tr("Image path")), currentGridRow, 0);

	pathLabel = new QLabel(settings.value(SETTINGS_IMAGE_PATH, QDir::homePath()).toString());
	gridLayout->addWidget(pathLabel, currentGridRow, 1);

	QPushButton* pathSelectBtn = new QPushButton(tr("Change"));
	connect(pathSelectBtn, SIGNAL(clicked()), this, SLOT(changeImagePath()));
	gridLayout->addWidget(pathSelectBtn, currentGridRow++, 2);

	// Css path
	gridLayout->addWidget(new QLabel(tr("QSS path")), currentGridRow, 0);

	qssLabel = new QLabel(settings.value(SETTINGS_QSS_PATH, QDir::homePath()).toString());
	gridLayout->addWidget(qssLabel, currentGridRow, 1);

	QPushButton* qsspathSelectBtn = new QPushButton(tr("Change"));
	connect(qsspathSelectBtn, SIGNAL(clicked()), this, SLOT(changeCssPath()));
	gridLayout->addWidget(qsspathSelectBtn, currentGridRow++, 2);

	// Accept button
	QPushButton* acceptButton = new QPushButton(tr("Accept"), this);
	connect(acceptButton, SIGNAL(clicked()), this, SLOT(accept()));
	gridLayout->addWidget(acceptButton, currentGridRow + 1, 0, 1, 3, Qt::AlignCenter);

	// Set layout
	setLayout(gridLayout);

}

void SetupDialog::accept() {

	// Store settings
	QSettings settings;

	settings.setValue(SETTINGS_CAMERA, cameraComboBox->currentData().toString());
	settings.setValue(SETTINGS_IMAGE_PATH, pathLabel->text());
	settings.setValue(SETTINGS_QSS_PATH, qssLabel->text());

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

void SetupDialog::changeCssPath() {
	QSettings settings;

	QString currentPath = settings.value(SETTINGS_QSS_PATH, QDir::homePath()).toString();
	QString newPath = QFileDialog::getOpenFileName(this, tr("Select QSS path"), currentPath, "QSS (*.qss)");
	if (newPath != 0) {
		qssLabel->setText(newPath);
	}
}
