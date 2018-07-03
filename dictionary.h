#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <QObject>
#include <QHash>

class Dictionary {

public:
	static bool loadFromFile(const QString& filename, QString* error = 0);
	static QString getValue(const QString& key);
	static QString getValue(const QString& key, const QString& defaultValue);

private:
	explicit Dictionary(QHash<QString, QString> values);

	static Dictionary* instance;
	QHash<QString, QString> values;

};

#define TR(k) Dictionary::getValue(k)

#endif // DICTIONARY_H
