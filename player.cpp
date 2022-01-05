#include "player.hh"

Player::Player(const QString& name, QLCDNumber* score, QLabel *name_label):
    name_(name), score_status_(score), player_label_(name_label),
    next_player_(nullptr)
{
    player_label_->setText(name_);
}

QString Player::getName() const
{
    return name_;
}

QLCDNumber *Player::getScoreLCD() const
{
    return score_status_;
}

QLabel *Player::getLabel() const
{
    return player_label_;
}

int Player::getNumberOfPairs() const
{
    return pairs_total_;
}

void Player::setLabelStyle(bool is_in_turn) const
{
    // style normalized, if player is not in turn
    if(!is_in_turn){
        player_label_->setText(name_);
        player_label_->setStyleSheet("");
        return;
    }
    // arrow and bold font added, if in turn
    player_label_->setText("-> " + name_);
    player_label_->setStyleSheet({"font-weight: bold"});
}

void Player::setNextPlayer(Player* next_in_turn)
{
    next_player_ = next_in_turn;
}

Player* Player::getNextPlayer() const
{
    return next_player_;
}

void Player::addPair()
{

    // pair is added, GUI LCDNumber element updated accordingly
    pairs_total_+=1;
    score_status_->display(pairs_total_);
}
