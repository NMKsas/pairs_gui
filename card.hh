/* Class Card
 * ----------
 * COMP.CS.110 SPRING 2021
 * ----------
 * Represents a single card in pairs (memory) game.
 * Card's attributes include pointers to assigned QPushButton in the GUI,
 * as well as card's front and back images, and pointer to the assigned Label.
 *
 * Program author: NMKsas
*/

#ifndef CARD_HH
#define CARD_HH

#include <QPushButton>
#include <QLabel>

const int DEFAULT_WIDTH = 60;
const int DEFAULT_HEIGHT = 90;


class Card
{
    public:

        // constructor
        Card(QPushButton* button, char card_id, QLabel* card_image);

        // returns card's id character
        char getID() const;

        // returns the button assigned to the card
        QPushButton* getButton() const;

        // disables card and changes it transparent
        void removeCard() const;

        // sets card's deck and pair images
        void setCardPixmaps();

        // turns card; changes the card label image
        void turnCard(bool is_closed = true);

    private:

        // source for images
        const std::string PREFIX = ":/resources/Images/";
        const std::string SUFFIX = ".png";

        char card_id_;
        int card_height_ = DEFAULT_HEIGHT;
        int card_width_ = DEFAULT_WIDTH;

        // assigned QWidgets in the GUI
        QPushButton* card_button_;
        QLabel* card_image_;

        // image pixmaps for deck and pair images
        QPixmap deck_image_;
        QPixmap pair_image_;

};

#endif // CARD_HH
