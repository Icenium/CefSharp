#include "stdafx.h"

#include "IRenderWebBrowser.h"
#include "RenderClientAdapter.h"


namespace CefSharp
{
    void RenderClientAdapter::OnPopupShow(CefRefPtr<CefBrowser> browser, bool show)
    {
        _renderBrowserControl->SetPopupIsOpen(show);
    }

    void RenderClientAdapter::OnPopupSize(CefRefPtr<CefBrowser> browser, const CefRect& rect)
    {
        _renderBrowserControl->SetPopupSizeAndPosition(rect);
    }

    void RenderClientAdapter::OnPaint(CefRefPtr<CefBrowser> browser, PaintElementType type, const RectList& dirtyRects, const void* buffer)
    {
        if (type == PET_VIEW)
        {
            int width, height;
            browser->GetSize(type, width, height);

            _renderBrowserControl->SetBuffer(width, height, buffer);
        }
        else if (type == PET_POPUP)
        {
            int width, height;
            browser->GetSize(type, width, height);

            _renderBrowserControl->SetPopupBuffer(width, height, buffer);
        }
    }

    void RenderClientAdapter::OnCursorChange(CefRefPtr<CefBrowser> browser, CefCursorHandle cursor)
    {
        _renderBrowserControl->SetCursor(cursor);
    }

	bool RenderClientAdapter::GetScreenRect(CefRefPtr<CefBrowser> browser, CefRect& rect)
    {
		Console::WriteLine("GetScreenRect");
		return false;
    }
	bool RenderClientAdapter::GetScreenPoint(CefRefPtr<CefBrowser> browser,
                              int viewX,
                              int viewY,
                              int& screenX,
                              int& screenY)
    {
		Console::WriteLine("GetScreenPoint");
		return false;
    }
	bool RenderClientAdapter::GetViewRect(CefRefPtr<CefBrowser> browser,
                           CefRect& rect)
    {
		Console::WriteLine("GetViewRect");
		return false;
    }
}
