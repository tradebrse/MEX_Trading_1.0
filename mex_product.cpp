#include "mex_product.h"

MEX_Product::MEX_Product()
{
}

MEX_Product::~MEX_Product()
{

}
//Getter Methods
QString MEX_Product::getName()
{
    return this->name;
}

QString MEX_Product::getSymbol()
{
    return this->symbol;
}

//Setter Methods
void MEX_Product::setName(QString name)
{
    this->name = name;
}

void MEX_Product::setSymbol(QString symbol)
{
    this->symbol = symbol;
}

bool MEX_Product::operator==(const MEX_Product &product) const
{
    if(product.name == name && product.symbol == symbol)
    {
        return true;
    }
    else
    {
        return false;
    }
}
