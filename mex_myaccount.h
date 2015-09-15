#ifndef MEX_MYACCOUNT_H
#define MEX_MYACCOUNT_H

#include <mex_main.h>
#include <QMainWindow>
#include <QWidget>
#include <QMessageBox>

//---------------//
//      SQL      //
//---------------//
#include <QtSql>


//MEX_Main * main;

namespace Ui {
class MEX_MyAccount;
}

class MEX_MyAccount : public QWidget
{
    Q_OBJECT

public:
    // Constructor/Deconstructor

    class MEX_Main;

    explicit MEX_MyAccount(QString, QWidget *parent = 0);
    ~MEX_MyAccount();

    void setUserID(QString);

private slots:
    void on_btnChangePW_clicked();

    void changePassword();

    void closeDB();

    QString encrypt(QString);

    QSqlQuery executeQuery(QString, bool&);

private:

    QString username;
    QString email;
    QString credit;
    QString usertype;
    QString currentUserPass;

    Ui::MEX_MyAccount *ui;

    //--------//
    // SQL-DB //
    //--------//

    QSqlDatabase db;

    //---------//
    // User ID //
    //---------//

    QString userID;

    QCryptographicHash* hash;
};

#endif // MEX_MYACCOUNT_H
