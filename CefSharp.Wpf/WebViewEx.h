#pragma once

#include "WebView.h"
#include "RequestAuthCredentialsEventArgs.h"
#include "JSPromptEventArgs.h"
#include "LoadStartedEventArgs.h"
using namespace System;
using namespace System::Net;
namespace CefSharp
{
	namespace Wpf
	{
		ref class DevToolsWebView;
		public delegate void RequestAuthCredentialsHandler(IWebBrowser^ browserControl,  RequestAuthCredentialsEventArgs^ args);
		public delegate void RequestResourceHandler(IWebBrowser^ browserControl, IRequestResponse^ requestResponse);

		public delegate void DevToolsShownHandler(DevToolsWebView^ view);
		public delegate void JSPromptHandler(JSPromptEventArgs^ args);

		public ref class WebViewEx : public WebView, IRequestHandler, IJsDialogHandler
		{
		private:
			bool showingDevTools;
			delegate void ActionHandler();
			
			delegate IntPtr GetMainWindowHandleHandler();
			IntPtr GetMainWindowHandle();
			DevToolsWebView^ CreateDevToolsView();
		protected:
			bool adapterInitialized;
			MCefRefPtr<RenderClientAdapter> adapter;
			virtual void Initialize(String^ address, BrowserSettings^ settings) override;
			virtual CefRefPtr<RenderClientAdapter> CreateClientAdapter() override;

		public:
			virtual event RequestAuthCredentialsHandler^ RequestAuthCredentials;
			virtual event RequestResourceHandler^ RequestResource;
			virtual event DevToolsShownHandler^ DevToolsShown;
			virtual event LoadStartedEventHandler^ LoadStarted;
			virtual event JSPromptHandler^ JSPromptHandler;

			WebViewEx() 
			{
								
			}
			
			WebViewEx(String^ address, BrowserSettings^ settings) : WebView(address,settings)
			{
			}

			virtual bool PopupShowing(CefRefPtr<CefBrowser> parentBrowser, const CefPopupFeatures& popupFeatures, CefWindowInfo& windowInfo, const CefString& url, CefRefPtr<CefClient>& client, CefBrowserSettings& settings);
			virtual void PopupShown(CefRefPtr<CefBrowser> browser) {};

			virtual  bool OnBeforeBrowse(IWebBrowser^ browser, IRequest^ request, NavigationType naigationvType, bool isRedirect){return false;};
			virtual bool OnBeforeResourceLoad(IWebBrowser^ browser, IRequestResponse^ requestResponse);
			virtual void OnResourceResponse(IWebBrowser^ browser, String^ url, int status, String^ statusText, String^ mimeType, WebHeaderCollection^ headers){};
			virtual bool GetAuthCredentials(IWebBrowser^ browser, bool isProxy, String^ host ,int port, String^ realm, String^ scheme, String^% username, String^% password);
		    virtual bool GetDownloadHandler(IWebBrowser^ browser, String^ mimeType, String^ fileName, Int64 contentLength, IDownloadHandler ^% handler){return false;};

			virtual void OnRequestResource(IWebBrowser^ browserControl, IRequestResponse^ requestResponse);
			virtual bool OnRequestAuthCredentials(IWebBrowser^ browserControl, String^ host, bool isProxy, String^ realm, String^% username, String^% password);
			virtual void OnShowDevTools(DevToolsWebView^ view);
			virtual void OnFrameLoadStart(String^ url) override;
			virtual void ShowDevTools() override;

			virtual bool OnJSAlert(IWebBrowser^ browser, String^ url, String^ message) { return false; };
			virtual bool OnJSConfirm(IWebBrowser^ browser, String^ url, String^ message, bool& retval) { return false; };
			virtual bool OnJSPrompt(IWebBrowser^ browser, String^ url, String^ message, String^ defaultValue, bool& retval,  String^% result);

			bool TryEvaluateScript(String^ script, TimeSpan timeout, Object^% result);
		};

	}
}
