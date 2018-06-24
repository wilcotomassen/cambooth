#ifndef SETUPDIALOG_H
#define SETUPDIALOG_H

#include <QDialog>
#include <QComboBox>
#include <QLabel>
#include <QPushButton>

class SetupDialog : public QDialog {
	Q_OBJECT

public:
	SetupDialog(QWidget* parent = nullptr);

public slots:
	void accept();

private slots:
	void changeImagePath();

private:
	QComboBox*		cameraComboBox;
	QLabel*			pathLabel;
	QPushButton*	pathSelectBtn;

};

#endif // SETUPDIALOG_H
