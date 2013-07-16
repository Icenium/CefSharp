
#include "WebViewEx.h"
#include "DevToolsWebView.h"
#include "RenderClientAdapterEx.h"

namespace CefSharp
{
	namespace Wpf
	{
		void WebViewEx::Initialize(String^ address, BrowserSettings^ settings)
		{
			WebView::Initialize(address, settings);
			
			WebView::RequestHandler = this;
			WebView::JsDialogHandler = this;
		}
		
		CefRefPtr<RenderClientAdapter> WebViewEx::CreateClientAdapter()
		{
			if(!adapterInitialized)
			{
				adapterInitialized = true;
				CefRefPtr<RenderClientAdapter> newAdapter = new RenderClientAdapterEx(this);
				adapter = newAdapter .get();
			}
			return adapter.get();
		}
		bool WebViewEx::OnBeforeResourceLoad(IWebBrowser^ browserControl, IRequestResponse^ requestResponse)
		{
			OnRequestResource(browserControl, requestResponse);
			return false;
		}
		void WebViewEx::OnRequestResource(IWebBrowser^ browserControl, IRequestResponse^ requestResponse)
		{
			RequestResource(browserControl, requestResponse);
		}

		void WebViewEx::OnFrameLoadStart(String^ url)
		{
			WebView::OnFrameLoadStart(url);

			LoadStartedEventArgs^ args = gcnew LoadStartedEventArgs(url);
			LoadStarted(this, args);
		}

		IntPtr WebViewEx::GetMainWindowHandle()
		{	
			HwndSource^ source = (HwndSource^)PresentationSource::FromVisual(this);
			return source->Handle;
		}

		bool WebViewEx::PopupShowing(CefRefPtr<CefBrowser> parentBrowser,
			const CefPopupFeatures& popupFeatures, 
			CefWindowInfo& windowInfo,
			const CefString& url, 
			CefRefPtr<CefClient>& client,
			CefBrowserSettings& settings)
		{
			String^ urlString = toClr(url);
			if(showingDevTools && urlString->StartsWith("chrome-devtools://"))
			{
				settings.user_style_sheet_enabled = false;
				IntPtr mwHandle = (IntPtr)Dispatcher->Invoke( gcnew GetMainWindowHandleHandler(this, &WebViewEx::GetMainWindowHandle));
				if(mwHandle != IntPtr::Zero)
				{
					RECT rect;
					CefWindowInfo window;
       
					window.SetAsOffScreen(static_cast<HWND>(mwHandle.ToPointer()));
					windowInfo = window;
					DevToolsWebView^ devToolsView = (DevToolsWebView^)Dispatcher->Invoke( gcnew Func<DevToolsWebView^>(this, &WebViewEx::CreateDevToolsView)) ;
					CefRefPtr<RenderClientAdapter> clientAdapter = devToolsView->CreateClientAdapter();
					client = clientAdapter;
				}
			}			
			return false;
		}

		DevToolsWebView^ WebViewEx::CreateDevToolsView()
		{
			return gcnew DevToolsWebView(this);
		}
		void WebViewEx::OnShowDevTools(DevToolsWebView^ view)
		{
			showingDevTools = false;
			DevToolsShown(view);
		}

		void WebViewEx::ShowDevTools()
		{
			showingDevTools = true;
			WebView::ShowDevTools();
		}

		bool WebViewEx::GetAuthCredentials(IWebBrowser^ browser, bool isProxy, String^ host ,int port, String^ realm, String^ scheme, String^% username, String^% password)
		{
			return OnRequestAuthCredentials(browser, host, isProxy, realm, username, password);
		}

		bool WebViewEx::OnRequestAuthCredentials(IWebBrowser^ browserControl, String^ host, bool isProxy, String^ realm, String^% username, String^% password)
		{
			auto args = gcnew RequestAuthCredentialsEventArgs(host, isProxy, realm);
			RequestAuthCredentials(browserControl, args);
			username = args->Username;
			password = args->Password;
			return args->IsSuccessful;
		}

		bool WebViewEx::OnJSPrompt(IWebBrowser^ browser, String^ url, String^ message, String^ defaultValue, bool& retval,  String^% result)
		{
			auto args = gcnew JSPromptEventArgs(message, defaultValue);

			JSPromptHandler(args);

			retval = args->ReturnValue;
			result = args->Result;

			return args->Handled;
		}

		bool WebViewEx::TryEvaluateScript(String^ script, TimeSpan timeout, Object^% result)
		{
			try
			{
				result = EvaluateScript(script, timeout);

				return true;
			}
			catch (Exception^ ex)
			{
				return false;
			}
		}

        void WebViewEx::SimulateButtonClick(Point point, MouseButton mouseButton)
        {
            CefRefPtr<CefBrowser> browser;
            if (TryGetCefBrowser(browser))
            {
                CefBrowser::MouseButtonType type;
                if (mouseButton == MouseButton::Left)
                {
                    type = CefBrowser::MouseButtonType::MBT_LEFT;
                }
                else if (mouseButton == MouseButton::Middle)
                {
                    type = CefBrowser::MouseButtonType::MBT_MIDDLE;
                }
                else
                {
                    type = CefBrowser::MouseButtonType::MBT_RIGHT;
                }

                browser->SendMouseMoveEvent(point.X + Math::E, point.Y + Math::E, false);
                browser->SendMouseMoveEvent(point.X, point.Y, false);
                browser->SendMouseClickEvent(point.X, point.Y, CefBrowser::MouseButtonType::MBT_LEFT, false, 1);
                browser->SendMouseClickEvent(point.X, point.Y, CefBrowser::MouseButtonType::MBT_LEFT, true, 1);
            }
        }
    }
}
