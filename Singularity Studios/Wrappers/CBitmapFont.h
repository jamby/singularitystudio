///////////////////////////////////////////////////////////////////////////////////////////////////////////
//	File:		"CBitmampFont.H"
//
//	Author:		Nick Bucciarelli
//
//	Purpose:	Display text using bitmaps
////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma once
#include <windows.h>

class CBitmapFont
{
private:
	int m_nFontImageID;
	int m_nNumCols;
	int m_nCharWidth;
	int m_nCharHeight;
	char m_cStartChar;

	RECT CalcRect(int id);
public:
	CBitmapFont(void);

	/////////////////////////////////////////////////////////////////////////////////////////////////////
	//	Function: "DrawString"
	//	
	//	Purpose:  Display a string
	//////////////////////////////////////////////////////////////////////////////////////////////////////
	void DrawString(const char* szText, int nPosX, int nPosY, float fScaleX = 1.0f, float fScaleY = 1.0f, int nSpacing = 0, DWORD color = 0xFFFFFFFF);

	/////////////////////////////////////////////////////////////////////////////////////////////////////
	//	Function: "DrawString"
	//	
	//	Purpose:  Display a letter
	//////////////////////////////////////////////////////////////////////////////////////////////////////
	void DrawLetter(const char szLetter, int nPosX, int nPosY, float fScaleX = 1.0f, float fScaleY = 1.0f, int nSpacing = 0, DWORD color = 0xFFFFFFFF);

	//////////////////////////////////////////////////////////////////////////////////////////////////////
	//  Function: Accessors
	//	
	//  Purpose : Returns the specified type.
	///////////////////////////////////////////////////////////////////////////////////////////////////////
	inline int GetFontImageID()					{ return m_nFontImageID; }
	inline int GetNumCols()						{ return m_nNumCols; }
	inline int GetCharWidth()					{ return m_nCharWidth; }
	inline int GetCharHeight()					{ return m_nCharHeight; }
	inline char GetStartChar()					{ return m_cStartChar; }

	///////////////////////////////////////////////////////////////////////////////////////////////////////
	//  Function: Modifiers
	//
	//  Purpose: Modifies the specified type.
	////////////////////////////////////////////////////////////////////////////////////////////////////////
	inline void SetFontImageID(int nImageID)	{ m_nFontImageID = nImageID; }
	inline void SetNumCols(int nNumCols)		{ m_nNumCols = nNumCols; }
	inline void SetCharWidth(int nWidth)		{ m_nCharWidth = nWidth; }
	inline void SetCharHeight(int nHeight)		{ m_nCharHeight = nHeight; }
	inline void SetStartChar(char startChar)	{ m_cStartChar = startChar; }
};