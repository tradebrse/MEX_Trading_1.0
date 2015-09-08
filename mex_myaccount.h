#ifndef MEX_MYACCOUNT_H
#define MEX_MYACCOUNT_H

#include <QWidget>

//---------------//
//      SQL      //
//---------------//
#include <QtSql>


namespace Ui {
class MEX_MyAccount;
}

class MEX_MyAccount : public QWidget
{
    Q_OBJECT

public:
    // Constructor/Deconstructor
    explicit MEX_MyAccount(QWidget *parent = 0);
    ~MEX_MyAccount();

    void setUserID(QString);

private:
    Ui::MEX_MyAccount *ui;

    //--------//
    // SQL-DB //
    //--------//

    QSqlDatabase db;

    //---------//
    // User ID //
    //---------//

    QString userID;
};

#endif // MEX_MYACCOUNT_H
