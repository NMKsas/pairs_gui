#include "card.hh"

Card::Card(QPushButton *button, char card_id, QLabel* card_image):
    card_id_(card_id), card_button_(button), card_image_(card_image)
{
    // presets, including fixed sizes, flattening pushbutton
    // setting deck and pair images
    card_button_->setFixedSize(DEFAULT_WIDTH,DEFAULT_HEIGHT);
    card_image_->setFixedSize(DEFAULT_WIDTH,DEFAULT_HEIGHT);
    card_button_->setFlat(true);
    setCardPixmaps();
}

char Card::getID() const
{
    return card_id_;
}

QPushButton* Card::getButton() const
{
    return card_button_;
}

void Card::removeCard() const
{
    // when card is removed, the button is disabled and set transparent,
    // the card image is removed from the image-label
    card_button_->
            setStyleSheet("QPushButton { background-color : transparent }");
    card_button_->setDisabled(true);
    card_image_->clear();

}


void Card::setCardPixmaps()
{

    // Setting deck image from resources
    std::string filename = PREFIX + "deck" + SUFFIX;
    QPixmap deck_image(QString::fromStdString(filename));
    deck_image_ = deck_image.scaled(DEFAULT_WIDTH, DEFAULT_HEIGHT,
                                   Qt::KeepAspectRatio);

    // Setting card's pair image
    filename = PREFIX + card_id_ + SUFFIX;
    QPixmap pair_image(QString::fromStdString(filename));
    pair_image_ = pair_image.scaled(DEFAULT_WIDTH,DEFAULT_HEIGHT,
                                   Qt::KeepAspectRatio);


    card_image_->setPixmap(deck_image_);

}

void Card::turnCard(bool is_closed)
{

    if(is_closed){
        card_button_->hide();
        card_image_->setPixmap(pair_image_);

    } else {
        card_button_->show();
        card_image_->setPixmap(deck_image_);
    }

}
