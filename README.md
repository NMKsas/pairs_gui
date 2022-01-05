# Memory Game

Author: NMKsas <br>
May 2021

*Created as an assignment during Programming II -course in Tampere University.*

<p>&nbsp;</p>

## INSTRUCTIONS 

The game contains four different views
- start page
- player names page
- game board page
- game over page <br>

, which are described in the order they are seen in the game.

### Start Page

Before starting the game, user decides how many players are 
participating the game, and how many cards are used. Player and 
pair amounts are chosen by clicking the arrows up and down near
the corresponding numbers. Total players amount can be chosen 
 between 2-6, while pairs can be chosen from 2 to 20 (= 4-40 cards).
By clicking Start -button, player can proceed to next view. By 
hitting Quit, the program closes.   

### Player Names Page 

After choosing the amount of players and cards, the user can name 
all players separately, by writing names in the shown boxes. 
If boxes are left blank, player will be named by default; 
"Player #", where # is replaced by player number. By hitting 
Game on! -button, player proceeds to the gameboard view. 

### Game Board Page

On left side of the page, all the cards are now shown their picture 
side down, showing only the deck images. On the right side there is a 
score board showing each player's current score. The player in turn is 
indicated by an arrow. Once the game is finished, player proceeds to 
the game over page.

### Game Over Page

On the game over view, user will see who won the game with the most 
points - or whether the game has ended up in a Tie. If user wants to continue
 playing the game, s/he can push the "New game" button, and the view returns
to the Start page. If player wants to quit, s/he can push the quit button,
closing the program.


### GAME RULES: 

The player in turn chooses two cards by clicking them. The cards turn
showing their image -side for two seconds (while other cards cannot be
clicked). If the cards have the same image, the player score adds by +1
and the cards are removed from the game board. The player in turn
remains the same and the game continues.
 
If the chosen cards are different, the cards are turned back (deck side up),
and the next player takes his/her turn. 

The game continues until all the pairs have been found. When all pairs
are found, game ends.


## THE STRUCTURE OF THE GAME

The game is built by using QStackedWidget and creating above mentioned
four pages to it. Some of the GUI -widgets are static (remaining the same
throughout the game), but some are dynamically created during the game round.
Dynamically created elements consist of Player and Card -objects and the 
related GUI-widgets (QLabels, QPushButtons, QLineEdits). 


### Player -class

Player -class has attributes related to the player information; such as 
the name and the amount of pairs the player has collected. Besides this,
Player -class has pointers to its corresponding elements on the GUI;
the QLabel and QLCDNumber element on scores' board (Game Board Page).
As Players are created using raw pointers, each Player object contains 
a pointer to the next player in turn. This attribute is used to 
delete existing players, if the user continues to play the next round.

### Card -class

Cards are created by using smart pointers (shared_ptr), which is why 
they are not manually deleted in the code, but simply removed from the 
related containers. Card class includes some useful methods related to the
game (removeCard(), turnCard()), to modify the card appearance on the game 
board accordingly. 
Each Card has pointers to its related QPushButton and QLabel. Besides this, 
the cards are equipped with a deck image, and a pair image (according to 
the card ID character). 


### MainWindow

MainWindow executes all the necessary functions related to the game, and
constructs the GUI. Some of the GUI's static widget content are constructed
in mainwindow.ui / designer. 

### Images Folder

Images -folder contains all the necessary art created for the GUI - card 
deck images and background photo. All the art (C) author. 


<p>&nbsp;</p>

## NOTES FOR FURTHER DEVELOPMENT

### Known flaws:
- the program doesn't prevent from naming two players with the same name
- GameOverMessageLabel (Game Over Page) doesn't expand as other QWidgets 
