#ifndef WMAIN_H
#define WMAIN_H

#include <QMainWindow>

namespace Ui {
class WMain;
}

/**
 * @brief Main window.
 */
class WMain : public QMainWindow
{
    Q_OBJECT

    //**************************************************************************
    // CONSTRUCTOR AND DESTRUCTOR.
    //**************************************************************************

    public:

        /**
         * @brief Constructor.
         * @param parent    parent widget
         */
        explicit WMain(QWidget *parent = 0);

        /**
         * @brief Destructor.
         */
        ~WMain();

    //**************************************************************************
    // SLOTS.
    //**************************************************************************

    public slots:

        /**
         * @brief Generates tables.
         */
        void generateTables();

        /**
         * @brief Prints table.
         */
        void printTable();

        /**
         * @brief Prints checker table.
         */
        void printChecker();

    //**************************************************************************
    // ATTRIBUTES.
    //**************************************************************************

    private:

        /// UI.
        Ui::WMain *ui;

        /// Vector with letters names.
        std::vector< std::vector<QString> > names;
        /// Vector with letters themselves.
        std::vector< std::vector<QString> > letters;

        /// Pixmap with table.
        QPixmap table;
        /// Pixmap with checker.
        QPixmap checker;
};

#endif // WMAIN_H
