#ifndef __GAMECONTROL_H__
#define __GAMECONTROL_H__
#include <time.h>
#include <windows.h>
#define CHESSBOARD_SIZE	15
#define WIN_SIZE		5

enum PlayerType
{
	PLAYER_EMPTY = 0,
	PLAYER_BLACK = 1,
	PLAYER_WHITE = 2
};

enum GameResult
{
	PLAYER_WIN	= 0,
	PLAYER_LOSE	= 1,
	PLAYER_NONE	= 2,
};

class GameControl
{

private:

	bool m_IsEnable;								//��Ϸ������
	int	m_ChessBoard[CHESSBOARD_SIZE][CHESSBOARD_SIZE];	//����
	int	m_Turn;										//��ǰ�Ѵ���������
	PlayerType m_Player;							//��ǰ�������
	GameResult m_Result;							//��ʤ���

private:

	bool SetChessPointBlack(POINT theSite);			//����������Ӧ��ֵΪPLAYER_BLACK
	bool SetChessPointWhite(POINT theSite);			//����������Ӧ��ֵΪPLAYER_WHITE

	bool IsChessPointEnable(POINT theSite);			//�����Ӧ���Ƿ��ܹ�����

	bool IsGameOver();								//�����Ϸ�Ƿ����
	bool IsAnyWinner();								//����Ƿ���ڻ�ʤ��
	bool IsChessBoardFull();						//��������Ƿ�����

public:
	GameControl();
	~GameControl();

	void InitGame();								//��ʼ������

	bool SetChessPoint(POINT theSite);				//����������Ӧ��ֵ
	
	PlayerType GetChessPointValue(POINT theSite);	//��ȡ������Ӧ��ֵ
	PlayerType GetChessPlayer();					//��ȡ��ǰ�������

	GameResult GetGameResult();						//��ȡ��ʤ���
	void SetGameResult();							//���û�ʤ���

	int GetChessTurnValue();						//��ȡ�����Ѵ���������
	bool CheckGameState();							//�����Ϸ״̬

	void MakeGameDisable();							//ʹ��Ϸֹͣ��Ӧ
	void MakeGameEnable();							//ʹ��Ϸ������Ӧ
	bool IsGameEnable();							//�����Ϸ�Ƿ����������Ӧ

	bool AI_Sample(POINT* AIpoint);					//AIʾ����������,�������
	bool AI_Level_1(POINT* AIpoint);				//AI_Level_1�������˹����ܣ��ɽ�������սʤСѧ��
};

#endif  // __GAMECONTROL_H__
