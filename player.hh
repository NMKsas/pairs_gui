/* Class: Player
 * -------------
 *  * COMP.CS.110 SPRING 2021
 * -------------
 * Represents a single player in pairs (memory) game. The class includes
 * pointers to the assigned GUI widgets of the Player.
 *
 * Program author: NMKsas
*/

#ifndef PLAYER_HH
#define PLAYER_HH

#include <QString>
#include <QLCDNumber>
#include <QLabel>


const int DEFAULT_PAIRS = 0;

class Player
{
public:

    // Constructor: creates a player with the given name.
    Player(const QString& name, QLCDNumber* score, QLabel* name_label);


    // Returns the name of the player.
    QString getName()const;

    // Returns the LCDNumber element, containing the score
    QLCDNumber* getScoreLCD() const;

    // Returns the player label element, containing the name
    QLabel* getLabel() const;

    // Returns the number of pairs collected by the player so far.
    int getNumberOfPairs() const;

    // Setting label style to indicate player in turn
    void setLabelStyle(bool is_in_turn = true) const;

    // sets the next player in game
    void setNextPlayer(Player* next_in_turn);

    // returns the player next in turn
    Player* getNextPlayer() const;

    // adds players cards by one pair
    void addPair();


private:

    QString name_;
    int pairs_total_ = DEFAULT_PAIRS;

    // Pointers to assigned GUI elements
    QLCDNumber* score_status_;
    QLabel* player_label_;

    // Pointer to the next player in turn, if any
    Player* next_player_;

};

#endif // PLAYER_HH
