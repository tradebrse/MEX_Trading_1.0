#include "mex_myaccount.h"
#include "ui_mex_myaccount.h"

// Constructor

MEX_MyAccount::MEX_MyAccount(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MEX_MyAccount)
{
    ui->setupUi(this);
    QString id;
}

//Deconstructor

MEX_MyAccount::~MEX_MyAccount()
{
    delete ui;
}

// Public member functions
/*************************/
void MEX_MyAccount::setUserID(QString userID){
    this->userID = userID;
}

// Private member functions
/*************************/
