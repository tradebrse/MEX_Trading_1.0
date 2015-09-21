#ifndef MEX_ORDER_H
#define MEX_ORDER_H
#include <QDateTime>
#include <mex_product.h>


class MEX_Order
{
public:
    MEX_Order();
    MEX_Order(QString traderID, int orderID, int value, int quantity, QString comment, MEX_Product *product);
    ~MEX_Order();

    // Getter/Setter methods
    QString getTraderID();
    void setTraderID(QString);
    int getOrderID();
    void setOrderID(int);
    int getValue();
    void setValue(int);
    int getQuantity();
    void setQuantity(int);
    QString getComment();
    void setComment(QString);
    QDateTime getTime();
    MEX_Product *getProduct();
    void setProduct(MEX_Product *);


//public slots:

    //getter


    //setter


    void modify(int value, int quantity);
    void deleteOrder();

//private slots:

private:

    QString traderID;
    int orderID;
    int value;
    int quantity;
    QString comment;
    QDateTime time;
    bool buy;
    bool sell;
    MEX_Product* product;

    //
};

#endif // MEX_ORDER_H
