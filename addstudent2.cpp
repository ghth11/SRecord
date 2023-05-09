#include "addstudent.h"
#include "qsqldatabase.h"
#include "ui_addstudent.h"

#include "srecord.h"

addstudent::addstudent(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addstudent)
{
    ui->setupUi(this);
    ui->txtcmbxstge->addItem("الاولى");
    ui->txtcmbxstge->addItem("الثانية");
    ui->txtGender->addItem("M");
    ui->txtGender->addItem("F");
    SRecord.conn;
 }
   /* SRecord conn;
    QSqlQueryModel * modal =new QSqlQueryModel();
    conn.connOpen();
    QSqlQuery*stg=new QSqlQuery(conn.sinfo);
    stg->prepare("select stage from stages");
    stg->exec();
    modal->setQuery(*stg);
    ui->txtcmbxstge->setModel(modal);*/
addstudent::~addstudent()
{
    delete ui;
}

void addstudent::on_ptn_savenewstudent_clicked()
{
    SRecord conn;

    QString txtname, txtsname, txtEnname, txtGender, txtdob, txtmothername, txtbloodtype,txtidno,
        txtphone, txtparantsphone, txtenrolyear, txtprepschool, txtStage, txtgraduation,
        txtgraduationyear, txtcontinuity, txtstate, txtemail, txtpass, txty2enrol, txtentership,
        txtaddress, txtFullnames, txtsno, txtrefadded, txtrefrendom1, txtsatifiedsubj, txtnotes,
        txtpara, txtenrollment, txtenroldate, txtSIDNo, txtIDdate, txtcmback;

    txtname=ui->txtname->text();
    txtsname=ui->txtsname->text();
    txtEnname=ui->txtEnname->text();
    //txtGender=ui->txtGender->text();
    txtGender=ui->txtGender->currentText();
    txtdob=ui->txtdob->text();
    txtmothername=ui->txtmothername->text();
    txtbloodtype=ui->txtbloodtype->text();
    txtidno=ui->txtidno->text();

    txtphone=ui->txtphone->text();
    txtparantsphone=ui->txtparantsphone->text();
    txtenrolyear=ui->txtenrolyear->text();
    txtprepschool=ui->txtprepschool->text();
    //txtStage=ui->txtStage->text();
    txtStage=ui->txtcmbxstge->currentText();//Combobox
    txtgraduation=ui->txtgraduation->text();
    txtgraduationyear=ui->txtgraduationyear->text();
    txtcontinuity=ui->txtcontinuity->text();

    txtstate=ui->txtstate->text();//حالة الطالب مستمر تخرج راسب ...
    txtemail=ui->txtemail->text();//الايميل
    txtpass=ui->txtpass->text();  //كلمة المرور
    txty2enrol=ui->txty2enrol->text();
    txtentership=ui->txtentership->text();
    txtaddress=ui->txtaddress->text();
    txtFullnames=ui->txtFullnames->text();
    txtsno=ui->txtsno->text();

    txtrefadded=ui->txtrefadded->text();
    txtrefrendom1=ui->txtrefrendom1->text();
    txtsatifiedsubj=ui->txtsatifiedsubj->text();
    txtnotes=ui->txtnotes->text();
    txtpara=ui->txtpara->text();//التعليم الموازي
    txtenrollment=ui->txtenrollment->text();//هل الطالب مباشر
    txtenroldate=ui->txtenroldate->text();
    txtSIDNo=ui->txtSIDNo->text();//رقم هوية الطالب


    txtIDdate=ui->txtIDdate->text();//تاريخ اصدار هوية الطالب
    txtcmback=ui->txtReturn->text();//رقم هوية الطالب

    if(!conn.connOpen())
    {
       // qDebug()<<"Failed to connect to the Database"; return;
    ui->lblfname->setText("Not Connected");
    }
    else
    {
    ui->lblfname->setText("Connected");
    }

    QSqlQuery qry;
    //qry.prepare("insert into sinfo2 (Names, Surname) values('"+txtname+"','"+txtsname+"') ");
    qry.prepare("insert into sinfo2 (Names, Surname, Enname, Gender, dob, mothername,"
                " bloodtype, idno, phone, parantsphone, enrolyear, prepschool, Stage, graduation,"
                " graduationyear, continuity, state, email, pass, y2enrol, entership, address,"
                " Fullnames, sno, refadded, refrendom1, satifiedsubj, notes, para, enrollment,"
                " enroldate, SIDNo, IDdate, cmback) VALUES('"+txtname+"', '"+txtsname+"',"
                " '"+txtEnname+"', '"+txtGender+"', '"+txtdob+"', '"+txtmothername+"',"
                " '"+txtbloodtype+"', '"+txtidno+"',"
                " '"+txtphone+"', '"+txtparantsphone+"', '"+txtenrolyear+"', '"+txtprepschool+"',"
                " '"+txtStage+"', '"+txtgraduation+"', '"+txtgraduationyear+"', '"+txtcontinuity+"',"
                " '"+txtstate+"', '"+txtemail+"', '"+txtpass+"', '"+txty2enrol+"',"
                " '"+txtentership+"', '"+txtaddress+"', '"+txtFullnames+"', '"+txtsno+"',"
                " '"+txtrefadded+"', '"+txtrefrendom1+"', '"+txtsatifiedsubj+"', '"+txtnotes+"',"
                " '"+txtpara+"', '"+txtenrollment+"', '"+txtenroldate+"', '"+txtSIDNo+"',"
                " '"+txtIDdate+"', '"+txtcmback+"')");

    if(qry.exec())
    {
        ui->lblfname->setText("Data saved");
    }
    else
    {
     ui->lblfname->setText("Not Saved");
    }
    conn.connClose();
}
