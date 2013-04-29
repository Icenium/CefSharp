using namespace System;

namespace CefSharp
{
  namespace Wpf
  {

	  public ref class JSPromptEventArgs : public EventArgs
	  {
	  private:
		  String^ message;
		  String^ defaultValue;
		  String^ result;
		  bool returnValue;
		  bool handled;

	  public:
		  JSPromptEventArgs(String^ message, String^ defaultValue){
			this->message = message;
			this->defaultValue = defaultValue;
		  }

		  virtual property String^ Message
		  {
			String^ get() { return message; }
		  }

		  virtual property String^ DefaultValue
		  {
			String^ get() { return defaultValue; }
		  }

		  virtual property String^ Result
		  {
			String^ get() { return result; }
			void set(String^ value) { result = value; }
		  }

		  virtual property bool ReturnValue
		  {
			bool get() { return returnValue; }
			void set(bool value) { returnValue = value; }
		  }

		  virtual property bool Handled
		  {
			bool get() { return handled; }
			void set(bool value) { handled = value;  }
		  }
	  };
  }
}
