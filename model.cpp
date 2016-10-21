#include "model.h"
#include <iostream>

using namespace std;
Model::Model(QObject *parent) : QObject(parent)
{

}
void Model::undoClicked()
{
    cout << "undoClick (model)" << endl;
}
