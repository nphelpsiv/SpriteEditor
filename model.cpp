#include "model.h"
#include <iostream>

using namespace std;
Model::Model(QObject *parent) : QObject(parent)
{

}
void Model::undoButtonClicked()
{
    cout << "undoClick (model)" << endl;
}

void Model::redoButtonClicked()
{
    cout << "redoClick (model)" << endl;
}

void Model::penButtonClicked()
{
    cout << "pen (model)" << endl;
}

void Model::eraserButtonClicked()
{
    cout << "eraser (model)" << endl;
}

void Model::rectButtonClicked()
{
    cout << "rectum (model)" << endl;
}

void Model::lineButtonClicked()
{
    cout << "line (model)" << endl;
}

void Model::colorPickerButtonClicked()
{
    cout << "colorP (model)" << endl;
}

void Model::colorCasterButtonClicked()
{
    cout << "ColorC (model)" << endl;
}

void Model::bucketButtonClicked()
{
    cout << "bucket (model)" << endl;
}

void Model::mirrorButtonClicked()
{
    cout << "mirror (model)" << endl;
}

void Model::rotateButtonClicked()
{
    cout << "rotate (model)" << endl;
}

void Model::flipButtonClicked()
{
    cout << "flip (model)" << endl;
}

void Model::previewButtonClicked()
{
    cout << "preview (model)" << endl;
}

void Model::addFrameButtonClicked()
{
    cout << "addF (model)" << endl;
}

void Model::duplicateFrameButtonClicked()
{
    cout << "dupF (model)" << endl;
}

void Model::removeFrameButtonClicked()
{
    cout << "removeF (model)" << endl;
}

void Model::saveButtonClicked()
{
    cout << "Save button (model)" << endl;
}
