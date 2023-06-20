#ifndef STADIUM_REPORTS_H
#define STADIUM_REPORTS_H

#include <QDialog>
#include <QString>
#include <QFile>
#include <QIcon>
#include <QTextStream>
#include <algorithm>
#include "stadium.h"

namespace Ui {
class Stadium_Reports;
}

/*********************************************************************
 * Stadium_Reports Class
 *   Represents the dialog window responsible for displaying
 *   customized baseball stadium reports.
 *********************************************************************/
class Stadium_Reports : public QDialog
{
    Q_OBJECT

public:
    explicit Stadium_Reports(std::vector<Stadium> stads, QWidget *parent = nullptr);
    ~Stadium_Reports();

private slots:
    void on_teamSortButton_clicked();

    void on_stadiumNameSortButton_clicked();

    void on_dateSortButton_clicked();

    void on_ALOnlyCheckBox_stateChanged(int arg1);

    void on_NLOnlyCheckBox_stateChanged(int arg1);

    void on_grassOnlyCheckBox_stateChanged(int arg1);

    void on_artificalFieldCheckBox_stateChanged(int arg1);

private:
    Ui::Stadium_Reports *ui;
    std::vector<Stadium> stadiums;  // list of all baseball stadiums
};

#endif // STADIUM_REPORTS_H
