#include "studenteditdelete.h"
#include "ui_studenteditdelete.h"
#include "srecord.h"

studenteditdelete::studenteditdelete(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::studenteditdelete)
{
    ui->setupUi(this);
    initializeComboBoxes();
    connectToDatabase();

    SRecord conn;
    conn.connOpen();

}

studenteditdelete::~studenteditdelete()
{
    delete ui;
}
void studenteditdelete::initializeComboBoxes()
{
    ui->txtcmbxstge2ed->addItems({"", "الاولى", "الثانية"});
    ui->txtGender2ed->addItems({"", "M", "F"});
    ui->txtpara2ed->addItems({"", "تعليم موازي"});
    ui->txtenrollment2ed->addItems({"", "باشر"});
    ui->txtcmbxcontinuity2ed->addItems({"", "مستمر"});
    ui->txtcmbxgraduation2ed->addItems({"", "الدور الأول", "الدور الثاني"});
    ui->txtcmbxentership2ed->addItems({"", "مستوفي", "غير مستوفي"});
    ui->txcmbxtReturn2ed->addItem("");
    ui->txcmbxtReturn2ed->addItem("مرقن عائد");

}

void studenteditdelete::connectToDatabase()
{
    QSqlQuery query;
    if (query.exec("SELECT states FROM states")) {
        while (query.next()) {
            QString value = query.value(0).toString();
            ui->txtcmbBxstates2ed->addItem(value);
        }
    }

    QSqlQuery qry; QString mytbl = getTableName();
    qry.prepare("select distinct bloodtype from "+mytbl+" order by bloodtype ASC");
    while (qry.next()) {
        QString name = query.value(0).toString();
        ui->txtcmbxbloodtype2ed->addItem(name);
    }
}
/************************************************************************/
void studenteditdelete::on_btneditstudent_clicked()
{
    QString txtemail, txtpass, txty2enrol, txtentership,txtaddress, txtFullnames,
        txtsno, txtrefadded, txtrefrendom1, txtsatifiedsubj, txtnotes,
        txtpara, txtenrollment, txtenroldate, txtSIDNo, txtIDdate, txtcmback;

    QString txtname=ui->txtname2ed->text();
    QString txtsname=ui->txtsname2ed->text();
    QString txtEnname=ui->txtEnname2ed->text();
    QString txtGender=ui->txtGender2ed->currentText();
    QString txtdob=ui->txtdob2ed->text();
    QString txtmothername=ui->txtmothername2ed->text();
    QString txtbloodtype=ui->txtcmbxbloodtype2ed->currentText();
    QString txtidno=ui->txtidno2ed->text();

    QString txtphone=ui->txtphone2ed->text();
    QString txtparantsphone=ui->txtparantsphone2ed->text();
    QString txtenrolyear=ui->txtenrolyear2ed->text();
    QString txtprepschool=ui->txtprepschool2ed->text();
    QString txtStage=ui->txtcmbxstge2ed->currentText();//Combobox
    QString txtgraduation=ui->txtcmbxgraduation2ed->currentText();
    QString txtgraduationyear=ui->txtgraduationyear2ed->text();
    QString txtcontinuity=ui->txtcmbxcontinuity2ed->currentText();
    QString txtstate=ui->txtcmbBxstates2ed->currentText();//حالة الطالب مستمر تخرج راسب ...
    txtemail=ui->txtemail2ed->text();//الايميل
    txtpass=ui->txtpass2ed->text();  //كلمة المرور
    txty2enrol=ui->txty2enrol2ed->text();
    txtentership=ui->txtcmbxentership2ed->currentText();
    txtaddress=ui->txtaddress2ed->text();
    txtFullnames=ui->txtFullnames2ed->text();
    txtsno=ui->txtsno2ed->text();
    txtrefadded=ui->txtrefadded2ed->text();
    txtrefrendom1=ui->txtrefrendom12ed->text();
    txtsatifiedsubj=ui->txtsatifiedsubj2ed->text();
    txtnotes=ui->txtnotes2ed->text();
    txtpara=ui->txtpara2ed->currentText();//التعليم الموازي
    txtenrollment=ui->txtenrollment2ed->currentText();//هل الطالب مباشر
        /*****************************************************/
        //QDateEdit *dateEdite = new QDateEdit(this);// Create a QDateEdit widget
    txtenroldate=ui->txtenroldate2ed->date().toString("yyyy-MM-dd");
    ui->txtenroldate2ed->setDisplayFormat("dd/MM/yyyy");// set the display format of the date edit widget
    QString sdt = ui->txtenroldate2ed->text();
    txtenroldate = QDate::fromString(sdt, "dd/MM/yyyy").toString("yyyy-MM-dd");
    //txtenroldate=ui->txtenroldate->text();
    /******************************************/
    txtSIDNo =ui->txtSIDNo2ed->text();//رقم هوية الطالب
    txtIDdate=ui->txtIDdate2ed->text();//تاريخ اصدار هوية الطالب
    txtcmback=ui->txcmbxtReturn2ed->currentText();//رقم هوية الطالب

    QSqlQuery qry; QString mytbl = getTableName();
    qry.prepare("UPDATE "+mytbl+" SET Names='"+txtname+"', Surname='"+txtsname+"',"
                " Enname='"+txtEnname+"', Gender='"+txtGender+"', dob='"+txtdob+"',"
                " mothername='"+txtmothername+"', bloodtype='"+txtbloodtype+"', idno='"+txtidno+"',"
                " phone='"+txtphone+"', parantsphone='"+txtparantsphone+"',"
                " enrolyear='"+txtenrolyear+"', prepschool='"+txtprepschool+"', Stage='"+txtStage+"',"
                " graduation='"+txtgraduation+"', graduationyear='"+txtgraduationyear+"',"
                " continuity='"+txtcontinuity+"', state='"+txtstate+"', email='"+txtemail+"',"
                " pass='"+txtpass+"', y2enrol='"+txty2enrol+"', entership='"+txtentership+"',"
                " address='"+txtaddress+"', Fullnames='"+txtFullnames+"', sno='"+txtsno+"',"
                " refadded='"+txtrefadded+"', refrendom1='"+txtrefrendom1+"',"
                " satifiedsubj='"+txtsatifiedsubj+"', notes='"+txtnotes+"', para='"+txtpara+"',"
                " enrollment='"+txtenrollment+"', enroldate='"+txtenroldate+"',"
                " SIDNo='"+txtSIDNo+"', IDdate='"+txtIDdate+"', cmback='"+txtcmback+"'"
                " where Names='"+txtname+"';");
    if(qry.exec())
    {
        ui->lblresult->setText("<font color='green'>تم تعديل الطالب بنجاح</font>");
    }
    else
    {
        ui->lblresult->setText("<font color=#F00>هناك مشكلة لم يتم اضافة الطلاب</font>");
    }
}
/*******************************************************/

void studenteditdelete::on_txtsearchname_textChanged(const QString &)
{
    QString ssbyname = ui->txtsearchname->text();

    QSqlQuery qry;
    //QSqlQueryModel *modal =static_cast<QSqlQueryModel*>
    //    (ui->tblviewshowstudents->model());
    QString mytbl = getTableName();
    //modal->setQuery("SELECT * FROM "+mytbl+" WHERE Names LIKE '%"+ ssbyname +"%'");
    qry.prepare("");
    //ui->tblviewshowstudents->model();
    qry.exec("SELECT * FROM "+mytbl+" WHERE Names LIKE '%"+ ssbyname +"%'");
    if(qry.exec())
    {
        while (qry.next())
        {
            ui->txtname2ed->  setText(qry.value(1).toString());
            ui->txtsname2ed-> setText(qry.value(2).toString());
            ui->txtEnname2ed->setText(qry.value(3).toString());
            ui->txtGender2ed->setCurrentText(qry.value(4).toString());//combobox
            ui->txtdob2ed->setDate(qry.value(5).toDate());//qdateEdit
            ui->txtmothername2ed->setText(qry.value(6).toString());
            ui->txtcmbxbloodtype2ed->setCurrentText(qry.value(7).toString());//combobox
            ui->txtidno2ed->setText(qry.value(8).toString());
            ui->txtphone2ed->setText(qry.value(9).toString());
            ui->txtparantsphone2ed->setText(qry.value(10).toString());
            ui->txtenrolyear2ed->setText(qry.value(11).toString());
            ui->txtprepschool2ed->setText(qry.value(12).toString());
            ui->txtcmbxstge2ed->setCurrentText(qry.value(13).toString());//combobox
            ui->txtcmbxgraduation2ed->setCurrentText(qry.value(14).toString());//combobox
            ui->txtgraduationyear2ed->setText(qry.value(15).toString());
            ui->txtcmbxcontinuity2ed->setCurrentText(qry.value(16).toString());//combobox
            ui->txtcmbBxstates2ed->setCurrentText(qry.value(17).toString());//combobox
            ui->txtemail2ed->setText(qry.value(18).toString());
            ui->txtpass2ed->setText(qry.value(19).toString());
            ui->txty2enrol2ed->setText(qry.value(20).toString());
            ui->txtcmbxentership2ed->setCurrentText(qry.value(21).toString());//combobox
            ui->txtaddress2ed->setText(qry.value(22).toString());
            ui->txtFullnames2ed->setText(qry.value(23).toString());
            ui->txtsno2ed->setText(qry.value(24).toString());
            ui->txtrefadded2ed->setText(qry.value(25).toString());
            ui->txtrefrendom12ed->setText(qry.value(26).toString());
            ui->txtsatifiedsubj2ed->setText(qry.value(27).toString());
            ui->txtnotes2ed->setText(qry.value(28).toString());
            ui->txtpara2ed->setCurrentText(qry.value(29).toString());//combobox
            ui->txtenrollment2ed->setCurrentText(qry.value(30).toString());//combobox
            ui->txtenroldate2ed->setDate(qry.value(31).toDate());//QdateEdit
            ui->txtSIDNo2ed->setText(qry.value(32).toString());
            ui->txtIDdate2ed->setDate(qry.value(33).toDate());
            ui->txcmbxtReturn2ed->setCurrentText(qry.value(34).toString());//combobox

        }
    }
    else
    {
        ui->lblresult->setText("لم يتم تعديل الاسم");
    }
}

