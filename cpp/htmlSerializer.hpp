#pragma once

#include "xmlSerializer.hpp"
#include <vector>

namespace Shared
{
	class HtmlSerializer : public XmlSerializer 
	{
		public:

			inline HtmlSerializer(std::ostream& ostr, bool startEmpty = false)
				:XmlSerializer(ostr),
				_isClosed(false)
		{
			if(!startEmpty)
			{
				BeginElement("html");

				BeginElement("head");

				std::list<Attribute> bootstrap_css;
				bootstrap_css.push_back(Attribute("rel", "stylesheet"));
				bootstrap_css.push_back(Attribute("type", "text/css"));
				bootstrap_css.push_back(Attribute("href", "bootstrap.css"));
				BeginElement("link", bootstrap_css, true);

				std::list<Attribute> main_css;
				main_css.push_back(Attribute("rel", "stylesheet"));
				main_css.push_back(Attribute("type", "text/css"));
				main_css.push_back(Attribute("href", "main.css"));
				BeginElement("link", main_css, true);

				std::list<Attribute> jquery_js;
				jquery_js.push_back(Attribute("src", "jquery.js"));
				BeginElement("script", jquery_js);
				EndElement("script");

				std::list<Attribute> bootstrap_js;
				bootstrap_js.push_back(Attribute("src", "bootstrap.js"));
				BeginElement("script", bootstrap_js);
				EndElement("script");

				BeginElement("script");
				WriteData("$(function () {$('[data-toggle=\"popover\"]').popover() })");
				EndElement("script");

				EndElement("head");

				BeginElement("body");
			}
		}

			inline ~HtmlSerializer()
			{
				Close();
			}

			inline void WriteTable(std::vector< std::vector<std::string> > table)
			{
				std::list<Attribute> table_class;
				table_class.push_back(Attribute("class", "table table-striped"));

				BeginElement("p");
				BeginElement("table",table_class);

				for(unsigned iRow = 0; iRow < table.size(); iRow++){
					BeginElement("tr");
					for(unsigned iCol = 0; iCol < table[iRow].size(); iCol++)
					{
						if(iCol == 0 || iRow == 0){
							BeginElement("th");
							WriteData(table[iRow][iCol]);
							EndElement("th");				
						}else{
							BeginElement("td");
							WriteData(table[iRow][iCol]);
							EndElement("td");
						}
					}
					EndElement("tr");
				}

				EndElement("table");
				EndElement("p");
			}

			inline void WriteH1(std::string text)
			{
				BeginElement("h1");
				WriteData(text);
				EndElement("h1");
			}


			// <div class="panel panel-primary">
			// 		    <div class="panel-heading" role="tab" id="headingOne">
			// 		      <h4 class="panel-title">
			// 		        <a class="collapsed" role="button" data-toggle="collapse" data-parent="#accordion" href="#collapseOne" aria-expanded="true" aria-controls="collapseOne">
			// 		          (0.54353, -0.4535, 11.3939)
			// 		          <span class="pull-right">IsProjection: <span class="glyphicon glyphicon-ok"></span></span> &nbsp;
			// 		          <span class="pull-right" style="margin-right: 10px;">IsInSet: <span class="glyphicon glyphicon-ok"></span></span>&nbsp;
			// 		          <span class="pull-right" style="margin-right: 10px;">Converged: <span class="glyphicon glyphicon-ok"></span></span>
			// 		        </a>
			// 		      </h4>
			// 		    </div>

			// 		    <div id="collapseOne" class="panel-collapse collapse in" role="tabpanel" aria-labelledby="headingOne">
			// 		      <div class="panel-body">
			// 		        Anim pariatur cliche reprehenderit, enim eiusmod high life accusamus terry richardson ad squid. 3 wolf moon officia aute, non cupidatat skateboard dolor brunch. Food truck quinoa nesciunt laborum eiusmod. Brunch 3 wolf moon tempor, sunt aliqua put a bird on it squid single-origin coffee nulla assumenda shoreditch et. Nihil anim keffiyeh helvetica, craft beer labore wes anderson cred nesciunt sapiente ea proident. Ad vegan excepteur butcher vice lomo. Leggings occaecat craft beer farm-to-table, raw denim aesthetic synth nesciunt you probably haven't heard of them accusamus labore sustainable VHS.
			// 		      </div>
			// 		    </div>
			// 		  </div>
			inline void BeginPanel(std::string name, std::string title, std::string classes)
			{
				std::list<Attribute> panelAttr;
				panelAttr.push_back(Attribute("class", std::string("panel panel-")+classes));
				BeginElement("div",panelAttr);

				std::list<Attribute> panelHeadingAttr;
				panelHeadingAttr.push_back(Attribute("class", "panel-heading"));
				panelHeadingAttr.push_back(Attribute("role", "tab"));
				panelHeadingAttr.push_back(Attribute("id", std::string("heading") + name));
				BeginElement("div",panelHeadingAttr);

				std::list<Attribute> panelH4;
				panelH4.push_back(Attribute("class", "panel-title"));
				BeginElement("h4",panelH4);

				std::list<Attribute> AAttr;
				AAttr.push_back(Attribute("class", "collapsed"));
				AAttr.push_back(Attribute("role", "button"));
				AAttr.push_back(Attribute("data-toggle", "collapse"));
				AAttr.push_back(Attribute("data-parent", "#accordion"));
				AAttr.push_back(Attribute("href", std::string("#collapse")+name));
				AAttr.push_back(Attribute("aria-expanded", "true"));
				AAttr.push_back(Attribute("aria-controls", std::string("#collapse")+name));
				BeginElement("a",AAttr);
				WriteData(title);
				EndElement("a");

				EndElement("h4");
				EndElement("div");

				std::list<Attribute> contentAttr;
				contentAttr.push_back(Attribute("class", "panel-collapse collapse in"));
				contentAttr.push_back(Attribute("id", std::string("collapse")+name));
				contentAttr.push_back(Attribute("role", "tabpanel"));
				contentAttr.push_back(Attribute("aria-labelledby", std::string("heading")+name));
				BeginElement("div",contentAttr);

				std::list<Attribute> panelBodyAttr;
				panelBodyAttr.push_back(Attribute("class", "panel-body"));
				BeginElement("div",panelBodyAttr);	
			}

			inline void EndPanel()
			{
				EndElement("div");
				EndElement("div");
				EndElement("div");
			}

			inline void Close()
			{
				if(!_isClosed){
					_isClosed = true;
					EndElement("body");
				}
			}

		private:
			bool _isClosed;
	};

}
