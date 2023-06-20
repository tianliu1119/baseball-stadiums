#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include <QtCore>
#include <QGraphicsEffect>
#include <QMessageBox>
#include <QPushButton>
#include <chrono>
#include <iostream>
#include <string>
#include <unordered_map>
#include <utility>
#include "password_change.h"
#include "souvenir.h"
#include "stadium.h"
#include "stadium_reports.h"
#include "undirectedgraph.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    int loadStadiums(QString filePath);
    int loadFlights(QString filePath);
    void setPicPaths();
    void initGUI();
    void setCurrFlights(Path tripPath);
    void changeDestin(std::vector<Stadium> &stads);
    virtual void paintEvent(QPaintEvent */*event*/) override;
    virtual void mousePressEvent(QMouseEvent */*event*/) override;
    void setUpStadiumInfoTable();
    void resizeHeaders();
    void updateTable(Stadium stad);
    void updateShortPath(QString picPath, Stadium stad);
    void updateShortPathTable(Path tripPath);
    void updateChooseStadsTable();
    void updateTripPathTable(std::vector<std::string> flightPath);
    void stadPressedActions(QString imagePath, Stadium stad);
    int countStadVisited(std::vector<std::string> path);
    void updateAddSouvTable();

private slots:
    void on_safeCoParkPush_clicked();
    void on_attParkPush_clicked();
    void on_ringCentralPush_clicked();
    void on_dodgerStadiumPush_clicked();
    void on_angelStadiumPush_clicked();
    void on_petcoParkPush_clicked();
    void on_chaseFieldPush_clicked();
    void on_coorsFieldPush_clicked();
    void on_kauffmanStadiumPush_clicked();
    void on_globeLifeFieldPush_clicked();
    void on_minuteMaidParkPush_clicked();
    void on_targetFieldPush_clicked();
    void on_millerParkPush_clicked();
    void on_wrigleyFieldPush_clicked();
    void on_usCellularFieldPush_clicked();
    void on_buschStadiumPush_clicked();
    void on_comericaParkPush_clicked();
    void on_progressiveFieldPush_clicked();
    void on_greatAmBallParkPush_clicked();
    void on_turnerFieldPush_clicked();
    void on_tropicanaFieldPush_clicked();
    void on_marlinsParkPush_clicked();
    void on_rogersCentrePush_clicked();
    void on_pncParkPush_clicked();
    void on_yankeeStadiumPush_clicked();
    void on_nationalsParkPush_clicked();
    void on_camdenYardsPush_clicked();
    void on_citizensBankParkPush_clicked();
    void on_citiFieldPush_clicked();
    void on_fenwayParkPush_clicked();
    void on_showMLRadio_clicked();
    void on_showALRadio_clicked();
    void on_showNLRadio_clicked();
    void on_showDistRadio_clicked();
    void on_showEdgeRadio_clicked();
    void on_showStadRadio_clicked();
    void on_showGrassRadio_clicked();
    void on_showTurfRadio_clicked();
    void on_verifyPush_clicked();
    void on_clearPasswordPush_clicked();
    void on_beginCalcDistPush_clicked();
    void on_calcShortPathCancelPush_clicked();
    void on_clearOriginPush_clicked();
    void on_clearDestinPush_clicked();
    void on_passwordLineEdit_returnPressed();
    void on_calcShortPathPush_clicked();
    void on_shortPathResetPush_clicked();
    void on_planYourOwnPush_clicked();
    void on_cancelGoLabel_clicked();
    void on_goLabel_clicked();
    void on_stadToVisitTableWidget_cellClicked(int row, int column);
    void on_deleteStadPush_clicked();
    void on_tripPlanResetPush_clicked();
    void on_visitMLPush_clicked();
    void on_visitALPush_clicked();
    void on_visitNLPush_clicked();
    void on_showTripTableWidget_cellClicked(int row, int column);
    void on_addSouvClosePush_clicked();
    void on_addSouvPush_clicked();
    void on_addSouvQtySpin_valueChanged(int arg1);
    void on_modifyStadPush_clicked();
    void on_modifySouvenirPush_clicked();
    void on_stadModifyCancelPush_clicked();
    void on_selectStadModifyCombo_currentIndexChanged(int index);
    void on_stadModifyApplyPush_clicked();
    void on_souvStadComboBox_currentIndexChanged(int index);
    void on_souvModifyDonePush_clicked();
    void on_souvModifyTableWidget_cellChanged(int row, int column);
    void on_addSouvComboBox_currentIndexChanged(int index);
    void on_souvModifyTableWidget_cellClicked(int row, int column);
    void on_souvModifyDeletePush_clicked();
    void on_souvModifyAddPush_clicked();
    void on_souvModifyAddClosePush_clicked();
    void on_souvModifyAddConfirmPush_clicked();
    void on_souvModifyAddNameLineEdit_returnPressed();
    void on_souvModifyAddPriceLineEdit_returnPressed();
    void on_moveToFirstPush_clicked();
    void on_addTeamPush_clicked();
    void onUserButtonClicked();
    void on_addStadNextPush_clicked();
    void on_addStadAddFlightPush_clicked();
    void on_addStadCancelPush_clicked();
    void on_addStadSelectSrcCombo_currentIndexChanged(int index);
    void on_addStadSkipPush_clicked();
    void on_changePasswordPush_clicked();
    void on_adminLogOutPush_clicked();
    void on_viewStadiumsPush_clicked();

private:
    Ui::MainWindow *ui;

    QPixmap pixmap;                                      // map display device
    QPainter painter;                                    // painting device for map
    std::unordered_map<std::string, size_t> stadIndexes; // hash table of all stadiums
    std::vector<Stadium> stadiums;                       // list of all stadiums
    std::vector<Stadium> currStadiums;                   // stadiums to display on map
    std::vector<Stadium> selected;                       // stadiums selected by user
    std::unordered_map<std::string, size_t> edgeIndexes; // hash table of all flights
    std::vector<Edge> flights;                           // list of all flights
    std::vector<Edge> currFlights;                       // flights to display on the map
    std::vector<Stadium> wishList;                       // souvenirs bought by user
    UndirectedGraph stadiumGraph;                        // represents the flight network
    QString password = "Password";                       // the admin password
    std::vector<QPushButton*> buttons;                   // buttons created by user
    bool calcShortPath;                                  // user wishes to calc. path
    bool calcTrip;                                       // user wishes to plan trip
    bool MLTrip;                                         // user wishes to plan ML Trip
    bool addingPush;                                     // user is adding push button
    bool addingDot;                                      // user is adding stadium pip
    int activeRow;                                       // row of the cell clicked in a
                                                         //   table widget
};

/**********************************************************
 *
 * Method loadStadiums: Class MainWindow
 *_________________________________________________________
 * This method loads the list of stadiums from a file.
 *   The file path is passed in as the argument.
 *   –returns 1 if there was an error with the file or
 *    file path and returns 0 if the file was read
 *_________________________________________________________
 * PRE-CONDITIONS
 *   filePath: the path of the file
 *
 * POST-CONDITIONS
 *   Loads stadiums from a file and stores the stadiums in
 *   class attributes, including the hash map.
 **********************************************************/

/**********************************************************
 *
 * Method loadFlights: Class MainWindow
 *_________________________________________________________
 * This method loads the list of flights from a file.
 *   The file path is passed in as the argument.
 *   –returns 1 if there was an error with the file or
 *    file path and returns 0 if the file was read
 *_________________________________________________________
 * PRE-CONDITIONS
 *   filePath: the path of the file
 *
 * POST-CONDITIONS
 *   Loads flights from a file and stores the flights in
 *   class attributes, including the hash map.
 **********************************************************/

/**********************************************************
 *
 * Method setPicPaths: Class MainWindow
 *_________________________________________________________
 * This method assigns to each stadium the file path to
 *   their own stadium pictures.
 *   –returns nothing
 *_________________________________________________________
 * PRE-CONDITIONS
 *
 * POST-CONDITIONS
 *   Sets the file path of the stadium picture for each
 *   stadium.
 **********************************************************/

/**********************************************************
 *
 * Method initGUI: Class MainWindow
 *_________________________________________________________
 * This method initializes the GUI.
 *   –returns nothing
 *_________________________________________________________
 * PRE-CONDITIONS
 *
 * POST-CONDITIONS
 *   Initializes the GUI.
 **********************************************************/

/**********************************************************
 *
 * Method setCurrFlights: Class MainWindow
 *_________________________________________________________
 * This method sets the currFlights attribute to the list
 *   of stadiums passed in as the argument.
 *   –returns nothing
 *_________________________________________________________
 * PRE-CONDITIONS
 *   destins: the list of stadiums to visit
 *
 * POST-CONDITIONS
 *   Sets currFlights to include only the stadiums in the
 *   argument.
 **********************************************************/

/**********************************************************
 *
 * Method changeDestin: Class MainWindow
 *_________________________________________________________
 * This method changes any stadiums in "stads" that are
 *   American League to the corresponding National League
 *   stadium if they are considered the same destination.
 *   –returns nothing
 *_________________________________________________________
 * PRE-CONDITIONS
 *   stads: the list of stadiums
 *
 * POST-CONDITIONS
 *   Changes any American League stadiums to corresponding
 *   National League stadiums if they are considered the
 *   same destination.
 **********************************************************/

/**********************************************************
 *
 * Method setUpStadiumInfoTable: Class MainWindow
 *_________________________________________________________
 * This method sets up the stadium info table.
 *   –returns nothing
 *_________________________________________________________
 * PRE-CONDITIONS
 *
 * POST-CONDITIONS
 *   Sets up the stadium info table.
 **********************************************************/

/**********************************************************
 *
 * Method resizeHeaders: Class MainWindow
 *_________________________________________________________
 * This method sets up the stadium info table's header
 *   resize mode and frame style.
 *   –returns nothing
 *_________________________________________________________
 * PRE-CONDITIONS
 *
 * POST-CONDITIONS
 *   Sets up the stadium info table's header resize mode
 *   and frame style.
 **********************************************************/

/**********************************************************
 *
 * Method updateTable: Class MainWindow
 *_________________________________________________________
 * This method updates the stadium info table with the
 *   given stadium's info.
 *   –returns nothing
 *_________________________________________________________
 * PRE-CONDITIONS
 *   stad: the stadium whose info is to be shown
 *
 * POST-CONDITIONS
 *   Updates the stadium info table to show the info of
 *   the given stadium.
 **********************************************************/

/**********************************************************
 *
 * Method updateShortPath: Class MainWindow
 *_________________________________________________________
 * This method updates the calculate shortest path between
 *   2 stadiums tool.
 *   –returns nothing
 *_________________________________________________________
 * PRE-CONDITIONS
 *   stad: the stadium to visit
 *   picPath: the path of the stadium's picture
 *
 * POST-CONDITIONS
 *   Updates the calculate shortest path tool.
 **********************************************************/

/**********************************************************
 *
 * Method updateChooseStadsTable: Class MainWindow
 *_________________________________________________________
 * This method updates the table showing the list of
 *   stadiums to visit.
 *   –returns nothing
 *_________________________________________________________
 * PRE-CONDITIONS
 *
 * POST-CONDITIONS
 *   Updates the table showing the list of stadiums to
 *   visit.
 **********************************************************/

/**********************************************************
 *
 * Method stadPressedActions: Class MainWindow
 *_________________________________________________________
 * This method manages the set of actions that must occur
 *   when a stadium is clicked on the map.
 *   –returns nothing
 *_________________________________________________________
 * PRE-CONDITIONS
 *
 * POST-CONDITIONS
 *   Invokes the set of actions that occurs when a
 *   stadium is clicked on the map.
 **********************************************************/

/**********************************************************
 *
 * Method countStadVisited: Class MainWindow
 *_________________________________________________________
 * This method counts the number of stadiums visited in
 *   the given path.
 *   –returns number of stadiums visited
 *_________________________________________________________
 * PRE-CONDITIONS
 *   path: the trip path
 *
 * POST-CONDITIONS
 *   Returns the number of stadiums visited in the given
 *   path.
 **********************************************************/

/**********************************************************
 *
 * Method updateShortPathTable: Class MainWindow
 *_________________________________________________________
 * This method updates the calculate shortest path between
 *   2 stadiums table to show the shortest path.
 *   –returns nothing
 *_________________________________________________________
 * PRE-CONDITIONS
 *   flightPath: the shortest path to display on the table
 *
 * POST-CONDITIONS
 *   Updates the shortest path between 2 stadiums table to
 *   show the shortest path.
 **********************************************************/

/**********************************************************
 *
 * Method updateTripPathTable: Class MainWindow
 *_________________________________________________________
 * This method updates the trip planner table to show the
 *   shortest path to visit all stadiums.
 *   –returns nothing
 *_________________________________________________________
 * PRE-CONDITIONS
 *   flightPath: the shortest path to display on the table
 *
 * POST-CONDITIONS
 *   Updates the trip planner table to show the shortest
 *   path to visit all stadiums.
 **********************************************************/

/**********************************************************
 *
 * Method updateAddSouvTable: Class MainWindow
 *_________________________________________________________
 * This method updates the add souvenir wish list table in
 *   the trip planner to show the list of souvenirs that
 *   the user wishes to buy.
 *   –returns nothing
 *_________________________________________________________
 * PRE-CONDITIONS
 *
 * POST-CONDITIONS
 *   Updates the add souvenir wish list table in the trip
 *   planner to show the list of souvenirs that the user
 *   wishes to buy.
 **********************************************************/

#endif // MAINWINDOW_H
