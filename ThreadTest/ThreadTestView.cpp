
// ThreadTestView.cpp : CThreadTestView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "ThreadTest.h"
#endif

#include "ThreadTestDoc.h"
#include "ThreadTestView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CThreadTestView

IMPLEMENT_DYNCREATE(CThreadTestView, CView)

BEGIN_MESSAGE_MAP(CThreadTestView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CThreadTestView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

// CThreadTestView 생성/소멸

CThreadTestView::CThreadTestView()
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CThreadTestView::~CThreadTestView()
{
}

BOOL CThreadTestView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CThreadTestView 그리기

void CThreadTestView::OnDraw(CDC* /*pDC*/)
{
	CThreadTestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}


// CThreadTestView 인쇄


void CThreadTestView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CThreadTestView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CThreadTestView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CThreadTestView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

void CThreadTestView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CThreadTestView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CThreadTestView 진단

#ifdef _DEBUG
void CThreadTestView::AssertValid() const
{
	CView::AssertValid();
}

void CThreadTestView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CThreadTestDoc* CThreadTestView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CThreadTestDoc)));
	return (CThreadTestDoc*)m_pDocument;
}
#endif //_DEBUG


// CThreadTestView 메시지 처리기

UINT ThreadFunc(LPVOID pParam)
{
	//LPVOID형을 UINT형으로 캐스팅
	UINT n = (UINT)pParam;

	UINT sum = 0;
	for(UINT i=1; i<n; i++){
		sum += i;
		//스레드로 동작하는 것을 확인하기 위해서
		//0.01초간 대기 시간을 둔다.
		Sleep(10);
	}

	//계산결과를 출력한다.
	CString str;
	str.Format(_T("계산결과= %d "), sum);
	AfxMessageBox(str);
	return 0;
}

void CThreadTestView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	UINT n=600;

	//스레드를 사용한 경우
	AfxBeginThread(ThreadFunc, (LPVOID)n );

	//스레드를 사용하지 않은 경우
	//ThreadFunc( (LPVOID) n );
	CView::OnLButtonDown(nFlags, point);
}
