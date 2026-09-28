#ifndef SRECORD_H
#define SRECORD_H

#include <QMainWindow>
#include <QCoreApplication>
#include <QDebug>
#include <QDir>
#include <QFileInfo>
#include <QSqlDatabase>
#include <QSqlError>
#include <QString>

QT_BEGIN_NAMESPACE
namespace Ui { class SRecord; }
QT_END_NAMESPACE

class SRecord : public QMainWindow
{
    Q_OBJECT

public:
    QSqlDatabase sinfo;

    void connClose()
    {
        if (sinfo.isValid()) {
            sinfo.close();
        }
    }

    bool connOpen()
    {
        const QString connectionName = QSqlDatabase::defaultConnection;

        // Reuse the default connection instead of repeatedly replacing it.
        // Existing QSqlQuery objects in the project rely on the default
        // connection, so keeping that connection name preserves compatibility.
        if (QSqlDatabase::contains(connectionName)) {
            sinfo = QSqlDatabase::database(connectionName, false);
        } else {
            sinfo = QSqlDatabase::addDatabase("QSQLITE", connectionName);
        }

        // Prefer a database deployed beside the executable. When running from
        // a development/CI working directory, also allow sinfo.db there.
        QString dbPath =
            QDir(QCoreApplication::applicationDirPath()).filePath("sinfo.db");

        if (!QFileInfo::exists(dbPath)) {
            const QString workingDirDb =
                QDir::current().filePath("sinfo.db");
            if (QFileInfo::exists(workingDirDb)) {
                dbPath = workingDirDb;
            }
        }

        // Do not let SQLite silently create an empty database when the real
        // application database was not deployed.
        if (!QFileInfo::exists(dbPath)) {
            qDebug() << "Database file not found. Checked:"
                     << QDir(QCoreApplication::applicationDirPath()).filePath("sinfo.db")
                     << "and"
                     << QDir::current().filePath("sinfo.db");
            return false;
        }

        if (sinfo.isOpen()) {
            const QString currentPath =
                QFileInfo(sinfo.databaseName()).absoluteFilePath();
            const QString requestedPath =
                QFileInfo(dbPath).absoluteFilePath();

            if (currentPath == requestedPath) {
                return true;
            }

            sinfo.close();
        }

        sinfo.setDatabaseName(dbPath);

        if (!sinfo.open()) {
            qDebug() << "Database connection failed:"
                     << sinfo.lastError().text()
                     << "Path:" << dbPath;
            return false;
        }

        qDebug() << "Database connected:" << dbPath;
        return true;
    }

    SRecord(QWidget *parent = nullptr);
    ~SRecord();

private slots:
    void on_btnaddstudent_clicked();
    void on_btnsrecordclose_clicked();
    void on_btnstdrecordshow_clicked();
    void on_btnstudenteditdelete_clicked();

private:
    Ui::SRecord *ui;
};

QString getTableName();

#endif // SRECORD_H
