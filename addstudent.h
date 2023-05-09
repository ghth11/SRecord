#ifndef ADDSTUDENT_H
#define ADDSTUDENT_H

#include <qsqlquerymodel>
#include <QDialog>

namespace Ui {
class addstudent;
}

class addstudent : public QDialog
{
    Q_OBJECT

public:
    explicit addstudent(QWidget *parent = nullptr);
    ~addstudent();

private slots:
    void on_ptn_savenewstudent_clicked();

    void on_ptnshowhomepage_clicked();

    void on_btnbrowse_clicked();

private:
    void initializeComboBoxes();
    void connectToDatabase();
    void insertStudentData();

    Ui::addstudent *ui;
    QSqlQueryModel *statesModel;
    QSqlQueryModel *bloodTypeModel;
};

#endif // ADDSTUDENT_H
