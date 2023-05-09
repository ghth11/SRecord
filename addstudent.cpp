//#include "qsqldatabase.h"
#include "addstudent.h"
#include "ui_addstudent.h"
#include "srecord.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QFileDialog>
#include <QDate>

addstudent::addstudent(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addstudent),
    statesModel(new QSqlQueryModel(this)),
    bloodTypeModel(new QSqlQueryModel(this))
{
    ui->setupUi(this);
    initializeComboBoxes();
    connectToDatabase();
}

//will be deleted
addstudent::~addstudent()
{
    delete ui;
}
void addstudent::initializeComboBoxes()
{
    ui->txtcmbxstge->addItems({"", "الاولى", "الثانية"});
    ui->txtGender->addItems({"", "M", "F"});
    ui->txtpara->addItems({"", "تعليم موازي"});
    ui->txtenrollment->addItems({"", "باشر"});
    ui->txtcmbxcontinuity->addItems({"", "مستمر"});
    ui->txtcmbxgraduation->addItems({"", "الدور الأول", "الدور الثاني"});
    ui->txtcmbxentership->addItems({"", "مستوفي", "غير مستوفي"});
    ui->txcmbxtReturn->addItem("");
    ui->txcmbxtReturn->addItem("مرقن عائد");
}

void addstudent::connectToDatabase()
{
    SRecord conn;
    conn.connOpen();
    statesModel->setQuery("select states from states", conn.sinfo);
    bloodTypeModel->setQuery("select distinct bloodtype from sinfo order by bloodtype ASC", conn.sinfo);
    ui->txtcmbBxstates->setModel(statesModel);//هذه العملية مقدماتها السطر 42 والسطر 12 وفي السطر 32 في الهيدر اضافةطالب
    ui->txtcmbxbloodtype->setModel(bloodTypeModel);
}
/*
    QSqlQueryModel * modal =new QSqlQueryModel();
    QSqlQuery*stg=new QSqlQuery(conn.sinfo);
    stg->prepare("select states from states");
    stg->exec();
    modal->setQuery(*stg);
    ui->txtcmbBxstates->setModel(modal);

    QSqlQueryModel * bldtype = new QSqlQueryModel();
    QSqlQuery*btype =new QSqlQuery(conn.sinfo);
    btype->prepare("select distinct bloodtype from sinfo order by bloodtype ASC ");btype->exec();
    bldtype->setQuery(*btype);
    ui->txtcmbxbloodtype->setModel(bldtype);
*/

void addstudent::on_ptn_savenewstudent_clicked()
{

    QString txtemail, txtpass, txty2enrol, txtentership,txtaddress, txtFullnames,
        txtsno, txtrefadded, txtrefrendom1, txtsatifiedsubj, txtnotes,
        txtpara, txtenrollment, txtenroldate, txtSIDNo, txtIDdate, txtcmback;

    QString txtname=ui->txtname->text();
    QString txtsname=ui->txtsname->text();
    QString txtEnname=ui->txtEnname->text();
    QString txtGender=ui->txtGender->currentText();
    QString txtdob=ui->txtdob->text();
    QString txtmothername=ui->txtmothername->text();
    QString txtbloodtype=ui->txtcmbxbloodtype->currentText();
    QString txtidno=ui->txtidno->text();

    QString txtphone=ui->txtphone->text();
    QString txtparantsphone=ui->txtparantsphone->text();
    QString txtenrolyear=ui->txtenrolyear->text();
    QString txtprepschool=ui->txtprepschool->text();
    QString txtStage=ui->txtcmbxstge->currentText();//Combobox
    QString txtgraduation=ui->txtcmbxgraduation->currentText();
    QString txtgraduationyear=ui->txtgraduationyear->text();
    QString txtcontinuity=ui->txtcmbxcontinuity->currentText();
    QString txtstate=ui->txtcmbBxstates->currentText();//حالة الطالب مستمر تخرج راسب ...
    txtemail=ui->txtemail->text();//الايميل
    txtpass=ui->txtpass->text();  //كلمة المرور
    txty2enrol=ui->txty2enrol->text();
    txtentership=ui->txtcmbxentership->currentText();
    txtaddress=ui->txtaddress->text();
    txtFullnames=ui->txtFullnames->text();
    txtsno=ui->txtsno->text();
    txtrefadded=ui->txtrefadded->text();
    txtrefrendom1=ui->txtrefrendom1->text();
    txtsatifiedsubj=ui->txtsatifiedsubj->text();
    txtnotes=ui->txtnotes->text();
    txtpara=ui->txtpara->currentText();//التعليم الموازي
    txtenrollment=ui->txtenrollment->currentText();//هل الطالب مباشر
    /*****************************************/
    //QDateEdit *dateEdite = new QDateEdit(this);// Create a QDateEdit widget
    txtenroldate=ui->txtenroldate->date().toString("yyyy-MM-dd");
    ui->txtenroldate->setDisplayFormat("dd/MM/yyyy");// set the display format of the date edit widget
    QString sdt = ui->txtenroldate->text();
    txtenroldate = QDate::fromString(sdt, "dd/MM/yyyy").toString("yyyy-MM-dd");
    //txtenroldate=ui->txtenroldate->text();
    /******************************************/
    txtSIDNo=ui->txtSIDNo->text();//رقم هوية الطالب
    txtIDdate=ui->txtIDdate->text();//تاريخ اصدار هوية الطالب
    txtcmback=ui->txcmbxtReturn->currentText();//رقم هوية الطالب

    QSqlQuery qry; QString mytbl = getTableName();
    qry.prepare("INSERT INTO "+mytbl+" (Names, Surname, Enname, Gender, dob, mothername,"
                " bloodtype, idno, phone, parantsphone, enrolyear, prepschool,"
                " Stage, graduation, graduationyear, continuity, state, email,"
                " pass, y2enrol, entership, address, Fullnames, sno,"
                " refadded, refrendom1, satifiedsubj, notes, para, enrollment,"
                " enroldate, SIDNo, IDdate, cmback)"
                " VALUES("
                " '"+txtname+"', '"+txtsname+"', '"+txtEnname+"', '"+txtGender+"', '"+txtdob+"', '"+txtmothername+"',"
                " '"+txtbloodtype+"', '"+txtidno+"', '"+txtphone+"', '"+txtparantsphone+"', '"+txtenrolyear+"', '"+txtprepschool+"',"
                " '"+txtStage+"', '"+txtgraduation+"', '"+txtgraduationyear+"', '"+txtcontinuity+"', '"+txtstate+"', '"+txtemail+"',"
                " '"+txtpass+"', '"+txty2enrol+"', '"+txtentership+"', '"+txtaddress+"', '"+txtFullnames+"', '"+txtsno+"',"
                " '"+txtrefadded+"', '"+txtrefrendom1+"', '"+txtsatifiedsubj+"', '"+txtnotes+"', '"+txtpara+"', '"+txtenrollment+"',"
                " '"+txtenroldate+"', '"+txtSIDNo+"', '"+txtIDdate+"', '"+txtcmback+"');");
    if(qry.exec())
    {
        ui->lblfname->setText("تم اضافة الطالب بنجاح");
    }
    else
    {
     ui->lblfname->setText("<font color=#00F>هناك مشكلة لم يتم اضافة الطلاب</font>");
    }
}

void addstudent::on_ptnshowhomepage_clicked()
{
    this->hide();
    SRecord w;
    w.show();
}
//C:/Users/ghth1/Desktop/sinfo csv/sinfo
void addstudent::on_btnbrowse_clicked()
{
    //SRecord conn;
    //conn.connOpen();
    QString filePath = QFileDialog::getOpenFileName(this,
               tr("Open CSV File"), QString(), tr("CSV Files (*.csv)"));
    if (filePath.isEmpty()) {
     return;
    }

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
     qDebug() << "Error: Failed to open file.";
     return;
    }

    QTextStream in(&file);
    QStringList fields;
    while (!in.atEnd()) {
     QString line = in.readLine();
     fields = line.split(",");
     QSqlQuery query;QString mytbl = getTableName();
     query.prepare("INSERT INTO "+mytbl+" (Names, Surname, Enname, Gender, dob, mothername,"
                   " bloodtype, idno, phone, parantsphone, enrolyear, prepschool, Stage,"
                   " graduation, graduationyear, continuity, state, email, pass,"
                   " entership, address, Fullnames, sno, refadded, refrendom1, satifiedsubj,"
                   " notes, para, enrollment, enroldate, SIDNo, IDdate, cmback,y2enrol)"
                   " VALUES (:Names, :Surname, :Enname, :Gender, :dob, :mothername,"
                   " :bloodtype, :idno, :phone, :parantsphone, :enrolyear, :prepschool, :Stage,"
                   " :graduation, :graduationyear, :continuity, :state, :email, :pass,"
                   " :entership, :address, :Fullnames, :sno, :refadded, :refrendom1, :satifiedsubj,"
                   " :notes, :para, :enrollment, :enroldate, :SIDNo, :IDdate, :cmback, :y2enrol)");
     query.bindValue(":Names", fields[1]);
     query.bindValue(":Surname", fields[2]);
     query.bindValue(":Enname", fields[3]);
     query.bindValue(":Gender", fields[4]);
     query.bindValue(":dob", fields[5]);
     query.bindValue(":mothername", fields[6]);
     query.bindValue(":bloodtype", fields[7]);
     query.bindValue(":idno", fields[8]);
     query.bindValue(":phone", fields[9]);
     query.bindValue(":parantsphone", fields[10]);
     query.bindValue(":enrolyear", fields[11]);
     query.bindValue(":prepschool", fields[12]);
     query.bindValue(":Stage", fields[13]);
     query.bindValue(":graduation", fields[14]);
     query.bindValue(":graduationyear", fields[15]);
     query.bindValue(":continuity", fields[16]);
     query.bindValue(":state", fields[17]);
     query.bindValue(":email", fields[18]);
     query.bindValue(":pass", fields[19]);
     query.bindValue(":y2enrol", fields[20]);
     query.bindValue(":entership", fields[21]);
     query.bindValue(":address", fields[22]);
     query.bindValue(":Fullnames", fields[23]);
     query.bindValue(":sno", fields[24]);
     query.bindValue(":refadded", fields[25]);
     query.bindValue(":refrendom1", fields[26]);
     query.bindValue(":satifiedsubj", fields[27]);
     query.bindValue(":notes", fields[28]);
     query.bindValue(":para", fields[29]);
     query.bindValue(":enrollment", fields[30]);
     query.bindValue(":enroldate", fields[31]);//enroldate, SIDNo, IDdate, cmback
     query.bindValue(":SIDNo", fields[32]);
     query.bindValue(":IDdate", fields[33]);
     query.bindValue(":cmback", fields[34]);

     if(query.exec())
     {
         ui->lblfname->setText("<font color='green'>تم اضافة الطلاب بنجاح</font>");
     }
     else
     {
         /*************************"<font color='red'>Some text</font>"*********/
         ui->lblfname->setText("<font color='red'>هناك مشكلة لم يتم اضافة الطلاب</font>");
     }
    }
    file.close();
    //conn.connClose();
    }
/*
void addstudent::on_btnbrowse_clicked()
{

    QFile file("C:/Users/ghth1/Desktop/sinfo csv/sinfo3.csv");
    if (!file.open(QIODevice::ReadOnly)) {
     qDebug() << "Error: Failed to open file.";
     return;
    }

    QTextStream in(&file);
    QStringList fields;
    while (!in.atEnd()) {
     QString line = in.readLine();
     fields = line.split(",");//qDebug() << "fields size:" << fields.size();
     QSqlQuery query2;
     query2.prepare("INSERT INTO sinfo4 (Names, Surname, Enname, Gender, dob)"
                    " VALUES (:Names, :Surname, :Enname, :Gender, :dob)");
     //query2.bindValue(":sid", fields[0]);
     query2.bindValue(":Names", fields[1]);
     query2.bindValue(":Surname", fields[2]);
     query2.bindValue(":Enname", fields[3]);
     query2.bindValue(":Gender", fields[4]);
     query2.bindValue(":dob", fields[5]);

     query2.exec();
     if(query2.exec())
     {
         ui->lblfname->setText("تم اضافة الطالاب بنجاح");
     }
     else
     {
         ui->lblfname->setText("Not Saved");
     }
    }
    file.close();

}*/
