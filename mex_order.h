#ifndef MEX_ORDER_H
#define MEX_ORDER_H
#include <QDateTime>
#include <mex_product.h>


class MEX_Order
{
public:
    MEX_Order();
    ~MEX_Order();


public slots:

    //getter


    //setter


    void modify(int value, int quantity);
    void deleteOrder();

private slots:

private:

    QString traderID;
    QString orderID;
    int value;
    int quantity;
    QString comment;
    QDateTime time;
    bool buy;
    bool sell;
    MEX_Product product;
};

#endif // MEX_ORDER_H
