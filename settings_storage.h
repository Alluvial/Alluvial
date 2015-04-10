#ifndef SETTINGS_STORAGE
#define SETTINGS_STORAGE

#include <QObject>
#include <QSettings>
#include <iostream>
#include <fstream>
#include <QFile>
#include <QCoreApplication>

///
/// \class Settings_storing
///
/// \preliminary
/// \brief The Settings_storing class
///
/// This class is a wrapper around the QSettings class, develooped by Qt
/// This particular class will perform ________
///
class Settings_storing:public QSettings{
    Q_OBJECT
    public:
        explicit Settings_storing(QObject*parent=0): QSettings(QSettings::NativeFormat, QSettings::UserScope,
                                                       QCoreApplication::instance()->organizationName(),
                                                       QCoreApplication::instance()->applicationName(),
                                                       parent){}
    //Q_INVOAKBLE Macro which will expose this setValue function to qml elements
    //This is used to set the value for the specified key
        Q_INVOKABLE inline void setValue(const QString & key, const QVariant & value){
            QSettings::setValue(key, value);
        }
    //Q_INVOAKBLE Macro which will expose this value function to qml elements
    //This is used to return the value of the specified key
        Q_INVOKABLE inline QVariant value(const QString &key, const QVariant & defaultValue = QVariant()) const {
            return QSettings::value(key, defaultValue);
        }
        Q_INVOKABLE inline bool contains(const QString &key) const{
            return QSettings::contains(key);
        }
        Q_INVOKABLE inline void sync(){
            QSettings::sync();
        }

    signals:
    public slots:
    private:
        QSettings client_settings;
};

Q_DECLARE_METATYPE(Settings_storing*)

#endif // SETTINGS_STORAGE
