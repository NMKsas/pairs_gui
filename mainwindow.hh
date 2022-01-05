/* Class: MainWindow
 * -------------
 *  * COMP.CS.110 SPRING 2021
 * -------------
 * Represents the GUI of the pairs (memory) game.
 *
 * Program author: NMKsas
*/


#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include "card.hh"
#include "player.hh"

#include <QStackedWidget>
#include <QLineEdit>
#include <QMainWindow>
#include <algorithm>
#include <random>
#include <chrono>
#include <vector>
#include <map>
#include <unordered_set>
#include <QPushButton>
#include <QLineEdit>
#include <QTimer>
#include <QTextBrowser>
#include <QLCDNumber>
#include <QGridLayout>
#include <memory>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

const unsigned int DEFAULT_PLAYERS = 2;
const unsigned int DEFAULT_CARDS = 4;
const unsigned int DEFAUL_ROWS = 2;
const unsigned int DEFAULT_COLUMNS = 2;
const int NO_SCORE = 0;

const QString DEFAULT_NAME = "Player ";
const QString GAMEOVER_TEXT = "Congratulations!";
const QString TIE = "No winners today! It's a tie between players ";
const QString WINNER = " wins with the score ";
const QString NEW_GAME = "Do you want to start a new game?";

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onStartPushButtonClicked();
    void onPlayersSpinBoxValueChanged();
    void onQuitPushButtonClicked();
    void onPairsSpinBoxValueChanged();
    void onGameOnButtonClicked();
    void onCardButtonClicked();
    void turnCards();
    void onNewGameButtonClicked();

private:
    Ui::MainWindow *ui;

    const int DELAY = 2000;      // how many milliseconds a card is shown
    const int DEFAULT_LABEL_WIDTH = 350;
    const int DEFAULT_LABEL_HEIGHT = 20;
    const int NAME_LABEL_WIDTH = 200;

    // containers for gameboard structure
    unsigned int cards_amount = DEFAULT_CARDS;
    unsigned int players_amount = DEFAULT_PLAYERS;
    unsigned int rows_ = DEFAUL_ROWS;
    unsigned int columns_ = DEFAULT_COLUMNS;

    // Creates widgets for asking player names on playerNamesPage
    void initPlayerPage();

    // Creates new players according to user input
    void initPlayers();

    // Creating a status box for each player on gameBoardPage
    void initStatusBoxes();

    // defining rows and columns according to the card amount
    void initRowsAndColumns();

    // creates a string to give each pair a character ID
    std::string createCardString();

    // Creating card objects
    void initCards();

    // disables or enables all card push buttons
    void setDisableAllCards(bool isEnabled = true);

    // pair is removed from the gameboard and cards container
    void removeFromGameBoard(std::shared_ptr<Card>);

    // if pair is found, returns true
    bool isPairFound();

    void changePlayerInTurn();

    // if all cards are turned, returns true
    bool isGameOver();

    // generates contents to gameOverPage
    void endGame();

    // clears the grid layout from its elements
    void clearGridLayout(QGridLayout* layout);

    // deletes dynamically created players
    void deletePlayers();

    // creates a set of winners; players who have the highest score
    std::unordered_set<Player*> findWinners();

    // generates a congratulations message for winners
    QString generateGameOverMessage();



    // container for player names as QLineEdit elements
    std::vector<QLineEdit*> player_names_;

    // pointer to player in turn
    Player* in_turn_;

    // all players in adding order
    std::vector<Player*> players_;

    // all card push buttons and pointers to corresponding Card objects
    std::map<QPushButton*,std::shared_ptr<Card>> cards_;

    // two cards that are turned
    std::vector<std::shared_ptr<Card>> chosen_pair_;

    // highest score after the game
    int winning_score_ = NO_SCORE;


};
#endif // MAINWINDOW_HH
