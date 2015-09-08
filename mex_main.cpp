#include "mex_main.h"
#include "ui_mex_main.h"

// Constructor

MEX_Main::MEX_Main(QString userID, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MEX_Main)
{
    ui->setupUi(this);

    //Setup DB
    QString dbPath = QApplication::applicationDirPath() + "/qt_db.sqlite";
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbPath);

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
    MEX_UserPanel *userPanelWidget = new MEX_UserPanel;
    userPanelWidget->show();
    userPanelWidget->setUserID(this->userID);

}

void MEX_Main::on_actionMy_Account_triggered()
{
    openMyAccount();
}

void MEX_Main::openMyAccount()
{
    MEX_MyAccount *myAccount = new MEX_MyAccount;
    myAccount->show();
    myAccount->setUserID(this->userID);
}

QSqlQuery MEX_Main::executeQuery( QString sqlCommand, bool &ok )
{
    if (!db.open())
    {
        ///db.lastError().text()
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

