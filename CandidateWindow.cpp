
#include "Globals.h"
#include "TextService.h"
#include "CandidateWindow.h"

ATOM CCandidateWindow::_atomWndClass = 0;

CCandidateWindow *CandidateWindow = NULL;

CCandidateWindow::CCandidateWindow(){
    _hwnd = NULL;

	CandidateWindow = this;

	SetCurPage(0);
	SetPageLimit(6);
}

void CCandidateWindow::SetCurPage(int page){
	_curPage = page;
}

int CCandidateWindow::CurPage() const{
	return _curPage;
}

void CCandidateWindow::NextPage(){
	_curPage++;

	if(unsigned(_curPage * _pageLimit) >= _candidates.size()){
		_curPage--;
	}

	InvalidateRect(_hwnd, NULL, true);
}

void CCandidateWindow::PrevPage(){
	_curPage--;

	if(_curPage < 0){
		_curPage = 0;
	}

	InvalidateRect(_hwnd, NULL, true);
}

void CCandidateWindow::SetPageLimit(int limit){
	_pageLimit = limit;

	if(limit > 0){
		_windowWidth = 50 * limit;
		_windowHeight = 24;
	}
}

int CCandidateWindow::PageLimit() const{
	return _pageLimit;
}

void CCandidateWindow::SetCandidates(const wstring &list){
	_candidates = list;
}

wstring CCandidateWindow::Candidates() const{
	return _candidates;
}

/* static */
BOOL CCandidateWindow::_InitWindowClass()
{
    WNDCLASS wc;

    wc.style = 0;
    wc.lpfnWndProc = CCandidateWindow::_WindowProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = g_hInst;
    wc.hIcon = NULL;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = TEXT("TextServiceCandidateWindow");

    _atomWndClass = RegisterClass(&wc);

    return (_atomWndClass != 0);
}

/* static */
void CCandidateWindow::_UninitWindowClass()
{
    if (_atomWndClass != 0)
    {
        UnregisterClass((LPCTSTR)_atomWndClass, g_hInst);
    }
}

BOOL CCandidateWindow::_Create()
{
    _hwnd = CreateWindowEx(WS_EX_TOPMOST | WS_EX_TOOLWINDOW,
                           (LPCTSTR)_atomWndClass,
                           TEXT("TextService Candidate Window"),
                           WS_BORDER | WS_DISABLED | WS_POPUP,
                           0, 0,
                           _windowWidth, _windowHeight,
                           NULL,
                           NULL,
                           g_hInst,
                           this);

    return (_hwnd != NULL);
}

void CCandidateWindow::_Destroy()
{
    if (_hwnd != NULL)
    {
        DestroyWindow(_hwnd);
        _hwnd = NULL;
    }
}

void CCandidateWindow::_Move(int x, int y)
{
    if (_hwnd != NULL)
    {
        RECT rc;
        GetWindowRect(_hwnd, &rc);
        MoveWindow(_hwnd, x, y, rc.right - rc.left, rc.bottom - rc.top, TRUE);
    }
}

void CCandidateWindow::_Show()
{
    ShowWindow(_hwnd, SW_SHOWNA);
}

void CCandidateWindow::_Hide()
{
    ShowWindow(_hwnd, SW_HIDE);
}

HRESULT CCandidateWindow::_OnKeyDown(UINT uVKey){
    return S_OK;
}

HRESULT CCandidateWindow::_OnKeyUp(UINT uVKey){
	if(uVKey == VK_UP){
		PrevPage();
	}else if(uVKey == VK_DOWN){
		NextPage();
	}

    return S_OK;
}

/* static */
LRESULT CALLBACK CCandidateWindow::_WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    PAINTSTRUCT ps;

    switch (uMsg)
    {
        case WM_CREATE:
            _SetThis(hwnd, lParam);
            return 0;

        case WM_PAINT:
            hdc = BeginPaint(hwnd, &ps);
            SetBkMode(hdc, TRANSPARENT);
            
			int limit = CandidateWindow->PageLimit();
			wstring candidates = CandidateWindow->Candidates().substr(CandidateWindow->CurPage() * limit, limit);
			wstring text;
			for(int i = 0; i < CandidateWindow->PageLimit(); i++){
				if(unsigned(i) >= candidates.size()){
					break;
				}

				text += '1' + i;
				text += '.';
				text.append(candidates, i, 1);
				text += ' ';
			}

			HFONT font = CreateFont(20, 10, 0, 0, FW_THIN, false, false, false, DEFAULT_CHARSET, OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS, DEFAULT_QUALITY, FF_MODERN, "����");
			SelectObject(hdc, font);
			TextOutW(hdc, 0, 0, text.c_str(), text.size());
			DeleteObject(font);

			EndPaint(hwnd, &ps);
			
			return 0;
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
