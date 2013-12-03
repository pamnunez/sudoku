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
		Sudoku();

	private:
		QTimer* timer;
		static const int WIDTH = 450;
		static const int HEIGHT = 450;
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
	protected:
		void paintEvent(QPaintEvent* event);
		void keyPressEvent(QKeyEvent* event);
		void keyReleaseEvent(QKeyEvent* event);

/*	public slots:
		void buttonPress();

	protected:
		void paintEvent(QPAINTEVENT* event);
		void keyPressEvent(QKeyEvent* event);
		void keyReleaseEvent(QKeyEvent* event);
		void insert(int i, int j, unsigned int num);

	private slots:
		void timerTicked();

	private:
		void reset();

	enum { PLAYING, AFTER_PLAY } state;

	QTimer* timer;

	int selected_square;
	static const int num_rows = 9;
	static const int num_cols = 9;

	bool win;
*/	
};

#endif
