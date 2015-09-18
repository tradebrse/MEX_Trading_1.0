#include "mex_main.h"
#include "ui_mex_main.h"

// Constructor

MEX_Main::MEX_Main(QString userID, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MEX_Main)
{
    ui->setupUi(this);
    this->setFixedSize(this->size()); //Set fixed window size
    ui->radioButtonBid->setEnabled(true);
    this->setAttribute(Qt::WA_DeleteOnClose);
    setUserID(userID);
    //Setup DB
    QString dbPath = QApplication::applicationDirPath() + "/qt_db.sqlite";
    db = QSqlDatabase::addDatabase("QSQLITE", "main_connection");
    db.setDatabaseName(dbPath);

    //load Trader data from DB
    loadTrader();

    //initialize Order ID
    orderID = 0;

    //generate Products
    readProductDB();
    generateProducts(productSymbolList, productNameList);

    //Check usertype to activate admin mode
    bool ok = false;

    QString sqlCommand = "SELECT usertype FROM userList WHERE id = '" + userID + "' ";

    QSqlQuery query(QSqlDatabase::database("main_connection"));

    query  = executeQuery(sqlCommand, ok);

    if ( ok )
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
}

// Deconstructor

MEX_Main::~MEX_Main()
{
    closeDB();
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
    connect( userPanelWidget, SIGNAL(destroyed()), this, SLOT(loadTrader()));
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
    connect( myAccount, SIGNAL(destroyed()), this, SLOT(loadTrader()));
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
        QSqlQuery query(QSqlDatabase::database("main_connection"));
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

void MEX_Main::readProductDB()
{
    bool ok = false;
    QString sqlCommand = "SELECT symbol, name FROM productList";
    QSqlQuery query(QSqlDatabase::database("main_connection"));

    query  = executeQuery(sqlCommand, ok);

    if (ok)
    {
        ok = query.first();								//go to first line
        while (ok)
        {
            productSymbolList.append(query.value(0).toString());	//fill QStringList
            productNameList.append(query.value(1).toString());	//fill QStringList
            ok = query.next();									//get next line
        } //while there are next lines
    }
    else
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
    for (int i = 0; i < symbol.size(); ++i)
    {
        productList.append(new MEX_Product(symbol.value(i), name.value(i)));
    }
}

void MEX_Main::loadTrader()
{
    bool ok = false;

    QString   sqlCommand = "SELECT user, pass, usertype, credit FROM userList WHERE id = '" + userID + "' ";

    QSqlQuery query(QSqlDatabase::database("main_connection"));

    query  = executeQuery(sqlCommand, ok);

    /** if the query successfully executed, then get the trader information */
    if ( ok == true )
    {
        query.first();
        traderID = userID;
        username = query.record().value(0).toString();
        password = query.record().value(1).toString();
        permission = query.record().value(2).toString();
        credit = query.record().value(3).toInt();
        trader.setTraderID(traderID);
        trader.setName(username);
        trader.setPassword(password);
        trader.setPermission(permission);
        trader.setCredit(credit);
    }
    else
    {
        QMessageBox messageBox;

        messageBox.critical(0,"Error","Database not found.");
        messageBox.show();
    }
}

void MEX_Main::on_btnExecute_clicked()
{
    executeOrder();
}

void MEX_Main::executeOrder()
{
    if(ui->radioButtonAsk->isChecked())
    {
        buy = true;
        sell = false;
    }
    else if(ui->radioButtonBid->isChecked())
    {
        sell = true;
        buy = false;
    }
    int cBoxIndex = ui->cBoxProductExec->currentIndex();

    product = productList.at(cBoxIndex);
    QString productName = product->getName();
    QString productSymbol = product->getSymbol();

    value = ui->edtValue->text().toInt();
    quantity = ui->edtQuantity->text().toInt();
    comment = ui->edtComment->text();
    orderID += 1;
    if (buy)
    {
        bool match = false;
        match = checkForMatch(new MEX_Order(traderID, orderID, value, quantity, comment, product), bidOrderBook, ui->tableWidgetOrderbookBid );
        if(match == false)
        {
            askOrderBook.append(new MEX_Order(traderID, orderID, value, quantity, comment, product));
            newRow = ui->tableWidgetOrderbookAsk->rowCount();
            ui->tableWidgetOrderbookAsk->insertRow(newRow);
            ui->tableWidgetOrderbookAsk->setItem(newRow, 0,new QTableWidgetItem(productSymbol));
            ui->tableWidgetOrderbookAsk->setItem(newRow, 1,new QTableWidgetItem("0"));
            ui->tableWidgetOrderbookAsk->setItem(newRow, 2,new QTableWidgetItem(QString::number(quantity)));
            ui->tableWidgetOrderbookAsk->setItem(newRow, 3,new QTableWidgetItem(QString::number(value)));
            ui->tableWidgetOrderbookAsk->setItem(newRow, 4,new QTableWidgetItem(comment));
        }
        buy = false;
    }
    else if(sell)
    {
        bool match = false;
        match = checkForMatch(new MEX_Order(traderID, orderID, value, quantity, comment, product), askOrderBook, ui->tableWidgetOrderbookAsk );
        if(match == false)
        {
            bidOrderBook.append((new MEX_Order(traderID, orderID, value, quantity, comment, product)));
            newRow = ui->tableWidgetOrderbookBid->rowCount();
            ui->tableWidgetOrderbookBid->insertRow(newRow);
            ui->tableWidgetOrderbookBid->setItem(newRow, 0,new QTableWidgetItem(productSymbol));
            ui->tableWidgetOrderbookBid->setItem(newRow, 1,new QTableWidgetItem("0"));
            ui->tableWidgetOrderbookBid->setItem(newRow, 2,new QTableWidgetItem(QString::number(quantity)));
            ui->tableWidgetOrderbookBid->setItem(newRow, 3,new QTableWidgetItem(QString::number(value)));
            ui->tableWidgetOrderbookBid->setItem(newRow, 4,new QTableWidgetItem(comment));
        }
        sell = false;
    }
}

bool MEX_Main::checkForMatch(MEX_Order &order, QList &orderList, QTableWidget tablewidget)
{
    bool match = false;
    QList<MEX_Order>::iterator i;
    for(i=orderList.begin(); i!=orderList.end(); i++){
        if(i->getProduct() == order.getProduct())
        {
            if(i->getValue() == order.getValue())
            {
                match = true;
                if( i->getQuantity() >= order.getQuantity())
                {
                    int newQuantity = i->getQuantity() - order.getQuantity();
                    if (newQuantity == 0)
                    {
                        orderList.removeAt(i->getOrderID().toInt()-1);
                        ui->tablewidget->removeRow(i->getOrderID()-1);
                    }
                    else
                    {
                        i->setQuantity(newQuantity);
                    }
                }
                else if ( order.getQuantity() > i->getQuantity())
                {
                    //nach weiteren Orders im Buch suchen / restliche qunatity refusen
                }
            }
        }
    }
    return match;
}
