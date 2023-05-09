#include "stdrecordshow.h"
#include "ui_stdrecordshow.h"
#include "srecord.h"
#include "QSqlQueryModel"
#include <QtWidgets>

showstudents::showstudents(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::showstudents)
{
    ui->setupUi(this);

    // Open database connection
    SRecord conn;
    conn.connOpen();

    // Create model for all students
    QSqlQueryModel *modal = new QSqlQueryModel(this);
    QString mytbl = getTableName();
    modal->setQuery("SELECT * FROM "+mytbl+"");
    ui->tblviewshowstudents->setModel(modal);

    //create lable count record
    QAbstractItemModel *model =ui->tblviewshowstudents->model(); // Get the model
    int rowCount = model->rowCount(); // Get the number of rows in the model
    ui->rowCountLabel->setText(QString("عدد الطلاب: %1").arg(rowCount)); // Set the text of the label to display the row count

    // Create model for stage filter
    QSqlQueryModel *cmbxstg = new QSqlQueryModel(this);
    cmbxstg->setQuery("SELECT stage FROM stages ORDER BY Stage ASC");
    ui->cmbxstage->setModel(cmbxstg);

    // Create model for gender filter
    QSqlQueryModel *cmbcgender = new QSqlQueryModel(this);
    cmbcgender->setQuery("SELECT DISTINCT Gender FROM "+mytbl+" ORDER BY Gender ASC");
    ui->cmbxgender->setModel(cmbcgender);

    // Create model for state filter
    QSqlQueryModel *cmbxcont = new QSqlQueryModel(this);
    cmbxcont->setQuery("SELECT DISTINCT states FROM states ORDER BY states ASC", conn.sinfo);
    ui->cmbxstate->setModel(cmbxcont);
/****************************************************/
    // Connect the currentIndexChanged signal of each combobox to the filterTable slot
    connect(ui->cmbxcontinuity, SIGNAL(currentIndexChanged(int)), this, SLOT(filterTable()));
    connect(ui->cmbxgender, SIGNAL(currentIndexChanged(int)), this, SLOT(filterTable()));
    connect(ui->cmbxstage, SIGNAL(currentIndexChanged(int)), this, SLOT(filterTable()));
    connect(ui->cmbxstate, SIGNAL(currentIndexChanged(int)), this, SLOT(filterTable()));
/*************************************************/
    // Close database connection
}

showstudents::~showstudents()
{
    delete ui;
}

void showstudents::on_cmbxgender_activated(int index)
{
    QString gender =ui->cmbxgender->currentText();
    /*QString stages =ui->cmbxstage->currentText();
    QString state =ui->cmbxstate->currentText();*/

    QSqlQueryModel *modal =static_cast<QSqlQueryModel*>
        (ui->tblviewshowstudents->model());
    QString mytbl = getTableName();
    modal->setQuery("SELECT * FROM "+mytbl+" WHERE (Gender= '" + gender + "');");
    //create lable count record
    QAbstractItemModel *model =ui->tblviewshowstudents->model(); // Get the model
    int rowCount = model->rowCount(); // Get the number of rows in the model
    ui->rowCountLabel->setText(QString("عدد الطلاب: %1").arg(rowCount)); // Set the text of the label to display the row count

}

void showstudents::on_cmbxstage_activated(int)
{
    /*QString gender =ui->cmbxgender->currentText();
    QString state =ui->cmbxstate->currentText();*/
    QString stages =ui->cmbxstage->currentText();
    QString mytbl = getTableName();
    QSqlQueryModel *modal =static_cast<QSqlQueryModel*>
        (ui->tblviewshowstudents->model());
    modal->setQuery("SELECT * FROM "+mytbl+" WHERE (Stage= '" + stages + "');");
    //create lable count record
    QAbstractItemModel *model =ui->tblviewshowstudents->model(); // Get the model
    int rowCount = model->rowCount(); // Get the number of rows in the model
    ui->rowCountLabel->setText(QString("عدد الطلاب: %1").arg(rowCount)); // Set the text of the label to display the row count

}


void showstudents::on_cmbxstate_activated(int)
{
    /*QString gender =ui->cmbxgender->currentText();
    QString stages =ui->cmbxstage->currentText();*/
    QString state =ui->cmbxstate->currentText();
    QString mytbl = getTableName();
    QSqlQueryModel *modal =static_cast<QSqlQueryModel*>
        (ui->tblviewshowstudents->model());
    modal->setQuery("SELECT * FROM "+mytbl+" WHERE (state= '" + state + "');");
    //create lable count record
    QAbstractItemModel *model =ui->tblviewshowstudents->model(); // Get the model
    int rowCount = model->rowCount(); // Get the number of rows in the model
    ui->rowCountLabel->setText(QString("عدد الطلاب: %1").arg(rowCount)); // Set the text of the label to display the row count


}

void showstudents::on_txtsearchstudentbyname_textChanged(const QString &)
{
        QString ssbyname = ui->txtsearchstudentbyname->text();

        QSqlQuery qry;
        QSqlQueryModel *modal =static_cast<QSqlQueryModel*>
            (ui->tblviewshowstudents->model());
        QString mytbl = getTableName();
        modal->setQuery("SELECT * FROM "+mytbl+" WHERE Names LIKE '%"+ ssbyname +"%'");
        ui->tblviewshowstudents->model();
        qry.exec();

        while (qry.next()) {
            ui->tblviewshowstudents->model();
        }
        //create lable count record
        QAbstractItemModel *model =ui->tblviewshowstudents->model(); // Get the model
        int rowCount = model->rowCount(); // Get the number of rows in the model
        ui->rowCountLabel->setText(QString("عدد الطلاب: %1").arg(rowCount)); // Set the text of the label to display the row count

}

void showstudents::on_cmbxcontinuity_activated(int)
{
        /*QString gender =ui->cmbxgender->currentText();
        QString stages =ui->cmbxstage->currentText();
        QString state =ui->cmbxstate->currentText();*/
        QString contin =ui->cmbxcontinuity->currentText();
        QString mytbl = getTableName();
        QSqlQueryModel *modal =static_cast<QSqlQueryModel*>
            (ui->tblviewshowstudents->model());
        modal->setQuery("SELECT * FROM "+mytbl+" WHERE (continuity= '" + contin + "');");    //create lable count record
        QAbstractItemModel *model =ui->tblviewshowstudents->model(); // Get the model
        int rowCount = model->rowCount(); // Get the number of rows in the model
        ui->rowCountLabel->setText(QString("عدد الطلاب: %1").arg(rowCount)); // Set the text of the label to display the row count



}
// Define the filterTable slot
void showstudents::filterTable()
{
        // Define a QStringList to hold the column values for filtering
        QStringList filters;

        // Clear the filters list
        filters.clear();

        // Check each combobox for a selected value and add it to the filters list
        if (ui->cmbxcontinuity->currentIndex() > 0) {
            filters << "continuity = '" + ui->cmbxcontinuity->currentText() + "'";
        }
        if (ui->cmbxgender->currentIndex() > 0) {
            filters << "Gender = '" + ui->cmbxgender->currentText() + "'";
        }
        if (ui->cmbxstage->currentIndex() > 0) {
            filters << "Stage = '" + ui->cmbxstage->currentText() + "'";
        }
        if (ui->cmbxstate->currentIndex() > 0) {
            filters << "state = '" + ui->cmbxstate->currentText() + "'";
        }
        // Combine the filters using 'AND' operator and create the filter string
        QString filter = filters.join(" AND ");

        QString originalModel;
        // Create a QSortFilterProxyModel and set the filter
        QSortFilterProxyModel *proxyModel = new QSortFilterProxyModel(this);
       /* proxyModel->setSourceModel(originalModel);
        proxyModel->setFilterRegExp(QRegExp(filter, Qt::CaseInsensitive));
        ui->tblviewshowstudents->setModel(proxyModel);

        proxyModel->setSourceModel(model);
        proxyModel->setFilterFixedString(filterString);
        ui->tblviewshowstudents->setModel(proxyModel);*/
}

