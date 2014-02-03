#include <QTime>
#include <QPainter>
#include <QDebug>
#include <QPrinter>
#include <QPrintDialog>

#include "WMain.h"
#include "ui_WMain.h"

//******************************************************************************
// DEFINES.
//******************************************************************************

/// Width of table cell.
#define TABLE_CELL_W    40
/// Height of table cell.
#define TABLE_CELL_H    40
/// Size of text in table.
#define TABLE_TEXT_SIZE 24

//******************************************************************************
// CONSTRUCTOR AND DESTRUCTOR.
//******************************************************************************

WMain::WMain(QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui::WMain),
    names(11),
    letters(11)
{
    // Setting up UI.
    ui -> setupUi(this);

    // Creating labels for scroll areas.
    ui -> sa_task -> setWidget(new QLabel);
    ui -> sa_checker -> setWidget(new QLabel);

    // Setting up names vector.
    names[0]  = {tr("a"), tr("i"), tr("u"), tr("e"),  tr("o")};
    names[1]  = {tr("ka"), tr("ki"), tr("ku"), tr("ke"), tr("ko")};
    names[2]  = {tr("sa"), tr("shi"), tr("su"), tr("se"), tr("so")};
    names[3]  = {tr("ta"), tr("chi"), tr("tsu"), tr("te"), tr("to")};
    names[4]  = {tr("na"), tr("ni"), tr("nu"), tr("ne"), tr("no")};
    names[5]  = {tr("ha"), tr("hi"), tr("fu"), tr("he"), tr("ho")};
    names[6]  = {tr("ma"), tr("mi"), tr("mu"), tr("me"), tr("mo")};
    names[7]  = {tr("ya"), tr("yu"), tr("yo")};
    names[8]  = {tr("ra"), tr("ri"), tr("ru"), tr("re"), tr("ro")};
    names[9]  = {tr("wa"), tr("wi"), tr("we"), tr("wo")};
    names[10] = {tr("n")};

    // Setting up letters vector.
    letters[0]  = {"あ", "い", "う", "え", "お"};
    letters[1]  = {"か", "き", "く", "け", "こ"};
    letters[2]  = {"さ", "し", "す", "せ", "そ"};
    letters[3]  = {"た", "ち", "つ", "て", "と"};
    letters[4]  = {"な", "に", "ぬ", "ね", "の"};
    letters[5]  = {"は", "ひ", "ふ", "へ", "ほ"};
    letters[6]  = {"ま", "み", "む", "め", "も"};
    letters[7]  = {"や", "ゆ", "よ"};
    letters[8]  = {"ら", "り", "る", "れ", "ろ"};
    letters[9]  = {"わ", "ゐ", "ゑ", "を"};
    letters[10] = {"ん"};
}

WMain::~WMain()
{
    delete ui -> sa_task -> widget();
    delete ui -> sa_checker -> widget();
    delete ui;
}

//******************************************************************************
// SLOTS.
//******************************************************************************

void WMain::generateTables()
{
    // Amount of columns and rows.
    uint columns = ui -> sb_columns -> value();
    uint rows    = ui -> sb_rows    -> value();

    // Creating pixmaps.
    table = QPixmap(2 * columns * TABLE_CELL_W + 1, rows * TABLE_CELL_H + 1);
    checker = QPixmap(table.size());

    // Filling up 'em with white.
    table.fill();
    checker.fill();

    // Creating painters.
    QPainter p_table(&table);
    QPainter p_checker(&checker);

    // Setting up font size.
    QFont font = p_table.font();
    font.setPixelSize(TABLE_TEXT_SIZE);
    p_table.setFont(font);
    p_checker.setFont(font);

    // Array with available columns.
    std::vector<uint> column_array;
    if (ui -> cb_0 -> isChecked())  column_array.push_back(0);
    if (ui -> cb_1 -> isChecked())  column_array.push_back(1);
    if (ui -> cb_2 -> isChecked())  column_array.push_back(2);
    if (ui -> cb_3 -> isChecked())  column_array.push_back(3);
    if (ui -> cb_4 -> isChecked())  column_array.push_back(4);
    if (ui -> cb_5 -> isChecked())  column_array.push_back(5);
    if (ui -> cb_6 -> isChecked())  column_array.push_back(6);
    if (ui -> cb_7 -> isChecked())  column_array.push_back(7);
    if (ui -> cb_8 -> isChecked())  column_array.push_back(8);
    if (ui -> cb_9 -> isChecked())  column_array.push_back(9);
    if (ui -> cb_10 -> isChecked()) column_array.push_back(10);

    // WTF?
    if (column_array.size() == 0)
        return;

    // Initializing random.
    qsrand(QTime::currentTime().secsTo(QTime()));

    // Creating tables.
    for (uint i = 0; i < columns; i++)
        for (uint j = 0; j < rows; j++)
        {
            // Generating index.
            int index_1 = column_array[qrand() % column_array.size()];
            int index_2 = qrand() % names[index_1].size();

            // Preparing rectangles.
            QRect r_left(2 * i * TABLE_CELL_W, j * TABLE_CELL_H,
                         TABLE_CELL_W,         TABLE_CELL_H);
            QRect r_right((2 * i + 1) * TABLE_CELL_W, j * TABLE_CELL_H,
                          TABLE_CELL_W,               TABLE_CELL_H);

            // Drawing on table.
            p_table.drawText(r_left,
                             Qt::AlignCenter | Qt::AlignHCenter,
                             names[index_1][index_2]);
            p_table.drawRect(r_left);
            p_table.drawRect(r_right);

            // Drawing on checker.
            p_checker.drawText(r_left,
                               Qt::AlignCenter | Qt::AlignHCenter,
                               names[index_1][index_2]);
            p_checker.drawText(r_right,
                               Qt::AlignCenter | Qt::AlignHCenter,
                               letters[index_1][index_2]);
            p_checker.drawRect(r_left);
            p_checker.drawRect(r_right);
        }

    // Saving pictures (for debug).
    #ifdef QT_DEBUG
        table.save("table.png", "png");
        checker.save("checker.png", "png");
    #endif

    // We're ready now!
    ((QLabel*) ui -> sa_task    -> widget()) -> setPixmap(table);
    ((QLabel*) ui -> sa_checker -> widget()) -> setPixmap(checker);
    ui -> t_task    -> setEnabled(true);
    ui -> t_checker -> setEnabled(true);
}

void WMain::printTable()
{
    // Preparing.
    QPrinter printer;
    printer.setOrientation(QPrinter::Landscape);
    QPrintDialog dialog(&printer, this);

    // Setting up margins.
    printer.setPageMargins(12.5, 12.5, 12.5, 12.5, QPrinter::Millimeter);

    // Printing.
    if (dialog.exec() == QDialog::Accepted)
    {
        QPainter painter(&printer);
        painter.drawPixmap(0, 0, table);
        painter.end();
    }
}

void WMain::printChecker()
{
    // Preparing.
    QPrinter printer;
    printer.setOrientation(QPrinter::Landscape);
    QPrintDialog dialog(&printer, this);

    // Setting up margins.
    printer.setPageMargins(12.5, 12.5, 12.5, 12.5, QPrinter::Millimeter);

    // Printing.
    if (dialog.exec() == QDialog::Accepted)
    {
        QPainter painter(&printer);
        painter.drawPixmap(0, 0, checker);
        painter.end();
    }
}
