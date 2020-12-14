#include "text_view.h"
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
using namespace std;

View::View (Controller *controller, Board *model) : controller{controller}, model{model} {
    // Attaches the view as an observer of the model board
    model->attach(this);
}

// Default destructor, no cleanup seems to be needed as using smart pointers
View::~View() {}

void View::setPlayers() {
    // Keeps trying to fill players until there are 4 players
    while (model->getPlayers().size() < 4) {
        // Which player are we currently filling: this format for input is based on main file from A5
        unsigned int playernum = model->getPlayers().size() + 1;
        cout << "Is Player" << playernum << " a human (h) or a computer (c)?" << endl;
        string s;
        getline(cin, s);
        istringstream iss{s};
        string ptype;
        iss >> ptype;
        if (ptype == "h") {
            controller->addPlayer(PlayerType::Human);
        } else if (ptype == "c") {
            controller->addPlayer(PlayerType::Computer);
        } else {
            // If neither h nor c have been inputed, ask user to try again
            cout << "Invalid Player Type: You can either input [h]uman or [c]omputer" << endl;
        }
    }
}

void View::nextCommand() {
    // This design for getting input is heavily based on the main file from A5
    string s;
    getline(cin, s);
    istringstream iss{s};
    string cmd;
    iss >> cmd;
    if (cmd == "deck") {
        printDeck();
    } else if (cmd == "ragequit") {
        controller->RageQuit();
    } else if (cmd == "quit") {
        controller->endGame();
    } else if (cmd == "play") {
        try {
                if (iss.eof()) {
                    cerr << "Play failed. Please use play [Card]." << endl;
                } else {
                    // Temporary card that will be read into: default to ace of spade
                    Card playcard(Ace,Spade);
                    iss >> playcard;
                    // Make a play using the given card: true indicates play
                    controller->makeMove(playcard,true);
                }
        } catch ( ArgExn & e ) {
            cerr << e.message << endl;
        }
    } else if (cmd == "discard") {
        try {
                if (iss.eof()) {
                    cerr << "Discard failed. Please use discard [Card]." << endl;
                } else {
                    // Temporary card that will be read into: default to ace of spade
                    Card discardcard(Ace,Spade);
                    iss >> discardcard;
                    // Make a discard using the given card: false indicates discard
                    controller->makeMove(discardcard,false);
                }
        } catch ( ArgExn & e ) {
            cerr << e.message << endl;
        }
    } else {
        std::cerr << "Unrecognized command " << cmd << "!" << std::endl;
    }
}

void View::update(State state) {
    if (state == State::PRINTCARD) {
        printTable();
    } else if (state == State::NEWROUND) {
        int playernum = model->getCurrentPlayer() + 1;
        cout << "A new round has begins. It's Player" << playernum << "'s turn to play." << endl;
    } else if (state == State::RAGEQUIT) {
        int playernum = model->getCurrentPlayer() + 1;
        cout << "Player" << playernum << " ragequits. A computer will now take over." << endl;
    } else if (state == State::PLAY) {
        int playernum = model->getCurrentPlayer() + 1;
        Card topplayed = *(model->topCard());
        cout << "Player" << playernum << " plays " << topplayed << "." << endl;
    } else if (state == State::DISCARD) {
        int playernum = model->getCurrentPlayer() + 1;
        Card topdiscarded = *(model->topDiscard());
        cout << "Player" << playernum << " discards " << topdiscarded << "." << endl;
    } else if (state == State::ENDROUND) {
        vector<shared_ptr<Player>> tmp = model->getPlayers();
        for (int i = 0; i < tmp.size(); i++) {
            cout << "Player" << (i + 1) << "'s discards: ";
            vector<shared_ptr<Card>> listdiscard = tmp.at(i)->getDiscard();
            for (shared_ptr<Card> discards : listdiscard) {
                cout << *discards << " ";
            }
            cout << endl;
            cout << "Player" << (i + 1) << "'s score: ";
            cout << tmp.at(i)->getScore() << " + " << tmp.at(i)->roundScore() << " = " << tmp.at(i)->totalScore() << endl;
        }
    } else if (state == State::ENDGAME) {
        vector<shared_ptr<Player>> tmp = model->getPlayers();
        // Stores the current lowest score: set at 10000, as there is no case in which
        // a player would have more than 10000 points (could also be int max)
        int lowestscore = 10000;
        // Finds the lowest score among the players
        for (int i = 0; i < tmp.size(); i++) {
            if (tmp.at(i)->totalScore() < lowestscore) {
                // If a lower score is found, we set the lowest score to that score
                lowestscore = tmp.at(i)->totalScore();
            }
        }
        // All players with the lowest score have won
        for (int i = 0; i < tmp.size(); i++) {
            if (tmp.at(i)->totalScore() == lowestscore) {
                cout << "Player" << (i + 1) << " wins!" << endl;
            }
        }
    }
}

void View::printTable() {
    vector<shared_ptr<Card>> curtable = model->getPlayed();
    vector<shared_ptr<Card>> playerhand = model->getHand();
    vector<shared_ptr<Card>> validplays = model->getValidPlays();
    cout << "Cards on the table:" << endl;
    cout << "Clubs: ";
    for (shared_ptr<Card> card : curtable) {
        if (card->getSuit() == Club) {
            if (card->getRank() == 0) {
                cout << "A ";
            } else if (card->getRank() == 9) {
                cout << "T ";
            } else if (card->getRank() == 10) {
                cout << "J ";
            } else if (card->getRank() == 11) {
                cout << "Q ";
            } else if (card->getRank() == 12) {
                cout << "K ";
            } else {
                cout << (card->getRank() + 1) << " ";
            }
        }
    }
    cout << endl;
    cout << "Diamonds: ";
    for (shared_ptr<Card> card : curtable) {
        if (card->getSuit() == Diamond) {
            if (card->getRank() == 0) {
                cout << "A ";
            } else if (card->getRank() == 9) {
                cout << "T ";
            } else if (card->getRank() == 10) {
                cout << "J ";
            } else if (card->getRank() == 11) {
                cout << "Q ";
            } else if (card->getRank() == 12) {
                cout << "K ";
            } else {
                cout << (card->getRank() + 1) << " ";
            }
        }
    }
    cout << endl;
    cout << "Hearts: ";
    for (shared_ptr<Card> card : curtable) {
        if (card->getSuit() == Heart) {
            if (card->getRank() == 0) {
                cout << "A ";
            } else if (card->getRank() == 9) {
                cout << "T ";
            } else if (card->getRank() == 10) {
                cout << "J ";
            } else if (card->getRank() == 11) {
                cout << "Q ";
            } else if (card->getRank() == 12) {
                cout << "K ";
            } else {
                cout << (card->getRank() + 1) << " ";
            }
        }
    }
    cout << endl;
    cout << "Spades: ";
    for (shared_ptr<Card> card : curtable) {
        if (card->getSuit() == Spade) {
            if (card->getRank() == 0) {
                cout << "A ";
            } else if (card->getRank() == 9) {
                cout << "T ";
            } else if (card->getRank() == 10) {
                cout << "J ";
            } else if (card->getRank() == 11) {
                cout << "Q ";
            } else if (card->getRank() == 12) {
                cout << "K ";
            } else {
                cout << (card->getRank() + 1) << " ";
            }
        }
    }
    cout << endl;
    cout << "Your hand: ";
    for (shared_ptr<Card> card : playerhand) {
        cout << *card << " ";
    }
    cout << endl;
    cout << "Legal plays: ";
    for (shared_ptr<Card> card : validplays) {
        cout << *card << " ";
    }
    cout << endl;
}

void View::printDeck() {
    vector<shared_ptr<Card>> tmpdeck = model->getDeck();
    for (int i = 0; i < tmpdeck.size(); i++) {
        if (i % 13 == 0 && i > 0) {
            cout << endl;
        }
        cout << *(tmpdeck.at(i)) << " ";
    }
    cout << endl;
}
