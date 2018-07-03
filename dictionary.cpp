#include "dictionary.h"

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>

Dictionary* Dictionary::instance = 0;

Dictionary::Dictionary(QHash<QString, QString> values) {
	this->values = values;
}

bool Dictionary::loadFromFile(const QString& filename, QString* error) {

	if (filename.isEmpty()) {
		return false;
	}

	try {

		// Skip if already initialized
		if (instance != 0) {
			throw QString("Dictionary already initialized");
		}

		// Read file contents
		QFile file(filename);
		if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
			throw QString("Failed to open dictionary file");
		}
		QString fileContents = file.readAll();
		file.close();

		// Read json document
		QJsonDocument document = QJsonDocument::fromJson(fileContents.toUtf8());
		if (document.isNull() || !document.isObject()) {
			throw QString("Invalid JSON format");
		}

		// Loop over values (only add direct children)
		QHash<QString, QString> values;
		QJsonObject root = document.object();
		QJsonObject::iterator it;
		for (it = root.begin(); it != root.end(); it++) {
			QJsonValue value = it.value();
			if (value.isString()) {
				values.insert(it.key(), value.toString());
			}

		}

		// Create instance
		instance = new Dictionary(values);

		return true;

	} catch (QString errorStr) {
		if (error != 0) {
			*error = errorStr;
		}
		return false;
	}

}

QString Dictionary::getValue(const QString& key) {
	return getValue(key, key);
}

QString Dictionary::getValue(const QString& key, const QString& defaultValue) {

	if (instance == 0) {
		return defaultValue;
	}

	return instance->values.value(key, defaultValue);

}

