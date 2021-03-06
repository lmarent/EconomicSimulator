//
// ClockServer.h
//
// Definition of the ClockServer class.
//
// Copyright (c) 2014, ChoiceNet Project.
// and Contributors.
//
// Permission is hereby granted, free of charge, to any person or organization
// obtaining a copy of the software and accompanying documentation covered by
// this license (the "Software") to use, reproduce, display, distribute,
// execute, and transmit the Software, and to prepare derivative works of the
// Software, and to permit third-parties to whom the Software is furnished to
// do so, all subject to the following:
// 
// The copyright notices in the Software and this entire statement, including
// the above license grant, this restriction and the following disclaimer,
// must be included in all copies of the Software, in whole or in part, and
// all derivative works of the Software, unless such copies or derivative
// works are solely in the form of machine-executable object code generated by
// a source language processor.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
// FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.
//

#ifndef ClockServer_INCLUDED
#define ClockServer_INCLUDED

#include <Poco/Util/ServerApplication.h>
#include <Poco/Util/Option.h>
#include <Poco/Util/OptionSet.h>
#include <Poco/Util/HelpFormatter.h>
#include <iostream>
#include "ClockSys.h"


namespace ChoiceNet
{

namespace Eco
{
	
	class ClockServer: public Poco::Util::ServerApplication
	{

	public:

		ClockServer();
		/// Creates an NetworkQualityServer using ...
		
		~ClockServer();
		/// Destroy the NetworkQualityServer

        ClockSys* getClockSubsystem();
        
	protected:	

		void initialize(Poco::Util::ServerApplication::Application& self);
		/// Initialize the procy with the corresponding application
		
		void uninitialize();
		
		void defineOptions(Poco::Util::OptionSet& options);
		/// Define the options for the Http Proxy
		
		void handleHelp(const std::string& name, 
						const std::string& value);
		/// Handles the options for executing the http proxy
		
		int main(const std::vector<std::string>& args);
		/// Put to execute the proxy servers with the configuration given

	private:
		bool _helpRequested;
		ClockSys *_clockSysPtr;
	};

} /// End Eco namespace

}  /// End ChoiceNet namespace

#endif // ClockServer_INCLUDE
