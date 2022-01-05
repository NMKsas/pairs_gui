#include "mainwindow.hh"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)

{
    ui->setupUi(this);    

    // Showing the start page
    ui->stackedWidget->setCurrentIndex(0);
    ui->playerNamesGridLayout->setVerticalSpacing(10);

    // Connecting buttons and spinboxes to different functions
    connect(ui->startPushButton, &QPushButton::clicked,
            this, &MainWindow::onStartPushButtonClicked);
    connect(ui->quitPushButton, &QPushButton::clicked, this,
            &MainWindow::onQuitPushButtonClicked);
    connect(ui->playersSpinBox, qOverload<int>(&QSpinBox::valueChanged),
            this, &MainWindow::onPlayersSpinBoxValueChanged);
    connect(ui->pairsSpinBox, qOverload<int>(&QSpinBox::valueChanged),
            this, &MainWindow::onPairsSpinBoxValueChanged);
    connect(ui->newGamePushButton, &QPushButton::clicked,
            this, &MainWindow::onNewGameButtonClicked);
    connect(ui->gameOnPushButton, &QPushButton::clicked,
            this, &MainWindow::onGameOnButtonClicked);

    ui->gameOnPushButton->setFixedSize(DEFAULT_LABEL_WIDTH,
                                       DEFAULT_LABEL_HEIGHT);


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::onStartPushButtonClicked()
{
    // set page to playerNamesPage
    ui->stackedWidget->setCurrentIndex(1);

    // player page is generated according to user input
    initPlayerPage();

    // rows and columns for gameboard are initialized
    initRowsAndColumns();
}

void MainWindow::onPlayersSpinBoxValueChanged()
{

    players_amount = ui->playersSpinBox->value();

}


void MainWindow::onQuitPushButtonClicked()
{
    if (!players_.empty()){
        deletePlayers();
    }

    close();
}

void MainWindow::onPairsSpinBoxValueChanged()
{

    cards_amount = ui->pairsSpinBox->value() * 2;

}


void MainWindow::onGameOnButtonClicked()
{
    // setting current page to gameBoardPage
    ui->stackedWidget->setCurrentIndex(2);

    // Creating players and cards
    initPlayers();
    initCards();

}

void MainWindow::onCardButtonClicked()
{

    QPushButton* card_sender = qobject_cast<QPushButton*>(sender());
    std::map<QPushButton*,std::shared_ptr<Card>>::iterator
            card_iter = cards_.find(card_sender);

    // the clicked card is turned and added to chosen pair
    card_iter->second->turnCard();
    chosen_pair_.push_back(card_iter->second);

    //  only one card is turned, returns
    if (chosen_pair_.size() == 1 ){
        return;
    }

    // a pair has been turned, other card buttons are disabled
    setDisableAllCards(true);

    // delay, to let user view cards
    QTimer::singleShot(DELAY, this, SLOT(turnCards()));

}

void MainWindow::initCards()
{

    std::string cards_string = createCardString();
    std::string::iterator card_it = cards_string.begin();

    // creating the gameboard, initializing card objects
    for ( unsigned int row = 0; row < rows_; ++row){

        for ( unsigned int column = 0; column < columns_; ++column ){

            // elements for new Card object
            QPushButton* card_button = new QPushButton(this);
            QLabel* card_image = new QLabel(this);
            std::shared_ptr<Card> new_card (new Card(card_button,
                                                     (*card_it),card_image));

            connect(card_button, &QPushButton::clicked, this,
                    &MainWindow::onCardButtonClicked);

            // adding card buttons and its image label to grid layout
            ui->gameBoardGridLayout->addWidget(card_image,row,column,
                                               Qt::AlignCenter);
            ui->gameBoardGridLayout->addWidget(card_button, row,
                                               column, Qt::AlignCenter);

            // adding cards to container
            cards_.insert({card_button,new_card});
            ++card_it;

        }

    }

}

void MainWindow::initRowsAndColumns()
{

    // creating rows and columns, by finding the greatest common divisor
    for (unsigned int i = 1; i * i <= cards_amount; ++i){

        if (cards_amount % i == 0){
            rows_ = i;
        }
    }
    columns_ = cards_amount / rows_;

}

void MainWindow::initPlayerPage()
{

    // Title for asking the player names
    QLabel* title_label = new QLabel("Enter player names",this);
    title_label->setFixedSize(DEFAULT_LABEL_WIDTH,DEFAULT_LABEL_HEIGHT);
    title_label->setAlignment(Qt::AlignCenter);
    ui->playerNamesGridLayout->addWidget(title_label);

    // creating widgets for user's input (player names)
    // according to amount of players
    for (unsigned int player_number = 1; player_number <= players_amount;
         ++player_number){

        // Creating label, adding to GridLayout
        QLabel* player_label = new QLabel("Player " +
                                          QString::number(player_number), this);
        player_label->setFixedSize(DEFAULT_LABEL_WIDTH,DEFAULT_LABEL_HEIGHT);
        ui->playerNamesGridLayout->addWidget(player_label);

        // Creating lineEdit element for user input, adding to GridLayout
        QLineEdit* enter_name = new QLineEdit(this);
        enter_name->setFixedSize(DEFAULT_LABEL_WIDTH,DEFAULT_LABEL_HEIGHT);
        ui->playerNamesGridLayout->addWidget(enter_name);

        // storing line edit elements to later use
        player_names_.push_back(enter_name);

    }


}

void MainWindow::initPlayers()
{

    int player_counter = 1;    

    // creating new Player -objects, according to user input
    for (auto player_name : player_names_){

        // Default player name and number
        QString name = DEFAULT_NAME + QString::number(player_counter);

        // if user has inserted a specific name, it is used
        if (!player_name->text().isEmpty()){
            name = player_name->text();
        }

        // creating graphic elements for GUI and Player -object
        Player* new_player = new Player(name, new QLCDNumber(this),
                                        new QLabel(this));

        // if previous player exists, new player is linked to it
        if (!players_.empty()){
            players_.back()->setNextPlayer(new_player);
        }
        players_.push_back(new_player);
        ++player_counter;

    }

    // creating corresponding status boxes
    initStatusBoxes();


}

void MainWindow::initStatusBoxes()
{

    // first in turn is chosen, highlighted by bold font
    in_turn_ = players_.at(0);
    in_turn_->setLabelStyle(true);

    int row_count = 1;

    // Adding each player's name and score LCDNumber to Scores -list
    for (auto player : players_){

        QLabel* player_label = player->getLabel();
        player_label->setFixedSize(NAME_LABEL_WIDTH,DEFAULT_LABEL_HEIGHT);
        ui->playerStatusGridLayout->addWidget(player_label, row_count,
                                              1, Qt::AlignCenter);
        ui->playerStatusGridLayout->addWidget(player->getScoreLCD(), row_count,
                                              2, Qt::AlignCenter);
        ++row_count;
    }

}

void MainWindow::changePlayerInTurn()
{
    // previous-in-turn's label style is changed to normal
    in_turn_->setLabelStyle(false);

    // choosing next in turn
    if (in_turn_->getNextPlayer() == nullptr){
        in_turn_ = players_.at(0);
    } else {
        in_turn_ = in_turn_->getNextPlayer();
    }

    // highlighting the (new) player in turn's label
    in_turn_->setLabelStyle(true);

}

void MainWindow::removeFromGameBoard(std::shared_ptr<Card> card)
{ 

    // card is removed from the board, erased from the cards container
    card->removeCard();
    cards_.erase(card->getButton());

}

bool MainWindow::isPairFound()
{
    // if card IDs are the same, pair is found
    if (chosen_pair_.at(0)->getID() != chosen_pair_.at(1)->getID()){
        return false;
    }
    return true;
}

void MainWindow::setDisableAllCards(bool isEnabled)
{
    // if cards are enabled, they are disabled; and vice versa
    for (auto& card : cards_){

        if (isEnabled){
            card.first->setDisabled(true);
        } else {
            card.first->setEnabled(true);
        }

    }
}

bool MainWindow::isGameOver()
{

    if (!cards_.empty()){
        return false;
    }

    // no cards are left, game over
    return true;
}

void MainWindow::endGame()
{
    // changing page to Game Over page
    ui->stackedWidget->setCurrentIndex(3);

    // generating game over message, adding it to the layout's label
    QString message = generateGameOverMessage();
    ui->gameOverMessageLabel->setText(message);

    // shifting quit button from page 1 to current page
    ui->gameOverGridLayout->addWidget(ui->quitPushButton,2,1);

}

void MainWindow::clearGridLayout(QGridLayout* layout)
{
    // deleting all the elements in the grid layout
    while (layout->count() !=0){
        QLayoutItem* item = layout->takeAt(0);
        delete item->widget();
        delete item;
    }

}

void MainWindow::deletePlayers()
{
    // deleting all the dynamically created players
    Player* first_player = players_.at(0);
    players_.clear();
    while (first_player != nullptr){
        Player* removal = first_player;
        first_player = first_player->getNextPlayer();
        delete removal;
    }
}


std::unordered_set<Player *> MainWindow::findWinners()
{

    std::unordered_set<Player*> winners;
    int highest_score = 0;

    // finding out the highest score among the players
    for ( auto player : players_ ){

        if (player->getNumberOfPairs() > highest_score){
            winners.clear();

            highest_score = player->getNumberOfPairs();
            winners.insert(player);
        }

        // two players have the same highest score
        if (player->getNumberOfPairs() == highest_score){
            winners.insert(player);
        }

    }

    // adding highest score to attributes
    winning_score_ = highest_score;
    return winners;

}

QString MainWindow::generateGameOverMessage()
{

    // finding the winners and the highest score
    std::unordered_set<Player*> winners = findWinners();
    QString win_score = QString::number(winning_score_);
    QString congratulation;

    // If many winners
    if (winners.size()!= 1){
        congratulation = TIE;
        for ( auto player : winners ){
            congratulation.append( player->getName() + " ");
        }
        congratulation.remove(-1,1);
        congratulation.append("! ");

    // only one winner
    } else {
        congratulation = GAMEOVER_TEXT + "\n";
        congratulation.append(" " + (*winners.begin())->getName());
        congratulation.append(WINNER);
        congratulation.append(win_score);
        congratulation.append(". ");
    }

    congratulation.append("\n" +NEW_GAME);

    return congratulation;
}

void MainWindow::turnCards()
{

    std::shared_ptr<Card> first_card = chosen_pair_.at(0);
    std::shared_ptr<Card> second_card = chosen_pair_.at(1);

    // pair not found - next player gets the turn, chosen pair is turned back
    if (!isPairFound()){

        changePlayerInTurn();
        first_card->turnCard(false);
        second_card->turnCard(false);

    // pair is found - player gets the card, card is removed from the board
    } else {

        in_turn_->addPair();
        removeFromGameBoard(first_card);
        removeFromGameBoard(second_card);

    }

    // all cards are enabled again, chosen pair vector cleared
    setDisableAllCards(false);
    chosen_pair_.clear();

    if (isGameOver()){
        endGame();
    }
}

void MainWindow::onNewGameButtonClicked()
{
    // shifting quit button back to start page
    ui->menuGridLayout->addWidget(ui->quitPushButton, 3,1);
    // shifting view to startPage
    ui->stackedWidget->setCurrentIndex(0);


    // Deleting old LineEdit and Label items, cleaning all grid layouts
    clearGridLayout(ui->playerNamesGridLayout);
    player_names_.clear();

    clearGridLayout(ui->gameBoardGridLayout);
    cards_.clear();

    clearGridLayout(ui->playerStatusGridLayout);

    // Deleting old players
    deletePlayers();

}

std::string MainWindow::createCardString()
{
    std::mt19937 rng
            (std::chrono::steady_clock::now().time_since_epoch().count());
    std::string cards_string = "";


    // creating a string with each character duplicated
    char last_card = 65 + (cards_amount/2);
    for ( char c = 65; c < last_card; ++c ){
        cards_string += c;
        cards_string += c;
    }

    // shuffling the card IDs, to create a random order
    shuffle(cards_string.begin(), cards_string.end(),rng);

    return cards_string;

}

