#include "stadium_reports.h"
#include "ui_stadium_reports.h"
#include <string.h>
#include <QMessageBox>
using namespace std;

/********************************************************************
 * Stadium Reports Class
 *   This class creates a user interface displaying all the
 *   stadiums that are currently in the program. The user
 *   can sort the stadiums by their names as well as the date
 *   they were opened and the names of the teams that they are
 *   home to. Users also have the ability to select which stadiums
 *   are displayed based on their league of play and the field
 *   surface.
 ********************************************************************/

/********************************************************************
 *
 * Method Stadium_Reports: Class Stadium_Reports
 *___________________________________________________________________
 * This is the constructor that initializes the Stadiums_Reports
 *   by loading a text file with the stadium data. Data is pulled
 *   from this file and placed into QListWidgetItems which are
 *   then inserted into a QListWidget.
 *   –returns nothing
 *___________________________________________________________________
 * PRE-CONDITIONS
 *
 * POST-CONDITIONS
 *   Initializes Stadium_Reports and populates it with a file input.
 ********************************************************************/
Stadium_Reports::Stadium_Reports(vector<Stadium> stads,
                                 QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Stadium_Reports),
    stadiums(stads)
{
    ui->setupUi(this);

    // Temporary variables used to hold data as it is moved/copied.
    QString name, dateOpened, imgName, spacing, teamName, spacing2;
    QListWidgetItem *item;

    for (unsigned i = 0; i < stadiums.size(); i++)
    {
        name = QString::fromStdString(stadiums[i].name);
        dateOpened = QString::fromStdString(stadiums[i].opened);
        teamName = QString::fromStdString(stadiums[i].team);

        // Some image files do not have the correct names. To avoid breaking
        //  any program dependencies handle the irregularities here.
        if (stadiums[i].name == "Miller Park")
            imgName = "American Family Field";
        else if (stadiums[i].name == "US Cellular Field")
            imgName = "Guaranteed Rate Field";
        else if (stadiums[i].name == "Marlins Park")
            imgName = "LoanDepot Park";
        else if (stadiums[i].name == "AT&T Park")
            imgName = "Oracle Park";
        else if (stadiums[i].name == "Oriole Park at Camden Yards")
            imgName = "Camden Yards";
        else if (stadiums[i].name == "SafeCo Field")
            imgName = "T-Mobile Park";
        else if (stadiums[i].name == "Turner Field")
            imgName = "Truist park";
        else
            imgName = name;

        // UI aesthetics.
        if (name.length() <= 15)
            spacing = "\t\t";
        else
            spacing = "\t";
        if (name == "Dodger Stadium" || name == "Yankee Stadium")
            spacing = "\t";
        spacing2 = "\t\t";
        if (name == "RingCentral Coliseum")
            spacing2 = "\t";

        // Add the stadiums name, the date it was opened, and the team name
        //  to the QListWidget.
        item = new QListWidgetItem(QIcon(":/images/Stadium Pics/" + imgName + ".jpg"),
                                   name + spacing + dateOpened + spacing2 + teamName);
        item->setSizeHint(QSize(25, 25));
        ui->listWidget->addItem(item);
    }

}

Stadium_Reports::~Stadium_Reports()
{
    delete ui;
}


/*******************************************************************************
 *
 * Method on_artificalFieldCheckBox_stateChanged: Class Stadium_Reports
 *______________________________________________________________________________
 * This is a checkbox that hides items in the QListWidget that do not have
 *  an artificial turf.
 *   –returns nothing
 *______________________________________________________________________________
 * POST-CONDITIONS
 *   Hides stadiums that don't have artificial turf.
 ******************************************************************************/
void Stadium_Reports::on_artificalFieldCheckBox_stateChanged(int arg1)
{
    if (arg1)
    {
        QString tempQStr;
        string tempStr;

        for (int i = 0; i < ui->listWidget->count(); i++)
        {
            tempQStr = ui->listWidget->item(i)->text();
            tempStr = tempQStr.toStdString();
            tempStr = tempStr.substr(0, 8);

            for (unsigned u = 0; u<stadiums.size(); u++)
            {
                if ((tempStr == stadiums[i].name.substr(0, 8)) &&
                    (stadiums[i].surface == "Grass"))
                {
                    ui->listWidget->item(i)->setHidden(true);
                }
            }
        }
    }
    else
    {
        QString tempQStr;
        string tempStr;

        for (int i = 0; i < ui->listWidget->count(); i++)
        {
            tempQStr = ui->listWidget->item(i)->text();
            tempStr = tempQStr.toStdString();
            tempStr = tempStr.substr(0, 8);

            for (unsigned u = 0; u<stadiums.size(); u++)
            {
                if ((tempStr == stadiums[i].name.substr(0, 8)) &&
                    (stadiums[i].surface == "Grass"))
                {
                    if (ui->listWidget->item(i)->isHidden())
                        ui->listWidget->item(i)->setHidden(false);
                }
            }
        }
        if (ui->ALOnlyCheckBox->isChecked())
            on_ALOnlyCheckBox_stateChanged(1);
        if (ui->NLOnlyCheckBox->isChecked())
            on_NLOnlyCheckBox_stateChanged(1);
        if (ui->grassOnlyCheckBox->isChecked())
            on_grassOnlyCheckBox_stateChanged(1);
    }
}

/*******************************************************************************
 *
 * Method on_grassOnlyCheckBox_stateChanged(int arg1): Class Stadium_Reports
 *______________________________________________________________________________
 * This is a checkbox that hides items in the QListWidget that do not have
 *  a grass field.
 *   –returns nothing
 *______________________________________________________________________________
 * PRE-CONDITIONS
 *
 * POST-CONDITIONS
 *   Hides stadiums that don't have a grass field.
 ******************************************************************************/
void Stadium_Reports::on_grassOnlyCheckBox_stateChanged(int arg1)
{
    if (arg1)
    {
        QString tempQStr;
        string tempStr;

        for (int i = 0; i < ui->listWidget->count(); i++)
        {
            tempQStr = ui->listWidget->item(i)->text();
            tempStr = tempQStr.toStdString();
            tempStr = tempStr.substr(0, 8);

            for (unsigned u = 0; u<stadiums.size(); u++)
            {
                if ((tempStr == stadiums[i].name.substr(0, 8)) &&
                    (stadiums[i].surface == "Artificial turf"))
                {
                    ui->listWidget->item(i)->setHidden(true);
                }
            }
        }
    }
    else
    {
        QString tempQStr;
        string tempStr;

        for (int i = 0; i < ui->listWidget->count(); i++)
        {
            tempQStr = ui->listWidget->item(i)->text();
            tempStr = tempQStr.toStdString();
            tempStr = tempStr.substr(0, 8);

            for (unsigned u = 0; u<stadiums.size(); u++)
            {
                if ((tempStr == stadiums[i].name.substr(0, 8)) &&
                    (stadiums[i].surface == "Artificial turf"))
                {
                    if (ui->listWidget->item(i)->isHidden())
                        ui->listWidget->item(i)->setHidden(false);
                }
            }
        }
        if (ui->ALOnlyCheckBox->isChecked())
            on_ALOnlyCheckBox_stateChanged(1);
        if (ui->NLOnlyCheckBox->isChecked())
            on_NLOnlyCheckBox_stateChanged(1);
        if (ui->artificalFieldCheckBox->isChecked())
            on_artificalFieldCheckBox_stateChanged(1);
    }
}

/*******************************************************************************
 *
 * Method on_NLOnlyCheckBox_stateChanged(int arg1): Class Stadium_Reports
 *______________________________________________________________________________
 * This is a checkbox that hides items in the QListWidget that do not have
 *  teams from the NL.
 *   –returns nothing
 *______________________________________________________________________________
 * PRE-CONDITIONS
 *
 * POST-CONDITIONS
 *   Hides stadiums that don't have NL teams.
 ******************************************************************************/
void Stadium_Reports::on_NLOnlyCheckBox_stateChanged(int arg1)
{
    if (arg1)
    {
        QString tempQStr;
        string tempStr;

        for (int i = 0; i < ui->listWidget->count(); i++)
        {
            tempQStr = ui->listWidget->item(i)->text();
            tempStr = tempQStr.toStdString();
            tempStr = tempStr.substr(0, 8);

            for (unsigned u = 0; u<stadiums.size(); u++)
            {
                if ((tempStr == stadiums[i].name.substr(0, 8)) &&
                    (stadiums[i].league.substr(0,2) == "AL"))
                {
                    ui->listWidget->item(i)->setHidden(true);
                }
            }
        }
    }
    else
    {
        QString tempQStr;
        string tempStr;

        for (int i = 0; i < ui->listWidget->count(); i++)
        {
            tempQStr = ui->listWidget->item(i)->text();
            tempStr = tempQStr.toStdString();
            tempStr = tempStr.substr(0, 8);

            for (unsigned u = 0; u<stadiums.size(); u++)
            {
                if ((tempStr == stadiums[i].name.substr(0, 8)) &&
                    (stadiums[i].league.substr(0,2) == "AL"))
                {
                    if (ui->listWidget->item(i)->isHidden())
                        ui->listWidget->item(i)->setHidden(false);
                }
            }
        }
    }
}

/*******************************************************************************
 *
 * Method on_ALOnlyCheckBox_stateChanged(int arg1): Class Stadium_Reports
 *______________________________________________________________________________
 * This is a checkbox that hides items in the QListWidget that do not have
 *  teams that play in the AL.
 *   –returns nothing
 *______________________________________________________________________________
 * PRE-CONDITIONS
 *
 * POST-CONDITIONS
 *   Hides stadiums that don't have AL teams.
 ******************************************************************************/
void Stadium_Reports::on_ALOnlyCheckBox_stateChanged(int arg1)
{
    if (arg1)
    {
        QString tempQStr;
        string tempStr;

        for (int i = 0; i < ui->listWidget->count(); i++)
        {
            tempQStr = ui->listWidget->item(i)->text();
            tempStr = tempQStr.toStdString();
            tempStr = tempStr.substr(0, 8);

            for (unsigned u = 0; u<stadiums.size(); u++)
            {
                if ((tempStr == stadiums[i].name.substr(0, 8)) &&
                    (stadiums[i].league.substr(0,2) == "NL"))
                {
                    ui->listWidget->item(i)->setHidden(true);
                }
            }
        }
    }
    else
    {
        QString tempQStr;
        string tempStr;

        for (int i = 0; i < ui->listWidget->count(); i++)
        {
            tempQStr = ui->listWidget->item(i)->text();
            tempStr = tempQStr.toStdString();
            tempStr = tempStr.substr(0, 8);

            for (unsigned u = 0; u<stadiums.size(); u++)
            {
                if ((tempStr == stadiums[i].name.substr(0, 8)) &&
                    (stadiums[i].league.substr(0,2) == "NL"))
                {
                    if (ui->listWidget->item(i)->isHidden())
                        ui->listWidget->item(i)->setHidden(false);
                }
            }
        }
    }
}

/*******************************************************************************
 *
 * Method on_dateSortButton_clicked(): Class Stadium_Reports
 *______________________________________________________________________________
 * This button sorts all the stadiums in the QListWidget by to their opening
 *  dates.
 *   –returns nothing
 *______________________________________________________________________________
 * PRE-CONDITIONS
 *
 * POST-CONDITIONS
 *   Sorts stadiums in the QListWidget by date opened.
 ******************************************************************************/
void Stadium_Reports::on_dateSortButton_clicked()
{
    ui->listWidget->clear();

    // sort by day
    stable_sort(stadiums.begin( ), stadiums.end( ),
                [ ](const Stadium& lhs, const Stadium& rhs)
        {
            std::string space = " ";
            return stoi(lhs.opened.substr(lhs.opened.find(space) + 1, 2)) <
                   stoi(rhs.opened.substr(rhs.opened.find(space), 2));
        });

    // sort by month
    stable_sort(stadiums.begin( ), stadiums.end( ),
                [ ](const Stadium& lhs, const Stadium& rhs)
        {
            return lhs.opened.substr(0,3) > rhs.opened.substr(0, 3);
        });

    // sort by year
    stable_sort(stadiums.begin(), stadiums.end(),
                [ ](const Stadium& lhs, const Stadium& rhs)
        {
            return stoi(lhs.opened.substr(lhs.opened.length()-4, lhs.opened.length()-1)) <
                   stoi(rhs.opened.substr(rhs.opened.length()-4, rhs.opened.length()-1));
        });

    QString name, dateOpened, imgName, spacing, teamName, spacing2;
    QListWidgetItem *item;

    for (unsigned i = 0; i < stadiums.size(); i++)
    {
        name = QString::fromStdString(stadiums[i].name);
        dateOpened = QString::fromStdString(stadiums[i].opened);
        teamName = QString::fromStdString(stadiums[i].team);

        // Some image files do not have the correct names. To avoid breaking any program
        // dependencies handle the irregularities here.
        if (stadiums[i].name == "Miller Park")
            imgName = "American Family Field";
        else if (stadiums[i].name == "US Cellular Field")
            imgName = "Guaranteed Rate Field";
        else if (stadiums[i].name == "Marlins Park")
            imgName = "LoanDepot Park";
        else if (stadiums[i].name == "AT&T Park")
            imgName = "Oracle Park";
        else if (stadiums[i].name == "Oriole Park at Camden Yards")
            imgName = "Camden Yards";
        else if (stadiums[i].name == "SafeCo Field")
            imgName = "T-Mobile Park";
        else if (stadiums[i].name == "Turner Field")
            imgName = "Truist park";
        else
            imgName = name;

        // UI aesthetics
        if (name.length() <= 15)
            spacing = "\t\t";
        else
            spacing = "\t";
        if (name == "Dodger Stadium" || name == "Yankee Stadium")
            spacing = "\t";
        spacing2 = "\t\t";
        if (name == "RingCentral Coliseum")
            spacing2 = "\t";

        // Add stadium name, date opened, and team name to QListWidget
        item = new QListWidgetItem(QIcon(":/images/Stadium Pics/" + imgName + ".jpg"),
                                   name + spacing + dateOpened + spacing2 + teamName);
        item->setSizeHint(QSize(25, 25));
        ui->listWidget->addItem(item);
    }
    if (ui->ALOnlyCheckBox->isChecked())
        on_ALOnlyCheckBox_stateChanged(1);
    if (ui->NLOnlyCheckBox->isChecked())
        on_NLOnlyCheckBox_stateChanged(1);
    if (ui->artificalFieldCheckBox->isChecked())
        on_artificalFieldCheckBox_stateChanged(1);
    if (ui->grassOnlyCheckBox->isChecked())
        on_grassOnlyCheckBox_stateChanged(1);
}

/*******************************************************************************
 *
 * Method on_stadiumNameSortButton_clicked(): Class Stadium_Reports
 *______________________________________________________________________________
 * This button sorts all the stadiums in the QListWidget by to their names.
 *   –returns nothing
 *______________________________________________________________________________
 * PRE-CONDITIONS
 *
 * POST-CONDITIONS
 *   Sorts stadiums in the QListWidget by stadium name.
 ******************************************************************************/
void Stadium_Reports::on_stadiumNameSortButton_clicked()
{
    ui->listWidget->clear();
    stable_sort(stadiums.begin(), stadiums.end(),
                [ ](const Stadium& lhs, const Stadium& rhs)
        {
            return lhs.name < rhs.name;
        });

    QString name, dateOpened, imgName, spacing, teamName, spacing2;
    QListWidgetItem *item;

    for (unsigned i = 0; i < stadiums.size(); i++)
    {
        name = QString::fromStdString(stadiums[i].name);
        dateOpened = QString::fromStdString(stadiums[i].opened);
        teamName = QString::fromStdString(stadiums[i].team);

        // Some image files do not have the correct names. To avoid breaking any program
        // dependencies handle the irregularities here.
        if (stadiums[i].name == "Miller Park")
            imgName = "American Family Field";
        else if (stadiums[i].name == "US Cellular Field")
            imgName = "Guaranteed Rate Field";
        else if (stadiums[i].name == "Marlins Park")
            imgName = "LoanDepot Park";
        else if (stadiums[i].name == "AT&T Park")
            imgName = "Oracle Park";
        else if (stadiums[i].name == "Oriole Park at Camden Yards")
            imgName = "Camden Yards";
        else if (stadiums[i].name == "SafeCo Field")
            imgName = "T-Mobile Park";
        else if (stadiums[i].name == "Turner Field")
            imgName = "Truist park";
        else
            imgName = name;

        // UI aesthetics.
        if (name.length() <= 15)
            spacing = "\t\t";
        else
            spacing = "\t";
        if (name == "Dodger Stadium" || name == "Yankee Stadium")
            spacing = "\t";
        spacing2 = "\t\t";
        if (name == "RingCentral Coliseum")
            spacing2 = "\t";

        // Add stadium name, date opened, and team name to QListWidget
        item = new QListWidgetItem(QIcon(":/images/Stadium Pics/" + imgName + ".jpg"),
                                   name + spacing + dateOpened + spacing2 + teamName);
        item->setSizeHint(QSize(25, 25));
        ui->listWidget->addItem(item);
    }
    if (ui->ALOnlyCheckBox->isChecked())
        on_ALOnlyCheckBox_stateChanged(1);
    if (ui->NLOnlyCheckBox->isChecked())
        on_NLOnlyCheckBox_stateChanged(1);
    if (ui->artificalFieldCheckBox->isChecked())
        on_artificalFieldCheckBox_stateChanged(1);
    if (ui->grassOnlyCheckBox->isChecked())
        on_grassOnlyCheckBox_stateChanged(1);
}

/*******************************************************************************
 *
 * Method on_teamSortButton_clicked(): Class Stadium_Reports
 *______________________________________________________________________________
 * This button sorts all the stadiums in the QListWidget by to their team names.
 *   –returns nothing
 *______________________________________________________________________________
 * PRE-CONDITIONS
 *
 * POST-CONDITIONS
 *   Sorts stadiums in the QListWidget by team name.
 ******************************************************************************/
void Stadium_Reports::on_teamSortButton_clicked()
{
    ui->listWidget->clear();
    stable_sort(stadiums.begin(), stadiums.end(),
                [ ](const Stadium& lhs, const Stadium& rhs)
        {
            return lhs.team < rhs.team;
        });

    QString name, dateOpened, imgName, spacing, teamName, spacing2;
    QListWidgetItem *item;

    for (unsigned i = 0; i < stadiums.size(); i++)
    {
        name = QString::fromStdString(stadiums[i].name);
        dateOpened = QString::fromStdString(stadiums[i].opened);
        teamName = QString::fromStdString(stadiums[i].team);

        // Some image files do not have the correct names. To avoid breaking
        //  any program dependencies handle the irregularities here.
        if (stadiums[i].name == "Miller Park")
            imgName = "American Family Field";
        else if (stadiums[i].name == "US Cellular Field")
            imgName = "Guaranteed Rate Field";
        else if (stadiums[i].name == "Marlins Park")
            imgName = "LoanDepot Park";
        else if (stadiums[i].name == "AT&T Park")
            imgName = "Oracle Park";
        else if (stadiums[i].name == "Oriole Park at Camden Yards")
            imgName = "Camden Yards";
        else if (stadiums[i].name == "SafeCo Field")
            imgName = "T-Mobile Park";
        else if (stadiums[i].name == "Turner Field")
            imgName = "Truist park";
        else
            imgName = name;

        // UI aesthetics.
        if (name.length() <= 15)
            spacing = "\t\t";
        else
            spacing = "\t";
        if (name == "Dodger Stadium" || name == "Yankee Stadium")
            spacing = "\t";
        spacing2 = "\t\t";
        if (name == "RingCentral Coliseum")
            spacing2 = "\t";

        // Add stadium name, date opened, and team name to QListWidget
        item = new QListWidgetItem(QIcon(":/images/Stadium Pics/" + imgName + ".jpg"),
                                   name + spacing + dateOpened + spacing2 + teamName);
        item->setSizeHint(QSize(25, 25));
        ui->listWidget->addItem(item);
    }
    if (ui->ALOnlyCheckBox->isChecked())
        on_ALOnlyCheckBox_stateChanged(1);
    if (ui->NLOnlyCheckBox->isChecked())
        on_NLOnlyCheckBox_stateChanged(1);
    if (ui->artificalFieldCheckBox->isChecked())
        on_artificalFieldCheckBox_stateChanged(1);
    if (ui->grassOnlyCheckBox->isChecked())
        on_grassOnlyCheckBox_stateChanged(1);
}
