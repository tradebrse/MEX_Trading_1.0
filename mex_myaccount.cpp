#include "mex_myaccount.h"
#include "ui_mex_myaccount.h"
#include <QDebug>

// Constructor

MEX_MyAccount::MEX_MyAccount(QString userID, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MEX_MyAccount)
{
    ui->setupUi(this);
    this->setFixedSize(this->size()); //Set fixed window size
    QString dbPath = QApplication::applicationDirPath() + "/qt_db.sqlite";
    db = QSqlDatabase::addDatabase("QSQLITE", "myAccount_connection"); //"myAccount_connection"
    db.setDatabaseName(dbPath);

    setUserID(userID);
    bool ok;
    QString sqlCommand = "SELECT user, email, credit, usertype, pass FROM userList WHERE id = '" + userID + "' ";
    QSqlQuery query  = executeQuery(sqlCommand, ok);

    if (ok)
    {
        query.first();
        username = query.record().value(0).toString();
        email = query.record().value(1).toString();
        credit = query.record().value(2).toString()+"€";
        usertype = query.record().value(3).toString();
        currentUserPass =  query.record().value(4).toString();
        ui->lblUserOutput->setText(username);
        ui->lblMailOutput->setText(email);
        ui->lblCreditOutput->setText(credit);
        ui->lblUsertypeOutput->setText(usertype);
    } else
    {
        QMessageBox messageBox;
        messageBox.critical(0,"Error","Database not found.");
        messageBox.show();
    }
}

//Deconstructor

MEX_MyAccount::~MEX_MyAccount()
{
    closeDB();
    delete ui;
}

// Public member functions
/*************************/
void MEX_MyAccount::setUserID(QString userID)
{
    this->userID = userID;
}

// Private member functions
/*************************/



void MEX_MyAccount::on_btnChangePW_clicked()
{
    changePassword();
}

void MEX_MyAccount::changePassword(){
    ui->lblInfoOutput->clear();
    QString currentUserPassInput = ui->edtCurrentPassword->text();
    QString newUserpass = ui->edtNewPassword->text();
    QString newUserpassCheck = ui->edtNewPassword_2->text();
    QString cryptCurrentPass = encrypt(currentUserPassInput);
        if (cryptCurrentPass == currentUserPass){
            if(newUserpass == newUserpassCheck)
            {
                if(!newUserpass.contains(" "))
                {
                    if (newUserpass.length() > 4)
                    {
                        QString cryptpass = encrypt(newUserpass);
                        bool ok;
                        QString sqlCommand = "UPDATE userList SET pass = '" + cryptpass + "' WHERE user = '" + username + "' ";
                        QSqlQuery query(QSqlDatabase::database("userpanel_connection"));
                        query = executeQuery(sqlCommand, ok);
                        if (ok)
                        {
                            ui->edtCurrentPassword->clear();
                            ui->edtNewPassword->clear();
                            ui->edtNewPassword_2->clear();
                            ui->lblInfoOutput->setText("Password has been changed.");
                        } else
                        {
                            ui->lblInfoOutput->setText("Password could not be changed."); //Query could not be executed
                        }
                    } else
                    {
                        ui->lblInfoOutput->setText("Password must be minimum 5 characters.");
                    }
                } else
                {
                    ui->lblInfoOutput->setText("Spaces are not allowed.");
                }
            } else
            {
                ui->lblInfoOutput->setText("Your passwords do not match.");
            }
        }else
        {
            ui->lblInfoOutput->setText("Current password does not match.");
        }
}

QSqlQuery MEX_MyAccount::executeQuery (QString sqlCommand, bool &ok)
{
    if (!db.open())
    {
        ///db.lastError().text()
        QSqlQuery emptyQuery;
        return emptyQuery;
    } else {
        QSqlQuery query(QSqlDatabase::database("myAccount_connection"));
        ok = query.exec(sqlCommand);
        return query;
    }
}

void MEX_MyAccount::closeDB()
{
    QString connection;
    connection = db.connectionName();
    db.close();
    db = QSqlDatabase();
    db.removeDatabase(connection);
}

QString MEX_MyAccount::encrypt(QString clearPass)
{
    QByteArray result = hash->hash(clearPass.toUtf8(),QCryptographicHash::Md5);
    return result.toHex();
}
