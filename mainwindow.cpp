#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_1_clicked()
{
    ui->lineEdit->insert("1");
}


void MainWindow::on_pushButton_2_clicked()
{
    ui->lineEdit->insert("2");
}

void MainWindow::on_pushButton_3_clicked()
{
    ui->lineEdit->insert("3");
}

void MainWindow::on_pushButton_4_clicked()
{
    ui->lineEdit->insert("4");
}

void MainWindow::on_pushButton_5_clicked()
{
    ui->lineEdit->insert("5");
}

void MainWindow::on_pushButton_6_clicked()
{
    ui->lineEdit->insert("6");
}

void MainWindow::on_pushButton_7_clicked()
{
    ui->lineEdit->insert("7");
}

void MainWindow::on_pushButton_8_clicked()
{
    ui->lineEdit->insert("8");
}

void MainWindow::on_pushButton_9_clicked()
{
    ui->lineEdit->insert("9");
}

void MainWindow::on_pushButton_0_clicked()
{
    ui->lineEdit->insert("0");
}

void MainWindow::on_pushButton_back_clicked()
{
    if (
            ui->lineEdit->text().length() == 0 ||
            ui->lineEdit->text().at(ui->lineEdit->text().length()-1) == '-' ||
            ui->lineEdit->text().indexOf('.') != -1
            )
    {
        return;
    }
    ui->lineEdit->setText(ui->lineEdit->text()+'.');
}

void MainWindow::on_pushButton_equals_clicked()
{
    if (ui->lineEdit->text().length() != 0 && stack.length() == 2) {stack.push(ui->lineEdit->text());}  //если есть 1 операнд и знак и в строке лайн едит не пусто, то помещаем из ле в стек
    if (stack.length() < 3) {return;}                       // если пусто то ничего не выполняем
    double val2 = stack.pop().toDouble();           // достаем из стека операнды  и знак
    QString sign = stack.pop();
    double val1 = stack.pop().toDouble();
    if (sign == "+") {                              // в стек помещаем результат действия
        stack.push(QString::number(val1+val2));
    } else if (sign == "-") {
        stack.push(QString::number(val1-val2));
    } else if (sign == "*") {
        stack.push(QString::number(val1*val2));
    } else if (sign == "/") {
        if (val2 == 0) {                // если делим на ноль, то возвращаем 1 операнд и знак обратно в стек, а лайн едит очищаем , чтобы можно было ввести новый делитель
            stack.push(QString::number(val1));
            stack.push(sign);
            ui->lineEdit->clear();
            return;
        }
        stack.push(QString::number(val1/val2));
    }
    ui->lineEdit->setText(stack.pop());             // из стека в лайн едит
    ui->lineEdit_2->setText(stack.toList().join(""));
}

void MainWindow::on_pushButton_plus_clicked()
{
    calculate("+");                 // передаем аргумент в функцию калк
}

void MainWindow::on_pushButton_minus_clicked()
{
    calculate("-");
}

void MainWindow::on_pushButton_mul_clicked()
{
    calculate("*");
}

void MainWindow::on_pushButton_div_clicked()
{
    calculate("/");
}

void MainWindow::on_pushButton_cancel_clicked()
{
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    stack.clear();
}

void MainWindow::on_pushButton_sign_clicked()
{
    if (ui->lineEdit->text().length() == 0 || ui->lineEdit->text().at(0) != '-') {
        ui->lineEdit->setText("-"+ui->lineEdit->text());
    } else {
        ui->lineEdit->setText(ui->lineEdit->text().remove(0,1));
    }
}
void MainWindow::calculate(QString sgn) {                   // функция отвечает за арифметические действие
    if (ui->lineEdit->text().length() == 0) {return;}       // если нихрена не введено то нехрен выполянть
    if (stack.length() >= 2) {                              // есди в стеке не менее двух эл-ов то
        double val2 = ui->lineEdit->text().toDouble();  // извлекаем значение второго операнда
        QString sign = stack.pop();                     // извлекаем знак арифм операции с вершины стека
        double val1 = stack.pop().toDouble();       // извлекаем значение первого операнда
        if (sign == "+") {
        stack.push(QString::number(val1+val2)); // помещаем в стек результат соотв операции
        } else if (sign == "-") {
            stack.push(QString::number(val1-val2));
        } else if (sign == "*") {
            stack.push(QString::number(val1*val2));
        } else if (sign == "/") {
            if (val2 == 0) {
                stack.push(QString::number(val1));
            } else {
            stack.push(QString::number(val1/val2));
            }
        }
        stack.push(sgn);                // помещаем только что нажатый знак
    } else {
        stack.push(ui->lineEdit->text());   //если в стеке ещё ничего не было , то помещаем значение и знак
        stack.push(sgn);
    }
    ui->lineEdit->clear();
    ui->lineEdit_2->setText(stack.toList().join(""));       // перезаписываем в верхний лайн едит новые значения первого операнда и знака. преобр к листу. джоин собирает в строку
}
