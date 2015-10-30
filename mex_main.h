#ifndef MEX_MAIN_H
#define MEX_MAIN_H

#include <mex_login.h>
#include <mex_userpanel.h>
#include <mex_myaccount.h>
#include <mex_product.h>
#include <mex_trader.h>
#include <mex_order.h>
#include <mex_tradelog.h>
#include <QMainWindow>
#include <QDebug>
#include <QVarLengthArray>
#include <ui_mex_main.h>

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

    void enableWindow();

    QSqlQuery executeQuery(QString, bool&);

    void readProductDB();

    void generateProducts(QStringList, QStringList, QStringList);

    void loadTrader();

    void on_btnExecute_clicked();

    void executeOrder();

    bool checkForMatch(MEX_Order*, QList<MEX_Order*>&, QTableWidget *&, QList<MEX_Order*> &, QTableWidget *&);

    void addOrder(MEX_Order*, QList<MEX_Order*>&, QTableWidget *&, QList<MEX_Order*> &, QTableWidget *&); //Overloaded function -> checks for order match, then adds Order to book

    void addOrder(MEX_Order*, QList<MEX_Order*>&, QTableWidget *&a); //Overloaded function -> only adds order to book

    void refreshTable(QString, QString);

    void on_btnShow_clicked();

    void on_actionTrade_Log_triggered();

    void openTradeLog();

    void sortAskTable(int index);

    void sortBidTable(int index);

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

    QStringList productNameList;

    QStringList productSymbolList;

    QStringList productIndexList;

    QList<MEX_Product> productList;

    MEX_Trader trader;

    QString traderID;

    QString username;

    QString password;

    QString permission;

    int credit;

    QList<MEX_Order*> bidOrderBook;

    QList<MEX_Order*> askOrderBook;

    QList<MEX_Order*> matchedOrders;

    //Order attritbutes//
    int orderID; //static?
    int value;
    int quantity;
    QString comment;
    bool buy;
    bool sell;
    MEX_Product product;
    int newRow;
    QVarLengthArray<int> ordersToDelete;

protected:

};

#endif // MEX_MAIN_H
