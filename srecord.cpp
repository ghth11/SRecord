
#include "srecord.h"
#include "studenteditdelete.h"
#include "ui_srecord.h"
#include"addstudent.h"
#include"stdrecordshow.h"



SRecord::SRecord(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SRecord)
{
    ui->setupUi(this);

}

SRecord::~SRecord()
{
    delete ui;
}

void SRecord::on_btnaddstudent_clicked()
{
    //this->hide();
    addstudent addnewstudent;
    addnewstudent.setModal(true);
    addnewstudent.exec();
}

void SRecord::on_btnsrecordclose_clicked()
{
    this->close();
}


void SRecord::on_btnstdrecordshow_clicked()
{
    //this->hide();
    showstudents ashow;
    ashow.setModal(true);
    ashow.exec();
}


void SRecord::on_btnstudenteditdelete_clicked()
{
    //this->hide();
    studenteditdelete ashow;
    ashow.setModal(true);
    ashow.exec();
}

QString getTableName() {
    // Assuming you have a predefined table name
    QString mytbl = "sinfo3";

    return mytbl;
}
