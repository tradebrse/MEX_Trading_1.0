#include "mex_main.h"
#include "ui_mex_main.h"

// Constructor

MEX_Main::MEX_Main(QString userID, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MEX_Main)
{
    ui->setupUi(this);
    this->setFixedSize(this->size()); //Set fixed window size
    this->setAttribute(Qt::WA_DeleteOnClose);
    setUserID(userID);
    //Setup DB
    QString dbPath = QApplication::applicationDirPath() + "/qt_db.sqlite";
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbPath);

    //generate Products
    readProductDB();
    generateProducts(productSymbolList, productNameList);

    //Check usertype to activate admin mode
    bool ok;
    QString sqlCommand = "SELECT usertype FROM userList WHERE id = '" + userID + "' ";
    QSqlQuery query  = executeQuery(sqlCommand, ok);

    if (ok)
    {
        query.first();
        if (query.record().value(0).toString() == "client")
        {
            ui->actionUser_Panel->setVisible(false);
        }
        else if(query.record().value(0).toString() == "admin")
        {
            ui->actionUser_Panel->setVisible(true);
        }
    } else
    {
        QMessageBox messageBox;
        messageBox.critical(0,"Error","Database not found.");
        ui->actionUser_Panel->setVisible(false);
        messageBox.show();
    }
    closeDB();
}

// Deconstructor

MEX_Main::~MEX_Main()
{
    delete ui;
}

// Public member functions
/*************************/
void MEX_Main::setUserID(QString userID){
    this->userID = userID;
}

QString MEX_Main::getUserID(){
    return this->userID;
}

// Private member functions
/*************************/
void MEX_Main::on_btnLogOut_clicked()
{
    logOutUser();
}

void MEX_Main::logOutUser()
{
    QWidget *loginWidget = new MEX_Login;
    loginWidget->show();
    this->close();
}

void MEX_Main::on_actionUser_Panel_triggered()
{
    openUserPanel();
}

void MEX_Main::openUserPanel()
{
    MEX_UserPanel *userPanelWidget = new MEX_UserPanel(); //this
    userPanelWidget->setAttribute(Qt::WA_DeleteOnClose);
    connect( userPanelWidget, SIGNAL(destroyed()), this, SLOT(enableWindow()));
    connect( this, SIGNAL(destroyed()), userPanelWidget, SLOT(close()));
    userPanelWidget->show();
    this->setDisabled(true);
    userPanelWidget->setUserID(this->userID);
}

void MEX_Main::on_actionMy_Account_triggered()
{
    openMyAccount();
}

void MEX_Main::openMyAccount()
{
    MEX_MyAccount *myAccount = new MEX_MyAccount(userID);
    myAccount->setAttribute(Qt::WA_DeleteOnClose);
    connect( myAccount, SIGNAL(destroyed()), this, SLOT(enableWindow()));
    connect( this, SIGNAL(destroyed()), myAccount, SLOT(close()));
    myAccount->show();
    this->setDisabled(true);
}

void MEX_Main::enableWindow()
{
    this->setEnabled(true);
}

QSqlQuery MEX_Main::executeQuery( QString sqlCommand, bool &ok )
{
    if (!db.open())
    {
        ///db.lastError().text()
        QSqlQuery emptyQuery;
        return emptyQuery;
    } else
    {
        //--------------------------------------//
        // Bei mehr als einer DB spezifizieren, //
        // für welche der Query gelten soll.    //
        //--------------------------------------//
        QSqlQuery query;
        ok = query.exec(sqlCommand);
        return query;
    }
}

void MEX_Main::closeDB()
{
    QString connection;
    connection = db.connectionName();
    db.close();
    db = QSqlDatabase();
    db.removeDatabase(connection);
}
/*
void MEX_Main::generateProducts()
{
   MEX_Product BAYN = new MEX_Product("Bayer AG");
    MEX_Product DPW = new MEX_Product("Deutsche Post AG");
    MEX_Product EOAN = new MEX_Product("E.ON SE");
    MEX_Product LIN = new MEX_Product("Linde AG");
    MEX_Product VOW3 = new MEX_Product("Volkswagen AG");
    new MEX_Product("Test");

    QStringList productList;
    productList.append(BAYN.getName());
}

*/

void MEX_Main::readProductDB()
{
    bool ok;
    QString sqlCommand = "SELECT symbol, name FROM productList";
    QSqlQuery query  = executeQuery(sqlCommand, ok);

    if (ok)
    {
        ok = query.first();								//go to first line
        while (ok) {
            productSymbolList.append(query.value(0).toString());	//fill QStringList
            productNameList.append(query.value(1).toString());	//fill QStringList
            ok = query.next();									//get next line
        } //while there are next lines
    } else
    {
        QMessageBox messageBox;
        messageBox.critical(0,"Error","Database not found.");
        ui->actionUser_Panel->setVisible(false);
        messageBox.show();
    }
    ui->cBoxProductShow->addItems(productNameList);
    ui->cBoxProductExec->addItems(productNameList);
}

void MEX_Main::generateProducts(QStringList symbol, QStringList name)
{
    for (int i = 0; i < symbol.size() ; i++){
        productList.append(new MEX_Product(symbol.value(i), name.value(i)));
    }
    for (int i = 0; i < productList.size() ; i++){
        qDebug() << productList.value(i)->getName();
    }
}
