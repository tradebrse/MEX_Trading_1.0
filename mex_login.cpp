#include "mex_login.h"
#include "ui_mex_login.h"
#include <mex_trader.h>

// Constructor

MEX_Login::MEX_Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MEX_Login)
{
    ui->setupUi(this);

    QString dbPath = QApplication::applicationDirPath() + "/qt_db.sqlite";
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbPath);
    connect(ui->edtLogInPW, SIGNAL(returnPressed()),ui->btnLogIn,SIGNAL(clicked()));
    connect(ui->edtSignPW, SIGNAL(returnPressed()),ui->btnSignUp,SIGNAL(clicked()));
}

//Deconstructor

MEX_Login::~MEX_Login()
{
    delete ui;
}

// Public member functions
/*************************/
inline void MEX_Login::setUserID(QString userID)
{
    this->userID = userID;
}

inline QString MEX_Login::getUserID()
{
    return this->userID;
}

// Private member functions
/*************************/
void MEX_Login::on_btnLogIn_clicked()
{
    logInUser();
}

void MEX_Login::on_btnSignUp_clicked()
{
    registerUser();

}

void MEX_Login::logInUser()
{
    QString username;
    QString userpass;
    username = ui->edtLogInUser->text();
    userpass = ui->edtLogInPW->text();
    refreshList();
    if (this->userList.contains(username))
    {
        bool ok;
        QString sqlCommand = "SELECT id,pass,usertype  FROM userList WHERE user = '" + username + "' ";
        QSqlQuery query = executeQuery(sqlCommand, ok);
        if (ok)
        {
            query.first();
            QString cryptPass = encrypt(userpass);
            if (cryptPass == query.record().value(1).toString() )
            {
                ui->edtLogInUser->clear();
                ui->edtLogInPW->clear();
                query.first();
                QString userID = query.record().value(0).toString();
                if (query.record().value(2).toString() == "client" )
                {
                    ui->lblLogInOutput->setText("Successsfully logged in as '" + username + "' !");
                    openMainWindow(userID);
                } else if(query.record().value(2).toString() == "admin" )
                {
                    ui->lblLogInOutput->setText("Successsfully logged in as admin!");
                    openMainWindow(userID);
                    ui->edtLogInPW->setEnabled(false);
                    ui->edtLogInUser->setEnabled(false);
                }

            } else
            {
                ui->lblLogInOutput->setText("Wrong username or password.");
                ui->edtLogInPW->clear();
            }
        } else
        {
            ui->lblLogInOutput->setText("Error: '" + username + "' could not be logged in");
        }

    } else
    {
        ui->lblLogInOutput->setText("Wrong username or password.");
    }

}

void MEX_Login::registerUser()
{
    QString username;
    QString userpass;
    username = ui->edtSignUser->text();
    userpass = ui->edtSignPW->text();

    refreshList();
    if(!username.contains(" ") && !userpass.contains(" "))
    {
        if (!this->userList.contains(username))
        {
            if (username.length() > 4 && userpass.length() > 4)
            {

                bool ok;
                QString cryptPass = encrypt(userpass);
                QString sqlCommand = "INSERT INTO userList (user, pass) VALUES ('" + username + "', '" + cryptPass + "') ";
                executeQuery(sqlCommand, ok);
                if (ok)
                {
                    ui->lblSignOutput->setText("'" + username + "' registered.");
                    userList.append(username);
                    ui->edtSignUser->clear();
                    ui->edtSignPW->clear();

                } else
                {   //else: Error while executing query
                    ui->lblSignOutput->setText("Error: '" + username + "' could not be registered.");
                }

            } else
            {   //else: Username too short
                ui->lblSignOutput->setText("Username and password must be minimum 5 characters.");
            }
        } else
        {   //else: Username taken
            ui->lblSignOutput->setText("'" + username + "' is already taken.");
        }
    } else
    {   //else: Spaces in the text
        ui->lblSignOutput->setText("Spaces are not allowed.");
    }
}


QSqlQuery MEX_Login::executeQuery (const QString sqlCommand, bool &ok) {


    if (!db.open())
    {
        QMessageBox messageBox;
        messageBox.critical(0,"Error","No database connection.");
        messageBox.show();
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

void MEX_Login::refreshList()
{
    bool ok;
    QString sqlCommand = "SELECT user FROM userList";
    QSqlQuery query = executeQuery(sqlCommand, ok);
    if (ok)
    {
        this->userList.clear();
        ok = query.first();								//go to first line
        while (ok)
        {
            this->userList.append(query.value(0).toString());	//fill list with usernames
            ok = query.next();									//next line
        } //while ok
    } else
    { //Error while executing SQL-Statement
        QMessageBox messageBox;
        messageBox.critical(0,"Error","Database not found.");
        messageBox.show();
    } //else: Error
}



QString MEX_Login::encrypt(QString clearPass)
{
    QByteArray result = hash->hash(clearPass.toUtf8(),QCryptographicHash::Md5);
    return result.toHex();
}

void MEX_Login::openMainWindow(QString userID)
{
    closeDB();
    MEX_Main *mainWindow = new MEX_Main(userID);
    mainWindow->show();
    this->hide();

}

void MEX_Login::closeDB()
{
    QString connection;
    connection = db.connectionName();
    db.close();
    db = QSqlDatabase();
    db.removeDatabase(connection);
}
