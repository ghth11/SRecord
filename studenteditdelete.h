#ifndef STUDENTEDITDELETE_H
#define STUDENTEDITDELETE_H

#include <QDialog>

namespace Ui {
class studenteditdelete;
}

class studenteditdelete : public QDialog
{
    Q_OBJECT

public:
    explicit studenteditdelete(QWidget *parent = nullptr);
    ~studenteditdelete();

private slots:
    void on_btneditstudent_clicked();

    void on_txtsearchname_textChanged(const QString &arg1);

private:
    void initializeComboBoxes();
    void connectToDatabase();
    Ui::studenteditdelete *ui;
};

#endif // STUDENTEDITDELETE_H
