#ifndef MEX_TRADER_H
#define MEX_TRADER_H
#include <QString>

using namespace std;

class MEX_Trader
{
public:
    MEX_Trader(QString username, QString password, long traderID, QString permission, int credit); //Constructor
    ~MEX_Trader();
                            //All methods
    QString getName();
    void setName(QString);
    QString getPassword();
    void setPassword(QString);
    long getTraderID();
    void setTraderID(long);
    QString getPermission();
    void setPermission(QString);
    int getCredit();
    void setCredit(int);
    //enterOrder(Order);
    //buy(Order);
    //sell(Order);
    //modify(Order);

private:
    QString username;
    QString password;
    long traderID;
    QString permission;
    int credit;
};

#endif // MEX_TRADER_H
