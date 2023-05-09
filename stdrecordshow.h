#ifndef STDRECORDSHOW_H
#define STDRECORDSHOW_H

#include <QDialog>

namespace Ui {
class showstudents;
}

class showstudents : public QDialog
{
    Q_OBJECT

public:
    explicit showstudents(QWidget *parent = nullptr);
    ~showstudents();

private slots:
 //   void on_ptnsearchstage_clicked();

    void on_cmbxgender_activated(int index);

    void on_cmbxstage_activated(int index);

    void on_cmbxstate_activated(int index);


    void on_txtsearchstudentbyname_textChanged(const QString &arg1);

    void on_cmbxcontinuity_activated(int);
//    void populateComboBox();
    void filterTable();


private:
    Ui::showstudents *ui;
};

#endif // STDRECORDSHOW_H
