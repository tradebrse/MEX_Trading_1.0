#ifndef MEX_PRODUCT_H
#define MEX_PRODUCT_H
#include <QString>

using namespace std;

class MEX_Product
{
public:
    MEX_Product(QString name);
    ~MEX_Product();

    QString getName();
    void setName(QString);

private:
    QString name;
};

#endif // MEX_PRODUCT_H
