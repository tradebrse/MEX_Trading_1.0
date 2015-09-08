#include "mex_userpanel.h"
#include "ui_mex_userpanel.h"

// Constructor/Deconstructor

MEX_UserPanel::MEX_UserPanel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MEX_UserPanel)
{
    ui->setupUi(this);

    QString dbPath = QApplication::applicationDirPath() + "/qt_db.sqlite";
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbPath);
}

//Deconstructor

MEX_UserPanel::~MEX_UserPanel()
{
    delete ui;
}

// Public member functions
/*************************/
void MEX_UserPanel::setUserID(QString userID)
{
    this->userID = userID;
}

// Private member functions
/*************************/
void MEX_UserPanel::on_btnShowPW_clicked()
{
    showUserPW();
}

void MEX_UserPanel::on_btnDeleteUser_clicked()
{
    deleteUser();
}

void MEX_UserPanel::on_btnShowUsers_clicked()
{
    showUsers();
}

void MEX_UserPanel::deleteUser()
{
    if(ui->lwUsers->selectedItems().count()==0)
    {
        QMessageBox messageBox;
        messageBox.information(0,"","No User selected.");
        messageBox.show();
    }
    else
    {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Delete", "Are you sure you want to delete this user?",
                                      QMessageBox::Yes|QMessageBox::No);
        if (reply == QMessageBox::Yes)
        {
            QString user = ui->lwUsers->selectedItems().first()->text();
            QString seperator = " ";
            if(user.contains(seperator))
            {
                int seperatorIndex = user.indexOf(seperator);
                user.truncate(seperatorIndex);
            }
            bool ok;

            QString sqlCommand = "SELECT usertype FROM userList WHERE user = '" + user + "' ";

            QSqlQuery query  = executeQuery(sqlCommand, ok);

            if (ok)
            {
                query.first();
                if (query.record().value(0).toString() == "client")
                {
                    bool ok;
                    QString sqlCommand = "DELETE FROM userList WHERE user = '" + user + "' ";
                    executeQuery(sqlCommand, ok);
                    if (ok)
                    {
                        showUsers();
                        QMessageBox messageBox;
                        messageBox.information(0,"","User deleted.");
                        messageBox.show();
                    } else
                    {
                        QMessageBox messageBox;
                        messageBox.critical(0,"Error","Database not found.");
                        messageBox.show();
                    }
                } else
                {
                    QMessageBox messageBox;
                    messageBox.information(0,"","This user can not be deleted.");
                    messageBox.show();
                }
            } else
            {
                QMessageBox messageBox;
                messageBox.critical(0,"Error","Database not found.");
                messageBox.show();
            }
        }
    }
}

void MEX_UserPanel::showUserPW(){

    if(ui->lwUsers->selectedItems().count() == 0)
    {
        QMessageBox messageBox;
        messageBox.information(0,"","No User selected.");
        messageBox.show();
    } else
    {
        QString user = ui->lwUsers->selectedItems().first()->text();

        bool ok;

        QString sqlCommand = "SELECT pass FROM userList WHERE user = '" + user + "' ";

        QSqlQuery query  = executeQuery(sqlCommand, ok);

        if (ok)
        {
            query.first();
            if (query.record().value(0).toString() != "")
            {
                ui->lwUsers->selectedItems().first()->setText(user + "  :  " + query.record().value(0).toString());
            }
        } else
        {
            QMessageBox messageBox;
            messageBox.critical(0,"Error","Database not found.");
            messageBox.show();
        }


    }
}

void MEX_UserPanel::showUsers()
{
    refreshList();  //show username list
    ui->lwUsers->clear();
    foreach (QString user, this->userList)
    {
        ui->lwUsers->addItem(user);
    }
    ui->btnShowPW->setEnabled(true);
    ui->lwUsers->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->lwUsers->item(0)->setSelected(true);
}

void MEX_UserPanel::refreshList()
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
            ok = query.next();									//get next line
        }   //while there is a next line
    } else
    { //Error while executing query
        QMessageBox messageBox;
        messageBox.critical(0,"Error","Database not found.");
        messageBox.show();
    }
}


QSqlQuery MEX_UserPanel::executeQuery (QString sqlCommand, bool &ok)
{
    if (!db.open())
    {
        ///db.lastError().text()
    } else {

        //--------------------------------------//
        // Bei mehr als einer DB spezifizieren, //
        // für welche der Query gelten soll.    //
        //--------------------------------------//

        QSqlQuery query;

        ok = query.exec(sqlCommand);
        return query;
    }

}

void MEX_UserPanel::closeDB()
{
    QString connection;
    connection = db.connectionName();
    db.close();
    db = QSqlDatabase();
    db.removeDatabase(connection);
}

