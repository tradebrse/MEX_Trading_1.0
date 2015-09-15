#include "mex_trader.h"
using namespace std;

MEX_Trader::MEX_Trader(QString username, QString password, long traderID, QString permission, int credit)
{
    this->username=username;
    this->password=password;
    this->traderID=traderID;
    this->permission=permission;
    this->credit=credit;
}

MEX_Trader::~MEX_Trader()
{

}
// Get Methods
QString MEX_Trader::getName()
{
    return this->username;
}
QString MEX_Trader::getPassword()
{
    return this->password;
}
long MEX_Trader::getTraderID()
{
    return this->traderID;
}
QString MEX_Trader::getPermission()
{
    return this->permission;
}
int MEX_Trader::getCredit()
{
    return this->credit;
}
// Set Methods
void MEX_Trader::setName(QString username)
{
    this->username=username;
    return;
}
void MEX_Trader::setPassword(QString password)
{
    this->password=password;
    return;
}
void MEX_Trader::setTraderID(long traderID)
{
    this->traderID=traderID;
    return;
}
void MEX_Trader::setPermission(QString permission)
{
    this->permission=permission;
    return;
}
void MEX_Trader::setCredit(int credit)
{
    this->credit=credit;
    return;
}
//void MEX_Trade::setName(QString)
//{

//}


