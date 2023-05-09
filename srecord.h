
#ifndef SRECORD_H
#define SRECORD_H

#include <QMainWindow>
#include <QTsql>
#include <Qdebug>
#include <QFileInfo>
#include <QSqlDatabase>
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
        sinfo.close();
        sinfo.removeDatabase(QSqlDatabase::defaultConnection);
    }
    bool connOpen()
    {
        sinfo=QSqlDatabase::addDatabase("QSQLITE");
        sinfo.setDatabaseName("C:/Users/ghth1/Documents/qtprojects/SRecord/sinfo.db");
        if(!sinfo.open()){
            qDebug()<<("Not Connected");
            return false;
        }
        else{
            qDebug()<<("Connected");
            return true;
        }
    }


public:
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
