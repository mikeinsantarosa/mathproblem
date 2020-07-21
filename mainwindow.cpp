#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QRandomGenerator>
#include <QDebug>
#include "random.hpp"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    _busy = true;

    dblValidator = new QDoubleValidator();
    dblValidator->setNotation(QDoubleValidator::ScientificNotation);
    dblValidator->setRange(-9.9E19, 9.9E19,12);
    ui->lineMin->setValidator(dblValidator);
    ui->lineMax->setValidator(dblValidator);

    _defaultPositionsRI << "Padding Value"  << "Baseline" << "0° Horiz" << "0° Vert" << "90° Horiz"
                      << "90° Vert" << "180° Horiz" << "180° Vert" << "270° Horiz" << "270° Vert";

    setControlsToDefault();

    _busy = false;
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btnTest_clicked()
{
   double min, max;
   //double value;

   if (_masterList.count() > 0)
   {
       _masterList.clear();
   }


   int rows = getNumberOfRows();
   int cols = getNumberOfColumns();

   min = ui->lineMin->text().toDouble();
   max = ui->lineMax->text().toDouble();

   _values.clear();
   ui->listValues->clear();

   loadFreqList();
//   listThisList(_masterList);

    for (int i = 0; i < cols; ++i)
    {
         QVector<double> dSet = getValueSet(min,max,rows);
         // add the set to the freq list
          AddDataSetToMaster(dSet,rows);

    }

    listThisList(_masterList);




}

void MainWindow::setControlsToDefault()
{

    ui->lineMin->setText("10e-10");
    ui->lineMax->setText("10e-08");
    ui->lineNumberOfRows->setText("255");
    ui->lineNumberOfColumns->setText("1");
    fillTypeList();

    ui->listValues->clear();





}

double MainWindow::getMin()
{
    double yMin = std::numeric_limits<double>::max();

    foreach (double d, _values)
    {
        yMin = qMin(yMin, d);
    }

    return yMin;
}

double MainWindow::getMax()
{

    double yMax = std::numeric_limits<double>::min();
    foreach (double d, _values)
    {
        yMax = qMax(yMax, d);
    }

    return yMax;
}

void MainWindow::fillList()
{
    if(_values.count() > 0)
    {
        for(int i=0; i < _values.count(); i++)
        {
            ui->listValues->addItem(QString::number(_values.at(i)));
        }

        ui->listValues->sortItems(Qt::AscendingOrder);
    }
}

void MainWindow::fillTypeList()
{
    ui->comboDataType->addItem(_TestTypes[0]);
    ui->comboDataType->addItem(_TestTypes[1]);
}

int MainWindow::getNumberOfRows()
{

    _numberOfRows = _numbersOfRows[getDataType()];

    return _numberOfRows;

}

int MainWindow::getNumberOfColumns()
{
    int result = 1;

    if(_numberOfColumns > 0 && _numberOfColumns <= 9)
    {
        result = _numberOfColumns;
    }

    return result;
}

int MainWindow::getDataType()
{
    return _dType;
}

void MainWindow::setNumberOfColumns(int value)
{
    if(value >= _minNumberOfColumns && value <= _maxNumberOfColumns)
    {
        _numberOfColumns = value;
    }
    else
    {
        qDebug() << " value " << value << " is not between " << _minNumberOfColumns << " and " << _maxNumberOfColumns;
    }
}

void MainWindow::loadFreqList()
{
    double startFreq = getMinFreq();
    double lastFreq = getLastFreq();
    double value;
    int lastIndex = getNumberOfRows();
    for (int i=0; i < lastIndex; i++)
    {
        _masterList.append(QString::number(startFreq));

        value = startFreq * _freqMultiplier;

        if (value > lastFreq)
        {
            startFreq = lastFreq;
        }
        else
        {
            startFreq = value;
        }

    }
}

double MainWindow::getMinFreq()
{
    return _startFreqs[getDataType()];
}

double MainWindow::getLastFreq()
{
    return _lastFreqs[_dType];
}

void MainWindow::listThisList(QStringList list)
{
    int last = list.count();
    for (int i = 0;i < last;i++)
    {
        qDebug() << "value " << i << " is " << list.at(i);
    }
}


void MainWindow::on_lineNumberOfColumns_editingFinished()
{
    int value = ui->lineNumberOfColumns->text().toInt();
    qDebug() << "Set number of columns to " << value;
    _numberOfColumns = value;
}



void MainWindow::on_comboDataType_currentIndexChanged(int index)
{
    _dType = index;
    ui->labelRunIndicator->setText(_TestTypes[_dType]);
}

QVector<double> MainWindow::getValueSet(double min, double max, int rows)
{
    QVector<double> newValues;

    double value;
    for (int i = 0; i < rows; ++i)
    {
        value = Random::get(min, max);
        newValues << value;
    }

    return newValues;

}

void MainWindow::AddDataSetToMaster(QVector<double> dSet, int rows)
{
    QString temp = "";
    for (int i = 0; i < rows; i++)
    {
        temp = _masterList.at(i) + _delimiter + QString::number(dSet.at(i));
        _masterList[i] = temp;
    }


}
