/*
	grive: an GPL program to sync a local directory with Google Drive
	Copyright (C) 2013 Wan Wai Ho

	This program is free software; you can redistribute it and/or
	modify it under the terms of the GNU General Public License
	as published by the Free Software Foundation version 2
	of the License.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program; if not, write to the Free Software
	Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
	MA  02110-1301, USA.
*/

#include "MainWnd.hh"

#include <QtGui/QApplication>
#include <QtCore/QDebug>

#include "drive2/Drive.hh"

#include "http/CurlAgent.hh"
#include "http/Header.hh"
#include "protocol/JsonResponse.hh"

#include "protocol/Json.hh"
#include "protocol/OAuth2.hh"
#include "protocol/AuthAgent.hh"

#include "util/File.hh"

#include <string>
#include <iostream>

const std::string client_id		= "22314510474.apps.googleusercontent.com" ;
const std::string client_secret	= "bl4ufi89h-9MkFlypcI7R785" ;

using namespace gr ;
using namespace gr::v2 ;

int main( int argc, char **argv )
{
	File file( ".grive" ) ;
	Json cfg = Json::Parse( &file ) ;
	
	std::string refresh_token = cfg["refresh_token"].Str() ;
	qDebug() << refresh_token.c_str() ;
	
	OAuth2 token( refresh_token, client_id, client_secret ) ;
	AuthAgent agent( token, std::auto_ptr<http::Agent>( new http::CurlAgent ) ) ;
	
/*	Feed feed ;
	feed.Start( &agent, feed_base + "/-/folder?max-results=50&showroot=true" ) ;
	
	do
	{
		// first, get all collections from the query result
		for ( Feed::iterator i = feed.begin() ; i != feed.end() ; ++i )
		{
			Entry e( *i ) ;
			qDebug() << e.Name().c_str() ;
		}
	} while ( feed.GetNext( &agent ) ) ;
*/
/*	http::JsonResponse jsp ;
	agent.Get( "https://www.googleapis.com/drive/v2/files", &jsp, http::Header() ) ;
	std::cout << jsp.Response() << std::endl ;
*/
/*	Feed feed( "https://www.googleapis.com/drive/v2/files" ) ;
	while ( feed.Next(&agent) )
	{
		std::cout << feed.Content() << std::endl ;
	}
*/
//	Drive drive ;
//	drive.Refresh( &agent ) ;

	QApplication app( argc, argv ) ;
	MainWnd wnd( &agent ) ;
	wnd.show();
		
	return app.exec() ;
}
