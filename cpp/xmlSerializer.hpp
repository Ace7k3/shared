#pragma once

#include <stdexcept>
#include <string>
#include <list>
#include <stack>
#include <iostream>

namespace Shared
{

	class XmlSerializer 
	{
		public:
			typedef std::pair<std::string, std::string> Attribute;

			inline XmlSerializer(std::ostream& ostr)
				:_outputStream(ostr)
			{
				_outputStream << "<?xml version=\"1.0\" encoding=\"utf-8\"?>" << std::endl;
			}

			inline void BeginElement(const std::string elementName, const std::list<Attribute>& attributes = std::list<Attribute>(), bool isEmptyElement = false)
			{
				_outputStream << GetIndentation() << "<" << elementName;
				if(attributes.size() > 0)
				{
					for(auto iter = attributes.begin(); iter != attributes.end(); iter++){
						auto attr = *iter;
						_outputStream << " ";
						_outputStream << attr.first << "=\"" << attr.second << "\"";
					}
				}
				if(isEmptyElement){
					_outputStream << "/>" << std::endl;
				}else{
					_outputStream << ">" << std::endl;
					_elementStack.push(elementName);	
				}
			}

			inline void EndElement(const std::string elementName)
			{
				if(elementName != _elementStack.top())
					throw std::logic_error("Tried to close element '" + elementName +"', but last opened element was '"+_elementStack.top()+"'");

				_elementStack.pop();
				_outputStream << GetIndentation() << "</" << elementName << ">" << std::endl;
			}

			void WriteData(const std::string data)
			{
				_outputStream << GetIndentation() << data << std::endl;
			}

		private:
			std::ostream& _outputStream;
			std::stack<std::string> _elementStack;

			inline std::string GetIndentation() const
			{
				std::string rtn;
				for(unsigned i = 0; i < _elementStack.size(); i++)
					rtn += "\t";

				return rtn;
			}
	};






}
