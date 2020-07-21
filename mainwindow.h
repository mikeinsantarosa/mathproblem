#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QRandomGenerator64>
#include <QtCore>
#include <QDoubleValidator>
#include <limits>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnTest_clicked();
    void setControlsToDefault();

    void on_lineNumberOfColumns_editingFinished();

    void on_comboDataType_currentIndexChanged(int index);

private:
    Ui::MainWindow *ui;
    QDoubleValidator *dblValidator;

    QVector<double> _values;

    QVector<double> getValueSet(double min, double max, int rows);
    void AddDataSetToMaster(QVector<double> dSet, int rows);

    double getMin();
    double getMax();
    void fillList();
    void fillTypeList();

    int getNumberOfRows();
    int getNumberOfColumns();
    int getDataType();
    void setNumberOfColumns(int value);

    void loadFreqList();

    double getMinFreq();
    double getLastFreq();
    double _startFreqs[2] = {80000000,150000};
    double _lastFreqs[2] = {6000000000,80000000};
    int _numbersOfRows[2] = {435,633};

    // debug functions
    void listThisList(QStringList list);


    QVector<double> getSortedList(QVector<double> list);

    QString _delimiter = ",";
    QStringList _defaultPositionsRI;
    QString _TestTypes[3] = {"Radiated Immunity","Conducted Immunity","--end of list--"};

    int _dType = 0;

    int _numberOfColumns;
    int const _minNumberOfColumns = 1;
    int const _maxNumberOfColumns = 9;
    int _numberOfRows;
    int const _minNumberOfRows = 1;
    int const _maxNumberOfRows = 435;

    double const _freqMultiplier = 1.010000;

    QStringList _masterList;


    bool _busy;



};
#endif // MAINWINDOW_H
