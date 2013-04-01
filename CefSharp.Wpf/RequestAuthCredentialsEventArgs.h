using namespace System;
namespace CefSharp
{
	namespace Wpf
	{
		public ref class RequestAuthCredentialsEventArgs: public EventArgs
		{
		private:
			bool isProxy;
			String^ host;
			String^ realm;
			String^ username;
			String^ password;
			bool isSuccessful;
		public:
			RequestAuthCredentialsEventArgs(String^ host, bool isProxy, String^ realm){
				this->host = host;
				this->isProxy = isProxy;
				this->realm = realm;
			}

			virtual property bool IsProxy
			{
				bool get() { return isProxy; }
			}
			virtual property String^ Host
			{
				String^ get() { return host; }
			}
			virtual property String^ Realm
			{
				String^ get() { return realm; }
			}
			virtual property String^ Username
			{
				String^ get() { return username; }
				void set(String^ value) { username = value; }
			}
			virtual property String^ Password
			{
				String^ get() { return password; }
				void set(String^ value) { password = value; }
			}
			virtual property bool IsSuccessful
			{
				bool get() { return isSuccessful; }
				void set(bool value) { isSuccessful = value; }
			}
		};
	}
}