/* File: sudoku.h
   Author: Pam Nunez and Mark Eisen
*/

#ifndef SUDOKU_H_
#define SUDOKU_H_

#include <QtGui>


class Sudoku : public QWidget
{
	Q_OBJECT

	public:
		Sudoku(QWidget* parent);

	private:
		QTimer* timer;
		static const int WIDTH = 450;
		static const int HEIGHT = 450;
		static const int MAIN_WIDTH = 450;
		static const int MAIN_HEIGHT = 500;
		int select_x;
		int select_y;

		bool selectDown;
		bool selectUp;
		bool selectLeft;
		bool selectRight;
		int init[9][9];
		int board[9][9];
	private slots:
		void timerTicked();
	public slots:
		void reset();
		void undo();
		void check();
	protected:
		void paintEvent(QPaintEvent* event);
		void keyPressEvent(QKeyEvent* event);
		void keyReleaseEvent(QKeyEvent* event);


};

class MainWindow : public QWidget {

	Q_OBJECT

	public:
		MainWindow();

	private:
		Sudoku* sudoku;
		QPushButton* new_game;
		QPushButton* check_game;
		QPushButton* undo_move;
};


#endif
