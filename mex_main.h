#ifndef MEX_MAIN_H
#define MEX_MAIN_H

#include <mex_login.h>
#include <mex_userpanel.h>
#include <mex_myaccount.h>
#include <QMainWindow>
#include <QDebug>

//---------------//
//      SQL      //
//---------------//
#include <QtSql>


namespace Ui {
class MEX_Main;
}

class MEX_Main : public QMainWindow
{
    Q_OBJECT

public:
    // Constructor/Deconstructor
    explicit MEX_Main(QString, QWidget *parent = 0);
    ~MEX_Main();

    void setUserID(QString);

    QString getUserID();

private slots:

    void on_btnLogOut_clicked();

    void logOutUser();

    void openUserPanel();

    void openMyAccount();

    void on_actionUser_Panel_triggered();

    void on_actionMy_Account_triggered();

    void closeDB();

    QSqlQuery executeQuery(QString, bool&);

private:
    Ui::MEX_Main *ui;

    //--------//
    // SQL-DB //
    //--------//

    QSqlDatabase db;

    //---------//
    // User ID //
    //---------//

    QString userID;
};

#endif // MEX_MAIN_H
