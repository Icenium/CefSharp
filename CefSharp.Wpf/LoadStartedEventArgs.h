#include "stdafx.h"
#pragma once

using namespace System;

namespace CefSharp
{
	namespace Wpf
	{
		public ref class LoadStartedEventArgs : EventArgs
		{
			String^ _url;

		public:
			LoadStartedEventArgs(String^ url)
				: _url(url) {}

			property String^ Url { String^ get() { return _url; } }
		};

		public delegate void LoadStartedEventHandler(Object^ sender, LoadStartedEventArgs^ url);
	}
}