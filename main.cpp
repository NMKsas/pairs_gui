/* PAIRS
 *
 * Desc:
 *
 * This program contains Pairs (memory) game with a simple GUI. The user can
 * choose the amount of players and cards in the beginning, and name the players
 * if needed. The cards are generated into the Gameboard view, and each user can
 * choose pairs by clicking the cards. The one who gets most cards, wins.
 *
 *
 * Program author: NMKsas
 * */



#include "mainwindow.hh"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
