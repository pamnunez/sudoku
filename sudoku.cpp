/*
   Author: Pam Nunez and Mark Eisen
   Desc: main sudoku functionality
*/

#include <QtGui>
#include "sudoku.h"
#include <iostream>
#include <fstream>
using namespace std;

MainWindow::MainWindow() {
	
	setWindowTitle("Qt Sudoku");
	QVBoxLayout* layout = new QVBoxLayout(this);
	sudoku = new Sudoku(this);
	layout->addWidget(sudoku);

	new_game = new QPushButton("New Game",this);
	check_game  = new QPushButton("Check",this);
	undo_move = new QPushButton("Undo Last Move",this);
	QHBoxLayout* buttons = new QHBoxLayout(this);
	buttons->addWidget(new_game);
	buttons->addWidget(undo_move);
	buttons->addWidget(check_game);
	layout->addLayout(buttons);
	
}

Sudoku::Sudoku(QWidget* parent)
 : QWidget(parent) {


	/* Init timer */
	timer = new QTimer(this);
	timer->setInterval(5);	
	connect(timer,SIGNAL(timeout()), this, SLOT(timerTicked()));

	selectDown = false;
	selectUp = false;
	selectLeft = false;
	selectRight = false;
	
	int initial[9][9];// = { {4,8,7,0,5,0,0,6,0},
//				{9,0,0,4,0,0,0,0,3},
//				{2,0,6,0,8,9,5,0,0},
//				{0,0,4,0,1,5,6,0,0},
//				{1,0,0,0,0,4,0,5,0},
//				{0,7,8,2,0,0,0,0,0},
//				{0,0,0,0,0,8,0,7,0},
//				{7,5,0,0,0,0,0,3,0},
//				{0,2,0,0,3,7,4,1,0} };


	ifstream gameData;
	int temp;
	gameData.open ("games.txt");
	if (gameData.is_open() == true) { cout << "File opened." << endl; }
	temp = gameData.get();
	cout << "First char in file: " << temp << endl;
	if (gameData.is_open()) {
		while(temp != '\n') {
			for (int x = 0; x < 9; x++) {
				for (int y = 0; y < 9; y++) {
					initial[y][x] = temp - '0';
					temp = gameData.get();
				}
			}
		}
	}
	gameData.close();
	for (int x = 0; x < 9; x++) {
		for (int y = 0; y < 9; y++) {
			cout << "initial[" << x << "][" << y << "] = " << initial[x][y] << endl;
		}
	}
//
//
//
//
//
	for (int i = 0; i <= 8; i++) { 
		for (int j = 0; j <= 8; j++) { 
			init[i][j] = initial[i][j];
		}
	}
	for (int i = 0; i <= 8; i++) { 
		for (int j = 0; j <= 8; j++) { 
			board[i][j] = init[i][j];
		}
	}

	setFixedSize(WIDTH,HEIGHT);
	
	// The coordinates of the selected square
	select_y = 4;
	select_x = 3;	
	grabKeyboard();

	timer->start(100);
	update();
}

void Sudoku::reset(){

}

void Sudoku::undo(){

}

void Sudoku::check(){
	for (int x = 0; x < 9; x++) {
		for (int y = 0; y < 9; y++) {
			if (board[select_x][select_y] != init[select_x][select_y]) {
		QPainter p(this);
	QPen pen(Qt::black);
	QFont font = QFont();
	p.setFont(font);			
	pen.setWidth(3);
	p.setPen(pen);

			QString qstr = QString::number(board[i][j]);
			}
		}
	}

}

void Sudoku::paintEvent(QPaintEvent*) {
	QPainter p(this);
	QPen pen(Qt::black);
	QFont font = QFont();
	p.setFont(font);

	// Draw border
	p.drawRect(0,0,WIDTH-1, HEIGHT-1);
	pen.setWidth(3);
	p.setPen(pen);
	p.drawLine(0,WIDTH/3,WIDTH,WIDTH/3);
	p.drawLine(0,2*WIDTH/3,WIDTH,2*WIDTH/3);
	p.drawLine(WIDTH/3,0,WIDTH/3,WIDTH);
	p.drawLine(2*WIDTH/3,0,2*WIDTH/3,WIDTH);


	// Iterate through each square
	for (int i=0;i<9;i++){
		for (int j=0;j<9;j++){
			
			// If selected square, make pen blue and thicker
			if ((select_x==i) && (select_y==j)){
				pen.setWidth(2);
				pen.setColor(Qt::blue);
			}
			else {
				pen.setWidth(1);
				pen.setColor(Qt::black);
			}
			p.setPen(pen);


			// Draw square and number inside
			QString qstr = QString::number(board[i][j]);
			QRectF qrect = QRectF(i*WIDTH/9,j*WIDTH/9,WIDTH/9,WIDTH/9);
			p.drawRect(qrect);
			if (init[i][j]) {
				font.setWeight(99);
				font.setPointSize(14);
				p.setFont(font);
				p.drawText(qrect, Qt::AlignCenter, qstr);
			}
			if (board[i][j]) {
				font.setWeight(50);
				font.setPointSize(14);
				p.setFont(font);
				p.drawText(qrect, Qt::AlignCenter, qstr);
			}
		}
	}

}

void Sudoku::timerTicked() {

	// Change selected square based on user input
	if(selectRight) {
		if((select_x >= 8)) { select_x += 0; }
		else { select_x++; }
	} if(selectLeft) {
		if((select_x <= 0)) { select_x += 0; }
		else{ select_x--; }	
	} if(selectUp) {
		if((select_y <= 0)) { select_y += 0; }
		else{ select_y--; }
	} if(selectDown) {
		if((select_y >= 8)) { select_y += 0; }
		else { select_y++; }
	}
	update();
}


void Sudoku::keyPressEvent(QKeyEvent* event) {

	if (event->key() == Qt::Key_Left) {
		selectLeft = true;
	}
	if (event->key() == Qt::Key_Right) {
		selectRight = true;
	}
	if (event->key() == Qt::Key_Up) {
		selectUp = true;
	}
	if (event->key() == Qt::Key_Down) {
		selectDown = true;
	}
	if (event->key() == Qt::Key_1) {
		if (init[select_x][select_y] == 0) {
			board[select_x][select_y] = 1;
		}
	}
	if (event->key() == Qt::Key_2) {
		if (init[select_x][select_y] == 0) {
			board[select_x][select_y] = 2;
		}
	}
	if (event->key() == Qt::Key_3) {
		if (init[select_x][select_y] == 0) {
			board[select_x][select_y] = 3;
		}
	}
	if (event->key() == Qt::Key_4) {
		if (init[select_x][select_y] == 0) {
			board[select_x][select_y] = 4;
		}
	}
	if (event->key() == Qt::Key_5) {
		if (init[select_x][select_y] == 0) {
			board[select_x][select_y] = 5;
		}
	}
	if (event->key() == Qt::Key_6) {
		if (init[select_x][select_y] == 0) {
			board[select_x][select_y] = 6;
		}
	}
	if (event->key() == Qt::Key_7) {
		if (init[select_x][select_y] == 0) {
			board[select_x][select_y] = 7;
		}
	}
	if (event->key() == Qt::Key_8) {
		if (init[select_x][select_y] == 0) {
			board[select_x][select_y] = 8;
		}
	}
	if (event->key() == Qt::Key_9) {
		if (init[select_x][select_y] == 0) {
			board[select_x][select_y] = 9;
		}
	}
	update();

}
void Sudoku::keyReleaseEvent(QKeyEvent*) {
	selectLeft = false;
	selectRight = false;
	selectUp = false;
	selectDown = false;
}


int main(int argc, char** argv)
{
	QApplication app(argc, argv);

	// Run game
	MainWindow game;
	game.show();

	return app.exec();
}
