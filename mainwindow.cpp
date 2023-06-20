#include "mainwindow.h"
#include "ui_mainwindow.h"
using namespace std;

/**********************************************************
 *
 * Method MainWindow: Class MainWindow
 *_________________________________________________________
 * This is the main window constructor. It assigns default
 *   values to class attributes and loads the stadiums and
 *   flights from text files. It also initializes the GUI.
 *   –returns nothing
 *_________________________________________________________
 * PRE-CONDITIONS
 *   parent: QWidget*
 *
 * POST-CONDITIONS
 *   Class attributes and GUI initialized. Stadiums and
 *   flights loaded.
 **********************************************************/
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , calcShortPath(false)
    , calcTrip(false)
    , MLTrip(false)
    , addingPush(false)
    , addingDot(false)
{
    ui->setupUi(this);

    loadStadiums("C:/Users/tlred/OneDrive/Documents/Project_2_CS008/stadiums.txt");
    loadFlights("C:/Users/tlred/OneDrive/Documents/Project_2_CS008/distances.txt");

    initGUI();
}

/**********************************************************
 *
 * Method ~MainWindow: Class MainWindow
 *_________________________________________________________
 * This is the main window destructor.
 *   –returns nothing
 *_________________________________________________________
 * PRE-CONDITIONS
 *
 * POST-CONDITIONS
 *   Destroys the MainWindow object.
 **********************************************************/
MainWindow::~MainWindow()
{
    delete ui;
}

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
int MainWindow::loadStadiums(QString filePath)    // IN - the stadiums file path
{
    QFile inFile;
    Stadium newStadium;
    string name;
    string team;
    string location;
    string phone;
    string capacity;
    string opened;
    string surface;
    string league;
    string xStr;
    string yStr;

    inFile.setFileName(filePath);

    if (!inFile.exists())
    {
        cout << "File doesn't exist" << endl;
        return 1;
    }

    if(!inFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        cout << "Error: Can't Open File." << endl;
        return 1;
    }

    QTextStream in(&inFile);
    while (!in.atEnd())
    {
        name     = in.readLine().toStdString();
        team     = in.readLine().toStdString();
        location = in.readLine().toStdString();
        phone    = in.readLine().toStdString();
        capacity = in.readLine().toStdString();
        opened   = in.readLine().toStdString();
        surface  = in.readLine().toStdString();
        league   = in.readLine().toStdString();
        xStr     = in.readLine().toStdString();
        yStr     = in.readLine().toStdString();

        newStadium = Stadium(name, team, location, phone, capacity, opened,
                             surface, league, stoi(xStr), stoi(yStr));

        stadIndexes[newStadium.name] = stadiums.size();
        stadiums.push_back(newStadium);
    }

    inFile.close();
    return 0;
}

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
int MainWindow::loadFlights(QString filePath)    // IN - the flights file path
{
    QFile inFile;
    QStringList edgeList;
    Edge newFlight;
    QString edgeLine;
    QString firstStadName;
    QString secondStadName;
    QString distance;
    Node firstStad;
    Node secondStad;

    inFile.setFileName(filePath);

    if (!inFile.exists())
    {
        cout << "File doesn't exist" << endl;
        return 1;
    }

    if (!inFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        cout << "Error: Can't Open File." << endl;
        return 1;
    }

    QTextStream in(&inFile);
    while (!in.atEnd())
    {
        edgeLine = in.readLine();
        edgeList = edgeLine.split(QLatin1Char(','), Qt::SkipEmptyParts);

        firstStadName = edgeList.at(0);
        secondStadName = edgeList.at(1);
        distance = edgeList.at(2);

        firstStad = Node(firstStadName.toStdString());
        secondStad = Node(secondStadName.toStdString());

        newFlight = Edge(firstStad, secondStad, distance.toInt());
        edgeIndexes[newFlight.key] = flights.size();
        flights.push_back(newFlight);
    }

    inFile.close();
    return 0;
}

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
void MainWindow::setPicPaths()
{
    for (unsigned i = 0; i < stadiums.size(); i++)
    {
        if (stadiums.at(i).name == "Miller Park")
        {
            stadiums.at(i).picPath =
                  ":/images/Stadium Pics/American Family Field.jpg";
            stadiums.at(i).lblTxt = "Miller Park";
        }
        else if (stadiums.at(i).name == "Angel Stadium")
        {
            stadiums.at(i).picPath =
                          ":/images/Stadium Pics/Angel Stadium.jpg";
            stadiums.at(i).lblTxt = "Angel Stadium";
        }
        else if (stadiums.at(i).name == "Busch Stadium")
        {
            stadiums.at(i).picPath =
                          ":/images/Stadium Pics/Busch Stadium.jpg";
            stadiums.at(i).lblTxt = "Busch\nStadium";
        }
        else if (stadiums.at(i).name == "Chase Field")
        {
            stadiums.at(i).picPath =
                            ":/images/Stadium Pics/Chase Field.jpg";
            stadiums.at(i).lblTxt = "Chase Field";
        }
        else if (stadiums.at(i).name == "Citi Field")
        {
            stadiums.at(i).picPath =
                             ":/images/Stadium Pics/Citi Field.jpg";
            stadiums.at(i).lblTxt = "Citi Field";
        }
        else if (stadiums.at(i).name == "Citizens Bank Park")
        {
            stadiums.at(i).picPath =
                     ":/images/Stadium Pics/Citizens Bank Park.jpg";
            stadiums.at(i).lblTxt = "Citizens Bank Park";
        }
        else if (stadiums.at(i).name == "Comerica Park")
        {
            stadiums.at(i).picPath =
                          ":/images/Stadium Pics/Comerica Park.jpg";
            stadiums.at(i).lblTxt = "Comerica\nPark";
        }
        else if (stadiums.at(i).name == "Coors Field")
        {
            stadiums.at(i).picPath =
                            ":/images/Stadium Pics/Coors Field.jpg";
            stadiums.at(i).lblTxt = "Coors Field";
        }
        else if (stadiums.at(i).name == "Dodger Stadium")
        {
            stadiums.at(i).picPath =
                         ":/images/Stadium Pics/Dodger Stadium.jpg";
            stadiums.at(i).lblTxt = "Dodger Stadium";
        }
        else if (stadiums.at(i).name == "Fenway Park")
        {
            stadiums.at(i).picPath =
                            ":/images/Stadium Pics/Fenway Park.jpg";
            stadiums.at(i).lblTxt = "Fenway\nPark";
        }
        else if (stadiums.at(i).name == "Globe Life Field")
        {
            stadiums.at(i).picPath =
                       ":/images/Stadium Pics/Globe Life Field.jpg";
            stadiums.at(i).lblTxt = "Globe Life Field";
        }
        else if (stadiums.at(i).name == "Great American Ball Park")
        {
            stadiums.at(i).picPath =
               ":/images/Stadium Pics/Great American Ball Park.jpg";
            stadiums.at(i).lblTxt = "Great American\nBall Park";
        }
        else if (stadiums.at(i).name == "US Cellular Field")
        {
            stadiums.at(i).picPath =
                  ":/images/Stadium Pics/Guaranteed Rate Field.jpg";
            stadiums.at(i).lblTxt = "US Cellular\nField";
        }
        else if (stadiums.at(i).name == "Kauffman Stadium")
        {
            stadiums.at(i).picPath =
                       ":/images/Stadium Pics/Kauffman Stadium.jpg";
            stadiums.at(i).lblTxt = "Kauffman Stadium";
        }
        else if (stadiums.at(i).name == "Marlins Park")
        {
            stadiums.at(i).picPath =
                         ":/images/Stadium Pics/LoanDepot Park.jpg";
            stadiums.at(i).lblTxt = "Marlins Park";
        }
        else if (stadiums.at(i).name == "Minute Maid Park")
        {
            stadiums.at(i).picPath =
                       ":/images/Stadium Pics/Minute Maid Park.jpg";
            stadiums.at(i).lblTxt = "Minute Maid Park";
        }
        else if (stadiums.at(i).name == "Nationals Park")
        {
            stadiums.at(i).picPath =
                         ":/images/Stadium Pics/Nationals Park.jpg";
            stadiums.at(i).lblTxt = "Nationals\nPark";
        }
        else if (stadiums.at(i).name == "AT&T Park")
        {
            stadiums.at(i).picPath =
                            ":/images/Stadium Pics/Oracle Park.jpg";
            stadiums.at(i).lblTxt = "AT&T Park";
        }
        else if (stadiums.at(i).name == "Oriole Park at Camden Yards")
        {
            stadiums.at(i).picPath =
                           ":/images/Stadium Pics/Camden Yards.jpg";
            stadiums.at(i).lblTxt = "Camden Yards";
        }
        else if (stadiums.at(i).name == "Petco Park")
        {
            stadiums.at(i).picPath =
                             ":/images/Stadium Pics/Petco Park.jpg";
            stadiums.at(i).lblTxt = "Petco Park";
        }
        else if (stadiums.at(i).name == "PNC Park")
        {
            stadiums.at(i).picPath =
                               ":/images/Stadium Pics/PNC Park.jpg";
            stadiums.at(i).lblTxt = "PNC\nPark";
        }
        else if (stadiums.at(i).name == "Progressive Field")
        {
            stadiums.at(i).picPath =
                      ":/images/Stadium Pics/Progressive Field.jpg";
            stadiums.at(i).lblTxt = "Progressive\nField";
        }
        else if (stadiums.at(i).name == "RingCentral Coliseum")
        {
            stadiums.at(i).picPath =
                   ":/images/Stadium Pics/RingCentral Coliseum.jpg";
            stadiums.at(i).lblTxt = "RingCentral Coliseum";
        }
        else if (stadiums.at(i).name == "Rogers Centre")
        {
            stadiums.at(i).picPath =
                          ":/images/Stadium Pics/Rogers Centre.jpg";
            stadiums.at(i).lblTxt = "Rogers\nCentre";
        }
        else if (stadiums.at(i).name == "SafeCo Field")
        {
            stadiums.at(i).picPath =
                          ":/images/Stadium Pics/T-Mobile Park.jpg";
            stadiums.at(i).lblTxt = "SafeCo Field";
        }
        else if (stadiums.at(i).name == "Target Field")
        {
            stadiums.at(i).picPath =
                           ":/images/Stadium Pics/Target Field.jpg";
            stadiums.at(i).lblTxt = "Target Field";
        }
        else if (stadiums.at(i).name == "Tropicana Field")
        {
            stadiums.at(i).picPath =
                        ":/images/Stadium Pics/Tropicana Field.jpg";
            stadiums.at(i).lblTxt = "Tropicana Field";
        }
        else if (stadiums.at(i).name == "Turner Field")
        {
            stadiums.at(i).picPath =
                            ":/images/Stadium Pics/Truist park.jpg";
            stadiums.at(i).lblTxt = "Turner Field";
        }
        else if (stadiums.at(i).name == "Wrigley Field")
        {
            stadiums.at(i).picPath =
                          ":/images/Stadium Pics/Wrigley Field.jpg";
            stadiums.at(i).lblTxt = "Wrigley Field";
        }
        else if (stadiums.at(i).name == "Yankee Stadium")
        {
            stadiums.at(i).picPath =
                         ":/images/Stadium Pics/Yankee Stadium.jpg";
            stadiums.at(i).lblTxt = "Yankee\nStadium";
        }
    }
}

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
void MainWindow::initGUI()
{
    QGraphicsDropShadowEffect *shadow;

    // general
    setPicPaths();
    stadiumGraph = UndirectedGraph(flights);

    // stadium info table
    setUpStadiumInfoTable();
    ui->stadiumInfoTable->hide();
    ui->selectForInfoLabel->show();

    // admin tools
    shadow = new QGraphicsDropShadowEffect;
    shadow->setBlurRadius(10);
    shadow->setXOffset(5);
    shadow->setYOffset(5);
    shadow->setColor(Qt::black);

    ui->badPasswordLabel->hide();
    ui->loggedInLabel->hide();
    ui->souvModifyAddFrame->setGraphicsEffect(shadow);
    ui->adminStacked->setCurrentIndex(0);
    ui->souvModifyAddFrame->hide();
    ui->souvModifyDeletePush->setDisabled(true);
    ui->souvModifyBadInputLabel->hide();
    ui->addStadCheckedLabel1->hide();
    ui->addStadCheckedLabel2->hide();
    ui->addStadCheckedLabel3->hide();
    ui->adminFrame->setDisabled(true);

    // map
    currStadiums = stadiums;
    currFlights = flights;
    ui->showMLRadio->click();
    ui->showStadRadio->click();

    // trip planner
    shadow = new QGraphicsDropShadowEffect;
    shadow->setBlurRadius(10);
    shadow->setXOffset(5);
    shadow->setYOffset(5);
    shadow->setColor(Qt::black);

    ui->tripPlannerStacked->setCurrentIndex(0);
    ui->addSouvFrame->setGraphicsEffect(shadow);
    ui->addSouvFrame->hide();
    ui->souvAddedLabel->hide();
    ui->startFromFirstRadio->click();
    ui->moveToFirstPush->setDisabled(true);

    // calculate shortest distance between 2 stadiums
    ui->chooseStadLabel->setWordWrap(true);
    ui->originNameLabel->setWordWrap(true);
    ui->destinNameLabel->setWordWrap(true);
    ui->calcDistStacked->setCurrentIndex(0);
}

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
void MainWindow::setCurrFlights(Path tripPath)  // IN - names of
                                                         //      stadiums to
                                                         //      visit
{
    currFlights.clear();
    currFlights = tripPath.edges;
}

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
void MainWindow::changeDestin(vector<Stadium> &stads)  // CALC: list of stadiums
{
    for (unsigned i = 0; i < stads.size(); i++)
    {
        if (stads.at(i).name == "RingCentral Coliseum")
            stads.at(i) = stadiums.at(stadIndexes["AT&T Park"]);
        else if (stads.at(i).name == "Angel Stadium")
            stads.at(i) = stadiums.at(stadIndexes["Dodger Stadium"]);
        else if (stads.at(i).name == "US Cellular Field")
            stads.at(i) = stadiums.at(stadIndexes["Wrigley Field"]);
        else if (stads.at(i).name == "Yankee Stadium")
            stads.at(i) = stadiums.at(stadIndexes["Citi Field"]);
        else if (stads.at(i).name == "Oriole Park at Camden Yards")
            stads.at(i) = stadiums.at(stadIndexes["Nationals Park"]);
    }
}

/**********************************************************
 *
 * Method paintEvent: Class MainWindow
 *_________________________________________________________
 * This method paints the pips of the stadiums as well as
 *   the lines denoting the flights.
 *   –returns nothing
 *_________________________________________________________
 * PRE-CONDITIONS
 *
 * POST-CONDITIONS
 *   Paints stadium pips and flight lines onto the map.
 **********************************************************/
void MainWindow::paintEvent(QPaintEvent */*event*/)
{
    QPixmap pixmap = QPixmap(ui->mlbLocationsMapLabel->width(),
                             ui->mlbLocationsMapLabel->height());
    pixmap.fill(QColor("transparent"));

    QPainter painter(&pixmap);
    painter.setRenderHint(QPainter::Antialiasing);

    for (size_t i = 0; i < stadiums.size(); i++)
    {
        if (stadiums.at(i).x == 0 && stadiums.at(i).y == 0)
            continue;

        if (!ui->showStadRadio->isChecked() && ui->showALRadio->isChecked())
        {
            if (stadiums.at(i).name != "AT&T Park" &&
                stadiums.at(i).name != "Dodger Stadium" &&
                stadiums.at(i).name != "Wrigley Field" &&
                stadiums.at(i).name != "Citi Field" &&
                stadiums.at(i).name != "Nationals Park")
            {
                if (stadiums.at(i).league.substr(0,2) != "AL")
                    continue;
            }
        }
        else if (!ui->showStadRadio->isChecked() && ui->showNLRadio->isChecked())
        {
            if (stadiums.at(i).name != "RingCentral Coliseum" &&
                stadiums.at(i).name != "Angel Stadium" &&
                stadiums.at(i).name != "US Cellular Field" &&
                stadiums.at(i).name != "Yankee Stadium" &&
                stadiums.at(i).name != "Oriole Park at Camden Yards")
            {
                if (stadiums.at(i).league.substr(0,2) != "NL")
                    continue;
            }
        }
        else
        {
            if (ui->showALRadio->isChecked() &&
                stadiums.at(i).league.substr(0,2) != "AL")
                continue;
            if (ui->showNLRadio->isChecked() &&
                stadiums.at(i).league.substr(0,2) != "NL")
                continue;
            if (ui->showGrassRadio->isChecked() &&
                stadiums.at(i).surface != "Grass")
                continue;
            if (ui->showTurfRadio->isChecked() &&
                stadiums.at(i).surface != "Artificial turf")
                continue;
        }

        if (stadiums.at(i).league == "AL East")
            painter.setPen(QPen(Qt::red, 7, Qt::SolidLine,
                                Qt::RoundCap));
        else if (stadiums.at(i).league == "AL Central")
            painter.setPen(QPen(Qt::yellow, 7, Qt::SolidLine,
                                Qt::RoundCap));
        else if (stadiums.at(i).league == "AL West")
            painter.setPen(QPen(QColor(255,165,0), 7, Qt::SolidLine,
                                Qt::RoundCap));
        else if (stadiums.at(i).league == "NL East")
            painter.setPen(QPen(Qt::blue, 7, Qt::SolidLine,
                                Qt::RoundCap));
        else if (stadiums.at(i).league == "NL Central")
            painter.setPen(QPen(Qt::magenta, 7, Qt::SolidLine,
                                Qt::RoundCap));
        else if (stadiums.at(i).league == "NL West")
            painter.setPen(QPen(Qt::darkGreen, 7, Qt::SolidLine,
                                Qt::RoundCap));

        painter.drawPoint(stadiums.at(i).x, stadiums.at(i).y);
    }

    if (!ui->showStadRadio->isChecked())
    {
        QPointF srcpt;
        QPointF endpt;
        Stadium srcStad;
        Stadium endStad;
        int xTxt;
        int yTxt;

        for (size_t i = 0; i < currFlights.size(); i++)
        {
            painter.setPen(QPen(QColor(70,70,70), 1, Qt::SolidLine));

            srcStad = stadiums.at(stadIndexes[currFlights.at(i).src]);
            endStad = stadiums.at(stadIndexes[currFlights.at(i).dst]);

            if (ui->showALRadio->isChecked())
            {
                if (srcStad.name == "AT&T Park")
                    srcStad = stadiums.at(stadIndexes["RingCentral "
                                                          "Coliseum"]);
                else if (srcStad.name == "Dodger Stadium")
                    srcStad = stadiums.at(stadIndexes["Angel Stadium"]);
                else if (srcStad.name == "Wrigley Field")
                    srcStad = stadiums.at(stadIndexes["US Cellular Field"]);
                else if (srcStad.name == "Citi Field")
                    srcStad = stadiums.at(stadIndexes["Yankee Stadium"]);
                else if (srcStad.name == "Nationals Park")
                    srcStad= stadiums.at(stadIndexes["Oriole Park at "
                                                         "Camden Yards"]);
                if (endStad.name == "AT&T Park")
                    endStad = stadiums.at(stadIndexes["RingCentral "
                                                          "Coliseum"]);
                else if (endStad.name == "Dodger Stadium")
                    endStad = stadiums.at(stadIndexes["Angel Stadium"]);
                else if (endStad.name == "Wrigley Field")
                    endStad = stadiums.at(stadIndexes["US Cellular Field"]);
                else if (endStad.name == "Citi Field")
                    endStad = stadiums.at(stadIndexes["Yankee Stadium"]);
                else if (endStad.name == "Nationals Park")
                    endStad= stadiums.at(stadIndexes["Oriole Park at "
                                                         "Camden Yards"]);

                if (srcStad.name == currFlights.at(i).src &&
                    srcStad.league.substr(0,2) != "AL")
                    continue;
                if (endStad.name == currFlights.at(i).dst &&
                    endStad.league.substr(0,2) != "AL")
                    continue;
            }
            else if (ui->showNLRadio->isChecked())
            {
                if (srcStad.league.substr(0,2) != "NL" ||
                    endStad.league.substr(0,2) != "NL")
                    continue;
            }

            srcpt = QPointF(srcStad.x, srcStad.y);
            endpt = QPointF(endStad.x, endStad.y);

            painter.drawLine(srcpt, endpt);

            if (ui->showDistRadio->isChecked())
            {
                painter.setPen(Qt::darkRed);
                xTxt = (endStad.x + srcStad.x) / 2;
                yTxt = (endStad.y + srcStad.y) / 2;

                if (currFlights.at(i) == Edge(Node("SafeCo Field"), Node("Target Field")))
                    xTxt += 5;
                else if (currFlights.at(i) == Edge(Node("SafeCo Field"), Node("Rogers Centre")))
                    xTxt += 10;
                else if (currFlights.at(i) == Edge(Node("SafeCo Field"),
                                                      Node("AT&T Park")))
                    xTxt += 5;
                else if (currFlights.at(i) == Edge(Node("AT&T Park"),
                                                   Node("Dodger Stadium")))
                {
                    xTxt -= 20;
                    yTxt += 10;
                }
                else if (currFlights.at(i) == Edge(Node("AT&T Park"),
                                                      Node("Chase Field")))
                {
                    xTxt -= 10;
                    yTxt -= 10;
                }
                else if (currFlights.at(i) == Edge(Node("Dodger Stadium"),
                                                    Node("Petco Park")))
                {
                    xTxt += 2;
                    yTxt += 3;
                }
                else if (currFlights.at(i) == Edge(Node("Petco Park"),
                                                      Node("Chase Field")))
                {
                    xTxt -= 10;
                    yTxt += 10;
                }
                else if (currFlights.at(i) == Edge(Node("Petco Park"),
                                                      Node("Coors Field")))
                {
                    xTxt -= 12;
                    yTxt -= 3;
                }
                else if (currFlights.at(i) == Edge(Node("Chase Field"),
                                                      Node("Coors Field")))
                {
                    xTxt += 3;
                    yTxt += 6;
                }
                else if (currFlights.at(i) == Edge(Node("Dodger Stadium"),
                                                    Node("Target Field")))
                {
                    xTxt -= 12;
                    yTxt -= 5;
                }
                else if (currFlights.at(i) == Edge(Node("Globe Life Field"),
                                                 Node("Kauffman Stadium")))
                    xTxt += 3;
                else if (currFlights.at(i) == Edge(Node("Minute Maid Park"),
                                                  Node("Busch Stadium")))
                    xTxt += 5;
                else if (currFlights.at(i) == Edge(Node("Globe Life Field"),
                                                  Node("Turner Field")))
                    yTxt -= 4;
                else if (currFlights.at(i) == Edge(Node("Target Field"),
                                                      Node("Miller Park")))
                {
                    xTxt -= 5;
                    yTxt -= 2;
                }
                else if (currFlights.at(i) == Edge(Node("Target Field"),
                                                    Node("Busch Stadium")))
                {
                    xTxt -= 19;
                    yTxt += 5;
                }
                else if (currFlights.at(i) == Edge(Node("Wrigley Field"),
                                                 Node("Kauffman Stadium")))
                {
                    xTxt += 5;
                    yTxt += 3;
                }
                else if (currFlights.at(i) == Edge(Node("Great American Ball Park"),
                                          Node("Busch Stadium")))
                {
                    xTxt -= 8;
                    yTxt -= 3;
                }
                else if (currFlights.at(i) == Edge(Node("Great American Ball Park"),
                                          Node("Progressive Field")))
                {
                    xTxt -= 20;
                    yTxt += 3;
                }
                else if (currFlights.at(i) == Edge(Node("Great American Ball Park"),
                                          Node("PNC Park")))
                {
                    xTxt -= 5;
                    yTxt += 10;
                }
                else if (currFlights.at(i) == Edge(Node("Progressive Field"),
                                                 Node("PNC Park")))
                {
                    xTxt -= 5;
                    yTxt -= 1;
                }
                else if (currFlights.at(i) == Edge(Node("Rogers Centre"),
                                                    Node("Comerica Park")))
                    yTxt += 9;
                else if (currFlights.at(i) == Edge(Node("Rogers Centre"),
                                                     Node("Miller Park")))
                    yTxt -= 6;
                else if (currFlights.at(i) == Edge(Node("Citi Field"),
                                                        Node("PNC Park")))
                    xTxt -= 15;
                else if (currFlights.at(i) == Edge(Node("Citi Field"),
                                               Node("Citizens Bank Park")))
                    yTxt += 8;
                else if (currFlights.at(i) == Edge(Node("Citi Field"),
                                                      Node("Fenway Park")))
                    xTxt -= 17;
                else if (currFlights.at(i) == Edge(Node("Turner Field"),
                                                   Node("Nationals Park")))
                    yTxt += 8;
                else if (currFlights.at(i) == Edge(Node("Turner Field"),
                                         Node("Great American Ball Park")))
                {
                    xTxt -= 18;
                    yTxt += 7;
                }
                else if (currFlights.at(i) == Edge(Node("Wrigley Field"),
                                                    Node("Comerica Park")))
                {
                    xTxt -= 5;
                    yTxt -= 3;
                }
                else if (currFlights.at(i) == Edge(Node("Nationals Park"),
                                               Node("Citizens Bank Park")))
                {
                    xTxt += 5;
                    yTxt += 2;
                }
                else if (currFlights.at(i) == Edge(Node("Wrigley Field"),
                                                     Node("Miller Park")))
                    yTxt += 3;
                else if (currFlights.at(i) == Edge(Node("Turner Field"),
                                                     Node("Marlins Park")))
                {
                    xTxt += 11;
                    yTxt += 16;
                }

                painter.drawText(xTxt, yTxt,
                                 QString::number(currFlights.at(i).weight));
            }
        }
    }

    ui->mlbLocationsMapLabel->setPixmap(pixmap);
}

/**********************************************************
 *
 * Method mousePressEvent: Class MainWindow
 *_________________________________________________________
 * This method records the mouse click event. It is used
 *   when the user wishes the add a new stadium and the
 *   corresponding stadium pip and push button on the map.
 *   –returns nothing
 *_________________________________________________________
 * PRE-CONDITIONS
 *   event: the mouse click event
 *
 * POST-CONDITIONS
 *   Adds the pip and push button of a newly created
 *   stadium onto the map.
 **********************************************************/
void MainWindow::mousePressEvent(QMouseEvent *event)  // CALC: mouse click event
{
    QPushButton *newButton;

    if (addingDot)
    {
        stadiums.at(stadiums.size() - 1).x = event->pos().x() - 311;
        stadiums.at(stadiums.size() - 1).y = event->pos().y() - 221;
        update();

        ui->addStadCheckedLabel1->show();
        ui->addStadInstructLabel->setText("Click on a location on the\nmap to "
                                          "add stadium label");
        addingDot = false;
        addingPush = true;
        return;
    }

    if (addingPush)
    {
        newButton = new QPushButton(ui->mlbLocationsMapLabel);
        newButton->setText
                (QString::fromStdString(stadiums.at(stadiums.size() - 1).name));
        newButton->setGeometry(event->pos().x() - 311, event->pos().y() - 225,
                               60, 20);
        newButton->setVisible(true);
        newButton->setEnabled(true);
        newButton->setStyleSheet("QPushButton {background-color: transparent; "
                                 "color: blue; border-image: none;}"
                                 "QPushButton:hover {text-decoration: "
                                 "underline; }");
        newButton->setCursor(QCursor(Qt::PointingHandCursor));
        newButton->raise();
        newButton->adjustSize();
        connect(newButton, SIGNAL(clicked()), this, SLOT(onUserButtonClicked()));

        ui->addStadCheckedLabel2->show();
        ui->addStadInstructLabel->hide();
        ui->addStadSelectSrcLabel->show();
        ui->addStadSelectSrcCombo->show();
        ui->addStadSrcDistanceLabel->show();
        ui->addStadSrcDistLineEdit->show();
        ui->addStadAddFlightMilesLabel->show();
        ui->addStadAddFlightPush->show();
        buttons.push_back(newButton);
        addingPush = false;
        ui->mlbLocationsMapLabel->setCursor(QCursor(Qt::ArrowCursor));
    }
}

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
void MainWindow::setUpStadiumInfoTable()
{
    QTableWidget *table;
    QTableWidgetItem *newItem;

    table = ui->stadiumInfoTable;
    table->setColumnCount(7);
    table->setRowCount(2);

    newItem = new QTableWidgetItem("Name");
    newItem->setTextAlignment(Qt::AlignCenter);
    table->setItem(0, 0, newItem);

    newItem = new QTableWidgetItem("Team");
    newItem->setTextAlignment(Qt::AlignCenter);
    table->setItem(0, 1, newItem);

    newItem = new QTableWidgetItem("Location");
    newItem->setTextAlignment(Qt::AlignCenter);
    table->setItem(0, 2, newItem);

    newItem = new QTableWidgetItem("Box Office #");
    newItem->setTextAlignment(Qt::AlignCenter);
    table->setItem(0, 3, newItem);

    newItem = new QTableWidgetItem("Capacity");
    newItem->setTextAlignment(Qt::AlignCenter);
    table->setItem(0, 4, newItem);

    newItem = new QTableWidgetItem("Opened");
    newItem->setTextAlignment(Qt::AlignCenter);
    table->setItem(0, 5, newItem);

    newItem = new QTableWidgetItem("Surface");
    newItem->setTextAlignment(Qt::AlignCenter);
    table->setItem(0, 6, newItem);

    table->verticalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
}

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
void MainWindow::resizeHeaders()
{
    QHeaderView *headerH;

    headerH = ui->stadiumInfoTable->horizontalHeader();
    headerH->setSectionResizeMode(1, QHeaderView::ResizeToContents);
    headerH->setSectionResizeMode(2, QHeaderView::ResizeToContents);

    ui->stadiumInfoTable->setFrameStyle(QFrame::StyledPanel | QFrame::Plain);
    ui->stadiumPicLabel ->setFrameStyle(QFrame::StyledPanel | QFrame::Plain);
    ui->stadiumInfoTable->show();
    ui->selectForInfoLabel->hide();
}

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
void MainWindow::updateTable(Stadium stad)  // CALC - stadium to show info on
{
    QTableWidget *table;
    QTableWidgetItem *newItem;

    table = ui->stadiumInfoTable;

    newItem = new QTableWidgetItem(QString::fromStdString(stad.name));
    newItem->setTextAlignment(Qt::AlignCenter);
    table->setItem(1, 0, newItem);

    newItem = new QTableWidgetItem(QString::fromStdString(stad.team));
    newItem->setTextAlignment(Qt::AlignCenter);
    table->setItem(1, 1, newItem);

    newItem = new QTableWidgetItem(QString::fromStdString(stad.location));
    newItem->setTextAlignment(Qt::AlignCenter);
    table->setItem(1, 2, newItem);

    newItem = new QTableWidgetItem(QString::fromStdString(stad.phone));
    newItem->setTextAlignment(Qt::AlignCenter);
    table->setItem(1, 3, newItem);

    newItem = new QTableWidgetItem(QString::fromStdString(stad.capacity));
    newItem->setTextAlignment(Qt::AlignCenter);
    table->setItem(1, 4, newItem);

    newItem = new QTableWidgetItem(QString::fromStdString(stad.opened));
    newItem->setTextAlignment(Qt::AlignCenter);
    table->setItem(1, 5, newItem);

    newItem = new QTableWidgetItem(QString::fromStdString(stad.surface));
    newItem->setTextAlignment(Qt::AlignCenter);
    table->setItem(1, 6, newItem);

    resizeHeaders();
}

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
void MainWindow::updateShortPath(QString picPath,  // CALC: stadium pic path
                                 Stadium stad)     // CALC: stadium to visit
{
    if (calcShortPath)
    {
        if (ui->originNameLabel->text() == "")
        {
            ui->originPicLabel->clear();
            ui->originPicLabel->setStyleSheet(picPath);
            ui->originNameLabel->setText(QString::fromStdString(stad.lblTxt));
            ui->clearOriginPush->show();
            ui->chooseStadLabel->setText("Choose destination stadium from the map");
            if (ui->destinNameLabel->text() != "")
            {
                ui->chooseStadLabel->setText("Select \"Go!\"");
                ui->calcShortPathPush->setEnabled(true);
                calcShortPath = false;
            }
        }
        else
        {
            ui->destinPicLabel->clear();
            ui->destinPicLabel->setStyleSheet(picPath);
            ui->clearDestinPush->show();
            ui->destinNameLabel->setText(QString::fromStdString(stad.lblTxt));
            if (ui->originNameLabel->text() != "")
            {
                ui->chooseStadLabel->setText("Select \"Go!\"");;
                ui->calcShortPathPush->setEnabled(true);
                calcShortPath = false;
            }
        }
    }
}

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
void MainWindow::updateChooseStadsTable()
{
    QImage *stadPic;
    QTableWidgetItem *newItem;
    QTableWidget *table;

    table = ui->stadToVisitTableWidget;
    table->clear();
    table->setColumnCount(2);
    table->setRowCount(selected.size());
    ui->chooseStadsLabel->hide();

    for (unsigned i = 0; i < selected.size(); i++)
    {
        stadPic = new QImage(QString::fromStdString(selected.at(i).picPath));
        newItem = new QTableWidgetItem;
        newItem->setData(Qt::DecorationRole,
                         QPixmap::fromImage(*stadPic).scaled(100, 75));
        table->setItem(i, 0, newItem);

        newItem = new QTableWidgetItem
                                (QString::fromStdString(selected.at(i).lblTxt));
        newItem->setTextAlignment(Qt::AlignCenter);
        table->setItem(i, 1, newItem);
    }

    ui->tripNumStadValLabel->setText(QString::number(selected.size()));
    table->horizontalHeader()->setSectionResizeMode
                                             (0, QHeaderView::ResizeToContents);
    table->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    table->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
}

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
void MainWindow::stadPressedActions(QString imagePath,  // CALC: stadium picpath
                                    Stadium stad)       // CALC: stadium clicked
{
    if(imagePath != "")
        ui->stadiumPicLabel->setStyleSheet(imagePath);
    else
        ui->stadiumPicLabel->setStyleSheet("image: none");

    updateTable(stad);
    updateShortPath(imagePath, stad);

    if (calcTrip)
    {
        for (unsigned i = 0; i < selected.size(); i++)
        {
            if (selected.at(i).name == stad.name)
                return;
        }

        selected.push_back(stad);
        ui->goLabel->setEnabled(true);
        updateChooseStadsTable();
    }
}

/**********************************************************
 *
 * Method on_safeCoParkPush_clicked: Class MainWindow
 *_________________________________________________________
 * This slot invokes the stadPressedActions function for
 *   the stadium that was clicked.
 *   –returns nothing
 *_________________________________________________________
 * PRE-CONDITIONS
 *
 * POST-CONDITIONS
 *   Calls the stadPressedActions function for the stadium
 *   clicked.
 **********************************************************/
void MainWindow::on_safeCoParkPush_clicked()
{
    QString imagePath;
    Stadium stad;

    imagePath = "image: url(:/images/Stadium Pics/T-Mobile Park.jpg)";
    stad = stadiums.at(stadIndexes["SafeCo Field"]);

    stadPressedActions(imagePath, stad);
}

/**********************************************************
 *
 * Method on_attParkPush_clicked: Class MainWindow
 *_________________________________________________________
 * This slot invokes the stadPressedActions function for
 *   the stadium that was clicked.
 *   –returns nothing
 *_________________________________________________________
 * PRE-CONDITIONS
 *
 * POST-CONDITIONS
 *   Calls the stadPressedActions function for the stadium
 *   clicked.
 **********************************************************/
void MainWindow::on_attParkPush_clicked()
{
    QString imagePath;
    Stadium stad;

    imagePath = "image: url(:/images/Stadium Pics/Oracle Park.jpg)";
    stad = stadiums.at(stadIndexes["AT&T Park"]);

    stadPressedActions(imagePath, stad);
}

/**********************************************************
 *
 * Method on_ringCentralPush_clicked: Class MainWindow
 *_________________________________________________________
 * This slot invokes the stadPressedActions function for
 *   the stadium that was clicked.
 *   –returns nothing
 *_________________________________________________________
 * PRE-CONDITIONS
 *
 * POST-CONDITIONS
 *   Calls the stadPressedActions function for the stadium
 *   clicked.
 **********************************************************/
void MainWindow::on_ringCentralPush_clicked()
{
    QString imagePath;
    Stadium stad;

    imagePath = "image: url(:/images/Stadium Pics/RingCentral Coliseum.jpg)";
    stad = stadiums.at(stadIndexes["RingCentral Coliseum"]);

    stadPressedActions(imagePath, stad);
}

/**********************************************************
 *
 * Method on_dodgerStadiumPush_clicked: Class MainWindow
 *_________________________________________________________
 * This slot invokes the stadPressedActions function for
 *   the stadium that was clicked.
 *   –returns nothing
 *_________________________________________________________
 * PRE-CONDITIONS
 *
 * POST-CONDITIONS
 *   Calls the stadPressedActions function for the stadium
 *   clicked.
 **********************************************************/
void MainWindow::on_dodgerStadiumPush_clicked()
{
    QString imagePath;
    Stadium stad;

    imagePath = "image: url(:/images/Stadium Pics/Dodger Stadium.jpg)";
    stad = stadiums.at(stadIndexes["Dodger Stadium"]);

    stadPressedActions(imagePath, stad);
}

/**********************************************************
 *
 * Method on_angelStadiumPush_clicked: Class MainWindow
 *_________________________________________________________
 * This slot invokes the stadPressedActions function for
 *   the stadium that was clicked.
 *   –returns nothing
 *_________________________________________________________
 * PRE-CONDITIONS
 *
 * POST-CONDITIONS
 *   Calls the stadPressedActions function for the stadium
 *   clicked.
 **********************************************************/
void MainWindow::on_angelStadiumPush_clicked()
{
    QString imagePath;
    Stadium stad;

    imagePath = "image: url(:/images/Stadium Pics/Angel Stadium.jpg)";
    stad = stadiums.at(stadIndexes["Angel Stadium"]);

    stadPressedActions(imagePath, stad);
}

/**********************************************************
 *
 * Method on_petcoParkPush_clicked: Class MainWindow
 *_________________________________________________________
 * This slot invokes the stadPressedActions function for
 *   the stadium that was clicked.
 *   –returns nothing
 *_________________________________________________________
 * PRE-CONDITIONS
 *
 * POST-CONDITIONS
 *   Calls the stadPressedActions function for the stadium
 *   clicked.
 **********************************************************/
void MainWindow::on_petcoParkPush_clicked()
{
    QString imagePath;
    Stadium stad;

    imagePath = "image: url(:/images/Stadium Pics/Petco Park.jpg)";
    stad = stadiums.at(stadIndexes["Petco Park"]);

    stadPressedActions(imagePath, stad);
}

/**********************************************************
 *
 * Method on_chaseFieldPush_clicked: Class MainWindow
 *_________________________________________________________
 * This slot invokes the stadPressedActions function for
 *   the stadium that was clicked.
 *   –returns nothing
 *_________________________________________________________
 * PRE-CONDITIONS
 *
 * POST-CONDITIONS
 *   Calls the stadPressedActions function for the stadium
 *   clicked.
 **********************************************************/
void MainWindow::on_chaseFieldPush_clicked()
{
    QString imagePath;
    Stadium stad;

    imagePath = "image: url(:/images/Stadium Pics/Chase Field.jpg)";
    stad = stadiums.at(stadIndexes["Chase Field"]);

    stadPressedActions(imagePath, stad);
}

/**********************************************************
 *
 * Method on_coorsFieldPush_clicked: Class MainWindow
 *_________________________________________________________
 * This slot invokes the stadPressedActions function for
 *   the stadium that was clicked.
 *   –returns nothing
 *_________________________________________________________
 * PRE-CONDITIONS
 *
 * POST-CONDITIONS
 *   Calls the stadPressedActions function for the stadium
 *   clicked.
 **********************************************************/
void MainWindow::on_coorsFieldPush_clicked()
{
    QString imagePath;
    Stadium stad;

    imagePath = "image: url(:/images/Stadium Pics/Coors Field.jpg)";
    stad = stadiums.at(stadIndexes["Coors Field"]);

    stadPressedActions(imagePath, stad);
}

/**********************************************************
 *
 * Method on_kauffmanStadiumPush_clicked: Class MainWindow
 *_________________________________________________________
 * This slot invokes the stadPressedActions function for
 *   the stadium that was clicked.
 *   –returns nothing
 *_________________________________________________________
 * PRE-CONDITIONS
 *
 * POST-CONDITIONS
 *   Calls the stadPressedActions function for the stadium
 *   clicked.
 **********************************************************/
void MainWindow::on_kauffmanStadiumPush_clicked()
{
    QString imagePath;
    Stadium stad;

    imagePath = "image: url(:/images/Stadium Pics/Kauffman Stadium.jpg)";
    stad = stadiums.at(stadIndexes["Kauffman Stadium"]);

    stadPressedActions(imagePath, stad);
}

/**********************************************************
 *
 * Method on_globeLifeFieldPush_clicked: Class MainWindow
 *_________________________________________________________
 * This slot invokes the stadPressedActions function for
 *   the stadium that was clicked.
 *   –returns nothing
 *_________________________________________________________
 * PRE-CONDITIONS
 *
 * POST-CONDITIONS
 *   Calls the stadPressedActions function for the stadium
 *   clicked.
 **********************************************************/
void MainWindow::on_globeLifeFieldPush_clicked()
{
    QString imagePath;
    Stadium stad;

    imagePath = "image: url(:/images/Stadium Pics/Globe Life Field.jpg)";
    stad = stadiums.at(stadIndexes["Globe Life Field"]);

    stadPressedActions(imagePath, stad);
}

/**********************************************************
 *
 * Method on_minuteMaidParkPush_clicked: Class MainWindow
 *_________________________________________________________
 * This slot invokes the stadPressedActions function for
 *   the stadium that was clicked.
 *   –returns nothing
 *_________________________________________________________
 * PRE-CONDITIONS
 *
 * POST-CONDITIONS
 *   Calls the stadPressedActions function for the stadium
 *   clicked.
 **********************************************************/
void MainWindow::on_minuteMaidParkPush_clicked()
{
    QString imagePath;
    Stadium stad;

    imagePath = "image: url(:/images/Stadium Pics/Minute Maid Park.jpg)";
    stad = stadiums.at(stadIndexes["Minute Maid Park"]);

    stadPressedActions(imagePath, stad);
}

/**********************************************************
 *
 * Method on_targetFieldPush_clicked: Class MainWindow
 *_________________________________________________________
 * This slot invokes the stadPressedActions function for
 *   the stadium that was clicked.
 *   –returns nothing
 *_________________________________________________________
 * PRE-CONDITIONS
 *
 * POST-CONDITIONS
 *   Calls the stadPressedActions function for the stadium
 *   clicked.
 **********************************************************/
void MainWindow::on_targetFieldPush_clicked()
{
    QString imagePath;
    Stadium stad;

    imagePath = "image: url(:/images/Stadium Pics/Target Field.jpg)";
    stad = stadiums.at(stadIndexes["Target Field"]);

    stadPressedActions(imagePath, stad);
}

/**********************************************************
 *
 * Method on_millerParkPush_clicked: Class MainWindow
 *_________________________________________________________
 * This slot invokes the stadPressedActions function for
 *   the stadium that was clicked.
 *   –returns nothing
 *_________________________________________________________
 * PRE-CONDITIONS
 *
 * POST-CONDITIONS
 *   Calls the stadPressedActions function for the stadium
 *   clicked.
 **********************************************************/
void MainWindow::on_millerParkPush_clicked()
{
    QString imagePath;
    Stadium stad;

    imagePath = "image: url(:/images/Stadium Pics/American Family Field.jpg)";
    stad = stadiums.at(stadIndexes["Miller Park"]);

    stadPressedActions(imagePath, stad);
}

/**********************************************************
 *
 * Method on_wrigleyFieldPush_clicked: Class MainWindow
 *_________________________________________________________
 * This slot invokes the stadPressedActions function for
 *   the stadium that was clicked.
 *   –returns nothing
 *_________________________________________________________
 * PRE-CONDITIONS
 *
 * POST-CONDITIONS
 *   Calls the stadPressedActions function for the stadium
 *   clicked.
 **********************************************************/
void MainWindow::on_wrigleyFieldPush_clicked()
{
    QString imagePath;
    Stadium stad;

    imagePath = "image: url(:/images/Stadium Pics/Wrigley Field.jpg)";
    stad = stadiums.at(stadIndexes["Wrigley Field"]);

    stadPressedActions(imagePath, stad);
}

/**********************************************************
 *
 * Method on_usCellularFieldPush_clicked: Class MainWindow
 *_________________________________________________________
 * This slot invokes the stadPressedActions function for
 *   the stadium that was clicked.
 *   –returns nothing
 *_________________________________________________________
 * PRE-CONDITIONS
 *
 * POST-CONDITIONS
 *   Calls the stadPressedActions function for the stadium
 *   clicked.
 **********************************************************/
void MainWindow::on_usCellularFieldPush_clicked()
{
    QString imagePath;
    Stadium stad;

    imagePath = "image: url(:/images/Stadium Pics/Guaranteed Rate Field.jpg)";
    stad = stadiums.at(stadIndexes["US Cellular Field"]);

    stadPressedActions(imagePath, stad);
}

/**********************************************************
 *
 * Method on_buschStadiumPush_clicked: Class MainWindow
 *_________________________________________________________
 * This slot invokes the stadPressedActions function for
 *   the stadium that was clicked.
 *   –returns nothing
 *_________________________________________________________
 * PRE-CONDITIONS
 *
 * POST-CONDITIONS
 *   Calls the stadPressedActions function for the stadium
 *   clicked.
 **********************************************************/
void MainWindow::on_buschStadiumPush_clicked()
{
    QString imagePath;
    Stadium stad;

    imagePath = "image: url(:/images/Stadium Pics/Busch Stadium.jpg)";
    stad = stadiums.at(stadIndexes["Busch Stadium"]);

    stadPressedActions(imagePath, stad);
}

/**********************************************************
 *
 * Method on_comericaParkPush_clicked: Class MainWindow
 *_________________________________________________________
 * This slot invokes the stadPressedActions function for
 *   the stadium that was clicked.
 *   –returns nothing
 *_________________________________________________________
 * PRE-CONDITIONS
 *
 * POST-CONDITIONS
 *   Calls the stadPressedActions function for the stadium
 *   clicked.
 **********************************************************/
void MainWindow::on_comericaParkPush_clicked()
{
    QString imagePath;
    Stadium stad;

    imagePath = "image: url(:/images/Stadium Pics/Comerica Park.jpg)";
    stad = stadiums.at(stadIndexes["Comerica Park"]);

    stadPressedActions(imagePath, stad);
}

/**********************************************************
 *
 * Method on_progressiveFieldPush_clicked: Class MainWindow
 *_________________________________________________________
 * This slot invokes the stadPressedActions function for
 *   the stadium that was clicked.
 *   –returns nothing
 *_________________________________________________________
 * PRE-CONDITIONS
 *
 * POST-CONDITIONS
 *   Calls the stadPressedActions function for the stadium
 *   clicked.
 **********************************************************/
void MainWindow::on_progressiveFieldPush_clicked()
{
    QString imagePath;
    Stadium stad;

    imagePath = "image: url(:/images/Stadium Pics/Progressive Field.jpg)";
    stad = stadiums.at(stadIndexes["Progressive Field"]);

    stadPressedActions(imagePath, stad);
}

/**********************************************************
 *
 * Method on_greatAmBallParkPush_clicked: Class MainWindow
 *_________________________________________________________
 * This slot invokes the stadPressedActions function for
 *   the stadium that was clicked.
 *   –returns nothing
 *_________________________________________________________
 * PRE-CONDITIONS
 *
 * POST-CONDITIONS
 *   Calls the stadPressedActions function for the stadium
 *   clicked.
 **********************************************************/
void MainWindow::on_greatAmBallParkPush_clicked()
{
    QString imagePath;
    Stadium stad;

    imagePath = "image: url(:/images/Stadium Pics/Great American Ball Park.jpg)";
    stad = stadiums.at(stadIndexes["Great American Ball Park"]);

    stadPressedActions(imagePath, stad);
}

/**********************************************************
 *
 * Method on_turnerFieldPush_clicked: Class MainWindow
 *_________________________________________________________
 * This slot invokes the stadPressedActions function for
 *   the stadium that was clicked.
 *   –returns nothing
 *_________________________________________________________
 * PRE-CONDITIONS
 *
 * POST-CONDITIONS
 *   Calls the stadPressedActions function for the stadium
 *   clicked.
 **********************************************************/
void MainWindow::on_turnerFieldPush_clicked()
{
    QString imagePath;
    Stadium stad;

    imagePath = "image: url(:/images/Stadium Pics/Truist park.jpg)";
    stad = stadiums.at(stadIndexes["Turner Field"]);

    stadPressedActions(imagePath, stad);
}

/**********************************************************
 *
 * Method on_tropicanaFieldPush_clicked: Class MainWindow
 *_________________________________________________________
 * This slot invokes the stadPressedActions function for
 *   the stadium that was clicked.
 *   –returns nothing
 *_________________________________________________________
 * PRE-CONDITIONS
 *
 * POST-CONDITIONS
 *   Calls the stadPressedActions function for the stadium
 *   clicked.
 **********************************************************/
void MainWindow::on_tropicanaFieldPush_clicked()
{
    QString imagePath;
    Stadium stad;

    imagePath = "image: url(:/images/Stadium Pics/Tropicana Field.jpg)";
    stad = stadiums.at(stadIndexes["Tropicana Field"]);

    stadPressedActions(imagePath, stad);
}

/**********************************************************
 *
 * Method on_marlinsParkPush_clicked: Class MainWindow
 *_________________________________________________________
 * This slot invokes the stadPressedActions function for
 *   the stadium that was clicked.
 *   –returns nothing
 *_________________________________________________________
 * PRE-CONDITIONS
 *
 * POST-CONDITIONS
 *   Calls the stadPressedActions function for the stadium
 *   clicked.
 **********************************************************/
void MainWindow::on_marlinsParkPush_clicked()
{
    QString imagePath;
    Stadium stad;

    imagePath = "image: url(:/images/Stadium Pics/LoanDepot Park.jpg)";
    stad = stadiums.at(stadIndexes["Marlins Park"]);

    stadPressedActions(imagePath, stad);
}

/**********************************************************
 *
 * Method on_rogersCentrePush_clicked: Class MainWindow
 *_________________________________________________________
 * This slot invokes the stadPressedActions function for
 *   the stadium that was clicked.
 *   –returns nothing
 *_________________________________________________________
 * PRE-CONDITIONS
 *
 * POST-CONDITIONS
 *   Calls the stadPressedActions function for the stadium
 *   clicked.
 **********************************************************/
void MainWindow::on_rogersCentrePush_clicked()
{
    QString imagePath;
    Stadium stad;

    imagePath = "image: url(:/images/Stadium Pics/Rogers Centre.jpg)";
    stad = stadiums.at(stadIndexes["Rogers Centre"]);

    stadPressedActions(imagePath, stad);
}

/**********************************************************
 *
 * Method on_pncParkPush_clicked: Class MainWindow
 *_________________________________________________________
 * This slot invokes the stadPressedActions function for
 *   the stadium that was clicked.
 *   –returns nothing
 *_________________________________________________________
 * PRE-CONDITIONS
 *
 * POST-CONDITIONS
 *   Calls the stadPressedActions function for the stadium
 *   clicked.
 **********************************************************/
void MainWindow::on_pncParkPush_clicked()
{
    QString imagePath;
    Stadium stad;

    imagePath = "image: url(:/images/Stadium Pics/PNC Park.jpg)";
    stad = stadiums.at(stadIndexes["PNC Park"]);

    stadPressedActions(imagePath, stad);
}

/**********************************************************
 *
 * Method on_yankeeStadiumPush_clicked: Class MainWindow
 *_________________________________________________________
 * This slot invokes the stadPressedActions function for
 *   the stadium that was clicked.
 *   –returns nothing
 *_________________________________________________________
 * PRE-CONDITIONS
 *
 * POST-CONDITIONS
 *   Calls the stadPressedActions function for the stadium
 *   clicked.
 **********************************************************/
void MainWindow::on_yankeeStadiumPush_clicked()
{
    QString imagePath;
    Stadium stad;

    imagePath = "image: url(:/images/Stadium Pics/Yankee Stadium.jpg)";
    stad = stadiums.at(stadIndexes["Yankee Stadium"]);

    stadPressedActions(imagePath, stad);
}

/**********************************************************
 *
 * Method on_nationalsParkPush_clicked: Class MainWindow
 *_________________________________________________________
 * This slot invokes the stadPressedActions function for
 *   the stadium that was clicked.
 *   –returns nothing
 *_________________________________________________________
 * PRE-CONDITIONS
 *
 * POST-CONDITIONS
 *   Calls the stadPressedActions function for the stadium
 *   clicked.
 **********************************************************/
void MainWindow::on_nationalsParkPush_clicked()
{
    QString imagePath;
    Stadium stad;

    imagePath = "image: url(:/images/Stadium Pics/Nationals Park.jpg)";
    stad = stadiums.at(stadIndexes["Nationals Park"]);

    stadPressedActions(imagePath, stad);
}

/**********************************************************
 *
 * Method on_camdenYardsPush_clicked: Class MainWindow
 *_________________________________________________________
 * This slot invokes the stadPressedActions function for
 *   the stadium that was clicked.
 *   –returns nothing
 *_________________________________________________________
 * PRE-CONDITIONS
 *
 * POST-CONDITIONS
 *   Calls the stadPressedActions function for the stadium
 *   clicked.
 **********************************************************/
void MainWindow::on_camdenYardsPush_clicked()
{    
    QString imagePath;
    Stadium stad;

    imagePath = "image: url(:/images/Stadium Pics/Camden Yards.jpg)";
    stad = stadiums.at(stadIndexes["Oriole Park at Camden Yards"]);

    stadPressedActions(imagePath, stad);
}

/**********************************************************
 *
 * Method on_citizensBankParkPush_clicked: Class MainWindow
 *_________________________________________________________
 * This slot invokes the stadPressedActions function for
 *   the stadium that was clicked.
 *   –returns nothing
 *_________________________________________________________
 * PRE-CONDITIONS
 *
 * POST-CONDITIONS
 *   Calls the stadPressedActions function for the stadium
 *   clicked.
 **********************************************************/
void MainWindow::on_citizensBankParkPush_clicked()
{
    QString imagePath;
    Stadium stad;

    imagePath = "image: url(:/images/Stadium Pics/Citizens Bank Park.jpg)";
    stad = stadiums.at(stadIndexes["Citizens Bank Park"]);

    stadPressedActions(imagePath, stad);
}

/**********************************************************
 *
 * Method on_citiFieldPush_clicked: Class MainWindow
 *_________________________________________________________
 * This slot invokes the stadPressedActions function for
 *   the stadium that was clicked.
 *   –returns nothing
 *_________________________________________________________
 * PRE-CONDITIONS
 *
 * POST-CONDITIONS
 *   Calls the stadPressedActions function for the stadium
 *   clicked.
 **********************************************************/
void MainWindow::on_citiFieldPush_clicked()
{
    QString imagePath;
    Stadium stad;

    imagePath = "image: url(:/images/Stadium Pics/Citi Field.jpg)";
    stad = stadiums.at(stadIndexes["Citi Field"]);

    stadPressedActions(imagePath, stad);
}

/**********************************************************
 *
 * Method on_fenwayParkPush_clicked: Class MainWindow
 *_________________________________________________________
 * This slot invokes the stadPressedActions function for
 *   the stadium that was clicked.
 *   –returns nothing
 *_________________________________________________________
 * PRE-CONDITIONS
 *
 * POST-CONDITIONS
 *   Calls the stadPressedActions function for the stadium
 *   clicked.
 **********************************************************/
void MainWindow::on_fenwayParkPush_clicked()
{
    QString imagePath;
    Stadium stad;

    imagePath = "image: url(:/images/Stadium Pics/Fenway Park.jpg)";
    stad = stadiums.at(stadIndexes["Fenway Park"]);

    stadPressedActions(imagePath, stad);
}

/**********************************************************
 *
 * Method on_showMLRadio_clicked: Class MainWindow
 *_________________________________________________________
 * This slot makes appropriate changes to the UI after the
 *   button has been clicked.
 *   –returns nothing
 *_________________________________________________________
 * PRE-CONDITIONS
 *
 * POST-CONDITIONS
 *   Makes changes to the UI after the button has been
 *   clicked.
 **********************************************************/
void MainWindow::on_showMLRadio_clicked()
{
    ui->safeCoParkPush->      show();
    ui->attParkPush->         show();
    ui->ringCentralPush->     show();
    ui->dodgerStadiumPush->   show();
    ui->angelStadiumPush->    show();
    ui->petcoParkPush->       show();
    ui->chaseFieldPush->      show();
    ui->coorsFieldPush->      show();
    ui->kauffmanStadiumPush-> show();
    ui->globeLifeFieldPush->  show();
    ui->minuteMaidParkPush->  show();
    ui->buschStadiumPush->    show();
    ui->targetFieldPush->     show();
    ui->millerParkPush->      show();
    ui->wrigleyFieldPush->    show();
    ui->usCellularFieldPush-> show();
    ui->greatAmBallParkPush-> show();
    ui->comericaParkPush->    show();
    ui->progressiveFieldPush->show();
    ui->turnerFieldPush->     show();
    ui->tropicanaFieldPush->  show();
    ui->marlinsParkPush->     show();
    ui->pncParkPush->         show();
    ui->rogersCentrePush->    show();
    ui->nationalsParkPush->   show();
    ui->camdenYardsPush->     show();
    ui->citizensBankParkPush->show();
    ui->citiFieldPush->       show();
    ui->yankeeStadiumPush->   show();
    ui->fenwayParkPush->      show();
    update();
}

/**********************************************************
 *
 * Method on_showALRadio_clicked: Class MainWindow
 *_________________________________________________________
 * This slot makes appropriate changes to the UI after the
 *   button has been clicked.
 *   –returns nothing
 *_________________________________________________________
 * PRE-CONDITIONS
 *
 * POST-CONDITIONS
 *   Makes changes to the UI after the button has been
 *   clicked.
 **********************************************************/
void MainWindow::on_showALRadio_clicked()
{
    ui->safeCoParkPush->      show();
    ui->attParkPush->         hide();
    ui->ringCentralPush->     show();
    ui->dodgerStadiumPush->   hide();
    ui->angelStadiumPush->    show();
    ui->petcoParkPush->       hide();
    ui->chaseFieldPush->      hide();
    ui->coorsFieldPush->      hide();
    ui->kauffmanStadiumPush-> show();
    ui->globeLifeFieldPush->  show();
    ui->minuteMaidParkPush->  show();
    ui->buschStadiumPush->    hide();
    ui->targetFieldPush->     show();
    ui->millerParkPush->      hide();
    ui->wrigleyFieldPush->    hide();
    ui->usCellularFieldPush-> show();
    ui->greatAmBallParkPush-> hide();
    ui->comericaParkPush->    show();
    ui->progressiveFieldPush->show();
    ui->turnerFieldPush->     hide();
    ui->tropicanaFieldPush->  show();
    ui->marlinsParkPush->     hide();
    ui->pncParkPush->         hide();
    ui->rogersCentrePush->    show();
    ui->nationalsParkPush->   hide();
    ui->camdenYardsPush->     show();
    ui->citizensBankParkPush->hide();
    ui->citiFieldPush->       hide();
    ui->yankeeStadiumPush->   show();
    ui->fenwayParkPush->      show();
    update();
}

/**********************************************************
 *
 * Method on_showNLRadio_clicked: Class MainWindow
 *_________________________________________________________
 * This slot makes appropriate changes to the UI after the
 *   button has been clicked.
 *   –returns nothing
 *_________________________________________________________
 * PRE-CONDITIONS
 *
 * POST-CONDITIONS
 *   Makes changes to the UI after the button has been
 *   clicked.
 **********************************************************/
void MainWindow::on_showNLRadio_clicked()
{
    ui->safeCoParkPush->      hide();
    ui->attParkPush->         show();
    ui->ringCentralPush->     hide();
    ui->dodgerStadiumPush->   show();
    ui->angelStadiumPush->    hide();
    ui->petcoParkPush->       show();
    ui->chaseFieldPush->      show();
    ui->coorsFieldPush->      show();
    ui->kauffmanStadiumPush-> hide();
    ui->globeLifeFieldPush->  hide();
    ui->minuteMaidParkPush->  hide();
    ui->buschStadiumPush->    show();
    ui->targetFieldPush->     hide();
    ui->millerParkPush->      show();
    ui->wrigleyFieldPush->    show();
    ui->usCellularFieldPush-> hide();
    ui->greatAmBallParkPush-> show();
    ui->comericaParkPush->    hide();
    ui->progressiveFieldPush->hide();
    ui->turnerFieldPush->     show();
    ui->tropicanaFieldPush->  hide();
    ui->marlinsParkPush->     show();
    ui->pncParkPush->         show();
    ui->rogersCentrePush->    hide();
    ui->nationalsParkPush->   show();
    ui->camdenYardsPush->     hide();
    ui->citizensBankParkPush->show();
    ui->citiFieldPush->       show();
    ui->yankeeStadiumPush->   hide();
    ui->fenwayParkPush->      hide();
    update();
}

/**********************************************************
 *
 * Method on_showGrassRadio_clicked: Class MainWindow
 *_________________________________________________________
 * This slot makes appropriate changes to the UI after the
 *   button has been clicked.
 *   –returns nothing
 *_________________________________________________________
 * PRE-CONDITIONS
 *
 * POST-CONDITIONS
 *   Makes changes to the UI after the button has been
 *   clicked.
 **********************************************************/
void MainWindow::on_showGrassRadio_clicked()
{
    ui->safeCoParkPush->      show();
    ui->attParkPush->         show();
    ui->ringCentralPush->     show();
    ui->dodgerStadiumPush->   show();
    ui->angelStadiumPush->    show();
    ui->petcoParkPush->       show();
    ui->chaseFieldPush->      hide();
    ui->coorsFieldPush->      show();
    ui->kauffmanStadiumPush-> show();
    ui->globeLifeFieldPush->  show();
    ui->minuteMaidParkPush->  show();
    ui->buschStadiumPush->    show();
    ui->targetFieldPush->     show();
    ui->millerParkPush->      show();
    ui->wrigleyFieldPush->    show();
    ui->usCellularFieldPush-> show();
    ui->greatAmBallParkPush-> show();
    ui->comericaParkPush->    show();
    ui->progressiveFieldPush->show();
    ui->turnerFieldPush->     show();
    ui->tropicanaFieldPush->  hide();
    ui->marlinsParkPush->     hide();
    ui->pncParkPush->         show();
    ui->rogersCentrePush->    hide();
    ui->nationalsParkPush->   show();
    ui->camdenYardsPush->     show();
    ui->citizensBankParkPush->show();
    ui->citiFieldPush->       show();
    ui->yankeeStadiumPush->   show();
    ui->fenwayParkPush->      show();
    update();
}

/**********************************************************
 *
 * Method on_showTurfRadio_clicked: Class MainWindow
 *_________________________________________________________
 * This slot makes appropriate changes to the UI after the
 *   button has been clicked.
 *   –returns nothing
 *_________________________________________________________
 * PRE-CONDITIONS
 *
 * POST-CONDITIONS
 *   Makes changes to the UI after the button has been
 *   clicked.
 **********************************************************/
void MainWindow::on_showTurfRadio_clicked()
{
    ui->safeCoParkPush->      hide();
    ui->attParkPush->         hide();
    ui->ringCentralPush->     hide();
    ui->dodgerStadiumPush->   hide();
    ui->angelStadiumPush->    hide();
    ui->petcoParkPush->       hide();
    ui->chaseFieldPush->      show();
    ui->coorsFieldPush->      hide();
    ui->kauffmanStadiumPush-> hide();
    ui->globeLifeFieldPush->  hide();
    ui->minuteMaidParkPush->  hide();
    ui->buschStadiumPush->    hide();
    ui->targetFieldPush->     hide();
    ui->millerParkPush->      hide();
    ui->wrigleyFieldPush->    hide();
    ui->usCellularFieldPush-> hide();
    ui->greatAmBallParkPush-> hide();
    ui->comericaParkPush->    hide();
    ui->progressiveFieldPush->hide();
    ui->turnerFieldPush->     hide();
    ui->tropicanaFieldPush->  show();
    ui->marlinsParkPush->     show();
    ui->pncParkPush->         hide();
    ui->rogersCentrePush->    show();
    ui->nationalsParkPush->   hide();
    ui->camdenYardsPush->     hide();
    ui->citizensBankParkPush->hide();
    ui->citiFieldPush->       hide();
    ui->yankeeStadiumPush->   hide();
    ui->fenwayParkPush->      hide();
    update();
}

/**********************************************************
 *
 * Method on_showDistRadio_clicked: Class MainWindow
 *_________________________________________________________
 * This slot makes appropriate changes to the UI after the
 *   button has been clicked.
 *   –returns nothing
 *_________________________________________________________
 * PRE-CONDITIONS
 *
 * POST-CONDITIONS
 *   Makes changes to the UI after the button has been
 *   clicked.
 **********************************************************/
void MainWindow::on_showDistRadio_clicked()
{
    update();
}

/**********************************************************
 *
 * Method on_showEdgeRadio_clicked: Class MainWindow
 *_________________________________________________________
 * This slot makes appropriate changes to the UI after the
 *   button has been clicked.
 *   –returns nothing
 *_________________________________________________________
 * PRE-CONDITIONS
 *
 * POST-CONDITIONS
 *   Makes changes to the UI after the button has been
 *   clicked.
 **********************************************************/
void MainWindow::on_showEdgeRadio_clicked()
{
    update();
}

/**********************************************************
 *
 * Method on_showStadRadio_clicked: Class MainWindow
 *_________________________________________________________
 * This slot makes appropriate changes to the UI after the
 *   button has been clicked.
 *   –returns nothing
 *_________________________________________________________
 * PRE-CONDITIONS
 *
 * POST-CONDITIONS
 *   Makes changes to the UI after the button has been
 *   clicked.
 **********************************************************/
void MainWindow::on_showStadRadio_clicked()
{
    update();
}

/**********************************************************
 *
 * Method on_verifyPush_clicked: Class MainWindow
 *_________________________________________________________
 * This slot makes appropriate changes to the UI after the
 *   button has been clicked.
 *   –returns nothing
 *_________________________________________________________
 * PRE-CONDITIONS
 *
 * POST-CONDITIONS
 *   Makes changes to the UI after the button has been
 *   clicked.
 **********************************************************/
void MainWindow::on_verifyPush_clicked()
{
    QString input;
    input = ui->passwordLineEdit->text();
    if (input == password)
    {
        ui->badPasswordLabel->hide();
        ui->passwordLineEdit->clear();
        ui->verifyPush->setDisabled(true);
        ui->adminFrame->setDisabled(false);
        ui->loggedInLabel->show();
        ui->adminFrame->setFocus();
    }
    else
    {
        ui->badPasswordLabel->show();
        ui->passwordLineEdit->selectAll();
        ui->passwordLineEdit->setFocus();
    }
}

/**********************************************************
 *
 * Method on_clearPasswordPush_clicked: Class MainWindow
 *_________________________________________________________
 * This slot makes appropriate changes to the UI after the
 *   button has been clicked.
 *   –returns nothing
 *_________________________________________________________
 * PRE-CONDITIONS
 *
 * POST-CONDITIONS
 *   Makes changes to the UI after the button has been
 *   clicked.
 **********************************************************/
void MainWindow::on_clearPasswordPush_clicked()
{
    ui->passwordLineEdit->clear();
    ui->passwordLineEdit->setFocus();
}

/**********************************************************
 *
 * Method on_beginCalcDistPush_clicked: Class MainWindow
 *_________________________________________________________
 * This slot makes appropriate changes to the UI after the
 *   button has been clicked. The calculate shortest
 *   distance between 2 stadiums tool is set to page 2.
 *   –returns nothing
 *_________________________________________________________
 * PRE-CONDITIONS
 *
 * POST-CONDITIONS
 *   Makes changes to the UI after the button has been
 *   clicked. The calculate shortest distance between 2
 *   stadiums tool is set to page 2.
 **********************************************************/
void MainWindow::on_beginCalcDistPush_clicked()
{
    ui->chooseStadLabel->setText("Choose stadium of origin from the map");
    ui->originPicLabel->setStyleSheet("background-color: transparent;");
    ui->originPicLabel->setText("Origin");
    ui->originNameLabel->clear();
    ui->destinPicLabel->setStyleSheet("background-color: transparent;");
    ui->destinPicLabel->setText("Destination");
    ui->destinNameLabel->clear();
    ui->clearOriginPush->hide();
    ui->clearDestinPush->hide();
    ui->calcShortPathPush->setDisabled(true);
    ui->calcDistStacked->setCurrentIndex(1);

    calcShortPath = true;
}

/**********************************************************
 *
 * Method on_calcShortPathCancelPush_clicked: Class MainWindow
 *_________________________________________________________
 * This slot makes appropriate changes to the UI after the
 *   button has been clicked.
 *   –returns nothing
 *_________________________________________________________
 * PRE-CONDITIONS
 *
 * POST-CONDITIONS
 *   Makes changes to the UI after the button has been
 *   clicked.
 **********************************************************/
void MainWindow::on_calcShortPathCancelPush_clicked()
{
    ui->calcDistStacked->setCurrentIndex(0);
}

/**********************************************************
 *
 * Method on_clearOriginPush_clicked: Class MainWindow
 *_________________________________________________________
 * This slot makes appropriate changes to the UI after the
 *   button has been clicked.
 *   –returns nothing
 *_________________________________________________________
 * PRE-CONDITIONS
 *
 * POST-CONDITIONS
 *   Makes changes to the UI after the button has been
 *   clicked.
 **********************************************************/
void MainWindow::on_clearOriginPush_clicked()
{
    ui->chooseStadLabel->setText("Choose stadium of origin from the map");
    ui->originPicLabel->setStyleSheet("background-color: transparent;");
    ui->originPicLabel->setText("Origin");
    ui->originNameLabel->clear();
    ui->clearOriginPush->hide();
    ui->calcShortPathPush->setDisabled(true);
    calcShortPath = true;
}

/**********************************************************
 *
 * Method on_clearDestinPush_clicked: Class MainWindow
 *_________________________________________________________
 * This slot makes appropriate changes to the UI after the
 *   button has been clicked.
 *   –returns nothing
 *_________________________________________________________
 * PRE-CONDITIONS
 *
 * POST-CONDITIONS
 *   Makes changes to the UI after the button has been
 *   clicked.
 **********************************************************/
void MainWindow::on_clearDestinPush_clicked()
{
    if (ui->originNameLabel->text() != "")
        ui->chooseStadLabel->setText("Choose destination stadium from the map");
    ui->destinPicLabel->setStyleSheet("background-color: transparent;");
    ui->destinPicLabel->setText("Destination");
    ui->destinNameLabel->clear();
    ui->clearDestinPush->hide();
    ui->calcShortPathPush->setDisabled(true);
    calcShortPath = true;
}

/**********************************************************
 *
 * Method on_passwordLineEdit_returnPressed: Class MainWindow
 *_________________________________________________________
 * This slot makes appropriate changes to the UI after the
 *   button has been clicked.
 *   –returns nothing
 *_________________________________________________________
 * PRE-CONDITIONS
 *
 * POST-CONDITIONS
 *   Makes changes to the UI after the button has been
 *   clicked.
 **********************************************************/
void MainWindow::on_passwordLineEdit_returnPressed()
{
    ui->verifyPush->click();
}

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
int MainWindow::countStadVisited(vector<string> path)  // CALC: the trip path
{
    int stadVisited;
    unordered_map<string, bool> visited;

    stadVisited = 0;
    for (unsigned i = 0; i < path.size(); i++)
    {
        if (visited[path[i]])
            continue;

        visited[path[i]] = true;
        stadVisited++;

        if (path.at(i) == "AT&T Park" || path.at(i) == "Dodger Stadium" ||
            path.at(i) == "Wrigley Field" || path.at(i) == "Citi Field" ||
            path.at(i) == "Nationals Park")
        {
            stadVisited++;
        }
    }

    return stadVisited;
}

/**********************************************************
 *
 * Method on_calcShortPathPush_clicked: Class MainWindow
 *_________________________________________________________
 * This method calculates the shortest path from a stadium
 *   to another by using the class attribute "stadiumGraph"
 *   which is of the UndirectedGraph class.
 *   –returns nothing
 *_________________________________________________________
 * PRE-CONDITIONS
 *
 * POST-CONDITIONS
 *   Uses the class attribute "stadiumGraph" to calculate
 *   the shortest path from one stadium to another.
 **********************************************************/
void MainWindow::on_calcShortPathPush_clicked()
{
    Stadium source;
    Stadium destin;
    size_t totalDist = 0;
    Path path;
    vector<string> pathNodes;

    for (unsigned i = 0; i < stadiums.size(); i++)
    {
        if (ui->originNameLabel->text().toStdString() == stadiums.at(i).lblTxt)
            source = stadiums.at(i);
        if (ui->destinNameLabel->text().toStdString() == stadiums.at(i).lblTxt)
            destin = stadiums.at(i);
    }

    currStadiums.clear();
    currStadiums.push_back(source);
    currStadiums.push_back(destin);
    selected = currStadiums;
    changeDestin(currStadiums);

    path = stadiumGraph.shortestPath(currStadiums[0].name, currStadiums[1].name);
    totalDist = path.cost;
    pathNodes = path.nodes;
    setCurrFlights(path);

    for (unsigned i = 0; i < selected.size(); i++)
    {
        if (selected.at(i).name == "RingCentral Coliseum")
        {
            for (unsigned j = 0; j < pathNodes.size(); j++)
            {
                if (pathNodes[j] == "AT&T Park")
                    pathNodes[j] = "RingCentral Coliseum";
            }
        }
        else if (selected.at(i).name == "Angel Stadium")
        {
            for (unsigned j = 0; j < pathNodes.size(); j++)
            {
                if (pathNodes[j] == "Dodger Stadium")
                    pathNodes[j] = "Angel Stadium";
            }
        }
        else if (selected.at(i).name == "US Cellular Field")
        {
            for (unsigned j = 0; j < pathNodes.size(); j++)
            {
                if (pathNodes[j] == "Wrigley Field")
                    pathNodes[j] = "US Cellular Field";
            }
        }
        else if (selected.at(i).name == "Yankee Stadium")
        {
            for (unsigned j = 0; j < pathNodes.size(); j++)
            {
                if (pathNodes[j] == "Citi Field")
                    pathNodes[j] = "Yankee Stadium";
            }
        }
        else if (selected.at(i).name == "Oriole Park at Camden Yards")
        {
            for (unsigned j = 0; j < pathNodes.size(); j++)
            {
                if (pathNodes[j] == "Nationals Park")
                    pathNodes[j] = "Oriole Park at Camden Yards";
            }
        }
    }

    updateShortPathTable(path);
    ui->totalShortDistLabel->setText
                      ("Total distance: " + QString::number(totalDist) + " mi");
    ui->calcDistStacked->setCurrentIndex(2);
    ui->showMLRadio->click();
    ui->showDistRadio->click();
    ui->showALRadio->setDisabled(true);
    ui->showNLRadio->setDisabled(true);
    ui->showStadRadio->setDisabled(true);
    ui->showGrassRadio->setDisabled(true);
    ui->showTurfRadio->setDisabled(true);
}

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
void MainWindow::updateShortPathTable(Path tripPath)  // CALC: path to display
{
    QTableWidget *table;
    QTableWidgetItem *newItem;
    QImage *stadPic;
    QHeaderView *headerH;
    Stadium currStad;

    table = ui->shortPathTableWidget;
    table->setColumnCount(3);
    table->setRowCount(tripPath.nodes.size() + 1);

    // set headers
    newItem = new QTableWidgetItem("Stadium\nvisited");
    newItem->setTextAlignment(Qt::AlignCenter);
    table->setItem(0, 1, newItem);

    newItem = new QTableWidgetItem("Distance\nfrom\nprevious");
    newItem->setTextAlignment(Qt::AlignCenter);
    table->setItem(0, 2, newItem);

    // set path
    currStad = stadiums.at(stadIndexes[tripPath.nodes[0]]);
    stadPic = new QImage(QString::fromStdString(currStad.picPath));
    newItem = new QTableWidgetItem;
    newItem->setData(Qt::DecorationRole,
                     QPixmap::fromImage(*stadPic).scaled(90, 65));
    table->setItem(1, 0, newItem);

    newItem = new QTableWidgetItem(QString::fromStdString(currStad.lblTxt));
    newItem->setTextAlignment(Qt::AlignCenter);
    table->setItem(1, 1, newItem);

    for (unsigned i = 0; i < tripPath.nodes.size() - 1; i++)
    {
        currStad = stadiums.at(stadIndexes[tripPath.nodes.at(i + 1)]);
        stadPic = new QImage(QString::fromStdString(currStad.picPath));
        newItem = new QTableWidgetItem;
        newItem->setData(Qt::DecorationRole,
                         QPixmap::fromImage(*stadPic).scaled(90, 65));
        table->setItem(i + 2, 0, newItem);

        newItem = new QTableWidgetItem(QString::fromStdString(currStad.lblTxt));
        newItem->setTextAlignment(Qt::AlignCenter);
        table->setItem(i + 2, 1, newItem);

        newItem = new QTableWidgetItem
                             (QString::number(currFlights.at(i).weight) + "mi");
        newItem->setTextAlignment(Qt::AlignCenter);
        table->setItem(i + 2, 2, newItem);
    }

    headerH = ui->shortPathTableWidget->horizontalHeader();
    headerH->setSectionResizeMode(QHeaderView::ResizeToContents);
    headerH->setSectionResizeMode(1, QHeaderView::Stretch);
    ui->shortPathTableWidget->verticalHeader()->setSectionResizeMode
                                             (QHeaderView::ResizeToContents);
}

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
void MainWindow::updateTripPathTable
                           (vector<string> flightPath)  // CALC: path to display
{
    QTableWidget *table;
    QTableWidgetItem *newItem;
    QImage *stadPic;
    QHeaderView *headerH;
    Stadium currStad;
    unsigned row;

    table = ui->showTripTableWidget;
    table->setColumnCount(3);
    table->setRowCount(0);
    row = 0;

    // set headers
    table->insertRow(row);
    newItem = new QTableWidgetItem("Stadium\nvisited");
    newItem->setTextAlignment(Qt::AlignCenter);
    table->setItem(0, 1, newItem);

    newItem = new QTableWidgetItem("Distance\nfrom\nprevious");
    newItem->setTextAlignment(Qt::AlignCenter);
    table->setItem(0, 2, newItem);

    // set path
    row++;
    table->insertRow(row);
    currStad = stadiums.at(stadIndexes[flightPath.at(0)]);
    stadPic = new QImage(QString::fromStdString(currStad.picPath));
    newItem = new QTableWidgetItem;
    newItem->setData(Qt::DecorationRole,
                     QPixmap::fromImage(*stadPic).scaled(90, 65));
    table->setItem(row, 0, newItem);

    newItem = new QTableWidgetItem(QString::fromStdString(currStad.lblTxt));
    newItem->setTextAlignment(Qt::AlignCenter);
    table->setItem(row, 1, newItem);

    if (currStad.name == "Angel Stadium")
    {
        for (unsigned i = 0; i < selected.size(); i++)
        {
            if (selected.at(i).name == "Dodger Stadium")
            {
                row++;
                table->insertRow(row);
                currStad = stadiums.at(stadIndexes["Dodger Stadium"]);
                stadPic = new QImage(QString::fromStdString(currStad.picPath));
                newItem = new QTableWidgetItem;
                newItem->setData(Qt::DecorationRole,
                                   QPixmap::fromImage(*stadPic).scaled(90, 65));
                table->setItem(row, 0, newItem);

                newItem = new QTableWidgetItem(QString::fromStdString
                                                             (currStad.lblTxt));
                newItem->setTextAlignment(Qt::AlignCenter);
                table->setItem(row, 1, newItem);

                newItem = new QTableWidgetItem("0mi");
                newItem->setTextAlignment(Qt::AlignCenter);
                table->setItem(row, 2, newItem);
                break;
            }
        }
    }
    else if (currStad.name == "Dodger Stadium")
    {
        for (unsigned i = 0; i < selected.size(); i++)
        {
            if (selected.at(i).name == "Angel Stadium")
            {
                row++;
                table->insertRow(row);
                currStad = stadiums.at(stadIndexes["Angel Stadium"]);
                stadPic = new QImage(QString::fromStdString(currStad.picPath));
                newItem = new QTableWidgetItem;
                newItem->setData(Qt::DecorationRole,
                                   QPixmap::fromImage(*stadPic).scaled(90, 65));
                table->setItem(row, 0, newItem);

                newItem = new QTableWidgetItem(QString::fromStdString
                                                             (currStad.lblTxt));
                newItem->setTextAlignment(Qt::AlignCenter);
                table->setItem(row, 1, newItem);

                newItem = new QTableWidgetItem("0mi");
                newItem->setTextAlignment(Qt::AlignCenter);
                table->setItem(row, 2, newItem);
                break;
            }
        }
    }
    else if (currStad.name == "RingCentral Coliseum")
    {
        for (unsigned i = 0; i < selected.size(); i++)
        {
            if (selected.at(i).name == "AT&T Park")
            {
                row++;
                table->insertRow(row);
                currStad = stadiums.at(stadIndexes["AT&T Park"]);
                stadPic = new QImage(QString::fromStdString(currStad.picPath));
                newItem = new QTableWidgetItem;
                newItem->setData(Qt::DecorationRole,
                                   QPixmap::fromImage(*stadPic).scaled(90, 65));
                table->setItem(row, 0, newItem);

                newItem = new QTableWidgetItem(QString::fromStdString
                                                             (currStad.lblTxt));
                newItem->setTextAlignment(Qt::AlignCenter);
                table->setItem(row, 1, newItem);

                newItem = new QTableWidgetItem("0mi");
                newItem->setTextAlignment(Qt::AlignCenter);
                table->setItem(row, 2, newItem);
                break;
            }
        }
    }
    else if (currStad.name == "AT&T Park")
    {
        for (unsigned i = 0; i < selected.size(); i++)
        {
            if (selected.at(i).name == "RingCentral Coliseum")
            {
                row++;
                table->insertRow(row);
                currStad = stadiums.at(stadIndexes["RingCentral Coliseum"]);
                stadPic = new QImage(QString::fromStdString(currStad.picPath));
                newItem = new QTableWidgetItem;
                newItem->setData(Qt::DecorationRole,
                                   QPixmap::fromImage(*stadPic).scaled(90, 65));
                table->setItem(row, 0, newItem);

                newItem = new QTableWidgetItem(QString::fromStdString
                                                             (currStad.lblTxt));
                newItem->setTextAlignment(Qt::AlignCenter);
                table->setItem(row, 1, newItem);

                newItem = new QTableWidgetItem("0mi");
                newItem->setTextAlignment(Qt::AlignCenter);
                table->setItem(row, 2, newItem);
                break;
            }
        }
    }
    else if (currStad.name == "US Cellular Field")
    {
        for (unsigned i = 0; i < selected.size(); i++)
        {
            if (selected.at(i).name == "Wrigley Field")
            {
                row++;
                table->insertRow(row);
                currStad = stadiums.at(stadIndexes["Wrigley Field"]);
                stadPic = new QImage(QString::fromStdString(currStad.picPath));
                newItem = new QTableWidgetItem;
                newItem->setData(Qt::DecorationRole,
                                   QPixmap::fromImage(*stadPic).scaled(90, 65));
                table->setItem(row, 0, newItem);

                newItem = new QTableWidgetItem(QString::fromStdString
                                                             (currStad.lblTxt));
                newItem->setTextAlignment(Qt::AlignCenter);
                table->setItem(row, 1, newItem);

                newItem = new QTableWidgetItem("0mi");
                newItem->setTextAlignment(Qt::AlignCenter);
                table->setItem(row, 2, newItem);
                break;
            }
        }
    }
    else if (currStad.name == "Wrigley Field")
    {
        for (unsigned i = 0; i < selected.size(); i++)
        {
            if (selected.at(i).name == "US Cellular Field")
            {
                row++;
                table->insertRow(row);
                currStad = stadiums.at(stadIndexes["US Cellular Field"]);
                stadPic = new QImage(QString::fromStdString(currStad.picPath));
                newItem = new QTableWidgetItem;
                newItem->setData(Qt::DecorationRole,
                                   QPixmap::fromImage(*stadPic).scaled(90, 65));
                table->setItem(row, 0, newItem);

                newItem = new QTableWidgetItem(QString::fromStdString
                                                             (currStad.lblTxt));
                newItem->setTextAlignment(Qt::AlignCenter);
                table->setItem(row, 1, newItem);

                newItem = new QTableWidgetItem("0mi");
                newItem->setTextAlignment(Qt::AlignCenter);
                table->setItem(row, 2, newItem);
                break;
            }
        }
    }
    else if (currStad.name == "Yankee Stadium")
    {
        for (unsigned i = 0; i < selected.size(); i++)
        {
            if (selected.at(i).name == "Citi Field")
            {
                row++;
                table->insertRow(row);
                currStad = stadiums.at(stadIndexes["Citi Field"]);
                stadPic = new QImage(QString::fromStdString(currStad.picPath));
                newItem = new QTableWidgetItem;
                newItem->setData(Qt::DecorationRole,
                                   QPixmap::fromImage(*stadPic).scaled(90, 65));
                table->setItem(row, 0, newItem);

                newItem = new QTableWidgetItem(QString::fromStdString
                                                             (currStad.lblTxt));
                newItem->setTextAlignment(Qt::AlignCenter);
                table->setItem(row, 1, newItem);

                newItem = new QTableWidgetItem("0mi");
                newItem->setTextAlignment(Qt::AlignCenter);
                table->setItem(row, 2, newItem);
                break;
            }
        }
    }
    else if (currStad.name == "Citi Field")
    {
        for (unsigned i = 0; i < selected.size(); i++)
        {
            if (selected.at(i).name == "Yankee Stadium")
            {
                row++;
                table->insertRow(row);
                currStad = stadiums.at(stadIndexes["Yankee Stadium"]);
                stadPic = new QImage(QString::fromStdString(currStad.picPath));
                newItem = new QTableWidgetItem;
                newItem->setData(Qt::DecorationRole,
                                   QPixmap::fromImage(*stadPic).scaled(90, 65));
                table->setItem(row, 0, newItem);

                newItem = new QTableWidgetItem(QString::fromStdString
                                                             (currStad.lblTxt));
                newItem->setTextAlignment(Qt::AlignCenter);
                table->setItem(row, 1, newItem);

                newItem = new QTableWidgetItem("0mi");
                newItem->setTextAlignment(Qt::AlignCenter);
                table->setItem(row, 2, newItem);
                break;
            }
        }
    }
    else if (currStad.name == "Oriole Park at Camden Yards")
    {
        for (unsigned i = 0; i < selected.size(); i++)
        {
            if (selected.at(i).name == "Nationals Park")
            {
                row++;
                table->insertRow(row);
                currStad = stadiums.at(stadIndexes["Nationals Park"]);
                stadPic = new QImage(QString::fromStdString(currStad.picPath));
                newItem = new QTableWidgetItem;
                newItem->setData(Qt::DecorationRole,
                                   QPixmap::fromImage(*stadPic).scaled(90, 65));
                table->setItem(row, 0, newItem);

                newItem = new QTableWidgetItem(QString::fromStdString
                                                             (currStad.lblTxt));
                newItem->setTextAlignment(Qt::AlignCenter);
                table->setItem(row, 1, newItem);

                newItem = new QTableWidgetItem("0mi");
                newItem->setTextAlignment(Qt::AlignCenter);
                table->setItem(row, 2, newItem);
                break;
            }
        }
    }
    else if (currStad.name == "Nationals Park")
    {
        for (unsigned i = 0; i < selected.size(); i++)
        {
            if (selected.at(i).name == "Oriole Park at Camden Yards")
            {
                row++;
                table->insertRow(row);
                currStad = stadiums.at(stadIndexes["Oriole Park at Camden Yards"]);
                stadPic = new QImage(QString::fromStdString(currStad.picPath));
                newItem = new QTableWidgetItem;
                newItem->setData(Qt::DecorationRole,
                                   QPixmap::fromImage(*stadPic).scaled(90, 65));
                table->setItem(row, 0, newItem);

                newItem = new QTableWidgetItem(QString::fromStdString
                                                             (currStad.lblTxt));
                newItem->setTextAlignment(Qt::AlignCenter);
                table->setItem(row, 1, newItem);

                newItem = new QTableWidgetItem("0mi");
                newItem->setTextAlignment(Qt::AlignCenter);
                table->setItem(row, 2, newItem);
                break;
            }
        }
    }

    for (unsigned i = 0; i < flightPath.size() - 1; i++)
    {
        row++;
        table->insertRow(row);
        currStad = stadiums.at(stadIndexes[flightPath.at(i + 1)]);
        stadPic = new QImage(QString::fromStdString(currStad.picPath));
        newItem = new QTableWidgetItem;
        newItem->setData(Qt::DecorationRole,
                         QPixmap::fromImage(*stadPic).scaled(90, 65));
        table->setItem(row, 0, newItem);

        newItem = new QTableWidgetItem(QString::fromStdString(currStad.lblTxt));
        newItem->setTextAlignment(Qt::AlignCenter);
        table->setItem(row, 1, newItem);

        newItem = new QTableWidgetItem
                             (QString::number(currFlights.at(i).weight) + "mi");
        newItem->setTextAlignment(Qt::AlignCenter);
        table->setItem(row, 2, newItem);

        if (currStad.name == "Angel Stadium")
        {
            for (unsigned i = 0; i < selected.size(); i++)
            {
                if (selected.at(i).name == "Dodger Stadium")
                {
                    row++;
                    table->insertRow(row);
                    currStad = stadiums.at(stadIndexes["Dodger Stadium"]);
                    stadPic = new QImage(QString::fromStdString
                                                            (currStad.picPath));
                    newItem = new QTableWidgetItem;
                    newItem->setData(Qt::DecorationRole,
                                   QPixmap::fromImage(*stadPic).scaled(90, 65));
                    table->setItem(row, 0, newItem);

                    newItem = new QTableWidgetItem(QString::fromStdString
                                                             (currStad.lblTxt));
                    newItem->setTextAlignment(Qt::AlignCenter);
                    table->setItem(row, 1, newItem);

                    newItem = new QTableWidgetItem("0mi");
                    newItem->setTextAlignment(Qt::AlignCenter);
                    table->setItem(row, 2, newItem);
                    break;
                }
            }
        }
        else if (currStad.name == "Dodger Stadium")
        {
            for (unsigned i = 0; i < selected.size(); i++)
            {
                if (selected.at(i).name == "Angel Stadium")
                {
                    row++;
                    table->insertRow(row);
                    currStad = stadiums.at(stadIndexes["Angel Stadium"]);
                    stadPic = new QImage(QString::fromStdString
                                                            (currStad.picPath));
                    newItem = new QTableWidgetItem;
                    newItem->setData(Qt::DecorationRole,
                                   QPixmap::fromImage(*stadPic).scaled(90, 65));
                    table->setItem(row, 0, newItem);

                    newItem = new QTableWidgetItem(QString::fromStdString
                                                             (currStad.lblTxt));
                    newItem->setTextAlignment(Qt::AlignCenter);
                    table->setItem(row, 1, newItem);

                    newItem = new QTableWidgetItem("0mi");
                    newItem->setTextAlignment(Qt::AlignCenter);
                    table->setItem(row, 2, newItem);
                    break;
                }
            }
        }
        else if (currStad.name == "RingCentral Coliseum")
        {
            for (unsigned i = 0; i < selected.size(); i++)
            {
                if (selected.at(i).name == "AT&T Park")
                {
                    row++;
                    table->insertRow(row);
                    currStad = stadiums.at(stadIndexes["AT&T Park"]);
                    stadPic = new QImage(QString::fromStdString
                                                            (currStad.picPath));
                    newItem = new QTableWidgetItem;
                    newItem->setData(Qt::DecorationRole,
                                   QPixmap::fromImage(*stadPic).scaled(90, 65));
                    table->setItem(row, 0, newItem);

                    newItem = new QTableWidgetItem(QString::fromStdString
                                                             (currStad.lblTxt));
                    newItem->setTextAlignment(Qt::AlignCenter);
                    table->setItem(row, 1, newItem);

                    newItem = new QTableWidgetItem("0mi");
                    newItem->setTextAlignment(Qt::AlignCenter);
                    table->setItem(row, 2, newItem);
                    break;
                }
            }
        }
        else if (currStad.name == "AT&T Park")
        {
            for (unsigned i = 0; i < selected.size(); i++)
            {
                if (selected.at(i).name == "RingCentral Coliseum")
                {
                    row++;
                    table->insertRow(row);
                    currStad = stadiums.at(stadIndexes["RingCentral Coliseum"]);
                    stadPic = new QImage(QString::fromStdString
                                                            (currStad.picPath));
                    newItem = new QTableWidgetItem;
                    newItem->setData(Qt::DecorationRole,
                                   QPixmap::fromImage(*stadPic).scaled(90, 65));
                    table->setItem(row, 0, newItem);

                    newItem = new QTableWidgetItem(QString::fromStdString
                                                             (currStad.lblTxt));
                    newItem->setTextAlignment(Qt::AlignCenter);
                    table->setItem(row, 1, newItem);

                    newItem = new QTableWidgetItem("0mi");
                    newItem->setTextAlignment(Qt::AlignCenter);
                    table->setItem(row, 2, newItem);
                    break;
                }
            }
        }
        else if (currStad.name == "US Cellular Field")
        {
            for (unsigned i = 0; i < selected.size(); i++)
            {
                if (selected.at(i).name == "Wrigley Field")
                {
                    row++;
                    table->insertRow(row);
                    currStad = stadiums.at(stadIndexes["Wrigley Field"]);
                    stadPic = new QImage(QString::fromStdString
                                                            (currStad.picPath));
                    newItem = new QTableWidgetItem;
                    newItem->setData(Qt::DecorationRole,
                                   QPixmap::fromImage(*stadPic).scaled(90, 65));
                    table->setItem(row, 0, newItem);

                    newItem = new QTableWidgetItem(QString::fromStdString
                                                             (currStad.lblTxt));
                    newItem->setTextAlignment(Qt::AlignCenter);
                    table->setItem(row, 1, newItem);

                    newItem = new QTableWidgetItem("0mi");
                    newItem->setTextAlignment(Qt::AlignCenter);
                    table->setItem(row, 2, newItem);
                    break;
                }
            }
        }
        else if (currStad.name == "Wrigley Field")
        {
            for (unsigned i = 0; i < selected.size(); i++)
            {
                if (selected.at(i).name == "US Cellular Field")
                {
                    row++;
                    table->insertRow(row);
                    currStad = stadiums.at(stadIndexes["US Cellular Field"]);
                    stadPic = new QImage(QString::fromStdString
                                                            (currStad.picPath));
                    newItem = new QTableWidgetItem;
                    newItem->setData(Qt::DecorationRole,
                                   QPixmap::fromImage(*stadPic).scaled(90, 65));
                    table->setItem(row, 0, newItem);

                    newItem = new QTableWidgetItem(QString::fromStdString
                                                             (currStad.lblTxt));
                    newItem->setTextAlignment(Qt::AlignCenter);
                    table->setItem(row, 1, newItem);

                    newItem = new QTableWidgetItem("0mi");
                    newItem->setTextAlignment(Qt::AlignCenter);
                    table->setItem(row, 2, newItem);
                    break;
                }
            }
        }
        else if (currStad.name == "Yankee Stadium")
        {
            for (unsigned i = 0; i < selected.size(); i++)
            {
                if (selected.at(i).name == "Citi Field")
                {
                    row++;
                    table->insertRow(row);
                    currStad = stadiums.at(stadIndexes["Citi Field"]);
                    stadPic = new QImage(QString::fromStdString
                                                            (currStad.picPath));
                    newItem = new QTableWidgetItem;
                    newItem->setData(Qt::DecorationRole,
                                   QPixmap::fromImage(*stadPic).scaled(90, 65));
                    table->setItem(row, 0, newItem);

                    newItem = new QTableWidgetItem(QString::fromStdString
                                                             (currStad.lblTxt));
                    newItem->setTextAlignment(Qt::AlignCenter);
                    table->setItem(row, 1, newItem);

                    newItem = new QTableWidgetItem("0mi");
                    newItem->setTextAlignment(Qt::AlignCenter);
                    table->setItem(row, 2, newItem);
                    break;
                }
            }
        }
        else if (currStad.name == "Citi Field")
        {
            for (unsigned i = 0; i < selected.size(); i++)
            {
                if (selected.at(i).name == "Yankee Stadium")
                {
                    row++;
                    table->insertRow(row);
                    currStad = stadiums.at(stadIndexes["Yankee Stadium"]);
                    stadPic = new QImage(QString::fromStdString
                                                            (currStad.picPath));
                    newItem = new QTableWidgetItem;
                    newItem->setData(Qt::DecorationRole,
                                   QPixmap::fromImage(*stadPic).scaled(90, 65));
                    table->setItem(row, 0, newItem);

                    newItem = new QTableWidgetItem(QString::fromStdString
                                                             (currStad.lblTxt));
                    newItem->setTextAlignment(Qt::AlignCenter);
                    table->setItem(row, 1, newItem);

                    newItem = new QTableWidgetItem("0mi");
                    newItem->setTextAlignment(Qt::AlignCenter);
                    table->setItem(row, 2, newItem);
                    break;
                }
            }
        }
        else if (currStad.name == "Oriole Park at Camden Yards")
        {
            for (unsigned i = 0; i < selected.size(); i++)
            {
                if (selected.at(i).name == "Nationals Park")
                {
                    row++;
                    table->insertRow(row);
                    currStad = stadiums.at(stadIndexes["Nationals Park"]);
                    stadPic = new QImage(QString::fromStdString
                                                            (currStad.picPath));
                    newItem = new QTableWidgetItem;
                    newItem->setData(Qt::DecorationRole,
                                   QPixmap::fromImage(*stadPic).scaled(90, 65));
                    table->setItem(row, 0, newItem);

                    newItem = new QTableWidgetItem(QString::fromStdString
                                                             (currStad.lblTxt));
                    newItem->setTextAlignment(Qt::AlignCenter);
                    table->setItem(row, 1, newItem);

                    newItem = new QTableWidgetItem("0mi");
                    newItem->setTextAlignment(Qt::AlignCenter);
                    table->setItem(row, 2, newItem);
                    break;
                }
            }
        }
        else if (currStad.name == "Nationals Park")
        {
            for (unsigned i = 0; i < selected.size(); i++)
            {
                if (selected.at(i).name == "Oriole Park at Camden Yards")
                {
                    row++;
                    table->insertRow(row);
                    currStad = stadiums.at(stadIndexes["Oriole Park at Camden Yards"]);
                    stadPic = new QImage(QString::fromStdString
                                                            (currStad.picPath));
                    newItem = new QTableWidgetItem;
                    newItem->setData(Qt::DecorationRole,
                                   QPixmap::fromImage(*stadPic).scaled(90, 65));
                    table->setItem(row, 0, newItem);

                    newItem = new QTableWidgetItem(QString::fromStdString
                                                             (currStad.lblTxt));
                    newItem->setTextAlignment(Qt::AlignCenter);
                    table->setItem(row, 1, newItem);

                    newItem = new QTableWidgetItem("0mi");
                    newItem->setTextAlignment(Qt::AlignCenter);
                    table->setItem(row, 2, newItem);
                    break;
                }
            }
        }
    }

    headerH = ui->showTripTableWidget->horizontalHeader();
    headerH->setSectionResizeMode(QHeaderView::ResizeToContents);
    headerH->setSectionResizeMode(1, QHeaderView::Stretch);
    ui->showTripTableWidget->verticalHeader()->setSectionResizeMode
                                             (QHeaderView::ResizeToContents);
}

/**********************************************************
 *
 * Method on_shortPathResetPush_clicked: Class MainWindow
 *_________________________________________________________
 * This slot makes appropriate changes to the UI after the
 *   button has been clicked.
 *   –returns nothing
 *_________________________________________________________
 * PRE-CONDITIONS
 *
 * POST-CONDITIONS
 *   Makes changes to the UI after the button has been
 *   clicked.
 **********************************************************/
void MainWindow::on_shortPathResetPush_clicked()
{
    currStadiums = stadiums;
    currFlights = flights;
    ui->calcDistStacked->setCurrentIndex(0);
    ui->showMLRadio->click();
    ui->showALRadio->setEnabled(true);
    ui->showNLRadio->setEnabled(true);
    ui->showStadRadio->setEnabled(true);
    ui->showGrassRadio->setEnabled(true);
    ui->showTurfRadio->setEnabled(true);
    ui->showStadRadio->click();
}

/**********************************************************
 *
 * Method on_planYourOwnPush_clicked: Class MainWindow
 *_________________________________________________________
 * This slot makes appropriate changes to the UI after the
 *   button has been clicked.
 *   –returns nothing
 *_________________________________________________________
 * PRE-CONDITIONS
 *
 * POST-CONDITIONS
 *   Makes changes to the UI after the button has been
 *   clicked.
 **********************************************************/
void MainWindow::on_planYourOwnPush_clicked()
{
    ui->calcDistStacked->hide();
    ui->tripPlannerStacked->setCurrentIndex(1);
    ui->deleteStadPush->setDisabled(true);
    selected.clear();
    updateChooseStadsTable();
    ui->chooseStadsLabel->show();
    ui->goLabel->setDisabled(true);
    calcTrip = true;
}

/**********************************************************
 *
 * Method on_cancelGoLabel_clicked: Class MainWindow
 *_________________________________________________________
 * This slot makes appropriate changes to the UI after the
 *   button has been clicked.
 *   –returns nothing
 *_________________________________________________________
 * PRE-CONDITIONS
 *
 * POST-CONDITIONS
 *   Makes changes to the UI after the button has been
 *   clicked.
 **********************************************************/
void MainWindow::on_cancelGoLabel_clicked()
{
    calcTrip = false;
    currStadiums = stadiums;
    currFlights = flights;
    wishList.clear();
    updateAddSouvTable();
    ui->showMLRadio->click();
    ui->showALRadio->setEnabled(true);
    ui->showNLRadio->setEnabled(true);
    ui->showStadRadio->setEnabled(true);
    ui->showGrassRadio->setEnabled(true);
    ui->showTurfRadio->setEnabled(true);
    ui->showStadRadio->click();
    ui->showTripTableWidget->clear();
    ui->souvListTableWidget->setRowCount(0);
    ui->calcDistStacked->show();
    ui->tripPlannerStacked->setCurrentIndex(0);
    ui->calcDistStacked->setCurrentIndex(0);
    ui->logInFrame->setEnabled(true);
    ui->addSouvFrame->hide();
    ui->startFromFirstRadio->click();
}

/**********************************************************
 *
 * Method on_goLabel_clicked: Class MainWindow
 *_________________________________________________________
 * This slot makes appropriate changes to the UI after the
 *   button has been clicked. The list of stadiums selected
 *   to visit is stored in currStadiums and the shortest
 *   path connecting all of those stadiums is calculated
 *   using the class attribute "stadiumGraph" and currFlights
 *   is set to include only the flights present in the
 *   path.
 *   –returns nothing
 *_________________________________________________________
 * PRE-CONDITIONS
 *
 * POST-CONDITIONS
 *   Makes changes to the UI after the button has been
 *   clicked. The shortest path to visit all of the
 *   selected stadiums is calculated and the flights are
 *   stored in currFlights.
 **********************************************************/
void MainWindow::on_goLabel_clicked()
{
    int totalDist;
    Path bestPath;
    vector<string> path;
    vector<string> altPath;
    string start;

    auto begin = chrono::steady_clock::now();

    currStadiums = selected;
    changeDestin(currStadiums);

    for (int i = 0; i < currStadiums.size(); i++)
    {
        path.push_back(currStadiums[i].name);
    }

    bestPath = stadiumGraph.shortestTripAStar(path);
    totalDist = bestPath.cost;

    setCurrFlights(bestPath);
    ui->numStadValLabel->setText(QString::number(countStadVisited(bestPath.nodes)));
    ui->tripTotalDistValLabel->setText(QString::number(totalDist) + " mi");

    for (unsigned i = 0; i < selected.size(); i++)
    {
        if (selected.at(i).name == "RingCentral Coliseum")
        {
            for (unsigned j = 0; j < bestPath.nodes.size(); j++)
            {
                if (bestPath.nodes.at(j) == "AT&T Park")
                {
                    bestPath.nodes.at(j) = "RingCentral Coliseum";
                }
            }
        }
        else if (selected.at(i).name == "Angel Stadium")
        {
            for (unsigned j = 0; j < bestPath.nodes.size(); j++)
            {
                if (bestPath.nodes.at(j) == "Dodger Stadium")
                    bestPath.nodes.at(j) = "Angel Stadium";
            }
        }
        else if (selected.at(i).name == "US Cellular Field")
        {
            for (unsigned j = 0; j < bestPath.nodes.size(); j++)
            {
                if (bestPath.nodes.at(j) == "Wrigley Field")
                    bestPath.nodes.at(j) = "US Cellular Field";
            }
        }
        else if (selected.at(i).name == "Yankee Stadium")
        {
            for (unsigned j = 0; j < bestPath.nodes.size(); j++)
            {
                if (bestPath.nodes.at(j) == "Citi Field")
                    bestPath.nodes.at(j) = "Yankee Stadium";
            }
        }
        else if (selected.at(i).name == "Oriole Park at Camden Yards")
        {
            for (unsigned j = 0; j < bestPath.nodes.size(); j++)
            {
                if (bestPath.nodes.at(j) == "Nationals Park")
                    bestPath.nodes.at(j) = "Oriole Park at Camden Yards";
            }
        }
    }

    updateTripPathTable(bestPath.nodes);
    ui->tripPlannerStacked->setCurrentIndex(2);
    ui->showMLRadio->click();
    ui->showDistRadio->click();
    ui->showALRadio->setDisabled(true);
    ui->showNLRadio->setDisabled(true);
    ui->showGrassRadio->setDisabled(true);
    ui->showTurfRadio->setDisabled(true);
    ui->showStadRadio->setDisabled(true);
    ui->logInFrame->setDisabled(true);
    ui->adminLogOutPush->click();
    calcTrip = false;
    MLTrip = false;

    auto end = chrono::steady_clock::now();
    auto elapsed = chrono::duration_cast<chrono::milliseconds>(end - begin);
    cout << "elapsed time: " << elapsed.count() << " ms" << endl;
}

/**********************************************************
 *
 * Method on_stadToVisitTableWidget_cellClicked: Class MainWindow
 *_________________________________________________________
 * This slot makes appropriate changes to the UI after the
 *   button has been clicked.
 *   –returns nothing
 *_________________________________________________________
 * PRE-CONDITIONS
 *   row: the row of the cell clicked
 *
 * POST-CONDITIONS
 *   Makes changes to the UI after the button has been
 *   clicked.
 **********************************************************/
void MainWindow::on_stadToVisitTableWidget_cellClicked(int row, int /*column*/)
{
    activeRow = row;
    ui->deleteStadPush->setEnabled(true);
    ui->moveToFirstPush->setEnabled(true);
}

/**********************************************************
 *
 * Method on_deleteStadPush_clicked: Class MainWindow
 *_________________________________________________________
 * This slot makes appropriate changes to the UI after the
 *   button has been clicked. It deletes the selected
 *   stadiums from the list of stadiums to visit.
 *   –returns nothing
 *_________________________________________________________
 * PRE-CONDITIONS
 *
 * POST-CONDITIONS
 *   Makes changes to the UI after the button has been
 *   clicked. Deletes the selected stadium from the list of
 *   stadiums to visit.
 **********************************************************/
void MainWindow::on_deleteStadPush_clicked()
{
    QString stadName;

    stadName = ui->stadToVisitTableWidget->item(activeRow, 1)->text();
    for (unsigned i = 0; i < selected.size(); i++)
    {
        if (selected.at(i).lblTxt == stadName.toStdString())
        {
            selected.erase(selected.begin() + i);
            updateChooseStadsTable();
            ui->deleteStadPush->setDisabled(true);

            if (selected.size() == 0)
            {
                ui->goLabel->setDisabled(true);
                ui->chooseStadsLabel->show();
            }

            return;
        }
    }
}

/**********************************************************
 *
 * Method on_tripPlanResetPush_clicked: Class MainWindow
 *_________________________________________________________
 * This slot makes appropriate changes to the UI after the
 *   button has been clicked.
 *   –returns nothing
 *_________________________________________________________
 * PRE-CONDITIONS
 *   row: the row of the cell clicked
 *
 * POST-CONDITIONS
 *   Makes changes to the UI after the button has been
 *   clicked.
 **********************************************************/
void MainWindow::on_tripPlanResetPush_clicked()
{
    on_cancelGoLabel_clicked();
}

/**********************************************************
 *
 * Method on_visitMLPush_clicked: Class MainWindow
 *_________________________________________________________
 * This slot makes appropriate changes to the UI after the
 *   button has been clicked. It populates the stadiums to
 *   visit table with all of the stadiums.
 *   –returns nothing
 *_________________________________________________________
 * PRE-CONDITIONS
 *
 * POST-CONDITIONS
 *   Makes changes to the UI after the button has been
 *   clicked. Populates the stadiums to visit table with
 *   all of the stadiums.
 **********************************************************/
void MainWindow::on_visitMLPush_clicked()
{
    ui->calcDistStacked->hide();
    ui->tripPlannerStacked->setCurrentIndex(1);
    ui->deleteStadPush->setDisabled(true);
    selected = stadiums;

    for (unsigned i = 0; i < selected.size(); i++)
    {
        if (selected.at(i).name == "Dodger Stadium")
        {
            selected.insert(selected.begin(), selected.at(i));
            selected.erase(selected.begin() + i + 1);
            break;
        }
    }

    updateChooseStadsTable();
    ui->chooseStadsLabel->hide();
    ui->goLabel->setEnabled(true);
    calcTrip = true;
    MLTrip = true;
}

/**********************************************************
 *
 * Method on_visitALPush_clicked: Class MainWindow
 *_________________________________________________________
 * This slot makes appropriate changes to the UI after the
 *   button has been clicked. It populates the stadiums to
 *   visit table with all of the American League stadium.
 *   –returns nothing
 *_________________________________________________________
 * PRE-CONDITIONS
 *
 * POST-CONDITIONS
 *   Makes changes to the UI after the button has been
 *   clicked. Populates the stadiums to visit table with
 *   all of the American League stadiums.
 **********************************************************/
void MainWindow::on_visitALPush_clicked()
{
    ui->calcDistStacked->hide();
    ui->tripPlannerStacked->setCurrentIndex(1);
    ui->deleteStadPush->setDisabled(true);
    selected.clear();

    for (unsigned i = 0; i < stadiums.size(); i++)
    {
        if (stadiums.at(i).league.substr(0,2) == "AL")
            selected.push_back(stadiums.at(i));
    }

    for (unsigned i = 0; i < selected.size(); i++)
    {
        if (selected.at(i).name == "Angel Stadium")
        {
            selected.insert(selected.begin(), selected.at(i));
            selected.erase(selected.begin() + i + 1);
            break;
        }
    }

    updateChooseStadsTable();
    ui->chooseStadsLabel->hide();
    ui->goLabel->setEnabled(true);
    calcTrip = true;
    MLTrip = false;
}

/**********************************************************
 *
 * Method on_visitNLPush_clicked: Class MainWindow
 *_________________________________________________________
 * This slot makes appropriate changes to the UI after the
 *   button has been clicked. It populates the stadiums to
 *   visit table with all of the National League stadium.
 *   –returns nothing
 *_________________________________________________________
 * PRE-CONDITIONS
 *
 * POST-CONDITIONS
 *   Makes changes to the UI after the button has been
 *   clicked. Populates the stadiums to visit table with
 *   all of the National League stadiums.
 **********************************************************/
void MainWindow::on_visitNLPush_clicked()
{
    ui->calcDistStacked->hide();
    ui->tripPlannerStacked->setCurrentIndex(1);
    ui->deleteStadPush->setDisabled(true);
    selected.clear();

    for (unsigned i = 0; i < stadiums.size(); i++)
    {
        if (stadiums.at(i).league.substr(0,2) == "NL")
            selected.push_back(stadiums.at(i));
    }

    for (unsigned i = 0; i < selected.size(); i++)
    {
        if (selected.at(i).name == "Dodger Stadium")
        {
            selected.insert(selected.begin(), selected.at(i));
            selected.erase(selected.begin() + i + 1);
            break;
        }
    }

    updateChooseStadsTable();
    ui->chooseStadsLabel->hide();
    ui->goLabel->setEnabled(true);
    calcTrip = true;
    MLTrip = false;
}

/**********************************************************
 *
 * Method on_showTripTableWidget_cellClicked: Class MainWindow
 *_________________________________________________________
 * This slot makes appropriate changes to the UI after the
 *   button has been clicked. It records the row of the
 *   cell clicked in the show trip path table in the trip
 *   planner.
 *   –returns nothing
 *_________________________________________________________
 * PRE-CONDITIONS
 *   row: the row of the cell clicked
 *
 * POST-CONDITIONS
 *   Makes changes to the UI after the button has been
 *   clicked. It records teh row of the cell clicked in the
 *   show trip path table in the trip planner.
 **********************************************************/
void MainWindow::on_showTripTableWidget_cellClicked(int row, int /*column*/)
{
    Stadium currStad;
    Souvenir souv;
    QString lbl;

    activeRow = row;
    lbl = ui->showTripTableWidget->item(activeRow, 1)->text();

    for (unsigned i = 0; i < stadiums.size(); i++)
    {
        if (stadiums.at(i).lblTxt == lbl.toStdString())
        {
            currStad = stadiums.at(i);
            break;
        }
    }

    ui->addSouvFromLabel->setText
               ("Add souvenirs from\n" + QString::fromStdString(currStad.name));
    ui->addSouvComboBox->blockSignals(true);
    ui->addSouvComboBox->clear();

    for (unsigned i = 0; i < currStad.souvenirs.size(); i++)
    {
        souv = currStad.souvenirs.at(i);
        ui->addSouvComboBox->addItem(QString::fromStdString(souv.name) + "  $" +
                                     QString::number(souv.price, 'f', 2));
        ui->addSouvComboBox->blockSignals(false);
    }

    ui->addSouvQtySpin->setValue(0);
    ui->souvAddedLabel->hide();
    ui->addSouvFrame->show();
}

/**********************************************************
 *
 * Method on_addSouvClosePush_clicked: Class MainWindow
 *_________________________________________________________
 * This slot makes appropriate changes to the UI after the
 *   button has been clicked.
 *   –returns nothing
 *_________________________________________________________
 * PRE-CONDITIONS
 *
 * POST-CONDITIONS
 *   Makes changes to the UI after the button has been
 *   clicked.
 **********************************************************/
void MainWindow::on_addSouvClosePush_clicked()
{
    ui->addSouvFrame->hide();
}

/**********************************************************
 *
 * Method on_addSouvPush_clicked: Class MainWindow
 *_________________________________________________________
 * This slot makes appropriate changes to the UI after the
 *   button has been clicked.
 *   –returns nothing
 *_________________________________________________________
 * PRE-CONDITIONS
 *
 * POST-CONDITIONS
 *   Makes changes to the UI after the button has been
 *   clicked.
 **********************************************************/
void MainWindow::on_addSouvPush_clicked()
{
    Stadium *currStad;
    Souvenir *currSouv;
    QString lbl;
    bool exists;

    lbl = ui->showTripTableWidget->item(activeRow, 1)->text();
    currStad = nullptr;
    currSouv = nullptr;
    exists = false;

    for (unsigned i = 0; i < wishList.size(); i++)
    {
        if (wishList.at(i).lblTxt == lbl.toStdString())
        {
            currStad = &wishList.at(i);
            exists = true;
            break;
        }
    }

    if (!exists)
    {
        for (unsigned i = 0; i < stadiums.size(); i++)
        {
            if (stadiums.at(i).lblTxt == lbl.toStdString())
            {
                wishList.push_back(stadiums.at(i));
                currStad = &wishList.at(wishList.size() - 1);
                break;
            }
        }
    }

    if (currStad)
    {
        currSouv = &currStad->souvenirs.at(ui->addSouvComboBox->currentIndex());
        currSouv->addQuantity(ui->addSouvQtySpin->value());
        ui->souvAddedLabel->setText(QString::fromStdString(currSouv->name) + " added!");
        ui->souvAddedLabel->show();
    }
    updateAddSouvTable();
}

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
void MainWindow::updateAddSouvTable()
{
    QTableWidget *table;
    QTableWidgetItem *newItem;
    Souvenir currSouv;
    double grandTotal;
    int numSouv;
    int row;

    table = ui->souvListTableWidget;
    table->clear();
    table->setRowCount(0);
    table->setColumnCount(4);
    grandTotal = 0;
    numSouv = 0;
    row = 0;

    // set headers
    table->insertRow(row);
    newItem = new QTableWidgetItem("Stadium");
    newItem->setTextAlignment(Qt::AlignCenter);
    table->setItem(row, 0, newItem);

    newItem = new QTableWidgetItem("Souvenir");
    newItem->setTextAlignment(Qt::AlignCenter);
    table->setItem(row, 1, newItem);

    newItem = new QTableWidgetItem("Quantity");
    newItem->setTextAlignment(Qt::AlignCenter);
    table->setItem(row, 2, newItem);

    newItem = new QTableWidgetItem("Total Price");
    newItem->setTextAlignment(Qt::AlignCenter);
    table->setItem(row, 3, newItem);

    for (unsigned i = 0; i < wishList.size(); i++)
    {
        for (unsigned j = 0; j < wishList.at(i).souvenirs.size(); j++)
        {
            currSouv = wishList.at(i).souvenirs.at(j);
            if (currSouv.quantity > 0)
            {
                row++;
                table->insertRow(row);
                newItem = new QTableWidgetItem(QString::fromStdString(wishList.at(i).lblTxt));
                newItem->setTextAlignment(Qt::AlignCenter);
                table->setItem(row, 0, newItem);

                newItem = new QTableWidgetItem(QString::fromStdString(currSouv.name));
                newItem->setTextAlignment(Qt::AlignCenter);
                table->setItem(row, 1, newItem);

                newItem = new QTableWidgetItem(QString::number(currSouv.quantity));
                newItem->setTextAlignment(Qt::AlignCenter);
                table->setItem(row, 2, newItem);

                newItem = new QTableWidgetItem("$" + QString::number(currSouv.total, 'f', 2));
                newItem->setTextAlignment(Qt::AlignCenter);
                table->setItem(row, 3, newItem);

                grandTotal += currSouv.total;
                numSouv += currSouv.quantity;
            }
        }
    }

    if (ui->souvListTableWidget->rowCount() <= 1)
    {
        ui->souvListTableWidget->setRowCount(0);
        ui->clickToAddLabel->show();
    }
    else
    {
        ui->clickToAddLabel->hide();
    }

    ui->souvListTableWidget->horizontalHeader()->setSectionResizeMode
                                                (QHeaderView::ResizeToContents);
    ui->souvListTableWidget->verticalHeader()->setSectionResizeMode
                                                (QHeaderView::ResizeToContents);
    ui->numSouvValLabel->setText(QString::number(numSouv));
    ui->totalSouvCostValLabel->setText("$" + QString::number(grandTotal, 'f', 2));
}

/**********************************************************
 *
 * Method on_addSouvPush_clicked: Class MainWindow
 *_________________________________________________________
 * This slot makes appropriate changes to the UI after the
 *   button has been clicked. It sets the quantity of the
 *   souvenir to be bought by the user.
 *   –returns nothing
 *_________________________________________________________
 * PRE-CONDITIONS
 *   arg1: value of the spin box denoting the quantity of
 *         the souvenir to be bought
 *
 * POST-CONDITIONS
 *   Makes changes to the UI after the button has been
 *   clicked. It sets the quantity of the souvenir to be
 *   bought by the user.
 **********************************************************/
void MainWindow::on_addSouvQtySpin_valueChanged(int arg1)  // IN - value of the
                                                           //      spin box
                                                           //      denoting the
                                                           //      quantity of
                                                           //      the souvenir
{
    Stadium currStad;
    Souvenir souv;
    QString lbl;
    double totalPrice;

    lbl = ui->showTripTableWidget->item(activeRow, 1)->text();

    for (unsigned i = 0; i < stadiums.size(); i++)
    {
        if (stadiums.at(i).lblTxt == lbl.toStdString())
        {
            currStad = stadiums.at(i);
            break;
        }
    }

    souv = currStad.souvenirs.at(ui->addSouvComboBox->currentIndex());
    totalPrice = arg1 * souv.price;
    ui->addSouvPriceLabel->setText("$" + QString::number(totalPrice, 'f', 2));
}

/**********************************************************
 *
 * Method on_modifyStadPush_clicked: Class MainWindow
 *_________________________________________________________
 * This slot makes appropriate changes to the UI after the
 *   button has been clicked.
 *   –returns nothing
 *_________________________________________________________
 * PRE-CONDITIONS
 *
 * POST-CONDITIONS
 *   Makes changes to the UI after the button has been
 *   clicked.
 **********************************************************/
void MainWindow::on_modifyStadPush_clicked()
{
    ui->selectStadModifyCombo->blockSignals(true);
    ui->selectStadModifyCombo->clear();
    ui->selectStadModifyCombo->addItem("None");
    ui->selectStadModifyCombo->blockSignals(false);
    for (unsigned i = 0; i < stadiums.size(); i++)
    {
        ui->selectStadModifyCombo->addItem(QString::fromStdString(stadiums.at(i).name));
    }
    ui->selectStadModifyCombo->setCurrentIndex(0);
    ui->stadModifiedLabel->hide();
    on_selectStadModifyCombo_currentIndexChanged(0);
    ui->adminStacked->setCurrentIndex(1);
}

/**********************************************************
 *
 * Method on_modifySouvenirPush_clicked: Class MainWindow
 *_________________________________________________________
 * This slot makes appropriate changes to the UI after the
 *   button has been clicked.
 *   –returns nothing
 *_________________________________________________________
 * PRE-CONDITIONS
 *
 * POST-CONDITIONS
 *   Makes changes to the UI after the button has been
 *   clicked.
 **********************************************************/
void MainWindow::on_modifySouvenirPush_clicked()
{
    ui->souvStadComboBox->blockSignals(true);
    ui->souvStadComboBox->clear();
    ui->souvStadComboBox->addItem("None");
    ui->souvStadComboBox->blockSignals(false);
    for (unsigned i = 0; i < stadiums.size(); i++)
    {
        ui->souvStadComboBox->addItem(QString::fromStdString(stadiums.at(i).name));
    }
    ui->souvStadComboBox->setCurrentIndex(0);
    on_souvStadComboBox_currentIndexChanged(0);
    ui->adminStacked->setCurrentIndex(2);
}

/**********************************************************
 *
 * Method on_stadModifyCancelPush_clicked: Class MainWindow
 *_________________________________________________________
 * This slot makes appropriate changes to the UI after the
 *   button has been clicked.
 *   –returns nothing
 *_________________________________________________________
 * PRE-CONDITIONS
 *
 * POST-CONDITIONS
 *   Makes changes to the UI after the button has been
 *   clicked.
 **********************************************************/
void MainWindow::on_stadModifyCancelPush_clicked()
{
    ui->adminStacked->setCurrentIndex(0);
}

/**********************************************************
 *
 * Method on_selectStadModifyCombo_currentIndexChanged: Class MainWindow
 *_________________________________________________________
 * This slot makes appropriate changes to the UI after the
 *   button has been clicked.
 *   –returns nothing
 *_________________________________________________________
 * PRE-CONDITIONS
 *   index: index of the selected item in the combo box
 *
 * POST-CONDITIONS
 *   Makes changes to the UI after the button has been
 *   clicked.
 **********************************************************/
void MainWindow::on_selectStadModifyCombo_currentIndexChanged(int index)
{
    Stadium currStad;

    if (ui->selectStadModifyCombo->currentText() == "None")
    {
        ui->stadModifyTeamLabel->hide();
        ui->stadModifyTeamLineEdit->hide();
        ui->stadModifyLocLabel->hide();
        ui->stadModifyLocLineEdit->hide();
        ui->stadModifyPhoneLabel->hide();
        ui->stadModifyPhoneLineEdit->hide();
        ui->stadModifyCapLabel->hide();
        ui->stadModifyCapLineEdit->hide();
        ui->stadModifyOpenedLabel->hide();
        ui->stadModifyOpenedLineEdit->hide();
        ui->stadModifySurfaceLabel->hide();
        ui->stadModifySurfaceCombo->hide();
        ui->stadModifyLeagueLabel->hide();
        ui->stadModifyLeagueCombo->hide();
        ui->stadModifyApplyPush->hide();
        ui->noStadSelectedLabel->show();
        return;
    }
    else
    {
        ui->stadModifyTeamLabel->show();
        ui->stadModifyTeamLineEdit->show();
        ui->stadModifyLocLabel->show();
        ui->stadModifyLocLineEdit->show();
        ui->stadModifyPhoneLabel->show();
        ui->stadModifyPhoneLineEdit->show();
        ui->stadModifyCapLabel->show();
        ui->stadModifyCapLineEdit->show();
        ui->stadModifyOpenedLabel->show();
        ui->stadModifyOpenedLineEdit->show();
        ui->stadModifySurfaceLabel->show();
        ui->stadModifySurfaceCombo->show();
        ui->stadModifyLeagueLabel->show();
        ui->stadModifyLeagueCombo->show();
        ui->stadModifyApplyPush->show();
        ui->noStadSelectedLabel->hide();
        ui->stadModifiedLabel->hide();
    }

    currStad = stadiums.at(index - 1);
    ui->stadModifyTeamLineEdit->setText(QString::fromStdString(currStad.team));
    ui->stadModifyLocLineEdit->setText(QString::fromStdString(currStad.location));
    ui->stadModifyPhoneLineEdit->setText(QString::fromStdString(currStad.phone));
    ui->stadModifyCapLineEdit->setText(QString::fromStdString(currStad.capacity));
    ui->stadModifyOpenedLineEdit->setText(QString::fromStdString(currStad.opened));

    if (currStad.surface == "Grass")
        ui->stadModifySurfaceCombo->setCurrentIndex(0);
    else
        ui->stadModifySurfaceCombo->setCurrentIndex(1);

    if (currStad.league == "AL East")
        ui->stadModifyLeagueCombo->setCurrentIndex(0);
    else if (currStad.league == "AL Central")
        ui->stadModifyLeagueCombo->setCurrentIndex(1);
    else if (currStad.league == "AL West")
        ui->stadModifyLeagueCombo->setCurrentIndex(2);
    else if (currStad.league == "NL East")
        ui->stadModifyLeagueCombo->setCurrentIndex(3);
    else if (currStad.league == "NL Central")
        ui->stadModifyLeagueCombo->setCurrentIndex(4);
    else if (currStad.league == "NL West")
        ui->stadModifyLeagueCombo->setCurrentIndex(5);

    ui->stadModifyLocLineEdit->setCursorPosition(0);
    ui->stadModifyCapLineEdit->setCursorPosition(0);
    ui->selectStadModifyCombo->setFocus();
}

/**********************************************************
 *
 * Method on_stadModifyApplyPush_clicked: Class MainWindow
 *_________________________________________________________
 * This slot makes appropriate changes to the UI after the
 *   button has been clicked. The changes made to the
 *   stadium information inputted by the user is stored.
 *   –returns nothing
 *_________________________________________________________
 * PRE-CONDITIONS
 *
 * POST-CONDITIONS
 *   Makes changes to the UI after the button has been
 *   clicked. The changes made to the stadium information
 *   inputted by the user is stored.
 **********************************************************/
void MainWindow::on_stadModifyApplyPush_clicked()
{
    QString newTeam;
    QString newLoc;
    QString newPhone;
    QString newCap;
    QString newOpened;
    Stadium *currStad;
    string newSurface;
    string newLeague;

    newTeam   = ui->stadModifyTeamLineEdit->text();
    newLoc    = ui->stadModifyLocLineEdit->text();
    newPhone  = ui->stadModifyPhoneLineEdit->text();
    newCap    = ui->stadModifyCapLineEdit->text();
    newOpened = ui->stadModifyOpenedLineEdit->text();

    if (ui->stadModifySurfaceCombo->currentIndex() == 0)
        newSurface = "Grass";
    else
        newSurface = "Artificial turf";

    if (ui->stadModifyLeagueCombo->currentIndex() == 0)
        newLeague = "AL East";
    else if (ui->stadModifyLeagueCombo->currentIndex() == 1)
        newLeague = "AL Central";
    else if (ui->stadModifyLeagueCombo->currentIndex() == 2)
        newLeague = "AL West";
    else if (ui->stadModifyLeagueCombo->currentIndex() == 3)
        newLeague = "NL East";
    else if (ui->stadModifyLeagueCombo->currentIndex() == 4)
        newLeague = "NL Central";
    else if (ui->stadModifyLeagueCombo->currentIndex() == 5)
        newLeague = "NL West";

    currStad = &stadiums.at(ui->selectStadModifyCombo->currentIndex() - 1);
    currStad->team     = newTeam.toStdString();
    currStad->location = newLoc.toStdString();
    currStad->phone    = newPhone.toStdString();
    currStad->capacity = newCap.toStdString();
    currStad->opened   = newOpened.toStdString();
    currStad->surface  = newSurface;
    currStad->league   = newLeague;

    ui->stadModifiedLabel->show();
    ui->selectStadModifyCombo->setCurrentIndex(0);
    ui->noStadSelectedLabel->hide();
}

/**********************************************************
 *
 * Method on_souvStadComboBox_currentIndexChanged: Class MainWindow
 *_________________________________________________________
 * This slot makes appropriate changes to the UI after the
 *   button has been clicked. The souvenirs of the stadium
 *   selected from the combo box is displayed.
 *   –returns nothing
 *_________________________________________________________
 * PRE-CONDITIONS
 *   index: the index of the element currently selected in
 *          the combo box
 *
 * POST-CONDITIONS
 *   Makes changes to the UI after the button has been
 *   clicked. The souvenirs of the stadium selected from
 *   the combo box is displayed.
 **********************************************************/
void MainWindow::on_souvStadComboBox_currentIndexChanged(int index)
{
    Stadium currStad;
    QTableWidget *table;
    QTableWidgetItem *newItem;

    if (ui->souvStadComboBox->currentText() == "None")
    {
        ui->souvModifyTableWidget->setRowCount(0);
        ui->souvNoStadSelectedLabel->show();
        ui->souvModifyAddPush->setDisabled(true);
        return;
    }
    else
    {
        ui->souvModifyAddPush->setEnabled(true);
        ui->souvNoStadSelectedLabel->hide();
    }

    currStad = stadiums.at(index - 1);
    table = ui->souvModifyTableWidget;
    table->setColumnCount(2);
    table->setRowCount(0);

    for (unsigned i = 0; i < currStad.souvenirs.size(); i++)
    {
        table->insertRow(i);
        newItem = new QTableWidgetItem(QString::fromStdString(currStad.souvenirs.at(i).name));
        newItem->setTextAlignment(Qt::AlignCenter);
        table->setItem(i, 0, newItem);

        newItem = new QTableWidgetItem
                ("$" + QString::number(currStad.souvenirs.at(i).price, 'f', 2));
        newItem->setTextAlignment(Qt::AlignCenter);
        table->setItem(i, 1, newItem);
    }

    table->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    table->horizontalHeader()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
    table->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
}

/**********************************************************
 *
 * Method on_souvModifyDonePush_clicked: Class MainWindow
 *_________________________________________________________
 * This slot makes appropriate changes to the UI after the
 *   button has been clicked.
 *   –returns nothing
 *_________________________________________________________
 * PRE-CONDITIONS
 *
 * POST-CONDITIONS
 *   Makes changes to the UI after the button has been
 *   clicked.
 **********************************************************/
void MainWindow::on_souvModifyDonePush_clicked()
{
    ui->souvModifyDeletePush->setDisabled(true);
    ui->adminStacked->setCurrentIndex(0);
}

/**********************************************************
 *
 * Method on_souvModifyDonePush_clicked: Class MainWindow
 *_________________________________________________________
 * This slot makes appropriate changes to the UI after the
 *   button has been clicked. The changes made to the
 *   souvenir in the cell is applied and stored.
 *   –returns nothing
 *_________________________________________________________
 * PRE-CONDITIONS
 *   row: the row of the cell clicked
 *   column: the column of the cell clicked
 *
 * POST-CONDITIONS
 *   Makes changes to the UI after the button has been
 *   clicked. The changes made to the souvenir in the cell
 *   is applied and stored.
 **********************************************************/
void MainWindow::on_souvModifyTableWidget_cellChanged(int row, int column)
{
    Stadium *currStad;
    Souvenir *currSouv;
    QTableWidget *table;
    string newName;
    string newPrice;

    currStad = &stadiums.at(ui->souvStadComboBox->currentIndex() - 1);
    currSouv = &currStad->souvenirs.at(row);
    table = ui->souvModifyTableWidget;

    if (unsigned(table->rowCount()) != currStad->souvenirs.size())
        return;

    if (column == 0)
    {
        newName = table->item(row, column)->text().toStdString();
        if (newName != "")
            currSouv->name = newName;
        table->item(row, 0)->setText(QString::fromStdString(currSouv->name));
    }
    else if (column == 1)
    {
        newPrice = table->item(row, column)->text().toStdString();

        if (newPrice[0] == '$')
            newPrice.erase(newPrice.begin());

        for (unsigned i = 0; i < newPrice.length(); i++)
        {
            if ( (int(newPrice[i]) < 48 || int(newPrice[i]) > 57) &&
                 int(newPrice[i]) != 46)
            {
                newPrice = to_string(currSouv->price);
                break;
            }
        }

        if (newPrice != "")
            currSouv->price = stod(newPrice);
        table->item(row, 1)->setText
                               ("$" + QString::number(currSouv->price, 'f', 2));
    }
}

/**********************************************************
 *
 * Method on_addSouvComboBox_currentIndexChanged: Class MainWindow
 *_________________________________________________________
 * This slot makes appropriate changes to the UI after the
 *   button has been clicked.
 *   –returns nothing
 *_________________________________________________________
 * PRE-CONDITIONS
 *
 * POST-CONDITIONS
 *   Makes changes to the UI after the button has been
 *   clicked.
 **********************************************************/
void MainWindow::on_addSouvComboBox_currentIndexChanged(int /*index*/)
{
    ui->addSouvQtySpin->setValue(0);
}

/**********************************************************
 *
 * Method on_souvModifyTableWidget_cellClicked: Class MainWindow
 *_________________________________________________________
 * This slot makes appropriate changes to the UI after the
 *   button has been clicked.
 *   –returns nothing
 *_________________________________________________________
 * PRE-CONDITIONS
 *   row: the row of the cell clicked
 *
 * POST-CONDITIONS
 *   Makes changes to the UI after the button has been
 *   clicked.
 **********************************************************/
void MainWindow::on_souvModifyTableWidget_cellClicked(int row, int /*column*/)
{
    activeRow = row;
    ui->souvModifyDeletePush->setEnabled(true);
}

/**********************************************************
 *
 * Method on_souvModifyDeletePush_clicked: Class MainWindow
 *_________________________________________________________
 * This slot makes appropriate changes to the UI after the
 *   button has been clicked. The current souvenir selected
 *   is deleted.
 *   –returns nothing
 *_________________________________________________________
 * PRE-CONDITIONS
 *
 * POST-CONDITIONS
 *   Makes changes to the UI after the button has been
 *   clicked. The current souvenir selected is deleted.
 **********************************************************/
void MainWindow::on_souvModifyDeletePush_clicked()
{
    Stadium *currStad;

    currStad = &stadiums.at(ui->souvStadComboBox->currentIndex() - 1);
    currStad->souvenirs.erase(currStad->souvenirs.begin() + activeRow);
    on_souvStadComboBox_currentIndexChanged(ui->souvStadComboBox->currentIndex());
}

/**********************************************************
 *
 * Method on_souvModifyAddPush_clicked: Class MainWindow
 *_________________________________________________________
 * This slot makes appropriate changes to the UI after the
 *   button has been clicked.
 *   –returns nothing
 *_________________________________________________________
 * PRE-CONDITIONS
 *
 * POST-CONDITIONS
 *   Makes changes to the UI after the button has been
 *   clicked.
 **********************************************************/
void MainWindow::on_souvModifyAddPush_clicked()
{
    ui->souvModifyAddFrame->show();
    ui->souvModifyAddNameLineEdit->setFocus();
}

/**********************************************************
 *
 * Method on_souvModifyAddClosePush_clicked: Class MainWindow
 *_________________________________________________________
 * This slot makes appropriate changes to the UI after the
 *   button has been clicked.
 *   –returns nothing
 *_________________________________________________________
 * PRE-CONDITIONS
 *
 * POST-CONDITIONS
 *   Makes changes to the UI after the button has been
 *   clicked.
 **********************************************************/
void MainWindow::on_souvModifyAddClosePush_clicked()
{
    ui->souvModifyAddNameLineEdit->clear();
    ui->souvModifyAddPriceLineEdit->clear();
    ui->souvModifyAddFrame->hide();
}

/**********************************************************
 *
 * Method on_souvModifyAddConfirmPush_clicked: Class MainWindow
 *_________________________________________________________
 * This slot makes appropriate changes to the UI after the
 *   button has been clicked. The newly created souvenir
 *   is added to the list of souvenirs belonging to the
 *   current stadium.
 *   –returns nothing
 *_________________________________________________________
 * PRE-CONDITIONS
 *
 * POST-CONDITIONS
 *   Makes changes to the UI after the button has been
 *   clicked. The newly created souvenir is added to the
 *   list of souvenirs belonging to the current stadium.
 **********************************************************/
void MainWindow::on_souvModifyAddConfirmPush_clicked()
{
    Stadium *currStad;
    Souvenir newSouv;
    string name_str;
    string price_str;

    name_str = ui->souvModifyAddNameLineEdit->text().toStdString();
    price_str = ui->souvModifyAddPriceLineEdit->text().toStdString();

    if (name_str == "" || price_str == "")
    {
        ui->souvModifyBadInputLabel->setText("Fill in all fields");
        ui->souvModifyBadInputLabel->show();
        return;
    }

    for (unsigned i = 0; i < price_str.length(); i++)
    {
        if ( (int(price_str[i]) < 48 || int(price_str[i]) > 57) &&
             int(price_str[i]) != 46)
        {
            ui->souvModifyBadInputLabel->setText("Invalid price input");
            ui->souvModifyBadInputLabel->show();
            return;
        }
    }

    ui->souvModifyBadInputLabel->hide();
    newSouv = Souvenir(name_str, stod(price_str));
    currStad = &stadiums.at(ui->souvStadComboBox->currentIndex() - 1);
    currStad->souvenirs.push_back(newSouv);
    ui->souvModifyAddNameLineEdit->clear();
    ui->souvModifyAddPriceLineEdit->clear();
    ui->souvModifyAddFrame->hide();
    on_souvStadComboBox_currentIndexChanged(ui->souvStadComboBox->currentIndex());
}

/**********************************************************
 *
 * Method on_souvModifyAddNameLineEdit_returnPressed: Class MainWindow
 *_________________________________________________________
 * This slot makes appropriate changes to the UI after the
 *   button has been clicked.
 *   –returns nothing
 *_________________________________________________________
 * PRE-CONDITIONS
 *
 * POST-CONDITIONS
 *   Makes changes to the UI after the button has been
 *   clicked.
 **********************************************************/
void MainWindow::on_souvModifyAddNameLineEdit_returnPressed()
{
    ui->souvModifyAddConfirmPush->click();
}

/**********************************************************
 *
 * Method on_souvModifyAddPriceLineEdit_returnPressed: Class MainWindow
 *_________________________________________________________
 * This slot makes appropriate changes to the UI after the
 *   button has been clicked.
 *   –returns nothing
 *_________________________________________________________
 * PRE-CONDITIONS
 *
 * POST-CONDITIONS
 *   Makes changes to the UI after the button has been
 *   clicked.
 **********************************************************/
void MainWindow::on_souvModifyAddPriceLineEdit_returnPressed()
{
    ui->souvModifyAddConfirmPush->click();
}

/**********************************************************
 *
 * Method on_moveToFirstPush_clicked: Class MainWindow
 *_________________________________________________________
 * This slot makes appropriate changes to the UI after the
 *   button has been clicked. The selected stadium is moved
 *   to the first position in the list of stadiums to
 *   visit.
 *   –returns nothing
 *_________________________________________________________
 * PRE-CONDITIONS
 *
 * POST-CONDITIONS
 *   Makes changes to the UI after the button has been
 *   clicked. The selected stadium is moved to the first
 *   position in the list of stadiums to visit.
 **********************************************************/
void MainWindow::on_moveToFirstPush_clicked()
{
    selected.insert(selected.begin(), selected.at(activeRow));
    selected.erase(selected.begin() + activeRow + 1);
    updateChooseStadsTable();
    ui->moveToFirstPush->setDisabled(true);
    ui->deleteStadPush->setDisabled(true);
}

/**********************************************************
 *
 * Method on_addTeamPush_clicked: Class MainWindow
 *_________________________________________________________
 * This slot makes appropriate changes to the UI after the
 *   button has been clicked.
 *   –returns nothing
 *_________________________________________________________
 * PRE-CONDITIONS
 *
 * POST-CONDITIONS
 *   Makes changes to the UI after the button has been
 *   clicked.
 **********************************************************/
void MainWindow::on_addTeamPush_clicked()
{
    ui->addStadCheckedLabel1->hide();
    ui->addStadCheckedLabel2->hide();
    ui->addStadCheckedLabel3->hide();
    ui->addStadSelectSrcLabel->hide();
    ui->addStadSelectSrcCombo->hide();
    ui->addStadSrcDistanceLabel->hide();
    ui->addStadSrcDistLineEdit->hide();
    ui->addStadAddFlightMilesLabel->hide();
    ui->addStadAddFlightPush->hide();
    ui->addStadFlightAddedLabel->hide();
    ui->addStadAddFlightBadInputLabel->hide();
    ui->addStadAddNameRequiredLabel->hide();
    ui->addStadNameLineEdit->clear();
    ui->addStadTeamLineEdit->clear();
    ui->addStadLocLineEdit->clear();
    ui->addStadPhoneLineEdit->clear();
    ui->addStadCapLineEdit->clear();
    ui->addStadOpenedLineEdit->clear();
    ui->addStadSurfaceCombo->setCurrentIndex(0);
    ui->addStadLeagueCombo->setCurrentIndex(0);
    ui->addStadNameLineEdit->setFocus();
    ui->addStadInstructLabel->setText("Click on a location on the\nmap to add stadium");
    ui->addStadInstructLabel->show();
    ui->addStadNameLineEdit->setFocus();
    ui->adminStacked->setCurrentIndex(3);
}

/**********************************************************
 *
 * Method onUserButtonClicked: Class MainWindow
 *_________________________________________________________
 * This slot makes appropriate changes to the UI after the
 *   button has been clicked.
 *   –returns nothing
 *_________________________________________________________
 * PRE-CONDITIONS
 *
 * POST-CONDITIONS
 *   Makes changes to the UI after the button has been
 *   clicked.
 **********************************************************/
void MainWindow::onUserButtonClicked()
{
    Stadium stad;
    QString imagePath;
    QPushButton *buttonSender;

    buttonSender = qobject_cast<QPushButton*>(sender());
    stad = stadiums.at(stadIndexes[buttonSender->text().toStdString()]);
    imagePath = "";

    stadPressedActions(imagePath, stad);
}

/**********************************************************
 *
 * Method on_addStadNextPush_clicked: Class MainWindow
 *_________________________________________________________
 * This slot makes appropriate changes to the UI after the
 *   button has been clicked. The newly created stadium is
 *   officially added.
 *   –returns nothing
 *_________________________________________________________
 * PRE-CONDITIONS
 *
 * POST-CONDITIONS
 *   Makes changes to the UI after the button has been
 *   clicked. The newly created stadium is officially
 *   added.
 **********************************************************/
void MainWindow::on_addStadNextPush_clicked()
{
    string name;
    string team;
    string location;
    string phone;
    string capacity;
    string opened;
    string surface;
    string league;
    Stadium newStad;

    name = ui->addStadNameLineEdit->text().toStdString();
    team = ui->addStadTeamLineEdit->text().toStdString();
    location = ui->addStadLocLineEdit->text().toStdString();
    phone = ui->addStadPhoneLineEdit->text().toStdString();
    capacity = ui->addStadCapLineEdit->text().toStdString();
    opened = ui->addStadOpenedLineEdit->text().toStdString();

    if (ui->addStadSurfaceCombo->currentIndex() == 0)
        surface = "Grass";
    else
        surface = "Artificial turf";

    if (ui->addStadLeagueCombo->currentIndex() == 0)
        league = "AL East";
    else if (ui->addStadLeagueCombo->currentIndex() == 1)
        league = "AL Central";
    else if (ui->addStadLeagueCombo->currentIndex() == 2)
        league = "AL West";
    else if (ui->addStadLeagueCombo->currentIndex() == 3)
        league = "NL East";
    else if (ui->addStadLeagueCombo->currentIndex() == 4)
        league = "NL Central";
    else if (ui->addStadLeagueCombo->currentIndex() == 5)
        league = "NL West";

    if (name == "")
    {
        ui->addStadAddNameRequiredLabel->show();
        return;
    }
    else
    {
        ui->addStadAddNameRequiredLabel->hide();
    }

    newStad = Stadium(name, team, location, phone, capacity, opened, surface,
                      league);
    stadIndexes[newStad.name] = stadiums.size();
    stadiums.push_back(newStad);

    ui->addStadSelectSrcCombo->blockSignals(true);
    ui->addStadSelectSrcCombo->clear();
    ui->addStadSelectSrcCombo->addItem("None");
    ui->addStadSelectSrcCombo->blockSignals(false);
    for (unsigned i = 0; i < stadiums.size(); i++)
    {
        ui->addStadSelectSrcCombo->addItem(QString::fromStdString(stadiums.at(i).name));
    }
    ui->addStadSelectSrcCombo->setCurrentIndex(0);
    on_addStadSelectSrcCombo_currentIndexChanged(0);

    addingDot = true;
    ui->mlbLocationsMapLabel->setCursor(QCursor(Qt::CrossCursor));
    ui->adminStacked->setCurrentIndex(4);
}

/**********************************************************
 *
 * Method on_addStadAddFlightPush_clicked: Class MainWindow
 *_________________________________________________________
 * This slot makes appropriate changes to the UI after the
 *   button has been clicked. The newly created flight is
 *   officially added.
 *   –returns nothing
 *_________________________________________________________
 * PRE-CONDITIONS
 *
 * POST-CONDITIONS
 *   Makes changes to the UI after the button has been
 *   clicked. The newly created flight is officially
 *   added.
 **********************************************************/
void MainWindow::on_addStadAddFlightPush_clicked()
{
    string source;
    string destin;
    string distance_str;

    source = stadiums.at(ui->addStadSelectSrcCombo->currentIndex() - 1).name;
    destin = stadiums.at(stadiums.size() - 1).name;
    distance_str = ui->addStadSrcDistLineEdit->text().toStdString();

    if (distance_str == "")
    {
        ui->addStadAddFlightBadInputLabel->show();
        return;
    }

    for (unsigned i = 0; i < distance_str.length(); i++)
    {
        if ((int(distance_str[i]) < 48 || int(distance_str[i]) > 57) &&
             int(distance_str[i]) != 46)
        {
            ui->addStadAddFlightBadInputLabel->show();
            return;
        }
    }

    if (source == "RingCentral Coliseum")
        source = "AT&T Park";
    else if (source == "Angel Stadium")
        source = "Dodger Stadium";
    else if (source == "US Cellular Field")
        source = "Wrigley Field";
    else if (source == "Yankee Stadium")
        source = "Citi Field";
    else if (source == "Oriole Park at Camden Yards")
        source = "Nationals Park";

    flights.push_back(Edge(Node(source), Node(destin), stoi(distance_str)));
    currFlights = flights;
    stadiumGraph = UndirectedGraph(flights);
    update();

    ui->addStadSelectSrcCombo->removeItem(ui->addStadSelectSrcCombo->currentIndex());
    ui->addStadSelectSrcCombo->setCurrentIndex(0);
    on_addStadSelectSrcCombo_currentIndexChanged(0);

    ui->addStadAddFlightBadInputLabel->hide();
    ui->addStadCheckedLabel3->show();
    ui->addStadFlightAddedLabel->show();
    ui->addStadSkipPush->setText("Done");
}

/**********************************************************
 *
 * Method on_addStadCancelPush_clicked: Class MainWindow
 *_________________________________________________________
 * This slot makes appropriate changes to the UI after the
 *   button has been clicked.
 *   –returns nothing
 *_________________________________________________________
 * PRE-CONDITIONS
 *
 * POST-CONDITIONS
 *   Makes changes to the UI after the button has been
 *   clicked.
 **********************************************************/
void MainWindow::on_addStadCancelPush_clicked()
{
    ui->adminStacked->setCurrentIndex(0);
}

/**********************************************************
 *
 * Method on_addStadSelectSrcCombo_currentIndexChanged: Class MainWindow
 *_________________________________________________________
 * This slot makes appropriate changes to the UI after the
 *   button has been clicked.
 *   –returns nothing
 *_________________________________________________________
 * PRE-CONDITIONS
 *
 * POST-CONDITIONS
 *   Makes changes to the UI after the button has been
 *   clicked.
 **********************************************************/
void MainWindow::on_addStadSelectSrcCombo_currentIndexChanged(int index)
{
    if (index == 0)
    {
        ui->addStadSrcDistanceLabel->setDisabled(true);
        ui->addStadSrcDistLineEdit->setDisabled(true);
        ui->addStadAddFlightMilesLabel->setDisabled(true);
        ui->addStadAddFlightPush->setDisabled(true);
    }
    else
    {
        ui->addStadSrcDistanceLabel->setEnabled(true);
        ui->addStadSrcDistLineEdit->setEnabled(true);
        ui->addStadAddFlightMilesLabel->setEnabled(true);
        ui->addStadAddFlightPush->setEnabled(true);
        ui->addStadSrcDistLineEdit->clear();
        ui->addStadFlightAddedLabel->hide();
    }
}

/**********************************************************
 *
 * Method on_addStadSkipPush_clicked: Class MainWindow
 *_________________________________________________________
 * This slot makes appropriate changes to the UI after the
 *   button has been clicked.
 *   –returns nothing
 *_________________________________________________________
 * PRE-CONDITIONS
 *
 * POST-CONDITIONS
 *   Makes changes to the UI after the button has been
 *   clicked.
 **********************************************************/
void MainWindow::on_addStadSkipPush_clicked()
{
    ui->adminStacked->setCurrentIndex(0);
}

/**********************************************************
 *
 * Method on_changePasswordPush_clicked: Class MainWindow
 *_________________________________________________________
 * This slot makes appropriate changes to the UI after the
 *   button has been clicked. The change password pop up
 *   is executed.
 *   –returns nothing
 *_________________________________________________________
 * PRE-CONDITIONS
 *
 * POST-CONDITIONS
 *   Makes changes to the UI after the button has been
 *   clicked. The change password pop up is executed.
 **********************************************************/
void MainWindow::on_changePasswordPush_clicked()
{
    Password_Change window;
    window.setOldPassword(password);
    window.exec();

    password = window.getNewPassword();
}

/**********************************************************
 *
 * Method on_adminLogOutPush_clicked: Class MainWindow
 *_________________________________________________________
 * This slot makes appropriate changes to the UI after the
 *   button has been clicked. The administrator tools are
 *   disabled.
 *   –returns nothing
 *_________________________________________________________
 * PRE-CONDITIONS
 *
 * POST-CONDITIONS
 *   Makes changes to the UI after the button has been
 *   clicked. The administrator tools are disabled.
 **********************************************************/
void MainWindow::on_adminLogOutPush_clicked()
{
    QMessageBox message;
    ui->passwordLineEdit->clear();
    ui->verifyPush->setDisabled(false);
    ui->adminFrame->setDisabled(true);
    ui->loggedInLabel->hide();
    ui->passwordLineEdit->setFocus();
    message.setText("You have been logged out.");
    message.setStandardButtons(QMessageBox::Ok);
    message.setDefaultButton(QMessageBox::Ok);
    message.exec();
}

/**********************************************************
 *
 * Method on_viewStadiumsPush_clicked: Class MainWindow
 *_________________________________________________________
 * This slot makes appropriate changes to the UI after the
 *   button has been clicked. The stadium report window is
 *   shown.
 *   –returns nothing
 *_________________________________________________________
 * PRE-CONDITIONS
 *
 * POST-CONDITIONS
 *   Makes changes to the UI after the button has been
 *   clicked. The stadium report window is shown.
 **********************************************************/
void MainWindow::on_viewStadiumsPush_clicked()
{
    Stadium_Reports sr(stadiums);

    sr.setModal(true);
    sr.exec();
}
