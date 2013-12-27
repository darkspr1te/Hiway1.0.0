#include <QtGui/QApplication>
#include <QtGui/QPainter>
#include <QtGui/QPaintEvent>
#include <QtGui/QPushButton>

#include "source/precomp.h"
#include "SBTable.h"

#define QCOLOR(_color_)			(QColor(qRed((_color_)), qGreen((_color_)), qBlue((_color_))))
#define MEMFREE(_p_)			{if ((_p_)) delete (_p_); (_p_) = NULL;}
#define RESOURCE_PATH			GUI_RESOURCE_PATH

#define LISTHDR_0_FILENAME		"listheader-0.png"
#define LISTHDR_1_FILENAME		"listheader-1.png"
#define LISTHDR_2_FILENAME		"listheader-2.png"
#define LISTHDR_HEIGHT			(m_HeaderUse ? 22 : 0)

#define SELECTED_ITEM_FILENAME	"selected-item.png"
#define SCROLL_BG_FILENAME		"scroll-bg.png"
#define SCROLL_ITEM_FILENAME	"scroll-item.png"
#define SCROLL_WIDTH			(m_ScrollUse ? 6 : 0)

//////////////////////////////////////////////////////////////////////////
SBTable::SBTable(QWidget *parent /* = NULL */)
	: QWidget(parent)
{
	m_tblBoundaryPen = NULL;
	m_tblForePen = NULL;
	m_tblSelectedForePen = NULL;
	m_tblHdrForePen = NULL;
	m_tblGridPen = NULL;
	m_tblBackgroundBrush = NULL;
	m_tblSelectedBkBrush = NULL;
	m_scrollUp = NULL;				// NotUsed
	m_scrollDown = NULL;			// NotUsed
	m_scrollMedium = NULL;			// NotUsed
	m_scrollBoundaryPen = NULL;		// NotUsed
	m_scrollFillBrush = NULL;		// NotUsed
	m_hdr0 = NULL;
	m_hdr1 = NULL;
	m_hdr2 = NULL;

	m_HeaderUse = TRUE;
	m_ScrollUse = TRUE;
	m_GridUse = FALSE;
	m_ContiniousScroll = TRUE;
	m_Transparent = FALSE;
	m_RotateUse = TRUE;
	m_LastColumnMerge = FALSE;
	m_BkColor = qRgb(255, 255, 255);
	m_SelectedBkColor = qRgb(210, 226, 249);
	m_ForeColor = qRgb(0, 0, 0);
	m_SelectedForeColor = qRgb(0, 0, 0);
	m_HdrForeColor = qRgb(0, 0, 0);
	m_GridColor = qRgb(199, 199, 199);
	m_MarginLeft = m_MarginRight = 5;
	m_MarginTop = m_MarginBottom = 1;
	m_RowHeight = 16;
	m_ColumnCount = 0;
	m_MaxScroll = 0;
	m_fnGetRowData = NULL;

	m_bRecreateItems = TRUE;
// 	m_TableItems = NULL;

	m_nPrevIndex = 0;
	m_nCurrentIndex = -1;
	m_nBaseIndex = 0;
	m_nVisableCount = 10;

	m_bkPixmap = NULL;

	m_tblBoundaryPen = new QPen(QColor(130, 161, 190)); m_tblBoundaryPen->setWidth(2);
	m_tblForePen = new QPen(QCOLOR(m_ForeColor));
	m_tblSelectedForePen = new QPen(QCOLOR(m_SelectedForeColor));
	m_tblHdrForePen = new QPen(QCOLOR(m_HdrForeColor));
	m_tblGridPen = new QPen(QCOLOR(m_GridColor));
	m_tblBackgroundBrush = new QBrush(QCOLOR(m_BkColor), Qt::SolidPattern);
	m_tblSelectedBkBrush = new QBrush(QCOLOR(m_SelectedBkColor), Qt::SolidPattern);
	m_tblArea = QRect(0, 0, LCD_SIZE_X, LCD_SIZE_Y);

	m_scrollUp = new QPixmap(GUI_RESOURCE_PATH "scroll-up.png");
	m_scrollDown = new QPixmap(GUI_RESOURCE_PATH "scroll-down.png");
	m_scrollMedium = new QPixmap(GUI_RESOURCE_PATH "scroll-medium.png");
	m_scrollBoundaryPen = new QPen(QColor(204, 204, 204)); m_scrollBoundaryPen->setStyle(Qt::DotLine);
	m_scrollFillBrush = new QBrush(QColor(239, 239, 239), Qt::Dense4Pattern);
	m_scrollArea = QRect(100, 100, 16, 100);

	m_hdr0 = new QPixmap(RESOURCE_PATH LISTHDR_0_FILENAME);
	m_hdr1 = new QPixmap(RESOURCE_PATH LISTHDR_1_FILENAME);
	m_hdr2 = new QPixmap(RESOURCE_PATH LISTHDR_2_FILENAME);

// 	m_bkPixmap = new QPixmap(m_tblArea.width(), m_tblArea.height());
// 	setPixmap(*m_bkPixmap);

	RecalcPageSize();
	setGeometry(m_tblArea);
}

SBTable::~SBTable()
{
	RemoveColumn(-1);

	MEMFREE(m_tblBoundaryPen);
	MEMFREE(m_tblForePen);
	MEMFREE(m_tblSelectedForePen);
	MEMFREE(m_tblHdrForePen);
	MEMFREE(m_tblHdrForePen);
	MEMFREE(m_tblBackgroundBrush);
	MEMFREE(m_tblSelectedBkBrush);

	MEMFREE(m_scrollUp);
	MEMFREE(m_scrollDown);
	MEMFREE(m_scrollMedium);
	MEMFREE(m_scrollBoundaryPen);
	MEMFREE(m_scrollFillBrush);

	MEMFREE(m_hdr0);
	MEMFREE(m_hdr1);
	MEMFREE(m_hdr2);

 	MEMFREE(m_bkPixmap);
}

//////////////////////////////////////////////////////////////////////////
BOOL SBTable::GetHeaderUse() const
{
	return m_HeaderUse;
}

void SBTable::SetHeaderUse(BOOL bUse /* = TRUE */)
{
	m_HeaderUse = bUse;
	RecalcPageSize();
}

BOOL SBTable::GetScrollUse() const
{
	return m_ScrollUse;
}

void SBTable::SetScrollUse(BOOL bUse /* = TRUE */)
{
	m_ScrollUse = bUse;
}

BOOL SBTable::GetGridUse() const
{
	return m_GridUse;
}

void SBTable::SetGridUse(BOOL bUse /* = FALSE */)
{
	m_GridUse = bUse;
}

BOOL SBTable::GetContiniousScrollUse() const
{
	return m_ContiniousScroll;
}

void SBTable::SetContiniousScrollUse(BOOL bUse)
{
	m_ContiniousScroll = bUse;
}

BOOL SBTable::GetTransparentUse() const
{
	return m_Transparent;
}

void SBTable::SetTransparentUse(BOOL bUse)
{
	m_Transparent = bUse;
}

BOOL SBTable::GetRotateUse() const
{
	return m_RotateUse;
}

void SBTable::SetRotateUse(BOOL bUse /* = FALSE */)
{
	m_RotateUse = bUse;
}

BOOL SBTable::GetLastColumnMergeUse() const
{
	return m_LastColumnMerge;
}

void SBTable::SetLastColumnMergeUse(BOOL bUse)
{
	m_LastColumnMerge = bUse;
}

QPixmap* SBTable::GetPixmap() const
{
	return m_bkPixmap;
}

BOOL SBTable::SetPixmap(QPixmap *pmap)
{
	MEMFREE(m_bkPixmap);
	if (pmap)
		m_bkPixmap = new QPixmap(*pmap);
	return TRUE;
}

QRgb SBTable::GetBkColor() const
{
	return m_BkColor;
}

BOOL SBTable::SetBkColor(QRgb c /* = qRgb(255, 255, 255) */)
{
	m_BkColor = c;
	MEMFREE(m_tblBackgroundBrush);
	m_tblBackgroundBrush = new QBrush(QCOLOR(m_BkColor), Qt::SolidPattern);
	return TRUE;
}

QRgb SBTable::GetSelectedBkColor() const
{
	return m_SelectedBkColor;
}

BOOL SBTable::SetSelectedBkColor(QRgb c /* = qRgb */)
{
	m_SelectedBkColor = c;
	MEMFREE(m_tblSelectedBkBrush);
	m_tblSelectedBkBrush = new QBrush(QCOLOR(m_SelectedBkColor), Qt::SolidPattern);
	return TRUE;
}

QRgb SBTable::GetForeColor() const
{
	return m_ForeColor;
}

BOOL SBTable::SetForeColor(QRgb c /* = qRgb */)
{
	m_ForeColor = c;
	MEMFREE(m_tblForePen);
	m_tblForePen = new QPen(QCOLOR(m_ForeColor));
	return TRUE;
}

QRgb SBTable::GetSelectedForeColor() const
{
	return m_SelectedForeColor;
}

BOOL SBTable::SetSelectedForeColor(QRgb c /* = QRgb */)
{
	m_SelectedForeColor = c;
	MEMFREE(m_tblSelectedForePen);
	m_tblSelectedForePen = new QPen(QCOLOR(m_SelectedForeColor));
	return TRUE;
}

QRgb SBTable::GetHdrForeColor() const
{
	return m_HdrForeColor;
}

BOOL SBTable::SetHdrForeColor(QRgb c /* = qRgb */)
{
	m_HdrForeColor= c;
	MEMFREE(m_tblHdrForePen);
	m_tblHdrForePen = new QPen(QCOLOR(m_HdrForeColor));
	return TRUE;
}

QRgb SBTable::GetGridColor() const
{
	return m_GridColor;
}

BOOL SBTable::SetGridColor(QRgb c /* = qRgb */)
{
	m_GridColor = c;
	MEMFREE(m_tblGridPen);
	m_tblGridPen = new QPen(QCOLOR(m_GridColor));
	return TRUE;
}

void SBTable::SetMargin(int left, int top, int right, int bottom)
{
	m_MarginLeft = left;
	m_MarginTop = top;
	m_MarginTop = right;
	m_MarginTop = bottom;
}

int SBTable::GetColumnWidth(int /*nCol*/) const
{
	return 0;
}

BOOL SBTable::SetColumnWidth(int /*nCol*/, int /*cx = 50 */)
{
	return TRUE;
}

int SBTable::GetRowHeight() const
{
	return m_RowHeight;
}

BOOL SBTable::SetRowHeight(int height /* = 16 */)
{
	m_RowHeight = height;
	RecalcPageSize();
	return TRUE;
}

int SBTable::GetColumnCount() const
{
	return m_ColumnCount;
}

BOOL SBTable::SetColumnCount(int /*nCnt*/)
{
	return TRUE;
}

int SBTable::GetRowCount() const
{
	return m_RowCount;
}

BOOL SBTable::SetRowCount(int nCnt)
{
	m_RowCount = nCnt;
	SetMaxScrollPos(m_RowCount);

	if (m_nCurrentIndex < 0)
		m_nCurrentIndex = 0;

	return TRUE;
}

int SBTable::GetMaxScrollPos() const
{
	return m_MaxScroll;
}

BOOL SBTable::SetMaxScrollPos(int nPos)
{
	m_MaxScroll = nPos;
	return TRUE;
}

BOOL SBTable::SetTableRect(int x, int y, int cx, int cy)
{
//	m_tblArea = QRect(x, y, cx, cy);
	m_tblArea = QRect(0, 0, cx, cy);
	RecalcPageSize();

// 	MEMFREE(m_bkPixmap);
// 	m_bkPixmap = new QPixmap(m_tblArea.width(), m_tblArea.height());

	setGeometry(x, y, cx, cy);
	return TRUE;
}

int SBTable::GetCurrentIndex() const
{
	return m_nCurrentIndex;
}

BOOL SBTable::SetCurrentIndex(int nIndex)
{
	m_nBaseIndex = MAX(0, MIN(nIndex, m_RowCount-m_nVisableCount));
	m_nCurrentIndex = nIndex;
	UpdateTableArea(0, m_nVisableCount);
	return TRUE;
}

int SBTable::GetBaseIndex() const
{
	return m_nBaseIndex;
}

BOOL SBTable::SetBaseIndex(int nIndex)
{
	m_nBaseIndex = nIndex;
	return TRUE;
}

BOOL SBTable::SetRowDataCallback(pfnGetRowData fn)
{
	m_fnGetRowData = fn;
	return TRUE;
}

T_ITEM_A* SBTable::GetCurrentItem()
{
	if (!m_fnGetRowData)
		return NULL;
	return m_fnGetRowData(m_nCurrentIndex);
}

BOOL SBTable::InsertColumn(int nCol, QString szValue, DWORD dwParam /* = -1UL */, int width /* = 50 */)
{
	T_ITEM_HDR *col = new T_ITEM_HDR;
	
	col->szValue = szValue;
	col->dwParam = dwParam;
	col->width = width;

	if (nCol < 0)
		m_HdrList.append(col);
	else
	if (m_HdrList.count() < nCol)
		return FALSE;
	else
		m_HdrList[nCol] = col;

	m_ColumnCount = m_HdrList.count();

	return TRUE;
}

BOOL SBTable::RemoveColumn(int nCol)
{
	T_ITEM_HDR *col = NULL;

	if (nCol < 0)
	{
		while (!m_HdrList.isEmpty())
		{
			col = m_HdrList[0];
			m_HdrList.removeFirst();
 			if (col)
 				DELETE(col);
		}
		goto _lExit;
	}

	col = m_HdrList[nCol];
	m_HdrList.removeAt(nCol);
// 	if (col)
// 		delete col;

_lExit:
	return TRUE;
}

BOOL SBTable::GetTableItemArea(int nRow, int nCol, int &x, int &y, int &cx, int &cy)
{
	int i;

	if (nCol + 1 > m_ColumnCount)
		return FALSE;

	x = m_nX;
	for (i=0; i<= nCol; i++)
	{
		if (i == nCol)
			break;
		x += m_HdrList[i]->width;
	}
	cx = m_HdrList[nCol]->width - (m_ScrollUse ? m_scrollArea.width() : 0);

	y = m_nY + (nRow - m_nBaseIndex) * m_RowHeight;
	cy = m_RowHeight;

	return TRUE;
}

void SBTable::RecalcPageSize()
{
	int h = m_tblArea.height();

	m_nVisableCount = (h - LISTHDR_HEIGHT) / m_RowHeight;
}

//////////////////////////////////////////////////////////////////////////
void SBTable::paintEvent(QPaintEvent *e)
{
	QWidget::paintEvent(e);
	QPainter painter(this);

	// 1: Background
	if (!m_Transparent)
	{
		painter.save();
		if (m_bkPixmap)
		{
			painter.drawPixmap(0, 0, m_bkPixmap->width(), m_bkPixmap->height(), *m_bkPixmap);
		}
		else
		{
			painter.setBrush(*m_tblBackgroundBrush);
			painter.setPen(*m_tblBoundaryPen);
			painter.drawRect(m_tblArea);
		}
		painter.restore();
	}

	// 2: Header
	DrawHeaderArea(&painter);

	// 3: Contents
	DrawTablesArea(&painter);

	// 4: Scroll
	DrawScrollArea(&painter);

	// 5: Border
	painter.save();
	painter.setBrush(Qt::NoBrush);
	painter.setPen(*m_tblBoundaryPen);
	painter.drawRect(m_tblArea);
	painter.restore();
}

void SBTable::DrawHeaderArea(QPainter *p)
{
	if (!m_HeaderUse)
		return;

	int x = m_tblArea.left();
	int y = m_tblArea.top();
	int w = m_tblArea.width();
	int h = LISTHDR_HEIGHT;
	int col_width;

	T_ITEM_HDR *hdr;

	p->save();

	p->setPen(*m_tblHdrForePen);
	for (int i=0; i<m_HdrList.count(); i++)
	{
		hdr = m_HdrList[i];
		if (!hdr)
			continue;

		//In the case of last column, auto-size
		if (i < m_HdrList.count() - 1)
			col_width = hdr->width;
		else
			col_width = w - x;

		p->drawPixmap(x, y, m_hdr0->width(), h, *m_hdr0);
		p->drawPixmap(x+3, y, col_width-m_hdr0->width()-m_hdr2->width(), h, *m_hdr1);
		p->drawPixmap(x+col_width-1, y, m_hdr2->width(), h, *m_hdr2);

		p->drawText(x, y, col_width, h, Qt::AlignHCenter|Qt::AlignVCenter, hdr->szValue);

		x += col_width;
	}

	p->restore();
}

void SBTable::DrawTablesArea(QPainter *p)
{
	if (!m_fnGetRowData || m_nCurrentIndex < 0)
		return;

	int i;
	int *col_width = new int[m_ColumnCount];
	int sum_width = 0;
	int col_width_1;

	for (i=0; i<m_ColumnCount; i++)
	{
		if (i < m_ColumnCount - 1)
			col_width_1 = m_HdrList[i]->width;
		else
			col_width_1 = m_tblArea.width() - sum_width - SCROLL_WIDTH;

		col_width[i] = col_width_1/* - m_MarginLeft - m_MarginRight*/;
		sum_width += col_width_1;
	}

	int x = m_tblArea.left();
	int y = m_tblArea.top() + LISTHDR_HEIGHT;
	int w = sum_width - (m_LastColumnMerge ? col_width[m_ColumnCount-1] : 0);
	int h = m_tblArea.height();
	int y_offset;
	int x1, y1, w1, h1;
	int nColumnCnt = (m_LastColumnMerge ? m_ColumnCount - 1 : m_ColumnCount);

	m_nX = x; m_nY = y;

	int ei = MIN(m_nBaseIndex + m_nVisableCount + 1, m_RowCount);

	T_ITEM_A *row;

	p->save();

	y_offset = 0;
	for (i = m_nBaseIndex; i < ei; i++)
	{
		row = m_fnGetRowData((DWORD)i);
		if (!row)
			continue;

		int offset = 0;
		if (i == m_nCurrentIndex)
		{
			p->setBrush(*m_tblSelectedBkBrush);
			p->setPen(*m_tblSelectedForePen);
			p->fillRect(x, y + y_offset, w, m_RowHeight, *m_tblSelectedBkBrush);
		}
		else
		{
			p->setPen(*m_tblForePen);
		}

		y1 = y + y_offset + m_MarginTop;
		h1 = m_RowHeight - m_MarginTop - m_MarginBottom;

		for (int j=0; j<nColumnCnt; j++)
		{
			x1 = x + offset + m_MarginLeft;
			w1 = col_width[j] - m_MarginLeft - m_MarginRight;
			p->drawText(x1, y1, w1, h1, (int)m_HdrList[j]->dwParam, row[j].szValue);
 			offset += col_width[j];
		}
		y_offset += m_RowHeight;
	}

	if (m_GridUse)
	{
		y_offset = 0;
		p->setPen(*m_tblGridPen);
		if (m_GridUse & 0x01)
		{
			for (i=0; i<m_nVisableCount; i++)
			{
				y_offset += m_RowHeight;
				p->drawLine(x, y + y_offset, x + w, y + y_offset);
			}
		}
		if (m_GridUse & 0x02)
		{
			for (i=1; i<m_HdrList.count(); i++)
			{
				x += col_width[i - 1];
				p->drawLine(x, y, x, y + h);
			}
		}
	}

	p->restore();

	DELETE(col_width);
}

void SBTable::DrawScrollArea(QPainter *p)
{
	if (!m_ScrollUse)
		return;

	int x = m_tblArea.left() + m_tblArea.width() - SCROLL_WIDTH;
	int y = m_tblArea.top() + LISTHDR_HEIGHT;
	int w = SCROLL_WIDTH;
	int h = m_tblArea.height() - LISTHDR_HEIGHT;
	int h_scroll, h_scroll_1;

	QPixmap pmap_scrollBg(RESOURCE_PATH SCROLL_BG_FILENAME);
	QPixmap pmap_scrollItem(RESOURCE_PATH SCROLL_ITEM_FILENAME);

	m_scrollArea = QRect(x, y, w, h);
	h_scroll = 65536 * h / m_RowCount;
	h_scroll_1 = MAX(10, h_scroll / 65536);
	h_scroll = 65536 * (h - h_scroll_1) / m_RowCount;

	p->save();
	p->drawPixmap(x, y, w, h, pmap_scrollBg, 0, 0, pmap_scrollBg.width(), pmap_scrollBg.height());
	if (m_nCurrentIndex < m_RowCount - 1)
		p->drawPixmap(x, y + h_scroll*m_nCurrentIndex/65536, w, h_scroll_1,
			pmap_scrollItem, 0, 0, pmap_scrollItem.width(), pmap_scrollItem.height());
	else
		p->drawPixmap(x, y + h - h_scroll_1, w, h_scroll_1,
			pmap_scrollItem, 0, 0, pmap_scrollItem.width(), pmap_scrollItem.height());
	p->restore();
}

//////////////////////////////////////////////////////////////////////////
void SBTable::SBTableProc()
{
	int nKey;

	while (uiTimeIsTimeout() == FALSE)
	{
		POST_EVENTS();
		nKey = uiKeyGetKey();
		OnKeyPress(nKey);
	}

// _lExit:
	return;
}

void SBTable::OnKeyPress(int nKey)
{
	if (nKey == UIKEY_NONE)
		return;
	switch (nKey)
	{
	case UIKEY_UP:
		OnKeyUp();
		break;
	case UIKEY_DOWN:
		OnKeyDown();
		break;
// 	case UIKEY_F2:
// 		OnPageUp();
// 		break;
// 	case UIKEY_F4:
// 		OnPageDown();
// 			break;
	}
}

void SBTable::OnKeyUp()
{
	if (m_nCurrentIndex <= 0)
	{
		if (!m_RotateUse)
			return;
		SetCurrentIndex(m_RowCount - 1);
		m_nCurrentIndex++;
	}

	m_nCurrentIndex--;
	if (m_nCurrentIndex < m_nBaseIndex)
	{
		if (m_ContiniousScroll)
			m_nBaseIndex = MAX(m_nBaseIndex-1, 0);
		else
			m_nBaseIndex = MAX(m_nBaseIndex-m_nVisableCount+3, 0);
		UpdateTableArea(0, m_nVisableCount);
	}
	else
	{
		UpdateTableArea(m_nCurrentIndex - m_nBaseIndex, m_nCurrentIndex - m_nBaseIndex + 1);
	}

//	RedrawTable();
}

void SBTable::OnKeyDown()
{
	if (m_nCurrentIndex >= m_RowCount - 1)
	{
		if (!m_RotateUse)
			return;
		SetCurrentIndex(0);
		m_nCurrentIndex--;
	}

	m_nCurrentIndex++;
	
	if (m_fnGetRowData && !m_fnGetRowData(m_nCurrentIndex))
	{
		m_nCurrentIndex--;
		return;
	}

	if (m_nCurrentIndex >= m_nBaseIndex + m_nVisableCount)
	{
		if (m_ContiniousScroll)
			m_nBaseIndex = MIN(m_nBaseIndex+1, m_RowCount);
		else
			m_nBaseIndex = MIN(m_nBaseIndex+m_nVisableCount-3, m_RowCount);
		UpdateTableArea(0, m_nVisableCount);
	}
	else
	{
		UpdateTableArea(m_nCurrentIndex - m_nBaseIndex - 1, m_nCurrentIndex - m_nBaseIndex);
	}

//	RedrawTable();
//	UpdateTableArea();
}

void SBTable::OnPageUp()
{
	if (m_nCurrentIndex <= 0)
		return;
	if (m_nCurrentIndex > m_nBaseIndex)
		m_nCurrentIndex = m_nBaseIndex;
	else
		m_nCurrentIndex = m_nBaseIndex = MAX(m_nBaseIndex-m_nVisableCount, 0);

//	RedrawTable();
	UpdateTableArea(0, m_nVisableCount);
}

void SBTable::OnPageDown()
{
	if (m_nCurrentIndex >= m_RowCount - 1)
		return;
	if (m_RowCount < m_nVisableCount)
		m_nCurrentIndex = m_RowCount - 1;
	else
	if (m_nCurrentIndex < m_nBaseIndex + m_nVisableCount - 1)
		m_nCurrentIndex = MIN(m_RowCount, m_nBaseIndex + m_nVisableCount - 1);
	else
	{
		m_nBaseIndex = MIN(m_nBaseIndex + m_nVisableCount, m_RowCount - m_nVisableCount);
		m_nCurrentIndex = m_nBaseIndex + m_nVisableCount - 1;
	}

//	RedrawTable();
	UpdateTableArea(0, m_nVisableCount);
}

void SBTable::OnRedraw()
{
	UpdateTableArea(0, m_nVisableCount);
}

void SBTable::UpdateTableArea(int from, int to)
{
	if (to < from)
		return;

	int x = m_tblArea.left();
	int y = m_tblArea.top() + LISTHDR_HEIGHT;
	int w = m_tblArea.width() - SCROLL_WIDTH;
//	int h = m_tblArea.height() - LISTHDR_HEIGHT;

	QRegion rgn(x, y + from * m_RowHeight, w, (to - from + 1) * m_RowHeight);
	rgn += QRegion(m_scrollArea);
	update(rgn);
}
