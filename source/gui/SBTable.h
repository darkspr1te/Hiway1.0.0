#ifndef __SB_TABLE_H__
#define __SB_TABLE_H__

#include "define.h"
#include <QtGui/QApplication>
#include <QtGui/QWidget>
#include <QtGui/QLabel>
#include <QtGui/QPixmap>
#include <QtGui/QBrush>
#include <QtGui/QPen>
#include <QtGui/QColor>
#include <QtCore/QList>

class QWidget;
class QBrush;

typedef struct _item_a
{
	QString szValue;
	DWORD dwParam;
}T_ITEM_A;

// typedef struct _row
// {
// 	DWORD dwID;
// 	T_ITEM_A* list;
// }T_ITEM;

typedef struct _item_hdr
{
	QString szValue;
	DWORD dwParam;
	QPixmap icon;
	int width;
}T_ITEM_HDR;

typedef QLabel T_ITEM;

typedef T_ITEM_A* (*pfnGetRowData)(DWORD dwID);

class SBTable : public QWidget
{
	Q_OBJECT

public:
	SBTable(QWidget *parent = NULL);
	~SBTable();
	BOOL GetHeaderUse() const;
	void SetHeaderUse(BOOL bUse = TRUE);
	BOOL GetScrollUse() const;
	void SetScrollUse(BOOL bUse = TRUE);
	BOOL GetGridUse() const;
	void SetGridUse(BOOL bUse = FALSE);
	BOOL GetContiniousScrollUse() const;
	void SetContiniousScrollUse(BOOL bUse);
	BOOL GetTransparentUse() const;
	void SetTransparentUse(BOOL bUse);
	BOOL GetRotateUse() const;
	void SetRotateUse(BOOL bUse = FALSE);
	BOOL GetLastColumnMergeUse() const;
	void SetLastColumnMergeUse(BOOL bUse);
	QPixmap* GetPixmap() const;
	BOOL SetPixmap(QPixmap *pmap);
	QRgb GetBkColor() const;
	BOOL SetBkColor(QRgb c = qRgb(255, 255, 255));
	QRgb GetSelectedBkColor() const;
	BOOL SetSelectedBkColor(QRgb c = qRgb(210, 226, 249));
	QRgb GetForeColor() const;
	BOOL SetForeColor(QRgb c = qRgb(0, 0, 0));
	QRgb GetSelectedForeColor() const;
	BOOL SetSelectedForeColor(QRgb c = qRgb(0, 0, 0));
	QRgb GetHdrForeColor() const;
	BOOL SetHdrForeColor(QRgb c = qRgb(255, 255, 255));
	QRgb GetGridColor() const;
	BOOL SetGridColor(QRgb c = qRgb(199, 199, 199));
	void SetMargin(int left, int top, int right, int bottom);
	int GetColumnWidth(int nCol) const;
	BOOL SetColumnWidth(int nCol, int cx = 50);
	int GetRowHeight() const;
	BOOL SetRowHeight(int height = 16);
	int GetColumnCount() const;
	BOOL SetColumnCount(int nCnt);
	int GetRowCount() const;
	BOOL SetRowCount(int nCnt);
	int GetMaxScrollPos() const;
	BOOL SetMaxScrollPos(int nPos);
	BOOL SetTableRect(int x, int y, int cx, int cy);
	int GetCurrentIndex() const;
	BOOL SetCurrentIndex(int nIndex);
	int GetBaseIndex() const;
	BOOL SetBaseIndex(int nIndex);
	BOOL SetRowDataCallback(pfnGetRowData fn);
	T_ITEM_A* GetCurrentItem();
	BOOL InsertColumn(int nCol, QString szValue, DWORD dwParam = -1UL, int width = 50);
	BOOL RemoveColumn(int nCol);
	BOOL GetTableItemArea(int nRow, int nCol, int &x, int &y, int &cx, int &cy);

	void SBTableProc();
	void OnKeyPress(int nKey);
	void OnKeyUp();
	void OnKeyDown();
	void OnPageUp();
	void OnPageDown();
	void OnRedraw();
	void UpdateTableArea(int from, int to);

protected:
 	void paintEvent(QPaintEvent *e);

private:
	QPixmap *m_bkPixmap;

	QPen *m_tblBoundaryPen;
	QPen *m_tblForePen;
	QPen *m_tblSelectedForePen;
	QPen *m_tblHdrForePen;
	QPen *m_tblGridPen;
	QBrush *m_tblBackgroundBrush;
	QBrush *m_tblSelectedBkBrush;
	QRect m_tblArea;

	QPixmap *m_scrollUp;
	QPixmap *m_scrollDown;
	QPixmap *m_scrollMedium;
	QPen *m_scrollBoundaryPen;
	QBrush *m_scrollFillBrush;
	QRect m_scrollArea;

	QPixmap *m_hdr0;
	QPixmap *m_hdr1;
	QPixmap *m_hdr2;

	BOOL m_HeaderUse;
	BOOL m_ScrollUse;
	BOOL m_GridUse;
	BOOL m_ContiniousScroll;
	BOOL m_Transparent;
	BOOL m_RotateUse;
	BOOL m_LastColumnMerge;
	QRgb m_BkColor;
	QRgb m_SelectedBkColor;
	QRgb m_ForeColor;
	QRgb m_SelectedForeColor;
	QRgb m_HdrForeColor;
	QRgb m_GridColor;
	int m_MarginLeft;
	int m_MarginRight;
	int m_MarginTop;
	int m_MarginBottom;
	int m_ColumnWidth;
	int m_RowHeight;
	int m_ColumnCount;
	int m_RowCount;
	int m_MaxScroll;

	int m_nPrevIndex;
	int m_nCurrentIndex;
	int m_nBaseIndex;
	int m_nVisableCount;
	pfnGetRowData m_fnGetRowData;

	BOOL m_bRecreateItems;
//	T_ITEM ***m_TableItems;

	QList<T_ITEM_HDR*> m_HdrList;
// 	QList<T_ITEM*> m_DataList;

	int m_nX, m_nY;

	void RecalcPageSize();
	void DrawHeaderArea(QPainter *p);
	void DrawTablesArea(QPainter *p);
	void DrawScrollArea(QPainter *p);
};

#endif /*__SB_TABLE_H__*/
