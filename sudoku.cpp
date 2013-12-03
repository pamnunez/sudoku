/*
   Author: Pam Nunez and Mark Eisen
   Desc: main sudoku functionality
*/

#include <QtGui>
#include "sudoku.h"
#include <iostream>
using namespace std;


Sudoku::Sudoku() {

	setWindowTitle("Qt Sudoku");
	QGridLayout* layout = new QGridLayout(this);

	/* Init timer */
	timer = new QTimer(this);
	timer->setInterval(5);	
	connect(timer,SIGNAL(timeout()), this, SLOT(timerTicked()));

	selectDown = false;
	selectUp = false;
	selectLeft = false;
	selectRight = false;
	
	int initial[9][9] = { {4,8,7,0,5,0,0,6,0},
				{9,0,0,4,0,0,0,0,3},
				{2,0,6,0,8,9,5,0,0},
				{0,0,4,0,1,5,6,0,0},
				{1,0,0,0,0,4,0,5,0},
				{0,7,8,2,0,0,0,0,0},
				{0,0,0,0,0,8,0,7,0},
				{7,5,0,0,0,0,0,3,0},
				{0,2,0,0,3,7,4,1,0} };

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

// For initializing numbers on board... for now they are all 1's
/*	for (int i=0;i<9;i++){
		for (int j=0;j<9;j++){
			QLabel *label = new QLabel(this);
			QString qstr = QString::number(1);
			label->setText(qstr);
			layout->addWidget(label,i,j);
		}
	}*/

	timer->start(100);
	update();
}

void Sudoku::paintEvent(QPaintEvent*) {
	QPainter p(this);
	QPen pen(Qt::black);
	QFont font = QFont();
	p.setFont(font);
	// Draw border
	p.drawRect(0,0,WIDTH-1, HEIGHT-1);

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

			// Draw square and number inside
			p.setPen(pen);
			QString qstr = QString::number(board[i][j]);
			QRectF qrect = QRectF(i*WIDTH/9,j*WIDTH/9,WIDTH/9,WIDTH/9);
			p.drawRect(qrect);
			if (init[i][j]) {
				font.setWeight(99);
				font.setPointSize(14);
				p.drawText(qrect, Qt::AlignCenter, qstr);
			}
			if (board[i][j]) {
				font.setWeight(50);
				font.setPointSize(14);
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
  Sudoku sudoku;
  sudoku.show();




  return app.exec();
}

/*

// Insert number at location i,j
Sudoku::Insert(int i, int j, unsigned int num){

	if ((i<9)&&(j<9)&&(num<10))
		board[i][j] = num;

}*/
